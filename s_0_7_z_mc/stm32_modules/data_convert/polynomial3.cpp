#include "polynomial3.h"
#include <math.h>

Polynomial3::Polynomial3(Py3_params *_params)
{
  params = _params;
  if ((-0.0000001f < _params->std) && (_params->std < 0.0000001f))
  {
    params->std = 1;
  }
}

Polynomial3::~Polynomial3()
{
}

float Polynomial3::convert(float value1, float value2, float value3)
{
  float nomalized = (value1 - params->mean) / params->std;
  return (params->p1 * pow(nomalized, 3) + params->p2 * pow(nomalized, 2) + params->p3 * nomalized + params->p4);
}
