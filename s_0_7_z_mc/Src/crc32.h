#ifndef _CRC_CRC32_H
#define _CRC_CRC32_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

extern const uint32_t crc32_tab[];
uint32_t CRC_Get32(const uint8_t* s, int len);
uint8_t CRC_Get8( uint8_t * pBuffer, uint16_t bufSize );
#ifdef __cplusplus
}
#endif /* __cplusplus  */
#endif
