/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      项目报警数据保存类
*
* 版本:
* V1.0 2019-06-27 初始版本程序编写 
***********************************************************/

#ifndef _PROJ_ALARM_STORE_H_
#define _PROJ_ALARM_STORE_H_

#include <stdbool.h>
#include "alarm_data_store.h"
#include "data_type.h"

class Proj_alarm_store : public Alarm_data_store
{
public:
  Proj_alarm_store(File *file);

  virtual bool store_data(void);

  ~Proj_alarm_store();
private:
  Alarm_store_data_t alarm_data;
};

#endif // _PROJ_ALARM_STORE_H_
