/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      Ltc2497 adc采集芯片类，获取电压值
*
* 版本:
* V1.0 2021-08-25 初始版本程序编写 
***********************************************************/

#ifndef _ADC_LTC2497_H_
#define _ADC_LTC2497_H_
#include "./hw_interface/i2c/i2c_if.h"
#include "modules_def.h"
#include "proj_data_type.h"
#define ADDR_LTC2497_1 (0X14)
#define ADDR_LTC2497_2 (0X15)
#define ADDR_LTC2497_3 (0X24)
#define ADC_MAX_CH (16)
class Adc_Ltc2497
{
public:
  Adc_Ltc2497(I2c_if *_i2c_handle, Rate_t *_rate_para, Calib_t *_calib_para, float ref = 2.5f);
  ~Adc_Ltc2497();
  bool init();
  bool translated_channel(unsigned char iic_addr, float *acq_data_buff, unsigned char select_ch);
  bool get_data(unsigned char iic_addr, float *acq_data_buff, unsigned char start_ch = 1, unsigned char end_ch = 16);
  bool set_transf_para(Rate_t *rate_para);
  bool set_calib_para(Calib_t *calib_para);

private:
  I2c_if *i2c_handle;
  char retry;
  char channel;
  Rate_t *rate_para;
  Calib_t *calib_para;
  unsigned char channel_value[ADC_MAX_CH];
  unsigned char re_data[ADC_MAX_CH * 3];
  unsigned char ref;
};
#endif
