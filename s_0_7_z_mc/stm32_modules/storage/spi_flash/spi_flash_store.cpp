#include "spi_flash_store.h"
#include <stdlib.h>
#include <string.h>

Spi_flash_store::Spi_flash_store(Spi_flash_if *_spi_flash, Crc16_if *_crc16)
{
  spi_flash = _spi_flash;
  crc16 = _crc16;
}

Spi_flash_store::~Spi_flash_store()
{
  if (spi_flash != NULL)
  {
    delete spi_flash;
    spi_flash = NULL;
  }

  if (crc16 != NULL)
  {
    delete crc16;
    crc16 = NULL;
  }
}

bool Spi_flash_store::store(Store_info *info)
{
  if (info == NULL)
  {
    return false;
  }
  bool ret = false;

  int store_len = info->data_len + sizeof(unsigned short);
  buffer = new unsigned char[store_len];
  if (buffer == NULL)
  {
    return false;
  }

  memset(buffer, 0, store_len);

  short crc = crc16->calc((unsigned char *)info->data, info->data_len);

  memcpy(buffer, info->data, info->data_len);
  memcpy(&buffer[info->data_len], (char *)&crc, sizeof(crc));

  if (spi_flash->write_bytes(info->addr, buffer, store_len))
  {
    ret = true;
  }

  delete buffer;
  buffer = NULL;

  return ret;
}

bool Spi_flash_store::read(Store_info *info)
{
  if (info == NULL)
  {
    return false;
  }

  bool ret = false;
  int read_len = info->data_len + sizeof(short);

  buffer = new unsigned char[read_len];
  if (buffer == NULL)
  {
    return false;
  }

  memset(buffer, 0, read_len);

  if (spi_flash->read_bytes(info->addr, buffer, read_len))
  {
    short crc = crc16->calc(buffer, info->data_len);
    if (memcmp((char *)&crc, &buffer[info->data_len], sizeof(crc)) == 0)
    {
      memcpy(info->data, buffer, info->data_len);
      ret = true;
    }
  }

  delete buffer;
  buffer = NULL;

  return ret;
}
