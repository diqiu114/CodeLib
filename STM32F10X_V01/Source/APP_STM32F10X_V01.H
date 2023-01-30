//==============================================================================================================================
#ifndef APP_STM32F10X_V01_H
#define APP_STM32F10X_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
extern const UINT32     BASE_ADC[],BASE_SPI[],BASE_TIM[],BASE_UART[],DTF_P_Count,DTF_P[][2];
//==============================================================================================================================
#define assert_param(expr)     ((expr) ? (void)0 : assert_failed((UINT8 *)__FILE__, __LINE__))
void assert_failed(UINT8* file, UINT32 line);
//------------------------------------------------------------------------------------------------------------------------------
//interrupt function
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void RSVD_N9_Handler(void);
void RSVD_N8_Handler(void);
void RSVD_N7_Handler(void);
void RSVD_N6_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void RSVD_N3_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
//------------------------------------------------------------------------------------------------------------------------------
void WWDG_IRQHandler(void);//Window Watchdog
void PVD_IRQHandler(void);//PVD through EXTI Line detect
void TAMPER_IRQHandler(void);//Tamper
void RTC_IRQHandler(void);//RTC
void FLASH_IRQHandler(void);//Flash
void RCC_IRQHandler(void);//RCC
void EXTI0_IRQHandler(void);//EXTI Line 0
void EXTI1_IRQHandler(void);//EXTI Line 1
void EXTI2_IRQHandler(void);//EXTI Line 2
void EXTI3_IRQHandler(void);//EXTI Line 3
void EXTI4_IRQHandler(void);//EXTI Line 4
void DMA1_Channel1_IRQHandler(void);//DMA1 Channel 1
void DMA1_Channel2_IRQHandler(void);//DMA1 Channel 2
void DMA1_Channel3_IRQHandler(void);//DMA1 Channel 3
void DMA1_Channel4_IRQHandler(void);//DMA1 Channel 4
void DMA1_Channel5_IRQHandler(void);//DMA1 Channel 5
void DMA1_Channel6_IRQHandler(void);//DMA1 Channel 6
void DMA1_Channel7_IRQHandler(void);//DMA1 Channel 7
//
void ADC12_IRQHandler(void);// ADC1_2
void USB1HP_CAN1TX_IRQHandler(void);//USB1 High Priority or CAN1 TX
void USB1LP_CAN1RX0_IRQHandler(void);//USB1 Low  Priority or CAN1 RX0
void CAN1RX1_IRQHandler(void);//CAN1 RX1
void CAN1SCE_IRQHandler(void);//CAN1 SCE
void EXTI9_5_IRQHandler(void);//EXTI Line 9..5
void TIM1_BRK_IRQHandler(void);//TIM1 Break
void TIM1_UP_IRQHandler(void);//TIM1 Update
void TIM1_TRGCOM_IRQHandler(void);//TIM1 Trigger and Commutation
void TIM1_CC_IRQHandler(void);//TIM1 Capture Compare
void TIM2_IRQHandler(void);//TIM2
void TIM3_IRQHandler(void);//TIM3
void TIM4_IRQHandler(void);//TIM4
void I2C1_EV_IRQHandler(void);//I2C1 Event
void I2C1_ER_IRQHandler(void);//I2C1 Error
void I2C2_EV_IRQHandler(void);//I2C2 Event
void I2C2_ER_IRQHandler(void);//I2C2 Error
void SPI1_IRQHandler(void);//SPI1
void SPI2_IRQHandler(void);//SPI2
void USART1_IRQHandler(void);//USART1
void USART2_IRQHandler(void);//USART2
void USART3_IRQHandler(void);//USART3
void EXTI15_10_IRQHandler(void);//EXTI Line 15..10
void RTCAlarm_IRQHandler(void);//RTC Alarm through EXTI Line
void USBWakeUp_IRQHandler(void);//USB Wakeup from suspend
void USB2HP_IRQHandler(void);
void USB2LP_IRQHandler(void);
//==============================================================================================================================
void Init(void);
void Init_SFR(void);
void Init_RCC(void);
void Init_PWR(void);
void Init_SYS(void);
void Init_FLASH(void);
void Init_IWDG(void);
void Init_WWDG(void);
void Init_FSMC(void);
void Init_GPIO(void);
void Init_AFIO(void);
void Init_EXTI(void);
void Init_SYSTICK(void);
void Init_RTC(void);
void Init_TIM(void);
void Init_ADC(void);
void Init_DAC(void);
void Init_I2C(void);
void Init_SPI(void);
void Init_I2S(void);
void Init_CAN(void);
void Init_ETH(void);
void Init_USB(void);
void Init_USBFS(void);
void Init_UART(void);
void Init_SDIO(void);
void Init_MEM(UINT8 IsAfter);
void Init_IEIP(void);
void Init_DisableAll(void);
void Init_JumpAPP(void);
//==============================================================================================================================
void ADC_SetClock(UINT8 Index);
void ADC_IRQ_Control(UINT8 Index);
void DMA_IRQ_Control(UINT8 Index,UINT8 CHIndex);
void EXTI_IRQ_Control(UINT8 Index);//Index:Line Index=0_15
//------------------------------------------------------------------------------------------------------------------------------
void I2C_Event_Control(UINT16 Index);
void I2C_Error_Control(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void SPI_IRQ_Control(UINT8 Index);
//------------------------------------------------------------------------------------------------------------------------------
void Uart_IRQ_Control(UINT16 Index);
void Uart_Reset(UINT16 Index);
void Uart_Read(UINT16 Index);
void Uart_Write(UINT16 Index);
void Uart_SendBUF(UINT16 Index);
void Uart_StartSendItem(UINT16 Index);
void Uart_EndSendItem(UINT16 Index);
void Uart_WaitSend(UINT16 Index);//User call
void Uart_SetClock(UINT16 Index,UINT8 EN);//CLK=72M(Uart1) or 36M(Uart2_5)
void Uart_SetBaud(UINT16 Index);//CLK=72M(Uart1) or 36M(Uart2_5), BRR= CLK/Baud
void Uart_SetIRQ(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void CAN_Read(UINT16 Index,UINT8 FIFOIndex);
void CAN_Write(UINT16 Index);
void CAN_SendBUF(UINT16 Index);
void CAN_StartSendItem(UINT16 Index);
void CAN_EndSendItem(UINT16 Index);
void CAN_WaitSend(UINT16 Index);//User call
UINT32 CAN_GetID(UINT16 Index,UINT8 IsFilter,UINT8 IsBroadcast);//User call
void CAN_SetClock(UINT16 Index,UINT8 EN);
//------------------------------------------------------------------------------------------------------------------------------
void USB_OVR_CallBack(void);
void USB_ERR_CallBack(void);
void USB_SOF_CallBack(void);
void USB_Suspend(void);
void USB_SetEPType(UINT8 EPIndex,UINT8 Type);
void USB_SetRXSTAT(UINT8 EPIndex,UINT8 RXSTAT);
void USB_SetTXSTAT(UINT8 EPIndex,UINT8 TXSTAT);
void USB_SetRXTXSTAT(UINT8 EPIndex,UINT8 RXSTAT,UINT8 TXSTAT);
void USB_Clear_KIND(UINT8 EPIndex);
void USB_Set_KIND(UINT8 EPIndex);
void USB_ToggleDTOG(UINT8 EPIndex,UINT8 IsTX);
void USB_SetRXCount(UINT8 EPIndex,UINT16 Count);
UINT16 USB_CountToRXCount(UINT16 Count);
void USB_SetEPAddress(UINT8 EPIndex,UINT8 EPAddr);
void USB_SetDeviceAddress(UINT8 DEVAddr);
void USB_SetAddress(UINT8 DEVAddr);
void USB_SetData(UINT8 EPIndex,UINT8 *s,UINT16 Count);
void USB_GetData(UINT8 EPIndex,UINT8 *s,UINT16 Count);
//------------------------------------------------------------------------------------------------------------------------------
UINT16 COM_BUFSize(UINT16 Index,UINT8 IsTX);
void COM_StartSend(UINT16 Index);
void COM_EndSend(UINT16 Index);
void COM_StartSendItem(UINT16 Index);//针对中断式发送(因为立即与定时都有各自进程)
void COM_EndSendItem(UINT16 Index);//针对中断式发送(因为立即与定时都有各自进程)
void COM_SendString(UINT16 Index,UINT8 *s,UINT16 Count,UINT32 Time);//UART+CAN+ETH+USB
void COM_Printf(UINT16 Index,UINT32 Time,UINT8 *Data,...);
void COM_Send_Timer(void);//Every 100us
UINT16 COM_PRTC_CodeToIndex(UINT16 PRTC_Code);
void  COM_PRTC_Init(UINT16 Index);
void  COM_PRTC_Timer(void);//every 100ms;
//------------------------------------------------------------------------------------------------------------------------------
void GPIO_SetPinMode(UINT16 PinNumber,UINT8 Mode);
void GPIO_SetMultiPinMode(UINT8 GPIOIndex,UINT32 PinMark,UINT8 Mode);
void GPIO_Init(volatile Type_GPIO* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
//------------------------------------------------------------------------------------------------------------------------------
void SPI_SetClock(UINT8 Index,UINT8 EN);
Type_Setup_SPI SPI_SetupFrom(UINT8 EN,UINT8 CPHA,UINT8 CPOL,UINT8 BR,UINT8 ALF,UINT8 BIDMode);
//------------------------------------------------------------------------------------------------------------------------------
void I2C_SetClock(UINT8 Index,UINT8 EN);
//------------------------------------------------------------------------------------------------------------------------------
void EXTI_SetIRQ(UINT8 Index);
Type_Setup_EXT EXTI_SetupFrom(UINT8 EN,UINT8 PN,UINT8 Rising,UINT8 Falling);
//==============================================================================================================================
void Flash_UnLock(void);
void Flash_Lock(void);
Flash_Status Flash_GetStatus(UINT8 IsBank2);
Flash_Status Flash_WaitForLastOperation(UINT8 IsBank2,UINT32 Timeout);
Flash_Status Flash_ReadOutProtection(UINT8 IsBank2,UINT8 EN);
Flash_Status Flash_EnableWriteProtection(UINT8 IsBank2,UINT32 FLASH_Pages);
Flash_Status Flash_EraseAddress(UINT32 Address);
Flash_Status Flash_ErasePage(UINT16 Page);//Page=0_127
Flash_Status Flash_EraseALL(void);
Flash_Status Flash_EraseOptionBytes(UINT8 IsBank2);
Flash_Status Flash_UserOptionByteConfig(UINT16 OB_IWDG,UINT16 OB_STOP,UINT16 OB_STDBY);
//------------------------------------------------------------------------------------------------------------------------------
void Flash_ReadString(UINT32 Address,UINT8 *s,UINT16 Len);
UINT16 Flash_WriteString(UINT32 Address,UINT8 *s,UINT16 Len);
void Flash_WriteItem(UINT32 Address,UINT8 *s,UINT16 Len);
UINT8 Flash_IsNew(void);
//==============================================================================================================================
UINT8 SYS_Dentify(UINT64 DV);
extern void AppMain(void);
//==============================================================================================================================
#endif
//==============================================================================================================================

