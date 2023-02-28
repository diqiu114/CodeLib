/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author     DFS Technology Department
*
* @brief      sub-g 433 wireless data receiver
*
***********************************************************/

#ifndef _RS485_433_DATA_TRANCEIVER_
#define _RS485_433_DATA_TRANCEIVER_

#include "data_tranceiver_if.h"
#include "rs485.h"

class Rs485_data_tranceiver : public Data_tranceiver_if
{
public:
  Rs485_data_tranceiver(RS485* _comm);
  ~Rs485_data_tranceiver();
  virtual unsigned int get_data(unsigned char *data);
  virtual bool send_data(unsigned char* data, unsigned int data_len);
private:
  RS485* comm;
};

#endif // _RS485_433_DATA_TRANCEIVER_
