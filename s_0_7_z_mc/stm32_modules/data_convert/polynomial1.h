/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      1阶线性转换

***********************************************************/

#ifndef _POLYNOMIAL1_H_
#define _POLYNOMIAL1_H_
#include "data_convert_if.h"

typedef struct _tag_polynomial_1_
{
  float k;
  float b;
}Polynomial_1;

class Py1_params
{
public:
  Py1_params(float _k, float _b)
  {
    k = _k;
    b = _b;
  };
  Py1_params(Polynomial_1 *_params)
  {
    k = _params->k;
    b = _params->b;
  }

  float k;
  float b;
};

class Polynomial1 : public Data_convert_if
{
public:
  Polynomial1(Py1_params *_params);
  virtual ~Polynomial1();
  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  Py1_params *params;
};

#endif //_POLYNOMIAL1_H_
