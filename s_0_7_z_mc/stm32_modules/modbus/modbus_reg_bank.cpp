#include "modbus_reg_bank.h"

Modbus_reg_bank::Modbus_reg_bank()
{
}

Modbus_reg_bank::~Modbus_reg_bank()
{
}

bool Modbus_reg_bank::add_analog_reg(unsigned short addr, short val)
{
  if ((addr < MODBUS_AI_REG_ADDR_START) || (MODBUS_AO_REG_ADDR_END < addr))
  {
    return false;
  }

  analog_reg.push_back(Modbus_analog_reg(addr, val));

  return true;
}

bool Modbus_reg_bank::add_analog_reg(Modbus_analog_reg &reg)
{
  if ((reg.addr < MODBUS_AI_REG_ADDR_START) || (MODBUS_AO_REG_ADDR_END < reg.addr))
  {
    return false;
  }

  analog_reg.push_back(reg);

  return true;
}

bool Modbus_reg_bank::add_digi_reg(unsigned short addr, char val)
{
  if (addr > MODBUS_DI_REG_ADDR_END)
  {
    return false;
  }

  digi_reg.push_back(Modbus_digi_reg(addr, val));

  return true;
}

bool Modbus_reg_bank::add_digi_reg(Modbus_digi_reg &reg)
{
  if (reg.addr > MODBUS_DI_REG_ADDR_END)
  {
    return false;
  }

  digi_reg.push_back(reg);

  return true;
}

char Modbus_reg_bank::get_digi_reg_val(unsigned short addr)
{
  if (addr > MODBUS_DI_REG_ADDR_END)
  {
    return 0;
  }

  if (digi_reg.empty())
  {
    return 0;
  }

  char ret = 0;

  list<Modbus_digi_reg>::iterator iter;
  for (iter = digi_reg.begin(); iter != digi_reg.end(); iter++)
  {
    if (addr == iter->addr)
    {
      ret = iter->val;
      break;
    }
  }

  return ret;
}

short Modbus_reg_bank::get_analog_reg_val(unsigned short addr)
{
  if ((addr < MODBUS_AI_REG_ADDR_START) || (MODBUS_AO_REG_ADDR_END < addr))
  {
    return 0;
  }

  if (analog_reg.empty())
  {
    return 0;
  }

  short ret = 0;

  list<Modbus_analog_reg>::iterator iter;
  for (iter = analog_reg.begin(); iter != analog_reg.end(); iter++)
  {
    if (addr == iter->addr)
    {
      ret = iter->val;
      break;
    }
  }

  return ret;
}

bool Modbus_reg_bank::set_analog_reg_val(unsigned short addr, short val)
{
  if ((addr < MODBUS_AI_REG_ADDR_START) || (MODBUS_AO_REG_ADDR_END < addr))
  {
    return false;
  }

  if (analog_reg.empty())
  {
    return false;
  }

  bool ret = false;

  list<Modbus_analog_reg>::iterator iter;
  for (iter = analog_reg.begin(); iter != analog_reg.end(); iter++)
  {
    if (addr == iter->addr)
    {
      iter->val = val;
      ret = true;
      break;
    }
  }

  return ret;
}

bool Modbus_reg_bank::set_digi_reg_val(unsigned short addr, unsigned short val)
{
  if (addr > MODBUS_DI_REG_ADDR_END)
  {
    return false;
  }

  if (digi_reg.empty())
  {
    return false;
  }

  bool ret = false;

  list<Modbus_digi_reg>::iterator iter;
  for (iter = digi_reg.begin(); iter != digi_reg.end(); iter++)
  {
    if (addr == iter->addr)
    {
      if (val > 0)
      {
        iter->val = 0xFF;
      }
      else
      {
        iter->val = 0x00;
      }

      ret = true;
      break;
    }
  }

  return ret;
}
