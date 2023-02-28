/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      项目数据类型定义头文件
*
* 版本:
* V1.0 2019-06-20 初始程序编写 
***********************************************************/

#ifndef _PROJ_DATA_TYPE_H_
#define _PROJ_DATA_TYPE_H_
#include "defines.h"
#include "proj_def.h"
#include "eng_calib.h"
#include "eng_transfer.h"
#include "mvb_module.h"
#include "eth_module.h"
#include "data_convert\polynomial1.h"
#include "data_convert\polynomial3.h"


// unit seconds
typedef struct _tag_period_
{
  unsigned int acquire;
  unsigned int cell_comm;
  unsigned int store;
} Period_t;

typedef enum _batt_state_
{
  FAST_CHARGE = 1,
  DISCHARGE,
  FLOAT_CHARGE
} Batt_state_t;

typedef struct _tag_total_battery_data_
{
  float total_volt;
  float total_cur[CUR_CH_CNT];
  float avg_curr;
  float amb_temp;
  float temp[COUNT_OF_TEMP];
} Tb_data_t;


typedef enum Adc_acq_mode
{
  INSIDE_ADC,
  ADC_128D818,
  MCP3221A5T
} Adc_acq_mode_e;

typedef enum Adc_acq_type
{
  TYPE_TEMP,
  TYPE_VOLT,
  TYPE_CURRENT,
  TYPE_MAX
} Adc_acq_type_e;

typedef struct _tag_adc_config_params_
{
  bool           is_enable;
  uint8_t        pack_bat_cnt;
  Adc_acq_type_e acq_type;
}Cell_adc_config_paras_t;

typedef struct _tag_cell_data_
{
  unsigned char id;
  short acq_val[ACQ_MAX_CNT];
} Cell_data_t;

typedef struct _tag_cell_sample_data_
{
  unsigned char id;
  float    acq_val[ACQ_MAX_CNT];
} Cell_sample_data_t;

typedef struct _tag_batt_t_
{
  Tb_data_t total_data;
  float soc;
  float soh;
  Batt_state_t state;
  Cell_data_t cell_data[CELL_CNT];
  //Cell_sample_data_t cell_data_adc_voltage[CELL_CNT];
} Batt_data_t;

typedef struct _tag_history_data_
{
  unsigned int crc32;
  unsigned int ts; 
  Batt_data_t batt_data;
} History_data_t;

typedef union {
    unsigned int i;
    float        f;
}KB_t;

typedef union {
    unsigned int u;
    int          i;
    float        f;
}FI_Conv_t;

typedef struct _tag_calib_
{
	Polynomial_1 total_batt[VOLT_CH_CNT + CUR_CH_CNT + COUNT_OF_TEMP];
} Calib_t;

typedef struct _tag_rate_
{
  Polynomial_1 total_batt[VOLT_CH_CNT + CUR_CH_CNT];
  Polynomial_3 temp_rate[COUNT_OF_TEMP]; 
} Rate_t;

typedef enum _tag_alarm_lvl_
{ 
  MIN_ALARM_LVL = 0,
  ALARM_LVL_1 = 0,
  ALARM_LVL_2 = 1,
  MAX_ALARM_LVL
} Alarm_lvl_t;

#if S07Y
typedef enum _tag_alarm_code_
{	
  TOTAL_VOLT_HI = 0,
  TOTAL_VOLT_LOW,
  TOTAL_VOLT_DEVIATE_HI,
  TEMP_HIGH,
  CHARGE_CUR_HIGH,
  DISCHARGE_CUR_HIGH,
  SOC_LOW,
  SOH_LOW,
  CELL_VOLT_HIGH,
  CELL_VOLT_LOW,
  CELL_VOLT_DIFF_HIGH,
  CELL_TEMP_DIFF_HIGH,
  CELL_COMM_ERROR,
  
  MAX_ALARM_TYPE
} Alarm_code_t;

#elif S07S
typedef enum _tag_alarm_code_
{	
  TOTAL_VOLT_LOW = 0,
  TOTAL_VOLT_DEVIATE_HI,
  TEMP_HIGH,
  CHARGE_CUR_HIGH,
  SOC_LOW,
  SOH_LOW,
  CELL_VOLT_HIGH,
  CELL_VOLT_LOW,
  CELL_VOLT_DIFF_HIGH,
  CELL_COMM_ERROR,
  MAX_ALARM_TYPE
} Alarm_code_t;
#elif(S07R)
typedef enum _tag_alarm_code_
{	
  TOTAL_VOLT_HI = 0,
  TOTAL_VOLT_LOW,
  TEMP_HIGH,
  CHARGE_CUR_HIGH,
  DISCHARGE_CUR_HIGH,
  SOC_LOW,
  CELL_VOLT_HIGH,
  CELL_VOLT_LOW,
  CELL_VOLT_DIFF_HIGH,
  CELL_COMM_ERROR,
  MAX_ALARM_TYPE
} Alarm_code_t;
#endif

typedef struct _tag_alarm_thr_
{
    float trigger_thress[MAX_ALARM_TYPE][MAX_ALARM_LVL]; 
	float reset_thress[MAX_ALARM_TYPE];
	unsigned int trigger_delays[MAX_ALARM_TYPE][MAX_ALARM_LVL];
	unsigned int reset_delays[MAX_ALARM_TYPE];
} Alarm_thres_t;

typedef struct _tag_alarm_data_
{
  unsigned int ts;
  unsigned char alm_status;
  Alarm_code_t alm_code;
  Alarm_lvl_t alm_lvl;
  unsigned char id;
  Batt_data_t batt_data;
} Alarm_data_t;

typedef struct _tag_alarm_store_data_
{
  unsigned int crc32;
  unsigned int ts;
  unsigned char alm_status;
  Alarm_code_t alm_code;
  Alarm_lvl_t alm_lvl;
  Tb_data_t total_data;
  float soc;
  float soh;
  Batt_state_t state;
  Cell_data_t cell_data;
} Alarm_store_data_t;

typedef struct _tag_soh_record_
{
  unsigned int last_update_ts;
  float soh;
} Soh_record_t;

typedef enum _msg_type_
{
  // history data store
  QM_HIST_DATA_STORE = 0x01,
  // alarm check
  QM_ALM_CHK,
  // alarm data store
  QM_ALM_DATA_STORE,
  QM_UPLOAD_DATA_UPDATE,
  QM_UPLOAD_ALM_DATA_UPDATE,
  QM_CNT_MAX,
}Queue_msg;

#endif // _PROJ_DATA_TYPE_H_
