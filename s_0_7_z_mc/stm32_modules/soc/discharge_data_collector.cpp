

#include "discharge_data_collector.h"
#include <stdlib.h>

/**
 * @brief Construct a new Discharge_data_collector::Discharge_data_collector object
 * 
 * @param _buffer_cnt buffer count,用于指定缓存多少次数据后,进行存储
 */
Discharge_data_collector::Discharge_data_collector(unsigned int _buffer_cnt)
{
  buffer_cnt = _buffer_cnt;
  buff = new Discharge_data[buffer_cnt];
  data_idx = 0;
}

/**
 * @brief Destroy the Discharge_data_collector::Discharge_data_collector object
 * 
 */
Discharge_data_collector::~Discharge_data_collector()
{
  if(buff != NULL)
  {
    delete[] buff;
  }
}

/**
 * @brief push data to buffer, when buffer full, store to the extern flash
 * 
 * @param data store data
 * @return true store ok
 * @return false store fail
 */
bool Discharge_data_collector::push_data(Discharge_data &data)
{
  if(data_idx < buffer_cnt)
  {
    buff[data_idx] = data;
  }

  data_idx++;
  if(data_idx >= buffer_cnt)
  {
    data_idx = 0;
    if(store_func != NULL)
    {
      store_func((unsigned char*)buff, buffer_cnt * sizeof(Discharge_data));
    }
  }
  
  return true;
}


/**
 * @brief set store callback
 * 
 * @param func store callback function pointer
 * @return true set ok
 * @return false set failed
 */
bool Discharge_data_collector::set_store_cb(Discharge_data_store_cb func)
{
  store_func = func;
  
  return true;
}
