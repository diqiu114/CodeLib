/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      microchip mcp3221 application. mcp3221 is a 12 bit high speed ADC
* datasheet link:
*https://ww1.microchip.com/downloads/en/DeviceDoc/20001732E.pdf
***********************************************************/
#ifndef _MCPP3221_ADC_H_
#define _MCPP3221_ADC_H_

#include <stdbool.h>
#include "i2c.h"
class Mcp3221
{
  public:
  Mcp3221(I2C_HandleTypeDef *_commHandle, int _Addr, int _adcVRef);
  ~Mcp3221();
  float GetVoltage(void);
  void UpdateAdcRef(int _adcVRef);
  bool init(void);
  private:
    unsigned int readI2cAdc();
    int Addr;
    int adcVRef;
    I2C_HandleTypeDef *commHandle;
};
#endif // _MCP3221_ADC_H_
