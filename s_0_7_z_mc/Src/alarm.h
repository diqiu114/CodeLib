#ifndef ALARM_H_H
#define ALARM_H_H

#include <stdbool.h>
//#include "../stm32_modules/observer/batt_data_observer.h"
#include "data_type.h"
#include <vector>
#include "batt_data_observer.h"
#include "alarm_data_subject.h"
#define DEFAULT_ID    (-1)
#if (USE_FREE_RTOS)
#include "cmsis_os.h"
#endif

using namespace std;

enum ALARM_STATUS
{
  NO_ALARM = 0,
  ALARM_STARTED,
  ALARMED,
  ALARMING,
  ALARM_RESET_STARTED,
  ALARM_RESET,
};


class Alarm_data
{
private:
  unsigned short clk;
  unsigned short cnt[MAX_ALARM_LVL];
  unsigned short MAX_CNT_AT_LVL[MAX_ALARM_LVL];
  unsigned short reset_cnt;
  unsigned short reset_max_cnt;
  friend class Alarm_holder;
  ALARM_STATUS accu_trigger(Alarm_lvl_t lvl);
  ALARM_STATUS accu_reset();
  void update(void);

public:
  ALARM_STATUS status;
  Alarm_lvl_t lvl;
  Alarm_code_t type;
  int id;
  int cell_id;
  bool low_lvl_alarm_clear_flag;
  Alarm_data(Alarm_code_t _type, Alarm_lvl_t new_lvl, unsigned int *max_lvls, unsigned int reset_max, int update_clk);
  void init(ALARM_STATUS new_status);
  bool clear();
};

class Alarm_holder
{
public:
  int update_time; // second
  Alarm_thres_t &preset_thres;
  vector<Alarm_data> dta;

  Alarm_holder(Alarm_thres_t &_preset_thres, int _update_time);
  Alarm_data *is_triggered(Alarm_code_t alarm_type, Alarm_lvl_t lvl, int _cell_id = DEFAULT_ID);
  Alarm_data *is_reset(Alarm_code_t alarm_type, int _cell_id = DEFAULT_ID);
  void clear(Alarm_code_t alarm_type, int _cell_id = DEFAULT_ID);
  bool update(void);
  Alarm_data *delete_alarm(Alarm_code_t alarm_type, int _cell_id = DEFAULT_ID);
  Alarm_data *delete_assign_alarm(Alarm_code_t alarm_type, Alarm_lvl_t lvl, int _cell_id = DEFAULT_ID);
};

class Alarm_handler : public Batt_data_observer, public Alarm_data_subject
{
public:
  Alarm_handler(Alarm_thres_t &_alarm_thresholds, int data_update_time);
  virtual void update(Batt_data_t *data, unsigned char opt = 0);
  virtual void alarm_check(void);
#if (USE_FREE_RTOS)
  void set_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout);
#endif

  Alarm_holder *alarm_holder;
  virtual void send_alarm(Alarm_data *alarm);
protected:
  int update_clk;
  Alarm_thres_t &preset_thres;
  
  Alarm_data_t curr_data;
  Alarm_data *delete_alarm(Alarm_code_t alarm_type, int _cell_id = DEFAULT_ID);
  Alarm_data *delete_assign_alarm(Alarm_code_t alarm_type, Alarm_lvl_t lvl , unsigned char id = 0);
  
  
#if (USE_FREE_RTOS)
  QueueHandle_t queue;
  Queue_msg msg;
  unsigned int timeout;
#endif
};

#endif
