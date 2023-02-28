/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      6阶多项式转换

***********************************************************/

#ifndef _POLYNOMIAL6_H_
#define _POLYNOMIAL6_H_

#include "data_convert_if.h"

typedef struct _tag_polynomial_6_
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
}Polynomial_6;

class Py6_params
{
public:
  Py6_params(float _p1, float _p2, float _p3, float _p4, float _p5, float _p6, float _p7, float _mean = 0, float _std = 1)
  {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    p4 = _p4;
    p5 = _p5;
    p6 = _p6;
    p7 = _p7;
    mean = _mean;
    std = _std;
  };

  Py6_params(Polynomial_6 *_params)
  {
    p1 = _params->p1;
    p2 = _params->p2;
    p2 = _params->p2;
    p3 = _params->p3;
    p4 = _params->p4;
    p5 = _params->p5;
    p6 = _params->p6;
    p7 = _params->p7;
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
  float mean;
  float std;
};

class Polynomial6 : public Data_convert_if
{
public:
  Polynomial6(Py6_params *_params);
  virtual ~Polynomial6();

  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py6_params *params;
};

#endif //_POLYNOMIAL6_H_
