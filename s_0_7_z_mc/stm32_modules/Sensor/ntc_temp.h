/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      NTC temp driver
*
* 版本:
* V1.0 2020-06-23 初始版本编写
***********************************************************/

#ifndef _NTC_TEMP_H_
#define _NTC_TEMP_H_

#include "stdbool.h"
#include "modules_def.h"
#include "sensor\measure_interfaces.h"
#include "adc\adc_app.h"


class Temp_adc_channels
{
  public:
    Temp_adc_channels(int _volt_ch)
    {
      volt_ch = _volt_ch;
    };
    int volt_ch;
};

class Ntc_temp : public Temperature_sensor_if
{
public:
  Ntc_temp(Adc_app *_adc, int _adc_chn);
  virtual ~Ntc_temp();
  virtual void start(void);
  virtual float get_temp(void);
  virtual Temp_sensor_status get_status(void);
  virtual void timeout_callback();
private:
  Adc_app *adc_app;
  int adc_chn;
  Temp_sensor_status status;
};

#endif
