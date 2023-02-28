#ifndef LWMQTT_STRING_H
#define LWMQTT_STRING_H

// C++ detection
#ifdef __cplusplus
extern "C" {
#endif

#include "lwmqtt_type.h"

/**
 * Returns a string object for the passed C string.
 *
 * @param str - The C string.
 * @return A string object.
 */
lwmqtt_string_t lwmqtt_string(const char *str);

/**
 * Compares a string object to a C string.
 *
 * @param a - The string object to compare.
 * @param b - The C string to compare.
 * @return Similarity e.g. strcmp().
 */
int lwmqtt_strcmp(lwmqtt_string_t a, const char *b);

// C++ detection
#ifdef __cplusplus
}
#endif

#endif // LWMQTT_STRING_H
