/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      battery inital capacity demarcation
* 用于蓄电池第一次安装蓄电池监测系统,蓄电池监测系统通过蓄电池电压以及放电电流
* 标定蓄电池初始容量
***********************************************************/

#ifndef _BATT_CAP_INIT_H_
#define _BATT_CAP_INIT_H_
#include <vector>
#include "data_convert\data_convert_if.h"
#include "batt_cap_data_type.h"

using namespace std;

// battery capacity initialize paramers
// 参数解释如下:
// data_buffer_size : 数据缓存区大小,用于保存一段时间的蓄电池电压、电流、温度数据。
// volt_upper_limit: 电压上限，限定标定蓄电池容量时，电压的上限值。
// volt_lower_limit: 电压下限，限定标定蓄电池容量时，电压的下限值。
// cur_upper_limit: 电流上限，限定标定蓄电池容量时，电流的上限值。
// cur_lower_limit: 电流下限，限定标定蓄电池容量时，电流的下限值。
// volt_diff: 电压差值, 当压差小于设定值时, 可进行核容
// cur_diff: 电流差值, 当电流差值小于设定值时,可进行核容
class Batt_cap_init_params
{
public:
  Batt_cap_init_params(
      unsigned int _data_buffer_size,
      float _nomial_cap,
      float _volt_upper_limit,
      float _volt_lower_limit,
      float _cur_upper_limit,
      float _cur_lower_limit,
      float _volt_diff,
      float _cur_diff)
  {
    data_buffer_size = _data_buffer_size;
    nomial_cap = _nomial_cap;
    volt_upper_limit = _volt_upper_limit;
    volt_lower_limit = _volt_lower_limit;
    cur_upper_limit = _cur_upper_limit;
    cur_lower_limit = _cur_lower_limit;
    volt_diff = _volt_diff;
    cur_diff = _cur_diff;

  }

  unsigned int data_buffer_size;
  float nomial_cap;
  float volt_upper_limit;
  float volt_lower_limit;
  float cur_upper_limit;
  float cur_lower_limit;
  float volt_diff;
  float cur_diff;
};


class Batt_cap_init
{
public:
  Batt_cap_init(Batt_cap_init_params *_init_params, Data_convert_if *_data_convert, bool _cap_init_flag = true);
  ~Batt_cap_init();
  bool push_data(Batt_info batt_info);
  // bool buff_full(void);
  bool get_cap(Batt_info &cur_batt_info, float *init_cap);

  void set_init_flag_store_callback(init_flag_store func);  
  bool set_init_cap_flag(bool flag, bool store = false);
  bool get_init_cap_flag();
private:
  Batt_info get_para_diff(void);
  init_flag_store flag_store_callback;
  vector<Batt_info> init_cap_buf;
  Data_convert_if *data_convert;
  Batt_cap_init_params *init_params;
  bool cap_init_flag;
  // unsigned int buff_cnt_max;
};

#endif // _BATT_CAP_INIT_H_
