/*
 * iap.h
 *
 *  Created on: Sep 6, 2021
 *      Author: weiou
 */

#ifndef __IAP_H_
#define __IAP_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
#include <stdint.h>
#include <stdbool.h>
     
#define APP_SIZE           320 * 1024
#define APP_ADDRESS        0x08010000
#define APP_BACK_ADDRESS   0x08060000

#define FRAME_BUFF_SIZE    1024
#define FRAME_MIN_SIZE     64
#define MAX_FRAME_NO       (APP_SIZE/FRAME_MIN_SIZE)



typedef enum {
	IAP_ONGOING = 0,
	IAP_FINISH,
	IAP_ERR,
}IAP_STATE_t;

typedef enum {
	IAP_CLEAR = 0,
	IAP_PROGRAME
}IAP_CMD_t;

typedef struct {
    uint32_t crc32;
    uint32_t magic; //55AA050A
    uint32_t file_length1;
    uint32_t file_length2;
    uint32_t file_checksum1;
    uint32_t file_checksum2;
}FILE_CHECK_t;

bool IAP_GetStatus(void);
void IAP_SetStatus(void);
void IAP_ClearStatus(void);
int IAP_GetPackSize(void);
errStatus_t IAP_Init(uint32_t file_size,uint32_t file_sum,uint16_t pack_size);
void IAP_Deinit(void);
bool IAP_isAppValid(void);
bool IAP_FlashCheck(void);
bool IAP_WriteCheckInfor(void);
errStatus_t IAP_Process(uint8_t *pdata,uint16_t length,uint16_t pack);

#ifdef __cplusplus
}
#endif
#endif
