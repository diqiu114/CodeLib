/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      battery state
*
* 版本:
* V1.0 2019-05-05 初始程序编写 
***********************************************************/

#ifndef _BATT_STATE_H_
#define _BATT_STATE_H_

#include <stdbool.h>
#include "data_type.h"

class Batt_state
{
public:
  Batt_state(Batt_state_thr_t *thr)
  {
    state = FLOAT_CHARGE;
    state_thr = thr;
  }

  Batt_state_t get_state(float cur)
  {
    if (cur > state_thr->float_to_fast_thr)
    {
      state = FAST_CHARGE;
    }
    else if (cur < state_thr->charge_to_discharge_thr)
    {
      state = DISCHARGE;
    }
    else
    {
      if (state == FAST_CHARGE )
      {
        if( cur < state_thr->fast_to_float_thr )
        {
          state = FLOAT_CHARGE;
        }
      }
      else
      {
        state = FLOAT_CHARGE;
      }

    }

    return state;
  }
  ~Batt_state(void);

private:
  Batt_state_thr_t *state_thr;
  Batt_state_t state;
};

#endif // _BATT_STATE_H_
