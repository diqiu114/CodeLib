/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ADC多通道数据采集类
*
* 版本:
* V1.3 2019-04-29 增加获取通道数量函数
                  在构造函数中增加htim默认值为NULL
* V1.2 2019-04-24 增加过滤类
* V1.1 2018-11-25 将基准AD值计算修改为基准电压值,兼容SDADC 
* V1.0 2018-04-03 初始程序编写 
***********************************************************/

#ifndef _ADC_ACQ_H_
#define _ADC_ACQ_H_

#include "stdbool.h"
#include "filter.h"
#include <vector>

using namespace std;

#define DEFAULT_FILTER_TYPE (FT_MEDIAN_AVG)
#define DEFAULT_AVG_FLT_PEAK_CNT (5)

class Adc_para
{
public:
  Adc_para(unsigned int _ch_cnt,
           unsigned int _ch_samp_cnt,
           unsigned int _ad_max,
           unsigned int _ref_volt_mv,
           Filter_type _filter_type = DEFAULT_FILTER_TYPE,
           unsigned int _peak_cnt = DEFAULT_AVG_FLT_PEAK_CNT,
           unsigned short _base_volt_mv = 0)
  {
    ch_cnt = _ch_cnt;
    ch_samp_cnt = _ch_samp_cnt;
    ad_max = _ad_max;
    ref_volt_mv = _ref_volt_mv;
    filter_type = _filter_type;
    peak_cnt = _peak_cnt;
    base_ad = _base_volt_mv*ad_max/ref_volt_mv;
  }

  unsigned int ch_cnt;
  unsigned int ch_samp_cnt;
  unsigned int ad_max;
  unsigned int ref_volt_mv;
  Filter_type filter_type;
  unsigned int peak_cnt;
  unsigned short base_ad;
};

typedef enum _tag_adc_state_
{
  Adc_State_ready = 0,
  Adc_State_busy = 1
} Adc_State;

class Adc_acq
{
public:
  Adc_acq(Adc_para *_para);
  virtual ~Adc_acq();

  const float *adc_get_all(void);
  // void set_timer(void *timer, unsigned int ch);

  virtual float ad_to_volt(float ad) = 0;
  virtual bool start_acq(short *buffer, unsigned int acq_cnt) = 0;
  virtual void stop(void) = 0;
  Adc_para *para;
  // unsigned int get_ch_cnt(void);

protected:
  unsigned int ad_max;
  unsigned int ref_volt_mv;
  volatile Adc_State State;

private:

  bool init_filter_type(Filter_type type);
  bool init_buffers(void);
  void calc_ad_volt(void);

  float ad_filter(short *data, unsigned int size, unsigned char ch_num);
  void short_to_float(short *data, float *tar, unsigned int size);
  short *ch_data(unsigned char ch_idx);

  unsigned int ch_cnt;
  unsigned int ch_samp_cnt;
  unsigned int avg_flt_peak_cnt;

  Filter_type *Ch_filt_type;
  short *Dma_buffer;
  float *Adc_ch_data;
  short *Ch_buffer;
  float *Rms_buffer;
  Filter *filter;
};

#endif // _ADC_ACQ_H_
