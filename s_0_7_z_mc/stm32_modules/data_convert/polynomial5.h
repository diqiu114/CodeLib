/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      5阶线性转换

***********************************************************/

#ifndef _POLYNOMIAL5_H_
#define _POLYNOMIAL5_H_

#include "data_convert_if.h"

typedef struct _tag_polynomial_5_
{
  float mean;
  float std;
  float p1;
  float p2;
  float p3;
  float p4;
  float p5;
  float p6;
}Polynomial_5;

class Py5_params
{
public:
  Py5_params(float _p1, float _p2, float _p3, float _p4, float _p5, float _p6, float _mean = 0, float _std = 1)
  {
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    p4 = _p4;
    p5 = _p5;
    p6 = _p6;

    mean = _mean;
    std = _std;
  };

  Py5_params(Polynomial_5 *_params)
  {
    p1 = _params->p1;
    p2 = _params->p2;
    p3 = _params->p3;
    p4 = _params->p4;
    p5 = _params->p5;
    p6 = _params->p6;
    mean = _params->mean;
    std = _params->std;
  }


  float p1;
  float p2;
  float p3;
  float p4;
  float p5;
  float p6;
  float mean;
  float std;
};

class Polynomial5 : public Data_convert_if
{
public:
  Polynomial5(Py5_params *_params);
  virtual ~Polynomial5();

  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py5_params *params;
};

#endif //_POLYNOMIAL5_H_
