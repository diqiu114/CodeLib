#include "rs485_data_tranceiver.h"

Rs485_data_tranceiver::Rs485_data_tranceiver(RS485 *_comm)
{
  comm = _comm;
}

Rs485_data_tranceiver::~Rs485_data_tranceiver()
{
}

unsigned int Rs485_data_tranceiver::get_data(unsigned char *data)
{
  unsigned int ret = 0;
  unsigned int data_len = comm->data_available();
  if( data_len > 0 )
  {
    ret = comm->read_all(data);
  }
  return ret;
}

bool Rs485_data_tranceiver::send_data(unsigned char *data, unsigned int data_len)
{
  return comm->send(data, data_len);
}
