#include "stm32_gpio.h"
#include "string.h"

Stm32_gpio::Stm32_gpio(GPIO_TypeDef *_port, unsigned short _pin)
{
  port = _port;
  pin = _pin;

  memset((void *)&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
}


Stm32_gpio::~Stm32_gpio()
{
}

void Stm32_gpio::set_hi(void)
{
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void Stm32_gpio::set_low(void)
{
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

GPIO_STATUES Stm32_gpio::read(void)
{
  if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET)
  {
    return GPIO_HI;
  }
  else
  {
    return GPIO_LOW;
  }
}

void Stm32_gpio::set_mode_in(GPIO_PULL pull, GPIO_SPEED speed)
{
  unsigned int stm32_pull;
  unsigned int stm32_speed;

  switch (pull)
  {
  case GPIO_NO_PULL:
    stm32_pull = GPIO_NOPULL;
    break;
  case GPIO_PULL_UP:
    stm32_pull = GPIO_PULLUP;
    break;
  case GPIO_PULL_DOWN:
    stm32_pull = GPIO_PULLDOWN;
    break;
  default:
    stm32_pull = GPIO_NOPULL;
    break;
  }

  switch (speed)
  {
  case GPIO_SPEED_LO:
    stm32_speed = GPIO_SPEED_FREQ_LOW;
    break;
  case GPIO_SPEED_MED:
    stm32_speed = GPIO_SPEED_FREQ_MEDIUM;
    break;
  case GPIO_SPEED_HI:
    stm32_speed = GPIO_SPEED_FREQ_HIGH;
    break;
  default:
    stm32_speed = GPIO_SPEED_FREQ_LOW;
    break;
  }

  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = stm32_pull;
  GPIO_InitStruct.Speed = stm32_speed;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void Stm32_gpio::set_mode_out(GPIO_OTYPE type, GPIO_PULL pull, GPIO_SPEED speed)
{
  unsigned int stm32_pull;
  unsigned int stm32_speed;
  unsigned int stm32_out_type;

  switch (type)
  {
  case GPIO_OTYPE_OD:
    stm32_out_type = GPIO_MODE_OUTPUT_OD;
    break;
  case GPIO_OTYPE_PP:
    stm32_out_type = GPIO_MODE_OUTPUT_PP;
    break;
  default:
    stm32_out_type = GPIO_MODE_OUTPUT_PP;
    break;
  }

  switch (pull)
  {
  case GPIO_NO_PULL:
    stm32_pull = GPIO_NOPULL;
    break;
  case GPIO_PULL_UP:
    stm32_pull = GPIO_PULLUP;
    break;
  case GPIO_PULL_DOWN:
    stm32_pull = GPIO_PULLDOWN;
    break;
  default:
    stm32_pull = GPIO_NOPULL;
    break;
  }

  switch (speed)
  {
  case GPIO_SPEED_LO:
    stm32_speed = GPIO_SPEED_FREQ_LOW;
    break;
  case GPIO_SPEED_MED:
    stm32_speed = GPIO_SPEED_FREQ_MEDIUM;
    break;
  case GPIO_SPEED_HI:
    stm32_speed = GPIO_SPEED_FREQ_HIGH;
    break;
  default:
    stm32_speed = GPIO_SPEED_FREQ_LOW;
    break;
  }

  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = stm32_out_type;
  GPIO_InitStruct.Pull = stm32_pull;
  GPIO_InitStruct.Speed = stm32_speed;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void Stm32_gpio::set_mode_it(GPIO_IT_TYPE type, GPIO_PULL pull, GPIO_SPEED speed)
{
  unsigned int stm32_pull;
  unsigned int stm32_speed;
  unsigned int stm32_it_type;

  switch (type)
  {
  case GPIO_IT_TYPE_RISING:
    stm32_it_type = GPIO_MODE_IT_RISING;
    break;
  case GPIO_IT_TYPE_FALLING:
    stm32_it_type = GPIO_MODE_IT_FALLING;
    break;
  case GPIO_IT_TYPE_RISING_FALLING:
    stm32_it_type = GPIO_MODE_IT_RISING_FALLING;
  default:
    stm32_it_type = GPIO_MODE_IT_RISING;
    break;
  }

  switch (pull)
  {
  case GPIO_NO_PULL:
    stm32_pull = GPIO_NOPULL;
    break;
  case GPIO_PULL_UP:
    stm32_pull = GPIO_PULLUP;
    break;
  case GPIO_PULL_DOWN:
    stm32_pull = GPIO_PULLDOWN;
    break;
  default:
    stm32_pull = GPIO_NOPULL;
    break;
  }

  switch (speed)
  {
  case GPIO_SPEED_LO:
    stm32_speed = GPIO_SPEED_FREQ_LOW;
    break;
  case GPIO_SPEED_MED:
    stm32_speed = GPIO_SPEED_FREQ_MEDIUM;
    break;
  case GPIO_SPEED_HI:
    stm32_speed = GPIO_SPEED_FREQ_HIGH;
    break;
  default:
    stm32_speed = GPIO_SPEED_FREQ_LOW;
    break;
  }

  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = stm32_it_type;
  GPIO_InitStruct.Pull = stm32_pull;
  GPIO_InitStruct.Speed = stm32_speed;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

