#include "s07y_upload_data.h"
#include "alarm.h"
#include <string.h>
#include "paras.h"
#include <iterator>
#include <algorithm>
#include "string.h"
#include "proj_paras.h"
#include "trdp_data.h"

extern bitset<8> complex_state;


const AlarmInfor_t alarmRemap[] = {
    {  TEMP_HIGH,            ALARM_LVL_1,  1, Group01TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  1, Group01TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  2, Group02TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  2, Group02TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  3, Group03TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  3, Group03TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  4, Group04TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  4, Group04TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  5, Group05TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  5, Group05TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  6, Group06TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  6, Group06TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  7, Group07TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  7, Group07TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  8, Group08TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  8, Group08TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1,  9, Group09TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2,  9, Group09TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 10, Group10TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 10, Group10TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 11, Group11TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 11, Group11TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 12, Group12TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 12, Group12TempHiLvl_2,  },
	
	{  TEMP_HIGH,            ALARM_LVL_1, 13, Group13TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 13, Group13TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 14, Group14TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 14, Group14TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 15, Group15TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 15, Group15TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 16, Group16TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 16, Group16TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 17, Group17TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 17, Group17TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 18, Group18TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 18, Group18TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 19, Group19TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 19, Group19TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 20, Group20TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 20, Group20TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 21, Group21TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 21, Group21TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 22, Group22TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 22, Group22TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 23, Group23TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 23, Group23TempHiLvl_2,  },
    {  TEMP_HIGH,            ALARM_LVL_1, 24, Group24TempHiLvl_1,  },
	{  TEMP_HIGH,            ALARM_LVL_2, 24, Group24TempHiLvl_2,  },
																 
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  1,  Cell01VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  1,  Cell01VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  1,  Cell01VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  1,  Cell01VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  2,  Cell02VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  2,  Cell02VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  2,  Cell02VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  2,  Cell02VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  3,  Cell03VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  3,  Cell03VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  3,  Cell03VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  3,  Cell03VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  4,  Cell04VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  4,  Cell04VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  4,  Cell04VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  4,  Cell04VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  5,  Cell05VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  5,  Cell05VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  5,  Cell05VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  5,  Cell05VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  6,  Cell06VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  6,  Cell06VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  6,  Cell06VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  6,  Cell06VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  7,  Cell07VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  7,  Cell07VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  7,  Cell07VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  7,  Cell07VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  8,  Cell08VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  8,  Cell08VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  8,  Cell08VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  8,  Cell08VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1,  9,  Cell09VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2,  9,  Cell09VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1,  9,  Cell09VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2,  9,  Cell09VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 10,  Cell10VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 10,  Cell10VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 10,  Cell10VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 10,  Cell10VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 11,  Cell11VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 11,  Cell11VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 11,  Cell11VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 11,  Cell11VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 12,  Cell12VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 12,  Cell12VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 12,  Cell12VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 12,  Cell12VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 13,  Cell13VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 13,  Cell13VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 13,  Cell13VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 13,  Cell13VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 14,  Cell14VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 14,  Cell14VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 14,  Cell14VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 14,  Cell14VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 15,  Cell15VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 15,  Cell15VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 15,  Cell15VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 15,  Cell15VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 16,  Cell16VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 16,  Cell16VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 16,  Cell16VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 16,  Cell16VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 17,  Cell17VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 17,  Cell17VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 17,  Cell17VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 17,  Cell17VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 18,  Cell18VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 18,  Cell18VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 18,  Cell18VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 18,  Cell18VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 19,  Cell19VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 19,  Cell19VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 19,  Cell19VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 19,  Cell19VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 20,  Cell20VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 20,  Cell20VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 20,  Cell20VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 20,  Cell20VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 21,  Cell21VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 21,  Cell21VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 21,  Cell21VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 21,  Cell21VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 22,  Cell22VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 22,  Cell22VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 22,  Cell22VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 22,  Cell22VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 23,  Cell23VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 23,  Cell23VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 23,  Cell23VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 23,  Cell23VolHiLvl_2, },
    {  CELL_VOLT_LOW,        ALARM_LVL_1, 24,  Cell24VolLoLvl_1, },
	{  CELL_VOLT_LOW,        ALARM_LVL_2, 24,  Cell24VolLoLvl_2, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_1, 24,  Cell24VolHiLvl_1, },
	{  CELL_VOLT_HIGH,       ALARM_LVL_2, 24,  Cell24VolHiLvl_2, },
    
																  
    {  CHARGE_CUR_HIGH,      ALARM_LVL_1, 0,  ChargeOverLvl_1,     },
    {  CHARGE_CUR_HIGH,      ALARM_LVL_2, 0,  ChargeOverLvl_2,     },
	{  DISCHARGE_CUR_HIGH,   ALARM_LVL_1, 0,  DischargeOverLvl_1,  },
    {  DISCHARGE_CUR_HIGH,   ALARM_LVL_2, 0,  DischargeOverLvl_2,  },
    {  TOTAL_VOLT_LOW,       ALARM_LVL_1, 0,  TotalVolLoLvl_1,     },
    {  TOTAL_VOLT_LOW,       ALARM_LVL_2, 0,  TotalVolLoLvl_2,     },
    {  TOTAL_VOLT_HI,        ALARM_LVL_1, 0,  TotalVolHiLvl_1,     },
    {  TOTAL_VOLT_HI,        ALARM_LVL_2, 0,  TotalVolHiLvl_2,     },
	
    {  TOTAL_VOLT_DEVIATE_HI,ALARM_LVL_1, 0,  TotalVolDeLvl_1,     },
    {  TOTAL_VOLT_DEVIATE_HI,ALARM_LVL_2, 0,  TotalVolDeLvl_2,     },
    {  CELL_VOLT_DIFF_HIGH,  ALARM_LVL_1, 3,  CellAVolDiffHi_Lvl_1, },
    {  CELL_VOLT_DIFF_HIGH,  ALARM_LVL_2, 3,  CellAVolDiffHi_Lvl_2, },
	{  CELL_VOLT_DIFF_HIGH,  ALARM_LVL_1, 4,  CellBVolDiffHi_Lvl_1, },
    {  CELL_VOLT_DIFF_HIGH,  ALARM_LVL_2, 4,  CellBVolDiffHi_Lvl_2, },
    {  CELL_TEMP_DIFF_HIGH,  ALARM_LVL_1, 0,  CellTempDiffHi_Lvl_1,},
    {  CELL_TEMP_DIFF_HIGH,  ALARM_LVL_2, 0,  CellTempDiffHi_Lvl_2,},
	
    {  SOC_LOW,              ALARM_LVL_1, 0,  SOCLoLvl_1,          },
    {  SOC_LOW,              ALARM_LVL_2, 0,  SOCLoLvl_2,          },
    {  SOH_LOW,              ALARM_LVL_1, 0,  SOHLoLvl_1,          },
    {  SOH_LOW,              ALARM_LVL_2, 0,  SOHLoLvl_2,          },
                             
};

#define ERROR_POS  0xff
#define ALARM_MAP_SIZE  sizeof(alarmRemap)/sizeof(alarmRemap[0])

S07Y_Upload_data::S07Y_Upload_data()
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
  //unsigned short volt_alarm_cnt = Dev_paras.volt_cnt * Sys_paras.batt_info.group_cnt * 2;
  //unsigned char volt_alarm_bit_8_cnt = volt_alarm_cnt % 8 == 0 ? volt_alarm_cnt / 8 : volt_alarm_cnt / 8 + 1;
  //eth_cell_alarm = new bitset<8>[volt_alarm_bit_8_cnt];
  //eth_cell_alarm->reset();
  //eth_total_alarm.reset();
  
  memset(&alarmAllBits,0,sizeof(AlarmBits_t));
  alarm_self_check_state = AlarmSelfCheckNo;
  alarm_self_flag.all = 0x00;
}

void S07Y_Upload_data::set_alarm_state_handle(Alarm_state *_state_handle)
{
  if (_state_handle != NULL)
  {
    alarm_state_handle = _state_handle;
  }
}

bool S07Y_Upload_data::get_alarm_flag(Alarm_data_t *data) {
    
    for(int i=0;i<ALARM_MAP_SIZE;i++) {
        
        switch(data->alm_code) {
            case TEMP_HIGH:
            case CELL_VOLT_HIGH:
            case CELL_VOLT_LOW:
            case CELL_VOLT_DIFF_HIGH:  //压差过大 此时Id为3 或者4。标志位为3联体或者4联体
            //case CELL_TEMP_DIFF_HIGH:
                if(data->alm_lvl == alarmRemap[i].alarm_lvl &&
                   data->alm_code == alarmRemap[i].alarm_code &&
                   data->id == alarmRemap[i].id) {
                    
                    uint8_t alarm_byte_pos = alarmRemap[i].alarm_pos / 8;
                    uint8_t alarm_bit_pos = alarmRemap[i].alarm_pos % 8;
                    
                    if(alarm_byte_pos >= ALARM_MAX_BYTES) {
                        return true;
                    }
                    
                    return (alarmAllBits.bits[alarm_byte_pos] & (1 << alarm_bit_pos)) ? true : false;
                    
                }
                break;
                
            default:
                if(data->alm_lvl == alarmRemap[i].alarm_lvl &&
                   data->alm_code == alarmRemap[i].alarm_code ) {
                    
                    uint8_t alarm_byte_pos = alarmRemap[i].alarm_pos / 8;
                    uint8_t alarm_bit_pos = alarmRemap[i].alarm_pos % 8;
                    
                    if(alarm_byte_pos >= ALARM_MAX_BYTES) {
                        return true;
                    }
                    
                    return (alarmAllBits.bits[alarm_byte_pos] & (1 << alarm_bit_pos)) ? true : false;
                }
                break;

        }
        
    }
    
    return true;
}

void S07Y_Upload_data::alarm_pos_op(Alarm_data_t *data) {

    for(int i=0;i<ALARM_MAP_SIZE;i++) {
        
        switch(data->alm_code) {
            case TEMP_HIGH:
            case CELL_VOLT_HIGH:
            case CELL_VOLT_LOW:
            case CELL_VOLT_DIFF_HIGH:
            //case CELL_TEMP_DIFF_HIGH:
                if(data->alm_lvl == alarmRemap[i].alarm_lvl &&
                   data->alm_code == alarmRemap[i].alarm_code &&
                   data->id == alarmRemap[i].id) {
                    
                    uint8_t alarm_byte_pos = alarmRemap[i].alarm_pos / 8;
                    uint8_t alarm_bit_pos = alarmRemap[i].alarm_pos % 8;
                    
                    if(alarm_byte_pos >= ALARM_MAX_BYTES) {
                        return;
                    }
                    
                    if(data->alm_status == ALARMED) {
                        alarmAllBits.bits[alarm_byte_pos] |= (1 << alarm_bit_pos);
                    }else if(data->alm_status == ALARM_RESET) {
                        alarmAllBits.bits[alarm_byte_pos] &= ~(1 << alarm_bit_pos);
                    }
                    return;
                }
                break;
                
            default:
                if(data->alm_lvl == alarmRemap[i].alarm_lvl &&
                   data->alm_code == alarmRemap[i].alarm_code ) {
                    
                    uint8_t alarm_byte_pos = alarmRemap[i].alarm_pos / 8;
                    uint8_t alarm_bit_pos = alarmRemap[i].alarm_pos % 8;
                    
                    if(alarm_byte_pos >= ALARM_MAX_BYTES) {
                        return;
                    }
                    
                    if(data->alm_status == ALARMED) {
                        alarmAllBits.bits[alarm_byte_pos] |= (1 << alarm_bit_pos);
                    }else if(data->alm_status == ALARM_RESET) {
                        alarmAllBits.bits[alarm_byte_pos] &= ~(1 << alarm_bit_pos);
                    }
                    return;
                }
                break;

        }
        
    }
    
    return;
}


int S07Y_Upload_data::get_mvb_update_buff(unsigned char *buff,uint16_t heart) {
  unsigned short index = 0;

  unsigned char volt_index = 0;
  unsigned char temp_index = 0;
  
  buff[index++] = (unsigned char)(heart >> 8); //生命特征
  buff[index++] = (unsigned char)heart;
  
  buff[index++] = Sys_paras.ver.MC_EX_SW_major;//版本信息
  buff[index++] = Sys_paras.ver.MC_EX_SW_revision;
    
  buff[index++] = alarm_self_check_state;//自检状态   
  buff[index++] = alarm_self_flag.all;//备用
    
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt);
  
  //冲电电流 和 放电电流
  if(eth_data.batt_data.total_data.total_cur[0] > 0) {
    buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0] >> 8);
    buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0]);
    buff[index++] = 0;
    buff[index++] = 0;
  } else {   
    buff[index++] = 0;
    buff[index++] = 0;
    buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0] >> 8);
    buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0]);
  }

  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc / 10);
  
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soh / 10);
  
  
  buff[index++] = (uint8_t)(SCALE(eth_data.max_temp.temp,CELL_TEMP_RATE) + 55);//最高温度
  buff[index++] = (uint8_t)(SCALE(eth_data.min_temp.temp,CELL_TEMP_RATE) + 55);//最低温度
  buff[index++] = eth_data.max_temp.id;
  buff[index++] = eth_data.min_temp.id;
  

  buff[index++] = eth_data.min_volt_4.volt / 70 + ((eth_data.min_volt_4.volt % 70 >= 35) ? 1 : 0);
  buff[index++] = eth_data.max_volt_4.volt / 70 + ((eth_data.max_volt_4.volt % 70 >= 35) ? 1 : 0);
  buff[index++] = eth_data.min_volt_4.id;
  buff[index++] = eth_data.max_volt_4.id;
  
  buff[index++] = eth_data.min_volt_3.volt / 70 + ((eth_data.min_volt_3.volt % 70 >= 35) ? 1 : 0);
  buff[index++] = eth_data.max_volt_3.volt / 70 + ((eth_data.max_volt_3.volt % 70 >= 35) ? 1 : 0);
  buff[index++] = eth_data.min_volt_3.id;
  buff[index++] = eth_data.max_volt_3.id;
  
  uint16_t alarm_bits = 0;
  
  //总电压高
  typedef struct {
      Alarm_code_t alarm_code;
      uint8_t      mvb_alarm_pos;
      uint8_t      is_cell;
      uint8_t      cell_type;
  }MVB_AlarmInfor_t;
  
  const MVB_AlarmInfor_t TempArray[] = {
      {TOTAL_VOLT_HI,      0, 0,0},
      {TOTAL_VOLT_LOW,     1, 0,0},
      {CHARGE_CUR_HIGH,    2, 0,0},
      {DISCHARGE_CUR_HIGH, 3, 0,0},
      {CELL_VOLT_HIGH,     4, 1,4},
      {CELL_VOLT_LOW,      5, 1,4},
      {CELL_VOLT_HIGH,     6, 1,3},
      {CELL_VOLT_LOW,      7, 1,3},

      {TEMP_HIGH,          8, 1,0},
      {CELL_TEMP_DIFF_HIGH,9, 0,0},
      //{CELL_VOLT_DIFF_HIGH,10,1,4},
      //{CELL_VOLT_DIFF_HIGH,11,1,3},
      //{SOC_LOW,            12,0,0},
      //{SOC_LOW,            13,0,0},
      {SOH_LOW,            14,0,0},
      
  };
  
  Alarm_data_t alarm_data = {0};
  bool break_flag;
  for(int i=0;i<sizeof(TempArray)/sizeof(TempArray[0]);i++) {
    break_flag = false;  
    for(int lvl = ALARM_LVL_1; lvl < MAX_ALARM_LVL;lvl ++) {
        memset(&alarm_data,0,sizeof(Alarm_data_t));
        alarm_data.alm_code = TempArray[i].alarm_code;
        alarm_data.alm_lvl = (Alarm_lvl_t)lvl;
        if(TempArray[i].is_cell) { //单体
            int id = 0;
            for(int cell_index = 0;cell_index < CELL_CNT;cell_index++) {
                for(int k = 0; k < 12;k++) {
                    id++;
                    if(TempArray[i].cell_type != 0) { //三联体或者四联体电压高或者低
                        if(Cell_adc_config_paras[k].pack_bat_cnt != TempArray[i].cell_type) {
                            continue;
                        }
                    } 
                    alarm_data.id = id;
                    if(get_alarm_flag(&alarm_data)) {
                        alarm_bits |= 1 << TempArray[i].mvb_alarm_pos;
                        break_flag = true;
                        break;
                    }
                }
                
                if(break_flag) {
                    break;
                }
            }
            
        } else { //
            if(get_alarm_flag(&alarm_data)) {
                alarm_bits |= 1 << TempArray[i].mvb_alarm_pos;
                break_flag = true;
                break;
            }
        }
        
        if(break_flag) {
            break;
        }
    }
  }
    
    
    //4联体 压差过大
    alarm_data.alm_code = CELL_VOLT_DIFF_HIGH;
    alarm_data.id = 4;
    alarm_data.alm_lvl = ALARM_LVL_1;
    if(get_alarm_flag(&alarm_data)) {
        alarm_bits |= 1 << 10;
    }
    alarm_data.alm_lvl = ALARM_LVL_2;
    if(get_alarm_flag(&alarm_data)) {
        alarm_bits |= 1 << 10;
    }
    
    //3联体 压差过大
    alarm_data.alm_code = CELL_VOLT_DIFF_HIGH;
    alarm_data.id = 3;
    alarm_data.alm_lvl = ALARM_LVL_1;
    if(get_alarm_flag(&alarm_data)) {
        alarm_bits |= 1 << 11;
    }
    alarm_data.alm_lvl = ALARM_LVL_2;
    if(get_alarm_flag(&alarm_data)) {
        alarm_bits |= 1 << 11;
    }
    
    alarm_data.id = 3;
    alarm_data.alm_lvl = ALARM_LVL_2;
    if(get_alarm_flag(&alarm_data)) {
        alarm_bits |= 1 << 11;
    }
    
    alarm_data.alm_code = SOC_LOW;
    alarm_data.id = 0;
    alarm_data.alm_lvl = ALARM_LVL_2;
    if(get_alarm_flag(&alarm_data)) {
        alarm_bits |= 1u << 13;
    } else {
        alarm_data.alm_code = SOC_LOW;
        alarm_data.id = 0;
        alarm_data.alm_lvl = ALARM_LVL_1;
        if(get_alarm_flag(&alarm_data)) {
            alarm_bits |= 1 << 12;
        }
    }
    

  
    buff[index++] = alarm_bits;
    buff[index++] = alarm_bits >> 8;
    
    index += 4;

    if(heartbeat == 65535)
    {
        heartbeat = 0;
    }
    return index;
}

int S07Y_Upload_data::get_eth_update_buff(unsigned char *buff,uint16_t heart) {
  unsigned short index = 0;
  //unsigned int total_alarm = 0;
    
  short *temp_value = new short[Dev_paras.temp_cnt];
  short *volt_value = new short[Dev_paras.volt_cnt];
  if(temp_value == NULL || volt_value == NULL)
  {
    return 0;
  }
  unsigned char volt_index = 0;
  unsigned char temp_index = 0;
  buff[index++] = (unsigned char)(heart >> 8);
  buff[index++] = (unsigned char)heart;
  

  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.total_data.total_volt);
  
  buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0] >> 8);
  buff[index++] = (char)((short)eth_data.batt_data.total_data.total_cur[0]);
  
  buff[index++] = eth_data.batt_data.state;
  
  buff[index++] = alarm_self_check_state;//自检
  
  buff[index++] = alarm_self_flag.all;
  buff[index++] = Sys_paras.ver.MC_EX_SW_major;
  buff[index++] = (unsigned char)((Sys_paras.ver.MC_EX_SW_minjor << 4) | (Sys_paras.ver.MC_EX_SW_revision & 0x0f));
  
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc >> 8);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soc);
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soh >> 8); //S07Y 预留
  buff[index++] = (unsigned char)((unsigned short)eth_data.batt_data.soh);
  
  
  buff[index++] = eth_data.max_volt_3.id;
  buff[index++] = eth_data.min_volt_3.id;
  buff[index++] = eth_data.max_volt_4.id;
  buff[index++] = eth_data.min_volt_4.id;
  buff[index++] = eth_data.max_temp.id;
  buff[index++] = eth_data.min_temp.id;
  
  buff[index++] = (unsigned char)(eth_data.max_volt_3.volt >> 8);
  buff[index++] = (unsigned char)eth_data.max_volt_3.volt;
  buff[index++] = (unsigned char)(eth_data.min_volt_3.volt >> 8);
  buff[index++] = (unsigned char)eth_data.min_volt_3.volt;
  
  buff[index++] = (unsigned char)(eth_data.max_volt_4.volt >> 8);
  buff[index++] = (unsigned char)eth_data.max_volt_4.volt;
  buff[index++] = (unsigned char)(eth_data.min_volt_4.volt >> 8);
  buff[index++] = (unsigned char)eth_data.min_volt_4.volt;
  
  buff[index++] = (unsigned char)(eth_data.max_temp.temp >> 8);
  buff[index++] = (unsigned char)eth_data.max_temp.temp;
  buff[index++] = (unsigned char)(eth_data.min_temp.temp >> 8);
  buff[index++] = (unsigned char)eth_data.min_temp.temp;
  
  
#if 1
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
#endif
  
  for (int i = 0; i < Dev_paras.temp_cnt; i++) //24路温度
  {
    buff[index++] = (char)(temp_value[i] >> 8);
    buff[index++] = (char)(temp_value[i]);
  }

  for (int i = 0; i < Dev_paras.volt_cnt; i++)//24路电压
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
  

  for(int i=0;i<ALARM_MAX_BYTES;i++) {
    buff[index++] = alarmAllBits.bits[i];
  }
  
  
  if(heartbeat == 65535)
  {
    heartbeat = 0;
  }
  return index;
}

Max_data_t S07Y_Upload_data::find_max_volt_val(Cell_data_t *cell_data)
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
  if(ret.id == 1 && ret.volt ==  0)
  {
    memset(&ret, 0, sizeof(Max_data_t));
  }
  return ret;
}

Max_data_t S07Y_Upload_data::find_max_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt) {
  Max_data_t ret = {1, 0};
  unsigned char volt_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        volt_index++;
        if (cell_data[i].acq_val[j] > ret.volt && Cell_adc_config_paras[j].pack_bat_cnt == bat_cnt)
        {
          ret.volt = cell_data[i].acq_val[j];
          ret.id = volt_index;
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

Min_data_t S07Y_Upload_data::find_min_volt_val(Cell_data_t *cell_data)
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
        if (cell_data[i].acq_val[j] < ret.volt \
            && cell_data[i].acq_val[j] != 0 \
            && volt_index != 11 && volt_index != 22)
        {
          ret.volt = cell_data[i].acq_val[j];
          ret.id = volt_index;
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

Min_data_t S07Y_Upload_data::find_min_volt_val(Cell_data_t *cell_data,uint8_t bat_cnt) {
  Min_data_t ret = {1, 30000};
  unsigned char volt_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  {
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
      {
        volt_index++;
        if (cell_data[i].acq_val[j] < ret.volt \
            && cell_data[i].acq_val[j] != 0 \
            && Cell_adc_config_paras[j].pack_bat_cnt == bat_cnt)
        {
          ret.volt = cell_data[i].acq_val[j];
          ret.id = volt_index;
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


Max_data_t S07Y_Upload_data::find_max_temp_val(Cell_data_t *cell_data)
{
  Max_data_t ret;// = {1, -1000};
  ret.id = 1;
  ret.temp = -1000;
  unsigned char temp_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  {
      
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_TEMP && Cell_adc_config_paras[j].is_enable == true)
      {
        temp_index++;
        if (cell_data[i].acq_val[j] > ret.temp)
        {
          ret.temp = cell_data[i].acq_val[j];
          ret.id = temp_index;
        }
      }
    }
  }
  if(ret.id == 1 && ret.temp ==  -1000)
  {
    memset(&ret, 0, sizeof(Max_data_t));
  }
  return ret;
}


Min_data_t S07Y_Upload_data::find_min_temp_val(Cell_data_t *cell_data)
{
  Min_data_t ret = {1, 3000};
  unsigned char temp_index = 0;
  for (int i = 0; i < CELL_CNT; i++)
  { 
      
    for (int j = 0; j < ACQ_MAX_CNT; j++)
    {
      if (Cell_adc_config_paras[j].acq_type == TYPE_TEMP && Cell_adc_config_paras[j].is_enable == true)
      {
        temp_index++;
        if (cell_data[i].acq_val[j] < ret.temp)
        {
          ret.temp = cell_data[i].acq_val[j];
          ret.id = temp_index;
        }
      }
    }
  }
  if(ret.id == 1 && ret.temp ==  3000)
  {
    memset(&ret, 0, sizeof(Min_data_t));
  }
  return ret;
}

void S07Y_Upload_data::update_batt_data(void)
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
  Max_data_t max_v3 = find_max_volt_val(batt_data->cell_data,3);
  Min_data_t min_v3 = find_min_volt_val(batt_data->cell_data,3);
  Max_data_t max_v4 = find_max_volt_val(batt_data->cell_data,4);
  Min_data_t min_v4 = find_min_volt_val(batt_data->cell_data,4);
  Max_data_t max_t = find_max_temp_val(batt_data->cell_data);
  Min_data_t min_t = find_min_temp_val(batt_data->cell_data);
  
  eth_data.max_volt_3.volt = max_v3.volt;
  eth_data.max_volt_3.id = max_v3.id;
  eth_data.min_volt_3.volt = min_v3.volt;
  eth_data.min_volt_3.id = min_v3.id;
  
  eth_data.max_volt_4.volt = max_v4.volt;
  eth_data.max_volt_4.id = max_v4.id;
  eth_data.min_volt_4.volt = min_v4.volt;
  eth_data.min_volt_4.id = min_v4.id;
  
  eth_data.max_temp.volt = max_t.volt;
  eth_data.max_temp.id = max_t.id;
  eth_data.min_temp.volt = min_t.volt;
  eth_data.min_temp.id = min_t.id;
}

unsigned char S07Y_Upload_data::judge_complex_alarm_state(Alarm_data_t *alarm_data)
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
  else if(alarm_data->alm_code == TOTAL_VOLT_DEVIATE_HI 
      || alarm_data->alm_code == TOTAL_VOLT_LOW 
      || alarm_data->alm_code == CHARGE_CUR_HIGH 
      || (alarm_data->alm_code == SOC_LOW && alarm_data->alm_lvl == ALARM_LVL_1)
      || alarm_data->alm_code == SOH_LOW 
      || (alarm_data->alm_code == TEMP_HIGH && alarm_data->alm_lvl == ALARM_LVL_1))
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

void S07Y_Upload_data::update_alarm_data(void)
{
  if (alm_data == NULL)
  {
    return;
  }
  
  //short pos = 0;
  unsigned char complex_alarm_pos = judge_complex_alarm_state(alm_data);
  
  alarm_pos_op(alm_data);
}


#if (USE_FREE_RTOS)
void S07Y_Upload_data::set_alm_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  alm_update_queue = handle;
  alm_update_msg = _msg;
  alm_update_timeout = _timeout;
}

void S07Y_Upload_data::set_data_update_queue_handle(QueueHandle_t handle, Queue_msg _msg, unsigned int _timeout)
{
  data_update_queue = handle;
  data_update_msg = _msg;
  data_update_timeout = _timeout;
}
#endif

void S07Y_Upload_data::update(Alarm_data_t *data, unsigned char opt)
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

void S07Y_Upload_data::update(Batt_data_t *data, unsigned char opt)
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


void S07Y_Upload_data::alarm_self_check_set_status(AlarmSelfCheckStatus_t status) {
    alarm_self_check_state = status;
}
void S07Y_Upload_data::alarm_self_check(Batt_data_t *data) {
    //temp check.
 
    float voltage_sum = 0;
    for (int i = 0; i < CELL_CNT; i++)
    {
        for (int j = 0; j < ACQ_MAX_CNT; j++)
        {
            if (Cell_adc_config_paras[j].acq_type == TYPE_VOLT && Cell_adc_config_paras[j].is_enable == true)
            {
                voltage_sum += SCALE(data->cell_data[i].acq_val[j],CELL_TEMP_RATE);
            }
        }
    }
    
    if(fabs(voltage_sum - data->total_data.total_volt) > TOTAL_VOLT_ERR_VAL) {
        alarm_self_flag.bits.volt_err = 1;
    } else {
       alarm_self_flag.bits.volt_err = 0;
    }
    
    if(alarm_self_flag.bits.comm_err || alarm_self_flag.bits.temp_err ) {
        alarm_self_check_state = AlarmSelfCheckFailed;
    }
    else {
        alarm_self_check_state = AlarmSelfCheckOk;
    }

    
}

short S07Y_Upload_data::eth_alarm_pos(Alarm_code_t alarm_code)
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

S07Y_Upload_data::~S07Y_Upload_data(void)
{
}
