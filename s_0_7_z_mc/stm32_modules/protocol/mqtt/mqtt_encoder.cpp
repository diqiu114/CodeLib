
#include "mqtt_encoder.h"
#include <string.h>

#define DEFAULT_CLEAN_SESSION (true)
#define DEFAULT_KEEP_ALIVE (60)
#define DEFAULT_QOS (LWMQTT_QOS0)
#define DEFAULT_RETAIN (false)

Mqtt_encoder::Mqtt_encoder()
{
  options.clean_session = DEFAULT_CLEAN_SESSION;
  options.client_id.len = 0;
  options.client_id.data = NULL;
  options.keep_alive = DEFAULT_KEEP_ALIVE;
  options.username.len = 0;
  options.username.data = NULL;
  options.password.len = 0;
  options.password.data = NULL;

  will.payload.len = 0;
  will.payload.data = NULL;
  will.qos = DEFAULT_QOS;
  will.retained = DEFAULT_RETAIN;
  will.topic.len = 0;
  will.topic.data = NULL;

  message.payload = NULL;
  message.payload_len = 0;
  message.qos = DEFAULT_QOS;
  message.retained = DEFAULT_RETAIN;

  string.data = NULL;
  string.len = 0;
}

Mqtt_encoder::~Mqtt_encoder()
{
}

/**
 * @brief mqtt connect message encode
 * 
 * @param ret_str string pointer after encode
 * @param ret_str_len encode string max length, prevent memory out of bounds
 * @param client_id clinet id
 * @param username username, usually device token
 * @return 0 - encode failed, >0 - encode string length
 */
int Mqtt_encoder::connect(char *ret_str, int ret_str_len, const char *client_id, const char *username)
{
  if( username != NULL )
  {
    options.username.len = strlen(username);
    options.username.data = (char *)username;
  }
  else
  {
    options.username.len = 0;
    options.username.data = NULL;
  }
  
  lwmqtt_string_t client_str = {strlen(client_id), (char *)client_id};
  options.client_id = client_str;
  size_t ret_len = 0;

  return (lwmqtt_encode_connect((unsigned char *)ret_str, ret_str_len, &ret_len, options, NULL) == LWMQTT_SUCCESS) ? ret_len: 0;

}

/**
 * @brief mqtt disconnect message encode
 * 
 * @param ret_str string pointer after encode
 * @param ret_str_len encode string max length, prevent memory out of bounds
 * @return 0 - encode failed, >0 - encode string length
 */
int Mqtt_encoder::disconnect(char *ret_str, int ret_str_len)
{
  size_t ret_len = 0;
  return (lwmqtt_encode_zero((unsigned char *)ret_str, ret_str_len, &ret_len, LWMQTT_DISCONNECT_PACKET) == LWMQTT_SUCCESS) ? ret_len : 0;
}

/**
 * @brief mqtt publish message encode
 * 
 * @param ret_str string pointer after encode
 * @param ret_str_len encode string max length, prevent memory out of bounds
 * @param topic publish topic
 * @param msg publish message
 * @return 0 - encode failed, >0 - encode string length 
 */
int Mqtt_encoder::publish(char *ret_str, int ret_str_len, const char *topic, const char *msg, int msg_len)
{
  size_t ret_len = 0;
  bool dup = false;
  unsigned short packet_id = 0;
  lwmqtt_string_t topic_str = {strlen(topic), (char *)topic};
  if(msg_len == 0)
  {
  message.payload_len = strlen(msg);
  }
  else
  {
     message.payload_len = msg_len;
  }
  message.payload = (unsigned char *)msg;

  return (lwmqtt_encode_publish((unsigned char *)ret_str, ret_str_len, &ret_len, dup, packet_id, topic_str, message) == LWMQTT_SUCCESS) ? ret_len : 0;
}

/**
 * @brief mqtt subscribe message encode
 * 
 * @param ret_str string pointer after encode
 * @param ret_str_len encode string max length, prevent memory out of bounds
 * @param topic topic to be subscribe
 * @param qos_lvl qos level
 * @return 0 - encode failed, >0 - encode string length 
 */
int Mqtt_encoder::subscribe(char *ret_str, int ret_str_len, const char *topic, Mqtt_qos_t qos_lvl)
{
  size_t ret_len = 0;
  unsigned short packet_id = 0;
  lwmqtt_string_t topic_str = {strlen(topic), (char *)topic};
  lwmqtt_qos_t qos = DEFAULT_QOS;

  return (lwmqtt_encode_subscribe((unsigned char *)ret_str, ret_str_len, &ret_len, packet_id, 1, &topic_str, &qos) == LWMQTT_SUCCESS) ? ret_len : 0;
}

/**
 * @brief mqtt unsubscribe message encode
 * 
 * @param ret_str string pointer after encode
 * @param ret_str_len encode string max length, prevent memory out of bounds
 * @param topic topic to be unsubscribe
 * @return 0 - encode failed, >0 - encode string length 
 */
int Mqtt_encoder::unsubscribe(char *ret_str, int ret_str_len, const char *topic)
{
  size_t ret_len = 0;
  unsigned short packet_id = 0;
  lwmqtt_string_t topic_str = {strlen(topic), (char *)topic};

  return (lwmqtt_encode_unsubscribe((unsigned char *)ret_str, ret_str_len, &ret_len, packet_id, 1, &topic_str) == LWMQTT_SUCCESS) ? ret_len : 0;
}

/**
 * @brief mqtt pingreq message encode
 * 
 * @param ret_str string pointer after encode
 * @param ret_str_len encode string max length, prevent memory out of bounds
 * @return 0 - encode failed, >0 - encode string length 
 */
int Mqtt_encoder::pingreq(char *ret_str, int ret_str_len)
{
  size_t ret_len = 0;
  return (lwmqtt_encode_zero((unsigned char *)ret_str, ret_str_len, &ret_len, LWMQTT_PINGREQ_PACKET) == LWMQTT_SUCCESS) ? ret_len : 0;
}
