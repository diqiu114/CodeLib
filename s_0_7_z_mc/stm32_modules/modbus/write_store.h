/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      Modbus 写入寄存器后,将数据存入EEPROM 
*
* 版本:
* V1.0 2018-11-30 初始版本程序编写 
***********************************************************/

#ifndef _WRITE_STORE_H_
#define _WRITE_STORE_H_
#include <stdint.h>
#include <map>
#include "write_process.h"
#include "eeprom_store.h"

using namespace std;

class Write_store : public Write_process
{
  public:
    Write_store(Storage* es, map<unsigned short, unsigned short>* addr_table);
    virtual bool write_process(unsigned short addr, unsigned short val);
    ~Write_store();
  private:
    Storage* eeprom_store;
    map<unsigned short, unsigned short>* reg_addr_table;
};

#endif // _WRITE_STORE_H_
