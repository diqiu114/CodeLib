/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      stm32 spi 实现
*
***********************************************************/

#ifndef _STM32_SPI_H_
#define _STM32_SPI_H_

#include "spi_if.h"
#include "main.h"

#define STM32_SPI_TX_TIMEOUT (1000)

class Stm32_spi : public Spi_if
{
public:
  Stm32_spi(SPI_HandleTypeDef *_spi, unsigned int _tx_timeout = STM32_SPI_TX_TIMEOUT);
  virtual ~Stm32_spi();

  virtual bool receive(unsigned char *data, unsigned int data_len);
  virtual bool send(unsigned char *data, unsigned int data_len);
  virtual bool send_receive(unsigned char *tx_data, unsigned char *rx_data, unsigned int data_len);

private:
  SPI_HandleTypeDef *hspi;
  unsigned int tx_timeout;
};

#endif // _STM32_SPI_H_
