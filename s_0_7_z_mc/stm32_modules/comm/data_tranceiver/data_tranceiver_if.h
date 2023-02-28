/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author     DFS Technology Department
*
* @brief      Data receiver interface
*
***********************************************************/

#ifndef _DATA_TRANCEIVER_IF_
#define _DATA_TRANCEIVER_IF_

class Data_tranceiver_if
{
public:
  virtual unsigned int get_data(unsigned char *data) = 0;
  virtual bool send_data(unsigned char* data, unsigned int data_len) = 0;
};

#endif // _DATA_TRANCEIVER_IF_
