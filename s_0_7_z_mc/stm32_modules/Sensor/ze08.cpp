#include "ze08.h"
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

Ze08::Ze08(Double_buffered_comm *_comm)
{

  buffer = new unsigned char[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  comm = _comm;
  error_times = 0;
}

Ze08::~Ze08()
{
  if( comm != NULL )
  {
    delete comm;
    comm = NULL;
  }
  if(buffer != NULL)
  {
    delete buffer;
    buffer = NULL;
  }
}

bool Ze08::init(void)
{
  return set_passive_mode();
}

bool Ze08::refresh_all_data(unsigned int timeout)
{
  memset(buffer, 0, BUFFER_SIZE);

  buffer[0] = HEADER;
  buffer[1] = 0x01; // dummy byte
  buffer[2] = CMD_GET_DATA;
  buffer[CRC_OFFSET] = crc8(buffer+1, CRC_CALC_BYTES);

  // send get data frame
  comm->send(buffer, BUFFER_SIZE);

  // return data process
  if(received_data(timeout))
  {
    memset(buffer, 0, BUFFER_SIZE);

    unsigned int data_cnt = comm->read(buffer, BUFFER_SIZE);
    if(data_cnt != BUFFER_SIZE)
    {
      return false;
    }

    if( !pack_complete(buffer, BUFFER_SIZE))
    {
      return false;
    }

    // copy data to returned data struct
    ch2o_ug = (buffer[2] << 8) | buffer[3];
    ch2o_ppb  = (buffer[6] << 8) | buffer[7];
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
unsigned short Ze08::get_ug_data()
{
  refresh_all_data();
  return ch2o_ug;
}
unsigned short Ze08::get_ppb_data()
{
  refresh_all_data();
  return ch2o_ppb;
}
bool Ze08::pack_complete(unsigned char* data, unsigned int data_len)
{
  bool ret = true;

  // header check 
  ret = ret && (data[0] == HEADER);

  // crc check
  ret = ret && (buffer[CRC_OFFSET] == crc8(data+1, CRC_CALC_BYTES));

  return ret;
}

bool Ze08::set_passive_mode()
{
  memset(buffer, 0, BUFFER_SIZE);

  buffer[0] = HEADER;
  buffer[1] = 0x01; // dummy byte
  buffer[2] = CMD_MODE_SET;
  buffer[3] = CMD_MODE_PASSIVE;

  buffer[CRC_OFFSET] = crc8(buffer+1, CRC_CALC_BYTES);

  return comm->send(buffer, BUFFER_SIZE);
  // TODO: add read command to verify mode switch success
}

bool Ze08::is_error()
{
  //ze08没有重新启动/重新初始化指令
 if(error_times > ERROR_TIMES)
 {
    init();
    return true;
 }
 return false;
}  

bool Ze08::received_data(int timeout)
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

unsigned char Ze08::crc8(unsigned char* data, unsigned int data_len)
{
  unsigned char ret = 0;

  for(int i=0; i<data_len; i++)
  {
    ret += data[i];
  }

  ret = (~ret) + 1;

  return ret;
}
