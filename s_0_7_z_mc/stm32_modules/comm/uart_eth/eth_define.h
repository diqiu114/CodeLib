/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      以太网模块数据定义

***********************************************************/

#ifndef _ETH_DEFINE_H_
#define _ETH_DEFINE_H_

#include "proj_eth_define.h"

#if ETH_SINGLE_MODULE 
#define ETH_DOUBLE_MODULE (0)
#else
#define ETH_DOUBLE_MODULE (1)
#endif

#define IPV4 (4)
#define MAX_RECV_COMMID_CNT (4)
#define MAX_MASTER_GROUP_IP_CNT (2)
#define MAX_UPGRADE_IP_MAX    (2)
#define MAX_RECV_SMI_CNT      (6)
#define MASTER_SDT_INDEX (0)
#define UPGRADE1_SDT_INDEX (1)
#define UPGRADE2_SDT_INDEX (2)
#define CONSISTID_COUNT (16)

#if ETH_DOUBLE_MODULE
#define TRDP_MODULE_ETH_PHY_CNT (2)
#define CFG_SUCCESS (0x11)
#elif ETH_SINGLE_MODULE
#define TRDP_MODULE_ETH_PHY_CNT (1)
#define CFG_SUCCESS (0x01)
#endif
#define SDT_MAX_COUNT (3)
#define UPGRADE_MAX_COUNT (2)
typedef unsigned char Ip[IPV4];

typedef struct _tag_bms_
{
  Ip eth_ip;
  Ip eth_gateway;
  Ip eth_mask;
  Ip eth_ttdb;
  unsigned short ttdb_port;
  unsigned char mac_hig[2];
  unsigned char mac_mid[2];
  unsigned char mac_min[2];
  Ip eth_dns;
  unsigned short dns_port;
  unsigned int bms_smi;
  unsigned short bms_commid;
  Ip eth_mast_group_ip[MAX_MASTER_GROUP_IP_CNT];
  unsigned short eth_mast_group_port[MAX_MASTER_GROUP_IP_CNT];  
  Ip eth_recv_group_ip;
  unsigned short eth_recv_group_port;
  Ip upgrade_ip[MAX_UPGRADE_IP_MAX];
  unsigned short dest_port[MAX_UPGRADE_IP_MAX];
  unsigned short src_port[MAX_UPGRADE_IP_MAX];
  unsigned int recv_commid[MAX_RECV_COMMID_CNT];
  unsigned int recv_smi[MAX_RECV_SMI_CNT];
  unsigned char consistid[CONSISTID_COUNT];
} Bms_t;

typedef struct _tag_trdp_eth_para_
{
  unsigned char main_version;
  unsigned char sub_version;
  unsigned short protol_version;
  unsigned int md_wait_time;
  Bms_t bms[TRDP_MODULE_ETH_PHY_CNT];
} Trdp_eth_para_t;

typedef unsigned int (*Proto_fill_template_func)(unsigned char eth_num, unsigned char *original_data, unsigned int original_len, unsigned char *pack_data);

#endif
