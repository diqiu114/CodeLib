#ifndef __DEBUG_H_
#define __DEBUG_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
#include <stdint.h>
#include <stdbool.h>     

typedef enum {
    errOK = 0,
    errErr,
    errBuzy,
    

}errStatus_t;

typedef enum {
    COMM_TYPE_COM = 0,
    COMM_TYPE_485,
    COMM_TYPE_ETH,
    COMM_TYPE_USB,
}COMM_TYPE_t;
#define PROTOCOL_TIME_OUT  50
#define PROTOCOL_RX_SIZE   512
typedef struct {
    uint32_t tick;
    uint8_t  buffer[PROTOCOL_RX_SIZE];
    uint16_t length;
} ProtocolMsg_t;

extern ProtocolMsg_t protocolRxMsg;
     
void debug_printf(COMM_TYPE_t commType,const char *fmt, ...);
void debug_sendstring(COMM_TYPE_t commType,char * msg);
bool commandHandle(COMM_TYPE_t commType,char *command,void *para);
    
   
#ifdef __cplusplus
}
#endif


#endif
