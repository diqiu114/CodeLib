/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池自放电修正
***********************************************************/

#ifndef _SELF_DISCHARGE_H_
#define _SELF_DISCHARGE_H_

#define SECONDS_IN_MONTH ((float)(30 * 24 * 60 * 60))
#define SECONDS_TO_MONTH(x) ((x) / SECONDS_IN_MONTH)
// atleast 10 days storage
#define TS_DIFF_MIN (SECONDS_IN_MONTH / 3)

class Self_discharge
{
public:
  Self_discharge(float _nomial_cap, float _discharge_rate_per_month);
  ~Self_discharge();

  float get_cap(float cur_cap, float ts_diff);

private:
  float nomial_cap;
  float dishcarge_rate;
};

#endif // _SELF_DISCHARGE_H_
