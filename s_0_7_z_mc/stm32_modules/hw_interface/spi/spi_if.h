/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      spi interface
*
***********************************************************/

#ifndef _SPI_IF_H_
#define _SPI_IF_H_

#include <stdbool.h>

class Spi_if
{
public:
  virtual bool receive(unsigned char *data, unsigned int data_len) = 0;
  virtual bool send(unsigned char *data, unsigned int data_len) = 0;
  virtual bool send_receive(unsigned char *tx_data, unsigned char* rx_data, unsigned int data_len) = 0;
  virtual ~Spi_if(){};
};

#endif // _SPI_IF_H_
