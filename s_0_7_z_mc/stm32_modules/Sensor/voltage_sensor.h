#ifndef VOLTAGE_SENSOR_H_H
#define VOLTAGE_SENSOR_H_H

#include "measure_interfaces.h"
#include "adc\adc_app.h"

class Voltage_sensor : public Voltage_sensor_if
{
public:
  Voltage_sensor(Adc_app *_adc, int _adc_chn);
  virtual ~Voltage_sensor();
  virtual float get_volt(void);

private:
  Adc_app *adc;
  int adc_chn;
};

#endif
