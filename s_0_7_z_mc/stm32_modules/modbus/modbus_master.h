/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      Modbus master类
*             用于主机modbus应用 
*
* 版本:
* V1.0 2018-11-30 初始版本程序编写 
***********************************************************/
#ifndef _MODBUS_MASTER_H_
#define _MODBUS_MASTER_H_

#include <stdint.h>
#include "comm/Double_buffered_comm.h"
#include "modules_def.h"
#include "modbus_def.h"

#define RTU     0x01
#define ASCII   0x02

#define MODBUS_ID_IDX       ( 0 )
#define MODBUS_CMD_IDX      ( 1 )
#define MODBUS_RET_DATA_CNT ( 2 )
#define MODBUS_RET_DATA_IDX ( 3 )
#define MODBUS_CRC_BYTES    ( 2 )

#define MODBUS_MASTER_SEND_BUFF_SIZE   ( 56 )
#define MODBUS_MASTER_RECV_BUFF_SIZE   ( 200 )

typedef struct _tag_modbus_data_
{
  unsigned char id;
  unsigned char cmd;
  unsigned short reg_addr;
  unsigned short reg_cnt;
}Modbus_data;

class Modbus_master
{
  public:
    Modbus_master(Double_buffered_comm * handle, unsigned int timeout,unsigned char _retry = 1);
    unsigned int read_reg(Modbus_data* reg_info, unsigned short* rev_buff);
    bool write_reg(Modbus_data* reg_info, unsigned short reg_data);
    void set_rev_timeout(unsigned int timeout);
    bool received_data(unsigned int timeout);
    Double_buffered_comm* modbus_master;
    ~Modbus_master();

  private:
    
    unsigned short crc16_modbus(unsigned char *pBuff, int len);
    bool pack_complete(Modbus_data* reg_info, unsigned char* data, unsigned int data_cnt);
    

    unsigned char send_buff[MODBUS_MASTER_SEND_BUFF_SIZE];
    unsigned char recv_buff[MODBUS_MASTER_RECV_BUFF_SIZE];
  
    unsigned int rev_timeout;
    unsigned char max_retry;
};
#endif // _MODBUS_MASTER_H_
