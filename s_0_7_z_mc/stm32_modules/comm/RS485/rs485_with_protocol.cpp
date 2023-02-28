#include "rs485_with_protocol.h"

Rs485_with_protocol::Rs485_with_protocol(UART_HandleTypeDef *uart_handle, unsigned int buff_size, Gpio_if *ctrl_pin, uart_idle_callback callback)
    : RS485(uart_handle, buff_size, ctrl_pin,GPIO_HI, callback)
{
  prot = NULL;
  data_buffer = NULL;
}

void Rs485_with_protocol::set_protocol(Protocol *prot)
{
  this->prot = prot;
}

bool Rs485_with_protocol::send_data(unsigned char *data, unsigned int data_len)
{
  if (data == NULL || data_len == 0)
  {
    return false;
  }

  unsigned int buff_len = 0;

  if (prot != NULL)
  {
    data_buffer = new unsigned char[data_len + prot->prot_len()];
    if (data_buffer == NULL)
    {
      return false;
    }

    buff_len = prot->pack(data, data_len, data_buffer);
  }
  else
  {
    buff_len = data_len;
    data_buffer = data;
  }

  if (send(data_buffer, buff_len))
  {
    delete[] data_buffer;
    data_buffer = NULL;
    return true;
  }
  else
  {
    delete[] data_buffer;
    data_buffer = NULL;
    return false;
  }
}

unsigned int Rs485_with_protocol::read_data(unsigned char *data)
{
  unsigned int read_cnt = data_available();
  if (read_cnt == 0)
  {
    return 0;
  }

  data_buffer = new unsigned char[read_cnt];
  if (data_buffer == NULL)
  {
    return 0;
  }

  read_cnt = read_all(data_buffer);
  if (read_cnt == 0)
  {
    delete[] data_buffer;
    data_buffer = NULL;
    return 0;
  }
  
  if( prot != NULL )
  {
    read_cnt = prot->unpack(data_buffer, read_cnt, data_buffer);
  }
  
  if (read_cnt != 0)
  {
    memcpy(data, data_buffer, read_cnt);
  }
  else
  {
    read_cnt = 0;
  }

  delete[] data_buffer;
  data_buffer = NULL;
  
  return read_cnt;
}

Rs485_with_protocol::~Rs485_with_protocol()
{
}
