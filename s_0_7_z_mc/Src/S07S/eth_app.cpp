#include "eth_app.h"

Eth_app::Eth_app(Eth_module* _eth, unsigned int buffer_size)
{
  eth = _eth;
  train_eth_proto = new Proj_eth_proto();
  eth_module_rev_data.data = new unsigned char[buffer_size];
  memset(eth_module_rev_data.data, 0, buffer_size);
  memset(&train_msg, 0, sizeof(train_msg));

  sour_dev_num[0] = ETH_SOUR1_NUM;
  sour_dev_num[1] = ETH_SOUR2_NUM;
  host_dev_num[0] = ETH_HOST1_NUM;
  host_dev_num[1] = ETH_HOST2_NUM;

}
void Eth_app::init_defualt_value(unsigned char idx)
{
  train_msg.sour = sour_dev_num[idx];
  train_msg.host = host_dev_num[idx];
  train_msg.msg_type = ETH_MSG_TYPE;
  train_msg.line = 5;
  train_msg.train_type = 10;
  train_msg.group = 0;
  
  if(idx == 0)
  {
    train_msg.carriage = 1;
  }
  else
  {
    train_msg.carriage = 6;
  }
  
  train_msg.proto_ver = 1;
}
bool Eth_app::init(Eth_Module_Cfg* cfg, char mode)
{
  bool ret = eth->config(cfg, mode);

  DELAY_MS(1500);

  return ret;
}

bool Eth_app::send_msg(unsigned char* data, unsigned int data_cnt)
{
  bool ret = true;;

  unsigned char* buffer = new unsigned char[ETH_APP_TRAIN_MSG_LEN + data_cnt];

  if( buffer == NULL )
  {
    return false;
  }

  memset(buffer, 0, ETH_APP_TRAIN_MSG_LEN + data_cnt);

  unsigned int data_len = fill_buffer(data, data_cnt, buffer);

  unsigned int s_bytes = train_eth_proto->pack(buffer, data_len, buffer);

  eth_module_send_data.data = buffer;
  eth_module_send_data.data_cnt = s_bytes;
  
  train_msg.dest_dev_id = 1;

  eth_module_send_data.cmd = train_msg.dest_dev_id + 0x70;
  eth->send_data(&eth_module_send_data);
  
  train_msg.dest_dev_id = 2;
  eth_module_send_data.cmd = train_msg.dest_dev_id + 0x70;
  eth->send_data(&eth_module_send_data);  
  
  delete []buffer;

  return ret;
}


unsigned int Eth_app::fill_buffer(unsigned char* data, unsigned int data_cnt, unsigned char* buffer)
{
  unsigned int len = 0;
  train_msg.vital++;
  buffer[len++] = train_msg.sour;
  buffer[len++] = train_msg.host;
  buffer[len++] = train_msg.msg_type >> 8;
  buffer[len++] = train_msg.msg_type;
  buffer[len++] = train_msg.vital >> 8;
  buffer[len++] = train_msg.vital;
  buffer[len++] = train_msg.line >> 8;
  buffer[len++] = train_msg.line;
  buffer[len++] = train_msg.train_type >> 8;
  buffer[len++] = train_msg.train_type;
  buffer[len++] = train_msg.group >> 8*3;
  buffer[len++] = train_msg.group >> 8*2;
  buffer[len++] = train_msg.group >> 8*1;
  buffer[len++] = train_msg.group >> 8*0;
  buffer[len++] = train_msg.carriage;
  buffer[len++] = train_msg.proto_ver;
  //reserve 10 bytes
  len += 10;
  memcpy(&buffer[len], data, data_cnt);
  len += data_cnt;
  
  return len;

}
void Eth_app::set_rtc_handle(Rtc_ops *rtc)
{
  this->rtc = rtc;
}
void Eth_app::rev_handle()
{

  bool ret = eth->get_data(&eth_module_rev_data);
  if (ret == false)
  {
    return ;
  }
  unsigned int data_cnt = train_eth_proto->unpack(eth_module_rev_data.data, eth_module_rev_data.data_cnt, eth_module_rev_data.data);  
  if (data_cnt == 0)
  {
    return;
  }
}
Eth_app::~Eth_app()
{

}
