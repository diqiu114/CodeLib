/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-07-15
 * 
 * @brief 锐能微 RN8202b 驱动
 *        数据手册: http://www.renergy-me.cn/upfile/2019060315414565.pdf
 * 
 * ***********************************************************
 */

#ifndef _RN8302B_H_
#define _RN8302B_H_
#include <string.h>
#include "hw_interface\spi\spi_if.h"
#include "crc\crc8_if.h"
#include "hw_interface\gpio\gpio_if.h"
#include "rn8302b_reg.h"

#define RN8302B_REG_LEN_MAX (4)

// 380V reference voltage for calibration
#define RN8302B_REF_VOLTAGE (380.0f)//(220.0f) //(380.0f) 
#define RN8302B_REF_VOLTAGE_REG_VAL (42000000)//(42200000)//(44000000)
#define RN8302B_VOLT_SCALE (RN8302B_REF_VOLTAGE / RN8302B_REF_VOLTAGE_REG_VAL)

// 50A reference current for calibaration
#define RN8302B_REF_CURRENT (50.0f)//(1.5f)
#define RN8302B_REF_CURRENT_REG_VAL (26000000)//(7500000)
#define RN8302B_CURR_SCALE (RN8302B_REF_CURRENT / RN8302B_REF_CURRENT_REG_VAL)

#define RN8302B_REF_POWER 1.0f
#define RN8302B_REF_POWER_REG_VAL (6550000)//(7500000)
#define RN8302B_POWER_SCALE (RN8302B_REF_POWER / RN8302B_REF_POWER_REG_VAL)

#define RN8302B_EC  (3200)
#define RN8302B_ENERGY_SCALE (1000.0f / RN8302B_EC)  //WH

// 电压
class Rn8302b_volt
{
public:
  float ua;
  float ub;
  float uc;
};

// 电流
class Rn8302b_curr
{
public:
  float ia;
  float ib;
  float ic;
};

// 有功功率
class Rn8302b_power
{
public:
  float pa;
  float pb;
  float pc;
  float pt;
};

// 无功功率
class Rn8302b_reactive_power
{
public:
  float qa;
  float qb;
  float qc;
  float qt;
};

// 视在功率
class Rn8302b_apparent_power
{
public:
  float sa;
  float sb;
  float sc;
  float st;
};

// 电能
class Rn8302b_energy
{
public:
  float ea;
  float eb;
  float ec;
  float et;
};

class Rn8302b_data
{
public:
  Rn8302b_volt volt;
  Rn8302b_curr curr;
  Rn8302b_power power;
  Rn8302b_reactive_power rtv_power;
  Rn8302b_apparent_power apt_power;
  Rn8302b_energy energy;
  float freq;
};

class Rn8302b_params
{
public:
  Rn8302b_params(float _volt_scale = RN8302B_VOLT_SCALE, float _curr_scale = RN8302B_CURR_SCALE,
                 float _power_scale = RN8302B_POWER_SCALE, float _rtv_power_scale = RN8302B_POWER_SCALE,
                 float _apt_power_scale = RN8302B_POWER_SCALE, float _enenrgy_scale = RN8302B_ENERGY_SCALE)
  {
    volt_scale = _volt_scale;
    curr_scale = _curr_scale;
    power_scale = _power_scale;
    rtv_power_scale = _rtv_power_scale;
    apt_power_scale = _apt_power_scale;
    energy_scale = _enenrgy_scale;
  }

  float volt_scale;
  float curr_scale;
  float power_scale;
  float rtv_power_scale;
  float apt_power_scale;
  float energy_scale;
};

class Rn8302b
{
public:
  Rn8302b(Spi_if *_spi, Gpio_if *_spi_cs, Crc8_if *_crc8, Rn8302b_params *_params = NULL);
  ~Rn8302b();

  bool init(void);

  bool get_all_data(Rn8302b_data *data);
  bool get_volt(Rn8302b_volt *data);
  bool get_current(Rn8302b_curr *data);
  bool get_power(Rn8302b_power *data);
  bool get_reactive_power(Rn8302b_reactive_power *data);
  bool get_apparent_power(Rn8302b_apparent_power *data);
  bool get_energy(Rn8302b_energy *data);
  bool get_volt_freq(float *data);
  unsigned short get_phase_status(void);

  int get_calib_gain(unsigned short reg_addr);
  int get_calib_offset(unsigned short reg_addr);
  int get_istart_setting(float k = 0.001f);
  int get_lost_voltage_setting(float k = 0.5f);
  int get_zxot_setting(float k = 0.05f);

private:
  Spi_if *spi;
  Crc8_if *crc;
  Gpio_if *spi_cs;
  Rn8302b_params *params;
  int get_reg_val(unsigned short reg_addr, unsigned char data_len);
  bool write_reg_val(unsigned short reg_addr, int data, unsigned char data_len);
  bool read_reg(unsigned short reg_addr, unsigned char *ret_data, unsigned char data_len);
  bool write_reg(unsigned short reg_addr, unsigned char *data, unsigned char data_len);
  unsigned char spi_read_write(unsigned char data = 0xFF);
  unsigned char buff[RN8302B_REG_LEN_MAX];
};

#endif // _RN8302B_H_
