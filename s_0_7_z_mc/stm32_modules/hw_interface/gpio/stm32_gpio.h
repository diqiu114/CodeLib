/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      stm32 gpio 实现
*
***********************************************************/

#ifndef _STM32_GPIO_H_
#define _STM32_GPIO_H_

#include "gpio_if.h"
#include "main.h"

class Stm32_gpio : public Gpio_if
{
public:
  Stm32_gpio(GPIO_TypeDef *_port, unsigned short _pin);
  virtual ~Stm32_gpio();
  virtual void set_hi(void);
  virtual void set_low(void);
  virtual GPIO_STATUES read(void);
  virtual void set_mode_in(GPIO_PULL pull, GPIO_SPEED speed);
  virtual void set_mode_out(GPIO_OTYPE type, GPIO_PULL pull, GPIO_SPEED speed);
  virtual void set_mode_it(GPIO_IT_TYPE type, GPIO_PULL pull, GPIO_SPEED speed);
private:
  GPIO_TypeDef *port;
  unsigned short pin;
  GPIO_InitTypeDef GPIO_InitStruct;
};

#endif // _Stm32_GPIO_H_
