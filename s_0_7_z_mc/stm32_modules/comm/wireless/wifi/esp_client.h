/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-28
 * 
 * @brief ESP8266 client mode 
 * 
 * ***********************************************************
 */

#ifndef _ESP_CLIENT_H_
#define _ESP_CLIENT_H_

#include "esp8266.h"
#include "..\wlan_comm_if.h"

class Esp_client : public Wlan_comm_if
{
  public :
  Esp_client(Esp8266 *_esp, char* _ssid, char* _pwd, Esp8266_transmission_mode _mode = ESP_COMMAND_MODE);
  virtual ~Esp_client();
  virtual bool init(void);
  virtual bool open_net(void);
  virtual bool close_net(void);
  virtual bool tcp_connect(char* server, unsigned short port);
  virtual bool udp_connect(char* server, unsigned short dst_port, unsigned short src_port = 0);
  virtual bool disconnect(void);
  virtual bool send(char* data, int data_len);
  virtual bool get(char* ret_data, int data_len = 0);
  private:
    Esp8266 *esp;
    char *ssid;
    char* pwd;
    unsigned short port;
    Esp8266_transmission_mode mode;
};



#endif // _ESP_CLIENT_H_
