#include "ntc_temp.h"

Ntc_temp::Ntc_temp(Adc_app *_adc, int _adc_chn)
{
    adc_app = _adc;
    adc_chn = _adc_chn;
    
}

Ntc_temp::~Ntc_temp()
{
 if(adc_app != NULL)
  {
    delete adc_app;
    adc_app = NULL;
  }
}

void Ntc_temp::timeout_callback()
{
  //空实现
}

void Ntc_temp::start(void)
{
    //空实现接口函数
}

float Ntc_temp::get_temp(void)
{
    return adc_app->get_eng_data(adc_chn);
}

Temp_sensor_status Ntc_temp::get_status(void)
{
    //空实现接口函数
    return READ_READY;
}
