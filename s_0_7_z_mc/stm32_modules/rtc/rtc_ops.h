/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      RTC操作类
*
* 版本:
* V1.0 2019-04-24 初始版本程序编写 
***********************************************************/

#ifndef _RTC_OPS_H_
#define _RTC_OPS_H_

#include <stdbool.h>
#include "rtc.h"

typedef struct _tag_rtc_date_t
{
  unsigned char year;
  unsigned char month;
  unsigned char date;
}Rtc_date_t;

typedef struct _tag_rtc_time_t
{
  unsigned char hours;
  unsigned char minutes;
  unsigned char seconds;
  unsigned int sub_seconds;
}Rtc_time_t;

typedef struct _tag_rtc_t_
{
  Rtc_date_t date;
  Rtc_time_t time;
}Rtc_t;

class Rtc_ops
{
public:
  Rtc_ops(RTC_HandleTypeDef* handle);
  
  bool set_date(Rtc_date_t* date);
  bool set_time(Rtc_time_t* time);
  bool set_datetime(unsigned int ts);
  bool set_datetime(Rtc_t* date_time);
  bool get_date(Rtc_date_t* date);
  bool get_time(Rtc_time_t* time);
  bool get_datetime(Rtc_t* date_time);
  unsigned int get_ts(Rtc_t* date_time);
  unsigned int get_ts(void);
  unsigned int get_ts_with8zone(Rtc_t* date_time);
  bool ts_to_datetime(unsigned int ts, Rtc_t* datetime);
  ~Rtc_ops();
  
private:
  RTC_HandleTypeDef* hrtc;
  RTC_TimeTypeDef rtc_time;
  RTC_DateTypeDef rtc_date;
  

};


#endif // _RTC_OPS_H_
