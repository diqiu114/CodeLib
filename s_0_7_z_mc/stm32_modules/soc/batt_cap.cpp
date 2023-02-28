#include "batt_cap.h"

// milliseconds to hour
#define MSEC_TO_HOUR(x) ((float)((x) / (3600000.0f)))

/**
 * @brief Construct a new Batt_cap::Batt_cap object
 * 
 * @param _params battery capacity parameters
 * @param _discharge_proc discharge process funtion
 * @param _charge_proc charge process function
 * @param _adjust soc adjust funcion
 */
Batt_cap::Batt_cap(Batt_cap_params *_params,
                   Batt_discharge_proc_if *_discharge_proc,
                   Batt_charge_proc_if *_charge_proc,
                   Batt_cap_adj *_adjust)
{
  params = _params;
  
  discharge_proc = _discharge_proc;
  charge_proc = _charge_proc;
  adjust = _adjust;

  cur_cap = params->nomial_cap;

  cap_init = NULL;
  self_discharge = NULL;
  discharged_record = NULL;

  update_clk_in_hours = MSEC_TO_HOUR(params->update_clk_in_ms);
}

/**
 * @brief Destroy the Batt_cap::Batt_cap object
 * 
 */
Batt_cap::~Batt_cap()
{
  if (discharge_proc != NULL)
  {
    delete discharge_proc;
    discharge_proc = NULL;
  }

  if(charge_proc != NULL)
  {
    delete charge_proc;
    charge_proc = NULL;
  }

  if(adjust != NULL)
  {
    delete adjust;
    adjust = NULL;
  }
}

/**
 * @brief update capaciity
 * 
 * @param cap_para battery infomation
 * @return float cpacity rate(from 0% ~ 100%)
 */
float Batt_cap::update_cap(Batt_info &cap_para)
{
  if (cap_para.cur > 0)
  {
    cur_cap = charge_process(cap_para);
  }
  else
  {
    cur_cap = discharge_process(cap_para);
  }

  return get_cap_rate();
}

/**
 * @brief set current capacity
 * 
 * @param cap_rate capacity rate
 * @param store store to flash or not
 * @return true set ok
 * @return false set failed
 */
bool Batt_cap::set_cap(float cap_rate, bool store)
{
  bool ret = false;

  if (0 <= cap_rate && cap_rate <= 100)
  {
    cur_cap = cap_rate / 100 * params->nomial_cap;
    ret = true;
  }

  if (store && (cap_store_callback != NULL))
  {
    ret = cap_store_callback(cap_rate);
  }

  return ret;
}

/**
 * @brief return battery capacity
 * 
 * @return float battery capacity
 */
float Batt_cap::get_cap(void)
{
  return cur_cap;
}

/**
 * @brief get battery nomial capacity
 * 
 * @return float bettery nomial capacity
 */
float Batt_cap::get_nomial_cap(void)
{
  return params->nomial_cap;
}

/**
 * @brief get capacity rate
 * 
 * @return float capacity rate value
 */
float Batt_cap::get_cap_rate(void)
{
  return cur_cap * 100.0f / params->nomial_cap;
}

/**
 * @brief set capacity storage callback function
 * 
 * @param func callback function
 */
void Batt_cap::set_cap_store_callback(cap_store func)
{
  cap_store_callback = func;
}

/**
 * @brief self discharge calibare
 * 
 * @param ts_diff time stamp differences in seconds
 * @return float battery capacity after calibare
 */
float Batt_cap::self_discharge_calib(float ts_diff)
{
  // 正常核容后,才进行自放电计算
  if ((self_discharge != NULL) && (cap_init != NULL) && (cap_init->get_init_cap_flag() == false))
  {
    cur_cap = self_discharge->get_cap(params->nomial_cap, ts_diff);
  }

  return cur_cap;
}

/**
 * @brief battery dishcarge process
 * 
 * @param para battery info
 * @return float current capacity
 */
float Batt_cap::discharge_process(Batt_info &para)
{
  float ret = cur_cap;
  calc_data = para;

  if (calc_data.cur > params->discharge_cur_thr)
  {
    return ret;
  }

  if (calc_data.cur < params->cur_lower_limit)
  {
    calc_data.cur = params->cur_lower_limit;
  }

  if ((calc_data.temp < params->temp_lower_limit) || (params->temp_upper_limit < calc_data.temp))
  {
    calc_data.temp = params->temp_default;
  }

  if(discharged_record != NULL)
  {
    discharged_record->dec_dishcarged_cap(fabs(calc_data.cur) * update_clk_in_hours);
  }

  // inital battery capacity
  if (cap_init != NULL)
  {
    cap_init->push_data(para);
    if (cap_init->get_cap(para, &ret))
    {
      cap_init->set_init_cap_flag(false, true);
      set_cap(ret, true);

      // 将核容后的剩余补充容量写入已放电容量,并根据当前放电电流比例(容量比例)调整已放电容量
      if (discharged_record != NULL)
      {
        // 说明：下面被注释的这个公式是正确的，在核容后的容量需要经过电流计算比例和充电效率的换算后才是真实已放电容量。
        // 由于batt_cap无法获取到充电效率以及电流计算比例，所以在核容后，第一次充电估算会出现不准确的情况。
        // discharged_record->set_discharged_cap((ret - params->nomial_cap) * (fabs(calc_data.cur) / cur_format->convert(fabs(calc_data.cur)))/ get_charge_efficiency(), true);
        discharged_record->set_discharged_cap((ret - params->nomial_cap), true);
      }
    }
  }

  ret = discharge_proc->discharge_proc(calc_data, cur_cap, update_clk_in_hours);

  ret = ret * (1.0f / params->aging_factor);

  if (adjust != NULL)
  {
    ret = adjust->discharge_adj(ret, &calc_data);
  }

  ret = soc_limit(ret);

  return ret;
}

/**
 * @brief set update clock(period)
 * 
 * @param clk_in_ms update in milliseconds
 */
void Batt_cap::set_update_clk(unsigned int clk_in_ms)
{
  params->update_clk_in_ms = clk_in_ms;
  update_clk_in_hours = MSEC_TO_HOUR(params->update_clk_in_ms);
}

/**
 * @brief battery charge process
 * 
 * @param para battery infomation
 * @return float current capacity
 */
float Batt_cap::charge_process(Batt_info &para)
{
  float ret = cur_cap;
  calc_data = para;

  if (calc_data.cur < params->charge_cur_thr)
  {
    return ret;
  }

  if (calc_data.cur > params->cur_upper_limit)
  {
    calc_data.cur = params->cur_upper_limit;
  }

  if(discharged_record != NULL)
  {
    discharged_record->inc_dishcarged_cap(calc_data.cur * update_clk_in_hours);
  }

  ret = charge_proc->charge_proc(calc_data, cur_cap, update_clk_in_hours);

  // 老化系数
  ret = ret * (1.0f / params->aging_factor);

  if (adjust != NULL)
  {
    ret = adjust->charge_adj(ret, &calc_data);
  }

  ret = soc_limit(ret);

  return ret;
}

/**
 * @brief set self discharge object pointer
 * 
 * @param _self_discharge object pointer
 */
void Batt_cap::set_self_dishcarge(Self_discharge *_self_discharge)
{
  self_discharge = _self_discharge;
}

/**
 * @brief get self discharge object pointer
 * 
 * @return Self_discharge* object pointer
 */
Self_discharge *Batt_cap::get_self_discharge(void)
{
  return self_discharge;
}

/**
 * @brief set capacity init object pointer
 * 
 * @param _cap_init object pointer
 */
void Batt_cap::set_cap_init(Batt_cap_init *_cap_init)
{
  cap_init = _cap_init;
}

/**
 * @brief get capacity init object pointer
 * 
 * @return Self_discharge* object pointer
 */
Batt_cap_init *Batt_cap::get_cap_init(void)
{
  return cap_init;
}

/**
 * @brief set discharged capacity record object pointer
 * 
 * @param _discharged_record object pointer
 */
void Batt_cap::set_discharged_cap_record(Discharged_cap_record *_discharged_record)
{
  discharged_record = _discharged_record;
}

/**
 * @brief get discharged capacity record object pointer
 * 
 * @return Discharged_cap_record* object pointer
 */
Discharged_cap_record *Batt_cap::get_discharged_cap_record(void)
{
  return discharged_record;
}

/**
 * @brief battery capacity upper and lower limit 
 * 
 * @param batt_cap battery capacity
 * @return float current capacity
 */
float Batt_cap::soc_limit(float batt_cap)
{
  float ret = batt_cap;

  if (batt_cap <= 0)
  {
    ret = 0;
  }
  else if (batt_cap > params->nomial_cap)
  {
    ret = params->nomial_cap;

    // 当容量满时, 将放电容量记录修改为0
    if (discharged_record != NULL)
    {
      discharged_record->set_discharged_cap(BATT_DISCHARGED_CAP_MAX);
    }
  }

  return ret;
}
