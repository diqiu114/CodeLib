/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      SAR ADC 应用类
*
* 版本:
* V1.0 2019-04-29 初始程序编写 
***********************************************************/
#ifndef _ADC_APP_H_
#define _ADC_APP_H_

#include "adc_acq.h"
#include "..\data_convert\data_convert_if.h"
class Adc_app
{
public:
  Adc_app(Adc_acq *_adc_acq);
  virtual ~Adc_app();

  float get_eng_data(unsigned int idx);
  float *get_eng_data(void);

  bool set_calib(vector<Data_convert_if *> &_calib);
  bool set_rate(vector<Data_convert_if *> &_rate);

  bool modify_calib(Data_convert_if *_calib, unsigned char idx = 0);
  bool modify_rate(Data_convert_if *_rate, unsigned char idx = 0);

  void stop_acq(void);

private:
  Adc_acq *adc_acq;
  vector<Data_convert_if *> calib;
  vector<Data_convert_if *> rate;
  float *eng_data;
  unsigned int channel_cnt;
};

#endif //_ADC_APP_H_
