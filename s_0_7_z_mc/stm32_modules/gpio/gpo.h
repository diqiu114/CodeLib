/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      GPO类
*
* 版本:
* V1.0 2019-04-30 初始化版本编写 
***********************************************************/

#ifndef _GPO_H_
#define _GPO_H_

#include <stdbool.h>
#include "gpio.h"

typedef struct _tag_gpio_info_
{
  GPIO_TypeDef* port;
  unsigned short pin;
}Gpo_Info;

class Gpo
{
public:
  Gpo(Gpo_Info* info, unsigned int cnt);
  void reverse(void);
  void on(unsigned int idx);
  void off(unsigned int idx);
  void toggle(unsigned int idx);
  virtual ~Gpo();

private:
  Gpo_Info* gpo_info;
  unsigned int pin_cnt;
  unsigned int gpio_info_size;
  bool reverse_control;
};

#endif // _GPO_H
