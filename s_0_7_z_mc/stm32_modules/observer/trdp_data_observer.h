/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      trdp upload data observer interface
*
* 版本:
* V1.0 2019-05-31 初始程序编写 
***********************************************************/

#ifndef _TRDP_DATA_OBSERVER_H_
#define _TRDP_DATA_OBSERVER_H_

#include <stdbool.h>
#include "trdp_data.h"

class Trdp_data_observer
{
public:
  virtual void update(Trdp_upload_data_t* data, unsigned char opt = 0) = 0;
};

#endif // _TRDP_DATA_OBSERVER_H_
