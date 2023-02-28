/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      EEPROM存储类
*
* 版本:
* V1.3 2019-06-13 设置地址时增加地址索引，避免存储只能实例化一个对象的BUG
* V1.2 2019-05-12 将地址结构体名称修改为Virt_addr, 增加默认构造函数与set_addr函数
* V1.1 2019-03-15 将地址修改为地址结构体 Quanfa
* V1.0 2018-11-09 初始版本程序编写
***********************************************************/

#ifndef _EEPROM_STORE_H_
#define _EEPROM_STORE_H_

#include <stdbool.h>
#include "storage\storage.h"
#if defined(STM32F427xx) || defined(STM32F407xx)
#include "eeprom_f4xx.h"
#elif (STM32F030x8)
#include "eeprom_f0xx.h"
#elif (STM32F103xB || STM32F103xE)
#include "eeprom_f1xx.h"
#elif defined(STM32F030xC)
#include "eeprom_f0xx.h"
#endif

extern Virt_addr VirtAddVarTab[NB_OF_VAR];

class Eeprom_store : public Storage
{
public:
  Eeprom_store();
  Eeprom_store(Virt_addr *virtual_addr, unsigned int addr_cnt, unsigned int addr_idx);
  void set_addr(Virt_addr *virtual_addr, unsigned int addr_cnt, unsigned int addr_idx);
  virtual bool init(void);
  virtual bool read(unsigned short addr, unsigned short *data, unsigned int data_cnt);
  virtual bool write(unsigned short addr, unsigned short *data, unsigned int data_cnt);

  ~Eeprom_store();

private:
  bool addr_valid(unsigned short addr);

  unsigned int var_cnt;
};

#endif // _EEPROM_STORE_H_
