#ifndef _MODULES_DEF_H_
#define _MODULES_DEF_H_

#define USE_FREE_RTOS (1)
#define IPV4 (4)

#if( USE_FREE_RTOS )
  #include "cmsis_os.h"
  #define DELAY_MS(x) vTaskDelay(x)
#else
  #define DELAY_MS(x) HAL_Delay(x) 
#endif

typedef unsigned char Ip[IPV4];

#endif // _MODULES_DEF_H_
