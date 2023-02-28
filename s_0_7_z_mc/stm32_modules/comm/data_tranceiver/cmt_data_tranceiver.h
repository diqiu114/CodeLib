/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author     DFS Technology Department
*
* @brief      sub-g 433 wireless data receiver
*
***********************************************************/

#ifndef _CMT_DATA_TRANCEIVER_
#define _CMT_DATA_TRANCEIVER_

#include "data_tranceiver_if.h"
#include "comm\wireless\cmt2300a\cmt2300a_tranceiver.h"

class Cmt_data_tranceiver : public Data_tranceiver_if
{
public:
  Cmt_data_tranceiver(Cmt2300a_tranceiver* _wl433);
  ~Cmt_data_tranceiver();
  virtual unsigned int get_data(unsigned char *data);
  virtual bool send_data(unsigned char* data, unsigned int data_len);
private:
  Cmt2300a_tranceiver* wl433;
};

#endif // _CMT_DATA_TRANCEIVER_
