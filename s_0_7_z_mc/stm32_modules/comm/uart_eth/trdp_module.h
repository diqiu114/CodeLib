/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      广州众志诚双冗余TRDP以太网卡类
*
* 版本:
* V1.0 2018-10-04 初始版本程序编写
***********************************************************/

#ifndef _TRDP_MODULE_H_
#define _TRDP_MODULE_H_

#include "stdbool.h"
#include "comm/Double_buffered_comm.h"
#include "eth_module_proto.h"
#include "modules_def.h"
#include "hw_interface\gpio\gpio_if.h"


#define TRDP_MODULE_ETH_PHY_CNT (2)
#define TRDP_ETH_CNT (2)

#define CFG_SUCCESS             (0x11)

typedef struct _tag_trdp_bms_
{
  unsigned char mac[6];
  Ip eth_ip;
  Ip eth_gateway;
  Ip eth_mask;
  unsigned short com_id;
} Trdp_bms_t;

typedef struct _tag_trdp_ccu_
{
  Ip ip;
  unsigned short com_id;
} Trdp_ccu_t;

typedef struct _tag_trdp_para_
{
  Ip grp_addr_ip[TRDP_ETH_CNT];
  unsigned short grp_port;
  Ip upgrade_ip;
  unsigned short upgrade_port;
  unsigned int ccu_smi;
  unsigned int bms_smi;
  Trdp_bms_t bms[TRDP_ETH_CNT];
  Trdp_ccu_t ccu[TRDP_ETH_CNT];
} Trdp_para_t;

class Trdp_module_data
{
public:
  Trdp_module_data();
  unsigned char sdt_en_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char sdt_en_rsp[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char cfg_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char cfg_rsp[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char send_pd_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char rev_pd_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned int sqe_counter[TRDP_MODULE_ETH_PHY_CNT];
  unsigned short sdt_en_pack_len;
  unsigned short sdt_en_rsp_pack_len;
  unsigned short sdt_en_rsp_delay;
  unsigned short cfg_pack_len;
  unsigned short cfg_rsp_pack_len;
  unsigned short cfg_rsp_delay;
  unsigned char mac_opt;
  unsigned char upgrade_conn_opt;
  unsigned char send_pd_non_data_bytes;
  unsigned int pd_pack_data_len_idx;
  unsigned int pd_pack_data_idx;
};

class Trdp_module
{
public:
  Trdp_module();
  Trdp_module(Double_buffered_comm *handle ,int train_num);
  bool set_para(Trdp_para_t *trdp_paras);
  virtual bool reset(void);
  virtual void set_rst_pin(Gpio_if * _gpio);
  virtual bool sdt_enable(void);
  virtual bool config(void);
  virtual bool send_pd(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  virtual unsigned int rev_pd(unsigned char* data, unsigned int data_len = 0);
  // #if( USE_FREE_RTOS )
  //   void set_queue_handle(QueueHandle_t handle);
  // #endif

  virtual ~Trdp_module();

private:
  unsigned char *sdt_buff_fill(unsigned char eth_num);
  bool sdt_rsp_ok(unsigned char eth_num);
  unsigned char *cfg_buff_fill(unsigned char eth_num);
  unsigned char *send_pd_buff_fill(unsigned char eth_num, unsigned char* data, unsigned int buff_len);

  bool cfg_rsp_ok(unsigned char eth_num);
  bool received_data(int timeout);
  int Train_num_idx;
  // #if( USE_FREE_RTOS )
  //   QueueHandle_t queue;
  // #endif

  Trdp_module_data module_data;
  Double_buffered_comm *uart;
  Trdp_para_t *paras;
  Protocol *trdp_proto;
  Gpio_if *rst_gpio;
};

#endif // _TRDP_MODULE_H_
