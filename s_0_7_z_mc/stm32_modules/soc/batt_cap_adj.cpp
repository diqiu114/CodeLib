#include "batt_cap_adj.h"

/**
 * @brief Construct a new Batt_cap_adj::Batt_cap_adj object
 * 
 * @param _batt_cap_min battery capacity minimum
 * @param _batt_cap_max battery capacity maximum
 */
Batt_cap_adj::Batt_cap_adj(float _batt_cap_min, float _batt_cap_max)
{
  batt_cap_min = _batt_cap_min;
  batt_cap_max = _batt_cap_max;
}

Batt_cap_adj::~Batt_cap_adj()
{
}

/**
 * @brief add discharge conditions
 * 
 * @param params adjust paramters
 * @return true set ok
 * @return false set failed
 */
bool Batt_cap_adj::add_discharge_condition(Batt_cap_adj_params &params)
{
  discharge_conditions.push_back(params);
  return true;
}

/**
 * @brief modify discharge confition
 * 
 * @param params modify paramters
 * @param idx modify paramter index
 * @return true modify ok
 * @return false modify failed
 */
bool Batt_cap_adj::modify_discharge_condition(Batt_cap_adj_params &params, int idx)
{
  if ((discharge_conditions.size() > 0) && (idx > discharge_conditions.size() - 1))
  {
    return false;
  }

  discharge_conditions[idx] = params;

  return true;
}

/**
 * @brief delete discharge conditon
 * 
 * @param idx delete index
 * @return true delete ok
 * @return false delete failed
 */
bool Batt_cap_adj::del_discharge_condition(int idx)
{
  if ((discharge_conditions.size() > 0) && (idx > discharge_conditions.size() - 1))
  {
    return false;
  }

  discharge_conditions.erase(discharge_conditions.begin() + idx);

  return true;
}

/**
 * @brief add charge conditions
 * 
 * @param params adjust paramters
 * @return true set ok
 * @return false set failed
 */
bool Batt_cap_adj::add_charge_condition(Batt_cap_adj_params &params)
{
  charge_conditions.push_back(params);
  return true;
}

/**
 * @brief modify charge confition
 * 
 * @param params modify paramters
 * @param idx modify paramter index
 * @return true modify ok
 * @return false modify failed
 */
bool Batt_cap_adj::modify_charge_condition(Batt_cap_adj_params &params, int idx)
{
  if (idx > charge_conditions.size() - 1)
  {
    return false;
  }

  charge_conditions[idx] = params;

  return true;
}

/**
 * @brief delete charge conditon
 * 
 * @param idx delete index
 * @return true delete ok
 * @return false delete failed
 */
bool Batt_cap_adj::del_charge_condition(int idx)
{
  if ((charge_conditions.size() > 0) && (idx > charge_conditions.size() - 1))
  {
    return false;
  }

  charge_conditions.erase(charge_conditions.begin() + idx);

  return true;
}

/**
 * @brief charge adjust, call at battery charge state
 * 
 * @param cur_batt_cap current battery capacity
 * @param cur_batt_info current battery infomation
 * @return float adjusted battery capacity
 */
float Batt_cap_adj::charge_adj(float cur_batt_cap, Batt_info *cur_batt_info)
{
  float ret = cur_batt_cap;

  if (cur_batt_cap >= batt_cap_max)
  {
    return ret;
  }

  for (int i = 0; i < charge_conditions.size(); i++)
  {
    // 根据温度修正拐点电压值, 温度值需在限定的温度范围内
    if ((charge_conditions[i].temp_min <= cur_batt_info->temp) && (cur_batt_info->temp <= charge_conditions[i].temp_max))
    {
      if (charge_conditions[i].volt_convert != NULL)
      {
        charge_conditions[i].batt_threshold->volt = charge_conditions[i].volt_convert->convert(cur_batt_info->temp);
      }
    }

    if ((cur_batt_info->volt >= charge_conditions[i].batt_threshold->volt) 
          && (cur_batt_info->cur <= charge_conditions[i].batt_threshold->cur) 
          && (cur_batt_cap < charge_conditions[i].terminal_cap))
    {
      ret += batt_cap_max * charge_conditions[i].rate;
      break;
    }
  }

  return ret;
}

/**
 * @brief discharge adjust, call at battery discharge state
 * 
 * @param cur_batt_cap current battery capacity
 * @param cur_batt_info current battery infomation
 * @return float adjusted battery capacity
 */
float Batt_cap_adj::discharge_adj(float cur_batt_cap, Batt_info *cur_batt_info)
{
  float ret = cur_batt_cap;

  if (cur_batt_cap <= batt_cap_min)
  {
    return ret;
  }

  for (int i = 0; i < discharge_conditions.size(); i++)
  {
    // // 根据温度修正拐点电压值
    // if( discharge_conditions[i].volt_convert != NULL)
    // {
    //   discharge_conditions[i].batt_threshold->volt = discharge_conditions[i].volt_convert->convert(cur_batt_info->temp);
    // }

    // 根据电流修正截止电压值
    if (discharge_conditions[i].cutoff_volt_convert != NULL)
    {
      discharge_conditions[i].batt_threshold->volt = discharge_conditions[i].cutoff_volt_convert->convert(cur_batt_info->cur);
    }

    if ((cur_batt_info->volt <= discharge_conditions[i].batt_threshold->volt) 
		&& (cur_batt_info->cur <= discharge_conditions[i].batt_threshold->cur) 
		&& (cur_batt_cap > discharge_conditions[i].terminal_cap))
    {
      ret -= batt_cap_max * discharge_conditions[i].rate;
      break;
    }
  }

  return ret;
}
