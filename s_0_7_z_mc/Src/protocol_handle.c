/*
 * protocol_handle.c
 *
 *  Created on: 2021Äê5ÔÂ10ÈÕ
 *      Author: weridy
 */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "proj_tasks.h"
#include "de_protocol.h"
#include "mem_malloc.h"
#include "debug.h"
#include "iap.h"

errStatus_t app_para_save(void);
void protocol_handle_config(uint8_t *pdata,uint16_t length,HandleResult *result,int *resultcnt) {

	int result_cnt = 0;

    errStatus_t  err = de_protocol_handle_config(pdata,length);

    if(err != errOK) {
        result[result_cnt].result = Result_MsgErr;
    } else {
        result[result_cnt].result = Result_OK;
    }
    result[result_cnt].DataId = 0;
    result[result_cnt].extLength = 0;

    result_cnt++;
    
	*resultcnt = result_cnt;
}
//#include "app_iap.h"

void protocol_handle_upgrade(uint8_t *pdata,uint16_t length,HandleResult *result,int *resultcnt) {
	uint16_t index = 0;

	int result_cnt = 0;
	uint8_t err_count = 0;

	uint8_t *p = NULL;

    bool ret = true;
	
    {
		uint8_t data_id = pdata[index++];

		switch(data_id) {
			case DataId_Upgrade_Header:
                {
                    uint32_t file_size;
                    uint32_t file_sum;
                    uint16_t pack_size;
                    if(pdata[index++] != 0x55) {
                        ret = false;
                        break;
                    }
                    
                    if(pdata[index++] != 0xAA) {
                        ret = false;
                        break;
                    }

                    //file size
                    file_size =  (uint32_t)pdata[25] << 24 \
                                |(uint32_t)pdata[26] << 16 \
                                |(uint32_t)pdata[27] << 8 \
                                |(uint32_t)pdata[28];
                    
                    file_sum =   (uint32_t)pdata[29] << 24 \
                                |(uint32_t)pdata[30] << 16 \
                                |(uint32_t)pdata[31] << 8 \
                                |(uint32_t)pdata[32];
                    
                    pack_size = (uint16_t)pdata[33] << 8 \
                                |pdata[34];
                    
                    
                    if(IAP_Init(file_size,file_sum,pack_size) != errOK) {
                        ret = false;
                        break;
                    }
                    uint8_t *pack_data = sys_malloc(pack_size);
                    if(pack_data == NULL) {
                        ret = false;
                        break;
                    }
                    memcpy(pack_data,pdata + 1,pack_size);
                    
                    IAP_Process(pack_data,pack_size,0);
                    
                    sys_free(pack_data);
                    
                }
				break;


			case DataId_Upgrade_FileData: 
                {
                    uint16_t pack_number = (uint16_t)pdata[index] << 8 | pdata[index+1];
                    index += 2;
                    uint16_t pack_size = (uint16_t)pdata[index] << 8 | pdata[index+1];
                    index += 2;
                    if(pack_size > IAP_GetPackSize()) {
                        ret = false;
                        break;
                    }
                    uint8_t *pack_data = sys_malloc(pack_size);
                    if(pack_data == NULL) {
                        ret = false;
                        break;
                    }
                    memcpy(pack_data,pdata + index,pack_size);

                    errStatus_t err = IAP_Process(pack_data,pack_size,pack_number);
                    if(err != errOK) {
                        ret = false;
                    }
                    
                    sys_free(pack_data);
  
                }
                
				break;


			default:
				err_count++;
				break;

		}

		if(err_count > 0) {
			result[result_cnt].result = Result_MsgErr;
		} else {
			result[result_cnt].result = Result_OK;
		}
		result[result_cnt].DataId = data_id;
		result[result_cnt].extLength = 0;

		result_cnt++;

	}

	if(!ret) {
		result[result_cnt].result = Result_MsgErr;
		result[result_cnt].DataId = 0x00;
		result[result_cnt].extLength = 0;
		result_cnt++;
	}

	if(p != NULL) {
		sys_free(p);
		p = NULL;
	}

	*resultcnt = result_cnt;
}


