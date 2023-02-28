#include "adc_acq.h"
#include <stdlib.h>
#include "string.h"
#include <stdio.h>

//short dma_ch_data[20];

Adc_acq::Adc_acq(Adc_para *_para)
{
  para = _para;
  // 如果峰值过滤数量超过采样的一半，将导致无法计算。
  if( para->peak_cnt * 2 >= para->ch_samp_cnt )
  {
    avg_flt_peak_cnt = para->ch_samp_cnt / 2 - 1;
  }
  else
  {
    avg_flt_peak_cnt = para->peak_cnt;
  }
  
  init_filter_type(para->filter_type);
  init_buffers();
  
  filter = new Filter();
    
  State = Adc_State_ready;
}

const float *Adc_acq::adc_get_all(void)
{
  start_acq(Dma_buffer, para->ch_cnt * para->ch_samp_cnt);

  // wait adc acquire complete
  while (State != Adc_State_ready)
    ;

  // 第一次计算结果时,需有一个延时,否则第一个通道的值计算结果为0
  if (Adc_ch_data[0] == 0)
  {
    
    //    HAL_Delay(1);
  }

  calc_ad_volt();

  return Adc_ch_data;
}

bool Adc_acq::init_buffers(void)
{
  Dma_buffer = new short[para->ch_cnt * para->ch_samp_cnt * sizeof(short)];
  if (Dma_buffer == NULL)
  {
    return false;
  }

  Adc_ch_data = new float[para->ch_cnt * sizeof(float)];
  if (Adc_ch_data == NULL)
  {
    return false;
  }

  Ch_buffer = new short[para->ch_samp_cnt * sizeof(unsigned short)];
  if (Ch_buffer == NULL)
  {
    return false;
  }

  Rms_buffer = new float[para->ch_samp_cnt * sizeof(float)];
  if (Rms_buffer == NULL)
  {
    return false;
  }

  return true;
}


bool Adc_acq::init_filter_type(Filter_type type)
{
  int i = 0;
  Ch_filt_type = new Filter_type[para->ch_cnt * sizeof(Filter_type)]; //(Filter_type*)malloc(para->ch_cnt * sizeof(Filter_type)); // new Filter_type(para->ch_cnt);
  if (Ch_filt_type != NULL)
  {
    for (i = 0; i < para->ch_cnt; i++)
    {
      Ch_filt_type[i] = type;
    }
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * calc_ad_volt
 *
 */

void Adc_acq::calc_ad_volt(void)
{
  for (int ch_num = 0; ch_num < para->ch_cnt; ch_num++)
  {
    short *p_data = ch_data(ch_num);
    
    Adc_ch_data[ch_num] = ad_filter(p_data, para->ch_samp_cnt, ch_num);

    Adc_ch_data[ch_num] = ad_to_volt(Adc_ch_data[ch_num]);
  }
}

/**
 * ad_filter
 * @param data TODO
 * @param size TODO
 * @param ch_num TODO
 * @return TODO
 */
float Adc_acq::ad_filter(short *data, unsigned int size, unsigned char ch_num)
{
  float ret = 0;
  unsigned char filter_type = Ch_filt_type[ch_num];
  // short base_ad = Base_ad_volt[ch_num];

  switch (filter_type)
  {
  case FT_AVG:
    ret = filter->average(data, size);
    // ret -= base_ad;
    break;

  case FT_MEDIAN_AVG:
    ret = filter->median_avg(data, size, avg_flt_peak_cnt);
    // ret -= base_ad;
    break;

  case FT_RMS:
    short_to_float(data, Rms_buffer, size);
    ret = filter->rms(Rms_buffer, size);
    break;
  default:
    break;
  }

  return ret;
}

/**
 * short_to_float
 * @param data TODO
 * @param tar TODO
 * @param size TODO
 * @param base_ad TODO
 */
void Adc_acq::short_to_float(short *data, float *tar, unsigned int size)
{
  int i = 0;

  for (i = 0; i < size; i++)
  {
    tar[i] = data[i] * 1.0f - para->base_ad;
  }
}

/**
 * ch_data
 * @param ch_idx TODO
 * @return TODO
 */
short *Adc_acq::ch_data(unsigned char ch_idx)
{
  int i = 0;

  for (i = 0; i < para->ch_samp_cnt; i++)
  {
    Ch_buffer[i] = Dma_buffer[i * para->ch_cnt + ch_idx];
  }

  return Ch_buffer;
}

Adc_acq::~Adc_acq()
{

  delete[] Ch_filt_type;
  Ch_filt_type = NULL;

  delete[] Dma_buffer;
  Dma_buffer = NULL;

  delete[] Adc_ch_data;
  Adc_ch_data = NULL;

  delete[] Ch_buffer;
  Ch_buffer = NULL;
}
