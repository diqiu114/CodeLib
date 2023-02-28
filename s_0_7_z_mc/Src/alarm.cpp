#include "alarm.h"
#include <memory>

Alarm_data::Alarm_data(Alarm_code_t _type, Alarm_lvl_t new_lvl, unsigned int *max_lvls, unsigned int reset_max, int update_clk)
{
  type = _type;
  for (int i = 0; i < MAX_ALARM_LVL; i++)
  {
    MAX_CNT_AT_LVL[i] = max_lvls[i] / update_clk;
  }
  reset_max_cnt = reset_max / update_clk;
  lvl = new_lvl;
  init(NO_ALARM);
}

void Alarm_data::init(ALARM_STATUS new_status)
{
  status = new_status;
  reset_cnt = 0;
  clk = 0;
  id = 0;
  low_lvl_alarm_clear_flag = false;
  memset(&cnt, 0, sizeof(unsigned short) * MAX_ALARM_LVL);
}

bool Alarm_data::clear()
{
  bool ret = false;
  if (status == ALARM_RESET_STARTED)
  {
    init(ALARMING);
  }
  else if (status != ALARMED || status != ALARMING)
  {
    init(NO_ALARM);
    ret = true;
  }

  return ret;
}

ALARM_STATUS Alarm_data::accu_trigger(Alarm_lvl_t _lvl)
{
  int cnt_sum = 0;
  
  if (status == ALARMED || status == ALARMING || status == ALARM_RESET_STARTED)
  {
    status = ALARMING;
    reset_cnt = 0;
    return status;     
  }
  else
    status = ALARM_STARTED;

  cnt[_lvl]++;

  for (short i = MAX_ALARM_LVL - 1; i >= MIN_ALARM_LVL; i--)
  {
    // If the higher level has not enough cnt for triggering, move the cnt to lower level.
    cnt_sum += cnt[i];
    if (clk >= MAX_CNT_AT_LVL[i])
    {
      if (cnt_sum == 0)
      {
        continue;
      }
      if (cnt_sum >= MAX_CNT_AT_LVL[i])
      {
        lvl = (Alarm_lvl_t)i;  
        status = ALARMED; 
        clk = 0;
        return status;
      }
    }
  }

  return status;
}

ALARM_STATUS Alarm_data::accu_reset()
{
  reset_cnt++;
  if (status == ALARMED || status == ALARMING)
  {
    status = ALARM_RESET_STARTED;
    clk = 1;
  }

  if (status == ALARM_RESET_STARTED)
  {
    if (clk >= reset_max_cnt && reset_cnt >= reset_max_cnt)
    {
      init(ALARM_RESET);
    }
  }
  else
  {
    init(NO_ALARM);
  }
  return status;
}

void Alarm_data::update(void)
{
  if (ALARM_STARTED || ALARM_RESET_STARTED)
    clk++;
}

Alarm_holder::Alarm_holder(Alarm_thres_t &_preset_thres, int _update_time)
    : preset_thres(_preset_thres)
{
  update_time = _update_time;
}

Alarm_data *Alarm_holder::is_triggered(Alarm_code_t alarm_type, Alarm_lvl_t lvl, int _cell_id)
{
  bool is_new = true;
  int curr_alarm_idx = 0;
  Alarm_data *ret = NULL;
  for (size_t i = 0; i < dta.size(); i++)
  {
    if (dta[i].type == alarm_type && ((_cell_id == DEFAULT_ID) || (_cell_id == dta[i].cell_id)) &&  dta[i].lvl >= lvl)
    {
      is_new = false;
      curr_alarm_idx = i;
      break;
    }
  }
  if (is_new)
  {
    Alarm_data new_alarm(alarm_type, lvl, preset_thres.trigger_delays[alarm_type], preset_thres.reset_delays[alarm_type], update_time);
    new_alarm.cell_id = _cell_id;
    dta.push_back(new_alarm);
    curr_alarm_idx = dta.size() - 1;
  }
  switch (dta[curr_alarm_idx].accu_trigger(lvl))
  {
  case ALARMED:
    // create a new alarm data copy for reporting. It will be freed in send_alarm().
    ret = new Alarm_data(dta[curr_alarm_idx]);
    break;
  case ALARM_STARTED:
  case ALARMING:
  case ALARM_RESET_STARTED:
    return NULL;
  case ALARM_RESET:
  case NO_ALARM:
    // shouldn't happen
    break;
  }
  return ret;
}

bool Alarm_holder::update(void)
{
  bool is_recorded = false;
  for (size_t i = 0; i < dta.size(); i++)
  {
    dta[i].update();
    is_recorded = true;
  }
  return is_recorded;
}

Alarm_data *Alarm_holder::is_reset(Alarm_code_t alarm_type, int _cell_id)
{
  Alarm_data *ret = NULL;
  for (size_t i = 0; i < dta.size(); i++)
  {
    if ((dta[i].type == alarm_type) && ((_cell_id == DEFAULT_ID) || dta[i].cell_id == _cell_id))
    {
      switch (dta[i].accu_reset())
      {
      case ALARM_RESET:
        // create a new alarm data copy for reporting. It will be freed in send_alarm().
        ret = new Alarm_data(dta[i]);
        dta.erase(dta.begin() + i);
        break;
      case NO_ALARM:
        dta.erase(dta.begin() + i);
        break;
      case ALARM_STARTED:
      case ALARMED:
      case ALARMING:
      case ALARM_RESET_STARTED:
        break;
      }
    }
  }
  return ret;
}

Alarm_data *Alarm_holder::delete_alarm(Alarm_code_t alarm_type, int _cell_id)
{
  Alarm_data *ret = NULL;
  for (size_t i = 0; i < dta.size(); i++)
  {
    if ((dta[i].type == alarm_type) && ((_cell_id == DEFAULT_ID) || dta[i].cell_id == _cell_id))
    {
      ret = new Alarm_data(dta[i]);
      ret->status = ALARM_RESET;
      dta.erase(dta.begin() + i);
      break;
    }
  }
  return ret;
}

Alarm_data *Alarm_holder::delete_assign_alarm(Alarm_code_t alarm_type, Alarm_lvl_t lvl, int _cell_id)
{
  Alarm_data *ret = NULL;
  for (size_t i = 0; i < dta.size(); i++)
  {
    if ((dta[i].type == alarm_type) && ((_cell_id == DEFAULT_ID) || dta[i].cell_id == _cell_id) && (dta[i].lvl == lvl))
    {
      ret = new Alarm_data(dta[i]);
      ret->status = ALARM_RESET;
      dta.erase(dta.begin() + i);
      break;
    }
  }
  return ret;
}

void Alarm_holder::clear(Alarm_code_t alarm_type,int _cell_id)
{
  for (size_t i = 0; i < dta.size(); i++)
  {
    if ((dta[i].type == alarm_type) && ((_cell_id == DEFAULT_ID) || dta[i].cell_id == _cell_id))
    {
      if (dta[i].clear())
        dta.erase(dta.begin() + i);
      break;
    }
  }
}

Alarm_handler::Alarm_handler(Alarm_thres_t &_alarm_thresholds, int data_update_clk)
    : preset_thres(_alarm_thresholds)
{
  alarm_holder = new Alarm_holder(_alarm_thresholds, data_update_clk);
  
#if (USE_FREE_RTOS)
  queue = NULL;
  msg = QM_CNT_MAX;
  timeout = 0;
#endif
}

void Alarm_handler::send_alarm(Alarm_data *alarm)
{
  delete (alarm);

  alarm_data = &curr_data;
  notify_observers();
}

void Alarm_handler::update(Batt_data_t *data, unsigned char opt)
{
  if (data == NULL)
  {
    return;
  }

  // update data
  //  memcpy(&curr_data.batt_data, data, sizeof(Batt_data_t));

#if (USE_FREE_RTOS)
  if (queue != NULL)
  {
    xQueueSend(queue, &msg, timeout);
  }
#else
  alarm_check();
#endif
}

#if (USE_FREE_RTOS)
void Alarm_handler::set_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  queue = handle;
  msg = _msg;
  timeout = _timeout;
}
#endif

void Alarm_handler::alarm_check(void)
{

  bool is_recorded = alarm_holder->update();

  if (!is_recorded)
    alarm_holder->update();
}

Alarm_data *Alarm_handler::delete_alarm(Alarm_code_t alarm_type, int _cell_id)
{
  return alarm_holder->delete_alarm(alarm_type, _cell_id);
}

Alarm_data *Alarm_handler::delete_assign_alarm(Alarm_code_t alarm_type, Alarm_lvl_t lvl ,unsigned char id)
{
  return alarm_holder->delete_assign_alarm(alarm_type, lvl, id);
}
