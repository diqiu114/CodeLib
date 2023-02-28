#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "debug.h"
#include "cmsis_os.h"
#include "my_tasks.h"
#include "logger.h"
#include "usbd_def.h"
#include "proj_tasks.h"


osSemaphoreId  comPrintSem = NULL;
osSemaphoreDef(comPrintSem);

void debug_sendstring(COMM_TYPE_t commType,char * msg);
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
void eth_sendbytes(uint8_t *pdata,uint16_t length);
void debug_sendstring(COMM_TYPE_t commType,char * msg) {
    
    if(commType == COMM_TYPE_ETH) {
        eth_sendbytes((uint8_t *)msg,strlen(msg));
    } else {
        uint16_t delay = 0xfff;
        while(delay--) {
            if(USBD_BUSY != CDC_Transmit_FS((uint8_t  *)msg, strlen((const char *)msg))) {
                break;
            }
        }
    }
}

static uint8_t LoggerBuf[512];
void debug_sendbytes(COMM_TYPE_t commType,uint8_t *p,uint16_t length) {
    if(commType == COMM_TYPE_ETH) {
        eth_sendbytes((uint8_t *)p,length);
        uint32_t delay = (1000 * 11.0f /115200.0f) * length + 0.5f;
        osDelay(delay);
    } else {
        uint16_t delay = 0xfff;
        while(delay--) {
            if(USBD_BUSY != CDC_Transmit_FS((uint8_t  *)p, length)) {
                break;
            }
        }
    }
}

void debug_printf(COMM_TYPE_t commType,const char *fmt, ...) {
    if(comPrintSem == NULL) {
        comPrintSem = osSemaphoreCreate(osSemaphore(comPrintSem), 1);
    }
    osSemaphoreWait(comPrintSem,osWaitForever);
    uint16_t length;
    va_list args;
    va_start(args, fmt);
    memset(LoggerBuf, 0, sizeof(LoggerBuf));
    length = vsnprintf((char *)LoggerBuf, sizeof(LoggerBuf) - 1, fmt, args);
    if(length > 0) {
        debug_sendbytes(commType,LoggerBuf,length);
    }
    
    va_end(args);
    osSemaphoreRelease(comPrintSem);
}


void debug_printf_with_debugon(COMM_TYPE_t commType,const char *fmt, ...) {
    #define DEBUG_ON  1
#if DEBUG_ON == 1
    if(comPrintSem == NULL) {
        comPrintSem = osSemaphoreCreate(osSemaphore(comPrintSem), 1);
    }
    osSemaphoreWait(comPrintSem,osWaitForever);
    uint16_t length;
    va_list args;
    va_start(args, fmt);
    memset(LoggerBuf, 0, sizeof(LoggerBuf));
    length = vsnprintf((char *)LoggerBuf, sizeof(LoggerBuf) - 1, fmt, args);
    if(length > 0) {
        debug_sendbytes(commType,LoggerBuf,length);
    }
    
    va_end(args);
    osSemaphoreRelease(comPrintSem);
#endif
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ) {
    //char msg[24];
    ///debug_sendstring((char *)"StackOverflowHook@");
    //debug_sendstring((char *)pcTaskName);
    //sprintf(msg,"TaskId:%08x,taskName:%s\r\n",(uint32_t)xTask,pcTaskName);
    //debug_sendstring(msg);

}


#include "ff.h"

#if LOGGER_WITH_FS == 1
void logger_infor_clear(void) {
     f_unlink("logger_info.ini");
}

void logger_infor_save(logger_msg_t msg) {
    
    FIL fp;
    
    UINT bytes_write;
    
    if (f_open(&fp, "logger_info.ini", FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_APPEND ) != FR_OK) {
        return;
    }
    
    logger_t log = {0};
    
    logger_get_time(&log.time);
    
    memcpy(&log.msg,&msg,sizeof(logger_msg_t));

    uint8_t *p = (uint8_t *)&log.time;
    
    for(int i=0;i<sizeof(logger_t) - 4;i++) {
        log.sum += *p++;
    }
    
    f_lseek(&fp,fp.obj.objsize);
    
    f_write(&fp, (void *)&log, sizeof(log), &bytes_write);

    f_close(&fp);
}



void logger_infor_load(void) {

    FIL fp;
    
    UINT bytes_read;
    
    if (f_open(&fp, "logger_info.ini", FA_READ | FA_OPEN_EXISTING ) != FR_OK)
    {
        return;
    }
    
    logger_t infor = {0};

    while(1) {
        if(f_read(&fp,(void *)&infor,sizeof(logger_t),&bytes_read) != FR_OK) {
            break;
        }

        if(bytes_read < sizeof(logger_t)) {
            break;
        }
        
        uint32_t sum = 0;
        uint8_t *p = (uint8_t *)&infor.time;
        for(uint8_t i=0;i<sizeof(logger_t)-4;i++) {
            sum += *p++;
        }

        if(sum == infor.sum) {
            switch(infor.msg.type) {
                case LOGGER_RESET:
                    break;
                case LOGGER_EXCEPT:
                    debug_printf("%04d-%02d-%02d %02d:%02d:%02d \r\nR0:%08x\r\nR1:%08x\r\nR2:%08x\r\nR3:%08x\r\nR12:%08x\r\nLR:%08x\r\nPC:%08x\r\nPSR:%08x\r\nThreadId:%08x\r\n",\
                        infor.time.bits.year + 2000,\
                        infor.time.bits.month,\
                        infor.time.bits.day,\
                        infor.time.bits.hour,\
                        infor.time.bits.min,\
                        infor.time.bits.sec,\
                        infor.msg.v.d4[0],\
                        infor.msg.v.d4[1],\
                        infor.msg.v.d4[2],\
                        infor.msg.v.d4[3],\
                        infor.msg.v.d4[4],\
                        infor.msg.v.d4[5],\
                        infor.msg.v.d4[6],\
                        infor.msg.v.d4[7],\
                        infor.msg.v.d4[8]);
                    break;
                       
            }
            
        }
    }
    
    f_close(&fp);
}
#else 


#endif

#include "FreeRTOS.h"
#include "task.h"
#include "debug.h"
typedef struct {
    const char *command;
    char *(*pFun)(COMM_TYPE_t commType,const void *,void *);

} DEBUG_COMMAND_t;

char *do_get_task_infor(COMM_TYPE_t commType,const void *command,void *para) {
    
    char *task_infor = (char *)pvPortMalloc(1024);
    
    memset(task_infor, 0, 1024);

	strcat((char *)task_infor, "Task Name\t Task Status\tTask Prio\tRemain Stack\tTask No.\r\n" );
    
	debug_sendstring(commType,(char  *)task_infor); 

	memset(task_infor, 0, 1024);
    
	vTaskList((char *)task_infor);
    
	debug_sendstring(commType,(char  *)task_infor); 
    
    debug_printf(commType,"memory infor:\r\ntotal:%d,left:%d,min_left:%d\r\n",configTOTAL_HEAP_SIZE,xPortGetFreeHeapSize(),xPortGetMinimumEverFreeHeapSize());

    
    vPortFree(task_infor);
    
    return NULL;
}

char *do_get_logger_infor(COMM_TYPE_t commType,const void *command,void *para) {
    logger_infor_load(commType,false);
    return NULL;
}

char *do_clear_logger_infor(COMM_TYPE_t commType,const void *command,void *para) {
    logger_infor_clear();
    return NULL;
}

char *do_generate_hardfault(COMM_TYPE_t commType,const void *command,void *para) {
    typedef void (* hardfault_t)(void);
    hardfault_t hardfault = NULL;
    hardfault();
    return NULL;
}

int8_t TestFileWriteRead(void)
{
    char szTestFileName[] = "test.txt";
    uint8_t retSD;
    FIL fTestR;
    retSD = f_open(&fTestR, szTestFileName, FA_READ | FA_OPEN_ALWAYS);
    if(FR_OK != retSD)
    {
        printf("read test:open file(%s) error : %d\r\n", szTestFileName, retSD);
        return -1;
    }
 
    FIL fTestW;
    retSD = f_open(&fTestW, szTestFileName, FA_WRITE | FA_OPEN_APPEND);
    if(FR_OK != retSD)
    {
        //printf("write test:open file(%s) error : %d\r\n", szTestFileName, retSD);
        return -1;
    }
		
		FIL fTestR2;
    retSD = f_open(&fTestR2, szTestFileName, FA_READ);
    if(FR_OK != retSD)
    {
        //printf("read2 test:open file(%s) error : %d\r\n", szTestFileName, retSD);
        return -1;
    }
		
	FIL fTestW2;
    retSD = f_open(&fTestW2, szTestFileName, FA_WRITE | FA_OPEN_APPEND);
    if(FR_OK != retSD)
    {// 这个会返回失败，因为已经打开一个写入
        //printf("write2 test:open file(%s) error : %d\r\n", szTestFileName, retSD);
        //return -1;
    }
 
    {
        char bufRead[512];
        f_lseek(&fTestR, 100);
        UINT br = 0;
        retSD = f_read(&fTestR, bufRead, 500, &br);
        bufRead[br] = 0;
        //printf("retSD:%d, read Data:%s\r\n", retSD, bufRead);
    }
    {
        char bufWrite[50] = "abcdefghijklmnopqrstuvwxyz";
        UINT bw = 0;
        retSD = f_write(&fTestW, bufWrite, 26, &bw);
        //printf("retSD:%d, write Data(%d):%s\r\n", retSD, bw, bufWrite);
    }
    {
        char bufRead[512];
        f_lseek(&fTestR2, 10002);
        UINT br = 0;
        retSD = f_read(&fTestR2, bufRead, 500, &br);
        bufRead[br] = 0;
        //printf("retSD:%d, read Data:%s\r\n", retSD, bufRead);
    }
 
    retSD = f_close(&fTestR);
	retSD = f_close(&fTestR2);
    retSD = f_close(&fTestW);
 
    return 0;
}


extern FATFS USERFatFS;
char *do_get_dir(COMM_TYPE_t commType,const void *command,void *para) {
    DIR dir;
    FILINFO fileinfo;
    FATFS *pfs = &USERFatFS;
    DWORD fre_clust, fre_size, tot_size;
    uint8_t result = f_getfree( "NAND:", &fre_clust, &pfs );
    if( result == FR_OK )
    {
		// 总容量计算方法
        // pfs->csize 该参数代表一个簇占用几个 SD卡物理扇区，每个扇区512字节
        // pfs->n_fatent 簇的数量+2
        // 总容量 = 总簇数*一个簇占用大小
        // 剩余容量 = 剩余簇数*一个簇占用大小
        tot_size = (pfs->n_fatent - 2) * pfs->csize/2; // K
        fre_size = fre_clust * pfs->csize/2;           // K
        debug_printf(commType,"----Flash Infor----\r\n");
        debug_printf(commType,"Flash total size:%d <KB>,Remain size:%d <KB>\r\n",tot_size,fre_size);
    }
        
    debug_printf(commType,"----FILE List----\r\n");
    if(f_opendir(&dir,(const char*)"NAND:") == FR_OK)
    {
        while(f_readdir(&dir, &fileinfo) == FR_OK)
        {
            if(!fileinfo.fname[0]) break;
            
            if (fileinfo.fattrib & AM_DIR) {
                debug_printf(commType,"<D> \t%s\r\n", fileinfo.fname);
            } else {
                debug_printf(commType,"[F] %8d<Byte>\t%s\r\n", fileinfo.fsize,fileinfo.fname);
            }
        }
    }
    return NULL;
}

#include "my_stm32_ftl.h"

char *do_fs_format(COMM_TYPE_t commType,const void *command,void *para) {
    //taskENTER_CRITICAL();
    FTL_Init();
    FTL_Format();
    NVIC_SystemReset();
    //taskEXIT_CRITICAL();
    return NULL;
}

//#include "proj_paras.h"
//extern Dev_paras_t Dev_paras;
char *do_get_sysinfor(COMM_TYPE_t commType,const void *command,void *para) {
    sys_infor_print(commType);
    return NULL;
}

char *do_get_realdata(COMM_TYPE_t commType,const void *command,void *para) {
    bat_infor_print(commType);
    return NULL;
}

char *do_enter_test_mode(COMM_TYPE_t commType,const void *command,void *para) {
    
    return NULL;
}


char *do_clear_alarms(COMM_TYPE_t commType,const void *command,void *para) {
    if(clear_alarm_data()){
        debug_printf(commType,"Clear alarm records OK.\r\n");
    } else {
        debug_printf(commType,"Clear alarm records failed.\r\n");
    }
    return NULL;
}

char *do_clear_hisdata(COMM_TYPE_t commType,const void *command,void *para) {
    if(clear_history_data()) {
        debug_printf(commType,"Clear history records OK.\r\n");
    } else {
        debug_printf(commType,"Clear history records Failed.\r\n");
    }
    return NULL;
}

char *do_softreset(COMM_TYPE_t commType,const void *command,void *para) {
    debug_printf(commType,"System reseting...\r\n");
    System_SoftReset();
    
}

const DEBUG_COMMAND_t commandList[] = {
    {"AT+GETTASKINFO?",do_get_task_infor},
    {"AT+LOGGER=0",    do_clear_logger_infor},
    {"AT+LOGGER?",     do_get_logger_infor},
    //{"AT+HARDFAULT",   do_generate_hardfault},
    {"AT+DIR?",        do_get_dir},
    {"AT+FSFORMAT",    do_fs_format},
    {"AT+SYSINFOR?",   do_get_sysinfor},
    {"AT+REALDATA?",   do_get_realdata},
    {"AT+CLRALARMS",   do_clear_alarms},
    {"AT+CLRHISDATA",  do_clear_hisdata},
    {"AT+SOFTRESET",   do_softreset},

};

#define MAX_COMMAND sizeof(commandList)/sizeof(commandList[0])
    
bool commandHandle(COMM_TYPE_t commType,char *command,void *para) {
    for(uint8_t index = 0; index < MAX_COMMAND; index++) {
        char *pIndexCmdStr = strstr(command, commandList[index].command);

        if(pIndexCmdStr != NULL) {
            if(commandList[index].pFun != NULL) {
                char *response = commandList[index].pFun(commType,command,para);
                return true;
            }
        }
    }
    
    return false;
}


