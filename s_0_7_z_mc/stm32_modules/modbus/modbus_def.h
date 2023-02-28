#ifndef _MODBUS_DEF_H_
#define _MODBUS_DEF_H_

//Modbus commands
enum Modbus_cmd
{
  READ_DO = 1,
  READ_DI,
  READ_AO,
  READ_AI,
  WRITE_DO,
  WRITE_AO,
};
#endif
