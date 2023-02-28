/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      trdp upload data
*
* 版本:
* V1.0 2019-06-01 初始程序编写 
***********************************************************/

#ifndef _TRDP_DATA_H_
#define _TRDP_DATA_H_

#include <stdbool.h>
#include "data_type.h"
#include "batt_data_observer.h"
#include "alarm_data_observer.h"
#include "rtc_ops.h"
#include <bitset>

#define ALARM_POS_BATT_TOTAL_VOLT_LOW (31)
#define ALARM_POS_BATT_TOTAL_VOLT_HI (29)
#define ALARM_POS_BATT_ARRAY_VOLT_UNBALANCE (25)
#define ALARM_POS_BATT_TEMP_HI (23)
#define ALARM_POS_BATT_TEMP_UNBALANCE (21)
#define ALARM_POS_BATT_SOC_LOW (17)
#define ALARM_POS_BATT_MOTOR_CUR_DISCHARGE_HI (15)
#define ALARM_POS_BATT_LOAD_CUR_DISCHARGE_HI (13)
#define ALARM_POS_BATT_CUR_CHARGE_HI (11)
#define ALARM_POS_BATT_TEMP_LOW (9)
#define CONTACTOR_POS_MAIN (5)
#define CONTACTOR_POS_VOLTAGE (6)
#define CONTACTOR_POS_DELAY (7)

#define TIME_UPDATE_DELAY_IN_MS (1000)

#define TEMP_SENSOR_ERR_VAL_MAX (125.0f)
#define TEMP_SENSOR_ERR_VAL_MIN (-40.0f)

#define TOTAL_VOLT_ERR_VAL      (5.0f)//

typedef struct _tag_trdp_upload_data_
{
  unsigned short vital;
  unsigned char status;
  unsigned char soc;
  unsigned short total_volt;
  unsigned short load_cur;
  unsigned short motor_cur;
  unsigned short charge_cur_limit;
  unsigned short charge_volt_limit;
  unsigned char unbalance_volt_id;
  unsigned char temp_max;
  unsigned char temp_max_id;
  unsigned char temp_min;
  unsigned char temp_min_id;
  unsigned int alarm;
  unsigned short software_ver;
  unsigned char year;
  unsigned char month;
  unsigned char date;
  unsigned char hours;
  unsigned char minutes;
  unsigned char seconds;
  unsigned char self_test;
  unsigned char crc;
} Trdp_upload_data_t;

using namespace ::std;

class Trdp_data : public Batt_data_observer, public Alarm_data_observer
{
public:
  Trdp_data(unsigned int update_clk);
  int get_update_buff(unsigned char *buff);
  virtual void update(Alarm_data_t *data, unsigned char opt = 0);
  virtual void update(Batt_data_t *data, unsigned char opt = 0);
  void set_rtc_handle(Rtc_ops *rtc);
  void set_temp_sensor_err_val(float val);
  bool alarmed(void);

  void update_batt_data(void);
  void update_alarm_data(void);

#if (USE_FREE_RTOS)
  void set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
  void set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);

#endif

  ~Trdp_data(void);

private:
  Trdp_upload_data_t trdp_data;
  bool alarm_flag;
  bitset<32> alarm;
  Rtc_ops *rtc;
  Rtc_t date_time;
  unsigned int time_update_clk;
  unsigned int time_update_cnt;
  Alarm_data_t* alm_data;
  Batt_data_t* batt_data;
  float temp_sensor_err_val;
  
#if (USE_FREE_RTOS)
  QueueHandle_t alm_update_queue;
  QueueHandle_t data_update_queue;

  Queue_msg alm_update_msg;
  Queue_msg data_update_msg;
  unsigned int alm_update_timeout;
  unsigned int data_update_timeout;
#endif

  bool has_alarm(void);
  unsigned char alarm_pos(Alarm_code_t alarm_code);
  unsigned char contactor_pos(unsigned char idx);
  void contactor_update(Batt_data_t *data);
  void set_alarm(unsigned char pos, Alarm_lvl_t alm_lvl);
  void rst_alarm(unsigned char pos);
  unsigned char crc8(unsigned char *buff, int buff_len);
};

#endif // _TRDP_DATA_H_
