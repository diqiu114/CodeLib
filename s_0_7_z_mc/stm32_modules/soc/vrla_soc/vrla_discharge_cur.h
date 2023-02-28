/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-08-04
 * 
 * @brief VRLA 阀控式铅酸蓄电池放电电流比例
 * 根据当前放电电流,估算出计算电流
 * 参照标准:YDT799-2010 通信用阀控式密封铅酸蓄电池 4章节
 * C10——10h 率额定容量(Ah)，数值为 1.00 C10；
 * C3——3h 率额定容量(Ah)，数值为 0.75 C10；
 * C1——1h 率额定容量(Ah)，数值为 0.55 C10；
 * Ct——当环境温度为 t 时的蓄电池实测容量(Ah)，是放电电流 I(A)与放电时间 T(h)的乘积；
 * Ce——在基准温度(25℃)条件时的蓄电池容量(Ah) ；
 * I10——10h 率放电电流(A), 数值为 1.00I10；
 * I3——3h 率放电电流(A), 数值为 2.50I10；
 * I1——1h 率放电电流(A), 数值为 5.50I10。
 * ***********************************************************
 */

#ifndef _VRLA_DISCHARGE_CUR_H_
#define _VRLA_DISCHARGE_CUR_H_

#include "..\..\data_convert\data_convert_if.h"
#include "..\..\data_convert\polynomial3.h"
#include <math.h>

#define VRLA_DISCHARGE_CUR_P1 (-1.3468f)
#define VRLA_DISCHARGE_CUR_P2 (2.6936f)
#define VRLA_DISCHARGE_CUR_P3 (0.7441f)
#define VRLA_DISCHARGE_CUR_P4 (-0.0000000000001f)

class Vrla_discharge_cur : public Data_convert_if
{
public:
  Vrla_discharge_cur(float nomial_soc)
  {
    soc = nomial_soc;
    cur_coeff_converter = new Polynomial3(new Py3_params(VRLA_DISCHARGE_CUR_P1, 
                                                         VRLA_DISCHARGE_CUR_P2, 
                                                         VRLA_DISCHARGE_CUR_P3, 
                                                         VRLA_DISCHARGE_CUR_P4));
  }

  virtual float convert(float value1, float value2 = 0, float value3 = 0)
  {
    float ret = 0;

    float cur_coeff = fabs(value1) / soc;
    ret = cur_coeff_converter->convert(cur_coeff) * soc;

    if (value1 > 0)
    {
      return ret;
    }
    else
    {
      return -ret;
    }
  }

private:
  float soc;
  Polynomial3* cur_coeff_converter;
};

#endif // _VRLA_DISCHARGE_CUR_H_
