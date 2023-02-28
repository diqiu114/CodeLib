/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      2阶多项式转换

***********************************************************/

#ifndef _POLYNOMIAL2_H_
#define _POLYNOMIAL2_H_

#include "data_convert_if.h"

typedef struct _tag_polynomial_2_
{
  float mean;
  float std;
  float p1;
  float p2;
  float p3;
}Polynomial_2;

class Py2_params
{
public:
  Py2_params(float _p1, float _p2, float _p3, float _mean = 0, float _std = 1)
  {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    mean = _mean;
    std = _std;
  };

  Py2_params(Polynomial_2 *_params)
  {
    p1 = _params->p1;
    p2 = _params->p2;
    p3 = _params->p3;
    mean = _params->mean;
    std = _params->std;
  }

  float p1;
  float p2;
  float p3;
  float mean;
  float std;
};

class Polynomial2 : public Data_convert_if
{
public:
  Polynomial2(Py2_params *_params);
  virtual ~Polynomial2();
  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py2_params *params;
};

#endif //_POLYNOMIAL2_H_
