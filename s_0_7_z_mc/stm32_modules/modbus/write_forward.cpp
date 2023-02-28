#include "write_forward.h"

Write_forward::Write_forward(Modbus_master* handle, map<unsigned short, Modbus_data>* addr_table)
{
  hcomm = handle;
  reg_device_table = addr_table;
}

bool Write_forward::write_process(unsigned short addr, unsigned short val)
{
  map<unsigned short, Modbus_data>::iterator iter;

  iter = reg_device_table->find(addr);

  if( iter != reg_device_table->end() )
  {
    return hcomm->write_reg(&iter->second, val);
  } 
  else
  {
    return false;
  }
}

Write_forward::~Write_forward()
{

}
