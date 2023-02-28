#include "ah_method_discharge.h"
#include "math.h"

// milliseconds to hour
#define MSEC_TO_HOUR(x) ((float)((x) / (3600000.0f)))

#define BATT_STD_CUR(x) (0.2f * (x))
/**
 * @brief Construct a new Ah_method_discharge::Ah_method_discharge object
 * 
 * @param _nomial_cap 标称容量
 * @param _cur_format 计算电流与实际电流的转换类
 * @param _temp_compensation 温度补偿类
 * @param _cme 充电记忆效应类
 */
Ah_method_discharge::Ah_method_discharge(
                    float _nomial_cap,
                    Data_convert_if* _cur_format,
                    Data_convert_if* _temp_compensation,
                    Batt_cme* _cme)
{
  nomial_cap = _nomial_cap;
  cur_format = _cur_format;
  temp_compensation = _temp_compensation;
  cme = _cme;
}

Ah_method_discharge::~Ah_method_discharge()
{
  if (cur_format != NULL)
  {
    delete cur_format;
    cur_format = NULL;
  }

  if(temp_compensation != NULL)
  {
    delete temp_compensation;
    temp_compensation = NULL;
  }

  if(cme != NULL)
  {
    delete cme;
    cme = NULL;
  }
}

/**
 * @brief 放电处理
 * 
 * @param para 蓄电池信息
 * @param cur_cap 当前容量
 * @param update_clk_in_hours 更新周期（单位：小时）
 * @return float 返回放电处理后的容量
 */
float Ah_method_discharge::discharge_proc(Batt_info &para, float cur_cap, float update_clk_in_hours)
{
  float ret = cur_cap;

  float calc_cur = para.cur;

  if (cur_format != NULL)
  {
    calc_cur = cur_format->convert(fabs(calc_cur));
  }

  if (cme != NULL)
  {
    // 累计实际放电容量
    cme->dec_addup_discharged_cap(fabs(para.cur) * update_clk_in_hours);
    // 计算累计放电容量与实际可放出容量之间的比例
    calc_cur = fabs(para.cur) * cme->get_cme(calc_cur / fabs(para.cur));
  }

  float temp_compen_rate = 1;
  if (temp_compensation != NULL)
  {
    float temp_coeff = temp_compensation->convert(para.temp, para.cur);
    if (-0.0000001f < temp_coeff && temp_coeff < 0.0000001f)
    {
    }
    else
    {
      temp_compen_rate = 1 / temp_coeff;
    }
  }

  ret = ret - calc_cur * update_clk_in_hours * temp_compen_rate;

  return ret;
}

/**
 * @brief 设置放电记忆效应对象指针
 * 
 * @param _cme 对象指针
 */
void Ah_method_discharge::set_charge_memory_effect(Batt_cme *_cme)
{
  cme = _cme;
  if (cur_format != NULL)
  {
    float std_cur_rate = cur_format->convert(fabs(BATT_STD_CUR(nomial_cap))) / BATT_STD_CUR(nomial_cap);
    cme->set_std_cur_rate(std_cur_rate);
  }
}
