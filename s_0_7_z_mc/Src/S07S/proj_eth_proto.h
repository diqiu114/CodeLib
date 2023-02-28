/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      武汉5以太网协议
*
* 版本:
* V1.0 2018-04-03 初始版本程序编写 
***********************************************************/

#ifndef _PROJ_ETH_PROTO_H_
#define _PROJ_ETH_PROTO_H_

#include "stdbool.h"
#include "protocol.h"

#define PROJ_ETH_HEAD1           ( 0x2C )
#define PROJ_ETH_HEAD2           ( 0x01 )
#define PROJ_ETH_LEN_IDX         ( 0x2 )
#define PROJ_ETH_HEAD_BYTES      ( 0x2 )
#define PROJ_ETH_LEN_BYTES       ( 2 )
#define PROJ_ETH_CRC_BYTES       ( 2 )

class Proj_eth_proto : public Protocol
{
public:

  Proj_eth_proto();
  virtual unsigned int pack(unsigned char* data, unsigned int data_cnt, unsigned char* pack, bool delete_pack_buffer = true);
  virtual unsigned int unpack(unsigned char* pack, unsigned int pack_cnt, unsigned char* data, unsigned int msg_fix_cnt = 0);
  virtual unsigned int prot_len(void);
  virtual ~Proj_eth_proto();
private:
  unsigned short Modbus_CRC16(unsigned char *Buff_addr,unsigned short len);
  bool pack_complelte(unsigned char* pack, unsigned int len);
};


#endif // _PROJ_ETH_PROTO_H_
