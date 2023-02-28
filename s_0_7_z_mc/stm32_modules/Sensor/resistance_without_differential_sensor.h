#ifndef RESISTANCE_SENSOR_H_H
#define RESISTANCE_SENSOR_H_H

#include <vector>
#include "adc\adc_app.h"
#include "sensor\measure_interfaces.h"
#include "hw_interface\gpio\gpio_if.h"
#include "modules_def.h"

using namespace std;

class Res_adc_without_differental_channels
{
  public:
    Res_adc_without_differental_channels(int _volt_ch, int _res_ch_hig,int _res_ch_low)
    {
      volt_ch = _volt_ch;
      res_ch_hig = _res_ch_hig;
      res_ch_low = _res_ch_low;
    };
    int volt_ch;
    int res_ch_hig;
    int res_ch_low;
};

class Resistance_without_differential_sensor : public Res_sensor_if
{
public:
  Resistance_without_differential_sensor(Gpio_if* _discharge_io, 
                    Adc_app *_adc, 
                    vector<Res_adc_without_differental_channels>& _adc_chn, 
                    float discharge_res, 
                    unsigned int dishcarge_delay = 1,
                    unsigned char max_retry = 1);
  virtual ~Resistance_without_differential_sensor();
  virtual vector<float>* get_res();
  virtual unsigned int get_res_chn_cnt();
  virtual float get_drop_volt();   
  virtual float get_dis_curr();                   

private:
  Adc_app *adc;
  Gpio_if* discharge_io;
  vector<Res_adc_without_differental_channels> adc_chn;

  vector<float> ress;
  vector<float> batt_normal_volt;
  vector<float> batt_discharge_volt;
  vector<float> res_volt_hig;
  vector<float> res_volt_low;
  float discharge_res;
  unsigned int dishcarge_delay;
  float res_scale;
  float res_thr;
  unsigned char retry;
  float volt_drop;
  float current;
};

#endif
