/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      放电电池数据收集类,用于定时收集放电的数据.
***********************************************************/

#ifndef _DISCHARGE_DATA_COLLECTOR_
#define _DISCHARGE_DATA_COLLECTOR_
#include "batt_cap_data_type.h"

typedef struct _tag_discharge_data_
{
  unsigned int ts;
  float volt;
  float cur;
  float temp;
  float soc;
}Discharge_data;

typedef bool (*Discharge_data_store_cb)(unsigned char *data, unsigned int data_len);

class Discharge_data_collector
{
public:
  Discharge_data_collector(unsigned int _buffer_cnt);
  ~Discharge_data_collector();
  bool push_data(Discharge_data &data);
  bool set_store_cb(Discharge_data_store_cb func);
private:
  unsigned int buffer_cnt;
  Discharge_data *buff;
  Discharge_data_store_cb store_func;
  unsigned int data_idx;

};

#endif // _DISCHARGE_DATA_COLLECTOR_
