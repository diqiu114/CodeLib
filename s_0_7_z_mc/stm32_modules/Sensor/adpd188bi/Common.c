
#include "Common.h"
#include "i2c.h"

ADI_HAL_STATUS_t ADPD_I2C_Transmit(uint8_t *pTxData, uint16_t Size)
{
    return (ADI_HAL_STATUS_t)HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)(0x64 << 1),
                                           (uint8_t *)pTxData, Size, 100);
}


ADI_HAL_STATUS_t ADPD_I2C_TxRx(uint8_t *reg_addr, uint8_t *pRxData,
                                    uint16_t RxSize)
{
    HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)(0x64 << 1),reg_addr, 1, 100);
    return (ADI_HAL_STATUS_t)HAL_I2C_Master_Receive(&hi2c2, (uint16_t)(0x64 << 1),
                                          pRxData, RxSize, 100);
}

void MCU_HAL_Delay(uint32_t delay)
{
  volatile uint32_t d = delay * 10;
  while(d--);
}

unsigned int PORT_TICKS_GET_COUNT(void)
{
  return HAL_GetTick();
}
