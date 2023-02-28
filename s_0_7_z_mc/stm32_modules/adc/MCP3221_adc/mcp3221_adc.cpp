#include "mcp3221_adc.h"
#include "string.h"
#include "class_init.h"
#define REREAD_I2C_TIMES 3
#define I2C_OP_TIMEOUT 300

Mcp3221::Mcp3221(I2C_HandleTypeDef *_commHandle, int _Addr, int _adcVRef)
{
  commHandle = _commHandle;
  Addr = _Addr;
  adcVRef = _adcVRef;
}
bool Mcp3221::init(void)
{
  bool ret = false;
  unsigned int i2c_ret = 0;
  i2c_ret = HAL_I2C_IsDeviceReady(commHandle, (unsigned short)(Addr << 1), REREAD_I2C_TIMES,I2C_OP_TIMEOUT);
  if(i2c_ret == HAL_I2C_ERROR_NONE)
  {
    ret = true;
  }
  return ret;
}
unsigned int Mcp3221::readI2cAdc(void)
{
  unsigned short numBytes = 2;
  unsigned int result = 0;
  unsigned char data[2] = {0};
  unsigned int i2c_ret = 0;

     
  i2c_ret = HAL_I2C_Master_Receive(commHandle, (unsigned short)(Addr << 1), 
                         data, numBytes, I2C_OP_TIMEOUT);
  if(i2c_ret == HAL_I2C_ERROR_NONE)
  {  
    result = data[0] << 8 | data[1];
  }
 
  return result;
}

float Mcp3221::GetVoltage(void)
{
  float mV = 0;
  mV = (float)readI2cAdc();
//  if(mV > 4096.0f)
//  {

//  }
  mV = (mV * adcVRef / 4096);
  return mV;
}

void Mcp3221::UpdateAdcRef(int _adcVRef)
{
  adcVRef = _adcVRef;
}
