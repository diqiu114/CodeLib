#include "mcp41xxx.h"
#include <stdlib.h>

#define TPY_WIPER_RES_10K (73)
#define TPY_WIPER_RES_50K (175)
#define TPY_WIPER_RES_100K (175)

#define TAPS (256)

/**
 * @brief Construct a new Mcp 4 1xxx:: Mcp 4 1xxx object
 * 
 * @param _spi spi interface pointer
 * @param _type mcp chip type @ref Mcp_type
 */
Mcp41xxx::Mcp41xxx(Spi_if *_spi, Gpio_if *_cs, Mcp_type _type)
{
  type = _type;
  spi = _spi;
  cs = _cs;
  wiper_res[MCP_TYPE_41010] = TPY_WIPER_RES_10K;
  wiper_res[MCP_TYPE_41050] = TPY_WIPER_RES_50K;
  wiper_res[MCP_TYPE_41100] = TPY_WIPER_RES_100K;
  
  max_res[MCP_TYPE_41010] = 10000;
  max_res[MCP_TYPE_41050] = 50000;
  max_res[MCP_TYPE_41100] = 100000;
}

/**
 * @brief Destroy the Mcp 4 1xxx:: Mcp 4 1xxx object
 * 
 */
Mcp41xxx::~Mcp41xxx()
{
  if (spi != NULL)
  {
    delete spi;
    spi = NULL;
  }
}

/**
 * @brief set current wipper resistance
 *  wipper resistance - The resistance of the analog switch 
 *    that connects the Wiper Terminal to the Resistor Ladder 
 * 
 * @param res wiper resistance value
 * @return true set ok
 * @return false set failed
 */
bool Mcp41xxx::set_wiper_res(float res)
{
  if (res > 0)
  {
    wiper_res[type] = res;
    return true;
  }
  else
  {
    return false;
  }
}

bool Mcp41xxx::set_max_res(float res)
{
  max_res[type] = res;
  return true;
}

/**
 * @brief 设置输出电阻值, 如果设置的值不能被整除时, 输出最接近的值.
 *        例如: 10K量程, 设置输出4.5K, 计算输出为4.492K
 * 
 * @param res output resitance
 * @return true set ok
 * @return false set failed
 */
bool Mcp41xxx::set_output_res(float res)
{
  if(res < 0)
  {
    return false;
  }

  if(res > wiper_res[type])
  {
    res = res - wiper_res[type];
  }
  else
  {
    res = 0;
  }

  if (res > max_res[type])
  {
    res = max_res[type];
  }
  
  short step = res * TAPS / max_res[type];
  step = step > 0 ? step : 0;
  
  return write_data_reg(step);

}

/**
 * @brief 按照step设置输出电阻, 从0~255
 * 
 * @param step output step
 * @return true set ok
 * @return false set failed
 */
bool Mcp41xxx::set_output_res_by_step(unsigned char step)
{
  return write_data_reg(step);
}

/**
 * @brief set step value to data register
 * 
 * @param val step, from 0-255
 * @return true set ok
 * @return false set failed
 */
bool Mcp41xxx::write_data_reg(unsigned char val)
{
  bool ret = false;
  unsigned char data[2] = {0x11, ~val};
  
  cs->set_low();
  ret = spi->send(data, sizeof(data));
  cs->set_hi();
  
  return ret;
}
