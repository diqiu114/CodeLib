#include "discharged_cap_record.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief Construct a new Discharged_cap_record::Discharged_cap_record object
 * 
 * @param _discharge_cap_min dishcarge capacity minimum
 */
Discharged_cap_record::Discharged_cap_record(float _discharge_cap_min)
{
  discharged_cap_min = _discharge_cap_min;
  discharged_cap = BATT_DISCHARGED_CAP_MAX;
  discharged_cap_store_callback = NULL;

  charge_efficiency = BATT_CAP_CONVERT_RATE_MAX;
}

/**
 * @brief Destroy the Discharged_cap_record::Discharged_cap_record object
 * 
 */
Discharged_cap_record::~Discharged_cap_record()
{
}

/**
 * @brief decrease dishchared capacity, call in discharge process
 * 
 * @param charge_cap current discharge capacity
 * @return true modify ok
 * @return false modify failed
 */
bool Discharged_cap_record::dec_dishcarged_cap(float charge_cap)
{
  discharged_cap -= fabs(charge_cap) / charge_efficiency;
  if (discharged_cap < discharged_cap_min)
  {
    discharged_cap = discharged_cap_min;
  }

  return true;
}

/**
 * @brief increase discharged capacity, call in charge process
 * 
 * @param charge_cap current charge capacity
 * @return true ok
 * @return false failed
 */
bool Discharged_cap_record::inc_dishcarged_cap(float charge_cap)
{
  discharged_cap += fabs(charge_cap);
  if (discharged_cap > BATT_DISCHARGED_CAP_MAX)
  {
    discharged_cap = BATT_DISCHARGED_CAP_MAX;
  }

  return true;
}

/**
 * @brief set discharged capacity
 * 
 * @param cap capacity to be modify
 * @param store store to flash or not
 * @return true set ok
 * @return false set failed
 */
bool Discharged_cap_record::set_discharged_cap(float cap, bool store)
{
  bool ret = false;

  if ((discharged_cap_min <= cap) && (cap <= BATT_DISCHARGED_CAP_MAX))
  {
    discharged_cap = cap;

    if (store && discharged_cap_store_callback != NULL)
    {
      ret = discharged_cap_store_callback(discharged_cap);
    }
  }

  return ret;
}

/**
 * @brief get dishcarged cap min value
 * 
 * @return float discharged capacity min value
 */
float Discharged_cap_record::get_dishcarged_cap_min(void)
{
  return discharged_cap_min;
}

/**
 * @brief get discharged capacity
 * 
 * @return float value of discharged capacity
 */
float Discharged_cap_record::get_discharged_cap(void)
{
  return discharged_cap;
}

/**
 * @brief set store discharged capacity function pointer
 * 
 * @param func function pointer
 */
void Discharged_cap_record::set_discharged_cap_store_callback(cap_store func)
{
  discharged_cap_store_callback = func;
}

/**
 * @brief store discharged capacity
 * 
 * @return true store ok
 * @return false store failed
 */
bool Discharged_cap_record::store_discharged_cap(void)
{
  bool ret = false;
  if (discharged_cap_store_callback != NULL)
  {
    ret = discharged_cap_store_callback(discharged_cap);
  }

  return ret;
}

/**
 * @brief get charge efficiency
 * 
 * @return float charge efficiency value
 */
float Discharged_cap_record::get_charge_efficiency(void)
{
  return charge_efficiency;
}


/**
 * @brief set charge efficiency
 * 
 * @param charge_effi charge efficiency
 * @return true set ok
 * @return false set failed
 */
bool Discharged_cap_record::set_charge_efficiency(float charge_effi)
{
  if((BATT_CAP_CONVERT_RATE_MIN <= charge_effi) && (charge_effi <= BATT_CAP_CONVERT_RATE_MAX))
  {
    charge_efficiency = charge_effi;
    return true;
  }
  return false;
}
