/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      flash操作接口类
*
***********************************************************/
#ifndef _FLASH_OPS_IF_H_
#define _FLASH_OPS_IF_H_

class Flash_ops_if
{
public:
  virtual unsigned int erase(unsigned int start_address, unsigned int end_address) = 0;
  virtual unsigned int write(unsigned int destination, unsigned int *p_source, unsigned int length) = 0;
  virtual unsigned int get_protection_config(void) = 0;
  virtual unsigned int get_protection_config(unsigned int protectionstate) = 0;

  virtual unsigned int get_start_addr(void) = 0;
  virtual unsigned int get_flash_size(void) = 0;

  virtual ~Flash_ops_if(){};
};

#endif //_FLASH_IF_H_
