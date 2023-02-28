/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      RS485类
*
* 版本:
* V1.0 2018-11-06 初始程序编写 
***********************************************************/

#ifndef _RS485_H_
#define _RS485_H_

#include "stdbool.h"
#include "comm\uart\stm32_uart.h"
#include "hw_interface\gpio\gpio_if.h"

class RS485 : public Stm32_uart
{
public:
  RS485(UART_HandleTypeDef *uart_handle, unsigned int buff_size, Gpio_if *ctrl_pin,  GPIO_STATUES ctrl_pin_status = GPIO_HI,  uart_idle_callback callback = NULL);
  void set_tx_pin_state(GPIO_STATUES pin_state);

  virtual bool start_rev_it(void);
  virtual bool stop_rev_it(void);

  virtual ~RS485();

private:
  void tx_mode(void);
  void rx_mode(void);
  Gpio_if *tr_pin;
  GPIO_STATUES tx_pin_state;
};

#endif // _RS485_CLASS_H_
