#include "single_trdp_module.h"


Trdp_single_module::Trdp_single_module(Double_buffered_comm *handle ,int train_num):Trdp_module(handle,train_num)
{
  uart = handle;
  Train_num_idx = 0;
  Train_num_idx = train_num;
  trdp_proto = new Eth_module_proto();
}

bool Trdp_single_module::set_para(Trdp_single_para_t *trdp_paras)
{
if(trdp_paras != NULL)
	{
		paras = trdp_paras;
		return true;
	} 
	return false;
}

bool Trdp_single_module::reset(void)
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
unsigned short Trdp_single_module::proto_buff_fill(unsigned char eth_num, unsigned char* data, unsigned int data_len,unsigned char* buff)
{
	unsigned short index = 0;
	unsigned short buff_len =  data_len +  20;
	if(realloc(buff,sizeof(unsigned char)* buff_len) == NULL)
	{
	  return 0;
	}
	unsigned int counter = module_data.sqe_counter[0]++;
	if(module_data.sqe_counter[0] > 65535)
	{
		module_data.sqe_counter[0] = 0;
	}
	
	buff[index ++] = 0xAA;
	buff[index ++] = 0x55;
	buff[index ++] = 0x01;
	buff[index ++] = 0x01;
	buff[index ++] = counter >> 8;
	buff[index ++] = counter;
	//Prevent duplication
	module_data.sqe_counter[0]--;
	buff[index ++] = paras[0].bms[eth_num].eth_ip[2];
	buff[index ++] = paras[0].ccu[0].ip[2];
	buff[index ++] = paras[0].grp_port >> 8;
	buff[index ++] = paras[0].grp_port;
	buff[index ++] = 0x8D;
	buff[index ++] = 0;
  buff[index ++] = (unsigned char)(data_len >> 8);
	buff[index ++] = (unsigned char)(data_len );
	index += 4;
	memcpy(buff + index, data,data_len);
	index += data_len;
	int crc = eth_proto->crc16(buff,index,0xffff);
	buff[index ++] = (unsigned char)(crc >> 8);
	buff[index ++] = (unsigned char)crc;
	
	return index;
}
void Trdp_single_module::set_rst_pin(Gpio_if * _gpio)
{
	if(_gpio != NULL)
  {
		rst_gpio = _gpio;
	}
}
bool Trdp_single_module::config(void)
{
	unsigned char ret = 0;
  unsigned char *buffer = NULL;

  for (int i = 0; i < TRDP_MODULE_SINGLE_PHY_CNT; i++)
  {
    buffer = cfg_buff_fill(i);
    if (buffer != NULL)
    {
      uart->send(buffer, module_data.cfg_pack_len);

      delete[] buffer;
      buffer = NULL;

      // wait receive data
      if (received_data(module_data.cfg_rsp_delay))
      {
        if (cfg_rsp_ok(i))
        {
          ret |= 1 << (i * 4);
        }
      }
    }
  }
  if (ret == CFG_SINGLE_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}
	
bool Trdp_single_module::send_pd(unsigned char eth_num, unsigned char *buff, unsigned int buff_len)
{
	if ((buff == NULL) || (buff_len == 0) || (eth_num >= BMS_TRDP_ETH_CNT))
  {
    return false;
  }
  bool ret = false;
	unsigned char *buffer = new unsigned char[1];
	unsigned short len =  proto_buff_fill( eth_num, buff, buff_len,buffer);
	if(len == 0)
	{
		if(buffer != NULL)
		{
		 delete[] buffer;
		}
		return false;
	}
	buffer = send_pd_buff_fill(eth_num, buffer, len);
	if (buffer != NULL)
	{
		ret = uart->send(buffer, module_data.send_pd_non_data_bytes + len);
		delete[] buffer;
	}
  return ret;
}
unsigned int Trdp_single_module::rev_pd(unsigned char* data, unsigned int data_len)
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

  unsigned char *pack_buffer = new unsigned char[rev_cnt];
  if (pack_buffer == NULL)
  {
    return 0;
  }
  memset(pack_buffer, 0, rev_cnt);

  unsigned int buff_cnt = uart->read(pack_buffer, rev_cnt);
  if (buff_cnt != rev_cnt)
  {
    delete[] pack_buffer;
    return 0;
  }

  // check pack
  buff_cnt = trdp_proto->unpack(pack_buffer, buff_cnt, pack_buffer);
  if ((buff_cnt == 0) || ((pack_buffer[0] != module_data.rev_pd_cmd[0]) ))
  {
    delete[] pack_buffer;
    return 0;
  }

  unsigned int read_data_len = (unsigned int)((pack_buffer[module_data.pd_pack_data_len_idx] << 24) 
                                              | (pack_buffer[module_data.pd_pack_data_len_idx + 1] << 16) 
                                              | (pack_buffer[module_data.pd_pack_data_len_idx + 2] << 8) 
                                              | (pack_buffer[module_data.pd_pack_data_len_idx + 3] << 0));
  if (data_len != 0)
  {
    read_data_len = read_data_len > data_len ? data_len : read_data_len;
  }

  // fill eth number
  if( pack_buffer[0] == module_data.rev_pd_cmd[0] )
  {
    data[0] = 0;
  }
  else
  {
    // error 
    data[0] = TRDP_MODULE_SINGLE_PHY_CNT;
  }

  // fill data
  memcpy(data+1, &pack_buffer[module_data.pd_pack_data_idx], read_data_len);
  
  delete[] pack_buffer;

  return read_data_len + 1;
}
unsigned char *Trdp_single_module::cfg_buff_fill(unsigned char eth_num)
{
	int comid_cnt = 1;
  unsigned char *pack_buffer = new unsigned char[module_data.cfg_pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  memset(pack_buffer, 0, module_data.cfg_pack_len);
  unsigned data_len = module_data.cfg_pack_len - (ETH_MP_CRC_CALC_OFFSET + ETH_MP_CRC_BYTES);
  unsigned int offset = 0;
  pack_buffer[offset++] = module_data.cfg_cmd[eth_num];
  pack_buffer[offset++] = (unsigned char)(data_len >> 8);
  pack_buffer[offset++] = (unsigned char)(data_len >> 0);

	offset += 7;
	eth_num = Train_num_idx;
	Train_num_idx = 0;

  // eth ip
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_ip[0];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_ip[1];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_ip[2];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_ip[3];
  // eth gateway
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_gateway[0];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_gateway[1];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_gateway[2];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_gateway[3];
  // eth mask
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_mask[0];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_mask[1];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_mask[2];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].eth_mask[3];
  // skip dns, ttdb config, 10 bytes
  offset += 10;

  //  receive group ip
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[0];
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[1];
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[2];
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[3];

  // skip ttdb port 2bytes
  offset += 2;

  // group port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 0);

  eth_num = 0;

  // ccu1 ip
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[0];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[1];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[2];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[3];
  // ccu port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 0);

// skip backup ccu ip and port 6bytes
//  offset += 6;
// ccu2 ip
  eth_num = 1;
  comid_cnt = 2;
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[0];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[1];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[2];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[3];
  // ccu port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 0);
	eth_num = 0;
  // comid count
  pack_buffer[offset++] = comid_cnt;
  // comid
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 0);

  eth_num = 1;
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 0);
  offset += 8;

  // program upgrade connection options
  pack_buffer[offset++] = module_data.upgrade_conn_opt;
  pack_buffer[offset++] = paras[Train_num_idx].upgrade_ip[0];
  pack_buffer[offset++] = paras[Train_num_idx].upgrade_ip[1];
  pack_buffer[offset++] = paras[Train_num_idx].upgrade_ip[2];
  pack_buffer[offset++] = paras[Train_num_idx].upgrade_ip[3];
  // destination port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].upgrade_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].upgrade_port >> 0);
  // source port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].upgrade_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].upgrade_port >> 0);

  // skip other connection config 8bytes
  offset += 8;

  unsigned int send_len = trdp_proto->pack(pack_buffer, offset, pack_buffer);
  if (send_len == module_data.cfg_pack_len)
  {
    return pack_buffer;
  }
  else
  {
    delete[] pack_buffer;
    return NULL;
  }
}
unsigned char *Trdp_single_module::send_pd_buff_fill(unsigned char eth_num, unsigned char* data, unsigned int buff_len)
{
	unsigned pack_len = module_data.send_pd_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;

  unsigned char *pack_buffer = new unsigned char[pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  module_data.sqe_counter[0]++;
  unsigned int offset = 0;
  // command
  pack_buffer[offset++] = module_data.send_pd_cmd[0];
  pack_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  pack_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  // sequence counter
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[0] >> 24);
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[0] >> 16);
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[0] >> 8);
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[0] >> 0);
  // protocol version, default 1.1
  pack_buffer[offset++] = 0x01;
  pack_buffer[offset++] = 0x01;
  // comm id
  pack_buffer[offset++] = (unsigned char)(paras[0].bms[Train_num_idx].com_id >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[0].bms[Train_num_idx].com_id >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[0].bms[Train_num_idx].com_id >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[0].bms[Train_num_idx].com_id >> 0);
  // data length
  pack_buffer[offset++] = (unsigned char)(buff_len >> 24);
  pack_buffer[offset++] = (unsigned char)(buff_len >> 16);
  pack_buffer[offset++] = (unsigned char)(buff_len >> 8);
  pack_buffer[offset++] = (unsigned char)(buff_len >> 0);

  memcpy(&pack_buffer[offset], data, buff_len);
	delete[]data;
  offset += buff_len;

  unsigned int send_len = trdp_proto->pack(pack_buffer, offset, pack_buffer);
  if (send_len == pack_len)
  {
    return pack_buffer;
  }
  else
  {
    delete[] pack_buffer;
    return NULL;
  }
}
bool Trdp_single_module::cfg_rsp_ok(unsigned char eth_num)
{
	unsigned char *pack_buffer = new unsigned char[module_data.cfg_rsp_pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  memset(pack_buffer, 0, module_data.cfg_rsp_pack_len);

  unsigned Pack_cnt = uart->read(pack_buffer, module_data.cfg_rsp_pack_len);
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

  if (pack_buffer[0] == module_data.cfg_rsp[eth_num])
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
bool Trdp_single_module::received_data(int timeout)
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

  DELAY_MS(2);
  return ret;
}


Trdp_single_module::~Trdp_single_module()
{

}
