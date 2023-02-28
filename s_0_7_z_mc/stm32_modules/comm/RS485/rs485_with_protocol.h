/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      带协议的RS485收发类
*
* 版本:
* V1.0 2019-06-21 初始程序编写 
***********************************************************/

#ifndef _RS485_WITH_PROTOCOL_H_
#define _RS485_WITH_PROTOCOL_H_

#include "stdbool.h"
#include "rs485.h"
#include "protocol\protocol.h"

class Rs485_with_protocol : public RS485
{
public:
  Rs485_with_protocol(UART_HandleTypeDef* uart_handle, unsigned int buff_size, Gpio_if *ctrl_pin, uart_idle_callback callback = NULL);
  virtual ~Rs485_with_protocol();
  
  void set_protocol(Protocol* prot);
  bool send_data(unsigned char* data, unsigned int len);
  unsigned int read_data(unsigned char* data);

  

private:
  Protocol* prot;
  unsigned char* data_buffer;
};

#endif // _RS485_WITH_PROTOCOL_H_
