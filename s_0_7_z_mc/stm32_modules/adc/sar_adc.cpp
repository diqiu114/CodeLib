#include "sar_adc.h"
#include <stdlib.h>
#include "filter.h"
#include "string.h"

Sar_adc::Sar_adc(ADC_HandleTypeDef* adc, Adc_para* _para, TIM_HandleTypeDef *_htim, unsigned int _tim_ch) : Adc_acq(_para)
{
  hadc = adc;
  htim = _htim;
  tim_ch = _tim_ch;
  ad_val_max = _para->ad_max;
  adc_ref_volt_in_mv = _para->ref_volt_mv;
}

/**
 * ad_to_volt
 * @param ad TODO
 * @return TODO
 */
float Sar_adc::ad_to_volt(float ad)
{
  return ( ad * adc_ref_volt_in_mv / ad_val_max); 
}



/**
 * start_acq
 * @param buffer TODO
 * @param acq_cnt TODO
 * @return TODO
 */
bool Sar_adc::start_acq(short *buffer, unsigned int acq_cnt)
{
  if( Adc_acq::State != Adc_State_busy )
  {

    HAL_ADC_Start_DMA(hadc, (unsigned int *)buffer, acq_cnt );
    
    if( htim != NULL )
    {
      HAL_TIM_PWM_Start(htim, tim_ch);
    }
      
    Adc_acq::State = Adc_State_busy;

    return true;
  }

  return false;
}

/**
 * Adc_ConvCpltCallback
 *
 */
void Sar_adc::stop(void)
{
  HAL_ADC_Stop_DMA(hadc);
  
  if( htim != NULL )
  {
    HAL_TIM_PWM_Stop(htim, tim_ch);
  }
  
  Adc_acq::State = Adc_State_ready;
}

Sar_adc::~Sar_adc()
{

}

