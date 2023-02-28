/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      Ds18b20 driver
*
* 版本:
* V1.1 2019-09-17 1. 增加外部计时调用与读取温度间隔设置
                  2. 增加温度更新后调用callback函数
* V1.0 2019-08-16 初始版本编写
***********************************************************/

#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "stdbool.h"
#include "onewire.h"
#include "string.h"
#include "modules_def.h"
#include "sensor\measure_interfaces.h"
#include "timer\sys_clock.h"

#define CMD_SKIP_ROM 0xCC
#define CMD_WRITE_SCRA 0x4E //write scratchpad memory
#define CMD_READ_SCRA 0xBE
#define CMD_TEMP_CONV 0x44
#define DS18b20_resolution_12bits 0x7F
#define DS18B20_DATA_FIXED_LEN (9)
#define CMD_DELAY (1)


class Ds18b20 : public Temperature_sensor_if
{
public:
  Ds18b20(Onewire *_ow, int _timeout_ms);
  virtual ~Ds18b20();
  void update(void);
  virtual void start(void);
  virtual float get_temp(void);
  virtual Temp_sensor_status get_status(void);
  virtual void timeout_callback(void);
private:
  bool read_temp();
  void read_cmd(void);
  void conv(void);
  void config(void);
  unsigned char crc8(unsigned char *buff, unsigned char len);


  float temperature;
  Onewire *ow;
  Temp_sensor_status status;
  unsigned char read_data[DS18B20_DATA_FIXED_LEN];
};

#endif
