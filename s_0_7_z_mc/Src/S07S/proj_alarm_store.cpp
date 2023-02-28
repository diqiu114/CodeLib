#include "proj_alarm_store.h"
#include "paras.h"
#include "crc32.h"
#include "s07y_upload_data.h"
#include "proj_class_init.h"

Proj_alarm_store::Proj_alarm_store(File *file) : Alarm_data_store(file)
{
}

bool Proj_alarm_store::store_data(void)
{
  if(alarm_data_buff.alm_status == ALARM_RESET) {
      if(!Train_data->get_alarm_flag(&alarm_data_buff)) {
          return true;
      }
  } 
    
  if (rtc != NULL)
  {
    alarm_data.ts = rtc->get_ts();
  }

  // fill data
  alarm_data.total_data = alarm_data_buff.batt_data.total_data;
  alarm_data.state = alarm_data_buff.batt_data.state;
  alarm_data.soc = alarm_data_buff.batt_data.soc;
  alarm_data.soh = alarm_data_buff.batt_data.soh;
  alarm_data.alm_status = alarm_data_buff.alm_status;
  alarm_data.alm_lvl = alarm_data_buff.alm_lvl;
  alarm_data.alm_code = alarm_data_buff.alm_code;
  
  
  if( alarm_data_buff.id != 0 && alarm_data_buff.alm_code != CELL_VOLT_DIFF_HIGH)
  {
      uint8_t box_id = 0;
    if(alarm_data_buff.alm_code == CELL_VOLT_HIGH || alarm_data_buff.alm_code == CELL_VOLT_LOW)
    {
       if(alarm_data_buff.id > Dev_paras.volt_cnt / CELL_CNT) {
            box_id = 1;
       }
       alarm_data.cell_data = alarm_data_buff.batt_data.cell_data[box_id];
    }
    if(alarm_data_buff.alm_code == TEMP_HIGH)
    {
       if(alarm_data_buff.id > Dev_paras.temp_cnt / CELL_CNT) {
            box_id = 1;
       }
       alarm_data.cell_data = alarm_data_buff.batt_data.cell_data[box_id];
    } 
  }
  else
  {
    extern S07Y_Upload_data* Train_data;
    if(alarm_data_buff.alm_code == CELL_VOLT_DIFF_HIGH)
    {
        Max_data_t max_v = Train_data->find_max_volt_val(alarm_data_buff.batt_data.cell_data,alarm_data_buff.id);
        Min_data_t min_v = Train_data->find_min_volt_val(alarm_data_buff.batt_data.cell_data,alarm_data_buff.id);
        if(max_v.id == 0 || min_v.id == 0) {
            alarm_data.cell_data = alarm_data_buff.batt_data.cell_data[0];
        } else {
            memset(&alarm_data.cell_data, 0, sizeof(alarm_data.cell_data));
            alarm_data.cell_data.acq_val[0] = max_v.id;
            alarm_data.cell_data.acq_val[1] = max_v.volt;
            
            alarm_data.cell_data.acq_val[2] = min_v.id;
            alarm_data.cell_data.acq_val[3] = min_v.volt;
        }
    } else if(alarm_data_buff.alm_code == CELL_TEMP_DIFF_HIGH) {
        Max_data_t max_v = Train_data->find_max_temp_val(alarm_data_buff.batt_data.cell_data);
        Min_data_t min_v = Train_data->find_min_temp_val(alarm_data_buff.batt_data.cell_data);
        if(max_v.id == 0 || min_v.id == 0) {
            alarm_data.cell_data = alarm_data_buff.batt_data.cell_data[0];
        } else {
            memset(&alarm_data.cell_data, 0, sizeof(alarm_data.cell_data));
            alarm_data.cell_data.acq_val[0] = max_v.id;
            alarm_data.cell_data.acq_val[1] = max_v.temp;
            
            alarm_data.cell_data.acq_val[2] = min_v.id;
            alarm_data.cell_data.acq_val[3] = min_v.temp;
        }
    }
    else
    {
      memset(&alarm_data.cell_data, 0, sizeof(alarm_data.cell_data));
    }
  }
  alarm_data.cell_data.id = alarm_data_buff.id;
  
  alarm_data.crc32 = CRC_Get32(((const uint8_t *)(&alarm_data)) + 4, sizeof(Alarm_store_data_t) - 4);
  
  if (file->write((unsigned char *)(&alarm_data), sizeof(Alarm_store_data_t)) == FR_OK )
  {
    return true;
  }
  else
  {
    return false;
  }
}

Proj_alarm_store::~Proj_alarm_store()
{
}
