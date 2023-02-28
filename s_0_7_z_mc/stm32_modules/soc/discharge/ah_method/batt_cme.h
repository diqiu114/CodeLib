/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-10-10
 * 
 * @brief charge memory effect of Ni/Cd batteries
 * 
 * ***********************************************************
 */

#ifndef _CHARGE_CME_H_
#define _CHARGE_CME_H_

#include "..\data_convert\data_convert_if.h"
#include "..\..\batt_cap_data_type.h"

#define BATT_CME_DISCHARGED_CAP_MIN (0.0f)
// 最大值为实测模拟最大值, 超过最大累计容量后, 可放出的电量是相同的.
#define BATT_CME_DISCHARGED_CAP_MAX (1126.579583f)

class Batt_cme
{
public:
  Batt_cme(float _nomial_cap, Data_convert_if *cnv);
  bool set_addup_discharged_cap(float cap, bool store = false);
  bool dec_addup_discharged_cap(float cap, bool store = false);
  bool update_addup_discharged_cap(void);
  float get_addup_discharged_cap(void);
  void set_std_cur_rate(float rate);
  float get_cme(float cur_rate);
  void set_addup_cap_store_callback(cap_store func);
  bool store_addup_cap(void);
  ~Batt_cme();

private:
  Data_convert_if *data_convert;
  float nomial_cap;
  float addup_discharged_cap;
  float addup_discharged_cap_for_calc;
  float std_cur_rate;
  cap_store store_func;
};

#endif // _CHARGE_CME_H_
