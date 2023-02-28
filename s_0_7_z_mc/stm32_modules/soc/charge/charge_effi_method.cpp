#include "charge_effi_method.h"

// battery charge effective
#define BATT_CAP_50_PECENT_CHARGE_EFFI (0.95f)
#define BATT_CAP_75_PECENT_CHARGE_EFFI (0.90f)
#define BATT_CAP_85_PECENT_CHARGE_EFFI (0.85f)
#define BATT_CAP_90_PECENT_CHARGE_EFFI (0.83f)
#define BATT_CAP_95_PECENT_CHARGE_EFFI (0.80f)

/**
 * @brief Construct a new Charge_effi_method::Charge_effi_method object
 * 
 * @param _nomial_cap nomial capacity
 */
Charge_effi_method::Charge_effi_method(float _nomial_cap)
{
  nomial_cap = _nomial_cap;
}

/**
 * @brief Destroy the Charge_effi_method::Charge_effi_method object
 * 
 */
Charge_effi_method::~Charge_effi_method()
{
}

/**
 * @brief charge process
 * 
 * @param para battery infomation
 * @param cur_cap current capacity
 * @param update_clk_in_hours update period in hours
 * @return float capacity after charge process
 */
float Charge_effi_method::charge_proc(Batt_info &para, float cur_cap, float update_clk_in_hours)
{
  float ret = cur_cap;
  float calc_cur = para.cur;

  // 0%~50% 充电效率
  if (cur_cap <= nomial_cap * 0.5f)
  {
    calc_cur = calc_cur * BATT_CAP_50_PECENT_CHARGE_EFFI;
  } // 50%~75% 充电效率
  else if (cur_cap <= nomial_cap * 0.75f)
  {
    calc_cur = calc_cur * BATT_CAP_75_PECENT_CHARGE_EFFI;
  } // 75%~85% 充电效率
  else if (cur_cap <= nomial_cap * 0.85f)
  {
    calc_cur = calc_cur * BATT_CAP_85_PECENT_CHARGE_EFFI;
  } // 85%~95% 充电效率
  else if (cur_cap <= nomial_cap * 0.9f)
  {
    calc_cur = calc_cur * BATT_CAP_90_PECENT_CHARGE_EFFI;
  }
  else // 95%~100%充电效率
  {
    calc_cur = calc_cur * BATT_CAP_95_PECENT_CHARGE_EFFI;
  }

  ret = cur_cap + calc_cur * update_clk_in_hours;

  return ret;
}
