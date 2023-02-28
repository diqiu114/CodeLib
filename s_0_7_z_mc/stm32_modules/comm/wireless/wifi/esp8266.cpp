#include "esp8266.h"
#include "modules_def.h"
#include "stdio.h"

Esp8266::Esp8266(At_command *_at_comm, Gpio_if *_rst_pin, int command_buff_size)
{
  at_comm = _at_comm;
  rst_pin = _rst_pin;

  buff_size = command_buff_size;
  buff = new char[buff_size];
  if (buff != NULL)
  {
    memset(buff, 0, buff_size);
  }

  transmission_mode = ESP_COMMAND_MODE;
}

Esp8266::~Esp8266()
{
  if (at_comm != NULL)
  {
    delete at_comm;
    at_comm = NULL;
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
 * @brief esp8266 ready
 * 
 * @return true ready
 * @return false not ready
 */
bool Esp8266::ready(void)
{
  return at_comm->send("AT\r\n", "OK");
}

/**
 * @brief hardware reset
 * 
 * @return true reset ok
 * @return false reset failed
 */
bool Esp8266::reset(void)
{
  bool ret = false;

  if (rst_pin != NULL)
  {
    rst_pin->set_low();
    DELAY_MS(1000);

    rst_pin->set_hi();
    DELAY_MS(2000);

    ret = true;
  }

  return ret;
}

/**
 * @brief software reset
 * 
 * @return true reset ok
 * @return false reset failed
 */
bool Esp8266::soft_reset(void)
{
  return at_comm->send("AT+RST\r\n", "OK");
}

/**
 * @brief set esp8266 work type
 * 
 * @param type work type
 * @param save save type to falsh
 * @return true set ok
 * @return false set failed
 */
bool Esp8266::set_type(Esp8266_type type, bool save)
{
  if (buff == NULL)
  {
    return false;
  }

  memset(buff, 0, buff_size);

  if (save)
  {
    sprintf(buff, "AT+CWMODE_DEF=%d\r\n", type);
  }
  else
  {
    sprintf(buff, "AT+CWMODE_CUR=%d\r\n", type);
  }

  return at_comm->send(buff, "OK");
}

/**
 * @brief config soft ap parameters
 * 
 * @param ssid wifi ssid
 * @param pwd access password
 * @param ch_id channel id
 * @param encry_method encryption method
 * @return true 
 * @return false 
 */
bool Esp8266::config_soft_ap(const char *ssid, const char *pwd, unsigned char ch_id, Esp8266_encry_method encry_method)
{
  return true;
}

/**
 * @brief search specific wifi
 * 
 * @param ssid wifi ssid
 * @return true search ok
 * @return false search failed
 */
bool Esp8266::search(const char *ssid)
{
  if ((buff == NULL) || (ssid == NULL))
  {
    return false;
  }

  memset(buff, 0, buff_size);

  sprintf(buff, "AT+CWLAP=\"%s\"\r\n", ssid);

  return at_comm->send_until(buff, "+CWLAP:(", NULL, 3000);
}

/**
 * @brief connect to wifi
 * 
 * @param ssid wifi ssid
 * @param pwd wifi password
 * @param save save to flash
 * @return true connect success
 * @return false connect failed
 */
bool Esp8266::connect(const char *ssid, const char *pwd, bool save)
{
  if ((buff == NULL) || (ssid == NULL))
  {
    return false;
  }

  memset(buff, 0, buff_size);

  if (save)
  {
    sprintf(buff, "AT+CWJAP_DEF=\"%s\",\"%s\"\r\n", ssid, pwd);
  }
  else
  {
    sprintf(buff, "AT+CWJAP_CUR=\"%s\",\"%s\"\r\n", ssid, pwd);
  }

  return at_comm->send_until(buff, "GOT IP", NULL, 10000);
}

/**
 * @brief disconnect from wifi
 * 
 * @return true disconnect ok
 * @return false disconnect error
 */
bool Esp8266::disconnect(void)
{
  return at_comm->send("AT+CWQAP\r\n", "OK");
}

/**
 * @brief set auto connect to wifi when esp8266 power-up
 * 
 * @param auto_conn auto connect or not
 * @return true set ok
 * @return false set failed
 */
bool Esp8266::set_auto_connect(bool auto_conn)
{
  if (auto_conn)
  {
    return at_comm->send("AT+CWAUTOCONN=1\r\n", "OK");
  }
  else
  {
    return at_comm->send("AT+CWAUTOCONN=0\r\n", "OK");
  }
}

/**
 * @brief get esp8266 connection status
 * 
 * @return Esp8266_conn_status current status
 */
Esp8266_conn_status Esp8266::status(void)
{
  if (buff == NULL)
  {
    return ESP_DISCONNECTED;
  }

  Esp8266_conn_status ret = ESP_DISCONNECTED;

  char str[10] = {0};
  memset(buff, 0, buff_size);
  if (at_comm->send_receive("AT+CIPSTATUS\r\n", buff))
  {
    sprintf(str, "STATUS:%d", ESP_CONNECTED);
    if (strstr(buff, str) != NULL)
    {
      ret = ESP_CONNECTED;
    }

    sprintf(str, "STATUS:%d", ESP_TCP_UDP_CONNECTED);
    if ((ret == ESP_DISCONNECTED) && (strstr(buff, str) != NULL))
    {
      ret = ESP_TCP_UDP_CONNECTED;
    }

    sprintf(str, "STATUS:%d", ESP_TCP_UDP_DISCONNECTED);
    if ((ret == ESP_DISCONNECTED) && (strstr(buff, str) != NULL))
    {
      ret = ESP_TCP_UDP_DISCONNECTED;
    }
  }

  return ret;
}

/**
 * @brief connect to tcp server
 * 
 * @param ip server ip
 * @param port server port
 * @param keep_alive keep alive timeout in seconds(0-7000)
 * @return true connect ok
 * @return false connect error
 */
bool Esp8266::tcp_connect(const char *ip, unsigned short port, unsigned short keep_alive)
{
  if ((buff == NULL) || (ip == NULL) || (port == NULL))
  {
    return false;
  }

  tcp_udp_disconnect();

  memset(buff, 0, buff_size);
  sprintf(buff, "AT+CIPSTART=\"TCP\",\"%s\",%d,%d\r\n", ip, port, keep_alive);

  return at_comm->send_until(buff, "CONNECT", NULL, 2000);
}

bool Esp8266::tcp_udp_disconnect(void)
{
  return at_comm->send("AT+CIPCLOSE\r\n", "OK");
}

/**
 * @brief connect to udp server
 * 
 * @param ip server ip
 * @param port server port
 * @param local_port device port
 * @param mode: 
 * ‣ 0: the destination peer entity of UDP will not change; this is the default setting.
 * ‣ 1: the destination peer entity of UDP can change once.
 * ‣ 2: the destination peer entity of UDP is allowed to change.
 * NOTE:To use <UDP mode> , <UDP local port> must be set first.
 * @return true connect ok
 * @return false connect error
 */
bool Esp8266::udp_connect(const char *ip, unsigned short port, unsigned short local_port, char mode)
{
  if ((buff == NULL) || (ip == NULL) || (port == NULL))
  {
    return false;
  }

  tcp_udp_disconnect();

  memset(buff, 0, buff_size);

  if (local_port == 0 && mode == 0)
  {
    sprintf(buff, "AT+CIPSTART=\"UDP\",\"%s\",%d\r\n", ip, port);
  }
  else
  {
    sprintf(buff, "AT+CIPSTART=\"UDP\",\"%s\",%d,%d,%d\r\n", ip, port, local_port, mode);
  }

  return at_comm->send_until(buff, "CONNECT", NULL, 2000);
}

/**
 * @brief send data to server
 * 
 * @param data data pointer
 * @param data_len data length
 * @return true send ok
 * @return false send failed
 */
bool Esp8266::send(char *data, int data_len)
{
  if ((buff == NULL) || (data == NULL) || (data_len <= 0))
  {
    return false;
  }

  bool ret = false;
  memset(buff, 0, buff_size);

  if (transmission_mode == ESP_COMMAND_MODE)
  {
    sprintf(buff, "AT+CIPSEND=%d\r\n", data_len);
    if (at_comm->send_until(buff, ">", NULL, 500))
    {
      ret = at_comm->send_until(data, data_len, "SEND OK", NULL, ESP8266_SEND_TIMEOUT_MS);
    }
  }
  else
  {
    // transparent mode no response after send data
    // NOTE: other server maybe response, need more test
    at_comm->send_until(data, data_len, "SEND OK", NULL, 0);
    ret = true;
  }

  return ret;
}

/**
 * @brief enter transparent data transmission mode
 * 
 * @return true enter success
 * @return false enter failed
 */
bool Esp8266::enter_transparent_mode(void)
{
  bool ret = true;

  ret = at_comm->send("AT+CIPMODE=1\r\n", "OK");

  ret = ret && at_comm->send("AT+CIPSEND\r\n", ">");

  if (ret)
  {
    transmission_mode = ESP_DATA_MODE;
  }

  return ret;
}

/**
 * @brief exit transparent data transmission mode
 * 
 * @return true enter success
 * @return false enter failed
 */
bool Esp8266::exit_transparent_mode(void)
{
  bool ret = at_comm->send("+++", "OK");

  if (ret && at_comm->send("AT+CIPMODE=0\r\n", "OK"))
  {
    transmission_mode = ESP_COMMAND_MODE;
    ret = true;
  }

  return ret;
}

/**
 * @brief ping server
 * 
 * @param ip target ip or address
 * @return true ping ok
 * @return false ping error
 */
bool Esp8266::ping(const char *ip)
{
  if ((buff == NULL) || (ip == NULL))
  {
    return false;
  }
  memset(buff, 0, buff_size);

  sprintf(buff, "AT+PING=\"%s\"\r\n", ip);

  return at_comm->send_until(buff, "OK", NULL, 1000);
}

/**
 * @brief read data from uart data buffer once
 * 
 * @param data data pointer
 * @return true read ok
 * @return false no data or read error
 */
bool Esp8266::receive(char *data, int data_len)
{
  return at_comm->read_buffer(data, data_len);
}

/**
 * @brief receive data from server at fixed time
 * 
 * @param data return data pointer
 * @param timeout receive timeout
 * @return true read ok
 * @return false no data or read error
 */
bool Esp8266::receive_until(char *data, int timeout)
{
  return at_comm->read_buffer_until(data, timeout);
}
