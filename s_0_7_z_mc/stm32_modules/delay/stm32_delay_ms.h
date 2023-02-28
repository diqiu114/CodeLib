/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      stm32 millisencods delay
*
* 版本:
* V1.0 2019-08-16 初始版本移植
***********************************************************/

#ifndef _STM32_DELAY_MS_H_
#define _STM32_DELAY_MS_H_

#include "main.h"
#include "delay_if.h"

#if (USE_FREE_RTOS)
#include "cmsis_os.h"
#define DELAY_MS(x) vTaskDelay(x)
#else
#define DELAY_MS(x) HAL_Delay(x)
#endif

class Stm32_delay_ms : public Delay_if
{
public:
  Stm32_delay_ms(){};
  virtual void delay(unsigned int cnt)
  {
    DELAY_MS(cnt);
  };
  virtual ~Stm32_delay_ms(){};
};

#endif // _STM32_DELAY_MS_H_
