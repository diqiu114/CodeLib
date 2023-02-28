#include "eng_calib.h"
#include <string.h>

Eng_calib::Eng_calib(vector<Data_convert_if *> &_convert)
{
  calib_para = _convert;
}

float Eng_calib::calib(float input_val, unsigned int idx)
{
  return (calib_para.at(idx)->convert(input_val));
}

Data_convert_if* Eng_calib::get_calib(unsigned int idx)
{
  if(idx >= calib_para.size())
  {
    return NULL;
  }
  return calib_para[idx];
}

bool Eng_calib::set_calib(Data_convert_if *para, unsigned int idx)
{
  if(para == NULL || idx >= calib_para.size())
  {
    return false;
  }
  calib_para.at(idx) = para;
  return true;
}

Eng_calib::~Eng_calib()
{

}
