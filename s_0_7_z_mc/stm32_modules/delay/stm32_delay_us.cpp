#include "Stm32_delay_us.h"
#include "main.h"

// system clock in M
Stm32_delay_us::Stm32_delay_us(unsigned char sys_clk)
{
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  fac_us = sys_clk;
}

Stm32_delay_us::~Stm32_delay_us()
{
}

void Stm32_delay_us::delay(unsigned int cnt)
{
  unsigned int ticks;
  unsigned int told = 0;
  unsigned int tnow = 0;
  unsigned int tcnt = 0;
  unsigned int reload = SysTick->LOAD;

  ticks = cnt * fac_us;
  told = SysTick->VAL;

  while (1)
  {
    tnow = SysTick->VAL;

    if (tnow != told)
    {
      if (tnow < told)
      {
        tcnt += (told - tnow);
      }
      else
      {
        tcnt += (reload - tnow + told);
      }
      told = tnow;
      if (tcnt >= ticks)
      {
        break;
      }
    }
  }
}



