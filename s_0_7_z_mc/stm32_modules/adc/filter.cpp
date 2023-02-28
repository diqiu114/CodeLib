#include "filter.h"
#include "stdbool.h"
#include "stdio.h"
#include <math.h>

#if (USE_DSP)
#include "arm_math.h"
#endif

//static short low_pass_filter(short cur_val, int *filter_reg);
//static void  bubble_sort(int *array, unsigned int len);
//static void  bubble_sort_short(short *array, unsigned int len);

Filter::Filter()
{
}

int Filter::rc(int pre_val, int cur_val, unsigned char factor)
{
  unsigned char scale = 100;

  // if factor valid
  bool factor_valid = (factor <= scale);

  if (!factor_valid)
  {
    return 0;
  }

  //当前值为第一个值时,前一个值为0,则将当前值赋给前一个值.
  if (pre_val == 0)
  {
    pre_val = cur_val;
  }

  return (((pre_val * 1.0f * factor) + (cur_val * 1.0f * (scale - factor))) / scale);
}

float Filter::rc(float pre_val, float cur_val, unsigned char factor)
{
  unsigned char scale = 100;

  // if factor valid
  bool factor_valid = (factor <= scale);

  if (!factor_valid)
  {
    return 0;
  }

  //当前值为第一个值时,前一个值为0,则将当前值赋给前一个值.
  if (pre_val == 0)
  {
    pre_val = cur_val;
  }

  return (((pre_val * factor) + (cur_val * (scale - factor))) / scale);
}

float Filter::average(int *array, unsigned int size)
{
  float ret = 0;
  int i = 0;

  for (i = 0; i < size; i++)
  {
    ret += array[i] * 1.0;
  }

  ret = ret / size;

  return ret;
}

float Filter::average(short *array, unsigned int size)
{
  float ret = 0;
  int i = 0;

  for (i = 0; i < size; i++)
  {
    ret += array[i];
    //ret = ( ret + array[i] ) >> 1;
  }

  ret = ret / (size * 1.0);

  return ret;
}

float Filter::median_avg(int *array, unsigned int size, unsigned int peak_cnt)
{
  unsigned int filter_cnt = peak_cnt * 2;

  // 滤波数据需小于总数
  if (filter_cnt >= size)
  {
    return 0;
  }

  // sort array
  bubble_sort(array, size);

  return average(array + peak_cnt, size - filter_cnt);
}

float Filter::median_avg(short *array, unsigned int size, unsigned int peak_cnt)
{
  unsigned int filter_cnt = peak_cnt * 2;

  // 滤波数据需小于总数
  if (filter_cnt >= size)
  {
    return 0;
  }

  // sort array
  bubble_sort(array, size);

  return average(array + peak_cnt, size - filter_cnt);
}

void Filter::low_pass(short *input, unsigned int size, short *output, short shift)
{
  int filter_reg = input[0];
  int i = 0;

  for (i = 0; i < size; i++)
  {
    output[i] = low_pass_filter(input[i], &filter_reg, shift);
  }
}

float Filter::rms(float *array, unsigned int len)
{
  float ret = 0;

#if (USE_DSP)
  arm_rms_f32(array, len, &ret);
#else
  ret = soft_rms(array, len);
#endif
  return ret;
}

float Filter::soft_rms(float *pSrc, unsigned int blockSize)
{
  float sum = 0.0f;    /* Accumulator */
  float in;            /* Tempoprary variable to store input value */
  unsigned int blkCnt; /* loop counter */

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* loop Unrolling */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */
    /* Compute sum of the squares and then store the result in a temporary variable, sum  */
    in = *pSrc++;
    sum += in * in;
    in = *pSrc++;
    sum += in * in;
    in = *pSrc++;
    sum += in * in;
    in = *pSrc++;
    sum += in * in;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4U;

  while (blkCnt > 0U)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */
    /* Compute sum of the squares and then store the results in a temporary variable, sum  */
    in = *pSrc++;
    sum += in * in;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Compute Rms and store the result in the destination */
  // arm_sqrt_f32(sum / (float) blockSize, pResult);
  return sqrt(sum / (float)blockSize);
}

/**
 * low_pass_filter
 * @param cur_val TODO
 * @param filter_reg TODO
 * @return TODO
 */
short Filter::low_pass_filter(short cur_val, int *filter_reg, short shift)
{
  *filter_reg = *filter_reg - (*filter_reg >> shift) + cur_val;

  return (*filter_reg >> shift);
}

/**
 * bubble_sort
 * @param array TODO
 * @param len TODO
 */
void Filter::bubble_sort(int *array, unsigned int len)
{
  int temp = 0;

  for (int i = 0; i < len - 1; i++)
  {
    for (int j = 0; j < len - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

/**
 * bubble_sort_short
 * @param array TODO
 * @param len TODO
 */
void Filter::bubble_sort(short *array, unsigned int len)
{
  short temp = 0;

  for (int i = 0; i < len - 1; i++)
  {
    for (int j = 0; j < len - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

Filter::~Filter()
{
}
