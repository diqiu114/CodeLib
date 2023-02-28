/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      AH积分法蓄电池容量估算放电处理
***********************************************************/

#ifndef _AH_METHOD_DISCHARGE_PROC_H_
#define _AH_METHOD_DISCHARGE_PROC_H_

#include "..\batt_discharge_proc_if.h"
#include "data_convert\data_convert_if.h"
#include "batt_cme.h"
#include <stdlib.h>

class Ah_method_discharge : public Batt_discharge_proc_if
{
public:
  Ah_method_discharge(
          float _nomial_cap,
          Data_convert_if* _cur_format = NULL,
          Data_convert_if* _temp_compensation = NULL,
          Batt_cme* _cme = NULL);
  virtual ~Ah_method_discharge();

  virtual float discharge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours);

  void set_charge_memory_effect(Batt_cme* _cme);

private:
  float nomial_cap;
  Data_convert_if* cur_format;
  Data_convert_if* temp_compensation;
  Batt_cme* cme;
};

#endif // _AH_METHOD_DISCHARGE_PROC_H_
