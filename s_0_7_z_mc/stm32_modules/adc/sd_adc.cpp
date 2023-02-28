#include "sd_adc.h"
#include <stdlib.h>
#include "string.h"

Sd_adc::Sd_adc(SDADC_HandleTypeDef *adc,
               Adc_para *_para,
               TIM_HandleTypeDef *_htim = NULL,
               unsigned int _tim_ch = 0,
               unsigned int ad_mid = SD_AD_VAL_MID) : Adc_acq(_para)
{
  hadc = adc;
  // avg_flt_peak_cnt = DEFAULT_AVG_FLT_PEAK_CNT;
  ad_val_max = _para->ad_max;
  adc_ref_volt_in_mv = _para->ref_volt_mv;
  ad_val_mid = ad_mid;
}

/**
 * ad_to_volt
 * @param ad TODO
 * @return TODO
 */
float Sd_adc::ad_to_volt(float ad)
{
  return (((ad + ad_val_mid) * adc_ref_volt_in_mv) / ad_val_max);
}

/**
 * start_acq
 * @param buffer TODO
 * @param acq_cnt TODO
 * @return TODO
 */
bool Sd_adc::start_acq(short *buffer, unsigned int acq_cnt)
{
  if (State != Adc_State_busy)
  {
    HAL_SDADC_InjectedStart_DMA(hadc, (unsigned int *)buffer, acq_cnt);

    if (htim != NULL)
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
void Sd_adc::stop(void)
{
  HAL_SDADC_InjectedStop_DMA(hadc);

  if (htim != NULL)
  {
    HAL_TIM_PWM_Stop(htim, tim_ch);
  }

  State = Adc_State_ready;
}

Sd_adc::~Sd_adc()
{
}
