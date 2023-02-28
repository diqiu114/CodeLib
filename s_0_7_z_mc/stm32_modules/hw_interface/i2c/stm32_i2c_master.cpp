#include "stm32_i2c_master.h"

Stm32_i2c_master::Stm32_i2c_master(I2C_HandleTypeDef *i2c_handle, unsigned int _timeout)
{
  handle = i2c_handle;
  timeout = _timeout;
}

Stm32_i2c_master::~Stm32_i2c_master()
{
}

bool Stm32_i2c_master::send(unsigned short dev_addr, unsigned char *data, unsigned int data_len)
{
  return (HAL_I2C_Master_Transmit(handle, dev_addr, data, data_len, timeout) == HAL_OK);
}

bool Stm32_i2c_master::receive(unsigned short dev_addr, unsigned char *data, unsigned int data_len)
{
  return (HAL_I2C_Master_Receive(handle, dev_addr, data, data_len, timeout) == HAL_OK);
}

bool Stm32_i2c_master::mem_send(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len)
{
  return (HAL_I2C_Mem_Write(handle, dev_addr, reg_addr, reg_addr_cnt, data, data_len, timeout) == HAL_OK);
}

bool Stm32_i2c_master::mem_receive(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len)
{
  return (HAL_I2C_Mem_Read(handle, dev_addr, reg_addr, reg_addr_cnt, data, data_len, timeout) == HAL_OK);
}
