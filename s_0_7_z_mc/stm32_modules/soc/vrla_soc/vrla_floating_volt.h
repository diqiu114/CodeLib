/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-08-04
 * 
 * @brief VRLA 阀控铅酸蓄电池截止电压
 * 根据当前放电电流换算出蓄电池截止电压
 * 参照标准:YDT799-2010 通信用阀控式密封铅酸蓄电池 6.13章节
 * 6.13.3 环境温度为 25℃时，蓄电池浮充充电电压为（2.20V～2.27V）/单体。
 * 6.13.4 蓄电池充电温度补偿系数宜为（-3mV～-7mV）/℃·单体。
 *  注：充电电压的具体数据由生产厂家提供。
 * ***********************************************************
 */

#ifndef _VRLA_FLOATING_VOLT_H_
#define _VRLA_FLOATING_VOLT_H_

#include "..\..\data_convert\data_convert_if.h"
#include <math.h>

#define VRLA_TEMP_MIN (-40.0f)
#define VRLA_TEMP_MAX (60.0f)
#define VRLA_TEMP_BASE (25.0f)

// voltage unit convert from mV to V
#define MV_TO_V(x) (x / 1000)

class Vrla_floating_volt : public Data_convert_if
{
public:
  Vrla_floating_volt(float _floating_volt_base,
                    float _temp_comp_mv, 
                    float _temp_base = VRLA_TEMP_BASE, 
                    float _temp_min = VRLA_TEMP_MIN, 
                    float _temp_max = VRLA_TEMP_MAX)
  {
    floating_volt_base = _floating_volt_base;
    temp_comp_volt = _temp_comp_mv;
    temp_base = _temp_base;
    temp_min = _temp_min;
    temp_max = temp_max;
  }

  virtual float convert(float value1, float value2 = 0, float value3 = 0)
  {
    if( value1 > temp_max)
    {
      value1 = temp_max;
    }
    else if(value1 < temp_min)
    {
      value1 = temp_min;
    }
    
    if(value1 > temp_base)
    {
      return floating_volt_base - (value1 - temp_base) * MV_TO_V(temp_comp_volt);
    }
    else
    {
      return floating_volt_base + (temp_base - value1) * MV_TO_V(temp_comp_volt);
    }
  }

private:
  float floating_volt_base;
  float temp_comp_volt;
  float temp_base;
  float temp_min;
  float temp_max;
};

#endif // _VRLA_FLOATING_VOLT_H_
