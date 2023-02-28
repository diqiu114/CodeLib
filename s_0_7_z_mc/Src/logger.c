#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "logger.h"
#include "debug.h"
#include "crc32.h"
#include "..\stm32_modules\storage\stm32flash\storage.h"

void logger_set_reset_reg(void);
void logger_print_reboot_reason(COMM_TYPE_t commType,uint32_t reg);
static uint32_t logger_index = 0;

const char* logger_type[] = {
    "复位", 
    "配置",
    "操作",
    "告警",
    "异常",
    "信息",
    "其他"
};


extern RTC_HandleTypeDef hrtc;
void logger_get_time(DATE_yymmddhhmmss_t *time) {
    RTC_TimeTypeDef rtc_time;
    RTC_DateTypeDef rtc_date;
    HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);
    
    //Rtc->ts_to_datetime();
    
    
    time->bits.year = rtc_date.Year;
    time->bits.month = rtc_date.Month;
    time->bits.day = rtc_date.Date;
    time->bits.hour = rtc_time.Hours;
    time->bits.min = rtc_time.Minutes;
    time->bits.sec = rtc_time.Seconds;
}

/*
get current logger index.
*/
uint32_t Logger_getIndex(void) {
	return logger_index;
}

/*
save the information.
*/
void logger_infor_save(logger_msg_t msg) {

    logger_t log = {0};

	/* mode index in total index numbers */
	uint16_t indexofMod = logger_index % INDEX_LOGGER_MAX_NUMBER;
	/* current index page address */
	uint32_t pageAddr = LOGGER_START_ADDR + indexofMod  * sizeof(logger_t) / LOGGER_SECTOR_SIZE * LOGGER_SECTOR_SIZE;
	/* aligne the erase address */
	if((logger_index % INDEX_LOGGER_OF_SECTOR) == 0) {
		storage_erasesector(pageAddr);
	}
    
    /* current write address */
	uint32_t addr = LOGGER_START_ADDR + indexofMod * sizeof(logger_t);
    
    storage_readbytes(addr,(uint8_t*)&log,sizeof(logger_t));
    uint8_t *p = (uint8_t*)&log;
    for(uint8_t i=0;i<sizeof(logger_t);i++) {
        if(p[i] != 0xff) {
            storage_erasesector(pageAddr);
            break;
        }
    }
    
    memset(&log,0,sizeof(logger_t));
    
    rtc_get_time(&log.time);
    
    memcpy(&log.msg,&msg,sizeof(logger_msg_t));
    
	log.index = logger_index;
    
    log.sum = CRC_Get32((uint8_t *)&log.time,sizeof(logger_t) - 4); 
    
    storage_writebytes(addr,(uint8_t *)&log, sizeof(logger_t));
	
    logger_index++;
}

void get_filename(const char *path, char *name)
{
    int i,j = 0;
    for(i = 0; path[i]; i ++)
        if(path[i] == '\\') j = i;
    strcpy(name, &path[j]);
}

void logger_infor_save_more(LOGGER_TYPE_t type,LOGGER_MORE_INFOR_t more,uint32_t infor,const char *str,const char *file,uint16_t line) {

    logger_msg_t msg = {0};
    
    
    msg.type = type;
    msg.more = more;
    
    get_filename(file,(char *)msg.file);
    msg.line = line;
    
    if(str != NULL) {
        strcpy((char *)msg.v.d1,str);
    } else {
        msg.v.d4[0] = infor;
    }

    logger_infor_save(msg);
}

void logger_infor_load(COMM_TYPE_t commType,bool load) {

    
	uint32_t addr = LOGGER_START_ADDR;
    
	bool find = false;
    
	logger_t logger = {0}; 

    uint8_t index = 0;

	for(uint32_t size = 0; size < LOGGER_MAX_SIZE; size += sizeof(logger_t),addr += sizeof(logger_t)) {

    if(size + sizeof(logger_t) >= LOGGER_MAX_SIZE) {
        break;
    }
		storage_readbytes(addr,(uint8_t *)&logger,sizeof(logger_t));
        
#if WATCH_DOG_ENABLE == 1
    hal_feed_dog();
#endif
	    if(logger.sum == CRC_Get32((uint8_t *)&logger.time,sizeof(logger_t) - 4)) 
        {
			if(load) {
                if(logger.index > logger_index) {
                    logger_index = logger.index;
                }
                find = true;
            } else {
                    if(logger.msg.type < LOGGER_TYPE_MAX) {
                        
                        debug_printf(commType,"<<< No:%04d,%04d-%02d-%02d %02d:%02d:%02d %s,%s,%d\r\n",logger.index,\
                                                                                  logger.time.bits.year + 2000,\
                                                                                  logger.time.bits.month,\
                                                                                  logger.time.bits.day,\
                                                                                  logger.time.bits.hour,\
                                                                                  logger.time.bits.min,\
                                                                                  logger.time.bits.sec,\
                                                                                  logger_type[logger.msg.type],\
                                                                                  logger.msg.file,\
                                                                                  logger.msg.line);
                        switch(logger.msg.type) {
                            case LOGGER_RESET:
                                debug_printf(commType,"PSR:%08x\r\n",logger.msg.v.d4[0]);
                                logger_print_reboot_reason(commType,logger.msg.v.d4[0]);
                                break;
                            
                            case LOGGER_CONFIG:
                                break;
                            
                            case LOGGER_OPERATE:
                                switch(logger.msg.more) {
                                    case LOGGER_MORE_FS_FORMAT:
                                        debug_printf(commType,"FS format. @%s\r\n",logger.msg.v.d1);
                                        break;
                                    case LOGGER_MORE_FILE_CREATE:
                                        debug_printf(commType,"File:%s create.\r\n",logger.msg.v.d1);
                                        break;
                                    case LOGGER_MOER_FILE_WIRTE_OPEN_FAILED:
                                        debug_printf(commType,"File:%s write open failed.\r\n",logger.msg.v.d1);
                                        break;
                                }
                                break;
                                
                            case LOGGER_ALARM:
                                break;
                            
                            case LOGGER_EXCEPT:
                                debug_printf(commType,"R0 :%08x\r\nR1 :%08x\r\nR2 :%08x\r\nR3 :%08x\r\nR12:%08x\r\nLR :%08x\r\nPC :%08x\r\nPSR:%08x\r\nTID:%08x,%s\r\n",\
                                                logger.msg.v.d4[0],\
                                                logger.msg.v.d4[1],\
                                                logger.msg.v.d4[2],\
                                                logger.msg.v.d4[3],\
                                                logger.msg.v.d4[4],\
                                                logger.msg.v.d4[5],\
                                                logger.msg.v.d4[6],\
                                                logger.msg.v.d4[7],\
                                                logger.msg.v.d4[8],\
                                                logger.msg.file);
                                break;
                            case LOGGER_OTHERS:
                                break;
                            case LOGGER_WARNING:
                                debug_printf(commType,"%s\r\n",logger.msg.v.d1);
                                break;
                        }
                }
            }
		}
	}
    
         
    if(load) {
        if(find) {
            logger_index++;
        }     
    }
}



/*
clear the logs.
*/
void logger_infor_clear(void) {

    uint32_t addr = LOGGER_START_ADDR;
    for(;addr < LOGGER_END_ADDR; addr += LOGGER_SECTOR_SIZE) {
        storage_erasesector(addr);
    }  
    logger_index = 0;
}
/*
get the reboot why?
*/
void logger_set_reset_reg(void) {
    
    //RCC_CSR_BORRSTF
	logger_infor_save_more(LOGGER_RESET,LOGGER_MORE_NONE,RCC->CSR,NULL,__FILE__,__LINE__);

	RCC->CSR |= RCC_CSR_RMVF; 
}

void logger_print_reboot_reason(COMM_TYPE_t commType,uint32_t reg) {
    uint8_t rst_src_cnt = 0;
    if(reg & RCC_CSR_BORRSTF) {
        debug_printf(commType,"BOR Reset\r\n");
		rst_src_cnt++;
	}

	if(reg & RCC_CSR_PORRSTF) {
        debug_printf(commType,"POR Reset\r\n");
		rst_src_cnt++;
	}
	
	if(reg & RCC_CSR_SFTRSTF) {
        debug_printf(commType,"SFT Reset\r\n");
		rst_src_cnt++;
	}  
	
	if(reg & RCC_CSR_IWDGRSTF) {
        debug_printf(commType,"IDW Reset\r\n");
		rst_src_cnt++;
	}
	
	if(reg & RCC_CSR_WWDGRSTF) {
        debug_printf(commType,"WWD Reset\r\n");
		rst_src_cnt++;
	}	
	
	if(reg & RCC_CSR_LPWRRSTF) {
        debug_printf(commType,"LPW Reset\r\n");
		rst_src_cnt++;
	}	

	if(reg & RCC_CSR_PINRSTF && !rst_src_cnt) {
        debug_printf(commType,"PIN Reset\r\n");
	}
}
