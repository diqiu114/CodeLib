#include "cont_adc.h"
#include <stdlib.h>
#include "string.h"

Cont_adc::Cont_adc(ADC_HandleTypeDef* adc, Adc_para* _para, TIM_HandleTypeDef *_htim, unsigned int _tim_ch,
           adc_iar_callback _adc_callback)
{
  hadc = adc;
  htim = _htim;
  tim_ch = _tim_ch;
  ad_val_max = _para->ad_max;
  adc_ref_volt_in_mv = _para->ref_volt_mv;
  para = _para;
  adc_callback = _adc_callback;
}
void Cont_adc::complete_irq_handle(void)
{
  if(adc_callback)
  {
    adc_callback(hadc, 2);
  }
//  stop();
}
void Cont_adc::half_irq_handle(void)
{
  if(adc_callback)
  {
    adc_callback(hadc, 1);
  }
}

/**
 * ad_to_volt
 * @param ad TODO
 * @return TODO
 */
float Cont_adc::ad_to_volt(float ad)
{
  return ( ad * adc_ref_volt_in_mv / ad_val_max); 
}



/**
 * start_acq
 * @param buffer TODO
 * @param acq_cnt TODO
 * @return TODO
 */
bool Cont_adc::start_acq(short *buffer, unsigned int acq_cnt)
{
  if( State != Adc_State_busy )
  {

    HAL_ADC_Start_DMA(hadc, (unsigned int *)buffer, acq_cnt );
    
    if( htim != NULL )
    {
      HAL_TIM_PWM_Start(htim, tim_ch);
    }
      
    State = Adc_State_busy;

    return true;
  }

  return false;
}

/**
 * Adc_ConvCpltCallback
 *
 */
void Cont_adc::stop(void)
{
  HAL_ADC_Stop_DMA(hadc);
  
  if( htim != NULL )
  {
    HAL_TIM_PWM_Stop(htim, tim_ch);
  }
  
  State = Adc_State_ready;
}

ADC_HandleTypeDef* Cont_adc::get_adc_handle(void)
{
  return hadc;
}
Cont_adc::~Cont_adc()
{
}

