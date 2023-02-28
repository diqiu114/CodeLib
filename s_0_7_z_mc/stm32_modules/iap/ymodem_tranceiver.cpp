#include "ymodem_tranceiver.h"

Ymodem_tranceiver::Ymodem_tranceiver(Double_buffered_comm *_comm, Delay_if *_delay_ms)
{
  comm = _comm;
  delay_ms = _delay_ms;
}

Ymodem_tranceiver::~Ymodem_tranceiver()
{
}

YMODEM_STATUS Ymodem_tranceiver::receive(unsigned char *data, unsigned int data_len, unsigned int timeout)
{
  unsigned int delay = 0;
  while ((comm->data_available() == 0) && (delay < timeout) )
  {
    delay_ms->delay(1);
    delay++;
  }

  if (delay >= timeout)
  {
    return YMODEM_TIMEOUT;
  }

  unsigned int bytes_read = comm->read(data, data_len);
  if (bytes_read == data_len)
  {
    return YMODEM_OK;
  }
  else
  {
    return YMODEM_ERROR;
  }
}

YMODEM_STATUS Ymodem_tranceiver::send(unsigned char *data, unsigned int data_len, unsigned int timeout)
{
  if (comm->send(data, data_len))
  {
    return YMODEM_OK;
  }
  else
  {
    return YMODEM_TIMEOUT;
  }
}
