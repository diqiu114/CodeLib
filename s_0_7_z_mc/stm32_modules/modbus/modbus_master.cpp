#include "modbus_master.h"
#include "stm32f4xx_hal.h"


Modbus_master::Modbus_master(Double_buffered_comm * handle, unsigned int timeout,unsigned char _retry)
{
  modbus_master = handle;
  rev_timeout = timeout;
  max_retry = _retry;
}

void Modbus_master::set_rev_timeout(unsigned int timeout)
{
  rev_timeout = timeout;
}

unsigned int Modbus_master::read_reg(Modbus_data* reg_info, unsigned short* rev_buff)
{
  unsigned int idx = 0;
  unsigned retry = max_retry;
  // fill register infomation to send buffer
  send_buff[idx++] = reg_info->id;
  send_buff[idx++] = reg_info->cmd;
  send_buff[idx++] = (unsigned char)(reg_info->reg_addr >> 8); 
  send_buff[idx++] = (unsigned char)(reg_info->reg_addr >> 0);
  send_buff[idx++] = (unsigned char)(reg_info->reg_cnt >> 8); 
  send_buff[idx++] = (unsigned char)(reg_info->reg_cnt >> 0);
  unsigned short crc = crc16_modbus(send_buff, idx);
  send_buff[idx++] = (unsigned char)(crc >> 0);
  send_buff[idx++] = (unsigned char)(crc >> 8);
  
  while(retry--)
  {
    //clear recieve buffer
    modbus_master->read_all(recv_buff);
    memset(recv_buff,0,sizeof(recv_buff));
    // send read frame
    modbus_master->send(send_buff, idx);
    // check slave response
    if(received_data(rev_timeout))
    {
      unsigned int data_cnt = modbus_master->read_all(recv_buff);
      // read out data from buffer
      if(data_cnt > 0)
      {
        if(pack_complete(reg_info, recv_buff, data_cnt))
        {
          // copy slave data to return buffer
          unsigned char* data = &recv_buff[MODBUS_RET_DATA_IDX];
          for(int i = 0, j = 0; j < recv_buff[MODBUS_RET_DATA_CNT]; i++, j+=2)
          {
            rev_buff[i] = ( data[j] << 8 ) | data[j+1];
          }
          return recv_buff[MODBUS_RET_DATA_CNT] / 2;
        }
      }  
    }
  }
  return 0;
}

bool Modbus_master::received_data(unsigned int timeout)
{
  bool ret = true;
  while( modbus_master->data_available() == 0 )
  {
    timeout--;
    if( timeout <= 0 )
    {
      ret = false;
      break;
    }
    DELAY_MS(1);
  }
  
  return ret;
}

bool Modbus_master::pack_complete(Modbus_data* reg_info, unsigned char* data, unsigned int data_cnt)
{
  bool ret = true;
  // check device id correct
  ret = ret && ( reg_info->id == data[MODBUS_ID_IDX] );
  // check command correct
  ret = ret && ( reg_info->cmd ==  data[MODBUS_CMD_IDX]);
  // check crc correct
  unsigned short crc = crc16_modbus(data, data_cnt - MODBUS_CRC_BYTES);
  ret = ret && ( ((unsigned char)(crc) == data[data_cnt-2]) 
                  && ((unsigned char)(crc>>8) == data[data_cnt-1]) );

  return ret; 
}

bool Modbus_master::write_reg(Modbus_data* reg_info, unsigned short reg_data)
{
  unsigned int idx = 0;
  unsigned retry = max_retry;
  // fill register infomation to send buffer
  send_buff[idx++] = reg_info->id;
  send_buff[idx++] = reg_info->cmd;
  send_buff[idx++] = (unsigned char)(reg_info->reg_addr >> 8); 
  send_buff[idx++] = (unsigned char)(reg_info->reg_addr >> 0);
  send_buff[idx++] = (unsigned char)(reg_data >> 8); 
  send_buff[idx++] = (unsigned char)(reg_data >> 0);
  unsigned short crc = crc16_modbus(send_buff, idx);
  send_buff[idx++] = (unsigned char)(crc >> 0);
  send_buff[idx++] = (unsigned char)(crc >> 8);

  while(retry--)
  { 
    // send read frame
    modbus_master->send(send_buff, idx); 
     // check slave response
    if(received_data(rev_timeout) )
    {
      DELAY_MS(4);
      // read out data from buffer
      unsigned data_cnt = modbus_master->read_all(recv_buff);
      if( data_cnt > 0 )
      {
        // check pack complete
        if(pack_complete(reg_info, recv_buff, data_cnt))
        {
          return true;
        }
      }
    }
  }
  return false;
}

unsigned short Modbus_master::crc16_modbus(unsigned char *pBuff, int len)
{
  if( len <= 0 )
  {
    return 0;
  }
  
  unsigned int   i, j;
  unsigned short crc = 0xffff;

  for(i = 0; i < len; i++)
  {
    crc ^= (unsigned short)( pBuff[i] );
    for(j = 0; j < 8; j++)
    {
      if(crc & 1)
      {
        crc >>= 1;
        crc  ^= 0xa001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}

Modbus_master::~Modbus_master()
{

}
