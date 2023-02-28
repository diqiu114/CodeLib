/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      battery data subject base class
*
* 版本:
* V1.1 2019-05-12 注册和移除观察者时，判断传入指针是否为空
* V1.0 2019-05-08 初始程序编写 
***********************************************************/

#ifndef _BATT_DATA_SUBJECT_H_
#define _BATT_DATA_SUBJECT_H_

#include <stdbool.h>
#include <list>
#include "batt_data_observer.h"

using namespace std;

class Batt_data_subject
{
public:
  bool register_observer(Batt_data_observer *obj);
  bool remove_observer(Batt_data_observer *obj);
  void notify_observers(void);
protected:
  Batt_data_t* batt_data;
private:
  list<Batt_data_observer*> obj_list;
};

#endif // _BATT_DATA_SUBJECT_H_
