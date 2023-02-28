/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      3阶多项式转换

***********************************************************/

#ifndef _POLYNOMIAL3_H_
#define _POLYNOMIAL3_H_

#include "data_convert_if.h"

typedef struct _tag_polynomial_3_
{
  float mean;
  float std;
  float p1;
  float p2;
  float p3;
  float p4;
}Polynomial_3;

class Py3_params
{
public:
  Py3_params(float _p1, float _p2, float _p3, float _p4, float _mean = 0, float _std = 1)
  {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    p4 = _p4;
    mean = _mean;
    std = _std;
  };

  Py3_params(Polynomial_3 *_params)
  {
    p1 = _params->p1;
    p2 = _params->p2;
    p3 = _params->p3;
    p4 = _params->p4;
    mean = _params->mean;
    std = _params->std;
  }

  float p1;
  float p2;
  float p3;
  float p4;
  float mean;
  float std;
};

class Polynomial3 : public Data_convert_if
{
public:
  Polynomial3(Py3_params *_params);
  virtual ~Polynomial3();
  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py3_params *params;
};

#endif //_POLYNOMIAL3_H_
