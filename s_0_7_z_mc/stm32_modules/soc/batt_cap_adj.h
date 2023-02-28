/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池充放电过程中拐点修正,包括充电修正和放电修正
* 充电时，可以根据温度补偿与浮充电压的关系，调整满电修正
* 放电时，可以根据电流与截止电压的关系，调整修正零电时的电压
***********************************************************/

#ifndef _BATT_CAP_ADJ_H_
#define _BATT_CAP_ADJ_H_
#include "batt_cap_data_type.h"
#include "data_convert\data_convert_if.h"
#include <vector>

using namespace std;

class Batt_cap_adj_params
{
  public:
  Batt_cap_adj_params()
  {
    rate = 1;
  }

  Batt_cap_adj_params(Batt_info* _batt_threshold, 
                      float _rate, 
                      float _terminal_cap, 
                      float _temp_min,
                      float _temp_max,
                      Data_convert_if* _volt_convert = NULL, 
                      Data_convert_if* _cutoff_volt_convert = NULL )
  {
    batt_threshold = _batt_threshold;
    rate = _rate;
    terminal_cap = _terminal_cap;
    volt_convert = _volt_convert;
    cutoff_volt_convert = _cutoff_volt_convert;
    temp_min = _temp_min;
    temp_max = _temp_max;
  }
  Batt_info* batt_threshold;
  Data_convert_if* volt_convert;
  Data_convert_if* cutoff_volt_convert;
  float rate;
  float terminal_cap;
  float temp_min;
  float temp_max;
};

class Batt_cap_adj
{
public:
  Batt_cap_adj(float _batt_cap_min, float _batt_cap_max);
  ~Batt_cap_adj();

  bool add_discharge_condition(Batt_cap_adj_params &params);
  bool modify_discharge_condition(Batt_cap_adj_params &params, int idx);
  bool del_discharge_condition(int idx);

  bool add_charge_condition(Batt_cap_adj_params &params);
  bool modify_charge_condition(Batt_cap_adj_params &params, int idx);
  bool del_charge_condition(int idx);

  float charge_adj(float cur_batt_cap, Batt_info* cur_batt_info);
  float discharge_adj(float cur_batt_cap, Batt_info* cur_batt_info);
  
private:
  vector<Batt_cap_adj_params> discharge_conditions;
  vector<Batt_cap_adj_params> charge_conditions;
  float batt_cap_min;
  float batt_cap_max;
};

#endif // _BATT_CAP_ADJ_H_
