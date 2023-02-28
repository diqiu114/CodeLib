#include "rs485.h"

RS485::  RS485(UART_HandleTypeDef *uart_handle, unsigned int buff_size, Gpio_if *ctrl_pin , GPIO_STATUES ctrl_pin_status,uart_idle_callback callback)
: Stm32_uart(uart_handle, buff_size, callback)
{
  set_idle_buffer_switch(true);
  tx_pin_state = ctrl_pin_status;
  tr_pin = ctrl_pin;
}

RS485::~RS485()
{
  if(tr_pin != NULL)
  {
    delete tr_pin;
    tr_pin = NULL;
  }
  
}

void RS485::set_tx_pin_state(GPIO_STATUES pin_state)
{
  tx_pin_state = pin_state;
}

bool RS485::start_rev_it(void)
{
  rx_mode();
  return Stm32_uart::start_rev_it();
}

bool RS485::stop_rev_it(void)
{
  tx_mode();
  return Stm32_uart::stop_rev_it();
}

void RS485::tx_mode(void)
{
  if(tx_pin_state == GPIO_HI )
  {
    tr_pin->set_hi();
  }
  else
  {
    tr_pin->set_low();
  }
}

void RS485::rx_mode(void)
{
  if(tx_pin_state == GPIO_HI )
  {
    tr_pin->set_low();
  }
  else
  {
    tr_pin->set_hi();
  }
}
