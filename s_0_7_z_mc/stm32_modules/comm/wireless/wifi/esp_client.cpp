#include "esp_client.h"

/**
 * @brief Construct a new Esp_client::Esp_client object
 * 
 * @param _esp esp8266 class pinter
 * @param _ssid wifi ssid,note: not support 5G WIFI
 * @param _pwd wifi password
 * @param _mode data mode
 */
Esp_client::Esp_client(Esp8266 *_esp, char *_ssid, char *_pwd, Esp8266_transmission_mode _mode)
{
  esp = _esp;
  ssid = _ssid;
  pwd = _pwd;
  mode = _mode;
}

Esp_client::~Esp_client()
{
  if (esp != NULL)
  {
    delete esp;
    esp = NULL;
  }
}

/**
 * @brief initalize esp8266
 * 
 * @return true ok
 * @return false failed
 */
bool Esp_client::init(void)
{
  bool ret = true;
  esp->reset();
  ret = ret && esp->ready();
  ret = ret && esp->set_auto_connect();
  ret = ret && esp->set_type();

  return ret;
}

/**
 * @brief connect to wifi route
 * 
 * @return true connect ok
 * @return false connect failed
 */
bool Esp_client::open_net(void)
{
  bool ret = true;

  ret = ret && esp->search(ssid);
  ret = ret && esp->connect(ssid, pwd);

  return ret;
}

/**
 * @brief disconnect from wifi route
 * 
 * @return true disconnect ok
 * @return false disconnect failed
 */
bool Esp_client::close_net(void)
{
  return esp->disconnect();
}

/**
 * @brief connect to tcp sever
 * 
 * @param server server ip or server address
 * @param port server port
 * @return true connect ok
 * @return false connect failed
 */
bool Esp_client::tcp_connect(char *server, unsigned short port)
{
  bool ret = false;

  if (esp->tcp_connect(server, port))
  {
    ret = true;
    if (mode == ESP_DATA_MODE)
    {
      ret = ret && esp->enter_transparent_mode();
    }
  }

  return ret;
}

/**
 * @brief conenct to udp server
 * 
 * @param server server ip or server address
 * @param dst_port server port
 * @param src_port device port
 * @return true connect ok
 * @return false connect failed
 */
bool Esp_client::udp_connect(char *server, unsigned short dst_port, unsigned short src_port)
{
   bool ret = false;

  if (esp->udp_connect(server, dst_port, src_port))
  {
    ret = true;
    if (mode == ESP_DATA_MODE)
    {
      ret = ret && esp->enter_transparent_mode();
    }
  }

  return ret;
}

/**
 * @brief disconnect from tcp/udp server
 * 
 * @return true ok
 * @return false failed
 */
bool Esp_client::disconnect(void)
{
  return esp->tcp_udp_disconnect();
}

/**
 * @brief send data to server
 * 
 * @param data data pointer 
 * @param data_len data length
 * @return true send ok
 * @return false send failed
 */
bool Esp_client::send(char *data, int data_len)
{
  return esp->send(data, data_len);
}

/**
 * @brief get data from esp8266 communication buffer
 * 
 * @param ret_data data pointer
 * @param data_len data length to be read
 * @return true get data ok
 * @return false no data or get data error
 */
bool Esp_client::get(char *ret_data, int data_len)
{
  return esp->receive(ret_data, data_len);
}
