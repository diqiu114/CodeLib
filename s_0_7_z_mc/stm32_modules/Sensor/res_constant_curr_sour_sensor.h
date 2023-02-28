#ifndef _RES_CONSTANT_CURR_SOUR_SENSOR_
#define _RES_CONSTANT_CURR_SOUR_SENSOR_

#include <vector>
#include "adc\adc_app.h"
#include "sensor\measure_interfaces.h"
#include "hw_interface\gpio\gpio_if.h"
#include "modules_def.h"
using namespace std;
//恒流源内阻采集通道(ccs恒流源简写)
class Res_ccs_adc_channels
{
public:
    Res_ccs_adc_channels(int _volt_ch)
    {
      volt_ch = _volt_ch;
    };
    int volt_ch;
};

class Res_constant_curr_sour_sensor : public Res_sensor_if
{
public:
  Res_constant_curr_sour_sensor(Gpio_if* _discharge_io, 
                    Adc_app *_adc, 
                    vector<Res_ccs_adc_channels>& _adc_chn, 
                    float ccs_curr_ma = 20600,
                    unsigned int _dishcarge_delay = 1,
                    unsigned int _res_scale = 1000000);
  virtual ~Res_constant_curr_sour_sensor();
  virtual vector<float>* get_res();
  virtual unsigned int get_res_chn_cnt();

private:
  Adc_app *adc;
  Gpio_if* discharge_io;
  vector<float> ress;
  vector<Res_ccs_adc_channels> adc_chn;
  vector<float> batt_normal_volt;
  vector<float> batt_discharge_volt;
  unsigned int dishcarge_delay;
  float current;
  float res_scale;
  float last_drop;
  bool is_first;
};

#endif
