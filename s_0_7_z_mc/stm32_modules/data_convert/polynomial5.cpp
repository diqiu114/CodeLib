#include "polynomial5.h"
#include <math.h>

Polynomial5::Polynomial5(Py5_params *_params)
{
  params = _params;

  if ((-0.0000001f < _params->std) && (_params->std < 0.0000001f))
  {
    params->std = 1;
  }
}

Polynomial5::~Polynomial5()
{
}

float Polynomial5::convert(float value1, float value2, float value3)
{
  float nomalized = (value1 - params->mean) / params->std;

  return (params->p1 * pow(nomalized, 5) + params->p2 * pow(nomalized, 4) + params->p3 * pow(nomalized, 3) 
          + params->p4 * pow(nomalized, 2) + params->p5 * nomalized + params->p6);
}
