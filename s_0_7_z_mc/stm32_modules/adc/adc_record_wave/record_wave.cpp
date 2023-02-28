#include "record_wave.h"
#include <stdlib.h>
#include "string.h"

Record_wave::Record_wave(Cont_adc *_cont_adc,
           unsigned short _adc_avg_cnt,
           unsigned short *_adc_thr_val)
{
  cont_adc = _cont_adc;
  adc_avg_cnt = _adc_avg_cnt;
  adc_thr_val = _adc_thr_val;
  idx_over_thr = -1;
  Dma_buffer = new short[cont_adc->para->ch_cnt * cont_adc->para->ch_samp_cnt];
  if (Dma_buffer == NULL)
  {
    return;
  }  
  Proc_dma_buf = new short[cont_adc->para->ch_cnt * cont_adc->para->ch_samp_cnt / adc_avg_cnt];
  if (Proc_dma_buf == NULL)
  {
    return;
  }
}
short *Record_wave::adc_get_raw_all(unsigned char start_cnt)
{
  cont_adc->start_acq(Dma_buffer, cont_adc->para->ch_cnt * cont_adc->para->ch_samp_cnt);

  // wait adc acquire complete
//  while (State != Adc_State_ready)
//    ;

  return Dma_buffer;
}
void Record_wave::dma_data_avg(unsigned char irq_state)
{
  int i;
  int comp_cnt;

  comp_cnt = irq_state + 1;
  for(i = cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt / 2 * irq_state; 
      i < (cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt * comp_cnt) / 2; i+=cont_adc->para->ch_cnt*adc_avg_cnt)
  {
    for (int ch_cnt = 0;ch_cnt < cont_adc->para->ch_cnt; ch_cnt++)
    {
      Proc_dma_buf[i/adc_avg_cnt + ch_cnt] = 0;
      for (int avg = 0;avg<adc_avg_cnt; avg++)
      {
        Proc_dma_buf[i/adc_avg_cnt + ch_cnt] += Dma_buffer[i + avg * cont_adc->para->ch_cnt + ch_cnt];
      }
      Proc_dma_buf[i/adc_avg_cnt + ch_cnt] /= adc_avg_cnt;
#if AC_MODULE
#else      
//      if(Proc_dma_buf[i/adc_avg_cnt + ch_cnt] > 80)
//        Proc_dma_buf[i/adc_avg_cnt + ch_cnt] = Proc_dma_buf[i/adc_avg_cnt + ch_cnt] * 1.02 + 17;
#endif      
    }
  } 
}
short *Record_wave::half_data_threshold_proc(void)
{
  bool loop = true;
  dma_data_avg(0);
  if(idx_over_thr >= (cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt / adc_avg_cnt )/ 2 && idx_over_thr != -1)
  {
    return Dma_buffer;
  }
  idx_over_thr = -1;
 // 半中断时，判断前半部分是否有超阈值
  for(int avg_cnt = 0; (loop) && avg_cnt < (cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt / adc_avg_cnt) / 2; avg_cnt += cont_adc->para->ch_cnt)
  {
    for (int ch_cnt = 0; (loop) && ch_cnt < cont_adc->para->ch_cnt; ch_cnt++)
    {
      if ((Proc_dma_buf[avg_cnt + ch_cnt] > adc_thr_val[ch_cnt * 2]) || (Proc_dma_buf[avg_cnt + ch_cnt] < adc_thr_val[ch_cnt * 2 + 1]))
      {
        idx_over_thr = avg_cnt;
        loop = false;
      }
    }  
  }  
  return Dma_buffer;
}

short *Record_wave::complete_data_threshold_proc(void)
{
  bool loop = true;
  dma_data_avg(1);
  if(idx_over_thr >= 0 && idx_over_thr < (cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt / adc_avg_cnt) / 2)
  {
    //stop();
    return Dma_buffer;
    
  }
  idx_over_thr = -1;
 // 全中断时，判断后半部分数据是否有超阈值
  for(int avg_cnt = (cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt / adc_avg_cnt) / 2; (loop) && avg_cnt < cont_adc->para->ch_samp_cnt * cont_adc->para->ch_cnt / adc_avg_cnt; avg_cnt += cont_adc->para->ch_cnt)
  {
    for (int ch_cnt = 0; (loop) && ch_cnt < cont_adc->para->ch_cnt; ch_cnt++)
    {
      if ((Proc_dma_buf[avg_cnt + ch_cnt] > adc_thr_val[ch_cnt * 2]) || (Proc_dma_buf[avg_cnt + ch_cnt] < adc_thr_val[ch_cnt * 2 + 1]))
      {
        idx_over_thr = avg_cnt;
        loop = false;
      }
    }
  } 
  return Dma_buffer;
}
void Record_wave::show_data_proc(float *ua, float *uc, float *ia, float *ic)
{
  unsigned int tmp_val[4] = {0};
  unsigned short avg_cnt = cont_adc->para->ch_samp_cnt / adc_avg_cnt;

  for(int i = 0; i <  avg_cnt * cont_adc->para->ch_cnt; i += cont_adc->para->ch_cnt)
  {
    tmp_val[0] += Proc_dma_buf[i];
    tmp_val[1] += Proc_dma_buf[i+1];
    tmp_val[2] += Proc_dma_buf[i+2];
    tmp_val[3] += Proc_dma_buf[i+3];
  }
  tmp_val[0] /= avg_cnt;
  tmp_val[1] /= avg_cnt;
  tmp_val[2] /= avg_cnt;
  tmp_val[3] /= avg_cnt;  
  *ia = (((float)tmp_val[0] * DC_CUR_PARA) * G_slope[0].k + G_slope[0].b) / 1000;
  *ic = (((float)tmp_val[1] * DC_CUR_PARA) * G_slope[1].k + G_slope[1].b) / 1000;
  *ua = (((float)tmp_val[2] * DC_VOL_PARA) * G_slope[2].k + G_slope[2].b) / 1000;
  *uc = (((float)tmp_val[3] * DC_VOL_PARA) * G_slope[3].k + G_slope[3].b) / 1000;
}

int Record_wave::get_thr_idx(void)
{
  return idx_over_thr;
}
void Record_wave::set_thr_idx(int idx_val)
{
  idx_over_thr = idx_val;
}

Record_wave::~Record_wave()
{
  delete[] Dma_buffer;
  Dma_buffer = NULL;
  
  delete[] Proc_dma_buf;
  Proc_dma_buf = NULL;
}

