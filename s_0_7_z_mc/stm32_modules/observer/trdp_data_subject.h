/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      trdp upload data subject base class
*
* 版本:
* V1.0 2019-05-31 初始程序编写 
***********************************************************/

#ifndef _TRDP_DATA_SUBJECT_H_
#define _TRDP_DATA_SUBJECT_H_

#include <stdbool.h>
#include <list>
#include "trdp_data_observer.h"

using namespace std;

class Trdp_data_subject
{
public:
  bool register_observer(Trdp_data_observer *obj);
  bool remove_observer(Trdp_data_observer *obj);
  void notify_observers(void);
protected:
  Trdp_upload_data_t* data;
private:
  list<Trdp_data_observer*> obj_list;
};

#endif // _TRDP_DATA_SUBJECT_H_
