/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      alarm data observer interface
*
* 版本:
* V1.0 2019-05-17 初始程序编写 
***********************************************************/

#ifndef _ALARM_DATA_OBSERVER_H_
#define _ALARM_DATA_OBSERVER_H_

#include <stdbool.h>
#include "data_type.h"

class Alarm_data_observer
{
public:
  virtual void update(Alarm_data_t* data, unsigned char opt = 0) = 0;
};

#endif // _ALARM_DATA_OBSERVER_H_
