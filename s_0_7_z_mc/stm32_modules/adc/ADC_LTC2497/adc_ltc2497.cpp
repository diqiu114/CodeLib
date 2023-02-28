#include "adc_ltc2497.h"

#define W_RETRY_TIMES (30)
#define R_RETRY_TIMES (30)

Adc_Ltc2497::Adc_Ltc2497(I2c_if *_i2c_handle, Rate_t *_rate_para, Calib_t *_calib_para, float _ref)
{
  i2c_handle = _i2c_handle;
  if (_rate_para != NULL)
  {
    rate_para = _rate_para;
  }
  if (_calib_para != NULL)
  {
    calib_para = _calib_para;
  }
  if (_ref != 0)
  {
    ref = _ref;
  }
}

Adc_Ltc2497::~Adc_Ltc2497()
{
}

bool Adc_Ltc2497::init()
{
  return true;
}

bool Adc_Ltc2497::translated_channel(unsigned char iic_addr, float *acq_data_buff, unsigned char select_ch)
{
  if (i2c_handle->send(ADDR_LTC2497_1 << 1, &channel_value[select_ch], 1) == 0)
    return true;
  else
    return false;
}

bool Adc_Ltc2497::set_transf_para(Rate_t *_rate_para)
{
  if (_rate_para != NULL)
  {
    rate_para = _rate_para;
    return true;
  }
  else
    return false;
}

bool Adc_Ltc2497::set_calib_para(Calib_t *_calib_para)
{
  if (_calib_para != NULL)
  {
    calib_para = _calib_para;
    return true;
  }
  else
    return false;
}

bool Adc_Ltc2497::get_data(unsigned char iic_addr, float *acq_data_buff, unsigned char start_ch, unsigned char end_ch)
{

  unsigned char buff[3] = {0};
  bool w_flag = false, r_flag = false;
  unsigned short w_retry_times = W_RETRY_TIMES, r_retry_times = R_RETRY_TIMES;
  unsigned char channel_num[16] = {0}, num = 0, status_flag[16] = {0}, rate_calib_num = 0;
  unsigned int adc_data = 0;

  for (num = start_ch; num < end_ch; num++)
  {
    w_flag = false;
    r_flag = false;
    w_retry_times = W_RETRY_TIMES;
    r_retry_times = R_RETRY_TIMES;

    if (num % 2 == 0)
      channel_num[num] = 0xb0 + num / 2;
    else
      channel_num[num] = 0xb8 + num / 2;

    switch (iic_addr)
    {
    case ADDR_LTC2497_1:
      rate_calib_num = num;
      break;

    case ADDR_LTC2497_2:
      rate_calib_num = num + 16;
      break;

    case ADDR_LTC2497_3:
      rate_calib_num = num + 32;
      break;
    }
    while (w_retry_times-- && !w_flag)
    {
      w_flag = i2c_handle->send(iic_addr << 1, &channel_num[num], 1);
      vTaskDelay(10);
    }
    //    w_flag = i2c_handle->send(iic_addr << 1, &channel_num[num], 1) ;
    if (w_flag)
    {
      while (r_retry_times-- && !r_flag)
      {
        r_flag = i2c_handle->receive((iic_addr << 1) | 1, buff, 3);
        vTaskDelay(10);
      }
      //      vTaskDelay(300);
      //      i2c_handle->receive((iic_addr << 1) | 1, buff, 3);
      status_flag[num] = (buff[0] >> 6) & 0x03;
      adc_data = ((buff[0] & 0x3f) << 10) + (buff[1] << 2) + (buff[2] >> 6);
      if (status_flag[num] == 2)
      {
        acq_data_buff[num] = (float)adc_data / 65536 * ref * 1000;
        acq_data_buff[num] = acq_data_buff[num] * rate_para->cell_rate[rate_calib_num].k + rate_para->cell_rate[rate_calib_num].b;
        acq_data_buff[num] = acq_data_buff[num] * calib_para->cell_calib[rate_calib_num].k + calib_para->cell_calib[rate_calib_num].b;
      }
      else
      {
        acq_data_buff[num] = 0;
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}
