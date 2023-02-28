#ifndef RESISTANCE_SENSOR_H_H
#define RESISTANCE_SENSOR_H_H

#include <vector>
#include "adc\adc_app.h"
#include "sensor\measure_interfaces.h"
#include "sensor\resistance_sensor.h"
#include "hw_interface\gpio\gpio_if.h"
#include "modules_def.h"

using namespace std;

class Res_adc_channels
{
  public:
    Res_adc_channels(int _volt_ch, int _res_ch)
    {
      volt_ch = _volt_ch;
      res_ch = _res_ch;
    };
    int volt_ch;
    int res_ch;
};

class Resistance_sensor : public Res_sensor_if
{
public:
  Resistance_sensor(Gpio_if* _discharge_io, 
                    Adc_app *_adc, 
                    vector<Res_adc_channels>& _adc_chn, 
                    float discharge_res, 
                    unsigned int dishcarge_delay);
  virtual ~Resistance_sensor();
  virtual vector<float>* get_res();
  virtual unsigned int get_res_chn_cnt();

private:
  Adc_app *adc;
  Gpio_if* discharge_io;
  vector<Res_adc_channels> adc_chn;

  vector<float> ress;
  vector<float> batt_normal_volt;
  vector<float> batt_discharge_volt;
  vector<float> res_volt;
  float discharge_res;
  unsigned int dishcarge_delay;
  float res_scale;
  float res_thr;
};

#endif
