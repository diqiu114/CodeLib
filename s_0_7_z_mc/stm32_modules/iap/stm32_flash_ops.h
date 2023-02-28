/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      flash操作接口类
*
***********************************************************/
#ifndef _STM32_FLASH_OPS_H_
#define _STM32_FLASH_OPS_H_

#include "flash_ops_if.h"

class Stm32_flash_ops : public Flash_ops_if
{
public:
  Stm32_flash_ops(unsigned int _start_addr, unsigned int _flash_size);
  virtual ~Stm32_flash_ops();

  virtual unsigned int erase(unsigned int start_address, unsigned int end_address);
  virtual unsigned int write(unsigned int dest_addr, unsigned int *data, unsigned int data_len);
  virtual unsigned int get_protection_config(void);
  virtual unsigned int get_protection_config(unsigned int state);

  virtual unsigned int get_start_addr(void);
  virtual unsigned int get_flash_size(void);

private:
  unsigned int start_addr;
  unsigned int flash_size;
};

#endif //_FLASH_IF_H_
