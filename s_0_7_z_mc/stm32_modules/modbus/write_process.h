/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      写入寄存器附带处理接口 
*
* 版本:
* V1.0 2018-11-30 初始版本程序编写 
***********************************************************/
#include <stdint.h>

#ifndef _WRITE_PROCESS_H_
#define _WRITE_PROCESS_H_

class Write_process
{
  public:
    virtual bool write_process(unsigned short addr, unsigned short val) = 0;
};

#endif // _WRITE_PROCESS_H_
