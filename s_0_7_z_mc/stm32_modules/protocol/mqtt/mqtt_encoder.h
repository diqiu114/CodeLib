/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-20
 * 
 * @brief MQTT protocol encoder
 *        MQTT version 3.1.1
 * 
 *  depend on lwmqtt(light weight mqtt)
 *  git : https://github.com/256dpi/lwmqtt.git
 *
 *  docs: https://mcxiaoke.gitbooks.io/mqtt-cn/content/
 * 
 * ***********************************************************
 */

#ifndef _MQTT_ENCODER_H_
#define _MQTT_ENCODER_H_

#include "thirdparty\lwmqtt\lwmqtt_packet.h"

typedef lwmqtt_qos_t Mqtt_qos_t;

class Mqtt_encoder
{
public:
  Mqtt_encoder();
  ~Mqtt_encoder();

  int connect(char *ret_str, int ret_str_len, const char *client_id, const char *username);
  int disconnect(char *ret_str, int ret_str_len);

  int publish(char *ret_str, int ret_str_len, const char *topic, const char *msg, int msg_len = 0);

  // puback();
  // pubrec();
  // pubrel();
  // pubcomp();

  int subscribe(char *ret_str, int ret_str_len, const char *topic, Mqtt_qos_t qos_lvl = LWMQTT_QOS0);
  int unsubscribe(char *ret_str, int ret_str_len, const char *topic);

  int pingreq(char *ret_str, int ret_str_len);

private:
  lwmqtt_options_t options;
  lwmqtt_will_t will;
  lwmqtt_message_t message;
  lwmqtt_string_t string;
};

#endif // _MQTT_H_
