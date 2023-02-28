/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author     DFS Technology Department
*
* @brief      Ymodemn program upgrade data receiver
*
***********************************************************/

#ifndef _YMODEM_TRANCEIVER_
#define _YMODEM_TRANCEIVER_

#include "iap\ymodem_trancerver_if.h"
#include "comm\Double_buffered_comm.h"
#include "delay\delay_if.h"

class Ymodem_tranceiver : public Ymodem_tranceiver_if
{
public:
  Ymodem_tranceiver(Double_buffered_comm* _comm, Delay_if* _delay_ms);
  virtual ~Ymodem_tranceiver();

  virtual YMODEM_STATUS receive(unsigned char *data, unsigned int data_len, unsigned int timeout);
  virtual YMODEM_STATUS send(unsigned char *data, unsigned int data_len, unsigned int timeout);

private:
  Double_buffered_comm* comm;
  Delay_if* delay_ms;
};

#endif // _YMODEM_TRANCEIVER_
