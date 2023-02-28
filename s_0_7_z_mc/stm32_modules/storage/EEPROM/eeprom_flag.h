/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      EEPROM 标志位类
*             用于在EEPROM的虚拟地址中写入一个值，对这个地址的值进行读写判断
*             可用作IAP标志，NAND FLASH格式化标志等
*
* 版本:
* V1.0 2010-06-13 初始版本程序编写， 由Upgrade类改写。 
***********************************************************/

#ifndef _EEPROM_FLAG_H_
#define _EEPROM_FLAG_H_

#include <stdbool.h>
#include "eeprom_store.h"

#define FLAG_ADDR_CNT (1)

typedef struct _tag_flag_t_
{
  Virt_addr v_addr;
  unsigned short set_val;
  unsigned short reset_val;
}Flag_t;

class Eeprom_flag : public Eeprom_store
{
public:
  Eeprom_flag(Flag_t flag, unsigned int addr_idx);
  bool flag_set(void);
  bool check_reset_val(void);
  bool write_set_val(void);
  bool write_reset_val(void);
  ~Eeprom_flag();
  
private:
  Flag_t flag;
};


#endif // _EEPROM_FLAG_H_
