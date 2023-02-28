/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池充电处理
* 根据蓄电池固定充电效率计算蓄电池充电，从0%~100%整体效率为90%
***********************************************************/

#ifndef _CHARGE_EFFI_METHOD_H_
#define _CHARGE_EFFI_METHOD_H_

#include "..\batt_cap_data_type.h"
#include "batt_charge_proc_if.h"

class Charge_effi_method : public Batt_charge_proc_if
{
public:
  Charge_effi_method(float _nomial_cap);
  virtual ~Charge_effi_method();
  virtual float charge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours);
private:
  float nomial_cap;
};

#endif // _CHARGE_EFFI_METHOD_H_
