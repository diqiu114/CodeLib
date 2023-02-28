/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief         Ramtron FM25W256(256Kbit) spi driver
* datasheet link https://pdf1.alldatasheet.com/datasheet-pdf/view/151112/ETC1/FM25W256.html
*
***********************************************************/

#ifndef _FM25W256_H_
#define _FM25W256_H_
#include "..\..\hw_interface\spi\spi_if.h"
#include "..\..\hw_interface\gpio\gpio_if.h"
#include "spi_flash_if.h"
// #include "modules_def.h"
#include <stdbool.h>

#define FM25W256_ID_LEN (3)
#define FM25W256_ERASE_SIZE (1024)

class Fm25w256 : public Spi_flash_if
{
public:
  Fm25w256(Spi_if *_spi, Gpio_if *_spi_nss);
  virtual ~Fm25w256();
  virtual bool read_bytes(unsigned int addr, unsigned char *data, unsigned int data_len);
  virtual bool write_bytes(unsigned int addr, unsigned char *data, unsigned int data_len);
  virtual bool erase(unsigned int addr);

private:
  unsigned char spi_read_write(unsigned char data);
  Spi_if *spi;
  Gpio_if *spi_nss;
};

#endif
