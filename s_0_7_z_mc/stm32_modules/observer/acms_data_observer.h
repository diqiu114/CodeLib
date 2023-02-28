/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      battery data observer interface
*
* 版本:
* V1.2 2019-05-14 update函数增加option参数
* V1.1 2019-05-07 update函数参数增加数据指针以及数据长度
* V1.0 2019-05-05 初始程序编写 
***********************************************************/
#ifndef _ACMS_DATA_OBSERVER_H_
#define _ACMS_DATA_OBSERVER_H_

#include <stdbool.h>
#include "data_type.h"

class Acms_data_observer
{
public:
  virtual void update(Acms_data_t* data, unsigned char opt = 0) = 0;
};

#endif // _ACMS_DATA_OBSERVER_H_
