/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      报警数据保存类
*
* 版本:
* V1.0 2019-05-17 初始版本程序编写 
***********************************************************/

#ifndef _ALARM_DATA_STORE_H_
#define _ALARM_DATA_STORE_H_

#include <stdbool.h>
#include "alarm_data_observer.h"
#include "file.h"
#include "rtc_ops.h"
#include "data_type.h"

class Alarm_data_store : public Alarm_data_observer
{
public:
  Alarm_data_store(File *file);
  void set_rtc_handle(Rtc_ops* handle);
  #if (USE_FREE_RTOS )
    void set_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
  #endif
  virtual void update(Alarm_data_t* data, unsigned char opt = 0);
  virtual bool store_data(void);
  ~Alarm_data_store();
protected:
  File *file;
  Alarm_data_t alarm_data_buff;
  Rtc_ops* rtc;
private:
  Rtc_t date_time;
  unsigned int cur_cnt;
  #if (USE_FREE_RTOS )
    QueueHandle_t queue;
    Queue_msg msg;
    unsigned int timeout;
  #endif

};

#endif // _ALARM_DATA_STORE_H_
