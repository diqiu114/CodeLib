/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      广州众志诚以太网卡类
*
* 版本:
* V1.1 2019-04-26 1. 修改类从Uart_tranceiver继承
*                 2. 避免send()函数与基类冲突，修改为send_data()
* V1.0 2018-10-04 初始程序编写
***********************************************************/

#ifndef _ETH_MODULE_H_
#define _ETH_MODULE_H_

#include "stdbool.h"
#include "comm/Double_buffered_comm.h"
#include "eth_module_proto.h"
#include "modules_def.h"
#include "hw_interface/gpio/gpio_if.h"
#include "defines.h"

#define ETH_MODULE_RET_TIMEOUT_MAX    ( 1000 )

#define ETH_MODULE_CFG_DATA_BYTES  ( (unsigned short)(83) )
#define ETH_MODULE_CFG_PACK_BYTES  ( ETH_MODULE_CFG_DATA_BYTES +  ETH_MP_HEADER_BYTES + ETH_MP_CMD_BYTES + ETH_MP_CRC_BYTES )
#define ETH_MODULE_NON_DATA_BYTES ( ETH_MP_HEADER_BYTES + ETH_MP_DATA_LEN_BYTES + ETH_MP_CRC_BYTES + ETH_MP_CMD_BYTES )

#define ETH_MODULE_CMD_CFG   ( 0x05 )
#define ETH_MODULE_CMD_DEST1 ( 0x31 )  // send data to dest ip1 
#define ETH_MODULE_CMD_DEST2 ( 0x32 )  // send data to dest ip2
#define ETH_MODULE_CFG_SUC   ( 0x06 )
#define ETH_MODULE_CFG_FAIL  ( 0x05 )

#define ETH_MODULE_MODE_CLIENT     ( 0x32 )
#define ETH_MODULE_MODE_UDP        ( 0xC2 )
// data index
#define ETH_MODULE_IP_IDX         ( 10 )
#define ETH_MODULE_GATEWAY_IDX    ( 14 )
#define ETH_MODULE_MASK_IDX       ( 18 )
#define ETH_MODULE_MODE_IDX       ( 69 )
#define ETH_MODULE_DEST_IP1_IDX   ( 70 )
#define ETH_MODULE_DEST_PORT1_IDX ( 74 )
#define ETH_MODULE_SRC_PORT1_IDX  ( 76 )
#define ETH_MODULE_DEST_IP2_IDX   ( 78 )
#define ETH_MODULE_DEST_PORT2_IDX ( 82 )
#define ETH_MODULE_SRC_PORT2_IDX  ( 84 )
#define ETH_MODULE_CFG_RESULT_IDX ( 0 )

#define ETH_MODE_TCP      (1)
#define ETH_MODE_UDP      (2)
// #define ETH_SEND_BUFFER_SIZE          ( 600 )

#if (USE_ETH_GENERAL && !USE_NEW_ETH_BOARD)
typedef struct  _tag_eth_cfg_
{
  Ip ip;
  Ip gateway;
  Ip mask;
  Ip dest_ip1;
  unsigned char dest_port1[2];
  unsigned char src_port1[2];
  Ip dest_ip2;
  unsigned char dest_port2[2];
  unsigned char src_port2[2];
}Eth_Module_Cfg;
#elif (ETH_SINGLE_MODULE && !USE_NEW_ETH_BOARD)
#include "single_trdp_module.h"
typedef struct  _tag_eth_cfg_
{
  Trdp_single_para_t trdp_paras;
}Eth_Module_Cfg;
#else 
#include "eth_board.h"
typedef struct  _tag_eth_cfg_
{
  Trdp_eth_para_t trdp_paras;
}Eth_Module_Cfg;
#endif

typedef struct _tag_eth_data_
{
  unsigned char cmd;
  unsigned char* data;
  unsigned short data_cnt;
}Eth_Data;

extern Eth_Module_Cfg Eth_default_cfg;

class Eth_module
{
public:
  Eth_module(Double_buffered_comm * _comm);
  bool reset(void);
  void set_rst_pin(Gpio_if *_gpio);
  bool config(Eth_Module_Cfg* cfg,char mode = ETH_MODE_TCP);
  bool send_data(Eth_Data* s_data);
  bool receive(Eth_Data* r_data, unsigned int timeout);
  Double_buffered_comm* tranceiver(void);
  bool get_data(Eth_Data* r_data);
  
  virtual ~Eth_module();

private:
  bool received_data(int timeout);

  Protocol* eth_module_proto;
  Gpio_if* rst_pin_port;
  unsigned short rst_pin;

  // unsigned char Pack[ETH_SEND_BUFFER_SIZE];
  // unsigned char Data[ETH_SEND_BUFFER_SIZE];
};



#endif // _ETH_H_
