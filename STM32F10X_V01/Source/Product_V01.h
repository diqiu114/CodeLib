//==============================================================================================================================
#ifndef Product_V01_H
#define Product_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
//by LDY,2022/7/27
//-----------------------------------------------------------------------------------------------------------------------------
//ACR:every 4 bit
//bit1_0=MODE:0=Input,1=Out_10M,2=Out_2M,3=Out_50M
//bit3_2=CNF:Input(0=Analog,1=Floating,2=PU/PD,3=Reserved),Output(0=PushPull,1=OpenDrain,2=ALTF_PushPull,3=ALTF_OpenDrain)
//==============================================================================================================================
//PIN_GPIOA
#define PI_AIN0         GPIO[0].IDR_BIT.B0//ADC_IN0
#define PI_AIN1         GPIO[0].IDR_BIT.B1//ADC_IN1
#define PI_AIN2         GPIO[0].IDR_BIT.B2//ADC_IN2
#define PI_AIN3         GPIO[0].IDR_BIT.B3//ADC_IN3
#define PI_AIN4         GPIO[0].IDR_BIT.B4//ADC_IN4
#define PI_AIN5         GPIO[0].IDR_BIT.B5//BAT
#define PI_KEY1         GPIO[0].IDR_BIT.B6//KEY1
#define PI_KEY2         GPIO[0].IDR_BIT.B7//KEY2
#define PI_KEY3         GPIO[0].IDR_BIT.B8//KEY3
#define PI_KEY4         GPIO[0].IDR_BIT.B9//KEY4
#define PO_USB_CONN     GPIO[0].ODR_BIT.B10//USB_CONN
#define PIO_USB_DM      GPIO[0].IDR_BIT.B11//USB_DM,D-
#define PIO_USB_DP      GPIO[0].IDR_BIT.B12//USB_DP,D+
#define PIO_SWDIO       GPIO[0].ODR_BIT.B13//SWDIO
#define PO_SWCLK        GPIO[0].ODR_BIT.B14//SWCLK
#define PO_RSVD0        GPIO[0].ODR_BIT.B15//Reserved

#define V_GPIOACRL      0x44000000//config
#define V_GPIOACRH      0x38844344//config
#define V_GPIOAODR      0x0000A03F//output
//-----------------------------------------------------------------------------------------------------------------------------
//PIN_GPIOB
#define PO_RSVD1        GPIO[1].ODR_BIT.B0//Reserved
#define PO_A7190_CKO    GPIO[1].ODR_BIT.B1//A7190_CKO
#define PO_A7190_GPIO2  GPIO[1].ODR_BIT.B2//A7190_GPIO2
#define PO_RSVD2        GPIO[1].ODR_BIT.B3//Reserved
#define PO_RSVD3        GPIO[1].ODR_BIT.B4//Reserved
#define PO_SY8810_LED1  GPIO[1].ODR_BIT.B5//SY8810_LED1
#define PO_SY8810_LED2  GPIO[1].ODR_BIT.B6//SY8810_LED1
#define PO_SY8810_LED3  GPIO[1].ODR_BIT.B7//SY8810_LED1
#define PO_RSVD4        GPIO[1].ODR_BIT.B8//Reserved
#define PO_RSVD5        GPIO[1].ODR_BIT.B9//Reserved
#define PO_LED_D2H      GPIO[1].ODR_BIT.B10//LED_D2H
#define PO_LED_D7H      GPIO[1].ODR_BIT.B11//LED_D7H
#define PO_A7190_SCS    GPIO[1].ODR_BIT.B12//A7190_SCS
#define PO_A7190_SCK    GPIO[1].ODR_BIT.B13//A7190_SCK
#define PO_A7190_GPIO1  GPIO[1].ODR_BIT.B14//A7190_GPIO1
#define PO_A7190_SDIO   GPIO[1].ODR_BIT.B15//A7190_SDIO

#define V_GPIOBCRL      0x33300330
#define V_GPIOBCRH      0x33333300
#define V_GPIOBODR      0x00000000
//-----------------------------------------------------------------------------------------------------------------------------
//PIN_GPIOC
#define PO_USB_SW       GPIO[2].IDR_BIT.B13//USBPW
#define PO_LED_RX       GPIO[2].ODR_BIT.B14//LED_RX
#define PO_LED_TX       GPIO[2].ODR_BIT.B15//LED_TX

#define V_GPIOCCRL      0x00000000
#define V_GPIOCCRH      0x33400000
#define V_GPIOCODR      0x00000000
//-----------------------------------------------------------------------------------------------------------------------------
#define USB_SetPullUp(EN)       PO_USB_CONN=!EN
//==============================================================================================================================
//interface function name=APP_*
void APP_IMM_Event(void);
void APP_INT_Event(void);
void APP_TMR_Event(void);
void APP_TMR(UINT8 Index);
void APP_Init(UINT8 IsAfter);
void Para_WriteItem(UINT16 Offset,UINT8 *s,UINT16 sLen);
void Para_ReadItem(UINT16 Offset,UINT8 *s,UINT16 sLen);
void Para_Default(void);
void Para_Write(void);
void Para_Read(void);
void Init_Chips(void);
void PowerOn(void);
void APP_IRQ_TIM(UINT8 Index);
void APP_ADC_Control(UINT8 Index);
void APP_DMA_Control(UINT8 Index,UINT8 CHIndex);
void APP_EXTI_Control(UINT8 Index);
//------------------------------------------------------------------------------------------------------------------------------
void Para_Save_Timer(void);//every 100ms
void SetSleepOn(UINT8 EN);
void Sleep_Timer(void);//every 100ms
//------------------------------------------------------------------------------------------------------------------------------
void Key_GetState(void);
void Key_RX_Timer(void);//every 5ms
void PVR_RX_Timer(void);//every 1ms(100us-5ms)
void Key_Save(UINT8 KeyCode,UINT8 EV);
void Key_DoEvent_IMM(void);
//------------------------------------------------------------------------------------------------------------------------------
void SetDeviceOn(UINT8 EN);
void ChangeDeviceOn(void);
//------------------------------------------------------------------------------------------------------------------------------
void  COM_Connect_TurnOn(UINT16 Index);
void  COM_Connect_TurnOff(UINT16 Index);
void  COM_Connect_Timer(void);//every 10ms
void  COM_VerifySend(void);
void  COM_Save_BUS(UINT16 Index);
void  COM_LED_Timer(void);//every 1ms
void  COM_Packet_Timer(void);//every 1ms
//------------------------------------------------------------------------------------------------------------------------------
UINT8 COM_IsHead(UINT16 Index,UINT8 BUFIndex,UINT8 *Head,UINT8 HeadLen);
void  COM_ClearRX(UINT16 Index,UINT8 ClearHead);
UINT16 COM_AddrToPort(UINT16 Index);//根据目标地址求目标端口（必须针对产品修改此函数),一般可以用高位表示端口编码地址，针对这种情况，可以处理此函数；当然也可以把端口号当成单独的地址，路径就会多一级。
UINT8 COM_SetPort(UINT8 *s,UINT8 PortLen,UINT16 PortIndex,UINT8 IsOutput);
UINT8 COM_GetPort(UINT8 *s,UINT8 PortLen,UINT16 *PortIndex,UINT8 IsOutput);
void  COM_TXRelayFrame(UINT16 Index,UINT8 IsEnd);//中继发送
void  COM_RXNoise(UINT16 Index,UINT8 Pos,UINT16 Len);
void  COM_RXSubFrame(UINT16 Index,UINT8 IsEnd);
void  COM_SetBack(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void COM_ReadPacket(UINT16 Index,UINT8* s,UINT16 Count);
void COM_ReadPacket_EMPTY(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadPacket_LS_V1(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadPacket_LS_V2(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadPacket_DMX512(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadPacket_LDY_V2(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadPacket_YY_BLT(UINT16 Index,UINT8 *s,UINT16 Count);
//------------------------------------------------------------------------------------------------------------------------------
void COM_ReadParameter(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadParameter_EMPTY(UINT16 Index,UINT8 IsEnd);
void COM_ReadParameter_LS_V1(UINT8 OB,UINT8 *s,UINT16 Count);
void COM_ReadParameter_LS_V2(UINT8 OB,UINT8 *s,UINT16 Count);
void COM_ReadParameter_DMX512(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadParameter_LDY_V2(UINT16 Index,UINT8 *s,UINT16 Count);
void COM_ReadParameter_YY_BLT(UINT8 *s,UINT16 Count);
void COM_ReadParameter_YY_NRF(UINT8 *s,UINT16 Count);
//------------------------------------------------------------------------------------------------------------------------------
void Read_DPStr(void);
void SetPWState(void);
void Event_Clear(void);
void Send_State(void);
//------------------------------------------------------------------------------------------------------------------------------
void Write_BaseDT(void);
void Write_MadeDT(void);
void Write_HS(void);
void Write_NSN(void);
//==============================================================================================================================
#endif
//==============================================================================================================================


