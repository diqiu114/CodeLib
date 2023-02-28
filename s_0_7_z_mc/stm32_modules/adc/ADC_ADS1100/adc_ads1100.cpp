#include "adc_ads1100.h"

Adc_Ads1100::Adc_Ads1100(I2c_if *_i2c_handle, Data_convert_if *_convert_rate, Data_convert_if *_convert_calib, float _volt_ref)
{
  i2c_handle = _i2c_handle;
  convert_rate = _convert_rate;
  convert_calib = _convert_calib;
  volt_ref = _volt_ref;
  memset(recv_data, 0, sizeof(recv_data));
  init();
}

Adc_Ads1100::~Adc_Ads1100()
{
}

Adc_state_e Adc_Ads1100::get_state()
{
  memset(recv_data, 0, sizeof(recv_data));
  if (i2c_handle->receive(IIC_R_ADDR_ADS1100A0IDBVR, recv_data, 3))
  {
    if ((recv_data[DATA_CONFIG_DATA_OFFSET] & SINGLE_MODE) != 0)
    {
      // 单次采集模式
      return (Adc_state_e)(recv_data[DATA_CONFIG_DATA_OFFSET]);
    }
    else
    {
      //连续采集模式总是在采集状态
      return CONVERSION_ALWAYS_STARTING;
    }
  }
  return CONVERSION_ERR;
}

bool Adc_Ads1100::init()
{
  return config(CONTINUOUS_CONVERSION_MODE, DATA_RATE_8_SPS, GAIN_1);
}

bool Adc_Ads1100::config(Conver_mode_e _conver_mode, Data_rate_e _data_rate, Gain_config_e _gain)
{
  send_buff = IIC_ADDR_RESET;
  if (!i2c_handle->send(IIC_W_ADDR_ADS1100A0IDBVR, &send_buff, 1))
  {
    return false;
  }

  send_buff |= SINGLE_MODE_START;

  switch (_conver_mode)
  {
  case SINGLE_CONVERSION_MODE:
    send_buff |= SINGLE_MODE;
    break;
  case CONTINUOUS_CONVERSION_MODE:
    send_buff |= CONTINUOS_MODE;
    break;
  default:
    return false;
  }

  switch (_data_rate)
  {
  case DATA_RATE_128_SPS:
    send_buff |= SPS_128;
    min_code = MIN_CODE_SPS_128;
    break;
  case DATA_RATE_32_SPS:
    send_buff |= SPS_32;
    min_code = MIN_CODE_SPS_32;
    break;
  case DATA_RATE_16_SPS:
    send_buff |= SPS_16;
    min_code = MIN_CODE_SPS_16;
    break;
  case DATA_RATE_8_SPS:
    send_buff |= SPS_8;
    min_code = MIN_CODE_SPS_8;
    break;
  default:
    return false;
  }

  switch (_gain)
  {
  case GAIN_1:
    send_buff |= PGA_GAIN_1;
    gain = 1;
    break;
  case GAIN_2:
    send_buff |= PGA_GAIN_2;
    gain = 2;
    break;
  case GAIN_4:
    send_buff |= PGA_GAIN_4;
    gain = 4;
    break;
  case GAIN_8:
    send_buff |= PGA_GAIN_8;
    gain = 8;
    break;
  default:
    return false;
  }
  config_data = send_buff;
  if (!i2c_handle->send(IIC_W_ADDR_ADS1100A0IDBVR, &send_buff, 1))
  {
    return false;
  }
  return true;
}

bool Adc_Ads1100::get_data(float *data)
{
  memset(recv_data, 0, sizeof(recv_data));
  if (i2c_handle->receive(IIC_R_ADDR_ADS1100A0IDBVR, recv_data, 3))
  {
    if (config_data != recv_data[DATA_CONFIG_DATA_OFFSET])
    {
      return false;
    }
    config_data = recv_data[DATA_CONFIG_DATA_OFFSET];
    switch (config_data & DATA_RATE_BIT)
    {
    case SPS_128:
      min_code = MIN_CODE_SPS_128;
      break;
    case SPS_32:
      min_code = MIN_CODE_SPS_32;
      break;
    case SPS_16:
      min_code = MIN_CODE_SPS_16;
      break;
    case SPS_8:
      min_code = MIN_CODE_SPS_8;
      break;
    default:
      return false;
    }

    switch (config_data & DATA_GAIN_BIT)
    {
    case PGA_GAIN_1:
      gain = 1;
      break;
    case PGA_GAIN_2:
      gain = 2;
      break;
    case PGA_GAIN_4:
      gain = 4;
      break;
    case PGA_GAIN_8:
      gain = 8;
      break;
    default:
      return false;
    }
    result = (short)(recv_data[DATA_CONVERSION_DATA_OFFSET]) << 8 | recv_data[DATA_CONVERSION_DATA_OFFSET + 1];

    result = -1 * result * volt_ref / min_code / gain;
    if (convert_rate != NULL)
    {
      result = convert_rate->convert(result);
    }
    if (convert_calib != NULL)
    {
      result = convert_calib->convert(result);
    }
    *data = result;
    return true;
  }
  return false;
}

bool Adc_Ads1100::set_transf_para(Data_convert_if *_convert_rate)
{
  if (_convert_rate != NULL)
  {
    convert_rate = _convert_rate;
    return false;
  }
  return true;
}

bool Adc_Ads1100::set_calib_para(Data_convert_if *_convert_calib)
{
  if (_convert_calib != NULL)
  {
    convert_calib = _convert_calib;
    return false;
  }
  return true;
}
