/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      浓度学习法蓄电池容量估算放电处理
***********************************************************/

#ifndef _DL_METHOD_DISCHARGE_H_
#define _DL_METHOD_DISCHARGE_H_

#include "..\batt_discharge_proc_if.h"
#include "..\..\..\deep_learning\dl_model_if.h"

#define BATT_FEATURE_CNT (2)
typedef bool (*data_normalize) (float* data, unsigned int data_cnt);

class Dl_method_discharge : public Batt_discharge_proc_if
{
public:
  Dl_method_discharge(Dl_model_if* _dl_model);
  virtual ~Dl_method_discharge();
  virtual float discharge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours);
  bool set_preprocess_callback(data_normalize func);
  bool set_postprocess_callback(data_normalize func);
private:
  Dl_model_if *dl_model;
  float batt_feature[BATT_FEATURE_CNT];
  data_normalize preprocess;
  data_normalize postprocess;
};

#endif // _DL_METHOD_DISCHARGE_H_
