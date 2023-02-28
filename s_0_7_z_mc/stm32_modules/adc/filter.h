/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      滤波类，由filter.c修改而来
*
* 版本:
* V1.0 2019-04-24 初始程序编写 
***********************************************************/

#ifndef _FILTER_H_
#define _FILTER_H_

enum Filter_type
{
  Flt_FIRST = 0,
  FT_AVG = 0,
  FT_MEDIAN_AVG = 1,
  FT_RMS = 2,
  FT_END = 2
};

class Filter
{
public:
  Filter();
  float rc(float pre_val, float cur_val, unsigned char factor);
  int rc(int pre_val, int cur_val, unsigned char factor);
  float average(int *array, unsigned int size);
  float average(short *array, unsigned int size);
  float median_avg(int *array, unsigned int size, unsigned int peak_cnt);
  float median_avg(short *array, unsigned int size, unsigned int peak_cnt);
  void low_pass(short *input, unsigned int size, short *output, short shift);

  float rms(float *array, unsigned int len);

  ~Filter();

private:
  void bubble_sort(int *array, unsigned int len);
  void bubble_sort(short *array, unsigned int len);
  short low_pass_filter(short cur_val, int *filter_reg, short shift);
  float soft_rms(float *pSrc, unsigned int blockSize);
};

#endif // _FILTER_H_
