/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author     DFS Technology Department
*
* @brief      sub-g 433 wireless data receiver
*
***********************************************************/

#ifndef _WL433_DATA_TRANCEIVER_
#define _WL433_DATA_TRANCEIVER_

#include "data_tranceiver_if.h"
#include "cmt2300a_app.h"
#include "modules_def.h"
//#include "board_init.h"


class Wl433_data_tranceiver : public Data_tranceiver_if
{
public:
  Wl433_data_tranceiver(Cmt2300a_app* _wl433, unsigned int buffer_size);
  ~Wl433_data_tranceiver();
  virtual unsigned int get_data(unsigned char *data);
  virtual bool send_data(unsigned char* data, unsigned int data_len);
private:
  unsigned char* buffer;
  Cmt2300a_app* wl433;
  bool send_ok;
  bool recv_ok;
};

#endif // _WL433_DATA_TRANCEIVER_
