#include "polynomial1.h"
#include <stdlib.h>

Polynomial1::Polynomial1(Py1_params *_params)
{
  params = _params;
  if ((-0.0000001f < params->k) && (params->k < 0.0000001f))
  {
    params->k = 1;
  }
}

Polynomial1::~Polynomial1()
{
  if(params != NULL)
  {
    delete params;
    params = NULL;
  }
}

float Polynomial1::convert(float value1, float value2, float value3)
{
  return value1 * params->k + params->b;
}
