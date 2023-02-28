#include "write_store.h"

Write_store::Write_store(Storage* es, map<unsigned short, unsigned short>* addr_table)
{
  eeprom_store = es;
  reg_addr_table = addr_table;
}

bool Write_store::write_process(unsigned short addr, unsigned short val)
{
  map<unsigned short, unsigned short>::iterator iter;
  unsigned short w_val = val;

  iter = reg_addr_table->find(addr);

  if( iter != reg_addr_table->end() )
  {
    return eeprom_store->write(iter->second, &w_val, 1);
  } 
  else
  {
    return false;
  }
}

Write_store::~Write_store()
{

}
