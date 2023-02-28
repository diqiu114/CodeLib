#include "stm32_flash_ops.h"

#if defined STM32F407xx || STM32F427xx
#include "flash_if_f407x.h"
#elif (STM32F103xB)
#include "flash_if_f103x.h"
#elif defined(STM32F030xC)
#include "flash_if_f030x.h"
#endif

Stm32_flash_ops::Stm32_flash_ops(unsigned int _start_addr, unsigned int _flash_size)
{
  start_addr = _start_addr;
  flash_size = _flash_size;
}

Stm32_flash_ops::~Stm32_flash_ops()
{
}

unsigned int Stm32_flash_ops::erase(unsigned int start_address, unsigned int end_address)
{
  return FLASH_If_Erase(start_addr, start_addr+flash_size);
}

unsigned int Stm32_flash_ops::write(unsigned int dest_addr, unsigned int *data, unsigned int data_len)
{
  return FLASH_If_Write(dest_addr, data, data_len);
}

unsigned int Stm32_flash_ops::get_protection_config(void)
{
  return FLASH_If_GetWriteProtectionStatus();
}

unsigned int Stm32_flash_ops::get_protection_config(unsigned int state)
{
  return FLASH_If_WriteProtectionConfig(state);
}

unsigned int Stm32_flash_ops::get_start_addr(void)
{
  return start_addr;
}

unsigned int Stm32_flash_ops::get_flash_size(void)
{
  return flash_size;
}

