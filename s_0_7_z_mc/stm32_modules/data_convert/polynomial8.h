/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      8阶多项式转换

***********************************************************/

#ifndef _POLYNOMIAL8_H_
#define _POLYNOMIAL8_H_

#include "data_convert_if.h"

typedef struct _tag_polynomial_8_
{
  float mean;
  float std;
  float p1;
  float p2;
  float p3;
  float p4;
  float p5;
  float p6;
  float p7;
  float p8;
  float p9;
}Polynomial_8;

class Py8_params
{
public:
  Py8_params(float _p1, float _p2, float _p3, float _p4, float _p5, float _p6, 
            float _p7, float _p8, float _p9, float _mean = 0, float _std = 1)
  {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    p4 = _p4;
    p5 = _p5;
    p6 = _p6;
    p7 = _p7;
    p8 = _p8;
    p9 = _p9;
    mean = _mean;
    std = _std;
  };

  Py8_params(Polynomial_8 *_params)
  {
    p1 = _params->p1;
    p2 = _params->p2;
    p2 = _params->p2;
    p3 = _params->p3;
    p4 = _params->p4;
    p5 = _params->p5;
    p6 = _params->p6;
    p7 = _params->p7;
    p8 = _params->p8;
    p9 = _params->p9;
    mean = _params->mean;
    std = _params->std;
  }

  float p1;
  float p2;
  float p3;
  float p4;
  float p5;
  float p6;
  float p7;
  float p8;
  float p9;
  float mean;
  float std;
};

class Polynomial8 : public Data_convert_if
{
public:
  Polynomial8(Py8_params *_params);
  virtual ~Polynomial8();

  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py8_params *params;
};

#endif //_POLYNOMIAL8_H_
