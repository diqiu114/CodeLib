/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      MVB网络通讯应用
*
* 版本:
* V1.0 2019-07-23 初始程序编写 
***********************************************************/

#ifndef _MVB_APP_H_
#define _MVB_APP_H_

#include "stdbool.h"
#include "mvb_module.h"
#include "rtc_ops.h"

#define TIME_SET_FLAG_IDX (3)
#define TIME_TRAIN_NUM_FLAG_IDX (3)
#define TIME_SET_AVALIBLE ( 0x08)
#define TRAIN_NUM_SET_AVALIBLE ( 0x10)
#define VITAL_ERR_DELAY (3)
#define DATE_TIME_ADDR (0x01)
#define VITAL_ADDR (0x74)

class Mvb_app
{
public:
  Mvb_app(Mvb_module *_mvb, unsigned char train_inx ,unsigned int rec_data_len);
  void set_send_frame(Mvb_data* frame);
  bool send_msg(unsigned char* data, unsigned int data_len);
  bool handle_rec_msg(unsigned short dest_addr);
  void set_rtc_handle(Rtc_ops* handle);
  bool comm_error(void);
  uint16_t get_mvb_update_buff(unsigned char *buff,uint16_t heart);
  virtual ~Mvb_app();

  Mvb_data rec_frame;

private:
  Mvb_data* send_frame; 
  Mvb_module* mvb;
  unsigned char Train_index;
  Rtc_ops* rtc;
  bool comm_err;
  unsigned int comm_err_cnt;
  unsigned short pre_vital;
};


#endif // _ETH_APPH_
