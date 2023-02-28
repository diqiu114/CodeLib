#include "polynomial2.h"
#include <math.h>

Polynomial2::Polynomial2(Py2_params *_params)
{
  params = _params;
  if ((-0.0000001f < _params->std) && (_params->std < 0.0000001f))
  {
    params->std = 1;
  }
}

Polynomial2::~Polynomial2()
{
}

float Polynomial2::convert(float value1, float value2, float value3)
{
  float nomalized = (value1 - params->mean) / params->std;
  return (params->p1 * pow(nomalized, 2) + params->p2 * nomalized + params->p3);
}
