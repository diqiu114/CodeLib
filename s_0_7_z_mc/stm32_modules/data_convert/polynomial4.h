/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      4阶多项式转换

***********************************************************/

#ifndef _POLYNOMIAL4_H_
#define _POLYNOMIAL4_H_

#include "data_convert_if.h"

typedef struct _tag_polynomial_4_
{
  float mean;
  float std;
  float p1;
  float p2;
  float p3;
  float p4;
  float p5;
}Polynomial_4;

class Py4_params
{
public:
  Py4_params(float _p1, float _p2, float _p3, float _p4, float _p5, float _mean = 0, float _std = 1)
  {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    p4 = _p4;
    p5 = _p5;
    mean = _mean;
    std = _std;
  };

  Py4_params(Polynomial_4 *_params)
  {
    p1 = _params->p1;
    p2 = _params->p2;
    p3 = _params->p3;
    p4 = _params->p4;
    p5 = _params->p5;
    mean = _params->mean;
    std = _params->std;
  }


  float p1;
  float p2;
  float p3;
  float p4;
  float p5;
  float mean;
  float std;
};

class Polynomial4 : public Data_convert_if
{
public:
  Polynomial4(Py4_params *_params);
  virtual ~Polynomial4();

  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py4_params *params;
};

#endif //_POLYNOMIAL4_H_
