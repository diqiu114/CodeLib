/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ADC多通道录制波形类
*
***********************************************************/

#ifndef _RECORD_WAVE_H_
#define _RECORD_WAVE_H_

#include "stdbool.h"
#include "cont_adc.h"
#include "main.h"
#include "paras.h"

#define DEFAULT_AVG_CNT (5)

class Record_wave
{
public:
  Record_wave(Cont_adc *_cont_adc,
           unsigned short _adc_avg_cnt = DEFAULT_AVG_CNT,
           unsigned short *_adc_thr_val = NULL);
  short *adc_get_raw_all(unsigned char start_cnt);
  short *half_data_threshold_proc(void);
  short *complete_data_threshold_proc(void);
  void show_data_proc(float *ua, float *uc, float *ia, float *ic);
  int get_thr_idx();
  void set_thr_idx(int idx_val);
  virtual ~Record_wave();

  Cont_adc *cont_adc;
 
private:
  void dma_data_avg(unsigned char irq_state);
  short *Dma_buffer;
  short *Proc_dma_buf;
  int idx_over_thr;
  unsigned short *adc_thr_val;
  unsigned short adc_avg_cnt;
};

#endif // _RECORD_WAVE_H_
