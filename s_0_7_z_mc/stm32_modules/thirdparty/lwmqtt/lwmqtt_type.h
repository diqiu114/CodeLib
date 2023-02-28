#ifndef LWMQTT_TYPE_H
#define LWMQTT_TYPE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * The error type used by all exposed APIs.
 *
 * If a function returns an error that operates on a connected client (e.g publish, keep_alive, etc.) the caller should
 * switch into a disconnected state, close and cleanup the current connection and start over by creating a new
 * connection.
 */
typedef enum {
  LWMQTT_SUCCESS = 0,
  LWMQTT_BUFFER_TOO_SHORT = -1,
  LWMQTT_VARNUM_OVERFLOW = -2,
  LWMQTT_NETWORK_FAILED_CONNECT = -3,
  LWMQTT_NETWORK_TIMEOUT = -4,
  LWMQTT_NETWORK_FAILED_READ = -5,
  LWMQTT_NETWORK_FAILED_WRITE = -6,
  LWMQTT_REMAINING_LENGTH_OVERFLOW = -7,
  LWMQTT_REMAINING_LENGTH_MISMATCH = -8,
  LWMQTT_MISSING_OR_WRONG_PACKET = -9,
  LWMQTT_CONNECTION_DENIED = -10,
  LWMQTT_FAILED_SUBSCRIPTION = -11,
  LWMQTT_SUBACK_ARRAY_OVERFLOW = -12,
  LWMQTT_PONG_TIMEOUT = -13,
} lwmqtt_err_t;

/**
 * A common string object.
 */
typedef struct {
  uint16_t len;
  char *data;
} lwmqtt_string_t;

/**
 * The initializer for string objects.
 */
#define lwmqtt_default_string \
  { 0, NULL }

/**
 * The available QOS levels.
 */
typedef enum { LWMQTT_QOS0 = 0, LWMQTT_QOS1 = 1, LWMQTT_QOS2 = 2, LWMQTT_QOS_FAILURE = 128 } lwmqtt_qos_t;

/**
 * The message object used to publish and receive messages.
 */
typedef struct {
  lwmqtt_qos_t qos;
  bool retained;
  uint8_t *payload;
  size_t payload_len;
} lwmqtt_message_t;

/**
 * The initializer for message objects.
 */
#define lwmqtt_default_message \
  { LWMQTT_QOS0, false, NULL, 0 }

/**
 * The object defining the last will of a client.
 */
typedef struct {
  lwmqtt_string_t topic;
  lwmqtt_qos_t qos;
  bool retained;
  lwmqtt_string_t payload;
} lwmqtt_will_t;

/**
 * The default initializer for the will object.
 */
#define lwmqtt_default_will \
  { lwmqtt_default_string, LWMQTT_QOS0, false, lwmqtt_default_string }

/**
 * The object containing the connection options for a client.
 */
typedef struct {
  lwmqtt_string_t client_id;
  uint16_t keep_alive;
  bool clean_session;
  lwmqtt_string_t username;
  lwmqtt_string_t password;
} lwmqtt_options_t;

/**
 * The default initializer for the options object.
 */
#define lwmqtt_default_options \
  { lwmqtt_default_string, 60, true, lwmqtt_default_string, lwmqtt_default_string }

/**
 * The available return codes transported by the connack packet.
 */
typedef enum {
  LWMQTT_CONNECTION_ACCEPTED = 0,
  LWMQTT_UNACCEPTABLE_PROTOCOL = 1,
  LWMQTT_IDENTIFIER_REJECTED = 2,
  LWMQTT_SERVER_UNAVAILABLE = 3,
  LWMQTT_BAD_USERNAME_OR_PASSWORD = 4,
  LWMQTT_NOT_AUTHORIZED = 5,
  LWMQTT_UNKNOWN_RETURN_CODE = 6
} lwmqtt_return_code_t;

#endif  // LWMQTT_TYPE_H
