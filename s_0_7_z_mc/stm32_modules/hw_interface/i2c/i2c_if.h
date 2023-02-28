/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      I2C interface
*
***********************************************************/

#ifndef _I2C_IF_H_
#define _I2C_IF_H_

#include <stdbool.h>

class I2c_if
{
public:
  virtual bool send(unsigned short dev_addr, unsigned char* data, unsigned int data_len) = 0;
  virtual bool receive(unsigned short dev_addr, unsigned char* data, unsigned int data_len) = 0;
  virtual bool mem_send(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char* data, unsigned int data_len) = 0;
  virtual bool mem_receive(unsigned short dev_addr, unsigned short reg_addr, unsigned int reg_addr_cnt, unsigned char* data, unsigned int data_len) = 0;
  virtual ~I2c_if(){};
};

#endif // _I2C_IF_H_
