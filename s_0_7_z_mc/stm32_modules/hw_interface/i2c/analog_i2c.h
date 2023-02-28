/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      IO口模拟i2c通讯
*
* 版本:
* V1.0 2021-11-16 初始版本程序编写 
***********************************************************/

#ifndef __ANALOG_I2C__H__
#define __ANALOG_I2C__H__
#include "i2c_if.h"
#include "./hw_interface/gpio/gpio_if.h"
#include "main.h"
#include "./delay/delay_if.h"

class Analog_i2c : public I2c_if
{
public:
  Analog_i2c(Gpio_if *gpio_clk, Gpio_if *gpio_sda, Delay_if *_delay_handle);
  virtual ~Analog_i2c();
  virtual bool send(unsigned short dev_addr, unsigned char *data, unsigned int data_len);
  virtual bool receive(unsigned short dev_addr, unsigned char *data, unsigned int data_len);
  virtual bool mem_send(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len);
  virtual bool mem_receive(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len);

private:
  void set_sda_input_mode();
  void set_sda_output_mode();
  void set_sda_gpio_out_hi();
  void set_sda_gpio_out_low();
  void set_clk_gpio_out_hi();
  void set_clk_gpio_out_low();
  GPIO_STATUES get_gpio_state(Gpio_if *gpio);

  void i2c_start(void);
  void i2c_stop(void);
  bool i2c_wait_ack(void);
  bool i2c_send_byte(unsigned char byte);
  unsigned char i2c_read_byte(bool ack);
  void i2c_read_bytes(unsigned char *recv_buff, unsigned int len);
  bool i2c_send_bytes(unsigned char *byte, unsigned int len);
  void i2c_send_ack(void);
  void i2c_send_nack(void);

  Gpio_if *gpio_clk;
  Gpio_if *gpio_sda;
  Delay_if *delay_handle;
};

#endif
