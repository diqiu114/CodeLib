//==============================================================================================================================
#ifndef UG_MEM_V01_H
#define UG_MEM_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
#define UG_DC_NameVer           "UG_V01"
#define UG_DC_FirstRun          UG_DC_NameVer
//------------------------------------------------------------------------------------------------------------------------------
//TIM
#define UG_TIM16_ReloadValue    100//us,[0,65535]
#define UG_TIM17_ReloadValue    200//us,[0,65535]
//------------------------------------------------------------------------------------------------------------------------------
//AppPara
#define UG_AppPara_RunTime      0
#define UG_AppPara_RunCount     4
#define UG_AppPara_Len          8
//==============================================================================================================================
extern const UINT8              UG_Device_BaseDT[],UG_Device_MadeDT[],UG_Device_HS[],UG_Device_NSN[],UG_Device_ID[];
extern const UINT8              UG_Device_CP[],UG_Device_NV[],UG_Device_FirstRun[],UG_Device_MadePos[],UG_Device_RunPos[];
extern const UINT8              UG_Device_BKP[],UG_AppPara[];
extern const UINT32             UG_SET_GPIO[][3];
extern const UINT16             UG_AppPara_Area_DelayTime[],UG_Key_CC[],UG_Key_LongTime[],UG_PVR_UD[][8];
extern const UINT32             UG_SPI_BAUD[],UG_UART_BAUD[];
extern const UINT8              UG_SPI_BAUD_COUNT,UG_SPI_BaudIndex[],UG_UART_BAUD_COUNT,UG_UART_BaudIndex[];
extern const UINT16             UG_PRTC_Time[][2],UG_PRTC[],UG_PRTC_UART1[],UG_PRTC_UART2[];
//==============================================================================================================================
#endif
//==============================================================================================================================
