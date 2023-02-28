#include "res_constant_curr_sour_sensor.h"

#define VOLT_TO_RISE_MIN_TIME  (5)
#define  SAMP_CNT               (3)

Res_constant_curr_sour_sensor::Res_constant_curr_sour_sensor(Gpio_if* _discharge_io, 
                                    Adc_app *_adc, 
                                    vector<Res_ccs_adc_channels>& _adc_chn, 
                                    float curr_ma,
                                    unsigned int _dishcarge_delay,
                                    unsigned int _res_scale)
{
  adc = _adc;
  adc_chn = _adc_chn;
  discharge_io = _discharge_io;
  ress.resize(adc_chn.size());
  batt_normal_volt.resize(adc_chn.size());
  batt_discharge_volt.resize(adc_chn.size());
  dishcarge_delay = _dishcarge_delay;
  current = curr_ma;
  res_scale = _res_scale;
  last_drop  = 0;
  is_first = true;
}

Res_constant_curr_sour_sensor::~Res_constant_curr_sour_sensor()
{
  if (adc != NULL)
  {
    delete adc;
    adc = NULL;
  }

  if (discharge_io != NULL)
  {
    delete discharge_io;
    discharge_io = NULL;
  }
}

unsigned int Res_constant_curr_sour_sensor::get_res_chn_cnt()
{
  return adc_chn.size();
}


vector<float> *Res_constant_curr_sour_sensor::get_res()
{
  float tmp_dis_v = 0;
  float tmp_nomal_v = 0;
  int index = 0;
  float *batt_data = NULL;
  float volt_drop = 0;
  // discharge
  discharge_io->set_hi();
  DELAY_MS(dishcarge_delay);
  index = 0;
    // battery discharge voltage
  for (vector<Res_ccs_adc_channels>::iterator it = adc_chn.begin(); it != adc_chn.end(); it++)
  { 
    for(int i =0 ; i < SAMP_CNT ;i++)
    {
      batt_data = adc->get_eng_data();
      tmp_dis_v += batt_data[it->volt_ch];
      DELAY_MS(1);
    }
    batt_data[it->volt_ch] = tmp_dis_v / SAMP_CNT;
    batt_discharge_volt[index++] = batt_data[it->volt_ch];
  }
  discharge_io->set_low();
 // Wait for the voltage to rise
  DELAY_MS(VOLT_TO_RISE_MIN_TIME);
   // battery normal voltage
  index = 0;
  for (vector<Res_ccs_adc_channels>::iterator it = adc_chn.begin(); it != adc_chn.end(); it++)
  {
    for(int i =0 ; i < SAMP_CNT ;i++)
    {
      batt_data = adc->get_eng_data();
      tmp_nomal_v += batt_data[it->volt_ch];
      DELAY_MS(1);
    }
    batt_data[it->volt_ch] = tmp_nomal_v / SAMP_CNT;
    batt_normal_volt[index++] = batt_data[it->volt_ch];
  }
  
  for (int i = 0; i < adc_chn.size(); i++)
  {
    // calculate battery Voltage difference
    volt_drop = batt_normal_volt[i] > batt_discharge_volt[i] ? (batt_normal_volt[i] - batt_discharge_volt[i]) : 0;
    // discharge resistance voltage lower than 10mA(adc acquire drift)，means discharge wire not connected
    if (((-0.0000001 < volt_drop) && (volt_drop < 0.0000001)) || ((-0.0000001 < current) && (current < 0.0000001)))
    {
      ress[i] = 0;
    }
    else
    {
      //calculate resistance
      ress[i] = (double)(volt_drop) * res_scale / current;
    }
  }

  return &ress;
}
