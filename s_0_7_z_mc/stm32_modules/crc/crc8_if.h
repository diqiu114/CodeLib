/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      CRC 8bit calculate interface
*
***********************************************************/

#ifndef _CRC8_IF_H_
#define _CRC8_IF_H_

class Crc8_if
{
public:
  virtual unsigned char calc(unsigned char *data, int data_len) = 0;
  virtual ~Crc8_if(){};
};

#endif // _CRC8_IF_H_
