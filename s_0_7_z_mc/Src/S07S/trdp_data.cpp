#include "trdp_data.h"
#include "alarm.h"
#include <string.h>
#include "paras.h"
#include <iterator>
#include <algorithm>

Trdp_data::Trdp_data(unsigned int update_clk)
{
  memset(&trdp_data, 0, sizeof(trdp_data));

  // 1 = 0.1A or 0.1V, charge voltage limit = 1.7V * 78 =132.6V
  trdp_data.charge_volt_limit = 1326;
  trdp_data.charge_cur_limit = User_paras.alm_thr.trigger_thress[CHARGE_CUR_HIGH][ALARM_LVL_3] * 10 + 0.0001f;
  trdp_data.software_ver = (Sys_paras.ver.MC_EX_SW_major << 8) | (Sys_paras.ver.MC_EX_SW_revision << 0);
  // 1. not test, 2. testing, 3. success, 4. test failed
  trdp_data.self_test = 3;
  alarm.reset();
  rtc = NULL;
  alarm_flag = false;
  time_update_clk = TIME_UPDATE_DELAY_IN_MS / update_clk;

  alm_data = NULL;
  batt_data = NULL;

  temp_sensor_err_val = 150.0f;

#if (USE_FREE_RTOS)
  alm_update_queue = NULL;
  data_update_queue = NULL;

  alm_update_msg = QM_CNT_MAX;
  data_update_msg = QM_CNT_MAX;
  alm_update_timeout = 0;
  data_update_timeout = 0;
#endif
}

void Trdp_data::set_rtc_handle(Rtc_ops *rtc)
{
  this->rtc = rtc;
}

int Trdp_data::get_update_buff(unsigned char *buff)
{
  if (buff == NULL)
  {
    return 0;
  }

  trdp_data.vital++;

  time_update_cnt++;
  if (time_update_cnt > time_update_clk)
  {
    time_update_cnt = 0;
    if (rtc != NULL)
    {
      if (rtc->get_datetime(&date_time))
      {
        trdp_data.year = date_time.date.year;
        trdp_data.month = date_time.date.month;
        trdp_data.date = date_time.date.date;
        trdp_data.hours = date_time.time.hours;
        trdp_data.minutes = date_time.time.minutes;
        trdp_data.seconds = date_time.time.seconds;
      }
    }
  }

  unsigned int alarm_bits = alarm.to_ulong();
  unsigned int idx = 0;

  buff[idx++] = (unsigned char)(trdp_data.vital >> 8);
  buff[idx++] = (unsigned char)(trdp_data.vital >> 0);
  if (alarm_flag == true)
  {
    buff[idx++] = 2;
  }
  else
  {
    buff[idx++] = 0;
  }
  buff[idx++] = trdp_data.soc;
  buff[idx++] = (unsigned char)(trdp_data.total_volt >> 8);
  buff[idx++] = (unsigned char)(trdp_data.total_volt >> 0);
  buff[idx++] = (unsigned char)(trdp_data.load_cur >> 8);
  buff[idx++] = (unsigned char)(trdp_data.load_cur >> 0);
  buff[idx++] = (unsigned char)(trdp_data.motor_cur >> 8);
  buff[idx++] = (unsigned char)(trdp_data.motor_cur >> 0);
  
  buff[idx++] = (unsigned char)(trdp_data.charge_cur_limit >> 8);
  buff[idx++] = (unsigned char)(trdp_data.charge_cur_limit >> 0); 
  
  buff[idx++] = (unsigned char)(trdp_data.charge_volt_limit >> 8);
  buff[idx++] = (unsigned char)(trdp_data.charge_volt_limit >> 0);

  // sikp reserved 4 bytes
  idx += 4;

  buff[idx++] = trdp_data.unbalance_volt_id;
  buff[idx++] = trdp_data.temp_max;
  buff[idx++] = trdp_data.temp_max_id;
  buff[idx++] = trdp_data.temp_min;
  buff[idx++] = trdp_data.temp_min_id;
  buff[idx++] = (unsigned char)(trdp_data.alarm >> 24);
  buff[idx++] = (unsigned char)(trdp_data.alarm >> 16);
  buff[idx++] = (unsigned char)(trdp_data.alarm >> 8);
  buff[idx++] = (unsigned char)(trdp_data.alarm >> 0);
  buff[idx++] = (unsigned char)(trdp_data.software_ver >> 8);
  buff[idx++] = (unsigned char)(trdp_data.software_ver >> 0);
  buff[idx++] = trdp_data.year;
  buff[idx++] = trdp_data.month;
  buff[idx++] = trdp_data.date;
  buff[idx++] = trdp_data.hours;
  buff[idx++] = trdp_data.minutes;
  buff[idx++] = trdp_data.seconds;
  buff[idx++] = trdp_data.self_test;

  // skip resered 2 bytes;
  idx += 2;
  unsigned char crc = crc8(buff,idx);
  buff[idx++] = crc;

  return idx;
}

unsigned char Trdp_data::crc8(unsigned char *buff, int buff_len)
{
  if ((buff == NULL) || (buff_len <= 0))
  {
    return 0;
  }

  unsigned char crc = 0, inbyte, i, mix;
  unsigned char *p = buff;
  while (buff_len--)
  {
    inbyte = *p++;
    for (i = 8; i; i--)
    {
      mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix)
      {
        crc ^= 0x8C;
      }
      inbyte >>= 1;
    }
  }

  // Return calculated CRC
  return crc;
}

bool Trdp_data::alarmed(void)
{
  return alarm_flag;
}

bool Trdp_data::has_alarm(void)
{
  unsigned int alarm_bits = alarm.to_ulong();
  // except contactor bits
  if ((((alarm_bits >> 8) & 0x00FFFFFF) == 0)      // bit8~bit31
      && (((alarm_bits << 27) & 0xFF000000) == 0)) // bit0~bit4
  {
    return false;
  }
  else
  {
    return true;
  }
}

void Trdp_data::set_temp_sensor_err_val(float val)
{
  temp_sensor_err_val = val;
}

void Trdp_data::update_batt_data(void)
{
  if (batt_data == NULL)
  {
    return;
  }

  // 1 = 0.4%
  trdp_data.soc = batt_data->soc / 4 * 10;
  // 1 = 0.1V
  trdp_data.total_volt = batt_data->total_data.total_volt * 10;
  // 1 = 0.1A offset +1000A
  trdp_data.load_cur = (batt_data->total_data.load_cur + 1000) * 10;
  trdp_data.motor_cur = (batt_data->total_data.motor_cur + 1000) * 10;

  // temperature offset +55 ℃
  float temp_max = 0.0f;
  unsigned char temp_max_id = 0;
  float temp_min = 180.0f;
  unsigned char temp_min_id = 0;

  for (int i = 0; i < TEMP_CH_CNT; i++)
  {
    if (batt_data->temp[i] > temp_sensor_err_val)
    {
      continue;
    }

    if (batt_data->temp[i] > temp_max)
    {
      temp_max = batt_data->temp[i];
      temp_max_id = i;
    }

    if (batt_data->temp[i] < temp_min)
    {
      temp_min = batt_data->temp[i];
      temp_min_id = i;
    }
  }

  trdp_data.temp_max = temp_max + 55;
  trdp_data.temp_max_id = temp_max_id;
  trdp_data.temp_min = temp_min + 55;
  trdp_data.temp_min_id = temp_min_id;

  for (int i = CONTACTOR_DETECT_CNT - 1; i > 0; i--)
  {
    if (batt_data->contactor_state[i] == 1)
    {
      alarm.set(contactor_pos(i));
    }
    else
    {
      alarm.reset(contactor_pos(i));
    }
  }
}

void Trdp_data::update_alarm_data(void)
{
  if (alm_data == NULL)
  {
    return;
  }

  if (alm_data->alm_status == ALARMED)
  {
    if (alm_data->alm_code == TEMP_ARRAY_UNBALANCE)
    {
      trdp_data.unbalance_volt_id = alm_data->alm_dev_id[0];
    }

    unsigned char pos = alarm_pos(alm_data->alm_code);
    if (pos != 0)
    {
      set_alarm(pos, alm_data->alm_lvl);
    }
  }
  else if (alm_data->alm_status == ALARM_RESET)
  {
    if (alm_data->alm_code == TEMP_ARRAY_UNBALANCE)
    {
      trdp_data.unbalance_volt_id = 0;
    }

    unsigned char pos = alarm_pos(alm_data->alm_code);
    if (pos != 0)
    {
      rst_alarm(pos);
    }
  }

  trdp_data.alarm = alarm.to_ulong();

  alarm_flag = has_alarm();
}

#if (USE_FREE_RTOS)
void Trdp_data::set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  alm_update_queue = handle;
  alm_update_msg = _msg;
  alm_update_timeout = _timeout;
}

void Trdp_data::set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  data_update_queue = handle;
  data_update_msg = _msg;
  data_update_timeout = _timeout;
}
#endif

void Trdp_data::update(Alarm_data_t *data, unsigned char opt)
{
  alm_data = data;

#if (USE_FREE_RTOS)
  if (alm_update_queue != NULL)
  {
    xQueueSend(alm_update_queue, &alm_update_msg, alm_update_timeout);
  }
#else
  update_alarm_data();
#endif
}

unsigned char Trdp_data::alarm_pos(Alarm_code_t alarm_code)
{
  unsigned char pos = 0;

  switch (alarm_code)
  {
  case TOTAL_VOLT_HIGH:
    pos = ALARM_POS_BATT_TOTAL_VOLT_HI;
    break;
  case TOTAL_VOLT_LOW:
    pos = ALARM_POS_BATT_TOTAL_VOLT_LOW;
    break;
  case TEMP_HIGH_CHARGE:
    pos = ALARM_POS_BATT_TEMP_HI;
    break;
  case TEMP_HIGH_DISCHARGE:
    pos = ALARM_POS_BATT_TEMP_HI;
    break;
  case TEMP_ARRAY_UNBALANCE:
    pos = ALARM_POS_BATT_TEMP_UNBALANCE;
    break;
  case LOAD_DISCHARGE_CUR_HIGH:
    pos = ALARM_POS_BATT_LOAD_CUR_DISCHARGE_HI;
    break;
  case MOTOR_DISCHARGE_CUR_HIGH:
    pos = ALARM_POS_BATT_MOTOR_CUR_DISCHARGE_HI;
    break;
  case CHARGE_CUR_HIGH:
    pos = ALARM_POS_BATT_CUR_CHARGE_HI;
    break;
  case BATT_ARRAY_VOLT_UNBALANCE:
    pos = ALARM_POS_BATT_ARRAY_VOLT_UNBALANCE;
    break;
  case SOC_LOW:
    pos = ALARM_POS_BATT_SOC_LOW;
    break;
  default:
    break;
  }

  return pos;
}

unsigned char Trdp_data::contactor_pos(unsigned char idx)
{
  unsigned char ret = 0;

  switch (idx)
  {
  case 3:
    ret = CONTACTOR_POS_DELAY;
    break;
  case 2:
    ret = CONTACTOR_POS_MAIN;
    break;
  case 1:
    ret = CONTACTOR_POS_VOLTAGE;
    break;
  default:
    break;
  }

  return ret;
}

void Trdp_data::update(Batt_data_t *data, unsigned char opt)
{
  batt_data = data;

#if (USE_FREE_RTOS)
  if (data_update_queue != NULL)
  {
    xQueueSend(data_update_queue, &data_update_msg, data_update_timeout);
  }
#else
  update_batt_data();
#endif
}

void Trdp_data::set_alarm(unsigned char pos, Alarm_lvl_t alm_lvl)
{
  switch (alm_lvl)
  {
  case ALARM_LVL_2:
    alarm.set(pos);
    break;
  case ALARM_LVL_3:
    alarm.set(pos);
    alarm.set(pos - 1);
    break;
  default:
    break;
  }
}

void Trdp_data::rst_alarm(unsigned char pos)
{
  alarm.reset(pos);
  alarm.reset(pos - 1);
}

Trdp_data::~Trdp_data(void)
{
}
