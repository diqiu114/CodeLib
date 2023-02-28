#include "modbus_slave.h"
#include "string.h"

#define BOARDCAST_ID (0)

Modbus_slave::Modbus_slave(unsigned char _id, Modbus_reg_bank *_reg_bank)
{
  id = _id;
  reg_bank = _reg_bank;
  cmd = 0;
  reg_addr = 0;
  reg_val = 0;
  write_callback = NULL;
  reg_data_buff = NULL;
}

Modbus_slave::~Modbus_slave()
{
  if (reg_bank != NULL)
  {
    delete reg_bank;
    reg_bank = NULL;
  }
}

void Modbus_slave::set_id(unsigned char _id)
{
  id = _id;
}

unsigned char Modbus_slave::get_id(void)
{
  return id;
}

void Modbus_slave::set_reg_bank(Modbus_reg_bank *_reg_bank)
{
  reg_bank = _reg_bank;
}

Modbus_reg_bank *Modbus_slave::get_reg_bank(void)
{
  return reg_bank;
}

void Modbus_slave::set_reg_write_callback(Reg_write_callback _func)
{
  write_callback = _func;
}

void Modbus_slave::set_reg_read_callback(Reg_read_callback _func)
{
  read_callback = _func;
}

int Modbus_slave::process(char *data, short data_cnt, char *ret_data)
{
  unsigned short crc = 0;

  // id check
  if ((data[0] != id && data[0] != BOARDCAST_ID) || (data_cnt <= sizeof(crc)))
  {
    return 0;
  }

  // crc check
  crc = crc16(data, data_cnt - sizeof(crc));
  if (crc != ((data[data_cnt - 2] << 8) | data[data_cnt - 1]))
  {
    return 0;
  }

  // switch command
  cmd = Modbus_cmd(data[1]);
  reg_addr = (data[2] << 8) | data[3];
  reg_val = (data[4] << 8) | data[5];

  unsigned int reg_data_len = 0;

  switch (cmd)
  {
  case READ_DO:
    reg_data_len = get_digi_reg_val(reg_addr, reg_val);
    break;

  case READ_DI:
    reg_addr += MODBUS_DI_REG_ADDR_START;
    reg_data_len = get_digi_reg_val(reg_addr, reg_val);
    break;

  case READ_AO:
    reg_addr += MODBUS_AO_REG_ADDR_START;
    reg_data_len = get_analog_reg_val(reg_addr, reg_val);
    break;

  case READ_AI:
    reg_addr += MODBUS_AI_REG_ADDR_START;
    reg_data_len = get_analog_reg_val(reg_addr, reg_val);
    break;

  case WRITE_DO:
    reg_data_len = set_digi_reg_val(reg_addr, reg_val);
    break;

  case WRITE_AO:
    reg_addr += MODBUS_AO_REG_ADDR_START;
    reg_data_len = set_analog_reg_val(reg_addr, reg_val);
    break;

  default:
    break;
  }

  unsigned int idx = 0;

  // fill return data
  if (reg_data_len != 0)
  {
    if ((cmd == WRITE_DO) || (cmd == WRITE_AO))
    {
      ret_data[idx++] = id;
      ret_data[idx++] = cmd;
      ret_data[idx++] = data[2];
      ret_data[idx++] = data[3];
    }
    else
    {
      ret_data[idx++] = id;
      ret_data[idx++] = cmd;
      ret_data[idx++] = reg_data_len;
    }

    memcpy(ret_data + idx, reg_data_buff, reg_data_len);

    delete[] reg_data_buff;
    reg_data_buff = NULL;

    idx += reg_data_len;

    unsigned short crc = crc16(ret_data, idx);
    ret_data[idx++] = (unsigned char)(crc >> 8);
    ret_data[idx++] = (unsigned char)(crc);
  }

  return idx;
}

unsigned int Modbus_slave::get_analog_reg_val(int reg_addr, int reg_cnt)
{
  if (reg_cnt > ANALOG_REG_WR_MAX)
  {
    return 0;
  }

  unsigned int reg_buff_len = reg_cnt * 2;

  reg_data_buff = new char[reg_buff_len];
  if (reg_data_buff != NULL)
  {
    memset(reg_data_buff, 0, reg_buff_len);
  }
  else
  {
    return 0;
  }

  unsigned short reg_val = 0;

  int offset = 0;

  for (int i = 0; i < reg_cnt; i++)
  {
    if (read_callback != NULL)
    {
      read_callback(reg_addr + i, id);
    }

    reg_val = reg_bank->get_analog_reg_val(reg_addr + i);
    reg_data_buff[offset++] = (char)(reg_val >> 8);
    reg_data_buff[offset++] = (char)(reg_val);
  }

  return reg_buff_len;
}

unsigned int Modbus_slave::get_digi_reg_val(int reg_addr, int reg_cnt)
{
  if (reg_cnt > DIGI_REG_WR_MAX)
  {
    return 0;
  }

  unsigned int reg_buff_len = reg_cnt / 8;

  if ((reg_cnt % 8) != 0)
  {
    reg_buff_len += 1;
  }

  reg_data_buff = new char[reg_buff_len];
  if (reg_data_buff != NULL)
  {
    memset(reg_data_buff, 0, reg_buff_len);
  }
  else
  {
    return 0;
  }

  unsigned int reg_offset = 0;
  unsigned char bitn = 0;

  for (int i = 0; i < reg_cnt; i++)
  {
    if (read_callback != NULL)
    {
      read_callback(reg_addr + i, id);
    }

    if (reg_bank->get_digi_reg_val(reg_addr + i) != 0)
    {
      set_bit(reg_data_buff[reg_offset], bitn);
    }
    else
    {
      clear_bit(reg_data_buff[reg_offset], bitn);
    }

    ++bitn;

    if (bitn >= 8)
    {
      bitn = 0;
      ++reg_offset;
    }
  }

  return reg_buff_len;
}

unsigned int Modbus_slave::set_digi_reg_val(unsigned short reg_addr, short reg_val)
{
  bool status = true;

  if (write_callback != NULL)
  {
    status = write_callback(reg_addr, reg_val, id);
  }

  if (status && reg_bank->set_digi_reg_val(reg_addr, reg_val))
  {
    unsigned int reg_buff_len = sizeof(reg_val);

    reg_data_buff = new char[reg_buff_len];
    if (reg_data_buff != NULL)
    {
      memset(reg_data_buff, 0, reg_buff_len);
    }
    else
    {
      return 0;
    }

    reg_data_buff[0] = (unsigned char)(reg_val >> 8);
    reg_data_buff[1] = (unsigned char)(reg_val);

    return reg_buff_len;
  }
  else
  {
    return 0;
  }
}

unsigned int Modbus_slave::set_analog_reg_val(unsigned short reg_addr, short reg_val)
{
  bool status = true;

  if (write_callback != NULL)
  {
    status = write_callback(reg_addr, reg_val, id);
  }

  if (status && reg_bank->set_analog_reg_val(reg_addr, reg_val))
  {
    unsigned int reg_buff_len = sizeof(reg_val);

    reg_data_buff = new char[reg_buff_len];
    if (reg_data_buff != NULL)
    {
      memset(reg_data_buff, 0, reg_buff_len);
    }
    else
    {
      return 0;
    }

    reg_data_buff[0] = (unsigned char)(reg_val >> 8);
    reg_data_buff[1] = (unsigned char)(reg_val);

    return reg_buff_len;
  }
  else
  {
    return 0;
  }
}

void Modbus_slave::set_bit(char &data, char bit)
{
  data |= (1 << bit);
}

void Modbus_slave::clear_bit(char &data, char bit)
{
  data &= ~(1 << bit);
}

unsigned short Modbus_slave::crc16(char *data, int data_len)
{
  char hi = 0xFF;
  char low = 0xFF;
  unsigned int idx = 0;
  if (data_len <= 0)
  {
    return 0;
  }

  while (data_len--)
  {
    idx = hi ^ *data++;
    hi = low ^ CRC_HI_TABLE[idx];
    low = CRC_LOW_TABLE[idx];
  }

  return (hi << 8) | low;
}
