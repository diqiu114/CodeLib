#include "voltage_sensor.h"

Voltage_sensor::Voltage_sensor(Adc_app *_adc, int _adc_chn)
{
  adc = _adc;
  adc_chn = _adc_chn;
}

Voltage_sensor::~Voltage_sensor()
{
  if(adc)
  {
    delete adc;
    adc = NULL;
  }
}

float Voltage_sensor::get_volt(void)
{
  return adc->get_eng_data(adc_chn);
}
