/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      modbus register bank
*
***********************************************************/

#ifndef _MODBUS_REG_BANK_H_
#define _MODBUS_REG_BANK_H_

#include <list>

// modbus address configuration
// DO addr from 0~09999
// DI addr from 10000~19999
// AI addr from 30000~39999
// AO addr from 40000~49999

#define MODBUS_DO_REG_ADDR_START (0)
#define MODBUS_DO_REG_ADDR_END (9999)
#define MODBUS_DI_REG_ADDR_START (10000)
#define MODBUS_DI_REG_ADDR_END (19999)
#define MODBUS_AI_REG_ADDR_START (30000)
#define MODBUS_AI_REG_ADDR_END (39999)
#define MODBUS_AO_REG_ADDR_START (40000)
#define MODBUS_AO_REG_ADDR_END (49999)

using namespace std;

class Modbus_digi_reg
{
public:
  Modbus_digi_reg(unsigned short _addr, unsigned char _val)
  {
    addr = _addr;
    val = _val;
  };

  unsigned short addr;
  unsigned char val;
};

class Modbus_analog_reg
{
public:
  Modbus_analog_reg(unsigned short _addr, short _val)
  {
    addr = _addr;
    val = _val;
  };

  unsigned short addr;
  short val;
};

class Modbus_reg_bank
{
public:
  Modbus_reg_bank();
  ~Modbus_reg_bank();

  bool add_analog_reg(unsigned short addr, short val = 0);
  bool add_analog_reg(Modbus_analog_reg &reg);

  bool add_digi_reg(unsigned short addr, char val = 0);
  bool add_digi_reg(Modbus_digi_reg &reg);

  char get_digi_reg_val(unsigned short addr);
  short get_analog_reg_val(unsigned short addr);

  bool set_analog_reg_val(unsigned short addr, short val);
  bool set_digi_reg_val(unsigned short addr, unsigned short val);

private:
  list<Modbus_digi_reg> digi_reg;
  list<Modbus_analog_reg> analog_reg;
};

#endif // _MODBUS_REG_BANK_H_
