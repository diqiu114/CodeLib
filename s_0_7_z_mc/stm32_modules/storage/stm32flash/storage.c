#include <stdint.h>
#include "bsp_flash.h"
#include "storage.h"

void storage_readbytes(uint32_t addr,uint8_t *pdata,uint16_t length) {
    Bsp_FlashRead(addr,(uint32_t *)pdata,length);
}

void storage_readwords(uint32_t addr,uint32_t *pdata,uint16_t length) {
    Bsp_FlashRead(addr,(uint32_t *)pdata,length);
}

void storage_writebytes(uint32_t addr,uint8_t *pdata,uint16_t length) {
    Bsp_FlashProgram(addr,(uint32_t *)pdata,length);  
}

void storage_erasesector(uint32_t addr) {
    Bsp_FlashEraseSector(addr);
}

void storage_init(void) {
    
}
