/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      CRC 16bit MODBUS calculate interface
*
***********************************************************/

#ifndef _CRC16_MODBUS_H_
#define _CRC16_MODBUS_H_
#include "crc16_if.h"

class Crc16_modbus : public Crc16_if
{
public:
  virtual unsigned short calc(unsigned char *data, int data_len)
  {
    if(data_len <= 0)
    {
      return 0;
    }

    unsigned int i, j;
    unsigned short crc = 0xffff;

    for (i = 0; i < data_len; i++)
    {
      crc ^= (unsigned short)(data[i]);
      for (j = 0; j < 8; j++)
      {
        if (crc & 1)
        {
          crc >>= 1;
          crc ^= 0xa001;
        }
        else
        {
          crc >>= 1;
        }
      }
    }
    return crc;
  }

  virtual ~Crc16_modbus(){};
};

#endif // _CRC16_MODBUS_H_
