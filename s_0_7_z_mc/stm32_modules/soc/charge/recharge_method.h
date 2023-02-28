/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池充电处理
* 根据蓄电池已放电容量以及蓄电池充电效率，估算充满所需的容量，称之为回充法
* 注意：在充电时，需要实时调用set_discharged_cap更新当前已放电容量，否则估算不准确。
***********************************************************/

#ifndef _RECHARGE_METHOD_PROC_
#define _RECHARGE_METHOD_PROC_

#include "..\batt_cap_data_type.h"
#include "batt_charge_proc_if.h"
#include "..\discharged_cap_record.h"


class Recharge_method : public Batt_charge_proc_if
{
public:
  Recharge_method(float _nomial_batt_cap);
  virtual ~Recharge_method();

  virtual float charge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours);
  
  bool set_discharged_cap(float cap = BATT_DISCHARGED_CAP_MAX);

  float get_charge_efficiency(void);
  bool set_charge_efficiency(float charge_effi);

private:
  float nomial_batt_cap;
  float discharged_cap;
  float discharged_cap_min;
  cap_store discharged_cap_store_callback;
};

#endif // _RECHARGE_METHOD_PROC_
