//==============================================================================================================================
#ifndef UG_V01_H
#define UG_V01_H
//-----------------------------------------------------------------------------------------------------------------------------
#include "STM32F10X_V01.h"
//==============================================================================================================================
//interface function name=APP_*
void UG_APP_IMM_Event(void);
void UG_APP_INT_Event(void);
void UG_APP_TMR_Event(void);
void UG_APP_TMR(UINT8 Index);
void UG_APP_Init(UINT8 IsAfter);
void UG_Para_WriteItem(UINT16 Offset,UINT8 *s,UINT16 sLen);
void UG_Para_ReadItem(UINT16 Offset,UINT8 *s,UINT16 sLen);
void UG_Para_Default(void);
void UG_Para_Write(void);
void UG_Para_Read(void);
void UG_Init_Chips(void);
void UG_PowerOn(void);
void UG_APP_IRQ_TIM(UINT8 Index);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Para_Save_Timer(void);//every 100ms
void UG_SetSleepOn(UINT8 EN);
void UG_Sleep_Timer(void);//every 100ms
void UG_LED_Timer(void);//every 1ms
//------------------------------------------------------------------------------------------------------------------------------
void UG_Key_GetState(void);
void UG_Key_RX_Timer(void);//every 5ms
void UG_PVR_RX_Timer(void);//every 1ms(100us-5ms)
void UG_Key_Save(UINT8 KeyCode,UINT8 EV);
void UG_Key_DoEvent_IMM(void);
//------------------------------------------------------------------------------------------------------------------------------
void UG_SetDeviceOn(UINT8 EN);
void UG_ChangeDeviceOn(void);
//------------------------------------------------------------------------------------------------------------------------------
void  UG_COM_Connect_TurnOn(UINT16 Index);
void  UG_COM_Connect_TurnOff(UINT16 Index);
void  UG_COM_Connect_Timer(void);//every 10ms
void  UG_COM_VerifySend(void);
void  UG_COM_Save_BUS(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void  UG_COM_Packet_Timer(void);//every 1ms
UINT8 UG_COM_IsHead(UINT16 Index,UINT8 BUFIndex,UINT8 *Head,UINT8 HeadLen);
void  UG_COM_ClearRX(UINT16 Index,UINT8 ClearHead);
UINT16 UG_COM_AddrToPort(UINT16 Index);//根据目标地址求目标端口（必须针对产品修改此函数),一般可以用高位表示端口编码地址，针对这种情况，可以处理此函数；当然也可以把端口号当成单独的地址，路径就会多一级。
UINT8 UG_COM_SetPort(UINT8 *s,UINT8 PortLen,UINT16 PortIndex,UINT8 IsOutput);
UINT8 UG_COM_GetPort(UINT8 *s,UINT8 PortLen,UINT16 *PortIndex,UINT8 IsOutput);
void  UG_COM_TXRelayFrame(UINT16 Index,UINT8 IsEnd);//中继发送
void  UG_COM_RXNoise(UINT16 Index,UINT8 Pos,UINT16 Len);
void  UG_COM_RXSubFrame(UINT16 Index,UINT8 IsEnd);
void  UG_COM_SetBack(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void UG_COM_ReadPacket(UINT16 Index,UINT8* s,UINT16 Count);
void UG_COM_ReadPacket_EMPTY(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadPacket_LS_V1(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadPacket_LS_V2(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadPacket_DMX512(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadPacket_LDY_V2(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadPacket_YY_BLT(UINT16 Index,UINT8 *s,UINT16 Count);
//------------------------------------------------------------------------------------------------------------------------------
void UG_COM_ReadParameter(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadParameter_EMPTY(UINT16 Index,UINT8 IsEnd);
void UG_COM_ReadParameter_LS_V1(UINT8 OB,UINT8 *s,UINT16 Count);
void UG_COM_ReadParameter_LS_V2(UINT8 OB,UINT8 *s,UINT16 Count);
void UG_COM_ReadParameter_DMX512(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadParameter_LDY_V2(UINT16 Index,UINT8 *s,UINT16 Count);
void UG_COM_ReadParameter_YY_BLT(UINT8 *s,UINT16 Count);
void UG_COM_ReadParameter_YY_NRF(UINT8 *s,UINT16 Count);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Read_DPStr(void);
void UG_SetPWState(void);
void UG_Event_Clear(void);
void UG_Send_State(void);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Write_BaseDT(void);
void UG_Write_MadeDT(void);
void UG_Write_HS(void);
void UG_Write_NSN(void);
//------------------------------------------------------------------------------------------------------------------------------
//extern void UGMain(void);
//==============================================================================================================================
#endif
//==============================================================================================================================


