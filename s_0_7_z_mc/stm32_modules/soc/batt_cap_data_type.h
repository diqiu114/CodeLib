/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      电池容量相关类型
***********************************************************/

#ifndef _BATT_CAP_DATA_TYPE_H_
#define _BATT_CAP_DATA_TYPE_H_

typedef bool (*cap_store) (float cap_rate);
typedef bool (*init_flag_store) (bool flag);

class Batt_info
{
public:
  Batt_info()
  {
    volt = 0;
    cur = 0;
    temp = 0;
  };
  Batt_info(float _volt, float _cur, float _temp = 20.0f)
  {
    volt = _volt;
    cur = _cur;
    temp = _temp;
  }

  float volt;
  float cur;
  float temp;
};

#endif // _BATT_CAP_DATA_TYPE_H_
