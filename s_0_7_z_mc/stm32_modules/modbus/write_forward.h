/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      Modbus 写入寄存器后,将设置值写入到子设备对应的寄存器 
*
* 版本:
* V1.0 2018-12-02 初始版本程序编写 
***********************************************************/

#ifndef _WRITE_FORWARD_H_
#define _WRITE_FORWARD_H_
#include <stdint.h>
#include <map>
#include "write_process.h"
#include "modbus_master.h"

using namespace std;

class Write_forward: public Write_process
{
  public:
    Write_forward(Modbus_master* handle, map<unsigned short, Modbus_data>* addr_table);
    virtual bool write_process(unsigned short addr, unsigned short val);
    ~Write_forward();
  private:
    Modbus_master* hcomm;
    map<unsigned short, Modbus_data>* reg_device_table;
};

#endif // _WRITE_FORWARD_H_
