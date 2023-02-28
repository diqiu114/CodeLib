#include "eeprom_flag.h"

Eeprom_flag::Eeprom_flag(Flag_t flag, unsigned int addr_idx) : Eeprom_store()
{
  this->flag = flag;

  set_addr(&this->flag.v_addr, FLAG_ADDR_CNT, addr_idx);
}




bool Eeprom_flag::check_reset_val(void)
{
  bool ret = false;
  unsigned short read_val = 0;
  
  if (read(flag.v_addr.addr, &read_val, FLAG_ADDR_CNT))
  {
    if (read_val == flag.reset_val)
    {
      ret = true;
    }
    else
    {
      if (write_reset_val())
      {
        ret = true;
      }
    }
  }

  return ret;
}

bool Eeprom_flag::flag_set(void)
{
  bool ret = false;
  unsigned short read_val = 0;
  
  if (read(flag.v_addr.addr, &read_val, FLAG_ADDR_CNT))
  {
    if (read_val == flag.set_val)
    {
      ret = true;
    }
  }

  return ret;
}

bool Eeprom_flag::write_set_val(void)
{
  return write(flag.v_addr.addr, &flag.set_val, FLAG_ADDR_CNT);
}



bool Eeprom_flag::write_reset_val(void)
{
  return write(flag.v_addr.addr, &flag.reset_val, FLAG_ADDR_CNT);
}

Eeprom_flag::~Eeprom_flag()
{
}
