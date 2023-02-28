/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      双循环buffer类
*
***********************************************************/

#ifndef _DOUBLE_BUFFER_
#define _DOUBLE_BUFFER_
#include "circular_buffer.h"

class Double_buffer
{
public:
  Double_buffer(unsigned int buff_size);
  ~Double_buffer();

  bool write(unsigned char data);
  bool write(unsigned char *data, unsigned int data_len);

  unsigned int read_out(unsigned char* data, unsigned int len);
  unsigned int read_all(unsigned char* data);

  unsigned int buffer_used(void);
  unsigned int buffer_free_size(void);
  unsigned int buffer_size(void);

  void buffer_switch(void);
  void buffer_reset(void);
  
private:
  Circular_buffer* in_buffer;
  Circular_buffer* out_buffer;
  Circular_buffer* buffer1;
  Circular_buffer* buffer2;

};


#endif // _DOUBLE_BUFFER_
