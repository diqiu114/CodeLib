/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池容量估算充电处理接口
***********************************************************/

#ifndef _BATT_CHARGE_PROC_IF_H_
#define _BATT_CHARGE_PROC_IF_H_
#include "..\batt_cap_data_type.h"

class Batt_charge_proc_if
{
public:
  virtual float charge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours) = 0;
  virtual ~Batt_charge_proc_if(){};
};

#endif // _BATT_CHARGE_PROC_IF_H_
