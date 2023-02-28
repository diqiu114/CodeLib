/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-08-04
 * 
 * @brief VRLA 阀控铅酸蓄电池截止电压
 * 根据当前放电电流换算出蓄电池截止电压
 * 参照标准:YDT799-2010 通信用阀控式密封铅酸蓄电池 6.6章节
 * 放电率 蓄电池终止电压(单体)
 *  10h       1.8V
 *  3h        1.8V
 *  1h        1.75V
 * ***********************************************************
 */

#ifndef _VRLA_CUTOFF_VOLT_H_
#define _VRLA_CUTOFF_VOLT_H_

#include "..\..\data_convert\data_convert_if.h"
#include <math.h>

#define VRLA_DISCHARGE_RATE_10H (0.1f)
#define VRLA_DISCHARGE_RATE_3H (0.25f)
#define VRLA_DISCHARGE_RATE_1H (0.55f)

#define VRLA_CUTOFF_VOLT1 (1.8f)
#define VRLA_CUTOFF_VOLT2 (1.75f)

class Vrla_cutoff_volt : public Data_convert_if
{
public:
  Vrla_cutoff_volt(float nomial_soc)
  {
    
    soc = nomial_soc;
  }

  virtual float convert(float value1, float value2 = 0, float value3 = 0)
  {
    float cur_coeff = fabs(value1) / soc;

    if(cur_coeff < VRLA_DISCHARGE_RATE_1H)
    {
      return VRLA_CUTOFF_VOLT1;
    }
    else
    {
      return VRLA_CUTOFF_VOLT2;
    }
  }

private:
  float soc;
};

#endif // _VRLA_CUTOFF_VOLT_H_
