#include "mqtt_client.h"
#include "modules_def.h"
/**
 * @brief Construct a new Mqtt_client::Mqtt_client object
 * 
 * @param _wlan waln class pointer
 * @param _params mqtt client parameters
 */
Mqtt_client::Mqtt_client(Wlan_comm_if *_wlan, Mqtt_client_params *_params)
{
  wlan = _wlan;
  params = _params;
  mqtt_encode = new Mqtt_encoder();
  status = MQTT_STATUS_ERROR;
  buffer = NULL;
  update = 0;
  retry = 0;
}

Mqtt_client::~Mqtt_client()
{
  if (wlan != NULL)
  {
    delete wlan;
    wlan = NULL;
  }

  if (params != NULL)
  {
    delete params;
    params = NULL;
  }
}

/**
 * @brief mqtt clinet init and wlan init
 * 
 * @return true 
 * @return false 
 */
bool Mqtt_client::init(void)
{
  bool ret = true;
  if (buffer == NULL)
  {
    buffer = new char[params->comm_buffer_size];
    if (buffer != NULL)
    {
      memset(buffer, 0, params->comm_buffer_size);
      ret = true;
    }
    else
    {
      ret = false;
    }
  }

  ret = ret && wlan->init();

  if (ret)
  {
    status = MQTT_STATUS_READY;
  }

  return ret;
}

/**
 * @brief send data to server with mqtt protocol
 * 
 * @param data data pinter
 * @param data_len data length
 * @return true send ok
 * @return false send failed 
 */
bool Mqtt_client::send(char *data, int data_len)
{
  if ((data == NULL) || (data_len == 0))
  {
    return false;
  }

  memset(buffer, 0, params->comm_buffer_size);
  int buffer_len = mqtt_encode->publish(buffer, params->comm_buffer_size, params->topic, data, data_len);
  
  if (wlan->send(buffer, buffer_len))
  {
    update = 0;
    retry = 0;
    return true;
  }
  else
  {
    retry++;
    if (retry >= params->err_retry_cnt)
    {
      retry = 0;
      status = MQTT_STATUS_READY;
    }
    return false;
  }
}

/**
 * @brief get data from server
 * 
 * @param data data pointer
 * @param data_len data length
 * @return true get ok
 * @return false get failed
 */
bool Mqtt_client::get(char *data, int data_len)
{
  if (data == NULL)
  {
    return false;
  }

  return wlan->get(data, data_len);
}
/**
 * @brief keep wlan connection permanent
 * 
 * @return Mqtt_client_status return connection status
 */
Mqtt_client_status Mqtt_client::keep_connection(void)
{
  int data_len = 0;

  switch (status)
  {
  case MQTT_STATUS_ERROR:
    init();
    break;
  case MQTT_STATUS_READY:
    if (wlan->open_net())
    {
      retry = 0;
      status = MQTT_STATUS_ROUTE_CONNECTED;
    }
    else
    {
      retry++;
      if (retry >= params->err_retry_cnt)
      {
        retry = 0;
        status = MQTT_STATUS_ERROR;
      }
    }

    break;
  case MQTT_STATUS_ROUTE_CONNECTED:
    if (wlan->tcp_connect(params->server, params->port))
    {
      retry = 0;
      status = MQTT_STATUS_SERVER_CONNECTED;
    }
    else
    {
      retry++;
      if (retry >= params->err_retry_cnt)
      {
        retry = 0;
        status = MQTT_STATUS_READY;
      }
    }
    break;
  case MQTT_STATUS_SERVER_CONNECTED:
    data_len = mqtt_encode->connect(buffer, params->comm_buffer_size, params->client_id, params->token);
    if (wlan->send(buffer, data_len))
    {
      retry = 0;
      status = MQTT_STATUS_MQTT_CONNECTED;
    }
    else
    {
      retry++;
      if (retry >= params->err_retry_cnt)
      {
        retry = 0;
        status = MQTT_STATUS_READY;
      }
    }
    break;
  case MQTT_STATUS_MQTT_CONNECTED:
    if (params->keep_alive > 0 && update > (params->keep_alive / params->update_clk))
    {
      update = 0;
      memset(buffer, 0, params->comm_buffer_size);
      data_len = mqtt_encode->pingreq(buffer, params->comm_buffer_size);
      if (wlan->send(buffer, data_len))
      {
        retry = 0;
      }
      else
      {
        retry++;
        if (retry >= params->err_retry_cnt)
        {
          retry = 0;
          status = MQTT_STATUS_ERROR;
        }
      }
    }
    break;
  default:
    break;
  }

  update++;

  return status;
}
