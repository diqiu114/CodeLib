/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池容量估算充电处理接口
***********************************************************/

#ifndef _CHARGE_FIXED_METHOD_H_
#define _CHARGE_FIXED_METHOD_H_
#include "batt_charge_proc_if.h"

class Charge_fixed_method : public Batt_charge_proc_if
{
public:
  virtual float charge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours)
  {
    return (cur_cap + batt_data.cur * update_clk_in_hours);
  }
  virtual ~Charge_fixed_method(){};
};

#endif // _CHARGE_FIXED_METHOD_H_
