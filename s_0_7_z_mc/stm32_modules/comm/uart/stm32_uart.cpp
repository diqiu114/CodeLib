#include "stm32_uart.h"
#include "string.h"

Stm32_uart::Stm32_uart(UART_HandleTypeDef *uart_handle, unsigned int buff_size, uart_idle_callback uart_callback, unsigned int _timeout)
    : Double_buffered_comm(buff_size)
{
  handle = uart_handle;
  callback = uart_callback;
  timeout = _timeout;
}

Stm32_uart::~Stm32_uart()
{
}

bool Stm32_uart::send(unsigned char *data, unsigned int data_len)
{
  if ((data == NULL) || (data_len == 0))
  {
    return false;
  }

  bool ret = false;

  data_buffer->buffer_reset();

  stop_rev_it();

  if (HAL_UART_Transmit(handle, data, data_len, timeout) == HAL_OK)
  {
    ret = true;
  }

  start_rev_it();

  return ret;
}

unsigned int Stm32_uart::read(unsigned char *data, unsigned int data_len)
{
  unsigned int read_data_len = data_len >= data_buffer->buffer_used() ? data_buffer->buffer_used() : data_len;
  return data_buffer->read_out(data, read_data_len);
}

unsigned int Stm32_uart::read_all(unsigned char *data)
{
  return data_buffer->read_all(data);
}

bool Stm32_uart::start_rev_it(void)
{
  return (HAL_UART_Receive_IT(handle, &rev_data, sizeof(rev_data)) == HAL_OK);
}

bool Stm32_uart::stop_rev_it(void)
{
  return (HAL_UART_AbortReceive_IT(handle) == HAL_OK);
}

/**
 * rev_data_handle  uart received data(RXNE) interrupt handle
 *                  call in HAL_UART_RxCpltCallback function
 * @return TODO
 */
bool enter_recv_handle = false;
bool Stm32_uart::rev_data_handle(unsigned char *data, unsigned int data_len)
{
  unsigned int remain_cnt = data_buffer->buffer_free_size();
  enter_recv_handle = true;
  if (remain_cnt == 0)
  {
    data_buffer->buffer_switch();
    if (callback)
    {
      callback(handle);
    }
  }

  bool ret = data_buffer->write(&rev_data, sizeof(rev_data));

  start_rev_it();

  return ret;
}

/**
 * idle_handle  usart idle interrup handle 
 *              call in void USARTx_IRQHandler(void),
 *              before function HAL_UART_IRQHandler(&huartx);
 * @return TODO
 */
void Stm32_uart::idle_handle(void)
{
  if (__HAL_UART_GET_FLAG(handle, UART_FLAG_IDLE) != RESET)
  {
    __HAL_UART_CLEAR_IDLEFLAG(handle);

    if(idle_buff_switch_is_open && enter_recv_handle)
    {
      data_buffer->buffer_switch();
    }
    if (callback && enter_recv_handle)
    {
      callback(handle);
    }
  }
  enter_recv_handle = false;
}
