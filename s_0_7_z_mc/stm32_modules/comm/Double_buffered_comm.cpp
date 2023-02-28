#include "double_buffered_comm.h"

Double_buffered_comm::Double_buffered_comm(unsigned int buff_size)
{
  data_buffer = new Double_buffer(buff_size);
  idle_buff_switch_is_open = true;
}

Double_buffered_comm::~Double_buffered_comm()
{
  if(data_buffer)
  {
    delete data_buffer;
  }
}

unsigned int Double_buffered_comm::data_available(void)
{
  return data_buffer->buffer_used();
}

unsigned int Double_buffered_comm::buffer_size(void)
{
  return data_buffer->buffer_size();
}

unsigned int Double_buffered_comm::buffer_free_size(void)
{
  return data_buffer->buffer_free_size();
}

void Double_buffered_comm::buffer_switch(void)
{
   data_buffer->buffer_switch();
}

void Double_buffered_comm::set_idle_buffer_switch(bool is_open)
{
  idle_buff_switch_is_open = is_open;
}
