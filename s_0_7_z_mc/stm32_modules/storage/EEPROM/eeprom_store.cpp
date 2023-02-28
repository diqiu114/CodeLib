#include "eeprom_store.h"
#include <string.h>

Eeprom_store::Eeprom_store(void)
{
  var_cnt = NB_OF_VAR;
}


void Eeprom_store::set_addr(Virt_addr *virtual_addr, unsigned int addr_cnt, unsigned int addr_idx)
{
  if ((addr_cnt + addr_idx) >= var_cnt)
  {
    addr_cnt = var_cnt - addr_idx - 1;
  }

  memcpy(&VirtAddVarTab[0] + addr_idx, virtual_addr, addr_cnt * sizeof(Virt_addr));
}

Eeprom_store::Eeprom_store(Virt_addr *virtual_addr, unsigned int addr_cnt, unsigned int addr_idx)
{
  var_cnt = NB_OF_VAR;

  if ((addr_cnt + addr_idx) >= var_cnt)
  {
    addr_cnt = var_cnt - addr_idx - 1;
  }

  memcpy(&VirtAddVarTab[0] + addr_idx, virtual_addr, addr_cnt * sizeof(Virt_addr));
}

bool Eeprom_store::init(void)
{
  if (EE_Init() == HAL_OK)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Eeprom_store::read(unsigned short addr, unsigned short *data, unsigned int data_cnt)
{
  if ((data == NULL) || (data_cnt == 0))
  {
    return false;
  }

  bool ret = true;

  if (addr_valid(addr))
  {
    unsigned short r_result = 0;

    HAL_FLASH_Unlock();

    for (int i = 0; i < data_cnt; i++)
    {
      r_result = EE_ReadVariable(addr, data);
      
      addr += sizeof(unsigned short);
      data++;

      if (r_result != 0)
      {
        ret = false;
        break;
      }
    }

    HAL_FLASH_Lock();
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool Eeprom_store::write(unsigned short addr, unsigned short *data, unsigned int data_cnt)
{
  if ((data == NULL) || (data_cnt == 0))
  {
    return false;
  }

  bool ret = true;

  if (addr_valid(addr))
  {
    unsigned short *w_data = data;
    unsigned short w_result = 0;

    HAL_FLASH_Unlock();

    for (int i = 0; i < data_cnt; i++)
    {
      w_result = EE_WriteVariable(addr, (unsigned short)(*w_data));
      addr += sizeof(unsigned short);
      w_data++;

      if (w_result != 0)
      {
        ret = false;
        break;
      }
    }

    HAL_FLASH_Lock();
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool Eeprom_store::addr_valid(unsigned short addr)
{
  bool ret = false;
  int i = 0;

  for (i = 0; i < var_cnt; i++)
  {
    if (VirtAddVarTab[i].addr == addr)
    {
      ret = true;
      break;
    }
  }

  return ret;
}

Eeprom_store::~Eeprom_store()
{
}
