/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      battery inital capacity demarcation
* 用于蓄电池第一次安装蓄电池监测系统,蓄电池监测系统通过蓄电池电压以及放电电流
* 标定蓄电池初始容量
***********************************************************/

#ifndef _BATT_CAP_H_
#define _BATT_CAP_H_
#include "batt_cap_data_type.h"
#include "self_discharge.h"
#include "batt_cap_adj.h"
#include ".\discharge\batt_discharge_proc_if.h"
#include ".\charge\batt_charge_proc_if.h"
#include "batt_cap_init.h"
#include "discharged_cap_record.h"

// 正常电池使用时，不存在超过50%衰减的情况
#define AGING_FACTOR_MIN (0.5f)

// battery monitor system operation temperature ：-25℃ ~ +70℃
#define TEMP_COMPENSATION_LOWER_LIMIT (-25.0f)
#define TEMP_COMPENSATION_UPPER_LIMIT (70.0f)
// vrla best temperature 
#define TEMP_DEFAULT (25.0f)

class Batt_cap_params
{
  public:
  Batt_cap_params(float _nomial_cap, 
                  float _cur_upper_limit, 
                  float _cur_lower_limit, 
                  float _charge_cur_thr, 
                  float _discharge_cur_thr, 
                  unsigned int _update_clk_in_ms, 
                  float _aging_factor = 1.0f,
                  float _temp_default = TEMP_DEFAULT,
                  float _temp_lower_limit = TEMP_COMPENSATION_LOWER_LIMIT,
                  float _temp_upper_limit = TEMP_COMPENSATION_UPPER_LIMIT)
  {
    nomial_cap = _nomial_cap;
    cur_upper_limit = _cur_upper_limit;
    cur_lower_limit = _cur_lower_limit;
    charge_cur_thr = _charge_cur_thr;
    discharge_cur_thr = _discharge_cur_thr;
    update_clk_in_ms = _update_clk_in_ms;
    if( _aging_factor > AGING_FACTOR_MIN )
    {
      aging_factor = _aging_factor;
    }
    else
    {
      aging_factor = 1.0f;
    }
    temp_default = _temp_default;
    temp_lower_limit = _temp_lower_limit;
    temp_upper_limit = _temp_upper_limit;
  }

  float nomial_cap;
  float cur_upper_limit;
  float cur_lower_limit;
  float charge_cur_thr;
  float discharge_cur_thr;
  unsigned int update_clk_in_ms;
  float aging_factor;
  float temp_default;
  float temp_lower_limit;
  float temp_upper_limit;
};

class Batt_cap
{
public:
  Batt_cap(Batt_cap_params* _params,
          Batt_discharge_proc_if* _discharge_proc,
          Batt_charge_proc_if* _charge_proc,
          Batt_cap_adj* _adjust = NULL);
  ~Batt_cap();

  float update_cap(Batt_info &cap_para);
  bool set_cap(float cap_rate, bool store = false);
  float get_cap(void);
  float get_nomial_cap(void);
  float get_cap_rate(void);
  void set_update_clk(unsigned int clk_in_ms);

  void set_cap_store_callback(cap_store func);
  float self_discharge_calib(float ts_diff);

  void set_self_dishcarge(Self_discharge* _self_discharge);
  Self_discharge* get_self_discharge(void);

  void set_cap_init(Batt_cap_init* _cap_init);
  Batt_cap_init* get_cap_init(void);

  void set_discharged_cap_record(Discharged_cap_record* _discharged_record);
  Discharged_cap_record* get_discharged_cap_record(void);

private:
  float charge_process(Batt_info &para);
  float discharge_process(Batt_info &para);
  float soc_limit(float batt_cap);

  Batt_cap_params* params;
  float update_clk_in_hours;

  Batt_discharge_proc_if* discharge_proc;
  Batt_charge_proc_if* charge_proc;
  Batt_cap_adj* adjust;

  Self_discharge* self_discharge;
  Batt_cap_init* cap_init;
  Discharged_cap_record* discharged_record;
  
  float cur_cap;
  cap_store cap_store_callback;
  Batt_info calc_data;
};
#endif // _BATT_CAP_H_
