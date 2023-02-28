/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      8位数码管驱动
*版本
V1.0 2020-08-09 初始编制
使用说明：
1.先将数码管公共引脚载入vector，将段选引脚传入vector并作为参数实现构造函数，
2.使用set_data将数据载入存储区
3.创建低优先级任务，任务内一直调用show_data
4.需要修改显示内容时，直接调用set_data即可
***********************************************************/

#ifndef __SEGMENT_LED_H__
#define __SEGMENT_LED_H__

#include <vector>
#include "hw_interface/gpio/stm32_gpio.h"

using namespace std;

class Segment_led
{
  public:
  Segment_led( vector<Gpio_if*> &_comm_gpios,vector<Gpio_if*> &_seg_gpios,GPIO_STATUES _comm_sta,unsigned short delay = 0);
  ~Segment_led();
  void set_data(unsigned char* _data,unsigned char offset = 0);
  void show_data();
  void show_ascii_single(unsigned char ascii, unsigned short location);
  
  private:
  void set_common(unsigned char common);
  void show_ascii(unsigned char ascii);
  void led_delay(unsigned int _delay);
  
  vector<Gpio_if*> comm_gpios;
  vector<Gpio_if*> seg_gpios;
  GPIO_STATUES sel_comm_sta;
  unsigned char data_len;
  unsigned char* data;
  unsigned short delay;

};

#endif

