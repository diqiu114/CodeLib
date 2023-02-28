#include "s07r_upload_data.h"
#include "alarm.h"
#include <string.h>
#include "paras.h"
#include <iterator>
#include <algorithm>
#include "string.h"
#include "proj_paras.h"

//BMS系统代号
#define SYS_CODE_NAME (0x6D)
//包含、采集数据、报警数据、版本号、状态以及最大最小电压数据的长度
#define DATA_LEN ((unsigned short)58)
extern bitset<8> complex_state;

static unsigned short heartbeat;
static unsigned char *proto_data_buff = NULL;

S07R_Upload_data::S07R_Upload_data()
{
  memset(&eth_data, 0, sizeof(eth_data));
  alarm_state_handle = NULL;
  alm_data = NULL;
  batt_data = NULL;
  heartbeat = 0;
  volt_value = NULL;
#if (USE_FREE_RTOS)
  alm_update_queue = NULL;
  data_update_queue = NULL;

  alm_update_msg = QM_CNT_MAX;
  data_update_msg = QM_CNT_MAX;
  alm_update_timeout = 0;
  data_update_timeout = 0;
#endif
  //volt hi and volt low
  unsigned short volt_alarm_cnt = Dev_paras.volt_cnt * Sys_paras.batt_info.group_cnt * 2;
  unsigned char volt_alarm_bit_8_cnt = volt_alarm_cnt % 8 == 0 ? volt_alarm_cnt / 8 : volt_alarm_cnt / 8 + 1;
  eth_cell_alarm = new bitset<8>[volt_alarm_bit_8_cnt];
  eth_cell_alarm->reset();
  eth_total_alarm.reset();
}

void S07R_Upload_data::set_alarm_state_handle(Alarm_state *_state_handle)
{
  if (_state_handle != NULL)
  {
    alarm_state_handle = _state_handle;
  }
}

unsigned int S07R_Upload_data::user_proto_fill(unsigned char eth_num, unsigned char *original_data, unsigned int original_len, unsigned char *pack_data)
{
  if (proto_data_buff == NULL)
  {
    proto_data_buff = new unsigned char[ETH_SEND_BUFF_SIZE];
    if (proto_data_buff == NULL)
    {
      return 0;
    }
  }
  memset(proto_data_buff, 0, ETH_SEND_BUFF_SIZE);
  unsigned int index = 0;
  heartbeat++;
  proto_data_buff[index++] = 0x5A;
  proto_data_buff[index++] = 0xA5;
  proto_data_buff[index++] = (unsigned char)(Dev_paras.eth_paras[eth_num].trdp_paras.protol_version >> 8);
  proto_data_buff[index++] = (unsigned char)(Dev_paras.eth_paras[eth_num].trdp_paras.protol_version);
  proto_data_buff[index++] = (unsigned char)(heartbeat >> 8);
  proto_data_buff[index++] = (unsigned char)heartbeat;
  proto_data_buff[index++] = (unsigned char)(Dev_paras.eth_paras[eth_num].trdp_paras.bms[0].eth_ip[2]);
  proto_data_buff[index++] = (unsigned char)(Dev_paras.eth_paras[eth_num].trdp_paras.bms[0].eth_ip[3]);
  proto_data_buff[index++] = (unsigned char)(Dev_paras.eth_paras[eth_num].trdp_paras.bms[0].src_port[0] >> 8);
  proto_data_buff[index++] = (unsigned char)(Dev_paras.eth_paras[eth_num].trdp_paras.bms[0].src_port[0]);
  proto_data_buff[index++] = SYS_CODE_NAME;
  index++;
  proto_data_buff[index++] = (unsigned char)(DATA_LEN >> 8);
  proto_data_buff[index++] = (unsigned char)DATA_LEN;
  index += 4;
  if (heartbeat == 0xFFFF)
  {
    heartbeat = 0;
  }
  memcpy(proto_data_buff + index, original_data, original_len);
  memcpy(pack_data, proto_data_buff, original_len + index);
  return (index + original_len);
}

int S07R_Upload_data::get_eth_update_buff(unsigned char *buff)
{
  unsigned short index = 0;
  unsigned int total_alarm = 0;
  if (volt_value == NULL)
  {
    volt_value = new short[Dev_paras.volt_cnt];
    if (volt_value == NULL)
    {
      return 0;
    }
  }
  unsigned char volt_index = 0;
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0] >> 8);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0]);
  buff[index++] = eth_data.batt_data.state;
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc);
  index += 2;
  buff[index++] = (char)((short)eth_data.batt_data.total_data.temp[0] >> 8);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.temp[0]);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.temp[1] >> 8);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.temp[1]);
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
      }
    }
  }

  for (int i = 0; i < Dev_paras.volt_cnt; i++)
  {
    buff[index++] = (unsigned char)(volt_value[i] >> 8);
    buff[index++] = (unsigned char)(volt_value[i]);
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
  buff[index++] = (unsigned char)eth_cell_alarm[2].to_ulong();
  buff[index++] = (unsigned char)complex_state.to_ulong();
  index += 11;
  buff[index++] = Sys_paras.ver.MC_EX_SW_major;
  buff[index++] = (unsigned char)((Sys_paras.ver.MC_EX_SW_minjor << 4) | (Sys_paras.ver.MC_EX_SW_revision & 0x0f));
  return index;
}

Max_data_t S07R_Upload_data::find_max_volt_val(Cell_data_t *cell_data)
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
          ret.id = volt_index;
        }
      }
    }
  }
  if (ret.id == 1 && ret.volt == 0)
  {
    memset(&ret, 0, sizeof(Max_data_t));
  }
  return ret;
}

Min_data_t S07R_Upload_data::find_min_volt_val(Cell_data_t *cell_data)
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
          ret.id = volt_index;
        }
      }
    }
  }
  if (ret.id == 1 && ret.volt == 30000)
  {
    memset(&ret, 0, sizeof(Min_data_t));
  }
  return ret;
}

void S07R_Upload_data::update_batt_data(void)
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

void S07R_Upload_data::update_alarm_data(void)
{
  if (alm_data == NULL)
  {
    return;
  }
  short pos = 0;
  //eth_total_alarm eth_cell_alarm
  if (alm_data->alm_status == ALARMED)
  {
    pos = eth_alarm_pos(alm_data);
    if (pos != ALARM_ETH_POS_UNKNOWN)
    {
      eth_alarm_bit_op(OP_SET, pos);
    }
  } // clear alarmed bits
  else if (alm_data->alm_status == ALARM_RESET)
  {
    pos = eth_alarm_pos(alm_data);
    if (pos != ALARM_ETH_POS_UNKNOWN)
    {
      eth_alarm_bit_op(OP_RESET, pos);
    }
  }
}

void S07R_Upload_data::eth_alarm_bit_op(Op_para_t op, short pos)
{
  unsigned char cell_alarm_id_idx = 0;

  if (alm_data->alm_code == CELL_VOLT_LOW || alm_data->alm_code == CELL_VOLT_HIGH)
  {
    cell_alarm_id_idx = (alm_data->id - 1) / 4;
    unsigned short cell_alarm_volt_pos = (alm_data->id - 1) % 4 * 2 + pos;
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
        eth_total_alarm.set(pos * 2);
      }
      else if (alm_data->alm_lvl == ALARM_LVL_2)
      {
        eth_total_alarm.set(pos * 2 + 1);
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
void S07R_Upload_data::set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  alm_update_queue = handle;
  alm_update_msg = _msg;
  alm_update_timeout = _timeout;
}

void S07R_Upload_data::set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  data_update_queue = handle;
  data_update_msg = _msg;
  data_update_timeout = _timeout;
}
#endif

void S07R_Upload_data::update(Alarm_data_t *data, unsigned char opt)
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

void S07R_Upload_data::update(Batt_data_t *data, unsigned char opt)
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

short S07R_Upload_data::eth_alarm_pos(Alarm_data_t *alarm_data)
{
  short pos = ALARM_ETH_POS_UNKNOWN;

  switch (alarm_data->alm_code)
  {
  case TOTAL_VOLT_LOW:
    pos = ALARM_ETH_POS_VOLT_LOW;
    break;
  case TOTAL_VOLT_HI:
    pos = ALARM_ETH_POS_VOLT_HI;
    break;
  case TEMP_HIGH:
    if (alarm_data->id == 1)
    {
      pos = ALARM_ETH_POS_TEMP1_HI;
    }
    else if (alarm_data->id == 2)
    {
      pos = ALARM_ETH_POS_TEMP2_HI;
    }
    break;
  case CHARGE_CUR_HIGH:
    pos = ALARM_ETH_POS_CHARG_CURR_HI;
    break;
  case DISCHARGE_CUR_HIGH:
    pos = ALARM_ETH_POS_DISCHARG_CURR_HI;
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
    pos = ALARM_ETH_POS_DROP_VOLT_HI;
    break;
  default:
    pos = ALARM_ETH_POS_UNKNOWN;
    break;
  }
  return pos;
}

S07R_Upload_data::~S07R_Upload_data(void)
{
}
