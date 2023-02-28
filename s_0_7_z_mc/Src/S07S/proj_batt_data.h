/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      project battery data
*
* 版本:
* V1.0 2019-06-20 初始程序编写 
***********************************************************/

#ifndef _PROJ_BATT_DATA_H_
#define _PROJ_BATT_DATA_H_


#include <stdbool.h>
#include "batt_data.h"

#define CELL_TEMP_RATE (10.00f)

class Proj_batt_data : public Batt_data
{
public:
  Proj_batt_data(void);
  virtual void set_data(Batt_data_t* data, bool update = true);
  float avg_temp(Batt_data_t * data, unsigned int temp_cnt);

  virtual ~Proj_batt_data(void);
private:
  Batt_info cap_para;
  bool is_zero(Cell_data_t &cell_data, unsigned int cnt);

};

#endif // _PROJ_BATT_DATA_H_
