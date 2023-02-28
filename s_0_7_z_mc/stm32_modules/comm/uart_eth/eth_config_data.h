#ifndef __ETH_CONFIG_DATA__H__
#define __ETH_CONFIG_DATA__H__

#include "eth_define.h"

class Eth_config_data
{
public:
  Eth_config_data()
  {
    sdt_en_cmd[0][0] = 0x04;
    sdt_en_cmd[0][1] = 0x61;
    sdt_en_cmd[0][2] = 0x62;

    sdt_en_rsp[0][0] = 0x02;
    sdt_en_rsp[0][1] = 0x69;
    sdt_en_rsp[0][2] = 0x6a;

    cfg_cmd[0] = 0x05;
    cfg_rsp[0] = 0x06;
    send_pd_cmd[0] = 0x09;
    rev_pd_cmd[0] = 0x07;

    send_md_cmd[0] = 0x0a;
    rev_md_cmd[0] = 0x08;
    send_udp_trdp_cmd[0][0] = 0x11;
    send_udp_trdp_cmd[0][1] = 0x12;

    rev_udp_trdp_cmd[0][0] = 0X21;
    rev_udp_trdp_cmd[0][1] = 0X22;
    send_udp_passthrough_cmd[0] = 0x71;
    rev_udp_passthrough_cmd[0] = 0x81;

    send_tcp_passthrough_cmd[0][0] = 0x31;
    send_tcp_passthrough_cmd[0][1] = 0x32;
    rev_tcp_passthrough_cmd[0][0] = 0x41;
    rev_tcp_passthrough_cmd[0][1] = 0x42;

    master_sqe_counter[0] = 0;
    upgrade_sqe_counter[0] = 0;

#if ETH_DOUBLE_MODULE
    sdt_en_cmd[1][0] = 0x84;
    sdt_en_cmd[1][1] = 0xe1;
    sdt_en_cmd[1][2] = 0xe2;
    sdt_en_rsp[1][0] = 0x82;
    sdt_en_rsp[1][1] = 0xe9;
    sdt_en_rsp[1][2] = 0xea;

    cfg_cmd[1] = 0x85;
    cfg_rsp[1] = 0x86;
    send_pd_cmd[1] = 0x89;
    rev_pd_cmd[1] = 0x87;
    send_md_cmd[1] = 0x8a;
    rev_md_cmd[1] = 0x88;
    send_udp_trdp_cmd[1][0] = 0x91;
    send_udp_trdp_cmd[1][1] = 0x92;
    rev_udp_trdp_cmd[1][0] = 0Xa1;
    rev_udp_trdp_cmd[1][1] = 0Xa2;
    send_udp_passthrough_cmd[1] = 0x72;
    rev_udp_passthrough_cmd[1] = 0x82;
    send_tcp_passthrough_cmd[1][0] = 0xb1;
    send_tcp_passthrough_cmd[1][1] = 0xb2;
    rev_tcp_passthrough_cmd[1][0] = 0xc1;
    rev_tcp_passthrough_cmd[1][1] = 0xc2;
    master_sqe_counter[1] = 0;
    upgrade_sqe_counter[1] = 0;
#endif

    sdt_en_pack_len = 57;
    sdt_en_rsp_pack_len = 10;
    sdt_en_rsp_delay = 2000;
    cfg_pack_len = 89;
    cfg_rsp_pack_len = 8;
    cfg_rsp_delay = 2000;
    mac_opt = 0;
    if (ETH_NEED_SET_MAC_HIG)
      mac_opt |= 0x30;
    if (ETH_NEED_SET_MAC_MID)
      mac_opt |= 0x0c;
    if (ETH_NEED_SET_MAC_MIN)
      mac_opt |= 0x03;

    upgrade_conn_opt = 0;
    if (UPGRADE_COUNT)
    {
      upgrade_conn_opt |= UPGRADE_COUNT;
      if (ETH_TCP_PASSTHROUGH)
      {
        if (UPGRADE_COUNT == 1)
          upgrade_conn_opt |= 0x50;
        if (UPGRADE_COUNT == 2)
          upgrade_conn_opt |= 0xff;
      }
      else if (ETH_UDP_PASSTHROUGH)
      {
        if (UPGRADE_COUNT == 1)
          upgrade_conn_opt |= 0x4f;
        if (UPGRADE_COUNT == 2)
          upgrade_conn_opt |= 0xcf;
      }
      else if (ETH_UDP_TRDP)
      {
        upgrade_conn_opt &= 0x0f;
      }
    }

    send_pd_non_data_bytes = 20;
    pd_pack_data_idx = 25;
    pd_pack_data_len_idx = 21;

    send_md_non_data_bytes = 43;
    md_pack_data_len_idx = 41;
    md_pack_data_idx = 37;

    send_udp_trdp_non_data_bytes = 20;
    udp_trdp_pack_data_len_idx = 17;
    udp_trdp_pack_data_idx = 13;

    send_udp_passthrough_non_data_bytes = 6;
    udp_passthrough_pack_data_len_idx = 3;
    udp_passthrough_pack_data_idx = 1;

    send_tcp_passthrough_non_data_bytes = 6;
    tcp_passthrough_pack_data_len_idx = 3;
    tcp_passthrough_pack_data_idx = 1;
  }
  unsigned char sdt_en_cmd[TRDP_MODULE_ETH_PHY_CNT][SDT_MAX_COUNT];
  unsigned char sdt_en_rsp[TRDP_MODULE_ETH_PHY_CNT][SDT_MAX_COUNT];
  unsigned char cfg_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char cfg_rsp[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char send_pd_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char rev_pd_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char send_md_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char rev_md_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char send_udp_trdp_cmd[TRDP_MODULE_ETH_PHY_CNT][UPGRADE_MAX_COUNT];
  unsigned char rev_udp_trdp_cmd[TRDP_MODULE_ETH_PHY_CNT][UPGRADE_MAX_COUNT];
  unsigned char send_udp_passthrough_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char rev_udp_passthrough_cmd[TRDP_MODULE_ETH_PHY_CNT];
  unsigned char send_tcp_passthrough_cmd[TRDP_MODULE_ETH_PHY_CNT][UPGRADE_MAX_COUNT];
  unsigned char rev_tcp_passthrough_cmd[TRDP_MODULE_ETH_PHY_CNT][UPGRADE_MAX_COUNT];
  unsigned int master_sqe_counter[TRDP_MODULE_ETH_PHY_CNT];
  unsigned int upgrade_sqe_counter[TRDP_MODULE_ETH_PHY_CNT];
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
  unsigned char send_md_non_data_bytes;
  unsigned int md_pack_data_len_idx;
  unsigned int md_pack_data_idx;
  unsigned char send_udp_trdp_non_data_bytes;
  unsigned int udp_trdp_pack_data_len_idx;
  unsigned int udp_trdp_pack_data_idx;
  unsigned char send_udp_passthrough_non_data_bytes;
  unsigned int udp_passthrough_pack_data_len_idx;
  unsigned int udp_passthrough_pack_data_idx;
  unsigned char send_tcp_passthrough_non_data_bytes;
  unsigned int tcp_passthrough_pack_data_len_idx;
  unsigned int tcp_passthrough_pack_data_idx;
};
#endif
