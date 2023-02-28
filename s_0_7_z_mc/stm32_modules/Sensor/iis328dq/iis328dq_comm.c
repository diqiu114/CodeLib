#include "iis328dq_comm.h"
#include "main.h"

#if (USE_SPI)
#include "spi.h"
void *comm_handle = &hspi3;
#define SPI_CS_PORT (SPI3_NSS_GPIO_Port)
#define SPI_CS_PIN (SPI3_NSS_Pin)
#else
#include "i2c.h"
#include "iis328dq_reg.h"
void *comm_handle = &hi2c1;
#endif

int stm32_write_regs(void *handle, unsigned char Reg, unsigned char *Bufp, unsigned short len)
{
#if (USE_I2C)
  if (handle == comm_handle)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x80;
    HAL_I2C_Mem_Write(comm_handle, IIS328DQ_I2C_ADD_H, Reg,
                      I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
  }
#elif (USE_SPI)
  if (handle == comm_handle)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x40;
    HAL_GPIO_WritePin(SPI_CS_PORT, SPI_CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(comm_handle, &Reg, 1, 1000);
    HAL_SPI_Transmit(comm_handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(SPI_CS_PORT, SPI_CS_PIN, GPIO_PIN_SET);
  }
#endif
  return 0;
}

int stm32_read_regs(void *handle, unsigned char Reg, unsigned char *Bufp, unsigned short len)
{
#if (USE_I2C)
  if (handle == comm_handle)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x80;
    HAL_I2C_Mem_Read(comm_handle, IIS328DQ_I2C_ADD_H, Reg,
                     I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
  }
#elif (USE_SPI)
  if (handle == comm_handle)
  {
    unsigned char dummy = 0xff;
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0xC0;
    HAL_GPIO_WritePin(SPI_CS_PORT, SPI_CS_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SPI_CS_PORT, SPI_CS_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_SPI_Transmit(comm_handle, &Reg, 1, 1000);
//    HAL_SPI_Receive(comm_handle, Bufp, len, 1000);
    HAL_SPI_TransmitReceive(comm_handle, &dummy, Bufp, len, 1000); 
    HAL_GPIO_WritePin(SPI_CS_PORT, SPI_CS_PIN, GPIO_PIN_SET);
  }
#endif
  return 0;
}
