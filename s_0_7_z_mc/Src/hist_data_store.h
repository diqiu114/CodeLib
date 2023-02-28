/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      历史数据保存类
*
* 版本:
* V1.1 2019-05-14 update增加立即写入option
* V1.0 2019-05-07 初始版本程序编写 
***********************************************************/

#ifndef _HIST_DATA_STORE_H_
#define _HIST_DATA_STORE_H_

#include <stdbool.h>
#include "batt_data_observer.h"
#include "file.h"
#include "rtc_ops.h"
#include "data_type.h"

class Hist_data_store : public Batt_data_observer
{
public:
  Hist_data_store(File *file);
  void set_rtc_handle(Rtc_ops* handle);
  #if (USE_FREE_RTOS)
    void set_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
  #endif

  virtual void update(Batt_data_t* data, unsigned char opt = 0);
  void set_store_interval(unsigned int cnt);
  virtual bool store_data(void);
  ~Hist_data_store();
private:
  File *file;
  History_data_t hist_data_buff;
  Rtc_ops* rtc;
  Rtc_t date_time;
  unsigned int cur_cnt;
  unsigned int interval_cnt;
  #if (USE_FREE_RTOS )
    QueueHandle_t queue;
    Queue_msg msg;
    unsigned int timeout;
  #endif

};

#endif // _HIST_DATA_STORE_H_
