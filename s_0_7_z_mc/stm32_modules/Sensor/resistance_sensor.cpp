#include "resistance_sensor.h"

Resistance_sensor::Resistance_sensor(Gpio_if *_discharge_io, 
                                      Adc_app *_adc, 
                                      vector<Res_adc_channels>& _adc_chn, 
                                      float _discharge_res, 
                                      unsigned int _dishcarge_delay)
{
  adc = _adc;
  adc_chn = _adc_chn;
  discharge_io = _discharge_io;
  ress.resize(adc_chn.size());
  batt_normal_volt.resize(adc_chn.size());
  batt_discharge_volt.resize(adc_chn.size());
  res_volt.resize(adc_chn.size());

  discharge_res = _discharge_res;
  dishcarge_delay = _dishcarge_delay;
  res_scale = 1000000;
  res_thr = 10;
}

Resistance_sensor::~Resistance_sensor()
{
  if (adc != NULL)
  {
    delete adc;
    adc = NULL;
  }
}

unsigned int Resistance_sensor::get_res_chn_cnt()
{
  return adc_chn.size();
}


vector<float> *Resistance_sensor::get_res()
{
  // battery normal voltage
  float *batt_data = adc->get_eng_data();
  int i = 0;
  
  for (vector<Res_adc_channels>::iterator it = adc_chn.begin(); it != adc_chn.end(); it++)
  {
    batt_normal_volt[i++] = batt_data[it->volt_ch];
  }

  // discharge
  discharge_io->set_hi();

  DELAY_MS(dishcarge_delay);

  batt_data = adc->get_eng_data();

  discharge_io->set_low();
  
  i = 0;
  // battery discharge voltage
  for (vector<Res_adc_channels>::iterator it = adc_chn.begin(); it != adc_chn.end(); it++)
  {
    batt_discharge_volt[i] = batt_data[it->volt_ch];
    res_volt[i] = batt_data[it->res_ch];
    i++;
  }

  // calculate battery resistance
  float volt_drop = 0;
  float current = 0;
  
  
  for (int i = 0; i < adc_chn.size(); i++)
  {
    volt_drop = batt_normal_volt[i] > batt_discharge_volt[i] ? (batt_normal_volt[i] - batt_discharge_volt[i]) : 0;
    current = res_volt[i] / discharge_res;

    // discharge resistance voltage lower than 10mA(adc acquire drift)，means discharge wire not connected
    if (((-0.0000001f < volt_drop) && (volt_drop < 0.0000001f)) || ((-0.0000001f < current) && (current < 0.0000001f)) || (res_volt[i] < res_thr))
    {
      ress[i] = 0;
    }
    else
    {
      ress[i] = (double)(volt_drop) * res_scale / current;
    }
  }

  return &ress;
}
