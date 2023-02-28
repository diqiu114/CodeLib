#include "analog_i2c.h"

Analog_i2c::Analog_i2c(Gpio_if *_gpio_clk, Gpio_if *_gpio_sda, Delay_if *_delay_handle)
{
  gpio_clk = _gpio_clk;
  gpio_sda = _gpio_sda;
  delay_handle = _delay_handle;
  gpio_clk->set_mode_out(GPIO_OTYPE_PP, GPIO_PULL_UP, GPIO_SPEED_HI);
  gpio_sda->set_mode_out(GPIO_OTYPE_OD, GPIO_NO_PULL, GPIO_SPEED_HI);
}

Analog_i2c::~Analog_i2c()
{
}

bool Analog_i2c::send(unsigned short dev_addr, unsigned char *data, unsigned int data_len)
{
  bool ret = false;
  i2c_start();
  if (data == NULL || data_len == 0)
  {
    return false;
  }
  ret = i2c_send_byte(dev_addr);
  if (ret)
  {
    ret = i2c_send_bytes(data, data_len);
  }
  i2c_stop();
  return ret;
}

bool Analog_i2c::receive(unsigned short dev_addr, unsigned char *data, unsigned int data_len)
{
  bool ret = false;
  i2c_start();
  if (data == NULL || data_len == 0)
  {
    return false;
  }
  ret = i2c_send_byte(dev_addr);
  if (ret)
  {
    i2c_read_bytes(data, data_len);
  }
  i2c_stop();
  return ret;
}

bool Analog_i2c::mem_send(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len)
{
  bool ret = false;
  i2c_start();
  if (data == NULL || data_len == 0)
  {
    return false;
  }

  ret = i2c_send_byte(dev_addr);

  if (ret)
  {
    ret = i2c_send_bytes((unsigned char *)&reg_addr, reg_addr_cnt);
  }

  if (ret)
  {
    ret = i2c_send_bytes(data, data_len);
  }

  i2c_stop();
  return ret;
}

bool Analog_i2c::mem_receive(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char *data, unsigned int data_len)
{
  bool ret = false;
  i2c_start();
  if (data == NULL || data_len == 0)
  {
    return false;
  }
  ret = i2c_send_byte(dev_addr);

  if (ret)
  {
    ret = i2c_send_bytes((unsigned char *)&reg_addr, reg_addr_cnt);
  }

  if (ret)
  {
    i2c_read_bytes(data, data_len);
  }
  i2c_stop();
  return ret;
}

void Analog_i2c::set_sda_input_mode()
{
  gpio_sda->set_mode_in(GPIO_NO_PULL);
}

void Analog_i2c::set_sda_output_mode()
{
  gpio_sda->set_mode_out(GPIO_OTYPE_OD, GPIO_NO_PULL, GPIO_SPEED_HI);
}

void Analog_i2c::set_sda_gpio_out_hi()
{
  gpio_sda->set_hi();
}

void Analog_i2c::set_sda_gpio_out_low()
{
  gpio_sda->set_low();
}

void Analog_i2c::set_clk_gpio_out_hi()
{
  gpio_clk->set_hi();
}

void Analog_i2c::set_clk_gpio_out_low()
{
  gpio_clk->set_low();
}

GPIO_STATUES Analog_i2c::get_gpio_state(Gpio_if *gpio)
{
  return gpio->read();
}

void Analog_i2c::i2c_start(void)
{
  set_sda_output_mode();
  set_clk_gpio_out_hi();
  set_sda_gpio_out_hi();
  delay_handle->delay(4);
  set_clk_gpio_out_hi();
  set_sda_gpio_out_low(); //当SCL线为高电平是， SDA线上由高到低电平跳变
  delay_handle->delay(4);
  set_clk_gpio_out_low(); //钳住，等待发送或接受
}

void Analog_i2c::i2c_stop(void)
{

  set_sda_output_mode();
  set_clk_gpio_out_low();
  set_sda_gpio_out_low();
  delay_handle->delay(4);
  set_clk_gpio_out_hi();
  set_sda_gpio_out_hi(); //当SCL线为高电平是， SDA线上由低到高电平跳变
  delay_handle->delay(4);
}

bool Analog_i2c::i2c_wait_ack(void)
{
  unsigned char ucTimeCnt = 0;
  set_sda_gpio_out_hi();
  delay_handle->delay(1);
  set_sda_input_mode(); //SDA管脚设为输入模式
  set_clk_gpio_out_hi();
  delay_handle->delay(1);
  while (get_gpio_state(gpio_sda))
  {
    ucTimeCnt++;
    delay_handle->delay(1);
    if (ucTimeCnt > 250)
    {
      i2c_stop();
      return false;
    }
  }
  set_clk_gpio_out_low(); //钳住，等待发送或接受
  return true;
}

bool Analog_i2c::i2c_send_byte(unsigned char byte)
{
  unsigned char i = 0;
  set_sda_output_mode();
  set_clk_gpio_out_low(); // 只有在SCL线为低电平时，SDA线才可以改变
  for (i = 0; i < 8; i++)
  {
    if ((byte & 0x80) >> 7) //每次发最高位
    {
      set_sda_gpio_out_hi();
    }
    else
    {
      set_sda_gpio_out_low();
    }
    byte <<= 1; //更新最高位
    delay_handle->delay(2);
    set_clk_gpio_out_hi();
    delay_handle->delay(2);
    set_clk_gpio_out_low();
    delay_handle->delay(2);
  }
  if (!i2c_wait_ack())
  {
    return false;
  }
  return true;
}

bool Analog_i2c::i2c_send_bytes(unsigned char *byte, unsigned int len)
{
  for (int j = 0; j < len; j++)
  {
    if (!i2c_send_byte(byte[j]))
    {
      return false;
    }
  }
  return true;
}

unsigned char Analog_i2c::i2c_read_byte(bool ack)
{
  unsigned char i, recvVal = 0;
  set_sda_input_mode();
  for (i = 0; i < 8; i++)
  {
    set_clk_gpio_out_low();
    delay_handle->delay(2); //等待输出
    set_clk_gpio_out_hi();  //可读取
    recvVal <<= 1;          //将最低位空出
    if (get_gpio_state(gpio_sda))
    {
      recvVal++; //高电平，则最低位为1
    }
    delay_handle->delay(1);
  }
  if (ack)
  {
    i2c_send_ack();
  }
  else
  {
    i2c_send_nack();
  }
  return recvVal;
}

void Analog_i2c::i2c_read_bytes(unsigned char *recv_buff, unsigned int len)
{
  bool ack = true;
  for (int j = 0; j < len; j++)
  {
    if (j == len - 1)
    {
      ack = false;
    }
    recv_buff[j] = i2c_read_byte(ack);
  }
}

void Analog_i2c::i2c_send_ack(void)
{
  set_sda_output_mode();
  set_clk_gpio_out_low();
  set_sda_gpio_out_low();
  delay_handle->delay(2);
  set_clk_gpio_out_hi();
  delay_handle->delay(2);
  set_clk_gpio_out_low();
  //必须加这个否则最后一个读不到
  set_sda_gpio_out_hi();
  delay_handle->delay(1);
}

void Analog_i2c::i2c_send_nack(void)
{
  set_sda_output_mode();
  set_clk_gpio_out_low();
  set_sda_gpio_out_hi();
  delay_handle->delay(2);
  set_clk_gpio_out_hi();
  delay_handle->delay(2);
  set_clk_gpio_out_low();
}
