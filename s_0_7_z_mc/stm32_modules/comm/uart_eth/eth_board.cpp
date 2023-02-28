#include "eth_board.h"

#define RECV_PD_FIX_LEN        28
#define RECV_MD_FIX_LEN        44
#define RECV_UDP_TRDP_FIX_LEN  20 
#define RECV_UDP_PASS_THROUGH_FIX_LEN  6 
#define RECV_TCP_PASS_THROUGH_FIX_LEN  6 


Eth_board::Eth_board(Double_buffered_comm *handle, Gpio_if *_gpio, int train_num, Trdp_eth_para_t *_paras)
{
  uart = handle;
  is_firs = true;
  Train_num_idx = train_num;
  user_proto_fill_func = NULL;
  send_buffer = NULL;
  recv_buffer = NULL;
  recv_max_len = 0;
  send_max_len = 0;
  trdp_proto = new Eth_module_proto();
  if (_gpio != NULL)
  {
    rst_gpio = _gpio;
  }
  if (_paras != NULL)
  {
    paras = _paras;
  }
}

bool Eth_board::init()
{
  bool ret = false;
  if (reset())
  {
    if(is_firs)
    {
      is_firs = false;
      vTaskDelay(20000);
    }
#if (ETH_NEED_SET_MASTER_SDT || ETH_NEED_SET_UPGRADE_SDT)
    if (!sdt_enable())
    {
      return false;
    }
#endif
    if (config())
    {
      ret = true;
    }
  }
  return ret;
}

bool Eth_board::send_data(unsigned char eth_num, unsigned char *send_buff, unsigned int send_len)
{
  bool ret = true;
#if ETH_TCP_PASSTHROUGH
  ret &= send_tcp_passthrough(eth_num, send_buff, send_len);
#endif
#if ETH_UDP_PASSTHROUGH
  ret &= send_udp_passthrough(eth_num, send_buff, send_len);
#endif
#if ETH_UDP_TRDP
  ret &= send_udp_trdp(eth_num, send_buff, send_len);
#endif
#if ETH_USE_PD
  ret &= send_pd(eth_num, send_buff, send_len);
#endif
#if ETH_USE_MD
  ret &= send_md(eth_num, send_buff, send_len);
#endif
  return ret;
}

unsigned int Eth_board::trdp_rx_handle(unsigned char *data) {
  if(data == NULL)
  {
    return 0;
  }
  DELAY_MS(15);
  unsigned int rev_cnt = uart->data_available();
  if (rev_cnt == 0)
  {
    return 0;
  }
  
  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }
  
  memset(recv_buffer, 0, rev_cnt);
  unsigned int buff_cnt = uart->read(recv_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(recv_buffer, buff_cnt, recv_buffer, 0);

  if(!buff_cnt) {
      return 0;
  }
  
  memcpy(data, recv_buffer, buff_cnt);
  
  return buff_cnt;
  
}



unsigned int Eth_board::recieve_data(unsigned char *data, unsigned int data_len)
{
  unsigned recv_len = 0;
#if ETH_TCP_PASSTHROUGH
  recv_len = rev_tcp_passthrough(data, data_len);
#endif
#if ETH_UDP_PASSTHROUGH
  recv_len = rev_udp_passthrough(data, data_len);
#endif
#if ETH_UDP_TRDP
  recv_len = rev_udp_trdp(data, data_len);
#endif
#if ETH_USE_PD
  recv_len = rev_pd(data, data_len);
#endif
#if ETH_USE_MD
  recv_len = rev_md(data, data_len);
#endif
  return recv_len;
}

bool Eth_board::set_para(Trdp_eth_para_t *_trdp_para)
{
  if (_trdp_para != NULL)
  {
    paras = _trdp_para;
    return true;
  }
  return false;
}

bool Eth_board::reset(void)
{
  if (rst_gpio == NULL)
  {
    return false;
  }

  rst_gpio->set_hi();
  DELAY_MS(1);
  rst_gpio->set_low();
  DELAY_MS(600);
  rst_gpio->set_hi();
  DELAY_MS(2200);
  return true;
}

bool Eth_board::set_recv_queue(QueueHandle_t *recv_queue)
{
  if(recv_queue == NULL)
  {
    return false;
  }
  Eth_comm_queue = recv_queue;
  return true;
}

bool Eth_board::config(void)
{
  unsigned char ret = 0;
  unsigned char *buffer = NULL;
  unsigned char data = 0;
  if (paras == NULL || Eth_comm_queue == NULL)
  {
    return false;
  }
  uart->set_idle_buffer_switch(false);
  for (int i = 0; i < TRDP_MODULE_ETH_PHY_CNT; i++)
  {
    buffer = cfg_buff_fill(i);
    if (buffer != NULL)
    {
      uart->send(buffer, module_data.cfg_pack_len);

      // wait receive data
      if(xQueueReceive(*Eth_comm_queue, &data, module_data.cfg_rsp_delay))
      {
        DELAY_MS(586);
        uart->buffer_switch();
        if (cfg_rsp_ok(i))
        {
          ret |= 1 << (i * 4);
        }
      }
    }
  }
  uart->set_idle_buffer_switch(true);
  if (ret == CFG_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#if (ETH_NEED_SET_MASTER_SDT || ETH_NEED_SET_UPGRADE_SDT)
bool Eth_board::sdt_enable(void)
{
  unsigned char *buffer = NULL;
  unsigned char cnt = 0;
  unsigned char suc_cnt = 0;
  for (int i = 0; i < TRDP_MODULE_ETH_PHY_CNT; i++)
  {
    if (ETH_NEED_SET_MASTER_SDT)
    {
      cnt++;
      buffer = sdt_buff_fill(i, MASTER_SDT_INDEX);

      if (buffer != NULL)
      {
        uart->send(buffer, module_data.sdt_en_pack_len);

        delete[] buffer;
        buffer = NULL;
        // wait receive data
        if (received_data(module_data.sdt_en_rsp_delay))
        {
          if (sdt_rsp_ok(i, MASTER_SDT_INDEX))
          {
            suc_cnt++;
          }
        }
      }
    }
    if (ETH_NEED_SET_UPGRADE_SDT)
    {
      for (int j = 0; j < UPGRADE_COUNT; j++)
      {
        cnt++;
        buffer = sdt_buff_fill(i, UPGRADE1_SDT_INDEX + j);

        if (buffer != NULL)
        {
          uart->send(buffer, module_data.sdt_en_pack_len);

          delete[] buffer;
          buffer = NULL;
          // wait receive data
          if (received_data(module_data.sdt_en_rsp_delay))
          {
            if (sdt_rsp_ok(i, MASTER_SDT_INDEX))
            {
              suc_cnt++;
            }
          }
        }
      }
    }
  }

  if (cnt == suc_cnt)
  {
    return true;
  }
  else
  {
    return false;
  }
}
#endif

#if (ETH_USE_PD)


bool Eth_board::trdp_pd_tx_handle(unsigned char eth_num, uint32_t commid,unsigned char *data, unsigned int data_len)
{
  unsigned char *buff = NULL;
  if ((data == NULL) || (data_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }
  bool ret = true;
  unsigned int len = 0;
  if (user_proto_fill_func != NULL)
  {
    len = user_proto_fill_func(Train_num_idx, data, data_len, data);
    if (len == 0)
    {
      return false;
    }
    data_len = len;
  }
  buff = send_pd_buff_fill(eth_num,commid, data, data_len);
  if (buff != NULL)
  {
    ret = uart->send(buff, module_data.send_pd_non_data_bytes + data_len);
  }
  return ret;
}

bool Eth_board::send_pd(unsigned char eth_num, unsigned char *data, unsigned int data_len)
{
  unsigned char *buff = NULL;
  if ((data == NULL) || (data_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }
  bool ret = true;
  unsigned int len = 0;
  if (user_proto_fill_func != NULL)
  {
    len = user_proto_fill_func(Train_num_idx, data, data_len, data);
    if (len == 0)
    {
      return false;
    }
    data_len = len;
  }
  buff = send_pd_buff_fill(eth_num, data, data_len);
  if (buff != NULL)
  {
    ret = uart->send(buff, module_data.send_pd_non_data_bytes + data_len);
  }
  return ret;
}

unsigned int Eth_board::rev_pd(unsigned char *data, unsigned int data_len)
{
  if(data == NULL)
  {
    return 0;
  }
  DELAY_MS(15);
  unsigned int rev_cnt = uart->data_available();
  if (rev_cnt == 0)
  {
    return 0;
  }
  
  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }
  
  memset(recv_buffer, 0, rev_cnt);
  unsigned int buff_cnt = uart->read(recv_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(recv_buffer, buff_cnt, recv_buffer, data_len + RECV_PD_FIX_LEN);
  if ((buff_cnt == 0) || ((recv_buffer[0] != module_data.rev_pd_cmd[0])
#if ETH_DOUBLE_MODULE
                          && (recv_buffer[0] != module_data.rev_pd_cmd[1])
#endif
                              ))
  {
    return 0;
  }

  unsigned int read_data_len = (unsigned int)((recv_buffer[module_data.pd_pack_data_len_idx] << 24) | (recv_buffer[module_data.pd_pack_data_len_idx + 1] << 16) | 
    (recv_buffer[module_data.pd_pack_data_len_idx + 2] << 8) | (recv_buffer[module_data.pd_pack_data_len_idx + 3] << 0));
  if (data_len != 0)
  {
    read_data_len = read_data_len > data_len ? data_len : read_data_len;
  }

  // fill eth number
  if (recv_buffer[0] == module_data.rev_pd_cmd[0])
  {
    data[0] = 0;
  }
#if ETH_DOUBLE_MODULE
  else if (recv_buffer[0] == module_data.rev_pd_cmd[1])
  {
    data[0] = 1;
  }
#endif
  else
  {
    // error
    data[0] = 0xff;
  }

  // fill data
  memcpy(data + 1, &recv_buffer[module_data.pd_pack_data_idx], read_data_len);
  return read_data_len + 1;
}
#endif

#if (ETH_USE_MD)
bool Eth_board::send_md(unsigned char eth_num, unsigned char *data, unsigned int data_len)
{
  if ((data == NULL) || (data_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }
  bool ret = true;
  unsigned int len = 0;
  if (user_proto_fill_func != NULL)
  {
    len = user_proto_fill_func(Train_num_idx, data, data_len, data);
    if (len == 0)
    {
      return false;
    }
    data_len = len;
  }
  for (int i = 0; i < MASTER_BROADCAST_COUNT; i++)
  {
    unsigned char *buff = send_md_buff_fill(eth_num, data, data_len, paras->eth_mast_group_ip[i]);
    if (buff != NULL)
    {
      ret &= uart->send(buff, module_data.send_md_non_data_bytes + data_len);
    }
  }
  return ret;
}

unsigned int Eth_board::rev_md(unsigned char *data, unsigned int data_len)
{
  if (data == NULL)
  {
    return 0;
  }

  unsigned int rev_cnt = uart->data_available();
  if (rev_cnt == 0)
  {
    return 0;
  }

  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }

  memset(recv_buffer, 0, rev_cnt);

  unsigned int buff_cnt = uart->read(recv_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(recv_buffer, buff_cnt, recv_buffer, data_len + RECV_MD_FIX_LEN);
  if ((buff_cnt == 0) || ((recv_buffer[0] != module_data.rev_md_cmd[0]) && (recv_buffer[0] != module_data.rev_md_cmd[1])))
  {
    return 0;
  }

  unsigned int read_data_len = (unsigned int)((recv_buffer[module_data.md_pack_data_len_idx] << 24) | (recv_buffer[module_data.md_pack_data_len_idx + 1] << 16) | (recv_buffer[module_data.md_pack_data_len_idx + 2] << 8) | (recv_buffer[module_data.md_pack_data_len_idx + 3] << 0));
  if (data_len != 0)
  {
    read_data_len = read_data_len > data_len ? data_len : read_data_len;
  }

  // fill eth number
  if (recv_buffer[0] == module_data.rev_md_cmd[0])
  {
    data[0] = 0;
  }
  else if (recv_buffer[0] == module_data.rev_md_cmd[1])
  {
    data[0] = 1;
  }
  else
  {
    // error
    data[0] = TRDP_MODULE_ETH_PHY_CNT;
  }

  // fill data
  memcpy(data + 1, &recv_buffer[module_data.md_pack_data_idx], read_data_len);

  return read_data_len + 1;
}
#endif

#if (ETH_UDP_TRDP)
bool Eth_board::send_udp_trdp(unsigned char eth_num, unsigned char *data, unsigned int data_len)
{
  if ((data == NULL) || (data_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }
  bool ret = true;
  unsigned int len = 0;
  if (user_proto_fill_func != NULL)
  {
    len = user_proto_fill_func(Train_num_idx, data, data_len, data);
    if (len == 0)
    {
      return false;
    }
    data_len = len;
  }
  for (int i = 0; i < UPGRADE_COUNT; i++)
  {
    unsigned char *buff = send_udp_trdp_buff_fill(eth_num, data, data_len, i);
    if (buff != NULL)
    {
      ret &= uart->send(buff, module_data.send_udp_trdp_non_data_bytes + data_len);
    }
  }
  return ret;
}

unsigned int Eth_board::rev_udp_trdp(unsigned char *data, unsigned int data_len)
{
  if (data == NULL)
  {
    return 0;
  }

  unsigned int rev_cnt = uart->data_available();
  if (rev_cnt == 0)
  {
    return 0;
  }

  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }

  memset(recv_buffer, 0, rev_cnt);

  unsigned int buff_cnt = uart->read(recv_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(recv_buffer, buff_cnt, recv_buffer, data_len + RECV_UDP_TRDP_FIX_LEN);
  if ((buff_cnt == 0) || ((recv_buffer[0] != module_data.rev_udp_trdp_cmd[0][0]) && (recv_buffer[0] != module_data.rev_udp_trdp_cmd[0][1]) && (recv_buffer[0] != module_data.rev_udp_trdp_cmd[1][0]) && (recv_buffer[0] != module_data.rev_udp_trdp_cmd[1][1])))
  {
    return 0;
  }

  unsigned int read_data_len = (unsigned int)((recv_buffer[module_data.udp_trdp_pack_data_len_idx] << 24) | (recv_buffer[module_data.udp_trdp_pack_data_len_idx + 1] << 16) | (recv_buffer[module_data.udp_trdp_pack_data_len_idx + 2] << 8) | (recv_buffer[module_data.udp_trdp_pack_data_len_idx + 3] << 0));
  if (data_len != 0)
  {
    read_data_len = read_data_len > data_len ? data_len : read_data_len;
  }

  // fill eth number
  if (recv_buffer[0] == module_data.rev_udp_trdp_cmd[0][0])
  {
    data[0] = 0x00;
  }
  else if (recv_buffer[0] == module_data.rev_udp_trdp_cmd[0][1])
  {
    data[0] = 0x01;
  }
  else if (recv_buffer[0] == module_data.rev_udp_trdp_cmd[1][0])
  {
    data[0] = 0x10;
  }
  else if (recv_buffer[0] == module_data.rev_udp_trdp_cmd[1][1])
  {
    data[0] = 0x11;
  }
  else
  {
    // error
    data[0] = TRDP_MODULE_ETH_PHY_CNT;
  }

  // fill data
  memcpy(data + 1, &recv_buffer[module_data.udp_trdp_pack_data_idx], read_data_len);

  return read_data_len + 1;
}
#endif

#if (ETH_UDP_PASSTHROUGH)
bool Eth_board::send_udp_passthrough(unsigned char eth_num, unsigned char *data, unsigned int data_len)
{
  if ((data == NULL) || (data_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }
  bool ret = true;
  unsigned int len = 0;
  if (user_proto_fill_func != NULL)
  {
    len = user_proto_fill_func(Train_num_idx, data, data_len, data);
    if (len == 0)
    {
      return false;
    }
    data_len = len;
  }
  unsigned char *buff = send_udp_passthrough_buff_fill(eth_num, data, data_len);
  if (buff != NULL)
  {
    ret = uart->send(buff, module_data.send_udp_passthrough_non_data_bytes + data_len);
  }
  return ret;
}

unsigned int Eth_board::rev_udp_passthrough(unsigned char *data, unsigned int data_len)
{
  if (data == NULL)
  {
    return 0;
  }

  unsigned int rev_cnt = uart->data_available();
  if (rev_cnt == 0)
  {
    return 0;
  }

  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }

  memset(pack_buffer, 0, rev_cnt);

  unsigned int buff_cnt = uart->read(recv_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(recv_buffer, buff_cnt, recv_buffer, data_len + RECV_UDP_PASS_THROUGH_FIX_LEN);
  if ((buff_cnt == 0) || ((recv_buffer[0] != module_data.rev_udp_passthrough_cmd[0]) && (recv_buffer[0] != module_data.rev_udp_passthrough_cmd[1])))
  {
    return 0;
  }

  unsigned int read_data_len = (unsigned int)((recv_buffer[module_data.udp_passthrough_pack_data_len_idx] << 24) | (recv_buffer[module_data.udp_passthrough_pack_data_len_idx + 1] << 16) | (recv_buffer[module_data.udp_passthrough_pack_data_len_idx + 2] << 8) | (recv_buffer[module_data.udp_passthrough_pack_data_len_idx + 3] << 0));
  if (data_len != 0)
  {
    read_data_len = read_data_len > data_len ? data_len : read_data_len;
  }

  // fill eth number
  if (recv_buffer[0] == module_data.rev_udp_passthrough_cmd[0])
  {
    data[0] = 0;
  }
  else if (recv_buffer[0] == module_data.rev_udp_passthrough_cmd[1])
  {
    data[0] = 1;
  }
  else
  {
    // error
    data[0] = TRDP_MODULE_ETH_PHY_CNT;
  }

  // fill data
  memcpy(data + 1, &recv_buffer[module_data.udp_passthrough_pack_data_idx], read_data_len);

  return read_data_len + 1;
}
#endif

#if (ETH_TCP_PASSTHROUGH)
bool Eth_board::send_tcp_passthrough(unsigned char eth_num, unsigned char *data, unsigned int data_len)
{
  if ((data == NULL) || (data_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }
  bool ret = true;
  unsigned int len = 0;
  if (user_proto_fill_func != NULL)
  {
    len = user_proto_fill_func(Train_num_idx, data, data_len, data);
    if (len == 0)
    {
      return false;
    }
    data_len = len;
  }
  for (int i = 0; i < UPGRADE_COUNT; i++)
  {
    unsigned char *buff = send_tcp_passthrough_buff_fill(eth_num, data, data_len, i);
    if (buff != NULL)
    {
      ret &= uart->send(buff, module_data.send_udp_trdp_non_data_bytes + data_len);
    }
  }
  return ret;
}

unsigned int Eth_board::rev_tcp_passthrough(unsigned char *data, unsigned int data_len)
{
  if (data == NULL)
  {
    return 0;
  }

  unsigned int rev_cnt = uart->data_available();
  if (rev_cnt == 0)
  {
    return 0;
  }

  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }

  memset(recv_buffer, 0, rev_cnt);

  unsigned int buff_cnt = uart->read(recv_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(recv_buffer, buff_cnt, recv_buffer, data_len + RECV_TCP_PASS_THROUGH_FIX_LEN);
  if ((buff_cnt == 0) || ((recv_buffer[0] != module_data.rev_tcp_passthrough_cmd[0][0]) && (recv_buffer[0] != module_data.rev_tcp_passthrough_cmd[0][1]) && (recv_buffer[0] != module_data.rev_tcp_passthrough_cmd[1][0]) && (recv_buffer[0] != module_data.rev_tcp_passthrough_cmd[1][1])))
  {
    return 0;
  }

  unsigned int read_data_len = (unsigned int)((recv_buffer[module_data.tcp_passthrough_pack_data_len_idx] << 24) | (recv_buffer[module_data.tcp_passthrough_pack_data_len_idx + 1] << 16) | (recv_buffer[module_data.tcp_passthrough_pack_data_len_idx + 2] << 8) | (recv_buffer[module_data.tcp_passthrough_pack_data_len_idx + 3] << 0));
  if (data_len != 0)
  {
    read_data_len = read_data_len > data_len ? data_len : read_data_len;
  }

  // fill eth number
  if (recv_buffer[0] == module_data.rev_tcp_passthrough_cmd[0][0])
  {
    data[0] = 0x00;
  }
  else if (recv_buffer[0] == module_data.rev_tcp_passthrough_cmd[0][1])
  {
    data[0] = 0x01;
  }
  else if (recv_buffer[0] == module_data.rev_tcp_passthrough_cmd[1][0])
  {
    data[0] = 0x10;
  }
  else if (recv_buffer[0] == module_data.rev_tcp_passthrough_cmd[1][1])
  {
    data[0] = 0x11;
  }
  else
  {
    // error
    data[0] = TRDP_MODULE_ETH_PHY_CNT;
  }

  // fill data
  memcpy(data + 1, &recv_buffer[module_data.tcp_passthrough_pack_data_idx], read_data_len);

  return read_data_len + 1;
}
#endif

bool Eth_board::set_user_proto_handle_func(Proto_fill_template_func _func)
{
  if (_func == NULL)
  {
    return false;
  }
  user_proto_fill_func = _func;
  return true;
}

#if (ETH_NEED_SET_UPGRADE_SDT || ETH_NEED_SET_MASTER_SDT)
unsigned char *Eth_board::sdt_buff_fill(unsigned char eth_num, unsigned char sdt_index)
{
  unsigned char *pack_buffer = new unsigned char[module_data.sdt_en_pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  memset(pack_buffer, 0, module_data.sdt_en_pack_len);
  unsigned data_len = module_data.sdt_en_pack_len - (ETH_MP_CRC_CALC_OFFSET + ETH_MP_CRC_BYTES);
  unsigned int offset = 0;
  pack_buffer[offset++] = module_data.sdt_en_cmd[eth_num][sdt_index];
  pack_buffer[offset++] = (unsigned char)(data_len >> 8);
  pack_buffer[offset++] = (unsigned char)(data_len >> 0);

  // fill smi
  pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num][Train_num_idx].bms_smi >> 24);
  pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num][Train_num_idx].bms_smi >> 16);
  pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num][Train_num_idx].bms_smi >> 8);
  pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num][Train_num_idx].bms_smi >> 0);
  // version
  pack_buffer[offset++] = (unsigned char)(paras->main_version);
  pack_buffer[offset++] = (unsigned char)(paras->sub_version);
#if (ETH_NEED_SET_CONSISTID)
  {
    for (int i = 0; i < CONSISTID_COUNT; i++)
    {
      pack_buffer[offset++] = (unsigned char)(paras->consistid[i]);
    }
  }
#else
  {
    offset += 16;
  }
#endif
  // safe topo count 4 bytes, default 0
  offset += 4;

  // smi receive count
  pack_buffer[offset++] = RECV_SMI_COUNT;

  for (int i = 0; i < RECV_SMI_COUNT; i++)
  {
    // receive smi
    pack_buffer[offset++] = (unsigned char)(paras->recv_smi[i] >> 24);
    pack_buffer[offset++] = (unsigned char)(paras->recv_smi[i] >> 16);
    pack_buffer[offset++] = (unsigned char)(paras->recv_smi[i] >> 8);
    pack_buffer[offset++] = (unsigned char)(paras->recv_smi[i] >> 0);
  }
  offset = (6 - RECV_SMI_COUNT) * 4;

  unsigned int send_len = trdp_proto->pack(pack_buffer, offset, pack_buffer, false);
  if (send_len == module_data.sdt_en_pack_len)
  {
    return pack_buffer;
  }
  else
  {
    delete[] pack_buffer;
    return NULL;
  }
}
bool Eth_board::sdt_rsp_ok(unsigned char eth_num, unsigned char sdt_index)
{
  unsigned char *pack_buffer = new unsigned char[module_data.sdt_en_rsp_pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  memset(pack_buffer, 0, module_data.sdt_en_rsp_pack_len);

  unsigned Pack_cnt = uart->read(pack_buffer, module_data.sdt_en_rsp_pack_len);
  if (Pack_cnt == 0)
  {
    delete[] pack_buffer;
    return false;
  }

  unsigned data_cnt = trdp_proto->unpack(pack_buffer, Pack_cnt, pack_buffer);
  if (data_cnt == 0)
  {
    delete[] pack_buffer;
    return false;
  }

  unsigned int cfg_status = (pack_buffer[3] << 24) | (pack_buffer[4] << 16) | (pack_buffer[5] << 8) | pack_buffer[6];
  if ((pack_buffer[0] == module_data.sdt_en_rsp[eth_num][sdt_index]) && (cfg_status == 0))
  {
    delete[] pack_buffer;
    return true;
  }
  else
  {
    delete[] pack_buffer;
    return false;
  }
}
#endif

unsigned char *Eth_board::cfg_buff_fill(unsigned char eth_num)
{
  if(module_data.cfg_pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[module_data.cfg_pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = module_data.cfg_pack_len;
  }
  
  unsigned char *pack_buffer = send_buffer;

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  memset(pack_buffer, 0, send_max_len);
  unsigned data_len = module_data.cfg_pack_len - (ETH_MP_CRC_CALC_OFFSET + ETH_MP_CRC_BYTES);
  unsigned int offset = 0;
  pack_buffer[offset++] = module_data.cfg_cmd[eth_num];
  pack_buffer[offset++] = (unsigned char)(data_len >> 8);
  pack_buffer[offset++] = (unsigned char)(data_len >> 0);

  // MAC option
  pack_buffer[offset++] = module_data.mac_opt;
  // MAC
#if (ETH_NEED_SET_MAC_HIG)
  {
    pack_buffer[offset++] = paras->bms[eth_num].mac_hig[0];
    pack_buffer[offset++] = paras->bms[eth_num].mac_hig[1];
  }
#else
  {
    offset += 2;
  }
#endif
#if (ETH_NEED_SET_MAC_MID)
  {
    pack_buffer[offset++] = paras->bms[eth_num].mac_mid[0];
    pack_buffer[offset++] = paras->bms[eth_num].mac_mid[1];
  }
#else
  {
    offset += 2;
  }
#endif
#if (ETH_NEED_SET_MAC_MIN)
  {
    pack_buffer[offset++] = paras->bms[eth_num].mac_min[0];
    pack_buffer[offset++] = paras->bms[eth_num].mac_min[1];
  }
#else
  {
    offset += 2;
  }
#endif
  // eth ip
  pack_buffer[offset++] = paras->bms[eth_num].eth_ip[0];
  pack_buffer[offset++] = paras->bms[eth_num].eth_ip[1];
  pack_buffer[offset++] = paras->bms[eth_num].eth_ip[2];
  pack_buffer[offset++] = paras->bms[eth_num].eth_ip[3];
  // eth gateway
  pack_buffer[offset++] = paras->bms[eth_num].eth_gateway[0];
  pack_buffer[offset++] = paras->bms[eth_num].eth_gateway[1];
  pack_buffer[offset++] = paras->bms[eth_num].eth_gateway[2];
  pack_buffer[offset++] = paras->bms[eth_num].eth_gateway[3];
  // eth mask
  pack_buffer[offset++] = paras->bms[eth_num].eth_mask[0];
  pack_buffer[offset++] = paras->bms[eth_num].eth_mask[1];
  pack_buffer[offset++] = paras->bms[eth_num].eth_mask[2];
  pack_buffer[offset++] = paras->bms[eth_num].eth_mask[3];
  //DNS
#if (ETH_NEED_SET_DNS)
  {
    pack_buffer[offset++] = paras->bms[eth_num].eth_dns[0];
    pack_buffer[offset++] = paras->bms[eth_num].eth_dns[1];
    pack_buffer[offset++] = paras->bms[eth_num].eth_dns[2];
    pack_buffer[offset++] = paras->bms[eth_num].eth_dns[3];
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].dns_port >> 8);
    pack_buffer[offset++] = (unsigned char)paras->bms[eth_num].dns_port;
  }
#else
  {
    offset += 6;
  }
#endif
  //TTDB
#if (ETH_NEED_SET_TTDB)
  {
    pack_buffer[offset++] = paras->bms[eth_num].eth_ttdb[0];
    pack_buffer[offset++] = paras->bms[eth_num].eth_ttdb[1];
    pack_buffer[offset++] = paras->bms[eth_num].eth_ttdb[2];
    pack_buffer[offset++] = paras->bms[eth_num].eth_ttdb[3];
  }
#else
  {
    offset += 4;
  }
#endif
//  receive group ip
#if (ETH_NEED_SET_RECV_GROUP)
  {
    pack_buffer[offset++] = paras->bms[eth_num].eth_recv_group_ip[0];
    pack_buffer[offset++] = paras->bms[eth_num].eth_recv_group_ip[1];
    pack_buffer[offset++] = paras->bms[eth_num].eth_recv_group_ip[2];
    pack_buffer[offset++] = paras->bms[eth_num].eth_recv_group_ip[3];
  }
#else
  {
    offset += 4;
  }
#endif
// ttdb port 2bytes
#if (ETH_NEED_SET_TTDB)
  {
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].ttdb_port >> 8);
    pack_buffer[offset++] = (unsigned char)paras->bms[eth_num].ttdb_port;
  }
#else
  {
    offset += 2;
  }
#endif
// receive group port
#if (ETH_NEED_SET_RECV_GROUP)
  {
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].eth_recv_group_port >> 8);
    pack_buffer[offset++] = (unsigned char)paras->bms[eth_num].eth_recv_group_port;
  }
#else
  {
    offset += 2;
  }
#endif
#if (ETH_NEED_SET_MASTR_BROADCAST)
  for(int i = 0; i < MASTER_BROADCAST_COUNT; i++)
  {
    // master connect ip1
    pack_buffer[offset++] = paras->bms[eth_num].eth_mast_group_ip[i][0];
    pack_buffer[offset++] = paras->bms[eth_num].eth_mast_group_ip[i][1];
    pack_buffer[offset++] = paras->bms[eth_num].eth_mast_group_ip[i][2];
    pack_buffer[offset++] = paras->bms[eth_num].eth_mast_group_ip[i][3];
    // master connect port1
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].eth_mast_group_port[0] >> 8);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].eth_mast_group_port[0] >> 0);
  }
  offset += (MAX_MASTER_GROUP_IP_CNT - MASTER_BROADCAST_COUNT) * 6;
#else
  offset += 12;
#endif
  // comid count
  pack_buffer[offset++] = COMMID_COUNT;
#if (ETH_NEED_SET_COMMID)
  for (int i = 0; i < COMMID_COUNT; i++)
  {
    // comid
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].recv_commid[i] >> 24);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].recv_commid[i] >> 16);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].recv_commid[i] >> 8);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].recv_commid[i] >> 0);
  }
#endif
  offset += (MAX_RECV_COMMID_CNT - COMMID_COUNT) * 4;

  // program upgrade connection options
  pack_buffer[offset++] = module_data.upgrade_conn_opt;
  for (int i = 0; i < UPGRADE_COUNT; i++)
  {
    // upgrade ip
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].upgrade_ip[i][0]);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].upgrade_ip[i][1]);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].upgrade_ip[i][2]);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].upgrade_ip[i][3]);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].dest_port[i] >> 8);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].dest_port[i] );
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].src_port[i]  >> 8);
    pack_buffer[offset++] = (unsigned char)(paras->bms[eth_num].src_port[i] );
  }
  offset += (MAX_UPGRADE_IP_MAX - UPGRADE_COUNT) * 8;

  unsigned int send_len = trdp_proto->pack(pack_buffer, offset, pack_buffer, false);
  if (send_len == module_data.cfg_pack_len)
  {
    return pack_buffer;
  }
  else
  {
    return NULL;
  }
}

bool Eth_board::cfg_rsp_ok(unsigned char eth_num)
{
  unsigned short rev_cnt = uart->data_available();
  
  if(rev_cnt > recv_max_len)
  {
    if(recv_buffer != NULL)
    {
      delete[] recv_buffer;
      recv_buffer = NULL;
    }
    
    recv_buffer = new unsigned char[rev_cnt];
    if (recv_buffer == NULL)
    {
      recv_max_len = 0;
      return 0;
    }
    recv_max_len = rev_cnt;
  }

  memset(recv_buffer, 0, recv_max_len);

  unsigned short Pack_cnt = uart->read(recv_buffer, rev_cnt);
  if (Pack_cnt == 0)
  {
    return false;
  }
  
  unsigned data_cnt = trdp_proto->unpack(recv_buffer, Pack_cnt, recv_buffer, 8);
  if (data_cnt == 0)
  {
    return false;
  }

  if (recv_buffer[0] == module_data.cfg_rsp[eth_num])
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Eth_board::received_data(int timeout)
{
  bool ret = true;

  while (uart->data_available() == 0)
  {
    timeout--;
    if (timeout <= 0)
    {
      ret = false;
      break;
    }
    DELAY_MS(1);
  }

  DELAY_MS(586);
  return ret;
}

bool Eth_board::delete_recv_buff()
{
  if(recv_buffer == NULL)
  {
    return false;
  }
  delete[] recv_buffer;
  recv_buffer = NULL;
  recv_max_len = 0;
  return true;
}

bool Eth_board::delete_send_buff()
{
  if(send_buffer == NULL)
  {
    return false;
  }
  delete[] send_buffer;
  send_buffer = NULL;
  send_max_len = 0;
  return trdp_proto->delete_pack_buffer();
}

#if ETH_USE_PD
unsigned char *Eth_board::send_pd_buff_fill(unsigned char eth_num, uint32_t commid,unsigned char *data, unsigned int buff_len) 
{
  unsigned pack_len = module_data.send_pd_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;
  
  if(pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = pack_len;
  }

  module_data.master_sqe_counter[eth_num]++;
  unsigned int offset = 0;
  // command
  send_buffer[offset++] = module_data.send_pd_cmd[eth_num];
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  // sequence counter
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 24);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 16);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 8);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 0);
  // protocol version, default 1.1
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 8);
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 0);
#if ETH_NEED_SET_COMMID
  // comm id
  send_buffer[offset++] = (unsigned char)(commid >> 24);
  send_buffer[offset++] = (unsigned char)(commid >> 16);
  send_buffer[offset++] = (unsigned char)(commid >> 8);
  send_buffer[offset++] = (unsigned char)(commid >> 0);
#else
  offset += 4;
#endif
  // data length
  send_buffer[offset++] = (unsigned char)(buff_len >> 24);
  send_buffer[offset++] = (unsigned char)(buff_len >> 16);
  send_buffer[offset++] = (unsigned char)(buff_len >> 8);
  send_buffer[offset++] = (unsigned char)(buff_len >> 0);

  memcpy(&send_buffer[offset], data, buff_len);
  offset += buff_len;
  if(module_data.master_sqe_counter[eth_num] == 0xffffffff)
  {
     module_data.master_sqe_counter[eth_num] = 0;
  }
  unsigned int send_len = trdp_proto->pack(send_buffer, offset, send_buffer, false);
  if (send_len == pack_len)
  {
    return send_buffer;
  }
  else
  {
    return NULL;
  }
}
unsigned char *Eth_board::send_pd_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len)
{
  unsigned pack_len = module_data.send_pd_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;
  
  if(pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = pack_len;
  }

  module_data.master_sqe_counter[eth_num]++;
  unsigned int offset = 0;
  // command
  send_buffer[offset++] = module_data.send_pd_cmd[eth_num];
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  // sequence counter
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 24);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 16);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 8);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 0);
  // protocol version, default 1.1
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 8);
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 0);
#if ETH_NEED_SET_COMMID
  // comm id
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 24);
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 16);
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 8);
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 0);
#else
  offset += 4;
#endif
  // data length
  send_buffer[offset++] = (unsigned char)(buff_len >> 24);
  send_buffer[offset++] = (unsigned char)(buff_len >> 16);
  send_buffer[offset++] = (unsigned char)(buff_len >> 8);
  send_buffer[offset++] = (unsigned char)(buff_len >> 0);

  memcpy(&send_buffer[offset], data, buff_len);
  offset += buff_len;
  if(module_data.master_sqe_counter[eth_num] == 0xffffffff)
  {
     module_data.master_sqe_counter[eth_num] = 0;
  }
  unsigned int send_len = trdp_proto->pack(send_buffer, offset, send_buffer, false);
  if (send_len == pack_len)
  {
    return send_buffer;
  }
  else
  {
    return NULL;
  }
}
#endif

#if (ETH_USE_MD)
unsigned char *Eth_board::send_md_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len, Ip ccu_ip)
{
  unsigned pack_len = module_data.send_md_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;

  if(pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = pack_len;
  }

  module_data.master_sqe_counter[eth_num]++;
  unsigned int offset = 0;
  // command
  send_buffer[offset++] = module_data.send_md_cmd[eth_num];
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);

  send_buffer[offset++] = ccu_ip[0];
  send_buffer[offset++] = ccu_ip[1];
  send_buffer[offset++] = ccu_ip[2];
  send_buffer[offset++] = ccu_ip[3];

  // sequence counter
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 24);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 16);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 8);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 0);
  // protocol version, default 1.1
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 8);
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 0);
#if ETH_NEED_SET_CONSISTID
  for (int i = 0; i < CONSISTID_COUNT; i++)
  {
    send_buffer[offset++] = paras->consistid[i];
  }
#else
  offset += 16;
#endif
  send_buffer[offset++] = (unsigned char)(paras->md_wait_time >> 24);
  send_buffer[offset++] = (unsigned char)(paras->md_wait_time >> 16);
  send_buffer[offset++] = (unsigned char)(paras->md_wait_time >> 8);
  send_buffer[offset++] = (unsigned char)(paras->md_wait_time >> 0);

  // data length
  send_buffer[offset++] = (unsigned char)(buff_len >> 24);
  send_buffer[offset++] = (unsigned char)(buff_len >> 16);
  send_buffer[offset++] = (unsigned char)(buff_len >> 8);
  send_buffer[offset++] = (unsigned char)(buff_len >> 0);

  memcpy(&send_buffer[offset], data, buff_len);
  offset += buff_len;

  unsigned int send_len = trdp_proto->pack(send_buffer, offset, send_buffer, false);
  if (send_len == pack_len)
  {
    return send_buffer;
  }
  else
  {
    return NULL;
  }
}
#endif

#if (ETH_UDP_TRDP)
unsigned char *Eth_board::send_udp_trdp_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len, unsigned upgrade_index)
{
  unsigned pack_len = module_data.send_udp_trdp_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;

  if(pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = pack_len;
  }

  module_data.master_sqe_counter[eth_num]++;
  unsigned int offset = 0;
  // command
  send_buffer[offset++] = module_data.send_udp_trdp_cmd[eth_num][upgrade_index];
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  // sequence counter
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 24);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 16);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 8);
  send_buffer[offset++] = (unsigned char)(module_data.master_sqe_counter[eth_num] >> 0);
  // protocol version, default 1.1
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 8);
  send_buffer[offset++] = (unsigned char)(paras->protol_version >> 0);
#if ETH_NEED_SET_COMMID
  // comm id
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 24);
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 16);
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 8);
  send_buffer[offset++] = (unsigned char)(paras->bms[eth_num].bms_commid >> 0);
#else
  offset += 4;
#endif
  // data length
  send_buffer[offset++] = (unsigned char)(buff_len >> 24);
  send_buffer[offset++] = (unsigned char)(buff_len >> 16);
  send_buffer[offset++] = (unsigned char)(buff_len >> 8);
  send_buffer[offset++] = (unsigned char)(buff_len >> 0);

  memcpy(&send_buffer[offset], data, buff_len);
  offset += buff_len;

  unsigned int send_len = trdp_proto->pack(send_buffer, offset, send_buffer, false);
  if (send_len == pack_len)
  {
    return send_buffer;
  }
  else
  {
    return NULL;
  }
}
#endif

#if (ETH_UDP_PASSTHROUGH)
unsigned char *Eth_board::send_udp_passthrough_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len)
{
  unsigned pack_len = module_data.send_udp_passthrough_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;

  if(pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = pack_len;
  }

  unsigned int offset = 0;
  // command
  send_buffer[offset++] = module_data.send_udp_passthrough_cmd[eth_num];
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  memcpy(&send_buffer[offset], data, buff_len);
  offset += buff_len;

  unsigned int send_len = trdp_proto->pack(send_buffer, offset, send_buffer, false);
  if (send_len == pack_len)
  {
    return send_buffer;
  }
  else
  {
    return NULL;
  }
}
#endif
#if (ETH_TCP_PASSTHROUGH)
unsigned char *Eth_board::send_tcp_passthrough_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len, unsigned upgrade_index)
{
  unsigned pack_len = module_data.send_tcp_passthrough_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;

  if(pack_len > send_max_len)
  {
    if(send_buffer != NULL)
    {
      delete[] send_buffer;
      send_buffer = NULL;
    }
    
    send_buffer = new unsigned char[pack_len];
    if (send_buffer == NULL)
    {
      send_max_len = 0;
      return NULL;
    }
    send_max_len = pack_len;
  }

  unsigned int offset = 0;
  // command
  send_buffer[offset++] = module_data.send_tcp_passthrough_cmd[eth_num][upgrade_index];
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  send_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  memcpy(&send_buffer[offset], data, buff_len);
  offset += buff_len;

  unsigned int send_len = trdp_proto->pack(send_buffer, offset, send_buffer, false);
  if (send_len == pack_len)
  {
    return send_buffer;
  }
  else
  {
    return NULL;
  }
}
#endif
Eth_board::~Eth_board()
{
}
