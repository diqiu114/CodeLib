#ifndef __LOG_RECODER_H__
#define __LOG_RECODER_H__

#ifdef __cplusplus
 extern "C" {
#endif
#include <stdbool.h>     
#include <stdint.h>
#include <string.h>
#include "bsp_flash.h"
#include "debug.h"

/* logger type */
typedef enum {
    LOG_TYPE_None = 0,
	LOG_TYPE_RESET,
	LOG_TYPE_OPERATE,
	LOG_TYPE_EXCEPTION,
	LOG_TYPE_MAX,
} LOG_TYPE_t;


#define LOGGER_WITH_FS   0
     
/* logger date */
typedef struct {
    uint32_t sec    : 6;
    uint32_t min    : 6;
    uint32_t hour   : 5;
    uint32_t day    : 5;
    uint32_t month  : 4;
    uint32_t year   : 6; 
} DATE_yymmddhhmmss_Bit;

typedef union {
    uint32_t        date;
    DATE_yymmddhhmmss_Bit bits;
} DATE_yymmddhhmmss_t;
     
#include <stdint.h>

typedef enum {
    LOGGER_RESET = 0,
    LOGGER_CONFIG,
    LOGGER_OPERATE,
    LOGGER_ALARM,
    LOGGER_EXCEPT,
    LOGGER_WARNING,
    LOGGER_OTHERS,
    LOGGER_TYPE_MAX,
}LOGGER_TYPE_t;

typedef enum {
    LOGGER_MORE_NONE = 0,
    LOGGER_MORE_FS_FORMAT,
    LOGGER_MORE_FILE_CREATE,
    LOGGER_MOER_FILE_WIRTE_OPEN_FAILED,
}LOGGER_MORE_INFOR_t;

typedef struct {
    uint32_t      type;         //日志的类型复位、异常、操作、配置等等
    uint32_t      more;         //日志的详细信息枚举类型，比如格式化等
    uint8_t       file[32];     //日志产生的文件
    uint32_t      line;         //日志产生文件的行号
    union {                     //共用体存储更详细的信息 
        uint8_t       d1[40];   //存储一些字符串信息，比如函数名，或者自己一些告警信息等
        uint16_t      d2[20];
        uint32_t      d4[10];   //比如寄存器的值（R0,R1,R2,...LR、PC等）存在d4中
    }v;
}logger_msg_t;

typedef struct {
    uint32_t                 sum;    //日志的校验信息 crc32校验
    DATE_yymmddhhmmss_t      time;   //日志产生的时间
    uint32_t                 index;  //日志的存储索引，存储算法相关
    logger_msg_t             msg;    //日志的详细信息
}logger_t;

#define LOGGER_MAX_SIZE        (256 * 1024u)
#define LOGGER_START_ADDR       ADDR_FLASH_SECTOR_10
#define LOGGER_END_ADDR        (LOGGER_START_ADDR +  LOGGER_MAX_SIZE)


#define LOGGER_SECTOR_SIZE        (128 * 1024u)
#define INDEX_LOGGER_OF_SECTOR    (LOGGER_SECTOR_SIZE/sizeof(logger_t))
#define INDEX_LOGGER_MAX_NUMBER   (LOGGER_MAX_SIZE / sizeof(logger_t))
    
void logger_infor_load(COMM_TYPE_t commType,bool load);
void logger_infor_clear(void);
void logger_infor_save(logger_msg_t msg);
void logger_infor_save_more(LOGGER_TYPE_t type,LOGGER_MORE_INFOR_t more,uint32_t infor,const char *str,const char *file,uint16_t line);
void logger_set_reset_reg(void);
void rtc_get_time(DATE_yymmddhhmmss_t *time);
#ifdef __cplusplus
}
#endif

#endif
