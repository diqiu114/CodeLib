/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      stm32 uart 实现
*
***********************************************************/

#ifndef _STM32_UART_H_
#define _STM32_UART_H_

#include "comm\double_buffered_comm.h"
#include "main.h"


// milliseconds
#define DEFAULT_TIME_OUT (0x1FF)

typedef void (*uart_idle_callback) (UART_HandleTypeDef* uart_handle);

class Stm32_uart : public Double_buffered_comm
{
public:
  Stm32_uart(UART_HandleTypeDef* uart_handle, unsigned int buff_size, uart_idle_callback callback = NULL, unsigned int _timeout = DEFAULT_TIME_OUT);
  virtual ~Stm32_uart();
  
  virtual bool send(unsigned char* data, unsigned int data_len);
  virtual unsigned int read(unsigned char* data, unsigned int data_len); 
  virtual unsigned int read_all(unsigned char *data);

  virtual bool rev_data_handle(unsigned char *data = NULL, unsigned int data_len = 0);
  
  void idle_handle(void);

  virtual bool start_rev_it(void);
  virtual bool stop_rev_it(void);

private:
  UART_HandleTypeDef* handle;
  uart_idle_callback callback;
  unsigned int timeout;
  unsigned char rev_data;
};

#endif // _STM32_UART_H_
