/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ADC多通道连续采样
*
***********************************************************/

#ifndef _CONT_ADC_H_
#define _CONT_ADC_H_

#include "stdbool.h"
#include "../adc_acq.h"
#include "main.h"
#include "paras.h"

typedef void (*adc_iar_callback) (ADC_HandleTypeDef* adc_handle, unsigned int adc_irq_type);

class Cont_adc
{
public:
  Cont_adc(ADC_HandleTypeDef* adc, Adc_para* _para = NULL, TIM_HandleTypeDef *_htim = NULL, unsigned int _tim_ch = 0,
           adc_iar_callback _adc_callback = NULL);
  void half_irq_handle(void);
  void complete_irq_handle(void);
  void stop(void);
  float ad_to_volt(float ad);
  bool start_acq(short *buffer, unsigned int acq_cnt);
  ADC_HandleTypeDef* get_adc_handle(void);
  virtual ~Cont_adc();

  adc_iar_callback adc_callback;
  Adc_para *para;
protected:
  volatile Adc_State State;  
private:
  ADC_HandleTypeDef* hadc;
  TIM_HandleTypeDef *htim;
  unsigned int tim_ch;
  unsigned short adc_ref_volt_in_mv;
  unsigned short ad_val_max;
};

#endif // _CONT_ADC_H_
