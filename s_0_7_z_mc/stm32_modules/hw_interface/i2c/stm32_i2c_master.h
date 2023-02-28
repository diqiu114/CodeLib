/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      stm32 I2C 实现
*
***********************************************************/

#ifndef _STM32_I2C_H_
#define _STM32_I2C_H_

#include "i2c_if.h"
#include "main.h"

#define I2C_TIME_OUT (20)

class Stm32_i2c_master : public I2c_if
{
public:
  Stm32_i2c_master(I2C_HandleTypeDef *i2c_handle, unsigned int _timeout = I2C_TIME_OUT);
  virtual ~Stm32_i2c_master();
  
  virtual bool send(unsigned short dev_addr, unsigned char *data, unsigned int data_len);
  virtual bool receive(unsigned short dev_addr, unsigned char *data, unsigned int data_len);
  virtual bool mem_send(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len);
  virtual bool mem_receive(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len);

private:
  I2C_HandleTypeDef *handle;
  unsigned int timeout;
};

#endif // _Stm32_GPIO_H_
