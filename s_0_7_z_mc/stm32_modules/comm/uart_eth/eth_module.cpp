#include "eth_module.h"

Eth_module::Eth_module(UART_HandleTypeDef* handle, unsigned int buffer_size, uart_idle_callback callback)
            :Uart_tranceiver(handle, buffer_size, callback)
{
  eth_module_proto = new Eth_module_proto();
}

bool Eth_module::reset(void)
{
  if( rst_pin_port == NULL )
  {
    return false;
  }

  HAL_GPIO_WritePin(rst_pin_port, rst_pin, GPIO_PIN_SET);
  DELAY_MS(1);
  HAL_GPIO_WritePin(rst_pin_port, rst_pin, GPIO_PIN_RESET);
  DELAY_MS(600);
  HAL_GPIO_WritePin(rst_pin_port, rst_pin, GPIO_PIN_SET);
  DELAY_MS(1500);

  return true;
}

void Eth_module::set_rst_pin(GPIO_TypeDef *GPIOx, unsigned short GPIO_Pin)
{
  rst_pin_port = GPIOx;
  rst_pin = GPIO_Pin;
}

bool Eth_module::config(Eth_Module_Cfg* cfg, char mode)
{
  unsigned char* pack_buffer = new unsigned char[ETH_MODULE_CFG_PACK_BYTES];

  if( pack_buffer == NULL )
  {
    return false;
  }
  
  memset(pack_buffer, 0, ETH_MODULE_CFG_PACK_BYTES);
  
  unsigned int offset = 0;
  pack_buffer[offset++] = ETH_MODULE_CMD_CFG;
  pack_buffer[offset++] = (unsigned char)(ETH_MODULE_CFG_DATA_BYTES>>8);
  pack_buffer[offset++] = (unsigned char)(ETH_MODULE_CFG_DATA_BYTES>>0);
  
  unsigned int src_info_len = sizeof(cfg->ip) + sizeof(cfg->gateway) + sizeof(cfg->mask);
  memcpy(pack_buffer + ETH_MODULE_IP_IDX , cfg->ip, src_info_len);
  if(mode == ETH_MODE_TCP)
  {
    pack_buffer[ETH_MODULE_MODE_IDX] = ETH_MODULE_MODE_CLIENT;
  }
  else if(mode == ETH_MODE_UDP)
  {
    pack_buffer[ETH_MODULE_MODE_IDX] = ETH_MODULE_MODE_UDP;
  }

  unsigned int dest_info_len = (sizeof(cfg->dest_ip1) + sizeof(cfg->dest_port1) + sizeof(cfg->src_port1)) * 2;
  
  memcpy(pack_buffer + ETH_MODULE_DEST_IP1_IDX , cfg->dest_ip1, dest_info_len);

  unsigned send_len = eth_module_proto->pack(pack_buffer, ETH_MODULE_CFG_DATA_BYTES + offset, pack_buffer);
  
  send(pack_buffer, send_len);

  if( received_data(ETH_MODULE_RET_TIMEOUT_MAX) )
  {
    DELAY_MS(2);
    unsigned Pack_cnt = read_all(pack_buffer);
    if( Pack_cnt == 0 )
    {
      delete []pack_buffer;
      return false;
    }

    unsigned data_cnt = eth_module_proto->unpack(pack_buffer, Pack_cnt, pack_buffer);
    if( data_cnt == 0 )
    {
      delete []pack_buffer;
      return false;
    }    

    if( pack_buffer[ETH_MODULE_CFG_RESULT_IDX] == ETH_MODULE_CFG_SUC )
    {
      delete []pack_buffer;

      return true;
    }
    else
    {
      delete []pack_buffer;
      return false;
    }
  }
  else
  {
    delete []pack_buffer;
    return false;
  }
}

bool Eth_module::send_data(Eth_Data* s_data)
{
  bool ret = false;

  unsigned int pack_bffer_size = s_data->data_cnt + ETH_MODULE_NON_DATA_BYTES;
  unsigned char* pack_buffer = new unsigned char[pack_bffer_size];

  if( pack_buffer == NULL )
  {
    ret = false;
    return ret;
  }

  memset(pack_buffer, 0, pack_bffer_size);
  unsigned int offset = 0;
  pack_buffer[offset++] = s_data->cmd;
  pack_buffer[offset++] = (unsigned char)(s_data->data_cnt>>8);
  pack_buffer[offset++] = (unsigned char)(s_data->data_cnt>>0);

  memcpy(pack_buffer + offset, s_data->data, s_data->data_cnt);

  unsigned int s_bytes = eth_module_proto->pack(pack_buffer, s_data->data_cnt + offset, pack_buffer);

  ret = send(pack_buffer, s_bytes);

  delete []pack_buffer;

  return ret;
}

bool Eth_module::receive(Eth_Data* r_data, unsigned int timeout)
{
  if( received_data(timeout) )
  {
    unsigned char* pack_buffer = new unsigned char[buffer_size()];
    memset(pack_buffer, 0, buffer_size());

    DELAY_MS(5);
    
    unsigned int pack_cnt = read_all(pack_buffer);
    if( pack_cnt == 0 )
    {
      delete []pack_buffer;
      return false;
    }

    unsigned int data_cnt = eth_module_proto->unpack(pack_buffer, pack_cnt, pack_buffer);
    if( data_cnt > 0  )
    {
      r_data->cmd = pack_buffer[0];
      memcpy(r_data ->data, pack_buffer + 3, data_cnt - 3);
      r_data->data_cnt = ( pack_buffer[1] << 8 ) | pack_buffer[2];

      delete []pack_buffer;
      return true;;
    }
    else
    {
      delete []pack_buffer;
      return false;
    }
  }
  else
  {
    return false;
  }
}
bool Eth_module::get_data(Eth_Data* r_data)
{
 
  if (r_data->data == NULL)
  {
    return false;
  }

  unsigned int rev_cnt = this->data_cnt();
  if (rev_cnt == 0)
  {
    return false;
  }

  unsigned char *pack_buffer = new unsigned char[rev_cnt];
  if (pack_buffer == NULL)
  {
    return false;
  }

  memset(pack_buffer, 0, rev_cnt);

  unsigned int buff_cnt = this->read_out(pack_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    delete[] pack_buffer;
    return 0;
  }

  unsigned int data_cnt = eth_module_proto->unpack(pack_buffer, buff_cnt, pack_buffer);
  if( data_cnt > 0  )
  {
    r_data->cmd = pack_buffer[0];
    memcpy(r_data ->data, pack_buffer + 3, data_cnt - 3);
    r_data->data_cnt = ( pack_buffer[1] << 8 ) | pack_buffer[2];

    delete []pack_buffer;
    return true;;
  }
  else
  {
    delete []pack_buffer;
    return false;
  }
}
bool Eth_module::received_data(int timeout)
{
  bool ret = true;
  while( data_cnt() == 0 )
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

Eth_module::~Eth_module()
{

}
