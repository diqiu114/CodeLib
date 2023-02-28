#include "cell_comm.h"
#include "dfs_proto.h"

Cell_comm::Cell_comm(UART_HandleTypeDef* uart_handle, unsigned int buff_size,  Gpio_if *ctrl_pin,uart_idle_callback callback ):Rs485_with_protocol(uart_handle,buff_size,ctrl_pin,callback)
{
  prot = new DFS_proto();
  set_protocol(prot);
#if (USE_FREE_RTOS)
  rev_queue = NULL;
#endif
  rev_delay = CELL_DEFAULT_REV_DELAY;
  send_buff = NULL;
}

#if (USE_FREE_RTOS)
void Cell_comm::set_queue_handle(QueueHandle_t handle)
{
  rev_queue = handle;
}
#endif

unsigned int Cell_comm::read_sw(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_SOFT_VER, cell_id, NULL, 0, rev_buff);
}

unsigned int Cell_comm::read_polynomial_val(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_POLYNOMIAL_CALIB_VAL, cell_id, NULL, 0, rev_buff);
}

unsigned int Cell_comm::read_volt(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_VOLT, cell_id, NULL, 0, rev_buff);
}

//unsigned int Cell_comm::read_res(unsigned char cell_id, unsigned char *rev_buff)
//{
//  return send_data_to_cell(CELL_READ_RES, cell_id, NULL, 0, rev_buff);
//}

unsigned int Cell_comm::read_temp(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_TEMP, cell_id, NULL, 0, rev_buff);
}

unsigned int Cell_comm::read_volt_and_temp(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_VOLT_AND_TEMP, cell_id, NULL, 0, rev_buff);
}

unsigned int Cell_comm::read_all_data(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_ALL, cell_id, NULL, 0, rev_buff);
}

unsigned int Cell_comm::read_all_and_calib(unsigned char cell_id, unsigned char *rev_buff)
{
  return send_data_to_cell(CELL_READ_ALL_AND_CALIB_VAL, cell_id, NULL, 0, rev_buff);
}

unsigned int Cell_comm::write_polynomial_val(unsigned char cell_id, unsigned char *data_buff, unsigned data_len)
{
  return send_data_to_cell(CELL_WRITE_POLYNOMIAL_CALIB_VAL, cell_id, data_buff, data_len, NULL);
}

unsigned int Cell_comm::volt_calib(unsigned char cell_id, unsigned char *data_buff, unsigned data_len)
{
  return send_data_to_cell(CELL_CALIB_VOLT, cell_id, data_buff, data_len, NULL);
}

//unsigned int Cell_comm::res_calib(unsigned char cell_id, unsigned char *data_buff, unsigned data_len)
//{
//  return send_data_to_cell(CELL_CALIB_RES, cell_id, data_buff, data_len, NULL);
//}

unsigned int Cell_comm::temp_calib(unsigned char cell_id, unsigned char *data_buff, unsigned data_len)
{
  return send_data_to_cell(CELL_CALIB_TEMP, cell_id, data_buff, data_len, NULL);
}

unsigned int Cell_comm::modify_id(unsigned char cell_id, unsigned char *data_buff, unsigned data_len)
{
  return send_data_to_cell(CELL_MODIFY_ID, cell_id, data_buff, data_len, NULL);
}

unsigned int Cell_comm::reset_calib(unsigned char cell_id)
{
  return send_data_to_cell(CELL_CALIB_TEMP, cell_id, NULL, 0, NULL);
}

unsigned int Cell_comm::program_upgrade(unsigned char cell_id)
{
  return send_data_to_cell(CELL_PROGRAM_UPGRADE, cell_id, NULL, 0, NULL);
}

unsigned int Cell_comm::transparent(unsigned char *data, unsigned int data_len, bool resp, unsigned char *rev_buff)
{
  unsigned int ret = 0;

  if( resp )
  {
    ret = send_data_to_cell((Cell_cmd)data[0], data[1], data+2, data_len - 2, rev_buff);
  }
  else
  {
    send_data_to_cell((Cell_cmd)data[0], data[1], data+2, data_len - 2);
  }
  
  return ret;
}

unsigned int Cell_comm::send_data_to_cell(Cell_cmd cmd, unsigned char cell_id, unsigned char *data,
                                          unsigned int data_len, unsigned char *rev_data)
{
  unsigned int pack_len = sizeof(cmd) + sizeof(cell_id) + data_len + prot->prot_len();
  unsigned char *buffer = new unsigned char[pack_len];
  if (buffer == NULL)
  {
    return 0;
  }

  unsigned int idx = 0;
  buffer[idx++] = cmd;
  buffer[idx++] = cell_id;

  if ((data_len != 0) && (data != NULL))
  {
    memcpy(buffer + idx, data, data_len);
  }
  idx += data_len;

  unsigned int send_len = prot->pack(buffer, idx, buffer);

  bool send_ok = send_data(buffer, send_len);

  delete[] buffer;
  buffer = NULL;

  if ( (!send_ok) || (rev_data == NULL) )
  {
    return 0;
  }

  // get response data
  if (received_data(rev_delay))
  {
    unsigned int data_len = unpack_buff_data(cmd, cell_id, rev_data);
    return data_len;
  }
  else
  {
    return 0;
  }
}

void Cell_comm::set_rev_timeout(unsigned int m_seconds)
{
  rev_delay = m_seconds;
}

unsigned int Cell_comm::get_rev_timeout(void)
{
  return rev_delay;
}

unsigned int Cell_comm::unpack_buff_data(Cell_cmd cmd, unsigned char cell_id, unsigned char *data)
{
  unsigned int rev_data_len = data_available();
  if (rev_data_len == 0)
  {
    return 0;
  }

  unsigned char *buffer = new unsigned char[rev_data_len];
  if (buffer == NULL)
  {
    return 0;
  }

  memset(buffer, 0, rev_data_len);
  rev_data_len = read_data(buffer);

  unsigned int data_len = prot->unpack(buffer, rev_data_len, buffer);
  if ((data_len != 0) && (buffer[CELL_CMD_IDX] == cmd) && buffer[CELL_ID_IDX] == cell_id)
  {
    memcpy(data, buffer + CELL_DATA_IDX, data_len - CELL_DATA_IDX);
    data_len -= CELL_DATA_IDX;
  }

  delete[] buffer;

  return data_len;
}

bool Cell_comm::received_data(int timeout)
{
  bool ret = true;

#if (USE_FREE_RTOS)
  if (rev_queue != NULL)
  {
    unsigned char data = 0;
    if (xQueueReceive(rev_queue, &data, timeout))
    {
      ret = true;
    }
    else
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }
#else
  while (data_cnt() == 0)
  {
    timeout--;
    if (timeout <= 0)
    {
      ret = false;
      break;
    }
    DELAY_MS(1);
  }
#endif

  DELAY_MS(1);
  return ret;
}

Cell_comm::~Cell_comm()
{
}
