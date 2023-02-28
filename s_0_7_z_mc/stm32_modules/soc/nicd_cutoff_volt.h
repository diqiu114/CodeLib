#ifndef _NICD_CUTOFF_VOLT_H_
#define _NICD_CUTOFF_VOLT_H_

#include "..\..\data_convert\data_convert_if.h"
#include <math.h>


#define NICD_CUTOFF_VOLT (1)

class Nicd_cutoff_volt : public Data_convert_if
{
public:
  Nicd_cutoff_volt()
  {
  }

  virtual float convert(float value1, float value2 = 0, float value3 = 0)
  {
    return 1.0f;
  }
};

#endif // _NICD_CUTOFF_VOLT_H_
