/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      数据类型定义头文件
*
* 版本:
* V1.0 2019-05-07 初始程序编写 
***********************************************************/

#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include "defines.h"

typedef enum _tag_train_line_
{
  CHANGSHA_LINE_3 = 1,
  DALIAN_LINE_JINPU,
  XIAMEN_LINE_2,
  WUHAN_LINE_2,
  BEIJING_LINE_7,
  CHENGDU_LINE_9,
  GUANGZHOU_LINE_3,
  HUHEHAOTE_LINE_1,
  TIANJIN_Z4,
  SUZHOU_12V,
  WUHAN_LINE5,
  QINGDAO_LINE6,
  QINGDAO_LINE2,
  CHANGSHA_LIN3,
  GROUND_48_LINE,
  YATONGDA,
  GUANGZHOU_18_22,
  KENUOER,
  KANGPU,
  XIYAN_GUANG7,
  SHENZHEN_16,
  CHANGSHA_6,
  NEW_YATONGDA,
  SHAOXING_2,
} Train_line;

typedef struct _tag_battery_infomation_
{
  // battery installation train number
  Train_line line;
  // battery nominal capacity
  unsigned short nomial_cap;
  // battery group count
  unsigned short group_cnt;
  // battery group voltage
  unsigned short group_volt;
} Batt_info_t;

typedef struct _tag_sys_version_
{
  unsigned char MC_SW_major;
  unsigned char MC_SW_minjor;
  unsigned char MC_SW_revision;

  unsigned char MC_HW_major;
  unsigned char MC_HW_minjor;
  unsigned char MC_HW_revision;
  // for train display
  unsigned char MC_EX_SW_major;
  unsigned char MC_EX_SW_minjor;
  unsigned char MC_EX_SW_revision;

  unsigned char node_SW_major;
  unsigned char node_SW_minjor;
  unsigned char node_SW_revision;

  unsigned char node_HW_major;
  unsigned char node_HW_minjor;
  unsigned char node_HW_revision;

} Sys_version_t;

typedef struct _tag_state_thr_
{
  float fast_to_float_thr;
  float float_to_fast_thr;
  float charge_to_discharge_thr;
  float discharge_to_charge_thr;
} Batt_state_thr_t;


#include "proj_data_type.h"

#endif // _DATA_TYPE_H_
