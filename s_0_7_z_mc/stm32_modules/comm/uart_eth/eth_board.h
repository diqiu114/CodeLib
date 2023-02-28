/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      以太网模块

***********************************************************/
#ifndef _ETH_BOARD_H_
#define _ETH_BOARD_H_
#include "eth_module_if.h"
#include "eth_module_proto.h"
#include "double_buffered_comm.h"

class Eth_board : public ETH_Module_if
{
public:
  Eth_board(Double_buffered_comm *handle, Gpio_if *_gpio, int train_num, Trdp_eth_para_t *_paras);
  virtual bool init();
  virtual bool send_data(unsigned char eth_num, unsigned char *send_buff, unsigned int send_len);
  virtual unsigned int recieve_data(unsigned char *data, unsigned int data_len = 0);
  virtual bool set_para(Trdp_eth_para_t *_trdp_para);
  virtual bool set_recv_queue(QueueHandle_t *recv_queue);

  unsigned int trdp_rx_handle(unsigned char *data);
  bool trdp_pd_tx_handle(unsigned char eth_num, uint32_t commid,unsigned char *data, unsigned int data_len);
#if ETH_NEED_SET_USE_PROTO
  bool set_user_proto_handle_func(Proto_fill_template_func _func);
#endif
  bool delete_recv_buff();
  bool delete_send_buff();
  virtual ~Eth_board();
    
private:
  bool is_firs;
  unsigned char *send_buffer;
  unsigned char *recv_buffer;
  unsigned int recv_max_len;
  unsigned int send_max_len;
  Eth_config_data module_data;
  int Train_num_idx;
  Double_buffered_comm *uart;
  Trdp_eth_para_t *paras;
  Protocol *trdp_proto;
  Gpio_if *rst_gpio;
  QueueHandle_t *Eth_comm_queue;
  Proto_fill_template_func user_proto_fill_func;
  bool reset(void);
  bool config(void);
  unsigned char *cfg_buff_fill(unsigned char eth_num);
  bool cfg_rsp_ok(unsigned char eth_num);
  bool received_data(int timeout);

  
#if (ETH_NEED_SET_MASTER_SDT || ETH_NEED_SET_UPGRADE_SDT)
  bool sdt_enable(void);
  unsigned char *sdt_buff_fill(unsigned char eth_num, unsigned char sdt_index);
  bool sdt_rsp_ok(unsigned char eth_num, unsigned char sdt_index);
#endif

#if (ETH_USE_PD)
  bool send_pd(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  
  unsigned int rev_pd(unsigned char *data, unsigned int data_len = 0);
  unsigned char *send_pd_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len);
  unsigned char *send_pd_buff_fill(unsigned char eth_num, uint32_t commid,unsigned char *data, unsigned int buff_len);
#endif

#if (ETH_USE_MD)
  bool send_md(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  unsigned int rev_md(unsigned char *data, unsigned int data_len = 0);
  unsigned char *send_md_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len, Ip ccu_ip);
#endif

#if (ETH_UDP_TRDP)
  unsigned char *send_udp_trdp_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len, unsigned upgrade_index);
  bool send_udp_trdp(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  unsigned int rev_udp_trdp(unsigned char *data, unsigned int data_len = 0);
#endif

#if (ETH_UDP_PASSTHROUGH)
  unsigned char *send_udp_passthrough_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len);
  bool send_udp_passthrough(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  unsigned int rev_udp_passthrough(unsigned char *data, unsigned int data_len = 0);
#endif

#if (ETH_TCP_PASSTHROUGH)
  unsigned char *send_tcp_passthrough_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len, unsigned upgrade_index);
  bool send_tcp_passthrough(unsigned char eth_num, unsigned char *data, unsigned int data_len);
  unsigned int rev_tcp_passthrough(unsigned char *data, unsigned int data_len = 0);
#endif
};
#endif
