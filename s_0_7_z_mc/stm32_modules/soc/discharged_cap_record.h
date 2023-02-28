/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      记录蓄电池一次完整充放电的容量
* 当蓄电池放电时，减小已放电容量，已放电容量值为-xxx ~ 0。
* 当蓄电池充电时，将已增大已放到容量,最大值为0。
***********************************************************/

#ifndef _DISCHARGED_CAP_RECORD_H_
#define _DISCHARGED_CAP_RECORD_H_

#include "batt_cap_data_type.h"

// 已放电容量最大为0, 正常为负数
#define BATT_DISCHARGED_CAP_MAX (0.0f)

// 充放电转换效率50% ~ 100%之间
#define BATT_CAP_CONVERT_RATE_MAX (1.0f)
#define BATT_CAP_CONVERT_RATE_MIN (0.5f)

class Discharged_cap_record
{
public:
  Discharged_cap_record(float _discharge_cap_min);
  ~Discharged_cap_record();
  
  bool set_discharged_cap(float cap = BATT_DISCHARGED_CAP_MAX, bool store = false);
  float get_discharged_cap(void);
  float get_dishcarged_cap_min(void);

  bool dec_dishcarged_cap(float charge_cap);
  bool inc_dishcarged_cap(float charge_cap);

  void set_discharged_cap_store_callback(cap_store func);
  bool store_discharged_cap(void);
  
  float get_charge_efficiency(void);
  bool set_charge_efficiency(float charge_effi);

private:
  float discharged_cap;
  float discharged_cap_min;
  float charge_efficiency;
  cap_store discharged_cap_store_callback;

};

#endif // _DISCHARGED_CAP_RECORD_H_
