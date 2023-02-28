/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      广州众志诚MVB网卡类
*
* 版本:
* V1.1 2019-04-26 1. 修改类从Uart_tranceiver继承
*                 2. 避免send()函数与基类冲突，修改为send_data()
* V1.0 2018-11-05 初始程序编写 
***********************************************************/

#ifndef _MVB_MODULE_H_
#define _MVB_MODULE_H_

#include "stdbool.h"
#include "comm\Double_buffered_comm.h"
#include "hw_interface/gpio/gpio_if.h"
#include "mvb_module_proto.h"
#include "modules_def.h"

#define MVB_MODULE_RET_TIMEOUT_MAX    ( 1000 )
#define MVB_MODULE_CFG_RET_TIMEOUT_MAX    ( 3000 )

#define MVB_MODULE_CMD_CFG      ( 0x05 )
#define MVB_MODULE_CMD_CFG_RET  ( 0x06 )
#define MVB_MODULE_CMD_READ     ( 0x07 )
#define MVB_MODULE_CMD_READ_RET ( 0x08 )
#define MVB_MODULE_CMD_SEND     ( 0x09 )

#define MVB_MODULE_CFG_RESULT_IDX ( 2 )

#define MVB_MODULE_CFG_BYTES    ( 250 )
#define MVB_MODULE_CFG_RES_BYTES ( 88 )
#define MVB_MODULE_SEND_READ_REQ_BYTES  ( 8 )

#define MVB_MODULE_CFG_SUC      ( 0x06 )
#define MVB_MODULE_CFG_FAIL     ( 0x05 )
#define MVB_MODULE_DATA_VALID   ( 1<<7 )
#define MVB_MODULE_CH_A_OK      ( 1<<1 )
#define MVB_MODULE_CH_B_OK      ( 1<<0 )

#define MVB_MODULE_USE_INC          ( 1<<6 )
#define MVB_MODULE_INC_BIT_16       ( 1<<5 )
#define MVB_MODULE_INC_TIMEOUT_10S  ( 10 )
#define MVB_MODULE_INC_OFFSET       ( 0 )

#define MVB_MODULE_SC_ALL_CH_CORRET    ( MVB_MODULE_DATA_VALID | MVB_MODULE_CH_A_OK |  MVB_MODULE_CH_B_OK )
#define MVB_MODULE_SC_CHA_CORRET    ( MVB_MODULE_DATA_VALID | MVB_MODULE_CH_A_OK )
#define MVB_MODULE_SC_CHB_CORRET    ( MVB_MODULE_DATA_VALID | MVB_MODULE_CH_B_OK )

#define MVB_MODULE_NO_INC           (  MVB_MODULE_DATA_VALID )
#define MVB_MODULE_16BIT_INC_10S_TIMEOUT (  MVB_MODULE_DATA_VALID | MVB_MODULE_USE_INC | MVB_MODULE_INC_BIT_16 | MVB_MODULE_INC_TIMEOUT_10S)
#define MVB_MODULE_8BIT_INC_10S_TIMEOUT (  MVB_MODULE_DATA_VALID | MVB_MODULE_USE_INC | MVB_MODULE_INC_TIMEOUT_10S)

#define MVB_MODULE_DATA_LEN_2BYTES  ( 0x00 )
#define MVB_MODULE_DATA_LEN_4BYTES  ( 0x01 )
#define MVB_MODULE_DATA_LEN_8BYTES  ( 0x02 )
#define MVB_MODULE_DATA_LEN_16BYTES ( 0x03 )
#define MVB_MODULE_DATA_LEN_32BYTES ( 0x04 )

#define MVB_MODULE_PORT_PERIOD_16MS   ( 0x01 )
#define MVB_MODULE_PORT_PERIOD_32MS   ( 0x02 )
#define MVB_MODULE_PORT_PERIOD_64MS   ( 0x03 )
#define MVB_MODULE_PORT_PERIOD_128MS  ( 0x04 )
#define MVB_MODULE_PORT_PERIOD_256MS  ( 0x05 )
#define MVB_MODULE_PORT_PERIOD_512MS  ( 0x06 )
#define MVB_MODULE_PORT_PERIOD_1024MS ( 0x07 )

#define MVB_MODULE_CMD_IDX       ( 0 )
#define MVB_MODULE_SC_IDX        ( 1 )
#define MVB_MODULE_ADDR_HI_IDX   ( 2 )
#define MVB_MODULE_ADDR_LO_IDX   ( 3 )
#define MVB_MODULE_DATA_IDX      ( 4 )

typedef struct _tag_mvb_port_info_
{
  unsigned char addr[2];
  unsigned char data_len;
  unsigned char comm_period;
}MVB_Addr;

typedef enum _tag_mvb_recv_switch_info_
{
  MVB_RECV_OFF,
  MVB_RECV_ON,
}MVB_recv_switch;

typedef struct  _tag_mvb_module_cfg_
{
  unsigned short device_addr;
  unsigned char dest_port_cnt;
  MVB_Addr dest_port[8];
  unsigned char src_port_cnt;
  MVB_Addr src_port[8];
}Mvb_module_cfg;

typedef struct _tag_mvb_data_
{
  // command
  unsigned char  cmd;
  // destination addr
  unsigned short dest_addr;
  // state or control
  unsigned char  sc;
  // life signal increase offset
  unsigned char inc_offset;
  // data
  unsigned char* data;
  // data count
  unsigned short data_cnt;
}Mvb_data;

class Mvb_module 
{
public:
  Mvb_module(Double_buffered_comm* handle,unsigned char train_num);
  bool reset(void);
  void set_rst_pin(Gpio_if * _gpio);
  bool config(Mvb_module_cfg* cfg, unsigned int timeout = MVB_MODULE_CFG_RET_TIMEOUT_MAX);
  bool send_data(Mvb_data* s_data);
  bool receive(unsigned short dest_addr, unsigned int recv_period, MVB_recv_switch recv_switch, Mvb_data* r_data, unsigned int timeout = MVB_MODULE_RET_TIMEOUT_MAX);
  
  virtual ~Mvb_module();

private:
  unsigned int send_max_len;
  unsigned char *read_buff;
  unsigned char *send_buff;
  bool is_first;
  bool received_data(int timeout);
  bool send_read_req(unsigned int recv_period, MVB_recv_switch recv_switch);

  Protocol* mvb_module_proto;
   Gpio_if* rst_gpio;
  unsigned short rst_pin;
  Double_buffered_comm *usart;
  unsigned char Train_num_idx;

};


#endif // _MVB_MODULE_H_
