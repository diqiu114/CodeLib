/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      stm32 microseconds delay
*
***********************************************************/

#ifndef _STM32_DELAY_US_H_
#define _STM32_DELAY_US_H_

#include "delay_if.h"

class Stm32_delay_us : public Delay_if
{
public:
  Stm32_delay_us(unsigned char sys_clk);
  virtual void delay(unsigned int cnt);
  virtual ~Stm32_delay_us();
private:
  unsigned char fac_us;
};


#endif // _STM32_DELAY_US_H_
