#include "zh03b.h"
#include <string>
#include "modules_def.h"

// command defines
#define HEADER (0xFF)
#define CMD_MODE_ACTIVE (0x40)
#define CMD_MODE_PASSIVE (0x41)
#define CMD_MODE_SET (0x78)
#define CMD_GET_DATA  (0x86)
#define CMD_SLEEP (0xA7)

#define BUFFER_SIZE (9)
#define ERROR_TIMES (2)
// except header and crc bytes(total 2 bytes)
#define CRC_CALC_BYTES (7)

#define CRC_OFFSET (8)

Zh03b::Zh03b(Double_buffered_comm *_comm)
{  
  buffer = new unsigned char[BUFFER_SIZE];

  memset(buffer, 0, BUFFER_SIZE);

  comm = _comm;
  error_times = 0;
}

Zh03b::~Zh03b()
{
  if( comm != NULL )
  {
    delete comm;
    comm = NULL;
  }
  if( buffer != NULL)
  {
    delete buffer;
    buffer = NULL;
  }
}

void Zh03b::exit_sleep(void)
{
  
  memset(buffer, 0, BUFFER_SIZE);

  //帧头0xff
  buffer[0] = HEADER;
  buffer[1] = 0x01; // dummy byte
  //获取数据命令0x86
  buffer[2] = 0xa7;
  buffer[3] = 0x00;
  //计算（去除帧头的7个数据的）校验和并添加至尾部
  buffer[CRC_OFFSET] = crc8(buffer+1, CRC_CALC_BYTES);

  // send get data frame
  comm->send(buffer, BUFFER_SIZE);

}

bool Zh03b::init(void)
{
  exit_sleep();
  //设置成一问一答式
  return set_passive_mode();

}

bool Zh03b::get_data(Zh03b_data *_data, unsigned int timeout)
{
  memset(buffer, 0, BUFFER_SIZE);

  //帧头0xff
  buffer[0] = HEADER;
  buffer[1] = 0x01; // dummy byte
  //获取数据命令0x86
  buffer[2] = CMD_GET_DATA;
  //计算（去除帧头的7个数据的）校验和并添加至尾部
  buffer[CRC_OFFSET] = crc8(buffer+1, CRC_CALC_BYTES);

  // send get data frame
  comm->send(buffer, BUFFER_SIZE);

  // return data process
  if(received_data(timeout))
  {
    //将buffer清空，并将收到的数据存储到buffer内
    memset(buffer, 0, BUFFER_SIZE);

    unsigned int data_cnt = comm->read(buffer, BUFFER_SIZE);
    if(data_cnt != BUFFER_SIZE)
    {
      return false;
    }
    //检测帧头与crc是否正常
    if( !pack_complete(buffer, BUFFER_SIZE))
    {
      return false;
    }

    // copy data to returned data struct
    _data->pm2_5 = (buffer[2] << 8) | buffer[3];
    _data->pm10 = (buffer[4] << 8) | buffer[5];
    _data->pm1  = (buffer[6] << 8) | buffer[7];
    error_times = 0;
    return true;
  }
  else
  {
    if (error_times <= ERROR_TIMES)
    {
      error_times ++;
    }
  }

  return false;
}

bool Zh03b::pack_complete(unsigned char* data, unsigned int data_len)
{
  bool ret = true;

  // header check 
  ret = ret && (data[0] == HEADER);

  // crc check
  ret = ret && (buffer[CRC_OFFSET] == crc8(data+1, CRC_CALC_BYTES));

  return ret;
}

//设置成一问一答式
bool Zh03b::set_passive_mode()
{
  //先将buffer清空
  memset(buffer, 0, BUFFER_SIZE);
  //将帧头0xFF和命令字0x01、0x78、0x41填入
  buffer[0] = HEADER;
  buffer[1] = 0x01; // dummy byte
  buffer[2] = CMD_MODE_SET;
  buffer[3] = CMD_MODE_PASSIVE;
  //计算（除去帧头的7个数据的）校验和并添加到尾部
  buffer[CRC_OFFSET] = crc8(buffer+1, CRC_CALC_BYTES);

  return comm->send(buffer, BUFFER_SIZE);
  // TODO: add read command to verify mode switch success
}

bool Zh03b::is_error()
{
  //zh03b没有重新初始化指令
 if(error_times > ERROR_TIMES)
 {
   init();
    return true;
 }
 return false;
}

bool Zh03b::received_data(int timeout)
{
  bool ret = true;
  while (comm->data_available() == 0)
  {
    timeout--;
    if (timeout <= 0)
    {
      ret = false;
      break;
    }
    DELAY_MS(1);
  }
  return ret;
}
//crc校验
unsigned char Zh03b::crc8(unsigned char* data, unsigned int data_len)
{
  unsigned char ret = 0;

  for(int i=0; i<data_len; i++)
  {
    ret += data[i];
  }

  ret = (~ret) + 1;

  return ret;
}
