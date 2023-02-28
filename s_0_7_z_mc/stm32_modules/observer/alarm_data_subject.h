/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      alarm data subject base class
*
* 版本:
* V1.0 2019-05-19 初始程序编写 
***********************************************************/

#ifndef _ALARM_DATA_SUBJECT_H_
#define _ALARM_DATA_SUBJECT_H_

#include <stdbool.h>
#include <list>
#include "alarm_data_observer.h"

using namespace std;

class Alarm_data_subject
{
public:
  bool register_observer(Alarm_data_observer *obj);
  bool remove_observer(Alarm_data_observer *obj);
  void notify_observers(void);
protected:
  Alarm_data_t* alarm_data;
private:
  list<Alarm_data_observer*> obj_list;
};

#endif // _ALARM_DATA_SUBJECT_H_
