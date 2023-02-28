#include "kqm6600tau.h"
#include <string>

#define CRC_CALC_BYTES (3)
#define CRC_OFFSET (3)
#define INVALID_VAL (0xFF)

Kqm6600tau::Kqm6600tau(Double_buffered_comm *_comm)
{
  comm = _comm;
  tvoc = 0;
}

Kqm6600tau::~Kqm6600tau()
{
  if (comm != NULL)
  {
    delete comm;
    comm = NULL;
  }
}

bool Kqm6600tau::update(void)
{
  if (comm->data_available() < KQM_DATA_LEN)
  {
    return false;
  }

  comm->read(buffer, KQM_DATA_LEN);

  if (pack_complete())
  {
    tvoc = (buffer[1] << 8) | buffer[2];
    return true;
  }

  return false;
}

unsigned short Kqm6600tau::get_tvoc(void)
{
  return tvoc;
}

bool Kqm6600tau::pack_complete(void)
{
  bool ret = true;

  // header ok
  ret = (buffer[0] == KQM_HEADER);
  // crc ok
  ret = ret && (buffer[CRC_OFFSET] == crc8(buffer, CRC_CALC_BYTES));
  // data not equal 0xFF
  ret = ret && ((buffer[1] != INVALID_VAL) && (buffer[2] != INVALID_VAL));

  return ret;
}

unsigned char Kqm6600tau::crc8(unsigned char *data, unsigned int data_len)
{
  unsigned char ret = 0;

  for (int i = 0; i < data_len; i++)
  {
    ret += data[i];
  }

  return ret;
}
