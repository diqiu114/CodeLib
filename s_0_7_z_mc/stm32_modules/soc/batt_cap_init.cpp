

#include "batt_cap_init.h"
#include <algorithm>

/**
 * @brief voltage compare
 * 
 */
struct Volt_cmp
{
  bool operator()(Batt_info i, Batt_info j) { return i.volt < j.volt; }
} volt_cmp;

/**
 * @brief current compare
 * 
 */
struct Cur_cmp
{
  bool operator()(Batt_info i, Batt_info j) { return i.cur < j.cur; }
} cur_cmp;

/**
 * @brief temperature compare
 * 
 */
struct Temp_cmp
{
  bool operator()(Batt_info i, Batt_info j) { return i.temp < j.temp; }
} temp_cmp;

/**
 * @brief Construct a new Batt_cap_init::Batt_cap_init object
 * 
 * @param _init_params battery soc initilize parameters
 * @param _data_convert 根据蓄电池当前信息（电压、电流、温度等）计算出当前剩余容量
 * @param _cap_init_flag 核容标记，一般情况下，当设备第一次安装在蓄电池上时，才进行核容，核容后，不再重新核容
 */
Batt_cap_init::Batt_cap_init(Batt_cap_init_params *_init_params, Data_convert_if *_data_convert, bool _cap_init_flag)
{
  init_params = _init_params;
  data_convert = _data_convert;
  flag_store_callback = NULL;
  cap_init_flag = _cap_init_flag;
  init_cap_buf.reserve(init_params->data_buffer_size);
}

Batt_cap_init::~Batt_cap_init()
{
  if (init_params != NULL)
  {
    delete init_params;
    init_params = NULL;
  }

  if (data_convert != NULL)
  {
    delete data_convert;
    data_convert = NULL;
  }
}

/**
 * @brief set init flag storage funcion
 * 
 * @param func callback funcion
 */
void Batt_cap_init::set_init_flag_store_callback(init_flag_store func)
{
  flag_store_callback = func;
}

/**
 * @brief set init flag
 * 
 * @param flag flag state
 * @param store store to flash or not
 * @return true set ok
 * @return false set failed
 */
bool Batt_cap_init::set_init_cap_flag(bool flag, bool store)
{
  bool ret = true;

  cap_init_flag = flag;

  if (store && (flag_store_callback != NULL))
  {
    ret = flag_store_callback(flag);
  }

  return ret;
}

/**
 * @brief return init flag state
 * 
 * @return true flag set
 * @return false flag reset
 */
bool Batt_cap_init::get_init_cap_flag()
{
  return cap_init_flag;
}

/**
 * @brief push battery data into vector
 * 
 * @param batt_info battery infomation
 * @return true push success
 * @return false push failed
 */
bool Batt_cap_init::push_data(Batt_info batt_info)
{
  if (cap_init_flag != true)
  {
    return false;
  }

  if ((batt_info.cur < init_params->cur_lower_limit) 
      || (batt_info.cur > init_params->cur_upper_limit))
  {
    return false;
  }

  if (init_cap_buf.size() < init_params->data_buffer_size)
  {
    init_cap_buf.push_back(batt_info);
  }
  else
  {
    init_cap_buf.erase(init_cap_buf.begin());
    init_cap_buf.push_back(batt_info);
  }

  return true;
}

/**
 * @brief 当一段时间的稳定数据放到vector中后，可以调用此函数返回核容容量
 * 
 * @param cur_batt_info current battery infomation
 * @param init_cap returned initalize capacity
 * @return true init ok
 * @return false init failed
 */
bool Batt_cap_init::get_cap(Batt_info &cur_batt_info, float *init_cap)
{
  if( cap_init_flag != true)
  {
    return false;
  }
  
  if ( (cur_batt_info.cur < init_params->cur_lower_limit) 
      || (cur_batt_info.cur > init_params->cur_upper_limit))
  {
    return false;
  }

  if (init_cap_buf.size() < init_params->data_buffer_size)
  {
    return false;
  }

  Batt_info batt_diff = get_para_diff();

  if ((batt_diff.volt <= init_params->volt_diff) && (batt_diff.cur <= init_params->cur_diff))
  {
    if( cur_batt_info.volt >= init_params->volt_upper_limit )
    {
      *init_cap = init_params->nomial_cap;
    }
    else if( cur_batt_info.volt <= init_params->volt_lower_limit)
    {
      *init_cap = 0;
    }
    else
    {
      *init_cap = data_convert->convert(cur_batt_info.cur, cur_batt_info.volt);
    }
    return true;
  }
  else
  {
    return false;
  }

}

/**
 * @brief get vector data differece
 * 
 * @return Batt_info diff infomation
 */
Batt_info Batt_cap_init::get_para_diff(void)
{
  Batt_info ret;
  Batt_info max_buff;
  Batt_info min_buff;

  max_buff = *max_element(init_cap_buf.begin(), init_cap_buf.end(), volt_cmp);
  min_buff = *min_element(init_cap_buf.begin(), init_cap_buf.end(), volt_cmp);
  ret.volt = fabsf(max_buff.volt - min_buff.volt);

  max_buff = *max_element(init_cap_buf.begin(), init_cap_buf.end(), cur_cmp);
  min_buff = *min_element(init_cap_buf.begin(), init_cap_buf.end(), cur_cmp);
  ret.cur = fabsf(max_buff.cur - min_buff.cur);

  max_buff = *max_element(init_cap_buf.begin(), init_cap_buf.end(), temp_cmp);
  min_buff = *min_element(init_cap_buf.begin(), init_cap_buf.end(), temp_cmp);
  ret.temp = fabsf(max_buff.temp - min_buff.temp);

  return ret;
}
