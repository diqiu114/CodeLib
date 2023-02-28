#include "resistance_without_differential_sensor.h"
#include "adc.h"

Resistance_without_differential_sensor::Resistance_without_differential_sensor(Gpio_if *_discharge_io, 
                                      Adc_app *_adc, 
                                      vector<Res_adc_without_differental_channels>& _adc_chn, 
                                      float _discharge_res, 
                                      unsigned int _dishcarge_delay,
                                      unsigned char max_retry)
{
  adc = _adc;
  adc_chn = _adc_chn;
  discharge_io = _discharge_io;
  ress.resize(adc_chn.size());
  batt_normal_volt.resize(adc_chn.size());
  batt_discharge_volt.resize(adc_chn.size());
  res_volt_hig.resize(adc_chn.size());
  res_volt_low.resize(adc_chn.size());

  discharge_res = _discharge_res;
  dishcarge_delay = _dishcarge_delay;
  res_scale = 1000000;
  res_thr = 10;
  retry = max_retry;
  volt_drop = 0;
  current = 0;
}

Resistance_without_differential_sensor::~Resistance_without_differential_sensor()
{
  if (adc != NULL)
  {
    delete adc;
    adc = NULL;
  }
}

unsigned int Resistance_without_differential_sensor::get_res_chn_cnt()
{
  return adc_chn.size();
}

float Resistance_without_differential_sensor::get_drop_volt()
{
  return  volt_drop ;
} 

float Resistance_without_differential_sensor::get_dis_curr()
{
  return current;
}  

vector<float> *Resistance_without_differential_sensor::get_res()
{
  // battery normal voltage
  float *batt_data;
  int index = 0;
  float tmp_nomal_v = 0;
  float tmp_dis_v_hig = 0;
  float tmp_dis_v_low = 0;
  
  MX_ADC1_Init(true);
  
  for (vector<Res_adc_without_differental_channels>::iterator it = adc_chn.begin(); it != adc_chn.end(); it++)
  {
    for(int i =0 ; i < retry ;i++)
    {
      batt_data = adc->get_eng_data();
      tmp_nomal_v += batt_data[it->volt_ch];
      DELAY_MS(1);
    }
    batt_normal_volt[index++] = tmp_nomal_v / retry;
  }
  
  
  // discharge
  discharge_io->set_hi();

  DELAY_MS(dishcarge_delay);
  index = 0;
  // battery discharge voltage
  for (vector<Res_adc_without_differental_channels>::iterator it = adc_chn.begin(); it != adc_chn.end(); it++)
  {
    for(int i =0 ; i < retry ;i++)
    {
      batt_data = adc->get_eng_data();
      tmp_dis_v_hig += batt_data[it->res_ch_hig];
      tmp_dis_v_low += batt_data[it->res_ch_low];
      DELAY_MS(1);
    }
//    batt_data[it->volt_ch] = tmp_dis_v / SAMP_CNT;
//    batt_discharge_volt[index++] = batt_data[it->volt_ch];
    
    batt_discharge_volt[index] = batt_data[it->volt_ch];
    res_volt_hig[index] = tmp_dis_v_hig / retry;
    res_volt_low[index] = tmp_dis_v_low / retry;
    index++;
  }
  discharge_io->set_low();
  
  MX_ADC1_Init(false);
  
  // calculate battery resistance
  volt_drop = 0;
  current = 0;
  
  for (int i = 0; i < adc_chn.size(); i++)
  {
    volt_drop = batt_normal_volt[i] > batt_discharge_volt[i] ? (batt_normal_volt[i] - batt_discharge_volt[i]) : 0;
    current = (res_volt_hig[i] -  res_volt_low[i])/ discharge_res;

    // discharge resistance voltage lower than 10mA(adc acquire drift)，means discharge wire not connected
    if (((-0.0000001 < volt_drop) && (volt_drop < 0.0000001)) || ((-0.0000001 < current) && (current < 0.0000001)) || (res_volt_hig[i] - res_volt_low[i]< res_thr))
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
