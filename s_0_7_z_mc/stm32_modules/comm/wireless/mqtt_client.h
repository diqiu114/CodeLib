/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-27
 * 
 * @brief MQTT client
 * 
 * ***********************************************************
 */

#ifndef _MQTT_CLIENT_H_
#define _MQTT_CLIENT_H_

#include <stdbool.h>
#include <string.h>
#include "wlan_comm_if.h"
#include "protocol\mqtt\mqtt_encoder.h"

#define MQTT_CLIENT_COMM_BUFFER_SIZE (1024)
#define MQTT_CLIENT_ERROR_RETRY_CNT (5)

typedef enum _mqtt_client_status_
{
  MQTT_STATUS_ERROR = -1,
  MQTT_STATUS_READY = 0,
  MQTT_STATUS_ROUTE_CONNECTED,
  MQTT_STATUS_SERVER_CONNECTED,
  MQTT_STATUS_MQTT_CONNECTED
} Mqtt_client_status;

class Mqtt_client_params
{
public:
  Mqtt_client_params(char *_server, unsigned short _port,
                     char *_token, char *_topic, char *_client_id,
                     int _keep_alive, int _update_clk,
                     int _err_retry_cnt = MQTT_CLIENT_ERROR_RETRY_CNT,
                     int _comm_buffer_size = MQTT_CLIENT_COMM_BUFFER_SIZE)
  {
    server = _server;
    port = _port;
    token = _token;
    topic = _topic;
    client_id = _client_id;
    keep_alive = _keep_alive;
    update_clk = _update_clk;
    comm_buffer_size = _comm_buffer_size;
    err_retry_cnt = _err_retry_cnt;
  }

  char *server;
  unsigned short port;
  char *token;
  char *topic;
  char* client_id;
  int keep_alive;
  int update_clk;
  int comm_buffer_size;
  int err_retry_cnt;
};

class Mqtt_client
{
public:
  Mqtt_client(Wlan_comm_if *_wlan, Mqtt_client_params *_params);
  ~Mqtt_client();
  bool init(void);
  bool send(char *data, int data_len);
  bool get(char *data, int data_len = 0);
  Mqtt_client_status keep_connection(void);

private:
  Wlan_comm_if *wlan;
  Mqtt_encoder *mqtt_encode;
  Mqtt_client_params *params;
  Mqtt_client_status status;
  char *buffer;
  int update;
  int retry;
};

#endif // _MQTT_CLIENT_H_
