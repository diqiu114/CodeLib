#include "stm32_spi.h"

Stm32_spi::Stm32_spi(SPI_HandleTypeDef *_spi, unsigned int _tx_timeout)
{
  hspi = _spi;
  tx_timeout = _tx_timeout;
}

Stm32_spi::~Stm32_spi()
{
}

bool Stm32_spi::receive(unsigned char *data, unsigned int data_len)
{
  return (HAL_SPI_Receive(hspi, data, data_len, tx_timeout) == HAL_OK);
}

bool Stm32_spi::send(unsigned char *data, unsigned int data_len)
{
  return (HAL_SPI_Transmit(hspi, data, data_len, tx_timeout) == HAL_OK);
}

bool Stm32_spi::send_receive(unsigned char *tx_data, unsigned char *rx_data, unsigned int data_len)
{
  return (HAL_SPI_TransmitReceive(hspi, tx_data, rx_data, data_len, tx_timeout) == HAL_OK);
}
