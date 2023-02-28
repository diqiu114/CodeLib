/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-08-04
 * 
 * @brief VRLA 阀控铅酸蓄电池温度补偿
 * 根据温度和电流估算出电池可放出的容量.
 * 参照标准:YDT799-2010 通信用阀控式密封铅酸蓄电池 7.7.4章节
 * Ce = Ct / (1+K(t-25)) 
 * 式中:Ce-25℃时的标称容量
 *      Ct-当前温度下容量
 *      t-放电时的环境温度
 *      K-温度系数:10h率时,K=0.006;3率时,K=0.008;1h率时,K=0.01
 * ***********************************************************
 */

#ifndef _VRLA_TEMP_COMP_H_
#define _VRLA_TEMP_COMP_H_

#include "..\..\data_convert\data_convert_if.h"
#include <math.h>

#define VRLA_TEMP_COMP_P1 (0.008571f)
#define VRLA_TEMP_COMP_P2 (0.005429f)

#define VRLA_STANDARD_TEMP (25)

class Vrla_temp_comp : public Data_convert_if
{
public:
  Vrla_temp_comp(float nomial_soc)
  {
    soc = nomial_soc;
  }

  // first value must be temperature, second value must be current
  virtual float convert(float value1, float value2 = 0, float value3 = 0)
  {
    float cur_coeff = fabs(value2) / soc;
    return (1 + (VRLA_TEMP_COMP_P1 * cur_coeff + VRLA_TEMP_COMP_P2) * (value1 - VRLA_STANDARD_TEMP));
  }

private:
  float soc;
};

#endif // _VRLA_TEMP_COMP_H_
