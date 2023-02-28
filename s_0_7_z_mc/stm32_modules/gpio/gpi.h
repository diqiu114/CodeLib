/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      GPIO输入类
*
* 版本:
* V1.1 2019-04-30 修改Gpio_Info结构体名称为Gpi_Info
* V1.0 2018-11-07 初始化版本编写 
***********************************************************/

#ifndef _GPI_H_
#define _GPI_H_

#include <stdbool.h>
#include "gpio.h"

typedef struct _tag_gpi_info_
{
  GPIO_TypeDef* port;
  unsigned short pin;
}Gpi_Info;

class Gpi
{
public:
  Gpi(Gpi_Info* info, unsigned int cnt);
  void reverse(void);
  unsigned int read(void);
  unsigned char read(unsigned char idx);
  virtual ~Gpi();

private:
  Gpi_Info* gpi_info;
  unsigned int pin_cnt;
  unsigned int gpio_info_size;
  bool reverse_ret;
};

#endif // _GPI_H_
