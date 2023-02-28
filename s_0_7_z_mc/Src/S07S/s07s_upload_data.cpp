#include "s07s_upload_data.h"
#include "alarm.h"
#include <string.h>
#include "paras.h"
#include <iterator>
#include <algorithm>
#include "string.h"
#include "proj_paras.h"

extern bitset<8> complex_state;

S07S_Upload_data::S07S_Upload_data()
{
  memset(&eth_data, 0, sizeof(eth_data));
  alarm_state_handle = NULL;
  alm_data = NULL;
  batt_data = NULL;

#if (USE_FREE_RTOS)
  alm_update_queue = NULL;
  data_update_queue = NULL;

  alm_update_msg = QM_CNT_MAX;
  data_update_msg = QM_CNT_MAX;
  alm_update_timeout = 0;
  data_update_timeout = 0;
  heartbeat = 0;
  slight_alarm_cnt = 0;
  moderate_alarm_cnt = 0;
  serious_alarm_cnt = 0;
#endif
  //volt hi and volt low
  unsigned short volt_alarm_cnt = Dev_paras.volt_cnt * Sys_paras.batt_info.group_cnt * 2;
  unsigned char volt_alarm_bit_8_cnt = volt_alarm_cnt % 8 == 0 ? volt_alarm_cnt / 8 : volt_alarm_cnt / 8 + 1;
  eth_cell_alarm = new bitset<8>[volt_alarm_bit_8_cnt];
  eth_cell_alarm->reset();
  eth_total_alarm.reset();
}

void S07S_Upload_data::set_alarm_state_handle(Alarm_state *_state_handle)
{
  if (_state_handle != NULL)
  {
    alarm_state_handle = _state_handle;
  }
}

int S07S_Upload_data::get_eth_update_buff(unsigned char *buff)
{
  unsigned short index = 0;
  unsigned int total_alarm = 0;
  short *temp_value = new short[Dev_paras.temp_cnt];
  short *volt_value = new short[Dev_paras.volt_cnt];
  if(temp_value == NULL || volt_value == NULL)
  {
    return 0;
  }
  unsigned char volt_index = 0;
  unsigned char temp_index = 0;
  buff[index++] = (unsigned char)(heartbeat >> 8);
  buff[index++] = (unsigned char)heartbeat;
  heartbeat++;
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0] >> 8);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0]);
  buff[index++] = eth_data.batt_data.state;
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soh >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soh);

  for (int i = 0; i < Sys_paras.batt_info.group_cnt; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].is_enable)
      {
        if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT)
        {
          volt_index++;
          if (volt_index > Dev_paras.volt_cnt)
          {
            continue;
          }
          volt_value[volt_index - 1] = eth_data.batt_data.cell_data[i].acq_val[j];
        }
        else if (Cell_adc_config_paras[j].acq_type == TYPE_TEMP)
        {
          temp_index++;
          if (temp_index > Dev_paras.temp_cnt)
          {
            continue;
          }
          temp_value[temp_index - 1] = eth_data.batt_data.cell_data[i].acq_val[j];
        }
      }
    }
  }
  for (int i = 0; i < Dev_paras.temp_cnt; i++)
  {
    buff[index++] = (char)(temp_value[i] >> 8);
    buff[index++] = (char)(temp_value[i]);
  }

  for (int i = 0; i < Dev_paras.volt_cnt; i++)
  {
    buff[index++] = (unsigned char)(volt_value[i] >> 8);
    buff[index++] = (unsigned char)(volt_value[i]);
  }
  if(temp_value != NULL)
  {
    delete[] temp_value;
  }
  if(volt_value != NULL)
  {
    delete[] volt_value;
  }
  buff[index++] = eth_data.max_data.id;
  buff[index++] = (unsigned char)(eth_data.max_data.volt >> 8);
  buff[index++] = (unsigned char)eth_data.max_data.volt;
  buff[index++] = eth_data.min_data.id;
  buff[index++] = (unsigned char)(eth_data.min_data.volt >> 8);
  buff[index++] = (unsigned char)eth_data.min_data.volt;

  total_alarm = eth_total_alarm.to_ulong();
  buff[index++] = (unsigned char)(total_alarm >> 8);
  buff[index++] = (unsigned char)total_alarm;
  buff[index++] = (unsigned char)eth_cell_alarm[0].to_ulong();
  buff[index++] = (unsigned char)eth_cell_alarm[1].to_ulong();
  buff[index++] = (unsigned char)complex_state.to_ulong();
  index += 12;
  buff[index++] = Sys_paras.ver.MC_EX_SW_major;
  buff[index++] = (unsigned char)((Sys_paras.ver.MC_EX_SW_minjor << 4) | (Sys_paras.ver.MC_EX_SW_revision & 0x0f));
  if(heartbeat == 65535)
  {
    heartbeat = 0;
  }
  return index;
}

Max_data_t S07S_Upload_data::find_max_volt_val(Cell_data_t *cell_data)
{
  Max_data_t ret = {1, 0};
  unsigned char volt_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        volt_index++;
        if (cell_data[i].acq_val[j] > ret.volt)
        {
          ret.volt = cell_data[i].acq_val[j];
          ret.id = i * Dev_paras.volt_cnt + volt_index;
        }
      }
    }
  }
  if(ret.id == 1 && ret.volt ==  0)
  {
    memset(&ret, 0, sizeof(Max_data_t));
  }
  return ret;
}

Min_data_t S07S_Upload_data::find_min_volt_val(Cell_data_t *cell_data)
{
  Min_data_t ret = {1, 30000};
  unsigned char volt_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        volt_index++;
        if (cell_data[i].acq_val[j] < ret.volt && cell_data[i].acq_val[j] != 0)
        {
          ret.volt = cell_data[i].acq_val[j];
          ret.id = i * Dev_paras.volt_cnt + volt_index;
        }
      }
    }
  }
  if(ret.id == 1 && ret.volt ==  30000)
  {
    memset(&ret, 0, sizeof(Min_data_t));
  }
  return ret;
}

void S07S_Upload_data::update_batt_data(void)
{
  if (batt_data == NULL)
  {
    return;
  }
  memset(&eth_data.batt_data, 0, sizeof(eth_data.batt_data));
  memcpy(&eth_data.batt_data, batt_data, sizeof(Batt_data_t));
  eth_data.batt_data.total_data.total_volt = batt_data->total_data.total_volt * 10;
  eth_data.batt_data.total_data.total_cur[0] = batt_data->total_data.total_cur[0] * 10;
  eth_data.batt_data.soc = batt_data->soc * 10;
  eth_data.batt_data.total_data.temp[0] = batt_data->total_data.temp[0] * 10;
  eth_data.batt_data.total_data.temp[1] = batt_data->total_data.temp[1] * 10;
  eth_data.batt_data.soh = batt_data->soh * 10;
  Max_data_t max_v = find_max_volt_val(batt_data->cell_data);
  Min_data_t min_v = find_min_volt_val(batt_data->cell_data);
  eth_data.max_data.volt = max_v.volt;
  eth_data.max_data.id = max_v.id;
  eth_data.min_data.volt = min_v.volt;
  eth_data.min_data.id = min_v.id;
}

unsigned char S07S_Upload_data::judge_complex_alarm_state(Alarm_data_t *alarm_data)
{
  if(alarm_data->alm_code == CELL_VOLT_HIGH || alarm_data->alm_code == CELL_VOLT_LOW || alarm_data->alm_code == CELL_VOLT_DIFF_HIGH)
  {
    if(alarm_data->alm_status == ALARMED)
    {
      slight_alarm_cnt++;
    }
    else if(alarm_data->alm_status == ALARM_RESET && slight_alarm_cnt > 0)
    {
      slight_alarm_cnt--;
    }
    return COMPLEX_ALARM_SLIGHT;
  }
  else if(alarm_data->alm_code == TOTAL_VOLT_DEVIATE_HI || alarm_data->alm_code == TOTAL_VOLT_LOW || alarm_data->alm_code == CHARGE_CUR_HIGH || (alarm_data->alm_code == SOC_LOW && alarm_data->alm_lvl == ALARM_LVL_1)
          || alarm_data->alm_code == SOH_LOW || (alarm_data->alm_code == TEMP_HIGH && alarm_data->alm_lvl == ALARM_LVL_1))
  {
    if(alarm_data->alm_status == ALARMED)
    {
      moderate_alarm_cnt++;
    }
    else if(alarm_data->alm_status == ALARM_RESET && moderate_alarm_cnt > 0)
    {
      moderate_alarm_cnt--;
    }
    return COMPLEX_ALARM_MODERATE;
  }
  else if((alarm_data->alm_code == TEMP_HIGH && alarm_data->alm_lvl == ALARM_LVL_2) || (alarm_data->alm_code == SOC_LOW && alarm_data->alm_lvl == ALARM_LVL_2))
  {
    if(alarm_data->alm_status == ALARMED)
    {
      serious_alarm_cnt++;
    }
    else if(alarm_data->alm_status == ALARM_RESET && serious_alarm_cnt > 0)
    {
      serious_alarm_cnt--;
    }
    return COMPLEX_ALARM_SERIOUS;
  }
  return ALARM_ETH_POS_UNKNOWN;
}

void S07S_Upload_data::update_alarm_data(void)
{
  if (alm_data == NULL)
  {
    return;
  }
  short pos = 0;
  unsigned char complex_alarm_pos = judge_complex_alarm_state(alm_data);
  //eth_total_alarm eth_cell_alarm
  if (alm_data->alm_status == ALARMED)
  {
    pos = eth_alarm_pos(alm_data->alm_code);
    if (pos != ALARM_ETH_POS_UNKNOWN)
    {
      eth_alarm_bit_op(OP_SET, pos);
    }
    if(complex_alarm_pos != ALARM_ETH_POS_UNKNOWN)
    {
      complex_state.set(complex_alarm_pos);
    }
    
    pos = alarm_state_handle->alarm_set_pos(alm_data->alm_code);
  } // clear alarmed bits
  else if (alm_data->alm_status == ALARM_RESET)
  {
    pos = eth_alarm_pos(alm_data->alm_code);
    if (pos != ALARM_ETH_POS_UNKNOWN)
    {
      eth_alarm_bit_op(OP_RESET, pos);
    }
    switch(complex_alarm_pos)
    {
      case COMPLEX_ALARM_SLIGHT:
      if(slight_alarm_cnt == 0)
      {
        complex_state.reset(complex_alarm_pos);
      }
      break;
      case COMPLEX_ALARM_MODERATE:
      if(moderate_alarm_cnt == 0)
      {
        complex_state.reset(complex_alarm_pos);
      }
      break;
      case COMPLEX_ALARM_SERIOUS:
      if(serious_alarm_cnt == 0)
      {
        complex_state.reset(complex_alarm_pos);
      }
      default: break;
    }
  }
}

void S07S_Upload_data::eth_alarm_bit_op(Op_para_t op, short pos)
{
  unsigned char cell_alarm_id_idx = 0;

  if (alm_data->alm_code == CELL_VOLT_LOW || alm_data->alm_code == CELL_VOLT_HIGH)
  {
    cell_alarm_id_idx = (alm_data->id - 1) / 4;
    unsigned short cell_alarm_volt_pos = -2 * (alm_data->id - (alm_data->id - 1) / 4 * 4) + 8 + pos;
    if (op == OP_SET)
    {
      eth_cell_alarm[cell_alarm_id_idx].set(cell_alarm_volt_pos);
    }
    else if (op == OP_RESET)
    {
      eth_cell_alarm[cell_alarm_id_idx].reset(cell_alarm_volt_pos);
    }
  }
  else
  {
    if (op == OP_SET)
    {
      if (alm_data->alm_lvl == ALARM_LVL_1)
      {
        eth_total_alarm.set(pos * 2 + 1);
      }
      else if (alm_data->alm_lvl == ALARM_LVL_2)
      {
        eth_total_alarm.set(pos * 2);
      }
    }
    else if (op == OP_RESET)
    {
      eth_total_alarm.reset(pos * 2 + 1);
      eth_total_alarm.reset(pos * 2);
    }
  }
}

#if (USE_FREE_RTOS)
void S07S_Upload_data::set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  alm_update_queue = handle;
  alm_update_msg = _msg;
  alm_update_timeout = _timeout;
}

void S07S_Upload_data::set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  data_update_queue = handle;
  data_update_msg = _msg;
  data_update_timeout = _timeout;
}
#endif

void S07S_Upload_data::update(Alarm_data_t *data, unsigned char opt)
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

void S07S_Upload_data::update(Batt_data_t *data, unsigned char opt)
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

short S07S_Upload_data::eth_alarm_pos(Alarm_code_t alarm_code)
{
  short pos = ALARM_ETH_POS_UNKNOWN;

  switch (alarm_code)
  {
  case TOTAL_VOLT_LOW:
    pos = ALARM_ETH_POS_TOTAL_VOLT_LOW;
    break;
  case TOTAL_VOLT_DEVIATE_HI:
    pos = ALARM_ETH_POS_VOLT_DEVI_HI;
    break;
  case TEMP_HIGH:
    pos = ALARM_ETH_POS_TEMP_HI;
    break;
  case CHARGE_CUR_HIGH:
    pos = ALARM_ETH_POS_CHARG_CURR_HI;
    break;
  case SOH_LOW:
    pos = ALARM_ETH_POS_SOH_LOW;
    break;
  case SOC_LOW:
    pos = ALARM_ETH_POS_SOC_LOW;
    break;
  case CELL_VOLT_HIGH:
    pos = ALARM_ETH_POS_CELL_VOLT_HI;
    break;
  case CELL_VOLT_LOW:
    pos = ALARM_ETH_POS_CELL_VOLT_LOW;
    break;
  case CELL_VOLT_DIFF_HIGH:
    pos = ALARM_ETH_POS_VOLT_DROP_HI;
    break;
  default:
    pos = ALARM_ETH_POS_UNKNOWN;
    break;
  }
  return pos;
}

S07S_Upload_data::~S07S_Upload_data(void)
{
}
