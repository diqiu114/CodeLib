#include "trdp_module.h"


Trdp_module_data::Trdp_module_data()
{
  sdt_en_cmd[0] = 0x04;
  sdt_en_cmd[1] = 0x84;
  sdt_en_rsp[0] = 0x02;
  sdt_en_rsp[1] = 0x82;
  cfg_cmd[0] = 0x05;
  cfg_cmd[1] = 0x85;
  cfg_rsp[0] = 0x06;
  cfg_rsp[1] = 0x86;
  send_pd_cmd[0] = 0x09;
  send_pd_cmd[1] = 0x89;
  rev_pd_cmd[0] = 0x07;
  rev_pd_cmd[1] = 0x87;
  sqe_counter[0] = 0;
  sqe_counter[1] = 0;

  sdt_en_pack_len = 57;
  sdt_en_rsp_pack_len = 10;
  sdt_en_rsp_delay = 2000;
  cfg_pack_len = 89;
  cfg_rsp_pack_len = 8;
  cfg_rsp_delay = 2000;
  mac_opt = 0x08;
  upgrade_conn_opt = 0x11;
  send_pd_non_data_bytes = 20;
  pd_pack_data_idx = 25;
  pd_pack_data_len_idx = 21;
}

Trdp_module::Trdp_module(Double_buffered_comm *handle, int train_num)
{
  uart = handle;
  Train_num_idx = 0;
//  Train_num_idx = train_num;
  trdp_proto = new Eth_module_proto();
}
bool Trdp_module::set_para(Trdp_para_t *trdp_paras)
{
	if(trdp_paras != NULL)
	{
		paras = trdp_paras;
		return true;
	} 
	return false;
}

Trdp_module::Trdp_module()
{
}

bool Trdp_module::reset(void)
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

void Trdp_module::set_rst_pin(Gpio_if *_gpio)
{
	if(_gpio != NULL)
  {
		rst_gpio = _gpio;
	}
}

bool Trdp_module::config(void)
{
  unsigned char ret = 0;
  unsigned char *buffer = NULL;

  for (int i = 0; i < TRDP_MODULE_ETH_PHY_CNT; i++)
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
  if (ret == CFG_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Trdp_module::sdt_enable(void)
{
  unsigned char ret = 0;
  unsigned char *buffer = NULL;

  for (int i = 0; i < TRDP_MODULE_ETH_PHY_CNT; i++)
  {
    buffer = sdt_buff_fill(i);

    if (buffer != NULL)
    {
      uart->send(buffer, module_data.sdt_en_pack_len);

      delete[] buffer;
      buffer = NULL;
      // wait receive data
      if (received_data(module_data.sdt_en_rsp_delay))
      {
        if (sdt_rsp_ok(i))
        {
          ret |= 1 << (i * 4);
        }
      }
    }
  }

  if (ret == CFG_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Trdp_module::cfg_rsp_ok(unsigned char eth_num)
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

unsigned char *Trdp_module::cfg_buff_fill(unsigned char eth_num)
{
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

  // MAC option
  pack_buffer[offset++] = module_data.mac_opt;
  // MAC
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].mac[0];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].mac[1];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].mac[2];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].mac[3];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].mac[4];
  pack_buffer[offset++] = paras[Train_num_idx].bms[eth_num].mac[5];

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
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[eth_num][0];
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[eth_num][1];
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[eth_num][2];
  pack_buffer[offset++] = paras[Train_num_idx].grp_addr_ip[eth_num][3];

  // skip ttdb port 2bytes
  offset += 2;

  // group port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 0);

  // ccu ip
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[0];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[1];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[2];
  pack_buffer[offset++] = paras[Train_num_idx].ccu[eth_num].ip[3];
  // ccu port
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].grp_port >> 0);

  // skip backup ccu ip and port 6bytes
//  offset += 6;
  // ccu ip
  pack_buffer[offset++] = paras[!Train_num_idx].ccu[eth_num].ip[0];
  pack_buffer[offset++] = paras[!Train_num_idx].ccu[eth_num].ip[1];
  pack_buffer[offset++] = paras[!Train_num_idx].ccu[eth_num].ip[2];
  pack_buffer[offset++] = paras[!Train_num_idx].ccu[eth_num].ip[3];
  // ccu port
  pack_buffer[offset++] = (unsigned char)(paras[!Train_num_idx].grp_port >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[!Train_num_idx].grp_port >> 0);
  // comid count
  pack_buffer[offset++] = 1;
  // comid
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu[eth_num].com_id >> 0);

  // skip other comid, 12bytes
  offset += 12;

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

bool Trdp_module::sdt_rsp_ok(unsigned char eth_num)
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

  unsigned int cfg_status = (pack_buffer[4] << 24) | (pack_buffer[5] << 16) | (pack_buffer[6] << 8) | pack_buffer[7];
  if ((pack_buffer[0] == module_data.sdt_en_rsp[eth_num]) && (cfg_status == 0))
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

unsigned int Trdp_module::rev_pd(unsigned char *data, unsigned int data_len)
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
  if ((buff_cnt == 0) || ((pack_buffer[0] != module_data.rev_pd_cmd[0]) && (pack_buffer[0] != module_data.rev_pd_cmd[1])))
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
  else if( pack_buffer[0] == module_data.rev_pd_cmd[1] )
  {
    data[0] = 1;
  }
  else
  {
    // error 
    data[0] = TRDP_MODULE_ETH_PHY_CNT;
  }

  // fill data
  memcpy(data+1, &pack_buffer[module_data.pd_pack_data_idx], read_data_len);
  
  delete[] pack_buffer;

  return read_data_len + 1;
}

bool Trdp_module::send_pd(unsigned char eth_num, unsigned char *buff, unsigned int buff_len)
{
  if ((buff == NULL) || (buff_len == 0) || (eth_num >= TRDP_MODULE_ETH_PHY_CNT))
  {
    return false;
  }

  bool ret = false;

  unsigned char *buffer = send_pd_buff_fill(eth_num, buff, buff_len);

  if (buffer != NULL)
  {
    ret = uart->send(buffer, module_data.send_pd_non_data_bytes + buff_len);

    delete[] buffer;
  }

  return ret;
}

unsigned char *Trdp_module::send_pd_buff_fill(unsigned char eth_num, unsigned char *data, unsigned int buff_len)
{
  unsigned pack_len = module_data.send_pd_non_data_bytes + buff_len;
  unsigned trdp_protocol_data_len = pack_len - 6;

  unsigned char *pack_buffer = new unsigned char[pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  module_data.sqe_counter[eth_num]++;
  unsigned int offset = 0;
  // command
  pack_buffer[offset++] = module_data.send_pd_cmd[eth_num];
  pack_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 8);
  pack_buffer[offset++] = (unsigned char)(trdp_protocol_data_len >> 0);
  // sequence counter
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[eth_num] >> 24);
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[eth_num] >> 16);
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[eth_num] >> 8);
  pack_buffer[offset++] = (unsigned char)(module_data.sqe_counter[eth_num] >> 0);
  // protocol version, default 1.1
  pack_buffer[offset++] = 0x01;
  pack_buffer[offset++] = 0x01;
  // comm id
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms[eth_num].com_id >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms[eth_num].com_id >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms[eth_num].com_id >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms[eth_num].com_id >> 0);
  // data length
  pack_buffer[offset++] = (unsigned char)(buff_len >> 24);
  pack_buffer[offset++] = (unsigned char)(buff_len >> 16);
  pack_buffer[offset++] = (unsigned char)(buff_len >> 8);
  pack_buffer[offset++] = (unsigned char)(buff_len >> 0);

  memcpy(&pack_buffer[offset], data, buff_len);
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

bool Trdp_module::received_data(int timeout)
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

unsigned char *Trdp_module::sdt_buff_fill(unsigned char eth_num)
{
  unsigned char *pack_buffer = new unsigned char[module_data.sdt_en_pack_len];

  if (pack_buffer == NULL)
  {
    return NULL;
  }

  memset(pack_buffer, 0, module_data.sdt_en_pack_len);
  unsigned data_len = module_data.sdt_en_pack_len - (ETH_MP_CRC_CALC_OFFSET + ETH_MP_CRC_BYTES);
  unsigned int offset = 0;
  pack_buffer[offset++] = module_data.sdt_en_cmd[eth_num];
  pack_buffer[offset++] = (unsigned char)(data_len >> 8);
  pack_buffer[offset++] = (unsigned char)(data_len >> 0);

  // fill smi
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms_smi >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms_smi >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms_smi >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].bms_smi >> 0);
  // version
  pack_buffer[offset++] = 0x01;
  pack_buffer[offset++] = 0x01;

  // consist id 15 bytes, default 0
  offset += 16;
  // safe topo count 4 bytes, default 0
  offset += 4;

  // smi receive count
  pack_buffer[offset++] = 0x01;

  // receive smi
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu_smi >> 24);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu_smi >> 16);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu_smi >> 8);
  pack_buffer[offset++] = (unsigned char)(paras[Train_num_idx].ccu_smi >> 0);

  // skip 0, 20bytes
  offset += 20;

  unsigned int send_len = trdp_proto->pack(pack_buffer, offset, pack_buffer);
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

Trdp_module::~Trdp_module()
{
}
