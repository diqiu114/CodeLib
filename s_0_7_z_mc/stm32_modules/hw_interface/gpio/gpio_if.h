/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      GPIO interface
*
***********************************************************/

#ifndef _GPIO_IF_H_
#define _GPIO_IF_H_

#include <stdbool.h>

enum GPIO_STATUES
{
  GPIO_LOW,
  GPIO_HI
};

enum GPIO_MODE
{
  GPIO_MODE_IN,
  GPIO_MODE_OUT
};

// gpio output type
enum GPIO_OTYPE
{
  GPIO_OTYPE_OD,
  GPIO_OTYPE_PP,
};

// gpio interrupt type
enum GPIO_IT_TYPE
{
  GPIO_IT_TYPE_RISING,
  GPIO_IT_TYPE_FALLING,
  GPIO_IT_TYPE_RISING_FALLING
};

enum GPIO_PULL
{
  GPIO_NO_PULL,
  GPIO_PULL_UP,
  GPIO_PULL_DOWN
};
enum GPIO_SPEED
{
  GPIO_SPEED_LO,
  GPIO_SPEED_MED,
  GPIO_SPEED_HI
};

class Gpio_if
{
public:
  virtual void set_hi(void) = 0;
  virtual void set_low(void) = 0;
  virtual GPIO_STATUES read(void) = 0;
  virtual void set_mode_in(GPIO_PULL pull = GPIO_NO_PULL, GPIO_SPEED speed = GPIO_SPEED_LO) = 0;
  virtual void set_mode_out(GPIO_OTYPE type = GPIO_OTYPE_PP, GPIO_PULL pull = GPIO_NO_PULL, GPIO_SPEED speed = GPIO_SPEED_LO) = 0;
  virtual void set_mode_it(GPIO_IT_TYPE type = GPIO_IT_TYPE_FALLING, GPIO_PULL pull = GPIO_NO_PULL, GPIO_SPEED speed = GPIO_SPEED_LO) = 0;
  virtual ~Gpio_if(){};
};

#endif // _GPIO_IF_H_
