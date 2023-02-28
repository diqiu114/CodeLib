/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-06-07
 * 
 * @brief SPI Flash存储类
 * 
 * ***********************************************************
 */

#ifndef _SPI_FLASH_STORE_H_
#define _SPI_FLASH_STORE_H_

#include "crc\crc16_if.h"
#include "storage\spi_flash\spi_flash_if.h"

class Store_info
{
public:
  int addr;
  void *data;
  int data_len;
};

class Spi_flash_store
{
public:
  Spi_flash_store(Spi_flash_if *_spi_flash, Crc16_if *_crc16);
  ~Spi_flash_store();
  bool store(Store_info *info);
  bool read(Store_info *info);

private:
  Spi_flash_if *spi_flash;
  Crc16_if *crc16;
  unsigned char *buffer;
};

#endif // _SPI_FLASH_STORE_H_
