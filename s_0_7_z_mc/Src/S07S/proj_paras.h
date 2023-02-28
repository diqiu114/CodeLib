/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      项目参数结构体定义及默认参数设置
*
* 版本:
* V1.0 2019-05-20 初始化版本编写 
***********************************************************/

#ifndef _PROJ_PARAS_H_
#define _PROJ_PARAS_H_

#include <stdbool.h>
#include "defines.h"
#include "data_type.h"

typedef struct _tag_common_paras_
{
  unsigned int dev_id;
  Batt_info_t batt_info;
  Sys_version_t ver;
} Sys_paras_t;

typedef struct _tag_dev_paras_
{
#if USE_MVB
  Mvb_module_cfg mvb[MC_CNT_PER_TRAIN];
#endif
    
#if USE_ETH
  Eth_Module_Cfg eth_paras[MC_CNT_PER_TRAIN];
#endif
  unsigned char soc_init;
  float soc_actual;
  Calib_t calib;
  Rate_t rate; 
  unsigned char volt_cnt;
  unsigned char temp_cnt;
} Dev_paras_t;


typedef struct _tag_user_paras_
{
  Period_t         period;
  Batt_state_thr_t batt_state_thr;
  Alarm_thres_t    alm_thr;
} User_paras_t;


typedef struct {
    uint32_t     crc32;
    float        soc;
    float        soh;
    uint32_t     device_id;
    User_paras_t user_para;
    Calib_t      calib;  
    uint32_t     reload_flag;
    //uint32_t     backup[100];
}Paras_NoInit_t;

extern const Cell_adc_config_paras_t  Cell_adc_config_paras[ACQ_MAX_CNT];
extern Dev_paras_t Dev_paras;
extern User_paras_t User_paras;
extern Soh_record_t Soh_record;
extern Sys_paras_t   Sys_paras;
extern Batt_data_t Batt_data_buff;
extern Cell_sample_data_t cell_data_adc_voltage[CELL_CNT];

extern Paras_NoInit_t paraNoInit;

#endif // _PROJ_PARAS_H_
