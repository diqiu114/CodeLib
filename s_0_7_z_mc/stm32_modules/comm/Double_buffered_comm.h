/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      带双buffer的通讯类
*             polling 模式发送， 中断模式接收
*
***********************************************************/

#ifndef _DOUBLE_BUFFERED_COMM_H_
#define _DOUBLE_BUFFERED_COMM_H_

#include "stdbool.h"
#include "buffer\double_buffer.h"

class Double_buffered_comm
{
public:
  Double_buffered_comm(unsigned int buff_size);
  virtual ~Double_buffered_comm();

  virtual bool send(unsigned char *data, unsigned int data_len) = 0;
  virtual unsigned int read(unsigned char *data, unsigned int data_len) = 0;
  virtual unsigned int read_all(unsigned char *data) = 0;

  virtual bool rev_data_handle(unsigned char *data = NULL, unsigned int data_len = 0) = 0;

  unsigned int data_available(void);
  unsigned int buffer_size(void);
  unsigned int buffer_free_size(void);
  void buffer_switch(void); 
  void set_idle_buffer_switch(bool is_open = true);
protected:
  Double_buffer *data_buffer;
  bool idle_buff_switch_is_open;
};

#endif // _DOUBLE_BUFFERED_COMM_H_
