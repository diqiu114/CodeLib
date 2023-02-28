#include "batt_cme.h"
#include <stdlib.h>
#include <math.h>

Batt_cme::Batt_cme(float _nomial_cap, Data_convert_if *cnv)
{
  nomial_cap = fabs(_nomial_cap);
  data_convert = cnv;
  addup_discharged_cap = BATT_CME_DISCHARGED_CAP_MIN;
  addup_discharged_cap_for_calc = addup_discharged_cap;
  std_cur_rate = 1;
  store_func = NULL;
}

Batt_cme::~Batt_cme(){};

/**
   * @brief Set the addup discharged cap object 
   *        设置累计已放置容量
   * @param cap 放电容量值
   */
bool Batt_cme::set_addup_discharged_cap(float cap, bool store)
{
  bool ret = true;

  addup_discharged_cap = fabs(cap);
  update_addup_discharged_cap();

  if (store && store_func != NULL)
  {
    ret = store_func(addup_discharged_cap);
  }

  return ret;
}

/**
 * @brief 增加累计放电容量
 * 
 * @param cap 当前需累计的容量
 * @param store 是否存储
 * @return true 成功
 * @return false 失败
 */
bool Batt_cme::dec_addup_discharged_cap(float cap, bool store)
{
  bool ret = true;

  addup_discharged_cap += fabs(cap);

  if (store && store_func != NULL)
  {
    ret = store_func(addup_discharged_cap);
  }

  return ret;
}

bool Batt_cme::update_addup_discharged_cap(void)
{
  if (fabs(addup_discharged_cap) > BATT_CME_DISCHARGED_CAP_MAX)
  {
    addup_discharged_cap_for_calc = BATT_CME_DISCHARGED_CAP_MAX;
  }
  else
  {
    addup_discharged_cap_for_calc = addup_discharged_cap;
  }
  
  return true;
}

/**
   * @brief Get the addup discharged cap object
   *        获取累计已放电容量值
   * @return float 累计已放电容量值
   */
float Batt_cme::get_addup_discharged_cap(void)
{
  return addup_discharged_cap;
}

/**
   * @brief Set the std cur rate object
   *        设置标准电流比例, 通常为0.2C电流比例
   *        如saft 100AH电池, 在0.2C(20A)电流放电情况,实际计算放电电流为17.7705
   *        则参数为 17.7705 / 20 = 0.888526
   * @param rate 比例值
   */
void Batt_cme::set_std_cur_rate(float rate)
{
  std_cur_rate = rate;
}

/**
   * @brief 获取充电记忆效应比例
   * 
   * @param cur_rate 当前电流比例
   *  如saft 100AH电池, 在100A放电情况下,实际计算放电电流为106.3716
   *  则参数为 106.3716 / 100 = 1.063716
   * @return float 返回计算比例值
   */
float Batt_cme::get_cme(float cur_rate)
{
  return (nomial_cap / data_convert->convert(fabs(addup_discharged_cap_for_calc))) * (cur_rate / std_cur_rate);
}

/**
   * @brief Set the addup cap store callback object
   *        设置存储累计容量回调函数
   * @param func 
   */
void Batt_cme::set_addup_cap_store_callback(cap_store func)
{
  store_func = func;
}

/**
   * @brief 累计容量
   * 
   * @return true 存储成功
   * @return false 存储失败
   */
bool Batt_cme::store_addup_cap(void)
{
  bool ret = false;
  if (store_func != NULL)
  {
    ret = store_func(addup_discharged_cap);
  }

  return ret;
}
