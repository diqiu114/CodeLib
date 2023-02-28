/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      Solo Wen dfs_ww@163.com
*
* @brief      车辆以太网通讯应用
*
* 版本:
* V1.0 2018-11-04 初始版本编写 Solo Wen
***********************************************************/

#ifndef _ETH_APP_H_
#define _ETH_APP_H_

#include "stdbool.h"
#include "proj_eth_proto.h"
#include "eth_module.h"
#include "rtc_ops.h"

#define ETH_APP_TRAIN_NUM     ( 5 )
#define ETH_APP_TRAIN_TYPE    ( 10 )
#define ETH_SOUR1_NUM     ( 160  )
#define ETH_HOST1_NUM     ( 40 )
#define ETH_SOUR2_NUM     ( 161  )
#define ETH_HOST2_NUM     ( 41 )
#define ETH_MSG_TYPE          (16020)
#ifdef __cplusplus
extern "C" {
#endif

// #define TRAIN_ETH_RET_TIMEOUT_MAX     ( 1000 )

#define ETH_APP_TRAIN_MSG_LEN         ( 50 )
#define ETH_APP_RETRY_TIMES_MAX       ( 3 )
#define ETH_APP_TRAIN_RET_TIME_MAX    ( 1000 )
#define ETH_APP_TRAIN_STATUS_RET_TIME_MAX    ( 1000 )

typedef struct _tag_train_msg_
{
  //sour device num
  unsigned char sour;
  //dest device num
  unsigned char host;
  //message type
  unsigned short msg_type;
  // meesage heart
  unsigned short vital;
  // line number
  unsigned short line;
  //train type
  unsigned short train_type;
  //Train marshalling number
  unsigned int group;
  //train carriage num
  unsigned char carriage;  
  // protocol version
  unsigned char proto_ver;
  // destination device id( 1 or 2)
  unsigned char dest_dev_id;  
  // data length
  unsigned int data_len;
  
}Train_Msg;

class Eth_app
{
public:
  Eth_app(Eth_module* _eth, unsigned int buffer_size);
  bool init(Eth_Module_Cfg* cfg, char mode = ETH_MODE_TCP);
  bool send_msg(unsigned char* data, unsigned int data_cnt);
  void init_defualt_value(unsigned char idx);
  void set_rtc_handle(Rtc_ops* handle);
  Train_Msg train_msg;
  void rev_handle();
  unsigned char sour_dev_num[2];
  unsigned char host_dev_num[2];
  virtual ~Eth_app();

private:
  unsigned int fill_buffer(unsigned char* data, unsigned int data_cnt, unsigned char* buffer);
  void eth_module_rst(void);
  Rtc_ops* rtc;

  Eth_Data eth_module_send_data;
  Eth_Data eth_module_rev_data;
  Protocol* train_eth_proto;
  Eth_module* eth;
};


#ifdef __cplusplus
}
#endif

#endif // _ETH_APP_H_
