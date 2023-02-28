#ifndef _SINGLE_TRDP_MODULE_H_
#define _SINGLE_TRDP_MODULE_H_
#include "trdp_module.h"
#include "stdlib.h"

#define TRDP_MODULE_SINGLE_PHY_CNT (1)
#define BMS_TRDP_ETH_CNT (4)
#define CCU_TRDP_ETH_CNT (2)
#define CFG_SINGLE_SUCCESS             (0x01)


typedef struct _tag_single_trdp_bms_
{
  Ip eth_ip;
  Ip eth_gateway;
  Ip eth_mask;
  unsigned short com_id;
} Trdp_single_bms_t;

typedef struct _tag_single_trdp_ccu_
{
  Ip ip;
  unsigned short com_id;
} Trdp_single_ccu_t;

typedef struct _tag_single_trdp_para_
{
  Ip grp_addr_ip;
  unsigned short grp_port;
  Ip upgrade_ip;
  unsigned short upgrade_port;
  Trdp_single_bms_t bms[BMS_TRDP_ETH_CNT];
  Trdp_single_ccu_t ccu[CCU_TRDP_ETH_CNT];
} Trdp_single_para_t;
class Trdp_single_module :public Trdp_module
{
public:
  Trdp_single_module();
  Trdp_single_module(Double_buffered_comm *handle ,int train_num);
  bool set_para(Trdp_single_para_t *trdp_paras);
  unsigned short proto_buff_fill(unsigned char eth_num, unsigned char* data, unsigned int data_len,unsigned char* buff);
  virtual bool reset(void);
  virtual void set_rst_pin(Gpio_if * _gpio);
  virtual bool config(void);
  virtual bool send_pd(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  virtual unsigned int rev_pd(unsigned char* data, unsigned int data_len = 0);
  virtual ~Trdp_single_module();

private:
  unsigned char *cfg_buff_fill(unsigned char eth_num);
  unsigned char *send_pd_buff_fill(unsigned char eth_num, unsigned char* data, unsigned int buff_len);
  bool cfg_rsp_ok(unsigned char eth_num);
  bool received_data(int timeout);
  int Train_num_idx;
  Trdp_module_data module_data;
  Double_buffered_comm *uart;
  Trdp_single_para_t *paras;
  Protocol *trdp_proto;
  Eth_module_proto *eth_proto;
  Gpio_if *rst_gpio;
};
#endif
