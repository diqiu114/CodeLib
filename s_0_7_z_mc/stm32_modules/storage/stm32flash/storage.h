/*
 * @Author: ZhiQiang
 * @Date: 2022-07-18 09:05:19
 * @CodedFormat: utf8
 * @LastEditors: ZhiQiang
 * @LastEditTime: 2022-11-15 21:35:31
 * @FilePath: \MDK-ARMe:\Desktop\s07z_mc\stm32_modules\storage\stm32flash\storage.h
 * @Description: 
 */
#ifndef __STORAGE_H_
#define __STORAGE_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
#include <stdint.h>
void storage_readbytes(uint32_t addr,uint8_t *pdata,uint16_t length);
void storage_writebytes(uint32_t addr,uint8_t *pdata,uint16_t length);
void storage_erasesector(uint32_t addr);
void storage_init(void);

#ifdef __cplusplus
}
#endif

#endif

