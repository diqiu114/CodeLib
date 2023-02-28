/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ads1100 采集芯片类，获取电压值
*
* 版本:
* V1.0 2021-11-16 初始版本程序编写 
***********************************************************/

#ifndef _ADC_ADS1100_H_
#define _ADC_ADS1100_H_
#include "./hw_interface/i2c/i2c_if.h"
#include "modules_def.h"
#include "proj_data_type.h"

#define VREF_ADS1100 (3000)
#define DATA_CONFIG_DATA_OFFSET (2)
#define DATA_CONVERSION_DATA_OFFSET (0)

#define IIC_W_ADDR_ADS1100A0IDBVR (0x90)
#define IIC_R_ADDR_ADS1100A0IDBVR (0x91)
#define IIC_ADDR_RESET (0x00)
#define SINGLE_MODE_START (0x80)
#define CONVERSION_STATE (0x80)
#define SINGLE_MODE (0x10)
#define CONTINUOS_MODE (0x00)
#define DATA_RATE_BIT (0x0c)
#define SPS_128 (0x00)
#define SPS_32 (0x04)
#define SPS_16 (0x08)
#define SPS_8 (0x0C)
#define DATA_GAIN_BIT (0x03)
#define PGA_GAIN_1 (0x00)
#define PGA_GAIN_2 (0x01)
#define PGA_GAIN_4 (0x02)
#define PGA_GAIN_8 (0x03)
#define MIN_CODE_SPS_8 (-32768)
#define MIN_CODE_SPS_16 (-16384)
#define MIN_CODE_SPS_32 (-8192)
#define MIN_CODE_SPS_128 (-2048)

typedef enum _con_mode_
{
  SINGLE_CONVERSION_MODE,
  CONTINUOUS_CONVERSION_MODE
} Conver_mode_e;

typedef enum _data_rate_
{
  DATA_RATE_128_SPS,
  DATA_RATE_32_SPS,
  DATA_RATE_16_SPS,
  DATA_RATE_8_SPS,
} Data_rate_e;

typedef enum _gain_config_
{
  GAIN_1,
  GAIN_2,
  GAIN_4,
  GAIN_8
} Gain_config_e;

typedef enum _adc_state_
{
  CONVERSION_FINISHED,
  CONVERSION_STARTING,
  CONVERSION_ALWAYS_STARTING,
  CONVERSION_ERR
} Adc_state_e;

class Adc_Ads1100
{
public:
  Adc_Ads1100(I2c_if *_i2c_handle, Data_convert_if *_convert_rate, Data_convert_if *_convert_calib, float volt_ref = VREF_ADS1100);
  ~Adc_Ads1100();
  bool init();
  Adc_state_e get_state();
  bool get_data(float *data);
  bool set_transf_para(Data_convert_if *_convert_rate);
  bool set_calib_para(Data_convert_if *_convert_calib);
  bool config(Conver_mode_e conver_mode, Data_rate_e data_rate = DATA_RATE_8_SPS, Gain_config_e gain = GAIN_1);

private:
  unsigned char recv_data[3];
  unsigned char send_buff;
  I2c_if *i2c_handle;
  short min_code;
  unsigned char gain;
  float result;
  Data_convert_if *convert_rate;
  Data_convert_if *convert_calib;
  float volt_ref;
  unsigned char config_data;
};
#endif
