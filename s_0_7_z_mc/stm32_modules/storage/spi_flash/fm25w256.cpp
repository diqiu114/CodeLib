#include "fm25w256.h"
#include <stdlib.h>

// command
#define WRITE 0x02 // Write to Memory instruction
#define WRSR 0x01  // Write Status Register instruction
#define WREN 0x06  // Write enable instruction
#define READ 0x03  // Read from Memory instruction
#define RDSR 0x05  // Read Status Register instruction
#define DUMMY_BYTE 0xA5

Fm25w256::Fm25w256(Spi_if *_spi, Gpio_if *_spi_nss)
{
  spi = _spi;
  spi_nss = _spi_nss;
}

Fm25w256::~Fm25w256()
{
  if (spi != NULL)
  {
    delete spi;
    spi = NULL;
  }

  if (spi_nss != NULL)
  {
    delete spi_nss;
    spi_nss = NULL;
  }
}

bool Fm25w256::read_bytes(unsigned int addr, unsigned char *data, unsigned int data_len)
{
  // Select the FLASH: Chip Select low
  spi_nss->set_low();
  unsigned char erase_value = 0xff;
  unsigned int erase_value_cnt = 0;
  unsigned int zero_value_cnt = 0;
  unsigned int read_cnt = data_len;
  // Send "Read from Memory " instruction
  spi_read_write(READ);

  // Send addr
  spi_read_write((addr & 0xFF00) >> 8);
  spi_read_write(addr & 0xFF);

  // read data
  while (read_cnt--)
  {
    *data = spi_read_write(DUMMY_BYTE);
    if(*data == erase_value)
    {
      erase_value_cnt++;
    }
    if(*data == 0)
    {
      zero_value_cnt++;
    }
    data++;
  }

  spi_nss->set_hi();

  if(data_len == erase_value_cnt || data_len == zero_value_cnt)
  {
    return false; 
  }
  
  return true;
}

bool Fm25w256::write_bytes(unsigned int addr, unsigned char *data, unsigned int data_len)
{
  // Select the FLASH: Chip Select low
  spi_nss->set_low();

  // Enable the write access to the FLASH
  spi_read_write(WREN);

  spi_nss->set_hi();

  spi_nss->set_low();

  // Send "Write to Memory " instruction
  spi_read_write(WRITE);

  // Send addr high nibble address byte to write to
  spi_read_write((addr & 0xFF00) >> 8);

  // Send addr low nibble address byte to write to
  spi_read_write(addr);

  // send write data
  while (data_len--)
  {
    spi_read_write(*data);
    data++;
  }

  spi_nss->set_hi();

  // TODO: read back to check if write successful
  return true;
}

bool Fm25w256::erase(unsigned int addr)
{
  // Select the FLASH: Chip Select low
  spi_nss->set_low();

  // Enable the write access to the FLASH
  spi_read_write(WREN);

  spi_nss->set_hi();

  spi_nss->set_low();

  // Send "Write to Memory " instruction
  spi_read_write(WRITE);

  // Send addr high nibble address byte to write to
  spi_read_write((addr & 0xFF00) >> 8);

  // Send addr low nibble address byte to write to
  spi_read_write(addr);

  unsigned int data_len = FM25W256_ERASE_SIZE;
  // send write data
  while (data_len--)
  {
    spi_read_write(0xFF);
  }

  spi_nss->set_hi();

  // TODO: read back to check if write successful
  return true;
}

unsigned char Fm25w256::spi_read_write(unsigned char data)
{
  unsigned char ret = 0;

  spi->send_receive(&data, &ret, 1);

  return ret;
}
