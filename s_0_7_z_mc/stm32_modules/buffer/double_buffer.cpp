#include "double_buffer.h"

Double_buffer::Double_buffer(unsigned int buff_size)
{
  buffer1 = new Circular_buffer(buff_size);
  buffer2 = new Circular_buffer(buff_size);

  in_buffer = buffer1;
  out_buffer = buffer2;
}

Double_buffer::~Double_buffer()
{
  delete buffer1;
  delete buffer2;
}

bool Double_buffer::write(unsigned char data)
{
  return write(&data, sizeof(data));
}

bool Double_buffer::write(unsigned char *data, unsigned int data_len)
{
  if ((data == NULL) || (data_len > in_buffer->get_size()))
  {
    return false;
  }

  if (in_buffer->write(data, data_len) != 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * Read_out read N data from read out buffer
 * @param buffer receive data pointer 
 * @param len read out data length
 * @return actual read out length 
 */
unsigned int Double_buffer::read_out(unsigned char *buffer, unsigned int len)
{
  return out_buffer->read(buffer, len);
}

/**
 * Read_all read all data from read out buffer
 * @param buffer recieve data buffer pointer
 * @return actual read out length 
 */
unsigned int Double_buffer::read_all(unsigned char *buffer)
{
  unsigned int read_cnt = out_buffer->get_full();

  return out_buffer->read(buffer, read_cnt);
}

unsigned int Double_buffer::buffer_used(void)
{
  return out_buffer->get_full();
}

unsigned int Double_buffer::buffer_free_size(void)
{
  return in_buffer->get_free();
}

unsigned int Double_buffer::buffer_size(void)
{
  return out_buffer->get_size();
}

/**
 * buffer_switch  swap in/out buffer
 * @return TODO
 */
void Double_buffer::buffer_switch(void)
{
  if (in_buffer == buffer1)
  {
    in_buffer = buffer2;
    out_buffer = buffer1;

    in_buffer->reset();
  }
  else
  {
    in_buffer = buffer1;
    out_buffer = buffer2;

    in_buffer->reset();
  }
}

void Double_buffer::buffer_reset(void)
{
  in_buffer->reset();
}
