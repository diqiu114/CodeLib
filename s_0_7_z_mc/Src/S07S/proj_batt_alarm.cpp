#include "proj_batt_alarm.h"
#include "paras.h"
#if S07Y
#include "s07y_upload_data.h"
#elif S07R
#include "s07r_upload_data.h"
#elif S07S
#include "s07s_upload_data.h"
#endif

#define CELL_VOLT_RATE (1000.0f)
#define CELL_TEMP_RATE (10.0f)
#define BATT_CNT (88)


extern bitset<8> complex_state;

Batt_alarm::Batt_alarm(Alarm_thres_t &_alarm_thresholds, int data_update_clk)
    : Alarm_handler(_alarm_thresholds, data_update_clk)
{
}

void Batt_alarm::send_alarm(Alarm_data *alarm)
{
  // Call observers
  curr_data.alm_status = alarm->status;
  curr_data.alm_code = alarm->type;
  curr_data.alm_lvl = alarm->lvl;
  curr_data.id = alarm->id;

  delete (alarm);

  alarm_data = &curr_data;
  notify_observers();
  //防止多条报警任务处理不及时导致误报漏报
  DELAY_MS(50);
}
void Batt_alarm::send_alarm(Alarm_data_t *alarm)
{
  // Call observers
  curr_data.alm_status = alarm->alm_status;
  curr_data.alm_code = alarm->alm_code;
  curr_data.alm_lvl = alarm->alm_lvl;
  curr_data.id = alarm->id;

  delete (alarm);

  alarm_data = &curr_data;
  notify_observers();
  //防止多条报警任务处理不及时导致误报漏报
  DELAY_MS(50);
}
void Batt_alarm::update(Batt_data_t *data, unsigned char opt)
{
  if (data == NULL)
  {
    return;
  }

  // In case previous data is needed for alarm.
  // mutex.lock();
  memcpy(&curr_data.batt_data, data, sizeof(Batt_data_t));
  // mutex.unlock();

#if (USE_FREE_RTOS)
  if (queue != NULL)
  {
    xQueueSend(queue, &msg, timeout);
  }
#else
  alarm_check();
#endif
}

void Batt_alarm::alarm_check(void)
{
  complex_state.set(POWER_ON_START_CHECK_SELF);
  bool is_recorded = alarm_holder->update();

  check_total_under_volt(curr_data.batt_data.total_data.total_volt);

  check_charge_over_cur(curr_data.batt_data.total_data.total_cur[0], curr_data.batt_data.state);

  check_low_soc(curr_data.batt_data.soc, curr_data.batt_data.state);

  check_overtemp(&curr_data.batt_data);
    
  check_drop_temp_over(curr_data.batt_data.cell_data);

  check_drop_volt_over(curr_data.batt_data.cell_data, curr_data.batt_data.state, 3);
    
  check_drop_volt_over(curr_data.batt_data.cell_data, curr_data.batt_data.state, 4);
    
  check_cell_overvolt(curr_data.batt_data.cell_data, curr_data.batt_data.total_data.amb_temp, curr_data.batt_data.state);

  check_cell_undervolt(curr_data.batt_data.cell_data);
    
    
#if S07S
#if !S07Z    
  check_total_volt_deviate_hi(curr_data.batt_data.state, curr_data.batt_data.total_data.total_volt, curr_data.batt_data.total_data.amb_temp);
#endif
  check_low_soh(curr_data.batt_data.soh);
  
#elif S07R

  check_total_over_volt(curr_data.batt_data.state, curr_data.batt_data.total_data.total_volt, curr_data.batt_data.total_data.amb_temp);

  check_discharge_over_cur(curr_data.batt_data.total_data.total_cur[0], curr_data.batt_data.state);
  
#endif

#if S07Y

  check_total_over_volt(curr_data.batt_data.total_data.total_volt);

  check_discharge_over_cur(curr_data.batt_data.total_data.total_cur[0], curr_data.batt_data.state);
    
#endif

  check_cell_comm_error(curr_data.batt_data.cell_data);
  
  if (!is_recorded)
    alarm_holder->update();
  
  complex_state.reset(POWER_ON_START_CHECK_SELF);
  complex_state.set(POWER_ON_CHECK_SELF_SUC);
  
#if S07S
  complex_state.set(POWER_ON_CHECK_SELF_END);
#endif
  
}

bool Batt_alarm::float_zero(float &val)
{
  if ((-0.000001f < val) && (val < 0.000001f))
  {
    return true;
  }
  else
  {
    return false;
  }
}

float S07s_get_temp_compensat_devat_value(float &volt, float &temp, Batt_state_t &state)
{
#if S07Y
  float ret = -0.24 * temp + 128.52;
  if (temp < -25)
  {
    ret = 134;
  }
  else if (temp > 60)
  {
    ret = 123.48;
  }
#else
    if (temp < -25)
  {
    ret = 128.4;
  }
  else if (temp > 60)
  {
    ret = 117.6;
  }
  
#endif
  
  return ret;
}

float S07r_get_temp_compensat_devat_value(float &volt, float &temp, Batt_state_t &state)
{
  //根据saft电池厂家提供的《SAFT蓄电池充电方案.pdf》计算
  float ret = (-0.003 * temp + 1.53) * BATT_CNT;
  if (temp < -25)
  {
    ret = 128.4;
  }
  else if (temp > 70)
  {
    ret = 117.6;
  }
  else if (temp > 65)
  {
    ret = 104;
  }
  else if (temp > 60)
  {
    ret = (-0.01 * temp + 1.95) * BATT_CNT;
  }
  return ret;
}

#if S07S
void Batt_alarm::check_total_volt_deviate_hi(Batt_state_t &state, float &volt, float &temp)
{
  float temp_compensate_volt = 0;
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;
  float drop_volt = 0;
  if (state != FLOAT_CHARGE)
  {
    ret = delete_alarm(TOTAL_VOLT_DEVIATE_HI);
    if (ret != NULL)
    {
      send_alarm(ret);
    }
    return;
  }
  temp_compensate_volt = S07s_get_temp_compensat_devat_value(volt, temp, state);
  drop_volt = volt - temp_compensate_volt;

  ret = check_high(drop_volt, TOTAL_VOLT_DEVIATE_HI, ALARM_LVL_1);
  alarm_type = TOTAL_VOLT_DEVIATE_HI;
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

void Batt_alarm::check_low_soh(float &val)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;
  alarm_type = SOH_LOW;
  ret = check_low(val, SOH_LOW, ALARM_LVL_2);

  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

#endif 

#if S07R || S07Y
void Batt_alarm::check_discharge_over_cur(float &cur, Batt_state_t &state)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;

  alarm_type = DISCHARGE_CUR_HIGH;
  if (state != DISCHARGE)
  {
    ret = delete_alarm(alarm_type);
    if (ret != NULL)
    {
      send_alarm(ret);
    }
    return;
  }

  ret = check_high(fabs(cur), alarm_type, ALARM_LVL_2);
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}
#endif

#if S07R || S07Y
void Batt_alarm::check_total_over_volt(Batt_state_t &state, float &volt, float &temp)
{
  float temp_compensate_volt = 0;
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;
  float drop_volt = 0;
    
#if S07R
  if (state != FLOAT_CHARGE)
  {
    ret = delete_alarm(TOTAL_VOLT_HI);
    if (ret != NULL)
    {
      send_alarm(ret);
    }
    return;
  }
#endif
  
  temp_compensate_volt = S07r_get_temp_compensat_devat_value(volt, temp, state);
  drop_volt = volt - temp_compensate_volt;

  ret = check_high(drop_volt, TOTAL_VOLT_HI, ALARM_LVL_1);
  alarm_type = TOTAL_VOLT_HI;
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

#endif

void Batt_alarm::check_total_under_volt(float &volt)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;

  alarm_type = TOTAL_VOLT_LOW;
  ret = check_low(volt, TOTAL_VOLT_LOW, ALARM_LVL_2);

  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}


void Batt_alarm::check_total_over_volt(float &volt)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;

  alarm_type = TOTAL_VOLT_HI;
  ret = check_high(volt, TOTAL_VOLT_HI, ALARM_LVL_2);

  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}


void Batt_alarm::check_charge_over_cur(float &cur, Batt_state_t &state)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;

  alarm_type = CHARGE_CUR_HIGH;
  if (state == DISCHARGE)
  {
    ret = delete_alarm(CHARGE_CUR_HIGH);
    if (ret != NULL)
    {
      send_alarm(ret);
    }
    return;
  }

  ret = check_high(cur, CHARGE_CUR_HIGH, ALARM_LVL_2);
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

void Batt_alarm::check_low_soc(float &val, Batt_state_t &state)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;

  alarm_type = SOC_LOW;
  if (state != DISCHARGE)
  {
    ret = delete_alarm(SOC_LOW);
    if (ret != NULL)
    {
      send_alarm(ret);
    }
    return;
  }
  ret = check_low(val, SOC_LOW, ALARM_LVL_2);

  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

void Batt_alarm::check_overtemp(Batt_data_t *batt_data)
{

  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
#if USE_MC_TEMP
  for (int i = 0; i < COUNT_OF_TEMP; i++)
  {
    ret = check_high(batt_data->total_data.temp[i], TEMP_HIGH, MIN_ALARM_LVL, i + 1);
    if (ret != NULL)
    {
      if (ret->low_lvl_alarm_clear_flag)
      {
        del_ret = delete_assign_alarm(TEMP_HIGH, ALARM_LVL_1, i + 1);
        if (del_ret != NULL)
        {
          del_ret->id = i + 1;
          send_alarm(del_ret);
        }
      }
      ret->id = i + 1;
      send_alarm(ret);
    }
  }
#else
  unsigned char temp_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_TEMP && Cell_adc_config_paras[j].is_enable == true)
      {
        temp_index++;
        ret = check_high(SCALE(batt_data->cell_data[i].acq_val[j], CELL_TEMP_RATE), TEMP_HIGH, MIN_ALARM_LVL, temp_index);
        if (ret != NULL)
        {
          if (ret->low_lvl_alarm_clear_flag)
          {
            del_ret = delete_assign_alarm(TEMP_HIGH, ALARM_LVL_1, temp_index);
            if (del_ret != NULL)
            {
              del_ret->id = temp_index;
              send_alarm(del_ret);
            }
          }
          ret->id = temp_index;
          send_alarm(ret);
        }
      }
    }
  }
#endif
}


Alarm_data *Batt_alarm::cell_volt_whether_hi(float volt, float &temp, unsigned int index)
{
  Alarm_data *ret = NULL;
#if S07S
  ret = check_high(volt, CELL_VOLT_HIGH, MIN_ALARM_LVL, index);
#elif S07R
  //根据saft电池厂家提供的《长沙6蓄电池报警阈值20210316.docx》计算
  float alarm_value = (1.47f + 0.025f - 0.003f * (temp - 20)) * 8 * 1.05f;
  float reset_value = (1.47f + 0.025f - 0.003f * (temp - 20)) * 8;
  if (volt >= alarm_value)
  {
    ret = alarm_holder->is_triggered(CELL_VOLT_HIGH, ALARM_LVL_2, index);
    ret->low_lvl_alarm_clear_flag = true;
  }
  else if (volt < reset_value)
  {
    ret = alarm_holder->is_reset(CELL_VOLT_HIGH, index);
  }
#endif
  return ret;
}

bool CheckSampleBoardCommErr(short *acq_val)
{
    for (int j = 0; j < ACQ_MAX_CNT; j++) {
        if (Cell_adc_config_paras[j].is_enable == true && acq_val[j] != 0) {
            return false;
        }
    }
    return true;
}

void Batt_alarm::check_cell_overvolt(Cell_data_t *cell_data, float &temp, Batt_state_t &state)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  unsigned char volt_index = 0;

  for (int i = 0; i < CELL_CNT; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
         
        volt_index++; 
#if (!S07Y || S07Z)	
        if (state != FLOAT_CHARGE)
        {
          ret = delete_alarm(CELL_VOLT_HIGH, volt_index);
          if (ret != NULL)
          {
            ret->id = volt_index;
            send_alarm(ret);
          }
          continue;
        }
#endif
          
        float voltage = SCALE(cell_data[i].acq_val[j], CELL_VOLT_RATE);
        
#if S07Y
        /*
        if(volt_index == 11 || volt_index == 22) {
            voltage = voltage * 2;
        } 
        */
        voltage = voltage * MAX_BAT_CNT_OF_PACK / Cell_adc_config_paras[j].pack_bat_cnt;
#endif
        
        ret = cell_volt_whether_hi(voltage, temp, volt_index);
        if (ret != NULL)
        {
          if (ret->low_lvl_alarm_clear_flag)
          {
            del_ret = delete_assign_alarm(CELL_VOLT_HIGH, ALARM_LVL_1, volt_index);
            if (del_ret != NULL)
            {
              del_ret->id = volt_index;
              send_alarm(del_ret);
            }
          }
          ret->id = volt_index;
          send_alarm(ret);
        }
      }
    }
  }
}

void Batt_alarm::check_cell_undervolt(Cell_data_t *cell_data)
{
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  unsigned char volt_index = 0;
  static bool lastCommStatu[CELL_CNT] = {false};
  static uint8_t commErrCount[CELL_CNT] = {0};
  for (int i = 0; i < CELL_CNT; i++)
  {
    // 通信断链增加三次滤波后才恢复已经产生的低压告警
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (!commerr) {
        lastCommStatu[i] = false;
        commErrCount[i] = 0;
    } else if (!lastCommStatu[i]) {
        commErrCount[i]++;
        if (commErrCount[i] == 3) {
            lastCommStatu[i] = true;
        }     
    } else {
        ;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        volt_index++;
        // 采集板通信断链时，低压告警都需要强制恢复
        if (lastCommStatu[i])
        {
          del_ret = delete_alarm(CELL_VOLT_LOW, volt_index);
          if (del_ret != NULL)
          {
            del_ret->id = volt_index;
            send_alarm(del_ret);
          }
          continue;
        }
        if (cell_data[i].acq_val[j] > 0)
        {
            float voltage = SCALE(cell_data[i].acq_val[j], CELL_VOLT_RATE);
        
#if S07Y
            /*
            if(volt_index == 11 || volt_index == 22) {
                voltage = voltage * 2;
            } 
            */
            
            voltage = voltage * MAX_BAT_CNT_OF_PACK / Cell_adc_config_paras[j].pack_bat_cnt;
#endif
          ret = check_low(voltage, CELL_VOLT_LOW, ALARM_LVL_2, volt_index);
          if (ret != NULL)
          {
            if (ret->low_lvl_alarm_clear_flag)
            {
              del_ret = delete_assign_alarm(CELL_VOLT_LOW, ALARM_LVL_1, volt_index);
              if (del_ret != NULL)
              {
                del_ret->id = volt_index;
                send_alarm(del_ret);
              }
            }
            ret->id = volt_index;
            send_alarm(ret);
          }
        }
      }
    }
  }
}

#define INVALID_ACQVALUE 0x7FFF
float Batt_alarm::find_max_volt_val(Cell_data_t *cell_data)
{
  short max = INVALID_ACQVALUE;
  for (int i = 0; i < CELL_CNT; i++)
  {
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (commerr) {
        continue;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        if (max == INVALID_ACQVALUE || cell_data[i].acq_val[j] > max)
        {
          max = cell_data[i].acq_val[j];
        }
      }
    }
  }
  if (max == INVALID_ACQVALUE) {
    return 1.0;
  } else {
    return (float)max;
  }
}

float Batt_alarm::find_max_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt)
{
  short max = INVALID_ACQVALUE;
  for (int i = 0; i < CELL_CNT; i++)
  {
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (commerr) {
        continue;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT \
          && Cell_adc_config_paras[j].is_enable == true \
          && Cell_adc_config_paras[j].pack_bat_cnt == bat_cnt)
      {
        if (max == INVALID_ACQVALUE || cell_data[i].acq_val[j] > max)
        {
          max = cell_data[i].acq_val[j];
        }
      }
    }
  }
  if (max == INVALID_ACQVALUE) {
    return 1.0;
  } else {
    return (float)max;
  }
}

float Batt_alarm::find_min_volt_val(Cell_data_t *cell_data)
{
  short min = INVALID_ACQVALUE;
  for (int i = 0; i < CELL_CNT; i++)
  {
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (commerr) {
        continue;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        if (min == INVALID_ACQVALUE || cell_data[i].acq_val[j] < min)
        {
          min = cell_data[i].acq_val[j];
        }
      }
    }
  }
  if (min == INVALID_ACQVALUE) {
    return 1.0;
  } else {
    return (float)min;
  }
}

float Batt_alarm::find_min_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt)
{
  short min = INVALID_ACQVALUE;
  for (int i = 0; i < CELL_CNT; i++)
  {
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (commerr) {
        continue;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT \
          && Cell_adc_config_paras[j].is_enable == true \
          && Cell_adc_config_paras[j].pack_bat_cnt == bat_cnt)
      {
        if (min == INVALID_ACQVALUE || cell_data[i].acq_val[j] < min)
        {
          min = cell_data[i].acq_val[j];
        }
      }
    }
  } 
  if (min == INVALID_ACQVALUE) {
    return 1.0;
  } else {
    return (float)min;
  }
}


float Batt_alarm::find_min_temp_val(Cell_data_t *cell_data)
{
  short min = INVALID_ACQVALUE;
  for (int i = 0; i < CELL_CNT; i++)
  {
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (commerr) {
        continue;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_TEMP \
          && Cell_adc_config_paras[j].is_enable == true)
      {
        if (min == INVALID_ACQVALUE || cell_data[i].acq_val[j] < min)
        {
          min = cell_data[i].acq_val[j];
        }
      }
    }
  }
  if (min == INVALID_ACQVALUE) {
    return 1.0;
  } else {
    return (float)min;
  }
}

float Batt_alarm::find_max_temp_val(Cell_data_t *cell_data)
{
  short max = INVALID_ACQVALUE;
  for (int i = 0; i < CELL_CNT; i++)
  {
    bool commerr = CheckSampleBoardCommErr(cell_data[i].acq_val);
    if (commerr) {
        continue;
    }
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_TEMP && Cell_adc_config_paras[j].is_enable == true)
      {
        if (max == INVALID_ACQVALUE || cell_data[i].acq_val[j] > max)
        {
          max = cell_data[i].acq_val[j];
        }
      }
    }
  }
  if (max == INVALID_ACQVALUE) {
    return 1.0;
  } else {
    return (float)max;
  }
}


void Batt_alarm::check_drop_temp_over(Cell_data_t *cell_data) {
  float max_drop_temp = find_max_temp_val(cell_data) - find_min_temp_val(cell_data);
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;
    

  ret = check_high(SCALE(max_drop_temp, CELL_TEMP_RATE), CELL_TEMP_DIFF_HIGH, ALARM_LVL_2);
  alarm_type = CELL_TEMP_DIFF_HIGH;
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

void Batt_alarm::check_drop_volt_over(Cell_data_t *cell_data, Batt_state_t &state,uint8_t bat_cnt)
{
  float max_drop_volt = find_max_volt_val(cell_data,bat_cnt) - find_min_volt_val(cell_data,bat_cnt);
  max_drop_volt = max_drop_volt * MAX_BAT_CNT_OF_PACK / bat_cnt;
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;
    
#if S07Z
  if (state != FLOAT_CHARGE)
  {
    ret = delete_alarm(CELL_VOLT_DIFF_HIGH, bat_cnt);
    if (ret != NULL)
    {
      ret->id = bat_cnt;
      send_alarm(ret);
    }
    return;
  }
#endif

  ret = check_high(SCALE(max_drop_volt, CELL_VOLT_RATE), CELL_VOLT_DIFF_HIGH, ALARM_LVL_1,bat_cnt);
  alarm_type = CELL_VOLT_DIFF_HIGH;
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1,bat_cnt);
      if (del_ret != NULL)
      {
        del_ret->id = bat_cnt;
        send_alarm(del_ret);
      }
    }
    ret->id = bat_cnt;
    send_alarm(ret);
  }
}

void Batt_alarm::check_drop_volt_over(Cell_data_t *cell_data, Batt_state_t &state)
{
  float max_drop_volt = find_max_volt_val(cell_data) - find_min_volt_val(cell_data);
  Alarm_data *ret = NULL;
  Alarm_data *del_ret = NULL;
  Alarm_code_t alarm_type;
    
#if 0
  if (state != FLOAT_CHARGE)
  {
    ret = delete_alarm(CELL_VOLT_DIFF_HIGH);
    if (ret != NULL)
    {
      send_alarm(ret);
    }
    return;
  }
#endif

  ret = check_high(SCALE(max_drop_volt, CELL_VOLT_RATE), CELL_VOLT_DIFF_HIGH, ALARM_LVL_1);
  alarm_type = CELL_VOLT_DIFF_HIGH;
  if (ret != NULL)
  {
    if (ret->low_lvl_alarm_clear_flag)
    {
      del_ret = delete_assign_alarm(alarm_type, ALARM_LVL_1);
      if (del_ret != NULL)
      {
        send_alarm(del_ret);
      }
    }
    send_alarm(ret);
  }
}

void Batt_alarm::check_cell_comm_error(Cell_data_t *cell_data)
{
#if 0
  Alarm_data *ret = NULL;

  for (int i = 0; i < CELL_CNT; i++)
  {
    ret = check_data_zero(cell_data[i], CELL_COMM_ERROR, MIN_ALARM_LVL);

    if (ret != NULL)
    {
      ret->id = cell_data[i].id;
      send_alarm(ret);
    }
  }
#endif
    
    
}

Alarm_data *Batt_alarm::check_low(float val, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl, int id)
{
  Alarm_data *ret = NULL;
  if (val <= preset_thres.trigger_thress[alarm_type][ALARM_LVL_2]) //10v  60
  {
    ret = alarm_holder->is_triggered(alarm_type, ALARM_LVL_2, id);

    if(ret != NULL) { //modify by ouyangwei 2021-11-30
        ret->low_lvl_alarm_clear_flag = true;
    }
  }
  else if (val <= preset_thres.trigger_thress[alarm_type][ALARM_LVL_1]) //10.5 10
  {
    ret = alarm_holder->is_triggered(alarm_type, ALARM_LVL_1, id);
  }
  else if (val > preset_thres.reset_thress[alarm_type])
  {
    ret = alarm_holder->is_reset(alarm_type, id);
  }

  return ret;
}

Alarm_data *Batt_alarm::check_high(float val, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl, int id)
{
  Alarm_data *ret = NULL;

  if (val >= preset_thres.trigger_thress[alarm_type][ALARM_LVL_2])
  {
    ret = alarm_holder->is_triggered(alarm_type, ALARM_LVL_2, id);

    if(ret != NULL) { //modify by ouyangwei 2021-11-30
        ret->low_lvl_alarm_clear_flag = true;
    }
  }
  else if (val >= preset_thres.trigger_thress[alarm_type][ALARM_LVL_1])
  {
    ret = alarm_holder->is_triggered(alarm_type, ALARM_LVL_1, id);
  }
  else if (val < preset_thres.reset_thress[alarm_type])
  {
    ret = alarm_holder->is_reset(alarm_type, id);
  }

  return ret;
}

bool is_zero(Cell_data_t &cell_data, unsigned int cnt)
{
  unsigned int sum = 0;
  for (int i = 0; i < cnt; i++)
  {
    sum += cell_data.acq_val[i];
  }

  return !sum;
}

Alarm_data *Batt_alarm::check_data_zero(Cell_data_t &cell_data, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl)
{
  Alarm_data *ret = NULL;
  if (is_zero(cell_data, ACQ_MAX_CNT))
  {
    ret = alarm_holder->is_triggered(alarm_type, alm_lvl, cell_data.id);
  }
  else
  {
    ret = alarm_holder->is_reset(alarm_type, cell_data.id);
  }

  return ret;
}

Alarm_data *Batt_alarm::check_alarm_status(enum ALARM_STATUS alm_state, Alarm_code_t alarm_type, Alarm_lvl_t alm_lvl)
{
  Alarm_data *ret = NULL;

  if (alm_state == ALARMED)
  {
    ret = alarm_holder->is_triggered(alarm_type, alm_lvl);
  }
  else
  {
    alarm_holder->clear(alarm_type);
  }

  return ret;
}
