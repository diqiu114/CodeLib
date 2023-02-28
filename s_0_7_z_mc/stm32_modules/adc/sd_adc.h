/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      SD ADC多通道数据采集类
*
* 版本:
* V1.0 2018-04-03 
***********************************************************/

#ifndef _SD_ADC_H_
#define _SD_ADC_H_

#include "stdbool.h"
#include "main.h"
#include "adc_acq.h"

#define SD_AD_VAL_MID (0x7FFF)
#define SD_AD_VAL_MAX (0xFFFF)
#define SD_ADC_REF_VOLT_IN_MV (3300)

class Sd_adc : public Adc_acq
{
public:
  Sd_adc(SDADC_HandleTypeDef *adc,
         Adc_para *_para,
         TIM_HandleTypeDef *_htim = NULL,
         unsigned int _tim_ch = 0,
         unsigned int ad_mid = SD_AD_VAL_MID);

  virtual void stop(void);
  virtual float ad_to_volt(float ad);
  virtual bool start_acq(short *buffer, unsigned int acq_cnt);
  virtual ~Sd_adc();

private:
  SDADC_HandleTypeDef *hadc;
  unsigned short adc_ref_volt_in_mv;
  unsigned short ad_val_max;
  unsigned short ad_val_mid;
};

#endif // _SD_ADC_H_
