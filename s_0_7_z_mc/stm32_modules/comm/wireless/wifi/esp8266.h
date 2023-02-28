/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ESP8266 AT指令驱动
* data_sheet:https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
*
***********************************************************/

#ifndef _ESP8266_H_
#define _ESP8266_H_

#include <stdbool.h>
#include <string.h>
#include "comm\AT_command\at_command.h"
#include "hw_interface\gpio\gpio_if.h"

#define ESP8266_SOFT_AP_CH_ID (3)
#define ESP8266_TCP_KEEP_ALIVE_TIME_MAX (7200)
#define ESP8266_COMM_BUFF_SIZE (50)
#define ESP8266_SEND_TIMEOUT_MS (1000)

typedef enum _esp8266_type_
{
  ESP_TYPE_STATION = 1,
  ESP_TYPE_SOFT_AP = 2,
  ESP_TYPE_STATION_AND_SOFT_AP = 3
} Esp8266_type;

typedef enum _esp8266_encryption_method_
{
  ESP_ENCRY_METHOD_OPEN = 0,
  ESP_ENCRY_METHOD_WPA_PSK = 2,
  ESP_ENCRY_METHOD_WPA2_PSK = 3,
  ESP_ENCRY_METHOD_WPA_WPA2_PSK = 4
} Esp8266_encry_method;

typedef enum _esp8266_connect_status_
{
  ESP_CONNECTED = 2,
  ESP_TCP_UDP_CONNECTED = 3,
  ESP_TCP_UDP_DISCONNECTED = 4,
  ESP_DISCONNECTED = 5
} Esp8266_conn_status;

typedef enum _esp8266_transmission_mode_
{
  ESP_COMMAND_MODE = 1,
  ESP_DATA_MODE = 2,
} Esp8266_transmission_mode;

class Esp8266
{
public:
  Esp8266(At_command *_at_comm, Gpio_if *_rst_pin = NULL, int command_buff_size = ESP8266_COMM_BUFF_SIZE);
  virtual ~Esp8266();

  bool ready(void);
  bool soft_reset(void);
  bool reset(void);
  bool set_type(Esp8266_type type = ESP_TYPE_STATION, bool save = false);
  bool config_soft_ap(const char *ssid, const char *pwd,
                      unsigned char ch_id = ESP8266_SOFT_AP_CH_ID,
                      Esp8266_encry_method encry_method = ESP_ENCRY_METHOD_WPA2_PSK);
  bool search(const char *ssid);
  bool connect(const char *ssid, const char *pwd, bool save = false);
  bool disconnect(void);
  bool set_auto_connect(bool auto_conn = true);
  Esp8266_conn_status status(void);
  bool tcp_connect(const char *ip, unsigned short port, unsigned short keep_alive = 0);
  bool tcp_udp_disconnect(void);
  bool udp_connect(const char *ip, unsigned short port, unsigned short local_port = 0, char mode = 0);
  bool enter_transparent_mode(void);
  bool exit_transparent_mode(void);
  bool ping(const char *ip);
  bool send(char *data, int data_len);
  bool receive(char* data, int data_len = 0);
  bool receive_until(char* data, int timeout);
  
private:
  At_command *at_comm;
  Gpio_if *rst_pin;
  char *buff;
  int buff_size;
  Esp8266_transmission_mode transmission_mode;
};

#endif // _ESP8266_H_
