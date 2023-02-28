/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      CRC 8bit calculate for sensirion sensor
*
***********************************************************/

#ifndef _CRC8_SENSIRION_H_
#define _CRC8_SENSIRION_H_
#include "crc8_if.h"

class Crc8_sensirion : public Crc8_if
{
public:
  Crc8_sensirion(unsigned char _init_val = 0xFF, unsigned char _polynomial = 0x31)
  {
    init_val = _init_val;
    polynomial = _polynomial;
  }

  virtual unsigned char calc(unsigned char *data, int data_len)
  {
    if (data_len <= 0)
    {
      return 0;
    }

    unsigned char crc = init_val;
    unsigned char crc_bit;

    /* calculates 8-Bit checksum with given polynomial */
    for (int i = 0; i < data_len; ++i)
    {
      crc ^= (data[i]);
      for (crc_bit = 8; crc_bit > 0; --crc_bit)
      {
        if (crc & 0x80)
          crc = (crc << 1) ^ polynomial;
        else
          crc = (crc << 1);
      }
    }
    return crc;
  }

  virtual ~Crc8_sensirion(){};

private:
  unsigned char init_val;
  unsigned char polynomial;
};

#endif // _CRC8_SENSIRION_H_
