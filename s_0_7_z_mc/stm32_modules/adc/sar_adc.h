/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ADC多通道数据采集类
*
***********************************************************/

#ifndef _SAR_ADC_H_
#define _SAR_ADC_H_

#include "stdbool.h"
#include "adc_acq.h"
#include "main.h"       

class Sar_adc : public Adc_acq
{
public:
  Sar_adc(ADC_HandleTypeDef* adc, Adc_para* _para, TIM_HandleTypeDef *_htim = NULL, unsigned int _tim_ch = 0);
  
  virtual void stop(void);
  virtual float ad_to_volt(float ad);
  virtual bool start_acq(short *buffer, unsigned int acq_cnt);
  virtual ~Sar_adc();

private:
  ADC_HandleTypeDef* hadc;
  TIM_HandleTypeDef *htim;
  unsigned int tim_ch;
  unsigned short adc_ref_volt_in_mv;
  unsigned short ad_val_max;
};

#endif // _SAR_ADC_H_
