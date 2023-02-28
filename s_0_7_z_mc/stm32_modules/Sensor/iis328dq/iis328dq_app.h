/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ST IIS328DQ application
*
***********************************************************/
#ifndef _IIS328DQ_APP_H_
#define _IIS328DQ_APP_H_

#include <stdbool.h>
#include "iis328dq_reg.h"
#include "iis328dq_comm.h"

// 3 axis data struct
typedef union{
  short i16bit[3];
  unsigned char u8bit[6];
} axis3_bit16_t;

class Iis328dq_app
{
public:
  Iis328dq_app(iis328dq_fs_t _full_scale, iis328dq_dr_t _data_rate);
  ~Iis328dq_app();

  bool dev_found(void);
  void dev_init(void);
  bool get_acc_data(float *data);
  void set_full_scale(iis328dq_fs_t fs);


private:
  iis328dq_fs_t full_scale;
  iis328dq_dr_t data_rate;
  stmdev_ctx_t dev_ctx;
  float *acc_data;
  axis3_bit16_t acc_raw_data;
};

#endif // _IIS328DQ_APP_H_
