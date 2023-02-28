/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      CRC 8bit sum calculate 
*
***********************************************************/

#ifndef _CRC8_SUM_H_
#define _CRC8_SUM_H_
#include "crc8_if.h"

class Crc8_sum : public Crc8_if
{
public:
  Crc8_sum(bool _reverse = false)
  {
    reverse = _reverse;
  }
  virtual unsigned char calc(unsigned char *data, int data_len)
  {
    if(data_len <= 0)
    {
      return 0;
    }

    unsigned char ret = 0;

    for(int i=0; i<data_len; i++)
    {
      ret += data[i];
    }

    if(reverse)
    {
      ret = ~ret;
    }
    
    return ret;
  }

  virtual ~Crc8_sum(){};
  private:
    bool reverse;
};

#endif // _CRC8_SUM_H_
