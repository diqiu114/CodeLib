/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      以太网卡协议
*
* 版本:
* V1.0 2018-04-03 
***********************************************************/

#ifndef _ETH_MODULE_PROTO_H_
#define _ETH_MODULE_PROTO_H_

#include "Protocol.h"


// header and command
#define ETH_MP_HEADER    ( 0xFE )

#define ETH_MP_HEADER_BYTES   ( 1 )
#define ETH_MP_CMD_BYTES      ( 1 )
#define ETH_MP_DATA_LEN_BYTES ( 2 )
#define ETH_MP_CRC_BYTES      ( 2 )
#define ETH_MP_CRC_CALC_OFFSET   ( ETH_MP_HEADER_BYTES + ETH_MP_CMD_BYTES + ETH_MP_DATA_LEN_BYTES )

class Eth_module_proto : public Protocol
{
public:

  Eth_module_proto();
  virtual unsigned int pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack, bool delete_pack_buffer = true);
  virtual unsigned int unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data, unsigned int msg_fix_cnt);
  virtual unsigned int prot_len(void);
  virtual ~Eth_module_proto();
  unsigned short crc16(unsigned char* data, unsigned int len, int init_val = 0x0000);
  virtual bool delete_pack_buffer();
private:
  unsigned int pack_max_len;
  unsigned char* pack_buffer;
  int header_offset(unsigned char *pack, unsigned int pack_len);
  int offset;
};


#endif // _ETH_MODULE_PROTO_H_
