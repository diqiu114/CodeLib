/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      trdp application
*
* 版本:
* V1.0 2019-06-02 初始程序编写 
***********************************************************/

#ifndef _TRDP_APP_H_
#define _TRDP_APP_H_

#include <stdbool.h>
#include "data_type.h"
#include "trdp_module.h"
#include "trdp_data.h"
#include "rtc_ops.h"

#define TRDP_REV_PACK_CNT (26)
#define TRDP_CRC_CALC_BYTES (9)
#define TRDP_CRC_IDX (10)
#define TRDP_TIME_START_IDX (3)
#define TRDP_TIME_SET_IDX (9)
#define TRDP_TIME_SET_BIT (0)
#define TRDP_REV_BUFF_SIZE (30)
#define TRDP_SEND_BUFF_SIZE (60)
#define TRDP_SET_TIME_DELAY_MAX (10)

class Trdp_app
{
public:
  Trdp_app();
  Trdp_app(Trdp_module *module, Trdp_data* data);
  void process(void);
  void set_rtc_handle(Rtc_ops* rtc);
  ~Trdp_app();
  void app_send_pd(void);

private:
  Trdp_module *trdp;
  Trdp_data * trdp_data;
  Rtc_ops* rtc;
  Rtc_t date_time;
  unsigned int set_time_delay;
  unsigned char *rev_buff;
  unsigned char *send_buff;
  unsigned char crc8(unsigned char *buff, int buff_len);
};

#endif // _TRDP_APP_H_
