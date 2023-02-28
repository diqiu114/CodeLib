/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      device id interface
*
* 版本:
* V1.0 2018-11-22 初始程序编写 
***********************************************************/

#ifndef _DEVICE_ID_H_
#define _DEVICE_ID_H_

#include <stdbool.h>

class Device_id
{
  public:
    virtual char get_id(void) = 0;
    virtual bool set_id(char id) = 0;
};

#endif // _DEVICE_ID_H_
