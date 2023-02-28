#include "recharge_method.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief Construct a new Recharge_method::Recharge_method object
 * 
 * @param _nomial_batt_cap nomial capacity
 */
Recharge_method::Recharge_method(float _nomial_batt_cap)
{
  nomial_batt_cap = _nomial_batt_cap;

  discharged_cap = BATT_DISCHARGED_CAP_MAX;

  discharged_cap_store_callback = NULL;
}

/**
 * @brief Destroy the Recharge_method::Recharge_method object
 * 
 */
Recharge_method::~Recharge_method()
{
}

/**
 * @brief 充电计算处理, 将实时充入容量转为计算容量
 * 
 * @param cur charge current
 * @param cur_cap current battery capacity
 * @param update_clk soc calculate period
 * @return float calculate battery capacity
 */
float Recharge_method::charge_proc(Batt_info &batt_data, float cur_cap, float update_clk_in_hours)
{
  float ret = 0;
  float charge_cap = fabs(batt_data.cur) * update_clk_in_hours;

  if (discharged_cap < 0)
  {
    ret = charge_cap * (cur_cap - nomial_batt_cap) / (discharged_cap);
  }
  else
  {
    ret = charge_cap;
  }

  return ret + cur_cap;
}

/**
 * @brief set dischared battery capacity
 * 
 * @param cap discharged capacity, max = 0
 * @return true set ok
 * @return false set failed
 */
bool Recharge_method::set_discharged_cap(float cap)
{
  if (cap <= BATT_DISCHARGED_CAP_MAX)
  {
    discharged_cap = cap;
    return true;
  }
  return false;
}

