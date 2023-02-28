#include "polynomial6.h"
#include <math.h>

Polynomial6::Polynomial6(Py6_params *_params)
{
  params = _params;

  if ((-0.0000001f < _params->std) && (_params->std < 0.0000001f))
  {
    params->std = 1;
  }
}

Polynomial6::~Polynomial6()
{
}

float Polynomial6::convert(float value1, float value2, float value3)
{
  float nomalized = (value1 - params->mean) / params->std;

  return (params->p1 * pow(nomalized, 6) + params->p2 * pow(nomalized, 5) + params->p3 * pow(nomalized, 4) 
          + params->p4 * pow(nomalized, 3) + params->p5 * pow(nomalized, 2) + params->p6 * nomalized + params->p7);
}
