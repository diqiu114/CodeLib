#include "modbus_id.h"
#include "class_init.h"

Modbus_id::Modbus_id()
{
  unsigned char id = 0;
  id = get_id_from_eeprom();
  if( id != 0 )
  {
    modbus_id = id;
  }
  else
  {
    set_id(DEFAULT_ID);
//    modbus_id = DEFAULT_ID;
  }
}

bool Modbus_id::set_id(char id)
{
  unsigned short tmp = id;
  if( Eeprom_data_store->write(EA_DEV_ID, &tmp, 1) )
  {
    modbus_id = id;
    return true;
  }
  else
  {
    return false;
  }
}

char Modbus_id::get_id(void)
{
	return modbus_id;
}

char Modbus_id::get_id_from_eeprom(void)
{
  char ret = 0;
  unsigned short tmp = 0;
  if( Eeprom_data_store->read(EA_DEV_ID, &tmp, 1) )
  {
    ret = tmp;
  }
  
  return ret;
}
Modbus_id::~Modbus_id()
{

}
