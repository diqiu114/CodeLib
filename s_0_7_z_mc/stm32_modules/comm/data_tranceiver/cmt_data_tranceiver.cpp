#include "cmt_data_tranceiver.h"

Cmt_data_tranceiver::Cmt_data_tranceiver(Cmt2300a_tranceiver *_wl433)
{
  wl433 = _wl433;
}

Cmt_data_tranceiver::~Cmt_data_tranceiver()
{
}

unsigned int Cmt_data_tranceiver::get_data(unsigned char *data)
{
  return wl433->read_all(data);
}

bool Cmt_data_tranceiver::send_data(unsigned char *data, unsigned int data_len)
{
  return wl433->send(data, data_len);
}
