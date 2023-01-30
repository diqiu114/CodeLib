//==============================================================================================================================
#ifndef UG_STM32F10X_V01_H
#define UG_STM32F10X_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
extern UINT32 const             UG_BASE_ADC[],UG_BASE_SPI[],UG_BASE_TIM[],UG_BASE_UART[],UG_DTF_P_Count,UG_DTF_P[][2];
//==============================================================================================================================
#define UG_assert_param(expr)     ((expr) ? (void)0 : UG_assert_failed((UINT8 *)__FILE__, __LINE__))
//------------------------------------------------------------------------------------------------------------------------------
void UG_assert_failed(UINT8* file, UINT32 line);
//------------------------------------------------------------------------------------------------------------------------------
//interrupt function
void UG_NMI_Handler(void);
void UG_HardFault_Handler(void);
void UG_MemManage_Handler(void);
void UG_BusFault_Handler(void);
void UG_UsageFault_Handler(void);
void UG_RSVD_N9_Handler(void);
void UG_RSVD_N8_Handler(void);
void UG_RSVD_N7_Handler(void);
void UG_RSVD_N6_Handler(void);
void UG_SVC_Handler(void);
void UG_DebugMon_Handler(void);
void UG_RSVD_N3_Handler(void);
void UG_PendSV_Handler(void);
void UG_SysTick_Handler(void);
//
void UG_WWDG_IRQHandler(void);//Window Watchdog
void UG_PVD_IRQHandler(void);//PVD through EXTI Line detect
void UG_TAMPER_IRQHandler(void);//Tamper
void UG_RTC_IRQHandler(void);//RTC
void UG_FLASH_IRQHandler(void);//Flash
void UG_RCC_IRQHandler(void);//RCC
void UG_EXTI0_IRQHandler(void);//EXTI Line 0
void UG_EXTI1_IRQHandler(void);//EXTI Line 1
void UG_EXTI2_IRQHandler(void);//EXTI Line 2
void UG_EXTI3_IRQHandler(void);//EXTI Line 3
void UG_EXTI4_IRQHandler(void);//EXTI Line 4
void UG_DMA1_Channel1_IRQHandler(void);//DMA1 Channel 1
void UG_DMA1_Channel2_IRQHandler(void);//DMA1 Channel 2
void UG_DMA1_Channel3_IRQHandler(void);//DMA1 Channel 3
void UG_DMA1_Channel4_IRQHandler(void);//DMA1 Channel 4
void UG_DMA1_Channel5_IRQHandler(void);//DMA1 Channel 5
void UG_DMA1_Channel6_IRQHandler(void);//DMA1 Channel 6
void UG_DMA1_Channel7_IRQHandler(void);//DMA1 Channel 7
void UG_ADC12_IRQHandler(void);// ADC1_2
void UG_USB1HP_CAN1TX_IRQHandler(void);//USB1 High Priority or CAN1 TX
void UG_USB1LP_CAN1RX0_IRQHandler(void);//USB1 Low  Priority or CAN1 RX0
void UG_CAN1RX1_IRQHandler(void);//CAN1 RX1
void UG_CAN1SCE_IRQHandler(void);//CAN1 SCE
void UG_EXTI9_5_IRQHandler(void);//EXTI Line 9..5
void UG_TIM1_BRK_IRQHandler(void);//TIM1 Break
void UG_TIM1_UP_IRQHandler(void);//TIM1 Update
void UG_TIM1_TRGCOM_IRQHandler(void);//TIM1 Trigger and Commutation
void UG_TIM1_CC_IRQHandler(void);//TIM1 Capture Compare
void UG_TIM2_IRQHandler(void);//TIM2
void UG_TIM3_IRQHandler(void);//TIM3
void UG_TIM4_IRQHandler(void);//TIM4
void UG_I2C1_EV_IRQHandler(void);//I2C1 Event
void UG_I2C1_ER_IRQHandler(void);//I2C1 Error
void UG_I2C2_EV_IRQHandler(void);//I2C2 Event
void UG_I2C2_ER_IRQHandler(void);//I2C2 Error
void UG_SPI1_IRQHandler(void);//SPI1
void UG_SPI2_IRQHandler(void);//SPI2
void UG_USART1_IRQHandler(void);//USART1
void UG_USART2_IRQHandler(void);//USART2
void UG_USART3_IRQHandler(void);//USART3
void UG_EXTI15_10_IRQHandler(void);//EXTI Line 15..10
void UG_RTCAlarm_IRQHandler(void);//RTC Alarm through EXTI Line
void UG_USBWakeUp_IRQHandler(void);//USB Wakeup from suspend
void UG_USB2HP_IRQHandler(void);
void UG_USB2LP_IRQHandler(void);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Init(void);
void UG_Init_SFR(void);
void UG_Init_RCC(void);
void UG_Init_PWR(void);
void UG_Init_SYS(void);
void UG_Init_FLASH(void);
void UG_Init_IWDG(void);
void UG_Init_WWDG(void);
void UG_Init_FSMC(void);
void UG_Init_GPIO(void);
void UG_Init_AFIO(void);
void UG_Init_EXTI(void);
void UG_Init_SYSTICK(void);
void UG_Init_RTC(void);
void UG_Init_TIM(void);
void UG_Init_ADC(void);
void UG_Init_DAC(void);
void UG_Init_I2C(void);
void UG_Init_SPI(void);
void UG_Init_I2S(void);
void UG_Init_CAN(void);
void UG_Init_ETH(void);
void UG_Init_USB(void);
void UG_Init_USBFS(void);
void UG_Init_UART(void);
void UG_Init_SDIO(void);
void UG_Init_MEM(UINT8 IsAfter);
void UG_Init_IEIP(void);
void UG_Init_DisableAll(void);
void UG_Init_JumpAPP(void);
//------------------------------------------------------------------------------------------------------------------------------
void UG_ADC_SetClock(UINT8 Index);
void UG_ADC_IRQ_Control(UINT8 Index);
void UG_DMA_IRQ_Control(UINT8 Index,UINT8 CHIndex);
void UG_EXTI_IRQ_Control(UINT8 Index);//Index:Line Index=0_15
//------------------------------------------------------------------------------------------------------------------------------
void UG_I2C_Event_Control(UINT16 Index);
void UG_I2C_Error_Control(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void UG_SPI_IRQ_Control(UINT8 Index);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Uart_IRQ_Control(UINT16 Index);
void UG_Uart_Reset(UINT16 Index);
void UG_Uart_Read(UINT16 Index);
void UG_Uart_Write(UINT16 Index);
void UG_Uart_SendBUF(UINT16 Index);
void UG_Uart_StartSendItem(UINT16 Index);
void UG_Uart_EndSendItem(UINT16 Index);
void UG_Uart_WaitSend(UINT16 Index);//User call
void UG_Uart_SetClock(UINT16 Index,UINT8 EN);//CLK=72M(Uart1) or 36M(Uart2_5)
void UG_Uart_SetBaud(UINT16 Index);//CLK=72M(Uart1) or 36M(Uart2_5), BRR= CLK/Baud
void UG_Uart_SetIRQ(UINT16 Index);
//------------------------------------------------------------------------------------------------------------------------------
void UG_CAN_Read(UINT16 Index,UINT8 FIFOIndex);
void UG_CAN_Write(UINT16 Index);
void UG_CAN_SendBUF(UINT16 Index);
void UG_CAN_StartSendItem(UINT16 Index);
void UG_CAN_EndSendItem(UINT16 Index);
void UG_CAN_WaitSend(UINT16 Index);//User call
UINT32 UG_CAN_GetID(UINT16 Index,UINT8 IsFilter,UINT8 IsBroadcast);//User call
void UG_CAN_SetClock(UINT16 Index,UINT8 EN);
//------------------------------------------------------------------------------------------------------------------------------
void UG_USB_OVR_CallBack(void);
void UG_USB_ERR_CallBack(void);
void UG_USB_SOF_CallBack(void);
void UG_USB_Suspend(void);
void UG_USB_SetEPType(UINT8 EPIndex,UINT8 Type);
void UG_USB_SetRXSTAT(UINT8 EPIndex,UINT8 RXSTAT);
void UG_USB_SetTXSTAT(UINT8 EPIndex,UINT8 TXSTAT);
void UG_USB_SetRXTXSTAT(UINT8 EPIndex,UINT8 RXSTAT,UINT8 TXSTAT);
void UG_USB_Clear_KIND(UINT8 EPIndex);
void UG_USB_Set_KIND(UINT8 EPIndex);
void UG_USB_ToggleDTOG(UINT8 EPIndex,UINT8 IsTX);
void UG_USB_SetRXCount(UINT8 EPIndex,UINT16 Count);
UINT16 UG_USB_CountToRXCount(UINT16 Count);
void UG_USB_SetEPAddress(UINT8 EPIndex,UINT8 EPAddr);
void UG_USB_SetDeviceAddress(UINT8 DEVAddr);
void UG_USB_SetAddress(UINT8 DEVAddr);
void UG_USB_SetData(UINT8 EPIndex,UINT8 *s,UINT16 Count);
void UG_USB_GetData(UINT8 EPIndex,UINT8 *s,UINT16 Count);
//------------------------------------------------------------------------------------------------------------------------------
UINT16 UG_COM_BUFSize(UINT16 Index,UINT8 IsTX);
void UG_COM_StartSend(UINT16 Index);
void UG_COM_EndSend(UINT16 Index);
void UG_COM_StartSendItem(UINT16 Index);//针对中断式发送(因为立即与定时都有各自进程)
void UG_COM_EndSendItem(UINT16 Index);//针对中断式发送(因为立即与定时都有各自进程)
void UG_COM_SendString(UINT16 Index,UINT8 *s,UINT16 Count,UINT32 Time);//UART+CAN+ETH+USB
void UG_COM_Printf(UINT16 Index,UINT32 Time,UINT8 *Data,...);
void UG_COM_Send_Timer(void);//Every 100us
UINT16 UG_COM_PRTC_CodeToIndex(UINT16 PRTC_Code);
void UG_COM_PRTC_Init(UINT16 Index);
void UG_COM_PRTC_Timer(void);//every 100ms;
//------------------------------------------------------------------------------------------------------------------------------
void UG_GPIO_SetPinMode(UINT16 PinNumber,UINT8 Mode);
void UG_GPIO_SetMultiPinMode(UINT8 GPIOIndex,UINT32 PinMark,UINT8 Mode);
void UG_GPIO_Init(volatile Type_GPIO* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void UG_NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
//------------------------------------------------------------------------------------------------------------------------------
void UG_SPI_SetClock(UINT8 Index,UINT8 EN);
Type_Setup_SPI UG_SPI_SetupFrom(UINT8 EN,UINT8 CPHA,UINT8 CPOL,UINT8 BR,UINT8 ALF,UINT8 BIDMode);
//------------------------------------------------------------------------------------------------------------------------------
void UG_I2C_SetClock(UINT8 Index,UINT8 EN);
//------------------------------------------------------------------------------------------------------------------------------
void UG_EXTI_SetIRQ(UINT8 Index);
Type_Setup_EXT UG_EXTI_SetupFrom(UINT8 EN,UINT8 PN,UINT8 Rising,UINT8 Falling);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Flash_UnLock(void);
void UG_Flash_Lock(void);
Flash_Status UG_Flash_GetStatus(UINT8 IsBank2);
Flash_Status UG_Flash_WaitForLastOperation(UINT8 IsBank2,UINT32 Timeout);
Flash_Status UG_Flash_ReadOutProtection(UINT8 IsBank2,UINT8 EN);
Flash_Status UG_Flash_EnableWriteProtection(UINT8 IsBank2,UINT32 FLASH_Pages);
Flash_Status UG_Flash_EraseAddress(UINT32 Address);
Flash_Status UG_Flash_ErasePage(UINT16 Page);//Page=0_127
Flash_Status UG_Flash_EraseALL(void);
Flash_Status UG_Flash_EraseOptionBytes(UINT8 IsBank2);
Flash_Status UG_Flash_UserOptionByteConfig(UINT16 OB_IWDG,UINT16 OB_STOP,UINT16 OB_STDBY);
//------------------------------------------------------------------------------------------------------------------------------
void UG_Flash_ReadString(UINT32 Address,UINT8 *s,UINT16 Len);
UINT16 UG_Flash_WriteString(UINT32 Address,UINT8 *s,UINT16 Len);
void UG_Flash_WriteItem(UINT32 Address,UINT8 *s,UINT16 Len);
UINT8 UG_Flash_IsNew(void);
//==============================================================================================================================
UINT8 UG_Flash_Dentify(UINT64 DV);
extern void UGMain(void);
//==============================================================================================================================
#endif
//==============================================================================================================================

