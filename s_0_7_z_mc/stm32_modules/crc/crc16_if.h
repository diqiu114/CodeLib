/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      CRC 16bit calculate interface
*
***********************************************************/

#ifndef _CRC16_IF_H_
#define _CRC16_IF_H_

class Crc16_if
{
public:
  virtual unsigned short calc(unsigned char *data, int data_len) = 0;
  virtual ~Crc16_if(){};
};

#endif // _CRC16_IF_H_
