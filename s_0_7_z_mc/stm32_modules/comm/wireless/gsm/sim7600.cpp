#include "sim7600.h"
#include "modules_def.h"
#include <stdlib.h>
#include <string>
using namespace std;
/**
 * @brief Construct a new Sim 7 6 0 0:: Sim 7 6 0 0 object
 * 
 * @param _at_comm AT command class pointer
 * @param _power_pin sim7600 power PIN
 * @param _rst_pin sim7600 reset PIN
 * @param command_buff_size command buffer size
 */
Sim7600::Sim7600(At_command *_at_comm, Gpio_if *_power_pin, Gpio_if *_rst_pin, int command_buff_size)
{
  at_comm = _at_comm;
  power_pin = _power_pin;
  rst_pin = _rst_pin;

  buff_size = command_buff_size;
  buff = new char[buff_size];
  if (buff != NULL)
  {
    memset(buff, 0, buff_size);
  }

  cid = SIM7600_CID;

  transmission_mode = SIM_COMMAND_MODE;

  protocol = SIM_PROTOCOL_TCP;
  server_ip = NULL;
  server_port = 0;
  link_num = SIM7600_LINK_NUM;
}

Sim7600::~Sim7600()
{
  if (at_comm != NULL)
  {
    delete at_comm;
    at_comm = NULL;
  }

  if (power_pin != NULL)
  {
    delete power_pin;
    power_pin = NULL;
  }

  if (rst_pin != NULL)
  {
    delete rst_pin;
    rst_pin = NULL;
  }

  if (buff != NULL)
  {
    delete[] buff;
    buff = NULL;
  }
}

/**
 * @brief sim7600 power up
 * 
 */
void Sim7600::power_up(void)
{
  power_pin->set_hi();
  DELAY_MS(1500);

  power_pin->set_low();
  DELAY_MS(SIM7600_POWER_UP_DELAY);
}

/**
 * @brief sim 7600 reset
 * 
 * @return true reset ok
 * @return false reset failed
 */
bool Sim7600::reset(void)
{
  if (rst_pin != NULL)
  {
    rst_pin->set_hi();
    DELAY_MS(100);

    rst_pin->set_low();
    DELAY_MS(100);

    return true;
  }

  return false;
}

/**
 * @brief sim7600 ready
 * 
 * @return true response AT command ok
 * @return false not response
 */
bool Sim7600::ready(void)
{
  bool ret = false;
  ret = at_comm->set_echo(false);
  ret &= at_comm->send_until("AT\r\n", "OK");
  return ret;
}
/**
 * @brief SIM card ready
 * 
 * @return true ready 
 * @return false not ready
 */
bool Sim7600::sim_card_ready(void)
{
  return at_comm->send_until("AT+CPIN?\r\n", "READY");
}

/**
 * @brief query sim7600 network register status
 * 
 * @return Sim7600_reg_status current status
 */
Sim7600_reg_status Sim7600::register_status(void)
{
  // TODO : send command to read status
  return SIM_UNKOWN;
}

/**
 * @brief query sim7600 already registed
 * 
 * @return true registed
 * @return false not register
 */
bool Sim7600::registed(void)
{
  return at_comm->send_until("AT+CREG?\r\n", "1", "5");
}

/**
 * @brief query sim7600 signal quality
 * 
 * @return unsigned char signal quality level 0-31
 */
unsigned char Sim7600::signal_quality(void)
{
  char rev_buf[20] = {0};
  unsigned char csq_val = 0;
  unsigned short csq_len = 0;
  at_comm->send_receive("AT+CSQ\r\n", rev_buf, 500);
  string rev_str = (char *)rev_buf;
  string csq;
  csq_len = rev_str.find_first_of(',') - rev_str.find_first_of(':') - 1;
  csq = rev_str.substr(rev_str.find_first_of(':')+1, csq_len);
  csq_val = atoi(csq.data());  
  return csq_val;
}

/**
 * @brief query sim7600 singal quality ok
 * 
 * @return true signal quality ok
 * @return false signal quality NG
 */
bool Sim7600::signal_quality_ok(void)
{
  return at_comm->send_until("AT+CSQ\r\n", "2", "1");
}

/**
 * @brief query current operator
 * 
 * @return true ok
 * @return false failed
 */
bool Sim7600::curr_operator(void)
{
  return at_comm->send_until("AT+COPS?\r\n", "OK");
}

/**
 * @brief config pdp context
 * 可以理解为数据通讯配置
 * @param char cid, default is 0
 * @param pdp_type "IP" or others
 * @return true config ok
 * @return false config failed
 */
bool Sim7600::config_pdp_context(unsigned char _cid, const char *pdp_type)
{
  if ((buff == NULL) || (pdp_type == NULL))
  {
    return false;
  }

  cid = _cid;
  memset(buff, 0, buff_size);
  sprintf(buff, "AT+CGDCONT=%d,\"%s\",\"CMNET\"\r\n", cid, pdp_type);

  return at_comm->send_until(buff, "OK");
}

/**
 * @brief active pdp context
 * 
 * @return true active ok
 * @return false active failed
 */
bool Sim7600::active_pdp_context(void)
{
  if (buff == NULL)
  {
    return false;
  }

  memset(buff, 0, buff_size);
  sprintf(buff, "AT+CSOCKSETPN=%d\r\n", cid);

  return at_comm->send_until(buff, "OK");
}

/**
 * @brief open gprs
 * 
 * @return true open ok 
 * @return false open failed
 */
bool Sim7600::net_open(void)
{
  // close net connection before open
  net_close();
  return at_comm->send_until("AT+NETOPEN\r\n", "OK");
}

/**
 * @brief get data fromm sim7600 buffer manually
 * 
 * @param manu_ret manually or auto
 * @return true set ok
 * @return false set failed
 */
bool Sim7600::get_data_manually(bool manu_ret)
{
  if (manu_ret)
  {
    return at_comm->send_until("AT+CIPRXGET=1\r\n", "OK");
  }
  else
  {
    return at_comm->send_until("AT+CIPRXGET=0\r\n", "OK");
  }
}

/**
 * @brief close gprs
 * 
 * @return true ok
 * @return false failed
 */
bool Sim7600::net_close(void)
{
  return at_comm->send_until("AT+NETCLOSE\r\n", "OK", NULL, 500);
}

/**
 * @brief get ip adress after open net
 * 
 * @param ret_ip data pointer
 * @return true ok
 * @return false failed
 */
bool Sim7600::ip_addr(const char *ret_ip)
{
  if (ret_ip == NULL)
  {
    return at_comm->send_until("AT+IPADDR\r\n", "OK");
  }
  else
  {
    // TODO: get ip and return
    return false;
  }
}
/**
 * @brief get real time clock
 * 
 * @param ret_str ntp time string
 * @return return ntp time string len
 */
int Sim7600::get_ntp_time(char *ret_str,  const char *ntp_server)
{
  int ret = 0;
  char rtc_ret[50] = {0};
  string time_str = NULL;
  int rev_len = 0;

  sprintf(rtc_ret, "AT+CNTP=%s, 32\r\n", ntp_server);//sprintf(rtc_ret, "AT+CNTP=\"ntp1.aliyun.com\", 32\r\n");
  ret = at_comm->send_until(rtc_ret, "OK");
  if(ret)
  {
    at_comm->send_until("AT+CNTP\r\n", "OK");
  }  
  memset(rtc_ret, 0, 50);
  if(at_comm->send_receive_until("AT+CCLK?\r\n", rtc_ret))
  {
    time_str = rtc_ret;
    rev_len = time_str.find_last_of('\"') - time_str.find_first_of('\"') - 1;
    time_str = time_str.substr(time_str.find_first_of('\"')+1, rev_len);
    ret = time_str.size();
    time_str.copy(ret_str, ret);
  }
  return ret;
}
/**
 * @brief connect to tcp server
 * 
 * @param ip server or ip
 * @param port server port
 * @param _link_num link number
 * @return true connect ok
 * @return false connect failed
 */
bool Sim7600::tcp_connect(const char *ip, unsigned short port, char _link_num)
{
  if ((buff == NULL) || (ip == NULL))
  {
    return false;
  }
  link_num = _link_num;

  memset(buff, 0, buff_size);
  sprintf(buff, "AT+CIPOPEN=%d,\"TCP\",\"%s\",%d\r\n", link_num, ip, port);

  if (at_comm->send_until(buff, "OK", NULL, 2000))
  {
    protocol = SIM_PROTOCOL_TCP;
    return true;
  }

  return false;
}

/**
 * @brief connect to udp server
 * 
 * @param ip server or ip
 * @param port server port
 * @param local_port device port
 * @param _link_num link number
 * @return true connect ok
 * @return false connect failed
 */
bool Sim7600::udp_connect(const char *ip, unsigned short port, unsigned short local_port, char _link_num)
{
  if ((buff == NULL) || (ip == NULL))
  {
    return false;
  }

  link_num = _link_num;
  memset(buff, 0, buff_size);
  sprintf(buff, "AT+CIPOPEN=%d,\"UDP\",\"%s\",%d,%d\r\n", link_num, ip, port, local_port);

  if (at_comm->send_until(buff, "OK", NULL, 2000))
  {
    if (server_ip != NULL)
    {
      delete[] server_ip;
      server_ip = NULL;
    }

    server_ip = new char[strlen(ip)];
    if (server_ip == NULL)
    {
      return false;
    }
    strcpy(server_ip, ip);
    server_port = port;
    protocol = SIM_PROTOCOL_UDP;
    return true;
  }

  return false;
}

/**
 * @brief disconnect from tcp/udp server
 * 
 * @return true ok
 * @return false failed
 */
bool Sim7600::tcp_udp_disconnect(void)
{
  return at_comm->send_until("AT+CIPCLOSE\r\n", "OK");
}

// bool Sim7600::enter_transparent_mode(void)
// {
//   bool ret = false;

//   if (at_comm->send_until("AT+CIPMODE=1\r\n", "OK"))
//   {
//     transmission_mode = SIM_DATA_MODE;
//     ret = true;
//   }

//   return ret;
// }

// bool Sim7600::exit_transparent_mode(void)
// {
//   bool ret = false;

//   if (at_comm->send_until("+++", "OK"))
//   {
//     transmission_mode = SIM_COMMAND_MODE;
//     ret = true;
//   }

//   return ret;
// }

/**
 * @brief send data to server
 * 
 * @param data data pointer
 * @param data_len data length
 * @return true send ok
 * @return false send failed
 */
bool Sim7600::send(char *data, int data_len)
{
  if ((buff == NULL) || (data == NULL) || (data_len <= 0))
  {
    return false;
  }

  bool ret = false;
  memset(buff, 0, buff_size);

  if (transmission_mode == SIM_COMMAND_MODE)
  {
    if (protocol == SIM_PROTOCOL_TCP)
    {
      sprintf(buff, "AT+CIPSEND=%d,%d\r\n", link_num, data_len);
    }
    else // SIM_PROTOCOL_UDP
    {
      sprintf(buff, "AT+CIPSEND=%d,%d,\"%s\",%d\r\n", link_num, data_len, server_ip, server_port);
    }

    if (at_comm->send_until(buff, ">", NULL, 500))
    {
      ret = at_comm->send_until(data, data_len, "+CIPSEND", NULL, SIM7600_SEND_TIMEOUT_MS);
    }
  }
  else
  {
    // transparent mode no response after send data
    // NOTE: other server maybe response, need more test
    at_comm->send_until(data, data_len, "+CIPSEND", NULL, 0);
    ret = true;
  }

  return ret;
}

/**
 * @brief get data from sim7600 buffer
 * 
 * @param data data pinter 
 * @param data_len data length to be get
 * @return true ok
 * @return false no data or get data failed
 */
bool Sim7600::get_data(char *data, int data_len)
{
  bool ret = false;

  // read rest data length
  sprintf(buff, "AT+CIPRXGET=4,%d\r\n", link_num);
  at_comm->send_receive_until(buff, buff);
  // return string：0x0D 0x0A +CIPRXGET:4,<link_num>,<data_length>0x0D 0x0A 0x0D 0x0A OK
  char *p = strpbrk(buff, ",");
  if (p == NULL)
  {
    return false;
  }
  // 3 is data_length offset
  int rest_data_len = atoi(p + 3);
  if(rest_data_len == 0)
  {
    return false;
  }
  
  int read_data_len = rest_data_len;

  if (data_len != 0)
  {
    read_data_len = data_len > rest_data_len ? rest_data_len : data_len;
  }

  char *buffer = new char[read_data_len + SIM7600_MANUAL_READ_PREFIX_DATA_LEN];
  if (buffer == NULL)
  {
    return false;
  }

  memset(buff, 0, buff_size);

  sprintf(buff, "AT+CIPRXGET=2,%d,%d\r\n", link_num, read_data_len);
  // return data format: 0x0D 0x0A +CIPRXGET:2,<link_num>,<data_length>,<rest_data_length> 0x0D 0x0A <data>  OK
  if (at_comm->send_receive_until(buff, buffer))
  {
    const char delim[2] = {0x0D, 0x0A};

    // offset 2 for avoid first 0X0D 0X0A
    char *p = strpbrk(buffer + 2, delim);
    if(p != NULL)
    {
      memcpy(data, p+2, read_data_len);
      ret = true;
    }
    
  }

  delete[] buffer;
  return ret;
}

/**
 * @brief read a frame data from AT command buffer
 *        用于透传模式或自动获取数据模式
 * @param data data pointer
 * @param data_len data length to be read, 0 means read all
 * @return false no data or read error
 */
bool Sim7600::read_buffer(char *data, int data_len)
{
  bool ret = false;
  int buffer_data_len = at_comm->buffer_data_cnt();

  int read_len = data_len > buffer_data_len ? buffer_data_len : data_len;

  char *buffer = new char[read_len];
  if (buffer == NULL)
  {
    return false;
  }

  if (at_comm->read_buffer(buffer, read_len))
  {
    // 服务器自动返回的数据格式为：RECV FROM <ip> 0x0D 0x0A +IPD:<data_length> 0x0D 0x0A <data>
    // 字符串处理步骤：
    // 1.找到+IPD，将指针指向+IPD的开始(去掉前面IP等无用数据)
    // 2.查找到LF(0x0A)，确定数据的偏移
    // 3.将查找到的数据copy给返回的数据指针
    char *p = strpbrk(buffer, "+IPD");
    if (p != NULL)
    {
      char delim = 0x0A;
      int offset = strcspn(p, &delim);

      memcpy(data, &p[offset + 1], strlen(p) - (offset + 1));
      ret = true;
    }
  }

  delete[] buffer;

  return ret;
}

/**
 * @brief receive data from AT command buffer at fixed time
 *        用于透传模式或自动获取数据模式
 * @param data return data pointer
 * @param data_len data length to be read, 0 means read all
 * @param timeout receive timeout
 * @return false no data or read error
 */
bool Sim7600::read_buffer_until(char *data, int data_len, int timeout)
{
  bool ret = false;
  int buffer_data_len = at_comm->buffer_data_cnt();

  int read_len = data_len > buffer_data_len ? buffer_data_len : data_len;

  char *buffer = new char[read_len];
  if (buffer == NULL)
  {
    return false;
  }

  if (at_comm->read_buffer_until(buffer, read_len, timeout))
  {
    // 服务器自动返回的数据格式为：RECV FROM <ip> 0x0D 0x0A +IPD:<data_length> 0x0D 0x0A <data>
    // 字符串处理步骤：
    // 1.找到+IPD，将指针指向+IPD的开始(去掉前面IP等无用数据)
    // 2.查找到LF(0x0A)，确定数据的偏移
    // 3.将查找到的数据copy给返回的数据指针
    char *p = strpbrk(buffer, "+IPD");
    if (p != NULL)
    {
      char delim = 0x0A;
      int offset = strcspn(p, &delim);

      memcpy(data, &p[offset + 1], strlen(p) - (offset + 1));
      ret = true;
    }
  }

  delete[] buffer;

  return ret;
}
