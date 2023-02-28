#include "mvb_module.h"

Mvb_module::Mvb_module(Double_buffered_comm* handle,unsigned char train_num)
{
  send_max_len = 0;
  send_buff = NULL;
  read_buff = NULL;
  is_first = true;
  mvb_module_proto = new MVB_module_proto();
  usart = handle;
  Train_num_idx = train_num;
}

bool Mvb_module::reset(void)
{
  if( rst_gpio == NULL )
  {
    return false;
  }

  rst_gpio->set_hi();
  DELAY_MS(1);
  rst_gpio->set_low();
  DELAY_MS(600);
  rst_gpio->set_hi();
  DELAY_MS(1500);
  
  is_first = true;

  return true;
}

void Mvb_module::set_rst_pin(Gpio_if * _gpio)
{
  if(_gpio != NULL)
  {
     rst_gpio = _gpio;
  }
}

bool Mvb_module::config(Mvb_module_cfg* cfg, unsigned int timeout)
{
  if(send_max_len < MVB_MODULE_CFG_BYTES)
  {
    if( send_buff != NULL )
    {
      delete []send_buff;
      send_buff = NULL;
    }
    send_buff = new unsigned char[MVB_MODULE_CFG_BYTES];
    if(send_buff == NULL )
    {
      send_max_len = 0;
      return false;
    }
    send_max_len = MVB_MODULE_CFG_BYTES;
  }
  memset(send_buff, 0, MVB_MODULE_CFG_BYTES);

  unsigned int offset = 0;

  send_buff[offset++] = MVB_MODULE_CMD_CFG;
  send_buff[offset++] = (unsigned char)(cfg->device_addr >> 8);
  send_buff[offset++] = (unsigned char)(cfg->device_addr >> 0);
  send_buff[offset++] = cfg->dest_port_cnt;

  memcpy(&send_buff[offset], cfg->dest_port, sizeof(cfg->dest_port));
  offset += sizeof(cfg->dest_port);

  offset += MVB_MODULE_CFG_RES_BYTES;

  send_buff[offset++] = cfg->src_port_cnt;

  memcpy(&send_buff[offset], cfg->src_port, sizeof(cfg->src_port));
  offset += sizeof(cfg->src_port);
  offset += MVB_MODULE_CFG_RES_BYTES;
	
  unsigned int s_bytes = mvb_module_proto->pack(send_buff, offset, send_buff, false);

  usart->send(send_buff, s_bytes);

  if( received_data(timeout) )
  {
    DELAY_MS(2);
    unsigned Pack_cnt = usart->read_all(send_buff);
    if( Pack_cnt == 0 || Pack_cnt > MVB_MODULE_CFG_BYTES)
    {
      return false;
    }

    unsigned data_cnt = mvb_module_proto->unpack(send_buff, Pack_cnt, send_buff);
    if( data_cnt == 0 )
    {
      return false;
    }    

    if( send_buff[MVB_MODULE_CFG_RESULT_IDX] == MVB_MODULE_CFG_SUC )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool Mvb_module::send_data(Mvb_data* s_data)
{
  bool ret = true;
  unsigned char pack_len = s_data->data_cnt + sizeof(s_data->cmd) + 
                           sizeof(s_data->dest_addr) + sizeof(s_data->sc) + 
                           sizeof(s_data->inc_offset) + MVB_MP_NON_DATA_LEN;

  if(send_max_len < pack_len)
  {
    if( send_buff != NULL )
    {
      delete []send_buff;
      send_buff = NULL;
    }
    send_buff = new unsigned char[pack_len];
    if(send_buff == NULL )
    {
      send_max_len = 0;
      return false;
    }
    send_max_len = pack_len;
  }
  memset(send_buff, 0, pack_len);

  unsigned offset = 0;
  send_buff[offset++] = MVB_MODULE_CMD_SEND;
  send_buff[offset++] = s_data->sc;
  send_buff[offset++] = s_data->inc_offset;
  send_buff[offset++] = (unsigned char)(s_data->dest_addr>>8);
  send_buff[offset++] = (unsigned char)(s_data->dest_addr>>0);
  memcpy(&send_buff[offset], s_data->data, s_data->data_cnt);
  offset += s_data->data_cnt;

  unsigned int s_bytes = mvb_module_proto->pack(send_buff, offset, send_buff, false);

  ret = usart->send(send_buff, s_bytes);
  
  return ret;
}

bool Mvb_module::receive(unsigned short dest_addr, unsigned int recv_period, MVB_recv_switch recv_switch, Mvb_data* r_data, unsigned int timeout)
{
  if(is_first)
  {
    is_first = false;
    if( !send_read_req(recv_period, recv_switch) )
    {
      return false;
    }
  }
  if( received_data(timeout) )
  {
    DELAY_MS(2);

    if(read_buff == NULL)
    {
      read_buff = new unsigned char[usart->buffer_size()];
      if( read_buff == NULL )
      {
        return false;
      }
    }
    memset(read_buff, 0, usart->buffer_size());

    unsigned int pack_cnt = usart->read_all(read_buff);
    if( pack_cnt == 0 )
    {
      return false;
    }

    unsigned int data_cnt = mvb_module_proto->unpack(read_buff, pack_cnt, read_buff);
    if( data_cnt > 0 )
    {
      
      bool cmd_correct = ( read_buff[MVB_MODULE_CMD_IDX] == MVB_MODULE_CMD_READ_RET );
      bool sc_correct = ( (read_buff[MVB_MODULE_SC_IDX] == MVB_MODULE_SC_ALL_CH_CORRET) || 
                          (read_buff[MVB_MODULE_SC_IDX] == MVB_MODULE_SC_CHA_CORRET) || 
                          (read_buff[MVB_MODULE_SC_IDX] == MVB_MODULE_SC_CHB_CORRET) );
      
      bool addr_correct = ( read_buff[MVB_MODULE_ADDR_HI_IDX] == (unsigned char)(dest_addr>>8) )
                           && ( read_buff[MVB_MODULE_ADDR_LO_IDX] == (unsigned char)(dest_addr>>0) );
      if( (cmd_correct) && (sc_correct) && (addr_correct) )
      {
        r_data->cmd = read_buff[MVB_MODULE_CMD_IDX];
        r_data->sc  = read_buff[MVB_MODULE_SC_IDX];
        r_data->dest_addr = (read_buff[MVB_MODULE_ADDR_HI_IDX]<<8) | read_buff[MVB_MODULE_ADDR_LO_IDX];
        r_data->data_cnt = data_cnt - MVB_MODULE_DATA_IDX;
        memcpy(r_data->data, &read_buff[MVB_MODULE_DATA_IDX], r_data->data_cnt);  
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool Mvb_module::send_read_req(unsigned int recv_period, MVB_recv_switch recv_switch)
{
  bool ret = true;
  
  if(send_max_len < MVB_MODULE_SEND_READ_REQ_BYTES)
  {
    if( send_buff != NULL )
    {
      delete []send_buff;
      send_buff = NULL;
    }
    send_buff = new unsigned char[MVB_MODULE_SEND_READ_REQ_BYTES];
    if(send_buff == NULL )
    {
      send_max_len = 0;
      return false;
    }
    send_max_len = MVB_MODULE_SEND_READ_REQ_BYTES;
  }
  
  memset(send_buff, 0, MVB_MODULE_SEND_READ_REQ_BYTES);

  unsigned offset = 0;
  send_buff[offset++] = MVB_MODULE_CMD_READ;
  send_buff[offset++] = recv_period;
  send_buff[offset++] = recv_switch;

  unsigned int s_bytes = mvb_module_proto->pack(send_buff, offset, send_buff, false);

  ret = usart->send(send_buff, s_bytes);

  return ret;
}

bool Mvb_module::received_data(int timeout)
{
  bool ret = true;
  while( usart->data_available() == 0 )
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

Mvb_module::~Mvb_module()
{

}
