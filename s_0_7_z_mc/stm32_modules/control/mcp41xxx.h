/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-09-28
 * 
 * @brief Single/Dual Digital Potentiometer with SPI™ Interface MCP41xxx
 * @link https://www.alldatasheet.com/datasheet-pdf/pdf/552926/MICROCHIP/MCP41010.html
 *  电阻电位器,通过SPI控制寄存器,输出对应的电阻值,电阻值被分为256个刻度
 * ***********************************************************
 */

#ifndef _MCP41XXX_H_
#define _MCP41XXX_H_
#include "hw_interface\spi\spi_if.h"
#include "hw_interface\gpio\gpio_if.h"

typedef enum _tag_mcp_type_
{
  MCP_TYPE_41010, // max resistance 10K
  MCP_TYPE_41050, // max resistance 50K
  MCP_TYPE_41100,  // max resistance 100K
  MCP_TYPE_END
} Mcp_type;

class Mcp41xxx
{
public:
  Mcp41xxx(Spi_if *_spi, Gpio_if *_cs, Mcp_type _type = MCP_TYPE_41100);
  ~Mcp41xxx();
  bool set_wiper_res(float res);
  bool set_max_res(float res);
  bool set_output_res(float res);
  bool set_output_res_by_step(unsigned char step);

private:
  bool write_data_reg(unsigned char val);
  Mcp_type type;
  Spi_if *spi;
  Gpio_if *cs;
  float wiper_res[MCP_TYPE_END];
  float max_res[MCP_TYPE_END];
};

#endif // _MCP41XXX_H_
