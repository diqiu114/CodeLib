/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      battery data subject类
*
* 版本:
* V1.0 2019-05-05 初始程序编写 
***********************************************************/

#ifndef _BATT_DATA_H_
#define _BATT_DATA_H_

#include <stdbool.h>
#include "data_type.h"
#include "batt_state.h"
#include "batt_data_subject.h"
#include "soc\batt_cap.h"

class Batt_data : public Batt_data_subject
{
public:
  Batt_data(void);
  virtual void set_data(Batt_data_t* data, bool update = true);
  virtual void set_state_handle(Batt_state* batt_state);
  virtual void set_soc_handle(Batt_cap* batt_cap);
  virtual ~Batt_data(void);

protected:
  Batt_state* state;
  Batt_cap* cap;
};

#endif // _BATT_DATA_H_
