/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-06-04
 * 
 * @brief spi flash interafce
 * 
 * ***********************************************************
 */

#ifndef _SPI_FALSH_IF_H_
#define _SPI_FALSH_IF_H_

class Spi_flash_if
{
public:
  virtual bool read_bytes(unsigned int addr, unsigned char *data, unsigned int data_len) = 0;
  virtual bool write_bytes(unsigned int addr, unsigned char *data, unsigned int data_len) = 0;
  virtual bool erase(unsigned int addr) = 0;

  virtual ~Spi_flash_if(){};
};

#endif // _SPI_FALSH_IF_H_
