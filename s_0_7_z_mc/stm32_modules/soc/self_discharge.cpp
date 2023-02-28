#include "self_discharge.h"

/**
 * @brief Construct a new Self_discharge::Self_discharge object
 * 
 * @param _nomial_cap nomial capacity
 * @param _discharge_rate_per_month self discharge rate by month
 */
Self_discharge::Self_discharge(float _nomial_cap, float _discharge_rate_per_month)
{
  nomial_cap = _nomial_cap;
  dishcarge_rate = _discharge_rate_per_month;
}

/**
 * @brief Destroy the Self_discharge::Self_discharge object
 * 
 */
Self_discharge::~Self_discharge()
{
}

/**
 * @brief 根据时间差计算自放电容量
 * 
 * @param cur_cap current capacity
 * @param ts_diff 时间差（s) 
 * @return float 返回自放电修正后的容量
 */
float Self_discharge::get_cap(float cur_cap, float ts_diff)
{
  float ret = cur_cap;

  if(ts_diff > TS_DIFF_MIN)
  {
    ret = ret - (nomial_cap * dishcarge_rate * SECONDS_TO_MONTH(ts_diff));
  }

  return ret;
}
