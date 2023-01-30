//==============================================================================================================================
#ifndef STM32F10x_V01_H
#define STM32F10x_V01_H
//==============================================================================================================================
#include "APP_Common_V01.h"
#include "UG_Common_V01.h"
//==============================================================================================================================
//STM32F10X_V01 program library, which  whatever the chips and the pdf datasheets
//The LIB can fastest edit and run and boot user program,and ensure no error in user program,run speed has nothing with progsize
//The LIB has highest run efficiency and fastest respond speed, the programmer must learned LDY program theory
//The LIB be Maked only by LDY at whole world
//by LDY, 2019/04/25,QQ:184324486 ,MB:18377381136
//==============================================================================================================================
//2 bit for BOOT MODE:B(x0)=Main flash memory(BOOT1 use as IO),B(01)=System memory,B(11)=Embedded SRAM
//M3 Flash:
//代码(0.5G):0x00000000-0x1fffffff
//SRAM(0.5G):0x20000000-0x3fffffff
//SRAM_bitband:0x22000000-0x23ffffff
//外设(0.5G):0x40000000-0x5fffffff
//外设bitband:0x42000000-0x43ffffff
//外部RAM(1GB):0x60000000-0x7fffffff,0x80000000-0x9fffffff
//外部设备(1GB):0xA0000000-0xBfffffff,0xC0000000-0xDfffffff
//专用外设总线:0xE0000000-0xE00FFFFF
//系统:0xE0100000-0xffffffff
//CAN与USB1不能同时共用
//==============================================================================================================================
#define CPUType_F100X4  0//LD
#define CPUType_F100X6  1//LD
#define CPUType_F100X8  2//LD
#define CPUType_F100XB  3//MD
#define CPUType_F101X4  4//LD
#define CPUType_F101X6  5//LD
#define CPUType_F101XC  6//HD
#define CPUType_F101XD  7//HD
#define CPUType_F101XE  8//HD
#define CPUType_F102X4  9//LD
#define CPUType_F102X6  10//LD
#define CPUType_F102X8  11//MD
#define CPUType_F102XB  12//MD
#define CPUType_F103X4  13//LD
#define CPUType_F103X6  14//LD
#define CPUType_F103X8  15//MD
#define CPUType_F103XB  16//MD
#define CPUType_F103XC  17//HD
#define CPUType_F103XD  18//HD
#define CPUType_F103XE  19//HD,FLASH=256-512K,SRAM=64K
#define CPUType_F105XX  20//CL
#define CPUType_F107XX  21//CL
#define CPUType         CPUType_F103XB
#define IsCPUType(name) (CPUType==CPUType_##name)
//==============================================================================================================================
#define Density_LD      0//16-32k
#define Density_LD_VL   1//16-32k
#define Density_MD      2//64-128k
#define Density_MD_VL   3//64-128k
#define Density_HD      4//256-512k
#define Density_HD_VL   5//256-512k
#define Density_XL      6//512-1024k
#define Density_CL      7//STM32F105xx,STM32F107xx
#define Density         Density_MD  
#define IsDensity(name) (Density==Density_##name)
#if Density>7
 #error "Please select first the target STM32F10x device used in your application (in STM32F10X_V01.h file)"
#endif
//==============================================================================================================================
//Bank1-NOR/PSRAM,4 sectors,bit27_26=sector index,bit25_0=address
#define BASE_FSMC_BANK1S0_START 0x60000000
#define BASE_FSMC_BANK1S0_END   0x63FFFFFF
#define BASE_FSMC_BANK1S1_START 0x64000000
#define BASE_FSMC_BANK1S1_END   0x67FFFFFF
#define BASE_FSMC_BANK1S2_START 0x68000000
#define BASE_FSMC_BANK1S2_END   0x6BFFFFFF
#define BASE_FSMC_BANK1S3_START 0x6C000000
#define BASE_FSMC_BANK1S3_END   0x6FFFFFFF
#define BASE_FSMC_BANK1_CH(i)   (0x60000000|(i<<26))//i=0_3=sector index
//RS PIN,数据命令区分线
#define BASE_FSMC_BANK1RS_A0    ((1<<1)-2)
#define BASE_FSMC_BANK1RS_A1    ((1<<2)-2)
#define BASE_FSMC_BANK1RS_A2    ((1<<3)-2)
#define BASE_FSMC_BANK1RS_A3    ((1<<4)-2)
#define BASE_FSMC_BANK1RS_A4    ((1<<5)-2)
#define BASE_FSMC_BANK1RS_A5    ((1<<6)-2)
#define BASE_FSMC_BANK1RS_A6    ((1<<7)-2)
#define BASE_FSMC_BANK1RS_A7    ((1<<8)-2)
#define BASE_FSMC_BANK1RS_A8    ((1<<9)-2)
#define BASE_FSMC_BANK1RS_A9    ((1<<10)-2)
#define BASE_FSMC_BANK1RS_A10   ((1<<11)-2)
#define BASE_FSMC_BANK1RS_A11   ((1<<12)-2)
#define BASE_FSMC_BANK1RS_A12   ((1<<13)-2)
#define BASE_FSMC_BANK1RS_A13   ((1<<14)-2)
#define BASE_FSMC_BANK1RS_A14   ((1<<15)-2)
#define BASE_FSMC_BANK1RS_A15   ((1<<16)-2)
#define BASE_FSMC_BANK1RS_A16   ((1<<17)-2)
#define BASE_FSMC_BANK1RS_A17   ((1<<18)-2)
#define BASE_FSMC_BANK1RS_A18   ((1<<19)-2)
#define BASE_FSMC_BANK1RS_A19   ((1<<20)-2)
#define BASE_FSMC_BANK1RS_A20   ((1<<21)-2)
#define BASE_FSMC_BANK1RS_A21   ((1<<22)-2)
#define BASE_FSMC_BANK1RS_A22   ((1<<23)-2)
#define BASE_FSMC_BANK1RS_A23   ((1<<24)-2)
#define BASE_FSMC_BANK1RS_A24   ((1<<25)-2)
#define BASE_FSMC_BANK1RS_A25   ((1<<26)-2)
#define BASE_FSMC_BANK1RS_A(i)  ((1<<(i+1))-2)//i=0_25=RS PIN Index
//Bank2-NAND FLASH,PATT2(6C),PMEM2(68)
#define BASE_FSMC_BANK2A_START  0x70000000
#define BASE_FSMC_BANK2A_END    0x73FFFFFF
#define BASE_FSMC_BANK2B_START  0x78000000
#define BASE_FSMC_BANK2B_END    0x7BFFFFFF
//Bank3-NAND FLASH,PATT3(8C),PMEM3(88)
#define BASE_FSMC_BANK3A_START  0x80000000
#define BASE_FSMC_BANK3A_END    0x83FFFFFF
#define BASE_FSMC_BANK3B_START  0x88000000
#define BASE_FSMC_BANK3B_END    0x8BFFFFFF
//Bank4-PC CARD,PATT4(AC),PMEM4(A8)
#define BASE_FSMC_BANK4A_START  0x90000000
#define BASE_FSMC_BANK4A_END    0x93FFFFFF
#define BASE_FSMC_BANK4B_START  0x98000000
#define BASE_FSMC_BANK4B_END    0x9BFFFFFF
//Bank4-PC CARD,PIO4(B0)
#define BASE_FSMC_BANK4C_START  0x9C000000
#define BASE_FSMC_BANK4C_END    0x9FFFFFFF
//LCD
#define LCD_CH                  0x00
#define LCD_RS                  0x10
#if     LCD_RS
#define BASE_LCD                ((BASE_FSMC_BANK1_CH(LCD_CH)|BASE_FSMC_BANK1RS_A(LCD_RS))-2)//align 4 bytes
#else   
#define BASE_LCD                BASE_FSMC_BANK1_CH(LCD_CH)
#endif
//==============================================================================================================================
#define SIZE_FLASHPAGE          0x00000400//1k
#define BASE_FLASH              0x08000000//FLASH base address in the alias region,128页，每页1K
#define SIZE_FLASH              0x00020000//128K
#define BASE_SYSMEM             0x1FFFF000
#define SIZE_SYSMEM             0x00000800
#define BASE_OB                 0x1FFFF800//Flash Option Bytes base address
#define SIZE_OB                 0x00000010
#define BASE_DES                0x1FFFF7E0//Device electronic signature
#define BASE_SRAM               0x20000000//SRAM base address in the alias region
#define BASE_PERIPH             0x40000000//Peripheral base address in the alias region
#define BASE_USBFS              0x50000000//USB2.0 OTG
#define BASE_SRAM_BB            0x22000000//SRAM base address in the bit-band region
#define BASE_PERIPH_BB          0x42000000//Peripheral base address in the bit-band region
#define BASE_FSMC               0xA0000000//FSMC registers base address

#define BASE_APP                BASE_FLASH
#define BASE_DEVICE             (BASE_APP+0x00001000) //DEVICE Property
#define BASE_UG                 (BASE_FLASH+0x18000)
#define UG_BASE_DEVICE          (BASE_UG+0x00001000) //DEVICE Property
//------------------------------------------------------------------------------------------------------------------------------
#define BASE_ITM                0xE0000000//M3 ITM Base Address
#define BASE_DWT                0xE0001000//DWT,观察点和触发
#define BASE_FPB                0xE0002000//FLASH repair,修补
#define BASE_TPI                0xE0040000//跟踪端口接口单元
#define BASE_ETM                0xE0041000//ETM,嵌入式跟踪宏单元
#define BASE_DBG                0xE0042000//Debug MCU registers base address

#define BASE_SCS                0xE000E000//M3 System Control Space Base Address
#define BASE_SYS                BASE_SCS
#define BASE_SYSTICK            0xE000E010//CM3 SYSTICK
#define BASE_NVIC               0xE000E100//CM3 NVIC
#define BASE_SCB                0xE000ED00//CM3 SCB
#define BASE_MPU                0xE000ED90//CM3 MPU
#define BASE_CDB                0xE000EDF0//CM3 Debug Base Address
#define BASE_TAB                0xE00FF000//CM3 Default RAM Table Values
//------------------------------------------------------------------------------------------------------------------------------
//Peripheral memory map
#define BASE_USBFS_DATAFIFO     BASE_USBFS+0x1000
#define SIZE_USBFS_DATAFIFO     0x1000

#define BASE_APB1PERIPH         BASE_PERIPH
#define BASE_APB2PERIPH         (BASE_PERIPH + 0x10000)
#define BASE_AHBPERIPH          (BASE_PERIPH + 0x20000)
#define BASE_TIM2               (BASE_APB1PERIPH + 0x0000)
#define BASE_TIM3               (BASE_APB1PERIPH + 0x0400)
#define BASE_TIM4               (BASE_APB1PERIPH + 0x0800)
#define BASE_TIM5               (BASE_APB1PERIPH + 0x0C00)
#define BASE_TIM6               (BASE_APB1PERIPH + 0x1000)
#define BASE_TIM7               (BASE_APB1PERIPH + 0x1400)
#define BASE_TIM12              (BASE_APB1PERIPH + 0x1800)
#define BASE_TIM13              (BASE_APB1PERIPH + 0x1C00)
#define BASE_TIM14              (BASE_APB1PERIPH + 0x2000)
#define BASE_RTC                (BASE_APB1PERIPH + 0x2800)
#define BASE_WWDG               (BASE_APB1PERIPH + 0x2C00)
#define BASE_IWDG               (BASE_APB1PERIPH + 0x3000)
#define BASE_SPI2               (BASE_APB1PERIPH + 0x3800)
#define BASE_SPI3               (BASE_APB1PERIPH + 0x3C00)
#define BASE_UART2              (BASE_APB1PERIPH + 0x4400)
#define BASE_UART3              (BASE_APB1PERIPH + 0x4800)
#define BASE_UART4              (BASE_APB1PERIPH + 0x4C00)
#define BASE_UART5              (BASE_APB1PERIPH + 0x5000)
#define BASE_I2C1               (BASE_APB1PERIPH + 0x5400)
#define BASE_I2C2               (BASE_APB1PERIPH + 0x5800)
#define BASE_I2C(i)             (BASE_I2C1+i*0x400)
#define BASE_USB                (BASE_APB1PERIPH + 0x5C00)
#define BASE_USBRAM             (BASE_APB1PERIPH + 0x6000)
#define BASE_CAN1               (BASE_APB1PERIPH + 0x6400)
#define BASE_CAN2               (BASE_APB1PERIPH + 0x6800)
#define BASE_CAN(i)             (BASE_CAN1+i*0x400)
#define BASE_BKP                (BASE_APB1PERIPH + 0x6C00)
#define BASE_PWR                (BASE_APB1PERIPH + 0x7000)
#define BASE_DAC                (BASE_APB1PERIPH + 0x7400)
#define BASE_CEC                (BASE_APB1PERIPH + 0x7800)
//------------------------------------------------------------------------------------------------------------------------------
#define BASE_AFIO               (BASE_APB2PERIPH + 0x0000)
#define BASE_EXTI               (BASE_APB2PERIPH + 0x0400)
#define BASE_GPIOA              (BASE_APB2PERIPH + 0x0800)
#define BASE_GPIOB              (BASE_APB2PERIPH + 0x0C00)
#define BASE_GPIOC              (BASE_APB2PERIPH + 0x1000)
#define BASE_GPIOD              (BASE_APB2PERIPH + 0x1400)
#define BASE_GPIOE              (BASE_APB2PERIPH + 0x1800)
#define BASE_GPIOF              (BASE_APB2PERIPH + 0x1C00)
#define BASE_GPIOG              (BASE_APB2PERIPH + 0x2000)
#define BASE_GPIO(i)            (BASE_GPIOA+i*0x400)
#define BASE_ADC1               (BASE_APB2PERIPH + 0x2400)
#define BASE_ADC2               (BASE_APB2PERIPH + 0x2800)
#define BASE_TIM1               (BASE_APB2PERIPH + 0x2C00)
#define BASE_SPI1               (BASE_APB2PERIPH + 0x3000)
#define BASE_TIM8               (BASE_APB2PERIPH + 0x3400)
#define BASE_UART1              (BASE_APB2PERIPH + 0x3800)
#define BASE_ADC3               (BASE_APB2PERIPH + 0x3C00)
#define BASE_TIM15              (BASE_APB2PERIPH + 0x4000)
#define BASE_TIM16              (BASE_APB2PERIPH + 0x4400)
#define BASE_TIM17              (BASE_APB2PERIPH + 0x4800)
#define BASE_TIM9               (BASE_APB2PERIPH + 0x4C00)
#define BASE_TIM10              (BASE_APB2PERIPH + 0x5000)
#define BASE_TIM11              (BASE_APB2PERIPH + 0x5400)
#define BASE_SDIO               (BASE_APB2PERIPH + 0x8000)
//------------------------------------------------------------------------------------------------------------------------------
#define BASE_DMA1               (BASE_AHBPERIPH + 0x0000)
#define BASE_DMA1_CH1           (BASE_AHBPERIPH + 0x0008)
#define BASE_DMA1_CH2           (BASE_AHBPERIPH + 0x001C)
#define BASE_DMA1_CH3           (BASE_AHBPERIPH + 0x0030)
#define BASE_DMA1_CH4           (BASE_AHBPERIPH + 0x0044)
#define BASE_DMA1_CH5           (BASE_AHBPERIPH + 0x0058)
#define BASE_DMA1_CH6           (BASE_AHBPERIPH + 0x006C)
#define BASE_DMA1_CH7           (BASE_AHBPERIPH + 0x0080)
#define BASE_DMA2               (BASE_AHBPERIPH + 0x0400)
#define BASE_DMA2_CH1           (BASE_AHBPERIPH + 0x0408)
#define BASE_DMA2_CH2           (BASE_AHBPERIPH + 0x041C)
#define BASE_DMA2_CH3           (BASE_AHBPERIPH + 0x0430)
#define BASE_DMA2_CH4           (BASE_AHBPERIPH + 0x0444)
#define BASE_DMA2_CH5           (BASE_AHBPERIPH + 0x0458)
#define BASE_DMA(i)             (BASE_DMA1+i*0x400)
#define BASE_RCC                (BASE_AHBPERIPH + 0x1000)
#define BASE_FLASHR             (BASE_AHBPERIPH + 0x2000) //Flash registers base address
#define BASE_CRC                (BASE_AHBPERIPH + 0x3000)

#define BASE_ETH                (BASE_AHBPERIPH + 0x8000)
#define BASE_ETH_MAC            (BASE_ETH)
#define BASE_ETH_MMC            (BASE_ETH + 0x0100)
#define BASE_ETH_PTP            (BASE_ETH + 0x0700)
#define BASE_ETH_DMA            (BASE_ETH + 0x1000)

#define BASE_FSMC_Bank1         (BASE_FSMC + 0x0000) //FSMC Bank1 registers base address
#define BASE_FSMC_Bank2         (BASE_FSMC + 0x0060) //FSMC Bank2 registers base address
#define BASE_FSMC_Bank3         (BASE_FSMC + 0x0080) //FSMC Bank3 registers base address
#define BASE_FSMC_Bank4         (BASE_FSMC + 0x00A0) //FSMC Bank4 registers base address
#define BASE_FSMC_Bank1E        (BASE_FSMC + 0x0104) //FSMC Bank1E registers base address
//------------------------------------------------------------------------------------------------------------------------------
//Cortex-M3 Processor Exceptions Numbers
#define IRQN_NonMaskableInt        -14  //2 Non Maskable Interrupt
#define IRQN_MemoryManagement      -12  //4 Cortex-M3 Memory Management Interrupt
#define IRQN_BusFault              -11  //5 Cortex-M3 Bus Fault Interrupt
#define IRQN_UsageFault            -10  //6 Cortex-M3 Usage Fault Interrupt
#define IRQN_SVCall                -5   //11 Cortex-M3 SV Call Interrupt
#define IRQN_DebugMonitor          -4   //12 Cortex-M3 Debug Monitor Interrupt
#define IRQN_PendSV                -2   //14 Cortex-M3 Pend SV Interrupt
#define IRQN_SysTick               -1   //15 Cortex-M3 System Tick Interrupt
//STM32 specific Interrupt Numbers
#define IRQN_WWDG                  0    //Window WatchDog Interrupt
#define IRQN_PVD                   1    //PVD through EXTI Line detection Interrupt
#define IRQN_TAMPER                2    //Tamper Interrupt
#define IRQN_RTC                   3    //RTC global Interrupt
#define IRQN_FLASH                 4    //FLASH global Interrupt
#define IRQN_RCC                   5    //RCC global Interrupt
#define IRQN_EXTI0                 6    //EXTI Line0 Interrupt
#define IRQN_EXTI1                 7    //EXTI Line1 Interrupt
#define IRQN_EXTI2                 8    //EXTI Line2 Interrupt
#define IRQN_EXTI3                 9    //EXTI Line3 Interrupt
#define IRQN_EXTI4                 10   //EXTI Line4 Interrupt
#define IRQN_DMA1_CH1              11   //DMA1 Channel 1 global Interrupt
#define IRQN_DMA1_CH2              12   //DMA1 Channel 2 global Interrupt
#define IRQN_DMA1_CH3              13   //DMA1 Channel 3 global Interrupt
#define IRQN_DMA1_CH4              14   //DMA1 Channel 4 global Interrupt
#define IRQN_DMA1_CH5              15   //DMA1 Channel 5 global Interrupt
#define IRQN_DMA1_CH6              16   //DMA1 Channel 6 global Interrupt
#define IRQN_DMA1_CH7              17   //DMA1 Channel 7 global Interrupt

#if IsDensity(LD)
#define IRQN_ADC12                 18   //ADC1 and ADC2 global Interrupt
#define IRQN_USB1HP_CAN1TX         19   //USB1 Device High Priority or CAN1 TX Interrupts
#define IRQN_USB1LP_CAN1RX0        20   //USB1 Device Low Priority or CAN1 RX0 Interrupts
#define IRQN_CAN1_RX1              21   //CAN1 RX1 Interrupt
#define IRQN_CAN1_SCE              22   //CAN1 SCE Interrupt
#define IRQN_EXTI9_5               23   //External Line[9:5] Interrupts
#define IRQN_TIM1_BRK              24   //TIM1 Break Interrupt
#define IRQN_TIM1_UP               25   //TIM1 Update Interrupt
#define IRQN_TIM1_TRGCOM           26   //TIM1 Trigger and Commutation Interrupt
#define IRQN_TIM1_CCn              27   //TIM1 Capture Compare Interrupt
#define IRQN_TIM2                  28   //TIM2 global Interrupt
#define IRQN_TIM3                  29   //TIM3 global Interrupt
#define IRQN_I2C1_EV               31   //I2C1 Event Interrupt
#define IRQN_I2C1_ER               32   //I2C1 Error Interrupt
#define IRQN_SPI1                  35   //SPI1 global Interrupt
#define IRQN_USART1                37   //USART1 global Interrupt
#define IRQN_USART2                38   //USART2 global Interrupt
#define IRQN_EXTI15_10             40   //External Line[15:10] Interrupts
#define IRQN_RTCAlarm              41   //RTC Alarm through EXTI Line Interrupt
#define IRQN_USBWakeUp             42   //USB Device WakeUp from suspend through EXTI Line Interrupt
#endif

#if IsDensity(LD_VL)
#define IRQN_ADC1                  18   //ADC1 global Interrupt
#define IRQN_EXTI9_5               23   //External Line[9:5] Interrupts
#define IRQN_TIM1_BRK_TIM15        24   //TIM1 Break and TIM15 Interrupts
#define IRQN_TIM1_UP_TIM16         25   //TIM1 Update and TIM16 Interrupts
#define IRQN_TIM1_TRGCOM_TIM17     26   //TIM1 Trigger and Commutation and TIM17 Interrupt
#define IRQN_TIM1_CC               27   //TIM1 Capture Compare Interrupt
#define IRQN_TIM2                  28   //TIM2 global Interrupt
#define IRQN_TIM3                  29   //TIM3 global Interrupt
#define IRQN_I2C1_EV               31   //I2C1 Event Interrupt
#define IRQN_I2C1_ER               32   //I2C1 Error Interrupt
#define IRQN_SPI1                  35   //SPI1 global Interrupt
#define IRQN_USART1                37   //USART1 global Interrupt
#define IRQN_USART2                38   //USART2 global Interrupt
#define IRQN_EXTI15_10             40   //External Line[15:10] Interrupts
#define IRQN_RTCAlarm              41   //RTC Alarm through EXTI Line Interrupt
#define IRQN_CEC                   42   //HDMI-CEC Interrupt
#define IRQN_TIM6_DAC              54   //TIM6 and DAC underrun Interrupt
#define IRQN_TIM7                  55   //TIM7 Interrupt
#endif //LD_VL

#if IsDensity(MD)
  #define IRQN_ADC12               18   //ADC1 and ADC2 global Interrupt
  #define IRQN_USB1HP_CAN1TX       19   //USB1 Device High Priority or CAN1 TX Interrupts
  #define IRQN_USB1LP_CAN1RX0      20   //USB1 Device Low Priority or CAN1 RX0 Interrupts
  #define IRQN_CAN1RX1             21   //CAN1 RX1 Interrupt
  #define IRQN_CAN1SCE             22   //CAN1 SCE Interrupt
  #define IRQN_EXTI9_5             23   //External Line[9:5] Interrupts
  #define IRQN_TIM1_BRK            24   //TIM1 Break Interrupt
  #define IRQN_TIM1_UP             25   //TIM1 Update Interrupt
  #define IRQN_TIM1_TRGCOM         26   //TIM1 Trigger and Commutation Interrupt
  #define IRQN_TIM1_CC             27   //TIM1 Capture Compare Interrupt
  #define IRQN_TIM2                28   //TIM2 global Interrupt
  #define IRQN_TIM3                29   //TIM3 global Interrupt
  #define IRQN_TIM4                30   //TIM4 global Interrupt
  #define IRQN_I2C1_EV             31   //I2C1 Event Interrupt
  #define IRQN_I2C1_ER             32   //I2C1 Error Interrupt
  #define IRQN_I2C2_EV             33   //I2C2 Event Interrupt
  #define IRQN_I2C2_ER             34   //I2C2 Error Interrupt
  #define IRQN_SPI1                35   //SPI1 global Interrupt
  #define IRQN_SPI2                36   //SPI2 global Interrupt
  #define IRQN_USART1              37   //USART1 global Interrupt
  #define IRQN_USART2              38   //USART2 global Interrupt
  #define IRQN_USART3              39   //USART3 global Interrupt
  #define IRQN_EXTI15_10           40   //External Line[15:10] Interrupts
  #define IRQN_RTCAlarm            41   //RTC Alarm through EXTI Line Interrupt
  #define IRQN_USBWakeUp           42   //USB Device WakeUp from suspend through EXTI Line Interrupt
#endif //MD  

#if IsDensity(MD_VL)
  #define IRQN_ADC1                18   //ADC1 global Interrupt
  #define IRQN_EXTI9_5             23   //External Line[9:5] Interrupts
  #define IRQN_TIM1_BRK_TIM15n     24   //TIM1 Break and TIM15 Interrupts
  #define IRQN_TIM1_UP_TIM16       25   //TIM1 Update and TIM16 Interrupts
  #define IRQN_TIM1_TRGCOM_TIM17   26   //TIM1 Trigger and Commutation and TIM17 Interrupt
  #define IRQN_TIM1_CC             27   //TIM1 Capture Compare Interrupt
  #define IRQN_TIM2                28   //TIM2 global Interrupt
  #define IRQN_TIM3                29   //TIM3 global Interrupt
  #define IRQN_TIM4                30   //TIM4 global Interrupt
  #define IRQN_I2C1_EV             31   //I2C1 Event Interrupt
  #define IRQN_I2C1_ER             32   //I2C1 Error Interrupt
  #define IRQN_I2C2_EV             33   //I2C2 Event Interrupt
  #define IRQN_I2C2_ER             34   //I2C2 Error Interrupt
  #define IRQN_SPI1                35   //SPI1 global Interrupt
  #define IRQN_SPI2                36   //SPI2 global Interrupt
  #define IRQN_USART1              37   //USART1 global Interrupt
  #define IRQN_USART2              38   //USART2 global Interrupt
  #define IRQN_USART3              39   //USART3 global Interrupt
  #define IRQN_EXTI15_10           40   //External Line[15:10] Interrupts
  #define IRQN_RTCAlarm            41   //RTC Alarm through EXTI Line Interrupt
  #define IRQN_CEC                 42   //HDMI-CEC Interrupt
  #define IRQN_TIM6_DAC            54   //TIM6 and DAC underrun Interrupt
  #define IRQN_TIM7                55   //TIM7 Interrupt
#endif //MD_VL

#if IsDensity(HD)
  #define IRQN_ADC12               18   //ADC1 and ADC2 global Interrupt
  #define IRQN_USB1HP_CAN1TX       19   //USB1 Device High Priority or CAN1 TX Interrupts
  #define IRQN_USB1LP_CAN1RX0      20   //USB1 Device Low Priority or CAN1 RX0 Interrupts
  #define IRQN_CAN1RX1             21   //CAN1 RX1 Interrupt
  #define IRQN_CAN1SCE             22   //CAN1 SCE Interrupt
  #define IRQN_EXTI9_5             23   //External Line[9:5] Interrupts
  #define IRQN_TIM1_BRK            24   //TIM1 Break Interrupt
  #define IRQN_TIM1_UP             25   //TIM1 Update Interrupt
  #define IRQN_TIM1_TRGCOM         26   //TIM1 Trigger and Commutation Interrupt
  #define IRQN_TIM1_CC             27   //TIM1 Capture Compare Interrupt
  #define IRQN_TIM2                28   //TIM2 global Interrupt
  #define IRQN_TIM3                29   //TIM3 global Interrupt
  #define IRQN_TIM4                30   //TIM4 global Interrupt
  #define IRQN_I2C1_EV             31   //I2C1 Event Interrupt
  #define IRQN_I2C1_ER             32   //I2C1 Error Interrupt
  #define IRQN_I2C2_EV             33   //I2C2 Event Interrupt
  #define IRQN_I2C2_ER             34   //I2C2 Error Interrupt
  #define IRQN_SPI1                35   //SPI1 global Interrupt
  #define IRQN_SPI2                36   //SPI2 global Interrupt
  #define IRQN_USART1              37   //USART1 global Interrupt
  #define IRQN_USART2              38   //USART2 global Interrupt
  #define IRQN_USART3              39   //USART3 global Interrupt
  #define IRQN_EXTI15_10           40   //External Line[15:10] Interrupts
  #define IRQN_RTCAlarm            41   //RTC Alarm through EXTI Line Interrupt
  #define IRQN_USBWakeUp           42   //USB Device WakeUp from suspend through EXTI Line Interrupt
  #define IRQN_TIM8_BRK            43   //TIM8 Break Interrupt
  #define IRQN_TIM8_UP             44   //TIM8 Update Interrupt
  #define IRQN_TIM8_TRGCOM         45   //TIM8 Trigger and Commutation Interrupt
  #define IRQN_TIM8_CC             46   //TIM8 Capture Compare Interrupt
  #define IRQN_ADC3                47   //ADC3 global Interrupt
  #define IRQN_FSMC                48   //FSMC global Interrupt
  #define IRQN_SDIO                49   //SDIO global Interrupt
  #define IRQN_TIM5                50   //TIM5 global Interrupt
  #define IRQN_SPI3                51   //SPI3 global Interrupt
  #define IRQN_UART4               52   //UART4 global Interrupt
  #define IRQN_UART5               53   //UART5 global Interrupt
  #define IRQN_TIM6                54   //TIM6 global Interrupt
  #define IRQN_TIM7                55   //TIM7 global Interrupt
  #define IRQN_DMA2_CH1            56   //DMA2 Channel 1 global Interrupt
  #define IRQN_DMA2_CH2            57   //DMA2 Channel 2 global Interrupt
  #define IRQN_DMA2_CH3            58   //DMA2 Channel 3 global Interrupt
  #define IRQN_DMA2_CH45           59   //DMA2 Channel 4 and Channel 5 global Interrupt
#endif

#if IsDensity(HD_VL)
  #define IRQN_ADC1                18   //ADC1 global Interrupt
  #define IRQN_EXTI9_5             23   //External Line[9:5] Interrupts
  #define IRQN_TIM1_BRK_TIM15      24   //TIM1 Break and TIM15 Interrupts
  #define IRQN_TIM1_UP_TIM16       25   //TIM1 Update and TIM16 Interrupts
  #define IRQN_TIM1_TRGCOM_TIM17   26   //TIM1 Trigger and Commutation and TIM17 Interrupt
  #define IRQN_TIM1_CC             27   //TIM1 Capture Compare Interrupt
  #define IRQN_TIM2                28   //TIM2 global Interrupt
  #define IRQN_TIM3                29   //TIM3 global Interrupt
  #define IRQN_TIM4                30   //TIM4 global Interrupt
  #define IRQN_I2C1_EV             31   //I2C1 Event Interrupt
  #define IRQN_I2C1_ER             32   //I2C1 Error Interrupt
  #define IRQN_I2C2_EV             33   //I2C2 Event Interrupt
  #define IRQN_I2C2_ER             34   //I2C2 Error Interrupt
  #define IRQN_SPI1                35   //SPI1 global Interrupt
  #define IRQN_SPI2                36   //SPI2 global Interrupt
  #define IRQN_USART1              37   //USART1 global Interrupt
  #define IRQN_USART2              38   //USART2 global Interrupt
  #define IRQN_USART3              39   //USART3 global Interrupt
  #define IRQN_EXTI15_10           40   //External Line[15:10] Interrupts
  #define IRQN_RTCAlarm            41   //RTC Alarm through EXTI Line Interrupt
  #define IRQN_CEC                 42   //HDMI-CEC Interrupt
  #define IRQN_TIM12               43   //TIM12 global Interrupt
  #define IRQN_TIM13               44   //TIM13 global Interrupt
  #define IRQN_TIM14               45   //TIM14 global Interrupt
  #define IRQN_TIM5                50   //TIM5 global Interrupt
  #define IRQN_SPI3                51   //SPI3 global Interrupt
  #define IRQN_UART4               52   //UART4 global Interrupt
  #define IRQN_UART5               53   //UART5 global Interrupt
  #define IRQN_TIM6_DAC            54   //TIM6 and DAC underrun Interrupt
  #define IRQN_TIM7                55   //TIM7 Interrupt
  #define IRQN_DMA2_CH1            56   //DMA2 Channel 1 global Interrupt
  #define IRQN_DMA2_CH2            57   //DMA2 Channel 2 global Interrupt
  #define IRQN_DMA2_CH3            58   //DMA2 Channel 3 global Interrupt
  #define IRQN_DMA2_CH45           59   //DMA2 Channel 4 and Channel 5 global Interrupt
  #define IRQN_DMA2_CH5            60   //DMA2 Channel 5 global Interrupt (DMA2 Channel 5 is\
                                             mapped at position 60 only if the MISC_REMAP bit in \
                                             the AFIO_MAPR2 register is set)
#endif

#if IsDensity(XL)
  #define IRQN_ADC12               18   //ADC1 and ADC2 global Interrupt
  #define IRQN_USB1HP_CAN1TX       19   //USB1 Device High Priority or CAN1 TX Interrupts
  #define IRQN_USB1LP_CAN1RX0      20   //USB1 Device Low Priority or CAN1 RX0 Interrupts
  #define IRQN_CAN1RX1             21   //CAN1 RX1 Interrupt
  #define IRQN_CAN1SCE             22   //CAN1 SCE Interrupt
  #define IRQN_EXTI9_5             23   //External Line[9:5] Interrupts
  #define IRQN_TIM1_BRK_TIM9       24   //TIM1 Break Interrupt and TIM9 global Interrupt
  #define IRQN_TIM1_UP_TIM10       25   //TIM1 Update Interrupt and TIM10 global Interrupt
  #define IRQN_TIM1_TRGCOM_TIM11   26   //TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt
  #define IRQN_TIM1_CC             27   //TIM1 Capture Compare Interrupt
  #define IRQN_TIM2                28   //TIM2 global Interrupt
  #define IRQN_TIM3                29   //TIM3 global Interrupt
  #define IRQN_TIM4                30   //TIM4 global Interrupt
  #define IRQN_I2C1_EV             31   //I2C1 Event Interrupt
  #define IRQN_I2C1_ER             32   //I2C1 Error Interrupt
  #define IRQN_I2C2_EV             33   //I2C2 Event Interrupt
  #define IRQN_I2C2_ER             34   //I2C2 Error Interrupt
  #define IRQN_SPI1                35   //SPI1 global Interrupt
  #define IRQN_SPI2                36   //SPI2 global Interrupt
  #define IRQN_USART1              37   //USART1 global Interrupt
  #define IRQN_USART2              38   //USART2 global Interrupt
  #define IRQN_USART3              39   //USART3 global Interrupt
  #define IRQN_EXTI15_10           40   //External Line[15:10] Interrupts
  #define IRQN_RTCAlarm            41   //RTC Alarm through EXTI Line Interrupt
  #define IRQN_USBWakeUp           42   //USB Device WakeUp from suspend through EXTI Line Interrupt
  #define IRQN_TIM8_BRK_TIM12      43   //TIM8 Break Interrupt and TIM12 global Interrupt
  #define IRQN_TIM8_UP_TIM13       44   //TIM8 Update Interrupt and TIM13 global Interrupt
  #define IRQN_TIM8_TRGCOM_TIM14   45   //TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt
  #define IRQN_TIM8_CC             46   //TIM8 Capture Compare Interrupt
  #define IRQN_ADC3                47   //ADC3 global Interrupt
  #define IRQN_FSMC                48   //FSMC global Interrupt
  #define IRQN_SDIO                49   //SDIO global Interrupt
  #define IRQN_TIM5                50   //TIM5 global Interrupt
  #define IRQN_SPI3                51   //SPI3 global Interrupt
  #define IRQN_UART4               52   //UART4 global Interrupt
  #define IRQN_UART5               53   //UART5 global Interrupt
  #define IRQN_TIM6                54   //TIM6 global Interrupt
  #define IRQN_TIM7                55   //TIM7 global Interrupt
  #define IRQN_DMA2_CH1            56   //DMA2 Channel 1 global Interrupt
  #define IRQN_DMA2_CH2            57   //DMA2 Channel 2 global Interrupt
  #define IRQN_DMA2_CH3            58   //DMA2 Channel 3 global Interrupt
  #define IRQN_DMA2_CH45           59   //DMA2 Channel 4 and Channel 5 global Interrupt
#endif

#if IsDensity(CL)
  #define IRQN_ADC12               18   //ADC1 and ADC2 global Interrupt
  #define IRQN_USB1HP_CAN1TX       19   //USB1 Device High Priority or CAN1 TX Interrupts
  #define IRQN_USB1LP_CAN1RX0      20   //USB1 Device Low Priority or CAN1 RX0 Interrupts
  #define IRQN_CAN1RX1             21   //CAN1 RX1 Interrupt
  #define IRQN_CAN1SCE             22   //CAN1 SCE Interrupt
  #define IRQN_EXTI9_5             23   //External Line[9:5] Interrupts
  #define IRQN_TIM1_BRK            24   //TIM1 Break Interrupt
  #define IRQN_TIM1_UP             25   //TIM1 Update Interrupt
  #define IRQN_TIM1_TRGCOM         26   //TIM1 Trigger and Commutation Interrupt
  #define IRQN_TIM1_CC             27   //TIM1 Capture Compare Interrupt
  #define IRQN_TIM2                28   //TIM2 global Interrupt
  #define IRQN_TIM3                29   //TIM3 global Interrupt
  #define IRQN_TIM4                30   //TIM4 global Interrupt
  #define IRQN_I2C1_EV             31   //I2C1 Event Interrupt
  #define IRQN_I2C1_ER             32   //I2C1 Error Interrupt
  #define IRQN_I2C2_EV             33   //I2C2 Event Interrupt
  #define IRQN_I2C2_ER             34   //I2C2 Error Interrupt
  #define IRQN_SPI1                35   //SPI1 global Interrupt
  #define IRQN_SPI2                36   //SPI2 global Interrupt
  #define IRQN_USART1              37   //USART1 global Interrupt
  #define IRQN_USART2              38   //USART2 global Interrupt
  #define IRQN_USART3              39   //USART3 global Interrupt
  #define IRQN_EXTI15_10           40   //External Line[15:10] Interrupts
  #define IRQN_RTCAlarm            41   //RTC Alarm through EXTI Line Interrupt
  #define IRQN_OTGFS_WKUP          42   //USB OTG FS WakeUp from suspend through EXTI Line Interrupt
  #define IRQN_TIM5                50   //TIM5 global Interrupt
  #define IRQN_SPI3                51   //SPI3 global Interrupt
  #define IRQN_UART4               52   //UART4 global Interrupt
  #define IRQN_UART5               53   //UART5 global Interrupt
  #define IRQN_TIM6                54   //TIM6 global Interrupt
  #define IRQN_TIM7                55   //TIM7 global Interrupt
  #define IRQN_DMA2_CH1            56   //DMA2 Channel 1 global Interrupt
  #define IRQN_DMA2_CH2            57   //DMA2 Channel 2 global Interrupt
  #define IRQN_DMA2_CH3            58   //DMA2 Channel 3 global Interrupt
  #define IRQN_DMA2_CH4            59   //DMA2 Channel 4 global Interrupt
  #define IRQN_DMA2_CH5            60   //DMA2 Channel 5 global Interrupt
  #define IRQN_ETH                 61   //Ethernet global Interrupt
  #define IRQN_ETH_WKUP            62   //Ethernet Wakeup through EXTI line Interrupt
  #define IRQN_CAN2_TX             63   //CAN2 TX Interrupt
  #define IRQN_CAN2_RX0            64   //CAN2 RX0 Interrupt
  #define IRQN_CAN2_RX1            65   //CAN2 RX1 Interrupt
  #define IRQN_CAN2_SCE            66   //CAN2 SCE Interrupt
  #define IRQN_OTGFS               67   //USB OTG FS global Interrupt
#endif
//------------------------------------------------------------------------------------------------------------------------------
typedef enum Enum_IRQN
{
//Cortex-M3 Processor Exceptions Numbers
  NonMaskableInt_IRQn         = -14,    //2 Non Maskable Interrupt
  MemoryManagement_IRQn       = -12,    //4 Cortex-M3 Memory Management Interrupt
  BusFault_IRQn               = -11,    //5 Cortex-M3 Bus Fault Interrupt
  UsageFault_IRQn             = -10,    //6 Cortex-M3 Usage Fault Interrupt
  SVCall_IRQn                 = -5,     //11 Cortex-M3 SV Call Interrupt
  DebugMonitor_IRQn           = -4,     //12 Cortex-M3 Debug Monitor Interrupt
  PendSV_IRQn                 = -2,     //14 Cortex-M3 Pend SV Interrupt
  SysTick_IRQn                = -1,     //15 Cortex-M3 System Tick Interrupt

//STM32 specific Interrupt Numbers
  WWDG_IRQn                   = 0,      //Window WatchDog Interrupt
  PVD_IRQn                    = 1,      //PVD through EXTI Line detection Interrupt
  TAMPER_IRQn                 = 2,      //Tamper Interrupt
  RTC_IRQn                    = 3,      //RTC global Interrupt
  FLASH_IRQn                  = 4,      //FLASH global Interrupt
  RCC_IRQn                    = 5,      //RCC global Interrupt
  EXTI0_IRQn                  = 6,      //EXTI Line0 Interrupt
  EXTI1_IRQn                  = 7,      //EXTI Line1 Interrupt
  EXTI2_IRQn                  = 8,      //EXTI Line2 Interrupt
  EXTI3_IRQn                  = 9,      //EXTI Line3 Interrupt
  EXTI4_IRQn                  = 10,     //EXTI Line4 Interrupt
  DMA1_Channel1_IRQn          = 11,     //DMA1 Channel 1 global Interrupt
  DMA1_Channel2_IRQn          = 12,     //DMA1 Channel 2 global Interrupt
  DMA1_Channel3_IRQn          = 13,     //DMA1 Channel 3 global Interrupt
  DMA1_Channel4_IRQn          = 14,     //DMA1 Channel 4 global Interrupt
  DMA1_Channel5_IRQn          = 15,     //DMA1 Channel 5 global Interrupt
  DMA1_Channel6_IRQn          = 16,     //DMA1 Channel 6 global Interrupt
  DMA1_Channel7_IRQn          = 17,     //DMA1 Channel 7 global Interrupt

#if IsDensity(LD)
  ADC1_2_IRQn                 = 18,     //ADC1 and ADC2 global Interrupt
  USB_HP_CAN1_TX_IRQn         = 19,     //USB Device High Priority or CAN1 TX Interrupts
  USB_LP_CAN1_RX0_IRQn        = 20,     //USB Device Low Priority or CAN1 RX0 Interrupts
  CAN1_RX1_IRQn               = 21,     //CAN1 RX1 Interrupt
  CAN1_SCE_IRQn               = 22,     //CAN1 SCE Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_IRQn               = 24,     //TIM1 Break Interrupt
  TIM1_UP_IRQn                = 25,     //TIM1 Update Interrupt
  TIM1_TRGCOM_IRQn            = 26,     //TIM1 Trigger and Commutation Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  USBWakeUp_IRQn              = 42      //USB Device WakeUp from suspend through EXTI Line Interrupt
#endif

#if IsDensity(LD_VL)
  ADC1_IRQn                   = 18,     //ADC1 global Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_TIM15_IRQn         = 24,     //TIM1 Break and TIM15 Interrupts
  TIM1_UP_TIM16_IRQn          = 25,     //TIM1 Update and TIM16 Interrupts
  TIM1_TRGCOM_TIM17_IRQn      = 26,     //TIM1 Trigger and Commutation and TIM17 Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  CEC_IRQn                    = 42,     //HDMI-CEC Interrupt
  TIM6_DAC_IRQn               = 54,     //TIM6 and DAC underrun Interrupt
  TIM7_IRQn                   = 55      //TIM7 Interrupt
#endif

#if IsDensity(MD)
  ADC1_2_IRQn                 = 18,     //ADC1 and ADC2 global Interrupt
  USB_HP_CAN1_TX_IRQn         = 19,     //USB Device High Priority or CAN1 TX Interrupts
  USB_LP_CAN1_RX0_IRQn        = 20,     //USB Device Low Priority or CAN1 RX0 Interrupts
  CAN1_RX1_IRQn               = 21,     //CAN1 RX1 Interrupt
  CAN1_SCE_IRQn               = 22,     //CAN1 SCE Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_IRQn               = 24,     //TIM1 Break Interrupt
  TIM1_UP_IRQn                = 25,     //TIM1 Update Interrupt
  TIM1_TRGCOM_IRQn            = 26,     //TIM1 Trigger and Commutation Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  TIM4_IRQn                   = 30,     //TIM4 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  I2C2_EV_IRQn                = 33,     //I2C2 Event Interrupt
  I2C2_ER_IRQn                = 34,     //I2C2 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  SPI2_IRQn                   = 36,     //SPI2 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  USART3_IRQn                 = 39,     //USART3 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  USBWakeUp_IRQn              = 42      //USB Device WakeUp from suspend through EXTI Line Interrupt
#endif

#if IsDensity(MD_VL)
  ADC1_IRQn                   = 18,     //ADC1 global Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_TIM15_IRQn         = 24,     //TIM1 Break and TIM15 Interrupts
  TIM1_UP_TIM16_IRQn          = 25,     //TIM1 Update and TIM16 Interrupts
  TIM1_TRGCOM_TIM17_IRQn      = 26,     //TIM1 Trigger and Commutation and TIM17 Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  TIM4_IRQn                   = 30,     //TIM4 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  I2C2_EV_IRQn                = 33,     //I2C2 Event Interrupt
  I2C2_ER_IRQn                = 34,     //I2C2 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  SPI2_IRQn                   = 36,     //SPI2 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  USART3_IRQn                 = 39,     //USART3 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  CEC_IRQn                    = 42,     //HDMI-CEC Interrupt
  TIM6_DAC_IRQn               = 54,     //TIM6 and DAC underrun Interrupt
  TIM7_IRQn                   = 55      //TIM7 Interrupt
#endif

#if IsDensity(HD)
  ADC1_2_IRQn                 = 18,     //ADC1 and ADC2 global Interrupt
  USB_HP_CAN1_TX_IRQn         = 19,     //USB Device High Priority or CAN1 TX Interrupts
  USB_LP_CAN1_RX0_IRQn        = 20,     //USB Device Low Priority or CAN1 RX0 Interrupts
  CAN1_RX1_IRQn               = 21,     //CAN1 RX1 Interrupt
  CAN1_SCE_IRQn               = 22,     //CAN1 SCE Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_IRQn               = 24,     //TIM1 Break Interrupt
  TIM1_UP_IRQn                = 25,     //TIM1 Update Interrupt
  TIM1_TRGCOM_IRQn            = 26,     //TIM1 Trigger and Commutation Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  TIM4_IRQn                   = 30,     //TIM4 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  I2C2_EV_IRQn                = 33,     //I2C2 Event Interrupt
  I2C2_ER_IRQn                = 34,     //I2C2 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  SPI2_IRQn                   = 36,     //SPI2 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  USART3_IRQn                 = 39,     //USART3 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  USBWakeUp_IRQn              = 42,     //USB Device WakeUp from suspend through EXTI Line Interrupt
  TIM8_BRK_IRQn               = 43,     //TIM8 Break Interrupt
  TIM8_UP_IRQn                = 44,     //TIM8 Update Interrupt
  TIM8_TRGCOM_IRQn            = 45,     //TIM8 Trigger and Commutation Interrupt
  TIM8_CC_IRQn                = 46,     //TIM8 Capture Compare Interrupt
  ADC3_IRQn                   = 47,     //ADC3 global Interrupt
  FSMC_IRQn                   = 48,     //FSMC global Interrupt
  SDIO_IRQn                   = 49,     //SDIO global Interrupt
  TIM5_IRQn                   = 50,     //TIM5 global Interrupt
  SPI3_IRQn                   = 51,     //SPI3 global Interrupt
  UART4_IRQn                  = 52,     //UART4 global Interrupt
  UART5_IRQn                  = 53,     //UART5 global Interrupt
  TIM6_IRQn                   = 54,     //TIM6 global Interrupt
  TIM7_IRQn                   = 55,     //TIM7 global Interrupt
  DMA2_Channel1_IRQn          = 56,     //DMA2 Channel 1 global Interrupt
  DMA2_Channel2_IRQn          = 57,     //DMA2 Channel 2 global Interrupt
  DMA2_Channel3_IRQn          = 58,     //DMA2 Channel 3 global Interrupt
  DMA2_Channel4_5_IRQn        = 59      //DMA2 Channel 4 and Channel 5 global Interrupt
#endif

#if IsDensity(HD_VL)
  ADC1_IRQn                   = 18,     //ADC1 global Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_TIM15_IRQn         = 24,     //TIM1 Break and TIM15 Interrupts
  TIM1_UP_TIM16_IRQn          = 25,     //TIM1 Update and TIM16 Interrupts
  TIM1_TRGCOM_TIM17_IRQn      = 26,     //TIM1 Trigger and Commutation and TIM17 Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  TIM4_IRQn                   = 30,     //TIM4 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  I2C2_EV_IRQn                = 33,     //I2C2 Event Interrupt
  I2C2_ER_IRQn                = 34,     //I2C2 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  SPI2_IRQn                   = 36,     //SPI2 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  USART3_IRQn                 = 39,     //USART3 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  CEC_IRQn                    = 42,     //HDMI-CEC Interrupt
  TIM12_IRQn                  = 43,     //TIM12 global Interrupt
  TIM13_IRQn                  = 44,     //TIM13 global Interrupt
  TIM14_IRQn                  = 45,     //TIM14 global Interrupt
  TIM5_IRQn                   = 50,     //TIM5 global Interrupt
  SPI3_IRQn                   = 51,     //SPI3 global Interrupt
  UART4_IRQn                  = 52,     //UART4 global Interrupt
  UART5_IRQn                  = 53,     //UART5 global Interrupt
  TIM6_DAC_IRQn               = 54,     //TIM6 and DAC underrun Interrupt
  TIM7_IRQn                   = 55,     //TIM7 Interrupt
  DMA2_Channel1_IRQn          = 56,     //DMA2 Channel 1 global Interrupt
  DMA2_Channel2_IRQn          = 57,     //DMA2 Channel 2 global Interrupt
  DMA2_Channel3_IRQn          = 58,     //DMA2 Channel 3 global Interrupt
  DMA2_Channel4_5_IRQn        = 59,     //DMA2 Channel 4 and Channel 5 global Interrupt
  DMA2_Channel5_IRQn          = 60      //DMA2 Channel 5 global Interrupt (DMA2 Channel 5 is\
                                             mapped at position 60 only if the MISC_REMAP bit in\
                                             the AFIO_MAPR2 register is set)
#endif

#if IsDensity(XL)
  ADC1_2_IRQn                 = 18,     //ADC1 and ADC2 global Interrupt
  USB_HP_CAN1_TX_IRQn         = 19,     //USB Device High Priority or CAN1 TX Interrupts
  USB_LP_CAN1_RX0_IRQn        = 20,     //USB Device Low Priority or CAN1 RX0 Interrupts
  CAN1_RX1_IRQn               = 21,     //CAN1 RX1 Interrupt
  CAN1_SCE_IRQn               = 22,     //CAN1 SCE Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_TIM9_IRQn          = 24,     //TIM1 Break Interrupt and TIM9 global Interrupt
  TIM1_UP_TIM10_IRQn          = 25,     //TIM1 Update Interrupt and TIM10 global Interrupt
  TIM1_TRGCOM_TIM11_IRQn      = 26,     //TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  TIM4_IRQn                   = 30,     //TIM4 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  I2C2_EV_IRQn                = 33,     //I2C2 Event Interrupt
  I2C2_ER_IRQn                = 34,     //I2C2 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  SPI2_IRQn                   = 36,     //SPI2 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  USART3_IRQn                 = 39,     //USART3 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  USBWakeUp_IRQn              = 42,     //USB Device WakeUp from suspend through EXTI Line Interrupt
  TIM8_BRK_TIM12_IRQn         = 43,     //TIM8 Break Interrupt and TIM12 global Interrupt
  TIM8_UP_TIM13_IRQn          = 44,     //TIM8 Update Interrupt and TIM13 global Interrupt
  TIM8_TRGCOM_TIM14_IRQn      = 45,     //TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt
  TIM8_CC_IRQn                = 46,     //TIM8 Capture Compare Interrupt
  ADC3_IRQn                   = 47,     //ADC3 global Interrupt
  FSMC_IRQn                   = 48,     //FSMC global Interrupt
  SDIO_IRQn                   = 49,     //SDIO global Interrupt
  TIM5_IRQn                   = 50,     //TIM5 global Interrupt
  SPI3_IRQn                   = 51,     //SPI3 global Interrupt
  UART4_IRQn                  = 52,     //UART4 global Interrupt
  UART5_IRQn                  = 53,     //UART5 global Interrupt
  TIM6_IRQn                   = 54,     //TIM6 global Interrupt
  TIM7_IRQn                   = 55,     //TIM7 global Interrupt
  DMA2_Channel1_IRQn          = 56,     //DMA2 Channel 1 global Interrupt
  DMA2_Channel2_IRQn          = 57,     //DMA2 Channel 2 global Interrupt
  DMA2_Channel3_IRQn          = 58,     //DMA2 Channel 3 global Interrupt
  DMA2_Channel4_5_IRQn        = 59      //DMA2 Channel 4 and Channel 5 global Interrupt
#endif

#if IsDensity(CL)
  ADC1_2_IRQn                 = 18,     //ADC1 and ADC2 global Interrupt
  CAN1_TX_IRQn                = 19,     //USB Device High Priority or CAN1 TX Interrupts
  CAN1_RX0_IRQn               = 20,     //USB Device Low Priority or CAN1 RX0 Interrupts
  CAN1_RX1_IRQn               = 21,     //CAN1 RX1 Interrupt
  CAN1_SCE_IRQn               = 22,     //CAN1 SCE Interrupt
  EXTI9_5_IRQn                = 23,     //External Line[9:5] Interrupts
  TIM1_BRK_IRQn               = 24,     //TIM1 Break Interrupt
  TIM1_UP_IRQn                = 25,     //TIM1 Update Interrupt
  TIM1_TRGCOM_IRQn            = 26,     //TIM1 Trigger and Commutation Interrupt
  TIM1_CC_IRQn                = 27,     //TIM1 Capture Compare Interrupt
  TIM2_IRQn                   = 28,     //TIM2 global Interrupt
  TIM3_IRQn                   = 29,     //TIM3 global Interrupt
  TIM4_IRQn                   = 30,     //TIM4 global Interrupt
  I2C1_EV_IRQn                = 31,     //I2C1 Event Interrupt
  I2C1_ER_IRQn                = 32,     //I2C1 Error Interrupt
  I2C2_EV_IRQn                = 33,     //I2C2 Event Interrupt
  I2C2_ER_IRQn                = 34,     //I2C2 Error Interrupt
  SPI1_IRQn                   = 35,     //SPI1 global Interrupt
  SPI2_IRQn                   = 36,     //SPI2 global Interrupt
  USART1_IRQn                 = 37,     //USART1 global Interrupt
  USART2_IRQn                 = 38,     //USART2 global Interrupt
  USART3_IRQn                 = 39,     //USART3 global Interrupt
  EXTI15_10_IRQn              = 40,     //External Line[15:10] Interrupts
  RTCAlarm_IRQn               = 41,     //RTC Alarm through EXTI Line Interrupt
  OTG_FS_WKUP_IRQn            = 42,     //USB OTG FS WakeUp from suspend through EXTI Line Interrupt
  TIM5_IRQn                   = 50,     //TIM5 global Interrupt
  SPI3_IRQn                   = 51,     //SPI3 global Interrupt
  UART4_IRQn                  = 52,     //UART4 global Interrupt
  UART5_IRQn                  = 53,     //UART5 global Interrupt
  TIM6_IRQn                   = 54,     //TIM6 global Interrupt
  TIM7_IRQn                   = 55,     //TIM7 global Interrupt
  DMA2_Channel1_IRQn          = 56,     //DMA2 Channel 1 global Interrupt
  DMA2_Channel2_IRQn          = 57,     //DMA2 Channel 2 global Interrupt
  DMA2_Channel3_IRQn          = 58,     //DMA2 Channel 3 global Interrupt
  DMA2_Channel4_IRQn          = 59,     //DMA2 Channel 4 global Interrupt
  DMA2_Channel5_IRQn          = 60,     //DMA2 Channel 5 global Interrupt
  ETH_IRQn                    = 61,     //Ethernet global Interrupt
  ETH_WKUP_IRQn               = 62,     //Ethernet Wakeup through EXTI line Interrupt
  CAN2_TX_IRQn                = 63,     //CAN2 TX Interrupt
  CAN2_RX0_IRQn               = 64,     //CAN2 RX0 Interrupt
  CAN2_RX1_IRQn               = 65,     //CAN2 RX1 Interrupt
  CAN2_SCE_IRQn               = 66,     //CAN2 SCE Interrupt
  OTG_FS_IRQn                 = 67      //USB OTG FS global Interrupt
#endif    
} Type_IRQN,IRQN_Type;
//==============================================================================================================================
//直接地址申明寄存器
//SCS
#define _ICTR                   *((volatile UINT32 *)0xE000E004)//Interrupt Controller Type Register Definitions
#define _ACTLR                  *((volatile UINT32 *)0xE000E008)//Auxiliary Control Register ,for __CM3_REV >= 0x200
//NVIC
#define _STCTRL                 *((volatile UINT32 *)0xE000E010)//SysTick Control and Status Register
#define _STLOAD                 *((volatile UINT32 *)0xE000E014)//SysTick Reload Value Register
#define _STVAL                  *((volatile UINT32 *)0xE000E018)//SysTick Current Value Register
#define _STCALIB                *((volatile UINT32 *)0xE000E01C)//SysTick Calibration Register

#define _IRQE0                  *((volatile UINT32 *)0xE000E100)//IRQ0-31, Set Enable
#define _IRQE1                  *((volatile UINT32 *)0xE000E104)//IRQ32-63, Set Enable
#define _IRQE2                  *((volatile UINT32 *)0xE000E108)//IRQ64-95, Set Enable
#define _IRQE3                  *((volatile UINT32 *)0xE000E10C)//IRQ96-127, Set Enable
#define _IRQE4                  *((volatile UINT32 *)0xE000E110)//IRQ128-159, Set Enable
#define _IRQE5                  *((volatile UINT32 *)0xE000E114)//IRQ160-191, Set Enable
#define _IRQE6                  *((volatile UINT32 *)0xE000E118)//IRQ192-223, Set Enable
#define _IRQE7                  *((volatile UINT32 *)0xE000E11C)//IRQ224-239, Set Enable
#define _IRQE(i)                *((volatile UINT32 *)(0xE000E100+i*4))//i=0_7
		
#define _ICER0                  *((volatile UINT32 *)0xE000E180)//IRQ0-31,Clear Enable
#define _ICER1                  *((volatile UINT32 *)0xE000E184)//IRQ32-63,Clear Enable
#define _ICER2                  *((volatile UINT32 *)0xE000E188)//IRQ64-95,Clear Enable
#define _ICER3                  *((volatile UINT32 *)0xE000E18C)//IRQ96-127,Clear Enable
#define _ICER4                  *((volatile UINT32 *)0xE000E190)//IRQ128-159,Clear Enable
#define _ICER5                  *((volatile UINT32 *)0xE000E194)//IRQ160-191,Clear Enable
#define _ICER6                  *((volatile UINT32 *)0xE000E198)//IRQ192-223,Clear Enable
#define _ICER7                  *((volatile UINT32 *)0xE000E19C)//IRQ224-239,Clear Enable
#define _ICER(i)                *((volatile UINT32 *)(0xE000E180+i*4))//i=0_7

#define _ISPR0                  *((volatile UINT32 *)0xE000E200)//IRQ0-31,Set Pending Enable
#define _ISPR1                  *((volatile UINT32 *)0xE000E204)//IRQ32-63,Set Pending Enable
#define _ISPR2                  *((volatile UINT32 *)0xE000E208)//IRQ64-95,Set Pending Enable
#define _ISPR3                  *((volatile UINT32 *)0xE000E20C)//IRQ96-127,Set Pending Enable
#define _ISPR4                  *((volatile UINT32 *)0xE000E210)//IRQ128-159,Set Pending Enable
#define _ISPR5                  *((volatile UINT32 *)0xE000E214)//IRQ160-191,Set Pending Enable
#define _ISPR6                  *((volatile UINT32 *)0xE000E218)//IRQ192-223,Set Pending Enable
#define _ISPR7                  *((volatile UINT32 *)0xE000E21C)//IRQ224-239,Set Pending Enable
#define _ISPR(i)                *((volatile UINT32 *)(0xE000E200+i*4))//i=0_7

#define _ICPR0                  *((volatile UINT32 *)0xE000E280)//IRQ0-31,clear Pending Enable
#define _ICPR1                  *((volatile UINT32 *)0xE000E284)//IRQ32-63,clear Pending Enable
#define _ICPR2                  *((volatile UINT32 *)0xE000E288)//IRQ64-95,clear Pending Enable
#define _ICPR3                  *((volatile UINT32 *)0xE000E28C)//IRQ96-127,clear Pending Enable
#define _ICPR4                  *((volatile UINT32 *)0xE000E290)//IRQ128-159,clear Pending Enable
#define _ICPR5                  *((volatile UINT32 *)0xE000E294)//IRQ160-191,clear Pending Enable
#define _ICPR6                  *((volatile UINT32 *)0xE000E298)//IRQ192-223,clear Pending Enable
#define _ICPR7                  *((volatile UINT32 *)0xE000E29C)//IRQ224-239,clear Pending Enable
#define _ICPR(i)                *((volatile UINT32 *)(0xE000E280+i*4))//i=0_7

#define _IABR0                  *((volatile UINT32 *)0xE000E300)//IRQ0-31,active
#define _IABR1                  *((volatile UINT32 *)0xE000E304)//IRQ32-63,active
#define _IABR2                  *((volatile UINT32 *)0xE000E308)//IRQ64-95,active
#define _IABR3                  *((volatile UINT32 *)0xE000E30C)//IRQ96-127,active
#define _IABR4                  *((volatile UINT32 *)0xE000E310)//IRQ128-159,active
#define _IABR5                  *((volatile UINT32 *)0xE000E314)//IRQ160-191,active
#define _IABR6                  *((volatile UINT32 *)0xE000E318)//IRQ192-223,active
#define _IABR7                  *((volatile UINT32 *)0xE000E31C)//IRQ224-239,active
#define _IABR(i)                *((volatile UINT32 *)(0xE000E300+i*4))//i=0_7

#define _IPR(i)                 *((volatile UINT8 *)(0xE000E400+i))//i=0_239
//==============================================================================================================================
#define RSTV_ADC_SR             0x00000000//0x000
struct ADC_SR_BIT
{
	UINT32 AWD:1;         //00,Analog watchdog flag
	UINT32 EOC:1;         //01,End of conversion
	UINT32 JEOC:1;        //02,Injected channel end of conversion
	UINT32 JSTRT:1;       //03,Injected channel Start flag
	UINT32 STRT:1;        //04,Regular channel Start flag
	UINT32 Reserved0:27;  //05,
};
#define ADC_SR_AWD(i)           (*ADC[i]).SR_BIT.AWD
#define ADC_SR_EOC(i)           (*ADC[i]).SR_BIT.EOC
#define ADC_SR_JEOC(i)          (*ADC[i]).SR_BIT.JEOC
#define ADC_SR_JSTRT(i)         (*ADC[i]).SR_BIT.JSTRT
#define ADC_SR_STRT(i)          (*ADC[i]).SR_BIT.STRT
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_CR1            0x00000000//0x004
struct ADC_CR1_BIT
{
	UINT32 AWDCH:5;       //00,AWDCH[4:0] bits (Analog watchdog channel select bits)
	UINT32 EOCIE:1;       //05,Interrupt enable for EOC
	UINT32 AWDIE:1;       //06,Analog Watchdog interrupt enable
	UINT32 JEOCIE:1;      //07,Interrupt enable for injected channels
	UINT32 SCAN:1;        //08,Scan mode
	UINT32 AWDSGL:1;      //09,Enable the watchdog on a single channel in scan mode
	UINT32 JAUTO:1;       //10,Automatic injected group conversion
	UINT32 DISCEN:1;      //11,Discontinuous mode on regular channels
	UINT32 JDISCEN:1;     //12,Discontinuous mode on injected channels
	UINT32 DISCNUM:3;     //13,DISCNUM[2:0] bits (Discontinuous mode channel count)
	UINT32 DUALMOD:4;     //16,DUALMOD[3:0] bits (Dual mode selection)
	UINT32 Reserved0:2;   //20,
	UINT32 JAWDEN:1;      //22,Analog watchdog enable on injected channels
	UINT32 AWDEN:1;       //23,Analog watchdog enable on regular channels
	UINT32 Reserved1:8;   //24,
};
#define ADC_CR1_AWDCH(i)        (*ADC[i]).CR1_BIT.AWDCH
#define ADC_CR1_EOCIE(i)        (*ADC[i]).CR1_BIT.EOCIE
#define ADC_CR1_AWDIE(i)        (*ADC[i]).CR1_BIT.AWDIE
#define ADC_CR1_JEOCIE(i)       (*ADC[i]).CR1_BIT.JEOCIE
#define ADC_CR1_SCAN(i)         (*ADC[i]).CR1_BIT.SCAN
#define ADC_CR1_AWDSGL(i)       (*ADC[i]).CR1_BIT.AWDSGL
#define ADC_CR1_JAUTO(i)        (*ADC[i]).CR1_BIT.JAUTO
#define ADC_CR1_DISCEN(i)       (*ADC[i]).CR1_BIT.DISCEN
#define ADC_CR1_JDISCEN(i)      (*ADC[i]).CR1_BIT.JDISCEN
#define ADC_CR1_DISCNUM(i)      (*ADC[i]).CR1_BIT.DISCNUM
#define ADC_CR1_DUALMOD(i)      (*ADC[i]).CR1_BIT.DUALMOD
#define ADC_CR1_JAWDEN(i)       (*ADC[i]).CR1_BIT.JAWDEN
#define ADC_CR1_AWDEN(i)        (*ADC[i]).CR1_BIT.AWDEN
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_CR2            0x00000000//0x008
struct ADC_CR2_BIT
{
	UINT32 ADON:1;        //00,A/D Converter ON / OFF
	UINT32 CONT:1;        //01,Continuous Conversion
	UINT32 CAL:1;         //02,A/D Calibration
	UINT32 RSTCAL:1;      //03,Reset Calibration
	UINT32 Reserved0:4;   //04,
	UINT32 DMA:1;         //08,Direct Memory access mode
	UINT32 Reserved1:2;   //09,
	UINT32 ALIGN:1;       //11,Data Alignment
	UINT32 JEXTSEL:3;     //12,JEXTSEL[2:0] bits (External event select for injected group)
	UINT32 JEXTTRIG:1;    //15,External Trigger Conversion mode for injected channels
	UINT32 Reserved2:1;   //16,
	UINT32 EXTSEL:3;      //17,EXTSEL[2:0] bits (External Event Select for regular group)
	UINT32 EXTTRIG:1;     //20,External Trigger Conversion mode for regular channels
	UINT32 JSWSTART:1;    //21,Start Conversion of injected channels
	UINT32 SWSTART:1;     //22,Start Conversion of regular channels
	UINT32 TSVREFE:1;     //23,Temperature Sensor and VREFINT Enable
	UINT32 Reserved3:8;   //24,
};
#define ADC_CR2_ADON(i)         (*ADC[i]).CR2_BIT.ADON
#define ADC_CR2_CONT(i)         (*ADC[i]).CR2_BIT.CONT
#define ADC_CR2_CAL(i)          (*ADC[i]).CR2_BIT.CAL
#define ADC_CR2_RSTCAL(i)       (*ADC[i]).CR2_BIT.RSTCAL
#define ADC_CR2_DMA(i)          (*ADC[i]).CR2_BIT.DMA
#define ADC_CR2_ALIGN(i)        (*ADC[i]).CR2_BIT.ALIGN
#define ADC_CR2_JEXTSEL(i)      (*ADC[i]).CR2_BIT.JEXTSEL
#define ADC_CR2_JEXTTRIG(i)     (*ADC[i]).CR2_BIT.JEXTTRIG
#define ADC_CR2_EXTSEL(i)       (*ADC[i]).CR2_BIT.EXTSEL
#define ADC_CR2_EXTTRIG(i)      (*ADC[i]).CR2_BIT.EXTTRIG
#define ADC_CR2_JSWSTART(i)     (*ADC[i]).CR2_BIT.JSWSTART
#define ADC_CR2_SWSTART(i)      (*ADC[i]).CR2_BIT.SWSTART
#define ADC_CR2_TSVREFE(i)      (*ADC[i]).CR2_BIT.TSVREFE
//------------------------------------------------------------------------------------------------------------------------------
//SMP Cycles: 0=1.5,1=7.5,2=13.5,3=28.5,4=41.5,5=55.5,6=71.5,7=239.5
#define RSTV_ADC_SMPR1          0x00000000//0x00C
#define RSTV_ADC_SMPR2          0x00000000//0x010
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_JOFR1          0x00000000//0x014
#define RSTV_ADC_JOFR2          0x00000000//0x018
#define RSTV_ADC_JOFR3          0x00000000//0x01C
#define RSTV_ADC_JOFR4          0x00000000//0x020
#define RSTV_ADC_JOFR           0x00000000
struct ADC_JOFR_BIT//0x014=JOFR1,0x018=JOFR2,0x01C=JOFR3,0x020=JOFR4
{
	UINT32 JOFFSET:12;    //00,Data offset for injected channel 1_4
	UINT32 Reserved0:20;  //12,
};
#define ADC_JOFR_JOFFSET(i,j)   (*ADC[i]).JOFR[j]_BIT.JOFFSET//i=0_2,j=0_3
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_HTR            0x00000000//0x024，Analog watchdog high threshold
#define RSTV_ADC_LTR            0x00000000//0x028，Analog watchdog low threshold
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_SQR1           0x00000000//0x02C,bit20_23=L=Regular channel sequence length
#define RSTV_ADC_SQR2           0x00000000//0x030
#define RSTV_ADC_SQR3           0x00000000//0x034
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_JSQR           0x00000000//0x038
struct ADC_JSQR_BIT
{
	UINT32 JSQ1:5;        //00,JSQ1[4:0] bits (1st conversion in injected sequence)
	UINT32 JSQ2:5;        //05,JSQ2[4:0] bits (2nd conversion in injected sequence)
	UINT32 JSQ3:5;        //10,JSQ3[4:0] bits (3rd conversion in injected sequence)
	UINT32 JSQ4:5;        //15,JSQ4[4:0] bits (4th conversion in injected sequence)
	UINT32 JL:2;          //20,JL[1:0] bits (Injected Sequence length)
	UINT32 Reserved0:10;  //22,
};
#define ADC_JSQR_JSQ1(i)        (*ADC[i]).JSQR_BIT.JSQ1
#define ADC_JSQR_JSQ2(i)        (*ADC[i]).JSQR_BIT.JSQ2
#define ADC_JSQR_JSQ3(i)        (*ADC[i]).JSQR_BIT.JSQ3
#define ADC_JSQR_JSQ4(i)        (*ADC[i]).JSQR_BIT.JSQ4
#define ADC_JSQR_JL(i)          (*ADC[i]).JSQR_BIT.JL
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_JDR1           0x00000000//0x03C
#define RSTV_ADC_JDR2           0x00000000//0x040
#define RSTV_ADC_JDR3           0x00000000//0x044
#define RSTV_ADC_JDR4           0x00000000//0x048
#define RSTV_ADC_JDR            0x00000000
struct ADC_JDR_BIT//JDR1,JDR2,JDR3,JDR4
{
	UINT32 JDATA:16;      //00,Injected data
	UINT32 Reserved0:16;  //16,
};
#define ADC_JDR_JDATA(i,j)      (*ADC[i]).JDR[j]_BIT.JDATA//i=0_2,j=0_3
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ADC_DR               0x00000000//0x04C
struct ADC_DR_BIT
{
	UINT32 DATA:16;       //00,Regular data
	UINT32 ADC2DATA:16;   //16,ADC2 data
};
#define ADC_DR_DATA(i)          (*ADC[i]).DR_BIT.DATA
#define ADC_DR_ADC2DATA(i)      (*ADC[i]).DR_BIT.ADC2DATA
//------------------------------------------------------------------------------------------------------------------------------
#define ADC_Struct Struct_ADC
typedef struct Struct_ADC//ADC1=0x40012400,ADC2=0x40012800,ADC3=0x40013C00 
{
  union{UINT32 SR;struct ADC_SR_BIT SR_BIT;};            //0x000(RW),ADC status register
  union{UINT32 CR1;struct ADC_CR1_BIT CR1_BIT;};         //0x004(RW),ADC control register 1
  union{UINT32 CR2;struct ADC_CR2_BIT CR2_BIT;};         //0x008(RW),ADC control register 2
  union{UINT32 SMPR[2];struct UINT32_B3P_BIT SMPR_BIT[2];};//0x00C(RW),ADC sample time register
  union{UINT32 JOFR[4];struct ADC_JOFR_BIT JOFR_BIT[4];};//0x014(RW),ADC injected channel data offset register 1_4
  union{UINT32 HTR;Type_UINT32_BIT12 HTR_BIT;};          //0x024(RW),ADC watchdog higher threshold register
  union{UINT32 LTR;Type_UINT32_BIT12 LTR_BIT;};          //0x028(RW),watchdog lower threshold register
  union{UINT32 SQR[3];struct UINT32_B5P_BIT SQR_BIT[3];};//0x02C(RW),regular sequence register 1_3
  union{UINT32 JSQR;struct ADC_JSQR_BIT JSQR_BIT;};      //0x038(RW),injected sequence register
  union{UINT32 JDR[4];struct ADC_JDR_BIT JDR_BIT[4];};   //0x03C(RW),injected data register 1_4
  union{UINT32 DR;struct ADC_DR_BIT DR_BIT;};            //0x04C(RW),ADC regular data register
} ADC_Type,Type_ADC;
#define PT_ADC1                 ((volatile Type_ADC *)BASE_ADC1)
#define PT_ADC2                 ((volatile Type_ADC *)BASE_ADC2)
#define PT_ADC3                 ((volatile Type_ADC *)BASE_ADC3)
#define PT_ADC(i)               ((volatile Type_ADC *)BASE_ADC[i])
//------------------------------------------------------------------------------------------------------------------------------
#define ADC_SR(i)               (*ADC[i]).SR//i=0_2
#define ADC_CR1(i)              (*ADC[i]).CR1//i=0_2
#define ADC_CR2(i)              (*ADC[i]).CR2//i=0_2
#define ADC_SMPR(i,j)           (*ADC[i]).SMPR[j]//i=0_2,j=0_1
#define ADC_JOFR(i,j)           (*ADC[i]).JOFR[j]//i=0_2,j=0_3
#define ADC_HTR(i)              (*ADC[i]).HTR//i=0_2
#define ADC_LTR(i)              (*ADC[i]).LTR//i=0_2
#define ADC_SQR(i,j)            (*ADC[i]).SQR[j]//i=0_2,j=0_2
#define ADC_JSQR(i)             (*ADC[i]).JSQR//i=0_2
#define ADC_JDR(i,j)            (*ADC[i]).JDR[j]//i=0_2,j=0_3
#define ADC_DR(i)               (*ADC[i]).DR//i=0_2
//==============================================================================================================================

#define RSTV_BKP_DRA            0x00000000//0x04
#define RSTV_BKP_DRB            0x00000000//0x40
#define RSTV_BKP_DR             0x00000000
struct BKP_DR_BIT//0x04=DRA,0x40=DRB
{
  UINT32 D:16;          //00,
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_BKP_RTCCR          0x00000000//0x2C
struct BKP_RTCCR_BIT
{
  UINT32 CAL:7;         //00,Calibration value
  UINT32 CCO:1;         //07,Calibration Clock Output
  UINT32 ASOE:1;        //08,Alarm or Second Output Enable
  UINT32 ASOS:1;        //09,Alarm or Second Output Selection
  UINT32 Reserved0:22;  //10,
};
#define BKP_RTCCR_CAL           BKP.RTCCR_BIT.CAL
#define BKP_RTCCR_CCO           BKP.RTCCR_BIT.CCO
#define BKP_RTCCR_ASOE          BKP.RTCCR_BIT.ASOE
#define BKP_RTCCR_ASOS          BKP.RTCCR_BIT.ASOS
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_BKP_CR             0x00000000//0x30
struct BKP_CR_BIT
{
  UINT32 TPE:1;         //0x00,TAMPER pin enable
  UINT32 TPAL:1;        //0x01,TAMPER pin active level
  UINT32 Reserved0:30;
};
#define BKP_CR_TPE              BKP.CR_BIT.TPE
#define BKP_CR_TPAL             BKP.CR_BIT.TPAL
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_BKP_CSR            0x00000000//0x34
struct BKP_CSR_BIT
{
  UINT32 CTE:1;         //Clear Tamper event
  UINT32 CTI:1;         //Clear Tamper Interrupt
  UINT32 TPIE:1;        //TAMPER Pin interrupt enable
  UINT32 Reserved0:5;
  UINT32 TEF:1;         //Tamper Event Flag
  UINT32 TIF:1;         //Tamper Interrupt Flag
};
#define BKP_CSR_CTE             BKP.CSR_BIT.CTE
#define BKP_CSR_CTI             BKP.CSR_BIT.CTI
#define BKP_CSR_TPIE            BKP.CSR_BIT.TPIE
#define BKP_CSR_TEF             BKP.CSR_BIT.TEF
#define BKP_CSR_TIF             BKP.CSR_BIT.TIF
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BKP_Struct Struct_BKP
typedef struct Struct_BKP
{
  UINT32 RESERVED0[1];  //0x00(R),
  union{UINT32 DRA[10];struct BKP_DR_BIT DRA_BIT[10];}; //0x04(RW),
  union{UINT32 RTCCR;struct BKP_RTCCR_BIT RTCCR_BIT;};  //0x2C(RW),
  union{UINT32 CR;struct BKP_CR_BIT CR_BIT;};           //0x30(RW),
  union{UINT32 CSR;struct BKP_CSR_BIT CSR_BIT;};        //0x34(RW),
	UINT32 RESERVED1[2];  //0x38(R),
  union{UINT32 DRB[32];struct BKP_DR_BIT DRB_BIT[32];}; //0x40(RW),
} BKP_Type,Type_BKP;
#define PT_BKP                  ((volatile Type_BKP *)BASE_BKP)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BKP_DRA(i)              BKP.DRA[i]//i=0_9
#define BKP_RTCCR               BKP.RTCCR
#define BKP_CR                  BKP.CR
#define BKP_CSR                 BKP.CSR
#define BKP_DRB(i)              BKP.DRB[i]//i=0_31
//==============================================================================================================================
#define RSTV_CAN_MCR            0x00010002//0x000
struct CAN_MCR_BIT
{
	UINT32 INRQ:1;        //00,Initialization Request
	UINT32 SLEEP:1;       //01,Sleep Mode Request
	UINT32 TXFP:1;        //02,Transmit FIFO Priority
	UINT32 RFLM:1;        //03,Receive FIFO Locked Mode
	UINT32 NART:1;        //04,No Automatic Retransmission
	UINT32 AWUM:1;        //05,Automatic Wakeup Mode
	UINT32 ABOM:1;        //06,Automatic Bus-Off Management
	UINT32 TTCM:1;        //07,Time Triggered Communication Mode
	UINT32 Reserved0:7;   //08,
	UINT32 RESET:1;       //15,CAN software master reset
	UINT32 DBF:1;         //16,Debug freeze
	UINT32 Reserved1:15;  //17,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_MSR            0x00000C02//0x004
struct CAN_MSR_BIT
{
	UINT32 INAK:1;        //00,Initialization Acknowledge
	UINT32 SLAK:1;        //01,Sleep Acknowledge
	UINT32 ERRI:1;        //02,Error Interrupt
	UINT32 WKUI:1;        //03,Wakeup Interrupt
	UINT32 SLAKI:1;       //04,Sleep Acknowledge Interrupt
	UINT32 Reserved0:3;   //05,
	UINT32 TXM:1;         //08,Transmit Mode
	UINT32 RXM:1;         //09,Receive Mode
	UINT32 SAMP:1;        //10,Last Sample Point
	UINT32 RX:1;          //11,CAN Rx Signal
	UINT32 Reserved1:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_TSR            0x1C000000//0x008
struct CAN_TSR_BIT
{
	UINT32 RQCP0:1;       //00,Request Completed Mailbox0
	UINT32 TXOK0:1;       //01,Transmission OK of Mailbox0
	UINT32 ALST0:1;       //02,Arbitration Lost for Mailbox0
	UINT32 TERR0:1;       //03,Transmission Error of Mailbox0
	UINT32 Reserved0:3;   //04,
	UINT32 ABRQ0:1;       //07,Abort Request for Mailbox0
	UINT32 RQCP1:1;       //08,Request Completed Mailbox1
	UINT32 TXOK1:1;       //09,Transmission OK of Mailbox1
	UINT32 ALST1:1;       //10,Arbitration Lost for Mailbox1
	UINT32 TERR1:1;       //11,Transmission Error of Mailbox1
	UINT32 Reserved1:3;   //12,
	UINT32 ABRQ1:1;       //15,Abort Request for Mailbox1
	UINT32 RQCP2:1;       //16,Request Completed Mailbox2
	UINT32 TXOK2:1;       //17,Transmission OK of Mailbox2
	UINT32 ALST2:1;       //18,Arbitration Lost for Mailbox2
	UINT32 TERR2:1;       //19,Transmission Error of Mailbox2
	UINT32 Reserved2:3;   //20,
	UINT32 ABRQ2:1;       //23,Abort Request for Mailbox2
  UINT32 CODE:2;        //24,Mailbox Code
	UINT32 TME:3;         //26,TME[2:0] bits=Transmit Mailbox 0_2 Empty
	UINT32 LOW:3;         //29,LOW[2:0] bits=Lowest Priority Flag for Mailbox 0_2
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_RF0R           0x00000000//0x00C
#define RSTV_CAN_RF1R           0x00000000//0x010
struct CAN_RFR_BIT//0x00C=RF0R,0x010=RF1R
{
	UINT32 FMP:2;         //00,FIFO 0/1 Message Pending
	UINT32 Reserved0:1;   //02,
	UINT32 FULL:1;        //03,FIFO 0/1 Full
	UINT32 FOVR:1;        //04,FIFO 0/1 Overrun
	UINT32 RFOM:1;        //05,Release FIFO 0/1 Output Mailbox
	UINT32 Reserved1:26;  //06,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_IER            0x00000000//0x014
struct CAN_IER_BIT
{
	UINT32 TMEIE:1;       //00,Transmit Mailbox Empty Interrupt Enable
	UINT32 FMPIE0:1;      //01,FIFO Message Pending Interrupt Enable
	UINT32 FFIE0:1;       //02,FIFO Full Interrupt Enable
	UINT32 FOVIE0:1;      //03,FIFO Overrun Interrupt Enable
	UINT32 FMPIE1:1;      //04,FIFO Message Pending Interrupt Enable
	UINT32 FFIE1:1;       //05,FIFO Full Interrupt Enable
	UINT32 FOVIE1:1;      //06,FIFO Overrun Interrupt Enable
	UINT32 Reserved0:1;   //07,
	UINT32 EWGIE:1;       //08,Error Warning Interrupt Enable
	UINT32 EPVIE:1;       //09,Error Passive Interrupt Enable
	UINT32 BOFIE:1;       //10,Bus-Off Interrupt Enable
	UINT32 LECIE:1;       //11,Last Error Code Interrupt Enable
	UINT32 Reserved1:3;   //12,
	UINT32 ERRIE:1;       //15,Error Interrupt Enable
	UINT32 WKUIE:1;       //16,Wakeup Interrupt Enable
	UINT32 SLKIE:1;       //17,Sleep Interrupt Enable
	UINT32 Reserved2:14;  //18,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_ESR            0x00000000//0x018
struct CAN_ESR_BIT
{
	UINT32 EWGF:1;        //00,Error Warning Flag
	UINT32 EPVF:1;        //01,Error Passive Flag
	UINT32 BOFF:1;        //02,Bus-Off Flag
	UINT32 Reserved0:1;   //03,
	UINT32 LEC:3;         //04,LEC[2:0] bits (Last Error Code)
	UINT32 Reserved1:9;   //07,
	UINT32 TEC:8;         //16,Least significant byte of the 9-bit Transmit Error Counter
	UINT32 REC:8;         //24,Receive Error Counter
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_BTR            0x01230000//0x01C
struct CAN_BTR_BIT
{
	UINT32 BRP:10;        //00,Baud Rate Prescaler
	UINT32 Reserved0:6;   //10,
	UINT32 TS1:4;         //16,Time Segment 1
	UINT32 TS2:3;         //20,Time Segment 2
	UINT32 Reserved1:1;   //23,
	UINT32 SJW:2;         //24,Resynchronization Jump Width
	UINT32 Reserved2:4;   //26,
	UINT32 LBKM:1;        //30,Loop Back Mode (Debug):1=enable
	UINT32 SILM:1;        //31,Silent Mode:0=normal,1=silent mode
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_TI0R           0x00000000//0x180
#define RSTV_CAN_TI1R           0x00000000//0x190 
#define RSTV_CAN_TI2R           0x00000000//0x1A0
#define RSTV_CAN_TIR            0x00000000
struct CAN_TIR_BIT//0x180=TI0R,0x190=TI1R,0x1A0=TI2R
{
	UINT32 TXRQ:1;        //00,Transmit Mailbox Request
	UINT32 RTR:1;         //01,Remote Transmission Request
	UINT32 IDE:1;         //02,Identifier Extension
	UINT32 EXID:18;       //03,Extended Identifier
	UINT32 STID:11;       //21,Standard Identifier or Extended Identifier
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_TDT0R          0x00000000//0x184
#define RSTV_CAN_TDT1R          0x00000000//0x194 
#define RSTV_CAN_TDT2R          0x00000000//0x1A4
#define RSTV_CAN_TDTR           0x00000000
struct CAN_TDTR_BIT//0x184=TDT0R,0x194=TDT1R,0x1A4=TDT2R
{
	UINT32 DLC:4;         //00,Data Length Code
	UINT32 Reserved0:4;   //04,
	UINT32 TGT:1;         //08,Transmit Global Time
	UINT32 Reserved1:7;   //09,
	UINT32 TIME:16;       //16,Message Time Stamp
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_TDL0R          0x00000000//0x188
#define RSTV_CAN_TDL1R          0x00000000//0x198 
#define RSTV_CAN_TDL2R          0x00000000//0x1A8
#define RSTV_CAN_RDL0R          0x00000000//0x1B8
#define RSTV_CAN_RDL1R          0x00000000//0x1C8
#define RSTV_CAN_DLR            0x00000000
struct CAN_DLR_BIT//0x188=TDL0R,0x198=TDL1R,0x1A8=TDL2R,0x1B8=RDL0R,0x1C8=RDL1R
{
	UINT32 DATA0:8;       //00,Data byte 0
	UINT32 DATA1:8;       //08,Data byte 1
	UINT32 DATA2:8;       //16,Data byte 2
	UINT32 DATA3:8;       //24,Data byte 3
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_TDH0R          0x00000000//0x18C
#define RSTV_CAN_TDH1R          0x00000000//0x19C 
#define RSTV_CAN_TDH2R          0x00000000//0x1AC
#define RSTV_CAN_RDH0R          0x00000000//0x1BC
#define RSTV_CAN_RDH1R          0x00000000//0x1CC
#define RSTV_CAN_DHR            0x00000000
struct CAN_DHR_BIT//0x18C=TDH0R,0x19C=TDH1R,0x1AC=TDH2R,0x1BC=RDH0R,0x1CC=RDH1R
{
	UINT32 DATA4:8;       //00,Data byte 0
	UINT32 DATA5:8;       //08,Data byte 1
	UINT32 DATA6:8;       //16,Data byte 2
	UINT32 DATA7:8;       //24,Data byte 3
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_RI0R           0x00000000//0x1B0
#define RSTV_CAN_RI1R           0x00000000//0x1C0 
#define RSTV_CAN_RIR            0x00000000
struct CAN_RIR_BIT//0x1B0=RI0R,0x1C0=RI1R
{
	UINT32 Reserved0:1;   //00,
	UINT32 RTR:1;         //01,Remote Transmission Request
	UINT32 IDE:1;         //02,Identifier Extension
	UINT32 EXID:18;       //03,Extended Identifier
	UINT32 STID:11;       //21,Standard Identifier or Extended Identifier
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_RDT0R          0x00000000//0x1B4
#define RSTV_CAN_RDT1R          0x00000000//0x1C4 
#define RSTV_CAN_RDTR           0x00000000
struct CAN_RDTR_BIT//0x1B4=RDT0R,0x1C4=RDT1R
{
	UINT32 DLC:4;         //00,Data Length Code
	UINT32 Reserved0:4;   //04,
	UINT32 FMI:8;         //08,Filter Match Index
	UINT32 TIME:16;       //16,Message Time Stamp
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_FMR            0x00000000//0x200
struct CAN_FMR_BIT
{
	UINT32 FINIT:1;       //00,Filter Init Mode
	UINT32 Reserved0:7;   //01,
	UINT32 CAN2SB:6;      //08,<LDY>
	UINT32 Reserved1:18;  //14,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_FM1R           0x00000000//0x204
struct CAN_FM1R_BIT
{
	UINT32 FBM:28;        //00,Filter Mode,or=14bits(IsDensity(CL)):0=mask mode,1=list mode
	UINT32 Reserved0:4;   //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_FS1R           0x00000000//0x20C
struct CAN_FS1R_BIT
{
	UINT32 FSC:28;        //00,Filter Scale Configuration,or=14bits(IsDensity(CL)):0=dual 16 bits,1=single 32 bits
	UINT32 Reserved0:4;   //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_FFA1R          0x00000000//0x214
struct CAN_FFA1R_BIT
{
	UINT32 FFA:28;        //00,Filter FIFO Assignment,or=14bits(IsDensity(CL)):0=fifo 0,1=fifo 1
	UINT32 Reserved0:4;   //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_FA1R           0x00000000//0x21C
struct CAN_FA1R_BIT
{
	UINT32 FACT:28;       //00,Filter Active,or=14bits(IsDensity(CL)):0=not active,1=active
	UINT32 Reserved0:4;   //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CAN_FR             0x00000000
//------------------------------------------------------------------------------------------------------------------------------
typedef union CAN_BUF
{
  UINT8  Item[8];
  struct CAN_BUFHL
  {
    union{UINT32 DLR;struct CAN_DLR_BIT DLR_BIT;UINT8 DLR_Byte[4];};
    union{UINT32 DHR;struct CAN_DHR_BIT DHR_BIT;UINT8 DHR_Byte[4];};
  }LH;
} CAN_BUF_Type,Type_CAN_BUF;
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Struct_CAN_TxMailBox
{
  union{UINT32 TIR;struct CAN_TIR_BIT TIR_BIT;};
  union{UINT32 TDTR;struct CAN_TDTR_BIT TDTR_BIT;UINT8 TDTR_Byte[4];};
  Type_CAN_BUF TBUF;
} CAN_TxMailBox_Type,Type_CAN_TxMailBox;
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Struct_CAN_RxMailBox
{
  union{UINT32 RIR;struct CAN_RIR_BIT RIR_BIT;};
  union{UINT32 RDTR;struct CAN_RDTR_BIT RDTR_BIT;UINT8 RDTR_Byte[4];};
  Type_CAN_BUF RBUF;
} CAN_RxMailBox_Type,Type_CAN_RxMailBox;
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Struct_CAN_FilterR
{
  union{UINT32 FR1;Type_BIT32 FR1_BIT;};
  union{UINT32 FR2;Type_BIT32 FR2_BIT;};
} CAN_FilterR_Type,Type_CAN_FilterR;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CAN_Struct Struct_CAN
typedef struct Struct_CAN//CAN1=0x40006400,CAN2=0x40006800
{
  union{UINT32 MCR;struct CAN_MCR_BIT MCR_BIT;};      //CAN1=0x40006400
  union{UINT32 MSR;struct CAN_MSR_BIT MSR_BIT;};      //CAN1=0x40006404
  union{UINT32 TSR;struct CAN_TSR_BIT TSR_BIT;};      //CAN1=0x40006408
  union{UINT32 RFR[2];struct CAN_RFR_BIT RFR_BIT[2];};//CAN1=0x4000640C
  union{UINT32 IER;struct CAN_IER_BIT IER_BIT;};      //CAN1=0x40006414
  union{UINT32 ESR;struct CAN_ESR_BIT ESR_BIT;};      //CAN1=0x40006418
  union{UINT32 BTR;struct CAN_BTR_BIT BTR_BIT;};      //CAN1=0x4000641C
  UINT32 Reserved0[88]; //CAN1=0x40006420
  Type_CAN_TxMailBox TXM[3];//CAN1=0x40006580,sTxMailBox
  Type_CAN_RxMailBox RXM[2];//CAN1=0x400065B0,sRxMailBox
  UINT32 Reserved1[12]; //CAN1=0x400065D0
  union{UINT32 FMR;struct CAN_FMR_BIT FMR_BIT;};      //CAN1=0x40006600
  union{UINT32 FM1R;struct CAN_FM1R_BIT FM1R_BIT;};   //CAN1=0x40006604
  UINT32 Reserved2[1];  //CAN1=0x40006608
  union{UINT32 FS1R;struct CAN_FS1R_BIT FS1R_BIT;};   //CAN1=0x4000660C
  UINT32 Reserved3[1];  //CAN1=0x40006610
  union{UINT32 FFA1R;struct CAN_FFA1R_BIT FFA1R_BIT;};//CAN1=0x40006614
  UINT32 Reserved4[1];  //CAN1=0x40006618
  union{UINT32 FA1R;struct CAN_FA1R_BIT FA1R_BIT;};   //CAN1=0x4000661C
  UINT32 Reserved5[8];  //CAN1=0x40006620
#if !IsDensity(CL)
  Type_CAN_FilterR SFR[14];//CAN1=0x40006640,sFilterRegister
	UINT32 Reserved6[84];  //CAN1=0x400066B0
#else
  Type_CAN_FilterR SFR[28];//CAN1=0x40006640,sFilterRegister
	UINT32 Reserved6[56];  //CAN1=0x40006720
#endif

} CAN_Type,Type_CAN;
#define PT_CAN1                 ((volatile Type_CAN *)BASE_CAN1)
#define PT_CAN2                 ((volatile Type_CAN *)BASE_CAN2)
#define PT_CAN(i)               ((volatile Type_CAN *)BASE_CAN(i))
#define CAN1                    CAN[0]
#define CAN2                    CAN[1]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CAN_MCR(i)              CAN[i].MCR//i=0_1,
#define CAN_MSR(i)              CAN[i].MSR//i=0_1,
#define CAN_TSR(i)              CAN[i].TSR//i=0_1,
#define CAN_RFR(i,j)            CAN[i].RFR[j]//i=0_1,j=0_1
#define CAN_IER(i)              CAN[i].IER//i=0_1,
#define CAN_ESR(i)              CAN[i].ESR//i=0_1,
#define CAN_BTR(i)              CAN[i].BTR//i=0_1,
#define CAN_TIR(i,j)            CAN[i].TXM[j].TIR//i=0_1,j=0_2
#define CAN_TDTR(i,j)           CAN[i].TXM[j].TDTR//i=0_1,j=0_2
#define CAN_TDLR(i,j)           CAN[i].TXM[j].TDLR//i=0_1,j=0_2
#define CAN_TDHR(i,j)           CAN[i].TXM[j].TDHR//i=0_1,j=0_2
#define CAN_RIR(i,j)            CAN[i].RXM[j].RIR//i=0_1,j=0_1
#define CAN_RDTR(i,j)           CAN[i].RXM[j].RDTR//i=0_1,j=0_1
#define CAN_RDLR(i,j)           CAN[i].RXM[j].RDLR//i=0_1,j=0_1
#define CAN_RDHR(i,j)           CAN[i].RXM[j].RDHR//i=0_1,j=0_1
#define CAN_FMR(i)              CAN[i].FMR//i=0_1,
#define CAN_FM1R(i)             CAN[i].FM1R//i=0_1,
#define CAN_FS1R(i)             CAN[i].FS1R//i=0_1,
#define CAN_FFA1R(i)            CAN[i].FFA1R//i=0_1,
#define CAN_FA1R(i)             CAN[i].FA1R//i=0_1,
#define CAN_FR1(i,j)            CAN[i].SFR[j].FR1//i=0_1,j=0_13 or j=0_27(IsDensity(CL))
#define CAN_FR2(i,j)            CAN[i].SFR[j].FR2//i=0_1,j=0_13 or j=0_27(IsDensity(CL))
//==============================================================================================================================
#define RSTV_CEC_CFGR           0x00000000//0x000
struct CEC_CFGR_BIT
{
	UINT32 PE:1;          //00,Peripheral Enable
	UINT32 IE:1;          //01,Interrupt Enable
	UINT32 BTEM:1;        //02,Bit Timing Error Mode
	UINT32 BPEM:1;        //03,Bit Period Error Mode
	UINT32 Reserved0:28;  //04,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CEC_OAR            0x00000000//0x004
struct CEC_OAR_BIT
{
	UINT32 OA:4;          //00,OA[3:0]: Own Address
	UINT32 Reserved0:28;  //04,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CEC_PRES           0x00000000//0x008
struct CEC_PRES_BIT
{
	UINT32 PRES:14;       //00,Prescaler Counter Value
	UINT32 Reserved0:18;  //14,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CEC_ESR            0x00000000//0x00C
struct CEC_ESR_BIT
{
	UINT32 BTE:1;         //00,Bit Timing Error
	UINT32 BPE:1;         //01,Bit Period Error
	UINT32 RBTFE:1;       //02,Rx Block Transfer Finished Error
	UINT32 SBE:1;         //03,Start Bit Error
	UINT32 ACKE:1;        //04,Block Acknowledge Error
	UINT32 LINE:1;        //05,Line Error
	UINT32 TBTFE:1;       //06,Tx Block Transfer Finished Error
	UINT32 Reserved0:25;  //07,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CEC_CSR            0x00000000//0x010
struct CEC_CSR_BIT
{
	UINT32 TSOM:1;        //00,Tx Start Of Message
	UINT32 TEOM:1;        //01,Tx End Of Message
	UINT32 TERR:1;        //02,Tx Error
	UINT32 TBTRF:1;       //03,Tx Byte Transfer Request or Block Transfer Finished
	UINT32 RSOM:1;        //04,Rx Start Of Message
	UINT32 REOM:1;        //05,Rx End Of Message
	UINT32 RERR:1;        //06,Rx Error
	UINT32 RBTF:1;        //07,Rx Block Transfer Finished
	UINT32 Reserved0:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CEC_TXD            0x00000000//0x014
#define RSTV_CEC_RXD            0x00000000//0x018
struct CEC_XD_BIT//0x014=TXD,0x18=RXD
{
	UINT32 XD:8;          //00,Tx/Rx Data register
	UINT32 Reserved0:24;  //08,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CEC_Struct Struct_CEC
typedef struct Struct_CEC
{
  union{UINT32 CFGR;struct CEC_CFGR_BIT CFGR_BIT;};
  union{UINT32 OAR;struct CEC_OAR_BIT OAR_BIT;};
  union{UINT32 PRES;struct CEC_PRES_BIT PRES_BIT;};
  union{UINT32 ESR;struct CEC_ESR_BIT ESR_BIT;};
  union{UINT32 CSR;struct CEC_CSR_BIT CSR_BIT;};
  union{UINT32 TXD;struct CEC_XD_BIT TXD_BIT;};
  union{UINT32 RXD;struct CEC_XD_BIT RXD_BIT;};  
} CEC_Type,Type_CEC;
#define PT_CEC                  ((volatile Type_CEC *)BASE_CEC)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CEC_CFGR                CEC.CFGR
#define CEC_OAR                 CEC.OAR
#define CEC_PRES                CEC.PRES
#define CEC_ESR                 CEC.ESR
#define CEC_CSR                 CEC.CSR
#define CEC_TXD                 CEC.TXD
#define CEC_RXD                 CEC.RXD
//==============================================================================================================================
#define RSTV_CRC_DR             0xFFFFFFFF//0x000
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CRC_IDR            0x00000000//0x004
struct CRC_IDR_BIT
{
  UINT32 IDR:8;         //00,
  UINT32 Reserved0:24;  //08,
};
#define CRC_IDR_IDR             CRC.IDR_BIT.IDR
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_CRC_CR             0x00000000//0x008
struct CRC_CR_BIT
{
  UINT32 RESET:1;       //00,Resets the CRC calculation unit
  UINT32 Reserved0:31;
};
#define CRC_CR_RESET            CRC.CR_BIT.RESET
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CRC_Struct Struct_CRC
typedef struct Struct_CRC
{
  union{UINT32 DR;};
  union{UINT32 IDR;struct CRC_IDR_BIT IDR_BIT;};
  union{UINT32 CR;struct CRC_CR_BIT CR_BIT;};
} CRC_Type,Type_CRC;
#define PT_CRC    ((volatile Type_CRC *)BASE_CRC)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CRC_DR     CRC.DR
#define CRC_IDR    CRC.IDR
#define CRC_CR     CRC.CR
//==============================================================================================================================
#define RSTV_DAC_CR             0x00000000//0x000
struct DAC_CR_BIT
{
	UINT32 EN1:1;         //00,DAC channel1 enable
	UINT32 BOFF1:1;       //01,DAC channel1 output buffer disable
	UINT32 TEN1:1;        //02,DAC channel1 Trigger enable
	UINT32 TSEL1:3;       //03,TSEL1[2:0] (DAC channel1 Trigger selection)
	UINT32 WAVE1:2;       //06,WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable)
	UINT32 MAMP1:4;       //08,MAMP1[3:0] (DAC channel1 Mask/Amplitude selector)
	UINT32 DMAEN1:1;      //12,DAC channel1 DMA enable
	UINT32 Reserved0:3;   //13,
	UINT32 EN2:1;         //16,DAC channel2 enable
	UINT32 BOFF2:1;       //17,DAC channel2 output buffer disable
	UINT32 TEN2:1;        //18,DAC channel2 Trigger enable
	UINT32 TSEL2:3;       //19,TSEL2[2:0] (DAC channel2 Trigger selection)
	UINT32 WAVE2:2;       //22,WAVE2[1:0] (DAC channel2 noise/triangle wave generation enable)
	UINT32 MAMP2:4;       //24,MAMP2[3:0] (DAC channel2 Mask/Amplitude selector)
	UINT32 DMAEN2:1;      //28,DAC channel2 DMA enabled
	UINT32 Reserved1:3;   //29,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_SWTRIGR        0x00000000//0x004
struct DAC_SWTRIGR_BIT
{
	UINT32 SWTRIG1:1;     //00,DAC channel1 software trigger
	UINT32 SWTRIG2:1;     //01,DAC channel2 software trigger
	UINT32 Reserved0:30;  //02,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR12R1        0x00000000//0x008
struct DAC_DHR12R1_BIT
{
	UINT32 DACC1DHR:12;   //00,DAC channel1 12-bit Right aligned data
	UINT32 Reserved0:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR12L1        0x00000000//0x00C
struct DAC_DHR12L1_BIT
{
	UINT32 Reserved0:4;   //00,
	UINT32 DACC1DHR:12;   //04,DAC channel1 12-bit Right aligned data
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR8R1         0x00000000//0x010
struct DAC_DHR8R1_BIT
{
	UINT32 DACC1DHR:8;    //00,DAC channel1 8-bit Right aligned data
	UINT32 Reserved0:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR12R2        0x00000000//0x014
struct DAC_DHR12R2_BIT
{
	UINT32 DACC2DHR:12;   //00,DAC channel2 12-bit Right aligned data
	UINT32 Reserved0:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR12L2        0x00000000//0x018
struct DAC_DHR12L2_BIT
{
	UINT32 Reserved0:4;   //00,
	UINT32 DACC2DHR:12;   //04,DAC channel2 12-bit Left aligned data
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR8R2         0x00000000//0x01C
struct DAC_DHR8R2_BIT
{
	UINT32 DACC2DHR:8;    //00,DAC channel2 8-bit Right aligned data
	UINT32 Reserved1:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR12RD        0x00000000//0x020
struct DAC_DHR12RD_BIT
{
	UINT32 DACC1DHR:12;   //00,DAC channel1 12-bit Right aligned data
	UINT32 Reserved0:4;   //16,
	UINT32 DACC2DHR:12;   //16,DAC channel2 12-bit Right aligned data
	UINT32 Reserved1:4;   //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR12LD        0x00000000//0x024
struct DAC_DHR12LD_BIT
{
	UINT32 Reserved0:4;   //00,
	UINT32 DACC1DHR:12;   //04,DAC channel1 12-bit Left aligned data
	UINT32 Reserved1:4;   //16,
	UINT32 DACC2DHR:12;   //20,DAC channel2 12-bit Left aligned data
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DHR8RD         0x00000000//0x028
struct DAC_DHR8RD_BIT
{
	UINT32 DACC1DHR:8;    //00,DAC channel1 8-bit Right aligned data
	UINT32 DACC2DHR:8;    //08,DAC channel2 8-bit Right aligned data
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DOR1           0x00000000//0x02C
struct DAC_DOR1_BIT
{
	UINT32 DACC1DOR:12;   //00,DAC channel1 data output
	UINT32 Reserved0:16;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_DOR2           0x00000000//0x030
struct DAC_DOR2_BIT
{
	UINT32 DACC2DOR:12;   //00,DAC channel2 data output
	UINT32 Reserved0:16;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DAC_SR             0x00000000//0x030
struct DAC_SR_BIT
{
	UINT32 Reserved0:13;  //00,
	UINT32 DMAUDR1:1;     //13,DAC channel1 DMA underrun flag
	UINT32 Reserved1:15;  //14,
	UINT32 DMAUDR2:1;     //29,DAC channel2 DMA underrun flag
	UINT32 Reserved2:2;   //30,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DAC_Struct Struct_DAC
typedef struct Struct_DAC
{
  union{UINT32 CR;struct DAC_CR_BIT CR_BIT;};
  union{UINT32 SWTRIGR;struct DAC_SWTRIGR_BIT SWTRIGR_BIT;};
  union{UINT32 DHR12R1;struct DAC_DHR12R1_BIT DHR12R1_BIT;};
  union{UINT32 DHR12L1;struct DAC_DHR12L1_BIT DHR12L1_BIT;};
  union{UINT32 DHR8R1;struct DAC_DHR8R1_BIT DHR8R1_BIT;};
  union{UINT32 DHR12R2;struct DAC_DHR12R2_BIT DHR12R2_BIT;};
  union{UINT32 DHR12L2;struct DAC_DHR12L2_BIT DHR12L2_BIT;};
  union{UINT32 DHR8R2;struct DAC_DHR8R2_BIT DHR8R2_BIT;};
  union{UINT32 DHR12RD;struct DAC_DHR12RD_BIT DHR12RD_BIT;};
  union{UINT32 DHR12LD;struct DAC_DHR12LD_BIT DHR12LD_BIT;};
  union{UINT32 DHR8RD;struct DAC_DHR8RD_BIT DHR8RD_BIT;};
  union{UINT32 DOR1;struct DAC_DOR1_BIT DOR1_BIT;};
  union{UINT32 DOR2;struct DAC_DOR2_BIT DOR2_BIT;};
  #if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  union{UINT32 SR;struct DAC_SR_BIT SR_BIT;};
  #endif
} DAC_Type,Type_DAC;
#define PT_DAC    ((volatile Type_DAC *)BASE_DAC)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DAC_CR                  DAC.CR
#define DAC_SWTRIGR             DAC.SWTRIGR
#define DAC_DHR12R1             DAC.DHR12R1
#define DAC_DHR12L1             DAC.DHR12L1
#define DAC_DHR8R1              DAC.DHR8R1
#define DAC_DHR12R2             DAC.DHR12R2
#define DAC_DHR12L2             DAC.DHR12L2
#define DAC_DHR8R2              DAC.DHR8R2
#define DAC_DHR12RD             DAC.DHR12RD
#define DAC_DHR12LD             DAC.DHR12LD
#define DAC_DHR8RD              DAC.DHR8RD
#define DAC_DOR1                DAC.DOR1
#define DAC_DOR2                DAC.DOR2
#define DAC_SR                  DAC.SR
//==============================================================================================================================
#define RSTV_DMA_ISR            0x00000000//0x000
#define RSTV_DMA_IFCR           0x00000000//0x004
struct DMA_INT_BIT//0x000=ISR,0x004=IFCR
{
	UINT32 GIF1:1;        //00,Channel 1 Global interrupt flag
	UINT32 TCIF1:1;       //01,Channel 1 Transfer Complete flag
	UINT32 HTIF1:1;       //02,Channel 1 Half Transfer flag
	UINT32 TEIF1:1;       //03,Channel 1 Transfer Error flag
	UINT32 GIF2:1;        //04,Channel 2 Global interrupt flag
	UINT32 TCIF2:1;       //05,Channel 2 Transfer Complete flag
	UINT32 HTIF2:1;       //06,Channel 2 Half Transfer flag
	UINT32 TEIF2:1;       //07,Channel 2 Transfer Error flag
	UINT32 GIF3:1;        //08,Channel 3 Global interrupt flag
	UINT32 TCIF3:1;       //09,Channel 3 Transfer Complete flag
	UINT32 HTIF3:1;       //10,Channel 3 Half Transfer flag
	UINT32 TEIF3:1;       //11,Channel 3 Transfer Error flag
	UINT32 GIF4:1;        //12,Channel 4 Global interrupt flag
	UINT32 TCIF4:1;       //13,Channel 4 Transfer Complete flag
	UINT32 HTIF4:1;       //14,Channel 4 Half Transfer flag
	UINT32 TEIF4:1;       //15,Channel 4 Transfer Error flag
	UINT32 GIF5:1;        //16,Channel 5 Global interrupt flag
	UINT32 TCIF5:1;       //17,Channel 5 Transfer Complete flag
	UINT32 HTIF5:1;       //18,Channel 5 Half Transfer flag
	UINT32 TEIF5:1;       //19,Channel 5 Transfer Error flag
	UINT32 GIF6:1;        //20,Channel 6 Global interrupt flag
	UINT32 TCIF6:1;       //21,Channel 6 Transfer Complete flag
	UINT32 HTIF6:1;       //22,Channel 6 Half Transfer flag
	UINT32 TEIF6:1;       //23,Channel 6 Transfer Error flag
	UINT32 GIF7:1;        //24,Channel 7 Global interrupt flag
	UINT32 TCIF7:1;       //25,Channel 7 Transfer Complete flag
	UINT32 HTIF7:1;       //26,Channel 7 Half Transfer flag
	UINT32 TEIF7:1;       //27,Channel 7 Transfer Error flag
	UINT32 Reserved0:4;   //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DMA_CCR1           0x00000000//0x008
#define RSTV_DMA_CCR2           0x00000000//0x01C
#define RSTV_DMA_CCR3           0x00000000//0x030
#define RSTV_DMA_CCR4           0x00000000//0x044
#define RSTV_DMA_CCR5           0x00000000//0x058
#define RSTV_DMA_CCR6           0x00000000//0x06C
#define RSTV_DMA_CCR7           0x00000000//0x080
struct DMA_CCR_BIT//0x008=CCR1,CCR2,CCR3,CCR4,CCR5,CCR6,CCR7
{
	UINT32 EN:1;          //00,Channel enable:1=enable
	UINT32 TCIE:1;        //01,Transfer complete interrupt enable:1=enable
	UINT32 HTIE:1;        //02,Half Transfer interrupt enable:1=enable
	UINT32 TEIE:1;        //03,Transfer error interrupt enable:1=enable
	UINT32 DIR:1;         //04,Data transfer direction:0=read from peripheral,1=read from memory
	UINT32 CIRC:1;        //05,Circular mode:1=enable
	UINT32 PINC:1;        //06,Peripheral increment mode:1=enable
	UINT32 MINC:1;        //07,Memory increment mode:1=enable
	UINT32 PSIZE:2;       //08,PSIZE[1:0] bits (Peripheral size):0=8 bits,1=16 bits,2=32 bits,3=reserved
	UINT32 MSIZE:2;       //10,MSIZE[1:0] bits (Memory size):0=8 bits,1=16 bits,2=32 bits,3=reserved
	UINT32 PL:2;          //12,PL[1:0] bits(Channel Priority level):0=Low,1=Medium,2=High,3=Very High
	UINT32 MEM2MEM:1;     //14,Memory to memory mode:1=enable
	UINT32 Reserved0:17;  //15,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DMA_CNDTR1         0x00000000//0x00C
#define RSTV_DMA_CNDTR2         0x00000000//0x020
#define RSTV_DMA_CNDTR3         0x00000000//0x034
#define RSTV_DMA_CNDTR4         0x00000000//0x048
#define RSTV_DMA_CNDTR5         0x00000000//0x05C
#define RSTV_DMA_CNDTR6         0x00000000//0x070
#define RSTV_DMA_CNDTR7         0x00000000//0x084
#define RSTV_DMA_CNDTR          0x00000000
struct DMA_CNDTR_BIT//0x00C=CNDTR1,CNDTR2,CNDTR3,CNDTR4,CNDTR5,CNDTR6,CNDTR7
{
	UINT32 NDT:16;        //00,Number of data to Transfer
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DMA_CPAR1          0x00000000//0x010,Peripheral Address
#define RSTV_DMA_CPAR2          0x00000000//0x024,Peripheral Address
#define RSTV_DMA_CPAR3          0x00000000//0x038,Peripheral Address
#define RSTV_DMA_CPAR4          0x00000000//0x04C,Peripheral Address
#define RSTV_DMA_CPAR5          0x00000000//0x060,Peripheral Address
#define RSTV_DMA_CPAR6          0x00000000//0x074,Peripheral Address
#define RSTV_DMA_CPAR7          0x00000000//0x088,Peripheral Address
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DMA_CMAR1          0x00000000//0x014,Memory Address
#define RSTV_DMA_CMAR2          0x00000000//0x028,Memory Address
#define RSTV_DMA_CMAR3          0x00000000//0x03C,Memory Address
#define RSTV_DMA_CMAR4          0x00000000//0x050,Memory Address
#define RSTV_DMA_CMAR5          0x00000000//0x064,Memory Address
#define RSTV_DMA_CMAR6          0x00000000//0x078,Memory Address
#define RSTV_DMA_CMAR7          0x00000000//0x08C,Memory Address
//------------------------------------------------------------------------------------------------------------------------------
typedef struct DMACH
{
  union{UINT32 CCR;struct DMA_CCR_BIT CCR_BIT;};
  union{UINT32 CNDTR;struct DMA_CNDTR_BIT CNDTR_BIT;};
  union{UINT32 CPAR;Type_BIT32 CPAR_BIT;};
  union{UINT32 CMAR;Type_BIT32 CMAR_BIT;};
	UINT32 Reserved0[1];
} DMACH_Type,Type_DMACH;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DMA_Struct Struct_DMA
typedef struct Struct_DMA//0x40020000=DMA1,0x40020400=DMA2
{
  union{UINT32 ISR;struct DMA_INT_BIT ISR_BIT;};    //0x000,
  union{UINT32 IFCR;struct DMA_INT_BIT IFCR_BIT;};  //0x004,
	Type_DMACH CH[8];//0x008,Index:DMA[0]=0_6,DMA[1]=0_4
	UINT32 Reserved0[214]; //0x0A8,
} DMA_Type,Type_DMA;
#define PT_DMA1                 ((volatile Type_DMA *)BASE_DMA1)
#define PT_DMA2                 ((volatile Type_DMA *)BASE_DMA2)
#define PT_DMA(i)               ((volatile Type_DMA *)BASE_DMA(i))
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DMA_ISR(i)              DMA[i].ISR//i=0_1
#define DMA_IFCR(i)             DMA[i].IFCR//i=0_1
#define DMA_CCR(i,j)            DMA[i].CH[j].CCR//i=0,j=0_6;i=1,j=0_4
#define DMA_CNDTR(i,j)          DMA[i].CH[j].CNDTR//i=0,j=0_6;i=1,j=0_4
#define DMA_CPAR(i,j)           DMA[i].CH[j].CPAR//i=0,j=0_6;i=1,j=0_4
#define DMA_CMAR(i,j)           DMA[i].CH[j].CMAR//i=0,j=0_6;i=1,j=0_4
//==============================================================================================================================
#define RSTV_ETH_MACCR          0x00000000//0x000
struct ETH_MACCR_BIT
{
	UINT32 Reserved0:2;   //00,
	UINT32 RE:1;          //02,Receiver enable
	UINT32 TE:1;          //03,Transmitter enable
	UINT32 DC:1;          //04,Defferal check
	UINT32 BL:2;          //05,Back-off limit: random integer number (r) of slot time delays before rescheduling
	                      //   a transmission attempt during retries after a collision: 0 =< r <2^k
	UINT32 APCS:1;        //07,Automatic Pad/CRC stripping
	UINT32 Reserved1:1;   //08,
	UINT32 RD:1;          //09,Retry disable
	UINT32 IPCO:1;        //10,IP Checksum offload
	UINT32 DM:1;          //11,Duplex mode
	UINT32 LM:1;          //12,loopback mode
	UINT32 ROD:1;         //13,Receive own disable
	UINT32 FES:1;         //14,Fast ethernet speed
	UINT32 Reserved2:1;   //15,
	UINT32 CSD:1;         //16,Carrier sense disable (during transmission)
	UINT32 IFG:3;         //17,Inter-frame gap
	UINT32 Reserved3:2;   //20,
	UINT32 JD:1;          //22,Jabber disable
	UINT32 WD:1;          //23,Watchdog disable
	UINT32 Reserved4:8;   //24,
};
#define ETH_MACCR_BL_10                 0//k = min (n, 10)
#define ETH_MACCR_BL_8                  1//k = min (n, 8)
#define ETH_MACCR_BL_4                  2//k = min (n, 4)
#define ETH_MACCR_BL_1                  3//k = min (n, 1)
#define ETH_MACCR_IFG_96Bit             0//Minimum IFG between frames during transmission is 96Bit
#define ETH_MACCR_IFG_88Bit             1//Minimum IFG between frames during transmission is 88Bit
#define ETH_MACCR_IFG_80Bit             2//Minimum IFG between frames during transmission is 80Bit
#define ETH_MACCR_IFG_72Bit             3//Minimum IFG between frames during transmission is 72Bit
#define ETH_MACCR_IFG_64Bit             4//Minimum IFG between frames during transmission is 64Bit      
#define ETH_MACCR_IFG_56Bit             5//Minimum IFG between frames during transmission is 56Bit
#define ETH_MACCR_IFG_48Bit             6//Minimum IFG between frames during transmission is 48Bit
#define ETH_MACCR_IFG_40Bit             7//Minimum IFG between frames during transmission is 40Bit 
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACFFR         0x00000000//0x004
struct ETH_MACFFR_BIT
{
	UINT32 PM:1;          //00,Promiscuous mode
	UINT32 HU:1;          //01,Hash unicast
	UINT32 HM:1;          //02,Hash multicast
	UINT32 DAIF :1;       //03,DA Inverse filtering
	UINT32 PAM:1;         //04,Pass all mutlicast
	UINT32 BFD:1;         //05,Broadcast frame disable
	UINT32 PCF:2;         //06,Pass control frames: 3 cases
	UINT32 SAIF:1;        //08,SA inverse filtering,<LDY>
	UINT32 SAF:1;         //09,Source address filter enable
	UINT32 HPF:1;         //10,Hash or perfect filter
	UINT32 Reserved0:20;  //11,
	UINT32 RA:1;          //31,Receive all
};
#define ETH_MACFFR_PCF_BlockAll         1//MAC filters all control frames from reaching the application
#define ETH_MACFFR_PCF_ForwardAll       2//MAC forwards all control frames to application even if they fail the Address Filter
#define ETH_MACFFR_PCF_FPAF             3//MAC forwards control frames that pass the Address Filter. 
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACHTHR        0x00000000//0x008,bit0_31=HTH=Hash table high
#define RSTV_ETH_MACHTLR        0x00000000//0x00C,bit0_31=HTL=Hash table low
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACMIIAR       0x00000000//0x010,Ethernet MAC MII Address Register
#define ETH_MACMIIAR_CR_Div42           0//HCLK:60-72 MHz; MDC clock= HCLK/42
#define ETH_MACMIIAR_CR_Div62           1//HCLK:60-72 MHz; MDC clock= HCLK/62
#define ETH_MACMIIAR_CR_Div16           2//HCLK:20-35 MHz; MDC clock= HCLK/16
#define ETH_MACMIIAR_CR_Div26           3//HCLK:35-60 MHz; MDC clock= HCLK/26
#define ETH_MACMIIAR_CR_Div102          4//HCLK:150-168 MHz; MDC clock= HCLK/102
struct ETH_MACMIIAR_BIT
{
	UINT32 MB:1;          //00,MII busy
	UINT32 MW:2;          //01,MII write
	UINT32 CR:3;          //02,CR clock range: 6 cases
	UINT32 Reserved0:1;   //05,
	UINT32 MR:5;          //06,MII register in the selected PHY
	UINT32 PA:5;          //11,Physical layer address
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACMIIDR       0x00000000//0x014
struct ETH_MACMIIDR_BIT
{
	UINT32 MD:16;         //00,MII data: read/write data from/to PHY
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACFCR         0x00000000//0x018
struct ETH_MACFCR_BIT
{
	UINT32 FCBBPA:1;      //00,Flow control busy/backpressure activate
	UINT32 TFCE:1;        //01,Transmit flow control enable
	UINT32 RFCE:1;        //02,Receive flow control enable
	UINT32 UPFD:1;        //03,Unicast pause frame detect
	UINT32 Reserved0:3;   //04,
	UINT32 ZQPD:1;        //07,Zero-quanta pause disable
	UINT32 Reserved1:8;   //08,
	UINT32 PT:16;         //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACVLANTR      0x00000000//0x01C
struct ETH_MACVLANTR_BIT
{
	UINT32 VLANTI:16;     //00,VLAN tag identifier (for receive frames)
	UINT32 VLANTC:1;      //16,12-bit VLAN tag comparison
	UINT32 Reserved0:15;  //17,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACRWUFFR      0x00000000//0x028,bit0_31=D=Wake-up frame filter register data,reg0_reg7
struct ETH_MACRWUFFR_BIT
{
	UINT32 REG0:4;        //00,Filter 0 Byte Mask
	UINT32 REG1:4;        //04,Filter 1 Byte Mask
	UINT32 REG2:4;        //08,Filter 2 Byte Mask
	UINT32 REG3:4;        //12,Filter 3 Byte Mask
	UINT32 REG4:4;        //16,RSVD - Filter3 Command - RSVD - Filter2 Command -RSVD - Filter1 Command - RSVD - Filter0 Command
	UINT32 REG5:4;        //20,Filter3 Offset - Filter2 Offset - Filter1 Offset - Filter0 Offset
	UINT32 REG6:4;        //24,Filter1 CRC16 - Filter0 CRC16
	UINT32 REG7:4;        //28,Filter3 CRC16 - Filter2 CRC16
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACPMTCSR      0x00000000//0x02C,MAC PMT Control and Status Register
struct ETH_MACPMTCSR_BIT
{
	UINT32 PD:1;          //00,Power Down
	UINT32 MPE:1;         //01,Magic Packet Enable
	UINT32 WFE:1;         //02,Wake-Up Frame Enable
	UINT32 Reserved0:2;   //03,
	UINT32 MPR:1;         //05,Magic Packet Received
	UINT32 WFR:1;         //06,Wake-Up Frame Received
	UINT32 Reserved1:2;   //07,
	UINT32 GU:1;          //09,Global Unicast
	UINT32 Reserved2:21;  //10,
	UINT32 WFFRPR:1;      //31,Wake-Up Frame Filter Register Pointer Reset
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACSR          0x00000000//0x038,Ethernet MAC Status Register
struct ETH_MACSR_BIT
{
	UINT32 Reserved0:3;   //00,
	UINT32 PMTS:1;        //03,PMT status
	UINT32 MMCS:1;        //04,MMC status
	UINT32 MMMCRS:1;      //05,MMC receive status
	UINT32 MMCTS:1;       //06,MMC transmit status
	UINT32 Reserved1:2;   //07,
	UINT32 TSTS:1;        //09,Time stamp trigger status
	UINT32 Reserved2:22;  //10,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACIMR         0x00000000//0x03C,Ethernet MAC Interrupt Mask Register
struct ETH_MACIMR_BIT
{
	UINT32 Reserved0:3;   //00,
	UINT32 PMTIM:1;       //03,PMT interrupt mask
	UINT32 Reserved1:5;   //04,
	UINT32 TSTIM:1;       //09,Time stamp trigger interrupt mask
	UINT32 Reserved2:22;  //10,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACA0LR        0xFFFFFFFF//0x044,MAC address0 low
#define RSTV_ETH_MACA1LR        0xFFFFFFFF//0x04C,MAC address1 low
#define RSTV_ETH_MACA2LR        0xFFFFFFFF//0x054,MAC address2 low
#define RSTV_ETH_MACA3LR        0xFFFFFFFF//0x05C,MAC address3 low
#define RSTV_ETH_MACALR         0xFFFFFFFF
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACA0HR        0x00000000//0x040,MAC address0 high
struct ETH_MACA0HR_BIT
{
	UINT32 MACA0H:16;     //00,
	UINT32 Reserved0:15;  //16,
	UINT32 MO:1;          //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MACA1HR        0x0000FFFF//0x048,MAC address1 high
#define RSTV_ETH_MACA2HR        0x0000FFFF//0x050,MAC address1 high
#define RSTV_ETH_MACA3HR        0x0000FFFF//0x058,MAC address1 high
#define RSTV_ETH_MACAHR         0x0000FFFF
struct ETH_MACA123HR_BIT//MACA1HR,MACA2HR,MACA3HR
{
	UINT32 MACAH:16;      //00,MAC address high
	UINT32 Reserved0:8;   //16,
	UINT32 MBC:6;         //24,Mask byte control: bits to mask for comparison of the MAC Address bytes,<LDY>
	UINT32 SA:1;          //30,Source address
	UINT32 AE:1;          //31,Address enable
};
#define ETH_MACAHR_MBC_HBits15_8        0x20//Mask MAC Address high reg bits [15:8]
#define ETH_MACAHR_MBC_HBits7_0         0x10//Mask MAC Address high reg bits [7:0]
#define ETH_MACAHR_MBC_LBits31_24       0x08//Mask MAC Address low reg bits [31:24]
#define ETH_MACAHR_MBC_LBits23_16       0x04//Mask MAC Address low reg bits [23:16]
#define ETH_MACAHR_MBC_LBits15_8        0x02//Mask MAC Address low reg bits [15:8]
#define ETH_MACAHR_MBC_LBits7_0         0x01//Mask MAC Address low reg bits [7:0] 
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MMCCR          0x00000000//0x100,Ethernet MMC Contol Register
struct ETH_MMCCR_BIT
{
	UINT32 CR:1;          //00,Counters Reset
	UINT32 CSR:1;         //01,Counter Stop Rollover
	UINT32 ROR:1;         //02,Reset on Read
	UINT32 MCF:1;         //03,MMC Counter Freeze
	UINT32 Reserved0:28;  //04,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MMCRIR         0x00000000//0x104,Ethernet MMC Receive Interrupt Register
#define RSTV_ETH_MMCRIMR        0x00000000//0x10C,Ethernet MMC Receive Interrupt mask Register
struct ETH_MMCRI_BIT//0x104=MMCRIR,0x10C=MMCRIMR
{
	UINT32 Reserved0:5;   //00,
	UINT32 RFCE:1;        //05,Set/Mask when Rx crc error counter reaches half the maximum value
	UINT32 RFAE:1;        //06,Set/Mask when Rx alignment error counter reaches half the maximum value
	UINT32 Reserved1:10;  //07,
	UINT32 RGUF:1;        //17,Set/Mask when Rx good unicast frames counter reaches half the maximum value
	UINT32 Reserved2:14;  //18,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MMCTIR         0x00000000//0x108,Ethernet MMC Transmit Interrupt Register
#define RSTV_ETH_MMCTIMR        0x00000000//0x110,Ethernet MMC Transmit Interrupt mask Register
struct ETH_MMCTI_BIT//0x108=MMCTIR,0x010=MMCTIMR
{
	UINT32 Reserved0:14;  //00,
	UINT32 TGFSC:1;       //14,Set/Mask when Tx good single col counter reaches half the maximum value
	UINT32 TGFMSC:1;      //15,Set/Mask when Tx good multi col counter reaches half the maximum value
	UINT32 Reserved1:5;   //16,
	UINT32 TGF:1;         //21,Set/Mask when Tx good frame count counter reaches half the maximum value
	UINT32 Reserved2:10;  //22,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_MMCTGFSCCR     0x00000000//0x14C,bit0_31=TGFSCC=Number of successfully transmitted frames after a single collision in Half-duplex mode
#define RSTV_ETH_MMCTGFMSCCR    0x00000000//0x150,bit0_31=TGFMSCC=Number of successfully transmitted frames after more than a single collision in Half-duplex mode
#define RSTV_ETH_MMCTGFCR       0x00000000//0x168,bit0_31=TGFC=Number of good frames transmitted
#define RSTV_ETH_MMCRFCECR      0x00000000//0x194,bit0_31=RFCEC=Number of frames received with CRC error
#define RSTV_ETH_MMCRFAECR      0x00000000//0x198,bit0_31=RFAEC=Number of frames received with alignment (dribble) error
#define RSTV_ETH_MMCRGUFCR      0x00000000//0x1C4,bit0_31=RGUFC=Number of good unicast frames received
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPTSCR        0x00000000//0x700,Ethernet PTP Time Stamp Contol Register
struct ETH_PTPTSCR_BIT
{
	UINT32 TSE:1;         //00,Time stamp enable
	UINT32 TSFCU:1;       //01,Time stamp fine or coarse update
	UINT32 TSSTI:1;       //02,Time stamp initialize
	UINT32 TSSTU:1;       //03,Time stamp update
	UINT32 TSITE:1;       //04,Time stamp interrupt trigger enable
	UINT32 TSARU:1;       //05,Addend register update
	UINT32 Reserved0:26;  //06,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPSSIR        0x00000000//0x704,Ethernet PTP Sub-Second Increment Register
struct ETH_PTPSSIR_BIT
{
	UINT32 STSSI:8;      //00,System time Sub-second increment value
	UINT32 Reserved0:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPTSHR        0x00000000//0x708,bit0_31=STS=System Time second,Ethernet PTP Time Stamp High Register
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPTSLR        0x00000000//0x70C,Ethernet PTP Time Stamp Low Register
struct ETH_PTPTSLR_BIT
{
	UINT32 STSS:31;       //00,System Time sub-seconds
	UINT32 STPNS:1;       //31,System Time Positive or negative time
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPTSHUR       0x00000000//0x710,bit0_31=TSUS=Time stamp update seconds,Ethernet PTP Time Stamp High Update Register
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPTSLUR       0x00000000//0x714,Ethernet PTP Time Stamp Low Update Register
struct ETH_PTPTSLUR_BIT
{
	UINT32 TSUSS:31;      //00,Time stamp update sub-seconds
	UINT32 TSUPNS:1;      //31,Time stamp update Positive or negative time
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_PTPTSAR        0x00000000//0x718,bit0_31=TSA=Time stamp addend,Ethernet PTP Time Stamp Addend Register
#define RSTV_ETH_PTPTTHR        0x00000000//0x71C,bit0_31=TTSH=Target time stamp high,Ethernet PTP Target Time High Register
#define RSTV_ETH_PTPTTLR        0x00000000//0x720,bit0_31=TTSL=Target time stamp low,Ethernet PTP Target Time Low Register
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMABMR         0x00000000//0x1000,Ethernet DMA Bus Mode Register
struct ETH_DMABMR_BIT
{
	UINT32 SR:1;          //00,Software reset
	UINT32 DA:1;          //01,DMA arbitration scheme
	UINT32 DSL:5;         //02,Descriptor Skip Length
	UINT32 Reserved0:1;   //07,
	UINT32 PBL:6;         //8,Programmable burst length
	UINT32 RTPR:2;        //14,Rx Tx priority ratio
	UINT32 FB:1;          //16,Fixed Burst
	UINT32 RDP:6;         //17,RxDMA PBL
	UINT32 USP:1;         //23,Use separate PBL
	UINT32 FPM:1;         //24,4xPBL mode
	UINT32 AAB:1;         //25,Address-Aligned beats
	UINT32 Reserved2:6;   //26,
};
#define ETH_DMABMR_RDP_1Beat            0x01//maximum number of beats to be transferred in one RxDMA transaction is 1,FPM=1=*4
#define ETH_DMABMR_RDP_2Beat            0x02//maximum number of beats to be transferred in one RxDMA transaction is 2,FPM=1=*4
#define ETH_DMABMR_RDP_4Beat            0x04//maximum number of beats to be transferred in one RxDMA transaction is 4,FPM=1=*4
#define ETH_DMABMR_RDP_8Beat            0x08//maximum number of beats to be transferred in one RxDMA transaction is 8,FPM=1=*4
#define ETH_DMABMR_RDP_16Beat           0x10//maximum number of beats to be transferred in one RxDMA transaction is 16,FPM=1=*4
#define ETH_DMABMR_RDP_32Beat           0x20//maximum number of beats to be transferred in one RxDMA transaction is 32,FPM=1=*4
#define ETH_DMABMR_RTPR_1_1             0//Rx Tx priority ratio
#define ETH_DMABMR_RTPR_2_1             1//Rx Tx priority ratio
#define ETH_DMABMR_RTPR_3_1             2//Rx Tx priority ratio
#define ETH_DMABMR_RTPR_4_1             3//Rx Tx priority ratio  
#define ETH_DMABMR_PBL_1Beat            0x01//maximum number of beats to be transferred in one TxDMA (or both) transaction is 1,FPM=1=*4
#define ETH_DMABMR_PBL_2Beat            0x02//maximum number of beats to be transferred in one TxDMA (or both) transaction is 2,FPM=1=*4
#define ETH_DMABMR_PBL_4Beat            0x04//maximum number of beats to be transferred in one TxDMA (or both) transaction is 4,FPM=1=*4
#define ETH_DMABMR_PBL_8Beat            0x08//maximum number of beats to be transferred in one TxDMA (or both) transaction is 8,FPM=1=*4
#define ETH_DMABMR_PBL_16Beat           0x10//maximum number of beats to be transferred in one TxDMA (or both) transaction is 16,FPM=1=*4
#define ETH_DMABMR_PBL_32Beat           0x20//maximum number of beats to be transferred in one TxDMA (or both) transaction is 32,FPM=1=*4               
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMATPDR        0x00000000//0x1004,bit0_31=TPD=Transmit poll demand,Ethernet DMA Transmit Poll Demand Register
#define RSTV_ETH_DMARPDR        0x00000000//0x1008,bit0_31=RPD=Receive poll demand,Ethernet DMA Receive Poll Demand Register
#define RSTV_ETH_DMARDLAR       0x00000000//0x100C,bit0_31=SRL=Start of receive list
#define RSTV_ETH_DMATDLAR       0x00000000//0x1010,bit0_31=STL=Start of transmit list
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMASR          0x00000000//0x1014
struct ETH_DMASR_BIT
{
	UINT32 TS:1;          //00,Transmit status
	UINT32 TPSS:1;        //01,Transmit process stopped status
	UINT32 TBUS:1;        //02,Transmit buffer unavailable status
	UINT32 TJTS:1;        //03,Transmit jabber timeout status
	UINT32 ROS:1;         //04,Receive overflow status
	UINT32 TUS:1;         //05,Transmit underflow status
	UINT32 RS:1;          //06,Receive status
	UINT32 RBUS:1;        //07,Receive buffer unavailable status
	UINT32 RPSS:1;        //08,Receive process stopped status
	UINT32 RWTS:1;        //09,Receive watchdog timeout status
	UINT32 ETS:1;         //10,Early transmit status
	UINT32 Reserved0:2;   //11,
	UINT32 FBES:1;        //13,Fatal bus error status
	UINT32 ERS:1;         //14,Early receive status
	UINT32 AIS:1;         //15,Abnormal interrupt summary
	UINT32 NIS:1;         //16,Normal interrupt summary
	UINT32 RPS:3;         //17,Receive process state
	UINT32 TPS:3;         //20,Transmit process state
	UINT32 EBS:3;         //23,Error bits status
	UINT32 Reserved1:1;   //26,
	UINT32 MMCS:1;        //27,MMC status
	UINT32 PMTS:1;        //28,PMT status
	UINT32 TSTS:1;        //29,Time-stamp trigger status
	UINT32 Reserved2:2;   //30,
};
#define ETH_DMASR_RPS_Stopped           0//Stopped - Reset or Stop Rx Command issued
#define ETH_DMASR_RPS_Fetching          1//Running - fetching the Rx descriptor
#define ETH_DMASR_RPS_Waiting           3//Running - waiting for packet
#define ETH_DMASR_RPS_Suspended         4//Suspended - Rx Descriptor unavailable
#define ETH_DMASR_RPS_Closing           5//Running - closing descriptor
#define ETH_DMASR_RPS_Queuing           7//Running - queuing the recieve frame into host memory
#define ETH_DMASR_TPS_Stopped           0//Stopped - Reset or Stop Tx Command issued
#define ETH_DMASR_TPS_Fetching          1//Running - fetching the Tx descriptor
#define ETH_DMASR_TPS_Waiting           2//Running - waiting for status
#define ETH_DMASR_TPS_Reading           3//Running - reading the data from host memory
#define ETH_DMASR_TPS_Suspended         6//Suspended - Tx Descriptor unavailabe
#define ETH_DMASR_TPS_Closing           7//Running - closing Rx descriptor
#define ETH_DMASR_EBS_DescAccess        4//Error bits 0-data buffer, 1-desc. access
#define ETH_DMASR_EBS_ReadTransf        2//Error bits 0-write trnsf, 1-read transfr
#define ETH_DMASR_EBS_DataTransfTx      1//Error bits 0-Rx DMA, 1-Tx DMA
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMAOMR         0x00000000//0x1018
struct ETH_DMAOMR_BIT
{
	UINT32 Reserved0:1;   //00,
	UINT32 SR:1;          //01,Start/stop receive
	UINT32 OSF:1;         //02,operate on second frame
	UINT32 RTC:2;         //03,receive threshold control
	UINT32 Reserved1:1;   //05,
	UINT32 FUGF:1;        //06,Forward undersized good frames
	UINT32 FEF:1;         //07,Forward error frames
	UINT32 Reserved2:5;   //08,
	UINT32 ST:1;          //13,Start/stop transmission command
	UINT32 TTC:3;         //14,Transmit threshold control
	UINT32 Reserved3:3;   //17,
	UINT32 FTF:1;         //20,Flush transmit FIFO
	UINT32 TSF:1;         //21,Transmit store and forward
	UINT32 Reserved4:2;   //22,
	UINT32 DFRF:1;        //24,Disable flushing of received frames
	UINT32 RSF:1;         //25,Receive store and forward
	UINT32 DTCEFD:1;      //26,Disable Dropping of TCP/IP checksum error frames
	UINT32 Reserved5:5;   //27,
};
#define ETH_DMAOMR_RTC_64Bytes           0//threshold level of the MTL Receive FIFO is 64 Bytes
#define ETH_DMAOMR_RTC_32Bytes           1//threshold level of the MTL Receive FIFO is 32 Bytes
#define ETH_DMAOMR_RTC_96Bytes           2//threshold level of the MTL Receive FIFO is 96 Bytes
#define ETH_DMAOMR_RTC_128Bytes          3//threshold level of the MTL Receive FIFO is 128 Bytes
#define ETH_DMAOMR_TTC_64Bytes           0//threshold level of the MTL Transmit FIFO is 64 Bytes
#define ETH_DMAOMR_TTC_128Bytes          1//threshold level of the MTL Transmit FIFO is 128 Bytes
#define ETH_DMAOMR_TTC_192Bytes          2//threshold level of the MTL Transmit FIFO is 192 Bytes
#define ETH_DMAOMR_TTC_256Bytes          3//threshold level of the MTL Transmit FIFO is 256 Bytes
#define ETH_DMAOMR_TTC_40Bytes           4//threshold level of the MTL Transmit FIFO is 40 Bytes
#define ETH_DMAOMR_TTC_32Bytes           5//threshold level of the MTL Transmit FIFO is 32 Bytes
#define ETH_DMAOMR_TTC_24Bytes           6//threshold level of the MTL Transmit FIFO is 24 Bytes
#define ETH_DMAOMR_TTC_16Bytes           7//threshold level of the MTL Transmit FIFO is 16 Bytes
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMAIER         0x00000000//0x101C
struct ETH_DMAIER_BIT
{
	UINT32 TIE:1;         //00,Transmit interrupt enable
	UINT32 TPSIE:1;       //01,Transmit process stopped interrupt enable
	UINT32 TBUIE:1;       //02,Transmit buffer unavailable interrupt enable
	UINT32 TJTIE:1;       //03,Transmit jabber timeout interrupt enable
	UINT32 ROIE:1;        //04,Receive Overflow interrupt enable
	UINT32 TUIE:1;        //05,Transmit Underflow interrupt enable
	UINT32 RIE:1;         //06,Receive interrupt enable
	UINT32 RBUIE:1;       //07,Receive buffer unavailable interrupt enable
	UINT32 RPSIE:1;       //08,Receive process stopped interrupt enable
	UINT32 RWTIE:1;       //09,Receive watchdog timeout interrupt enable
	UINT32 ETIE:1;        //10,Early transmit interrupt enable
	UINT32 Reserved0:2;   //11,
	UINT32 FBEIE:1;       //13,Fatal bus error interrupt enable
	UINT32 ERIE:1;        //14,Early receive interrupt enable
	UINT32 AISE:1;        //15,Abnormal interrupt summary enable
	UINT32 NISE:1;        //16,Normal interrupt summary enable
	UINT32 Reserved1:15;  //17,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMAMFBOCR      0x00000000//0x1020,Ethernet DMA Missed Frame and Buffer Overflow Counter Register
struct ETH_DMAMFBOCR_BIT
{
	UINT32 MFC:16;        //00,Number of frames missed by the controller
	UINT32 OMFC:1;        //16,Overflow bit for missed frame counter
	UINT32 MFA:11;        //17,Number of frames missed by the application
	UINT32 OFOC:1;        //28,Overflow bit for FIFO overflow counter
	UINT32 Reserved0:3;   //29,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETH_DMACHTDR       0x00000000//0x1048,bit0_31=HTDAP=Host transmit descriptor address pointer
#define RSTV_ETH_DMACHRDR       0x00000000//0x104C,bit0_31=HRDAP=Host receive descriptor address pointer
#define RSTV_ETH_DMACHTBAR      0x00000000//0x1050,bit0_31=HTBAP=Host transmit buffer address pointer
#define RSTV_ETH_DMACHRBAR      0x00000000//0x1054,bit0_31=HRBAP=Host receive buffer address pointer
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ETH_Struct Struct_ETH
typedef struct Struct_ETH//0x40028000
{
  union{UINT32 MACCR;struct ETH_MACCR_BIT MACCR_BIT;};          //0x000(RW),Ethernet MAC Control Register register
  union{UINT32 MACFFR;struct ETH_MACFFR_BIT MACFFR_BIT;};       //0x004(RW),Ethernet MAC Frame Filter Register
  union{UINT32 MACHTHR;Type_BIT32 MACHTHR_BIT;};                //0x008(RW),Ethernet MAC Hash Table High Register
  union{UINT32 MACHTLR;Type_BIT32 MACHTLR_BIT;};                //0x00C(RW),Ethernet MAC Hash Table Low Register
  union{UINT32 MACMIIAR;struct ETH_MACMIIAR_BIT MACMIIAR_BIT;}; //0x010(RW),Ethernet MAC MII Address Register
  union{UINT32 MACMIIDR;struct ETH_MACMIIDR_BIT MACMIIDR_BIT;}; //0x014(RW),Ethernet MAC MII Data Register
  union{UINT32 MACFCR;struct ETH_MACFCR_BIT MACFCR_BIT;};       //0x018(RW),Ethernet MAC Flow Control Register
  union{UINT32 MACVLANTR;struct ETH_MACVLANTR_BIT MACVLANTR_BIT;};//0x01C(RW),Ethernet MAC VLAN Tag Register
  UINT32 Reserved0[2];  //0x020(R),
  union{UINT32 MACRWUFFR;struct ETH_MACRWUFFR_BIT MACRWUFFR_BIT;};//0x028(RW),Ethernet MAC Remote Wake-UpFrame Filter Register
  union{UINT32 MACPMTCSR;struct ETH_MACPMTCSR_BIT MACPMTCSR_BIT;};//0x02C(RW),MAC PMT Control and Status Register
  UINT32 Reserved1[2];  //0x030(R),
  union{UINT32 MACSR;struct ETH_MACSR_BIT MACSR_BIT;};          //0x038(RW),Ethernet MAC Status Register
  union{UINT32 MACIMR;struct ETH_MACIMR_BIT MACIMR_BIT;};       //0x03C(RW),Ethernet MAC Interrupt Mask Register
  union{UINT32 MACA0HR;struct ETH_MACA0HR_BIT MACA0HR_BIT;};    //0x040(RW),MAC address0 high
  union{UINT32 MACA0LR;Type_BIT32 MACA0LR_BIT;};                //0x044(RW),MAC address0 low
  union{UINT32 MACA1HR;struct ETH_MACA123HR_BIT MACA1HR_BIT;};  //0x048(RW),MAC address1 high
  union{UINT32 MACA1LR;Type_BIT32 MACA1LR_BIT;};                //0x04C(RW),MAC address1 low
  union{UINT32 MACA2HR;struct ETH_MACA123HR_BIT MACA2HR_BIT;};  //0x050(RW),MAC address2 high
  union{UINT32 MACA2LR;Type_BIT32 MACA2LR_BIT;};                //0x054(RW),MAC address2 low
  union{UINT32 MACA3HR;struct ETH_MACA123HR_BIT MACA3HR_BIT;};  //0x058(RW),MAC address3 high
  union{UINT32 MACA3LR;Type_BIT32 MACA3LR_BIT;};                //0x05C(RW),MAC address3 low
  UINT32 Reserved2[40]; //0x060(R),
  union{UINT32 MMCCR;struct ETH_MMCCR_BIT MMCCR_BIT;};          //0x100(RW),Ethernet MMC Contol Register
  union{UINT32 MMCRIR;struct ETH_MMCRI_BIT MMCRIR_BIT;};        //0x104(RW),Ethernet MMC Receive Interrupt Register
  union{UINT32 MMCTIR;struct ETH_MMCTI_BIT MMCTIR_BIT;};        //0x108(RW),Ethernet MMC Transmit Interrupt Register
  union{UINT32 MMCRIMR;struct ETH_MMCRI_BIT MMCRIMR_BIT;};      //0x10C(RW),Ethernet MMC Receive Interrupt Mask Register
  union{UINT32 MMCTIMR;struct ETH_MMCTI_BIT MMCTIMR_BIT;};      //0x110(RW),Ethernet MMC Transmit Interrupt Mask Register
  UINT32 Reserved3[14]; //0x114(R),
  union{UINT32 MMCTGFSCCR;Type_BIT32 MMCTGFSCCR_BIT;};          //0x14C(RW),Ethernet MMC Transmitted Good Frames after Single Collision Counter Register
  union{UINT32 MMCTGFMSCCR;Type_BIT32 MMCTGFMSCCR_BIT;};        //0x150(RW),Ethernet MMC Transmitted Good Frames after More than a Single Collision Counter Register
  UINT32 Reserved4[5];  //0x154(R),
  union{UINT32 MMCTGFCR;Type_BIT32 MMCTGFCR_BIT;};              //0x168(RW),Ethernet MMC Transmitted Good Frames Counter Register
  UINT32 Reserved5[10]; //0x16C(R),
  union{UINT32 MMCRFCECR;Type_BIT32 MMCRFCECR_BIT;};            //0x194(RW),Ethernet MMC Received Frames with CRC Error Counter Register
  union{UINT32 MMCRFAECR;Type_BIT32 MMCRFAECR_BIT;};            //0x198(RW),Ethernet MMC Received Frames with Alignement Error Counter Register
  UINT32 Reserved6[10]; //0x19C(R),
  union{UINT32 MMCRGUFCR;Type_BIT32 MMCRGUFCR_BIT;};            //0x1C4(RW),Ethernet MMC Received Good Unicast Frames Counter Register
  UINT32 Reserved7[334]; //0x1C8(R),
  union{UINT32 PTPTSCR;struct ETH_PTPTSCR_BIT PTPTSCR_BIT;};    //0x700(RW),Ethernet PTP Time Stamp Contol Register
  union{UINT32 PTPSSIR;struct ETH_PTPSSIR_BIT PTPSSIR_BIT;};    //0x704(RW),Ethernet PTP Sub-Second Increment Register
  union{UINT32 PTPTSHR;Type_BIT32 PTPTSHR_BIT;};                //0x708(RW),Ethernet PTP Time Stamp High Register
  union{UINT32 PTPTSLR;struct ETH_PTPTSLR_BIT PTPTSLR_BIT;};    //0x70C(RW),Ethernet PTP Time Stamp Low Register
  union{UINT32 PTPTSHUR;Type_BIT32 PTPTSHUR_BIT;};              //0x710(RW),Ethernet PTP Time Stamp High Update Register
  union{UINT32 PTPTSLUR;struct ETH_PTPTSLUR_BIT PTPTSLUR_BIT;}; //0x714(RW),Ethernet PTP Time Stamp Low Update Register
  union{UINT32 PTPTSAR;Type_BIT32 PTPTSAR_BIT;};                //0x718(RW),Ethernet PTP Time Stamp Addend Register
  union{UINT32 PTPTTHR;Type_BIT32 PTPTTHR_BIT;};                //0x71C(RW),Ethernet PTP Target Time High Register
  union{UINT32 PTPTTLR;Type_BIT32 PTPTTLR_BIT;};                //0x720(RW),Ethernet PTP Target Time Low Register
  UINT32 Reserved8[567];//0x724(R),
  union{UINT32 DMABMR;struct ETH_DMABMR_BIT DMABMR_BIT;};       //0x1000(RW),Ethernet DMA Bus Mode Register
  union{UINT32 DMATPDR;Type_BIT32 DMATPDR_BIT;};                //0x1004(RW),Ethernet DMA Transmit Poll Demand Register
  union{UINT32 DMARPDR;Type_BIT32 DMARPDR_BIT;};                //0x1008(RW),Ethernet DMA Receive Poll Demand Register
  union{UINT32 DMARDLAR;Type_BIT32 DMARDLAR_BIT;};              //0x100C(RW),Ethernet DMA Receive Descriptor List Address Register
  union{UINT32 DMATDLAR;Type_BIT32 DMATDLAR_BIT;};              //0x1010(RW),Ethernet DMA Transmit Descriptor List Address Register
  union{UINT32 DMASR;struct ETH_DMASR_BIT DMASR_BIT;};          //0x1014(RW),Ethernet DMA Status Register
  union{UINT32 DMAOMR;struct ETH_DMAOMR_BIT DMAOMR_BIT;};       //0x1018(RW),Ethernet DMA Operation Mode Register
  union{UINT32 DMAIER;struct ETH_DMAIER_BIT DMAIER_BIT;};       //0x101C(RW),Ethernet DMA Interrupt Enable Register
  union{UINT32 DMAMFBOCR;struct ETH_DMAMFBOCR_BIT DMAMFBOCR_BIT;};//0x1020(RW),Ethernet DMA Missed Frame and Buffer Overflow Counter Register
  UINT32 Reserved9[9];   //0x1024(R),
  union{UINT32 DMACHTDR;Type_BIT32 DMACHTDR_BIT;};              //0x1048(RW),Ethernet DMA Current Host Transmit Descriptor Register
  union{UINT32 DMACHRDR;Type_BIT32 DMACHRDR_BIT;};              //0x104C(RW),Ethernet DMA Current Host Receive Descriptor Register
  union{UINT32 DMACHTBAR;Type_BIT32 DMACHTBAR_BIT;};            //0x1050(RW),Ethernet DMA Current Host Transmit Buffer Address Register
  union{UINT32 DMACHRBAR;Type_BIT32 DMACHRBAR_BIT;};            //0x1054(RW),Ethernet DMA Current Host Receive Buffer Address Register
} ETH_Type,Type_ETH;
#define PT_ETH                  ((volatile Type_ETH *)BASE_ETH)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ETH_MACCR               ETH.MACCR
#define ETH_MACFFR              ETH.MACFFR
#define ETH_MACHTHR             ETH.MACHTHR
#define ETH_MMACHTLR            ETH.MACHTLR
#define ETH_MACMIIAR            ETH.MACMIIAR
#define ETH_MACMIIDR            ETH.MACMIIDR
#define ETH_MACFCR              ETH.MACFCR
#define ETH_MACVLANTR           ETH.MACVLANTR
#define ETH_MACRWUFFR           ETH.MACRWUFFR
#define ETH_MACPMTCSR           ETH.MACPMTCSR
#define ETH_MACSR               ETH.MACSR
#define ETH_MACIMR              ETH.MACIMR
#define ETH_MACA0HR             ETH.MACA0HR
#define ETH_MACA0LR             ETH.MACA0LR
#define ETH_MACA1HR             ETH.MACA1HR
#define ETH_MACA1LR             ETH.MACA1LR
#define ETH_MACA2HR             ETH.MACA2HR
#define ETH_MACA2LR             ETH.MACA2LR
#define ETH_MACA3HR             ETH.MACA3HR
#define ETH_MACA3LR             ETH.MACA3LR
#define ETH_MMCCR               ETH.MMCCR
#define ETH_MMCRIR              ETH.MMCRIR
#define ETH_MMCTIR              ETH.MMCTIR
#define ETH_MMCRIMR             ETH.MMCRIMR
#define ETH_MMCTIMR             ETH.MMCTIMR
#define ETH_MMCTGFSCCR          ETH.MMCTGFSCCR
#define ETH_MMCTGFMSCCR         ETH.MMCTGFMSCCR
#define ETH_MMCTGFCR            ETH.MMCTGFCR
#define ETH_MMCRFCECR           ETH.MMCRFCECR
#define ETH_MMCRFAECR           ETH.MMCRFAECR
#define ETH_MMCRGUFCR           ETH.MMCRGUFCR
#define ETH_PTPTSCR             ETH.PTPTSCR
#define ETH_PTPSSIR             ETH.PTPSSIR
#define ETH_PTPTSHR             ETH.PTPTSHR
#define ETH_PTPTSLR             ETH.PTPTSLR
#define ETH_PTPTSHUR            ETH.PTPTSHUR
#define ETH_PTPTSLUR            ETH.PTPTSLUR
#define ETH_PTPTSAR             ETH.PTPTSAR
#define ETH_PTPTTHR             ETH.PTPTTHR
#define ETH_PTPTTLR             ETH.PTPTTLR
#define ETH_DMABMR              ETH.DMABMR
#define ETH_DMATPDR             ETH.DMATPDR
#define ETH_DMARPDR             ETH.DMARPDR
#define ETH_DMARDLAR            ETH.DMARDLAR
#define ETH_DMATDLAR            ETH.DMATDLAR
#define ETH_DMASR               ETH.DMASR
#define ETH_DMAOMR              ETH.DMAOMR
#define ETH_DMAIER              ETH.DMAIER
#define ETH_DMAMFBOCR           ETH.DMAMFBOCR
#define ETH_DMACHTDR            ETH.DMACHTDR
#define ETH_DMACHRDR            ETH.DMACHRDR
#define ETH_DMACHTBAR           ETH.DMACHTBAR
#define ETH_DMACHRBAR           ETH.DMACHRBAR
//==============================================================================================================================
#define RSTV_EXTI_IMR             0x00000000//0x000,bit0_19=Interrupt Mask on line 0_19
#define RSTV_EXTI_EMR             0x00000000//0x004,bit0_19=Event Mask on line 0_19
#define RSTV_EXTI_RTSR            0x00000000//0x008,bit0_19=Rising trigger event configuration bit of line 0_19
#define RSTV_EXTI_FTSR            0x00000000//0x00C,bit0_19=Falling trigger event configuration bit of line 0_19
#define RSTV_EXTI_SWIER           0x00000000//0x010,bit0_19=Software Interrupt on line 0_19
#define RSTV_EXTI_PR              0x00000000//0x014,bit0_19=Pending bit for line 0_19
struct EXTI_R_BIT//0x000=IMR,EMR,RTSR,FTSR,SWIER,PR
{
	UINT32 B0:1;          //00,
	UINT32 B1:1;          //01,
	UINT32 B2:1;          //02,
	UINT32 B3:1;          //03,
	UINT32 B4:1;          //04,
	UINT32 B5:1;          //05,
	UINT32 B6:1;          //06,
	UINT32 B7:1;          //07,
	UINT32 B8:1;          //08,
	UINT32 B9:1;          //09,
	UINT32 B10:1;         //10,
	UINT32 B11:1;         //11,
	UINT32 B12:1;         //12,
	UINT32 B13:1;         //13,
	UINT32 B14:1;         //14,
	UINT32 B15:1;         //15,
	UINT32 B16:1;         //16,
	UINT32 B17:1;         //17,
	UINT32 B18:1;         //18,
	UINT32 B19:1;         //19,
	UINT32 Reserved0:12;  //20,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define EXTI_Struct Struct_EXTI
typedef struct Struct_EXTI//0x40010400
{
  union{UINT32 IMR;struct EXTI_R_BIT IMR_BIT;};   //0x000(RW),Interrupt mask register
  union{UINT32 EMR;struct EXTI_R_BIT EMR_BIT;};   //0x004(RW),Event mask register
  union{UINT32 RTSR;struct EXTI_R_BIT RTSR_BIT;}; //0x008(RW),Rising trigger selection register 
  union{UINT32 FTSR;struct EXTI_R_BIT FTSR_BIT;}; //0x00C(RW),Falling trigger selection register
  union{UINT32 SWIER;struct EXTI_R_BIT SWIER_BIT;};//0x010(RW),Software interrupt event register
  union{UINT32 PR;struct EXTI_R_BIT PR_BIT;};     //0x014(RW),Pending register,1=selected trigger request occurred
} EXTI_Type,Type_EXTI;
#define PT_EXTI                 ((volatile Type_EXTI *)BASE_EXTI)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define EXTI_IMR                EXTI.IMR
#define EXTI_EMR                EXTI.EMR
#define EXTI_RTSR               EXTI.RTSR
#define EXTI_FTSR               EXTI.FTSR
#define EXTI_SWIER              EXTI.SWIER
#define EXTI_PR                 EXTI.PR
//==============================================================================================================================
#define RSTV_FLASH_ACR          0x00000000//0x000(0x40022000)
struct FLASH_ACR_BIT
{
	UINT32 LATENCY:3;     //00,LATENCY[2:0] bits (Latency),SYSCLK:(0,24M]=0,(24M,48M]=1;(48M,72M]=2
	UINT32 HLFCYA:1;      //03,Flash Half Cycle Access Enable
	UINT32 PRFTBE:1;      //04,Prefetch Buffer Enable
	UINT32 PRFTBS:1;      //05,Prefetch Buffer Status
	UINT32 Reserved0:26;  //06,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FLASH_KEYR         0x00000000//0x004
#define RSTV_FLASH_OPTKEYR      0x00000000//0x008
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FLASH_SR           0x00000000//0x00C
struct FLASH_SR_BIT
{
	UINT32 BSY:1;         //00,Busy
	UINT32 Reserved0:1;   //01,
	UINT32 PGERR:1;       //02,Programming Error
	UINT32 Reserved1:1;   //03,
	UINT32 WRPRTERR:1;    //04,Write Protection Error
	UINT32 EOP:1;         //05,End of operation
	UINT32 Reserved2:26;  //06,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FLASH_CR           0x00000000//0x010
struct FLASH_CR_BIT
{
	UINT32 PG:1;          //00,Programming
	UINT32 PER:1;         //01,Page Erase
	UINT32 MER:1;         //02,Mass Erase
	UINT32 Reserved0:1;   //03,
	UINT32 OPTPG:1;       //04,Option Byte Programming
	UINT32 OPTER:1;       //05,Option Byte Erase
	UINT32 STRT:1;        //06,Start
	UINT32 LOCK:1;        //07,Lock
	UINT32 Reserved1:1;   //08,
	UINT32 OPTWRE:1;      //09,Option Bytes Write Enable
	UINT32 ERRIE:1;       //10,Error Interrupt Enable
	UINT32 Reserved2:1;   //11,
	UINT32 EOPIE:1;       //12,End of operation interrupt enable
	UINT32 Reserved3:19;  //13,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FLASH_AR           0x00000000//0x014,Flash Address
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FLASH_OBR          0x00000000//0x01C
struct FLASH_OBR_BIT
{
	UINT32 OPTERR:1;      //00,Option Byte Error
	UINT32 RDPRT:1;       //01,Read protection
	UINT32 USER:8;        //02,User Option Bytes(bit2=WDG_SW,bit3=nRST_STOP,bit4=nRST_STDBY,bit5=BFB2)
	UINT32 Reserved0:22;  //10,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FLASH_WRP          0x00000000//0x020,Write Protect
//------------------------------------------------------------------------------------------------------------------------------
#define FLASH_Struct Struct_FLASH
typedef struct Struct_FLASH//0x40020000
{
  union{UINT32 ACR;struct FLASH_ACR_BIT ACR_BIT;};      //0x000(RW),
  union{UINT32 KEYR;Type_UINT32 KEYR_BIT;};              //0x004(RW),
  union{UINT32 OPTKEYR;Type_UINT32 OPTKEYR_BIT;};        //0x008(RW),
  union{UINT32 SR;struct FLASH_SR_BIT SR_BIT;};         //0x00C(RW),
  union{UINT32 CR;struct FLASH_CR_BIT CR_BIT;};         //0x010(RW),
  union{UINT32 AR;Type_BIT32 AR_BIT;};                  //0x014(RW),
  UINT32 Reserved0[1];//0x018(R),
  union{UINT32 OBR;struct FLASH_OBR_BIT OBR_BIT;};      //0x01C(RW),
  union{UINT32 WRP;Type_BIT32 WRP_BIT;};    //0x020(RW),
#if IsDensity(XL)
  UINT32 Reserved1[8];//0x024(R), 
  union{UINT32 KEYR2;Type_BIT32 KEYR2_BIT;};//0x028(RW),
  UINT32 Reserved2[1];//0x02C(R),   
  union{UINT32 SR2;struct FLASH_SR_BIT SR2_BIT;};//0x030(R),
  union{UINT32 CR2;struct FLASH_CR_BIT CR2_BIT;};//0x034(RW),
  union{UINT32 AR2;Type_BIT32 AR2_BIT;};//0x038(RW), 
#endif
} FLASH_Type,Type_FLASH;
#define PT_FLASH                ((volatile Type_FLASH *)BASE_FLASHR)
//------------------------------------------------------------------------------------------------------------------------------
#define FLASH_ACR               FLASH.ACR
#define FLASH_KEYR              FLASH.KEYR
#define FLASH_OPTKEYR           FLASH.OPTKEYR
#define FLASH_SR                FLASH.SR
#define FLASH_CR                FLASH.CR
#define FLASH_AR                FLASH.AR
#define FLASH_OBR               FLASH.OBR
#define FLASH_WRP               FLASH.WRP
#if IsDensity(XL)
#define FLASH_KEYR2             FLASH.KEYR2
#define FLASH_SR2               FLASH.SR2
#define FLASH_CR2               FLASH.CR2
#define FLASH_AR2               FLASH.AR2
#endif
//==============================================================================================================================
#define RSTV_OB_RDP             0x00000000//0x000
#define RSTV_OB_USER            0x00000000//0x002
#define RSTV_OB_DATA0           0x00000000//0x004
#define RSTV_OB_DATA1           0x00000000//0x006
#define RSTV_OB_WRP0            0x00000000//0x008
#define RSTV_OB_WRP1            0x00000000//0x00A
#define RSTV_OB_WRP2            0x00000000//0x00C
#define RSTV_OB_WRP3            0x00000000//0x00E
struct OB_REG_BIT
{
	UINT32 V:8;           //00,option byte
	UINT32 nV:8;          //08,complemented option byte
};
//------------------------------------------------------------------------------------------------------------------------------
#define OB_Struct Struct_OB
typedef struct Struct_OB//0x1FFFF800
{
  union{UINT16 RDP;struct OB_REG_BIT RDP_BIT;};         //0x000(RW),Read protection option byte
  union{UINT16 USER;struct OB_REG_BIT USER_BIT;};       //0x002(RW),User option byte
  union{UINT16 Data0[2];struct OB_REG_BIT Data_BIT[2];};//0x004(RW),User data storage option byte
  union{UINT16 WRP[4];struct OB_REG_BIT WRP_BIT[4];};   //0x008(RW),memory write protection option bytes
} OB_Type,Type_OB;
#define PT_OB                   ((volatile Type_OB *)BASE_OB)
//------------------------------------------------------------------------------------------------------------------------------
#define OB_RDP                  OB.RDP
#define OB_USER                 OB.USER
#define OB_Data(i)              OB.Data[i]//i=0_1
#define OB_WRP(i)               OB.WRP[i]//i=0_3
//==============================================================================================================================
#define RSTV_FSMC_BCR1          0x00000081//0x000
#define RSTV_FSMC_BCR2          0x00000081//0x008
#define RSTV_FSMC_BCR3          0x00000081//0x010
#define RSTV_FSMC_BCR4          0x00000081//0x018
struct FSMC_BCR_BIT//0x000=BCR1,0x008=BCR2,0x010=BCR3,0x018=BCR4
{
	UINT32 MBKEN:1;       //00,Memory bank enable bit
	UINT32 MUXEN:1;       //01,Address/data multiplexing enable bit
	UINT32 MTYP:2;        //02,MTYP[1:0] bits (Memory type):0=SRAM,1=PSRAM/CRAM,2=NOR FLASH,3=Reserve
	UINT32 MWID:2;        //04,MWID[1:0] bits (Memory data bus width):0=8bit,1=16bit
	UINT32 FACCEN:1;      //06,Flash access enable
	UINT32 Reserved0:1;   //07,
	UINT32 BURSTEN:1;     //08,Burst enable bit
	UINT32 WAITPOL:1;     //09,Wait signal polarity bit:
	UINT32 WRAPMOD:1;     //10,Wrapped burst mode support
	UINT32 WAITCFG:1;     //11,Wait timing configuration
	UINT32 WREN:1;        //12,Write enable bit
	UINT32 WAITEN:1;      //13,Wait enable bit
	UINT32 EXTMOD:1;      //14,Extended mode enable
	UINT32 ASYNCWAIT:1;   //15,Asynchronous wait
	UINT32 Reserved1:3;   //16,
	UINT32 CBURSTRW:1;    //19,Write burst enable
	UINT32 Reserved2:12;  //20,
};
#define FSMC_BCR_MODE_1         0x00000081//SRAM/PSRAM(CRAM)
#define FSMC_BCR_MODE_2         0x000000C9//NOR FLASH
#define FSMC_BCR_MODE_B         0x000040C9//NOR FLASH
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FSMC_BTR1          0x00000000//0x004
#define RSTV_FSMC_BTR2          0x00000000//0x00C
#define RSTV_FSMC_BTR3          0x00000000//0x014
#define RSTV_FSMC_BTR4          0x00000000//0x01C
#define RSTV_FSMC_BTR           0x00000000
struct FSMC_BTR_BIT//0x004=BTR1,0x00C=BTR2,0x014=BTR3,0x01C=BTR4
{
	UINT32 ADDSET:4;      //00,ADDSET[3:0] bits (Address setup phase duration):ADDSET+1 HCLK
	UINT32 ADDHLD:4;      //04,ADDHLD[3:0] bits (Address-hold phase duration):0_15=1_16 HCLK cycles
	UINT32 DATAST:8;      //08,DATAST [3:0] bits (Data-phase duration):DATAST+1 HCLK for write,DATAST+3 HCLK for read. min=1
	UINT32 BUSTURN:4;     //16,BUSTURN[3:0] bits (Bus turnaround phase duration):BUSTURN HCLK cycles
  UINT32 CLKDIV:4;      //20,CLKDIV[3:0] bits (Clock divide ratio):0=reserve,1_15=2_16 HCLK cycles
	UINT32 DATLAT:4;      //24,DATLA[3:0] bits (Data latency):DATLAT+2 HCLK
	UINT32 ACCMOD:2;      //28,ACCMOD[1:0] bits (Access mode):0=A,1=B,2=C,3=D ;Write=0
	UINT32 Reserved0:2;   //30, =0
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FSMC_BWTR1           0x00000000//0x104
#define RSTV_FSMC_BWTR2           0x00000000//0x10C
#define RSTV_FSMC_BWTR3           0x00000000//0x114
#define RSTV_FSMC_BWTR4           0x00000000//0x11C
#define RSTV_FSMC_BWTR            0x00000000
struct FSMC_BWTR_BIT//0x104=BWTR1,0x10C=BWTR2,0x114=BWTR3,0x11C=BWTR4，<LDY>
{
	UINT32 ADDSET:4;      //00,ADDSET[3:0] bits (Address setup phase duration),ADDSET+1 HCLK
	UINT32 ADDHLD:4;      //04,ADDHLD[3:0] bits (Address-hold phase duration):don't care
	UINT32 DATAST:8;      //08,DATAST [3:0] bits (Data-phase duration):DATAST+1 HCLK for write,DATAST+3 HCLK for read. min=1
	UINT32 BUSTURN:4;     //16,BUSTURN[3:0] bits (Bus turnaround phase duration)
  UINT32 Reserved0:8;   //20,:don't care
	UINT32 ACCMOD:2;      //28,ACCMOD[1:0] bits (Access mode):=0
	UINT32 Reserved1:2;   //30, =0
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FSMC_PCR2            0x00000018//0xA0000060
#define RSTV_FSMC_PCR3            0x00000018//0xA0000080
#define RSTV_FSMC_PCR4            0x00000018//0xA00000A0
#define RSTV_FSMC_PCR             0x00000018
struct FSMC_PCR_BIT//0xA0000060=PCR2,0xA0000080=PCR3,0xA00000A0=PCR4
{
	UINT32 Reserved0:1;   //00,
	UINT32 PWAITEN:1;     //01,Wait feature enable bit
	UINT32 PBKEN:1;       //02,PC Card/NAND Flash memory bank enable bit
	UINT32 PTYP:1;        //03,Memory type:0=PC Card,CompactFlash,CF+ or PCMCIA;1=NAND flash
	UINT32 PWID:2;        //04,PWID[1:0] bits (NAND Flash databus width):0=8bits,1=16bits,2_3=reserved
  UINT32 ECCEN:1;       //06,ECC computation logic enable bit
	UINT32 Reserved1:2;   //07,
	UINT32 TCLR:4;        //09,TCLR[3:0] bits (CLE to RE delay)
	UINT32 TAR:4;         //13,TAR[3:0] bits (ALE to RE delay)
	UINT32 ECCPS:3;       //17,ECCPS[1:0] bits (ECC page size)
	UINT32 Reserved2:12;  //20,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FSMC_SR2             0x00000040//0xA0000064
#define RSTV_FSMC_SR3             0x00000040//0xA0000084
#define RSTV_FSMC_SR4             0x00000040//0xA00000A4
#define RSTV_FSMC_SR              0x00000040
struct FSMC_SR_BIT//0xA0000064=SR2,0xA0000084=SR3,0xA00000A4=SR4
{
	UINT32 IRS:1;         //00,Interrupt Rising Edge status
	UINT32 ILS:1;         //01,Interrupt Level status
	UINT32 IFS:1;         //02,Interrupt Falling Edge status
	UINT32 IREN:1;        //03,Interrupt Rising Edge detection Enable bit
	UINT32 ILEN:1;        //04,Interrupt Level detection Enable bit
  UINT32 IFEN:1;        //05,Interrupt Falling Edge detection Enable bit
	UINT32 FEMPT:1;       //06,FIFO empty
	UINT32 Reserved2:25;  //07,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FSMC_PMEM2           0x00000000//0xA0000068,Common memory 2
#define RSTV_FSMC_PMEM3           0x00000000//0xA0000088,Common memory 3
#define RSTV_FSMC_PMEM4           0x00000000//0xA00000A8,Common memory 4
#define RSTV_FSMC_PMEM            0x00000000
#define RSTV_FSMC_PATT2           0x00000000//0xA000006C,Attribute memory 2
#define RSTV_FSMC_PATT3           0x00000000//0xA000008C,Attribute memory 3
#define RSTV_FSMC_PATT4           0x00000000//0xA00000AC,Attribute memory 4
#define RSTV_FSMC_PATT            0x00000000
#define RSTV_FSMC_PIO4            0x00000000//0xA00000B0,I/O 4
struct FSMC_SWHH_BIT//0xA0000068=PMEM2,0xA0000088=PMEM3,0xA00000A8=PMEM4,0xA000006C=PATT2,0xA000008C=PATT3,0xA00000AC=PATT4,0xA00000B0=PIO4
{
	UINT32 SET:8;         //00,MEMSET2[7:0] bits ( setup time)
	UINT32 WAIT:8;        //08,MEMWAIT2[7:0] bits (Common memory 2 wait time)
	UINT32 HOLD:8;        //16,MEMHOLD2[7:0] bits (Common memory 2 hold time)
	UINT32 HIZ:8;         //24,MEMHIZ2[7:0] bits (Common memory 2 databus HiZ time)
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_FSMC_ECCR2           0x00000000//0xA0000074,ECC result 2
#define RSTV_FSMC_ECCR3           0x00000000//0xA0000094,ECC result 3
//------------------------------------------------------------------------------------------------------------------------------
typedef struct FSMCCH//0x000=CH[0],Bank1
{
  union{UINT32 BCR;struct FSMC_BCR_BIT BCR_BIT;}; 
  union{UINT32 BTR;struct FSMC_BTR_BIT BTR_BIT;};  
} FSMCCH_Type,Type_FSMCCH;
//------------------------------------------------------------------------------------------------------------------------------
typedef struct FSMCPC//0x060=PC[0],Bank2
{
  union{UINT32 PCR;struct FSMC_PCR_BIT PCR_BIT;};//0x000(RW),
  union{UINT32 SR;struct FSMC_SR_BIT SR_BIT;};//0x004(RW),
  union{UINT32 PMEM;struct FSMC_SWHH_BIT PMEM_BIT;};//0x008(RW),Common memory space timing register
  union{UINT32 PATT;struct FSMC_SWHH_BIT PATT_BIT;};//0x00C(RW),Attribute memory space timing register
  union{UINT32 PIO4;struct FSMC_SWHH_BIT PIO4_BIT;};//0x010(RW),only for bank4,PC Card  I/O space timing register   
  union{UINT32 ECCR;Type_BIT32 ECCR_BIT;};//0x014(RW), 
	UINT32 Reserved0[2];//0x018(R),
} FSMCPC_Type,Type_FSMCPC;  
//------------------------------------------------------------------------------------------------------------------------------
typedef struct FSMCBW//0x100=BW[0],0x108=BW[1],0x110=BW[2],0x118=BW[3],Bank1E
{
	UINT32 Reserved0[1];
  union{UINT32 BWTR;struct FSMC_BWTR_BIT BWTR_BIT;};
} FSMCBW_Type,Type_FSMCBW;
//------------------------------------------------------------------------------------------------------------------------------
#define FSMC_Struct Struct_FSMC
typedef struct Struct_FSMC//0xA0000000
{
	Type_FSMCCH CH[4];    //0xA0000000,Bank1
	UINT32 Reserved0[16]; //0xA0000020,
	Type_FSMCPC PC[3];    //0xA0000060,Bank2,Bank3,Bank4
	UINT32 Reserved1[16]; //0xA00000C0,
	Type_FSMCBW BW[4];    //0xA0000100,Bank1E
} FSMC_Type,Type_FSMC;
#define PT_FSMC                 ((volatile Type_FSMC *)BASE_FSMC)
//------------------------------------------------------------------------------------------------------------------------------
#define FSMC_BCR(i)             FSMC.CH[i].BCR//i=0_3
#define FSMC_BTR(i)             FSMC.CH[i].BTR//i=0_3
#define FSMC_PCR(i)             FSMC.PC[i].PCR//i=0_2
#define FSMC_SR(i)              FSMC.PC[i].SR//i=0_2
#define FSMC_PMEM(i)            FSMC.PC[i].PMEM//i=0_2
#define FSMC_PATT(i)            FSMC.PC[i].PATT//i=0_2
#define FSMC_PIO4(i)            FSMC.PC[i].PIO4//i=0_2
#define FSMC_ECCR(i)            FSMC.PC[i].ECCR//i=0_2
#define FSMC_BWTR(i)            FSMC.BW[i].BWTR//i=0_3
//==============================================================================================================================
typedef struct Struct_LCD
{
  #if LCD_RS
  UINT16 Reserved0;
  #endif
  UINT16 REG;
  UINT16 RAM;
} LCD_Type,Type_LCD;
#define PT_LCD                  ((volatile Type_LCD *)BASE_LCD)
#define LCD_REG                 LCD.REG
#define LCD_RAM                 LCD.RAM
//==============================================================================================================================
#define RSTV_GPIO_CRL           0x44444444//0x000
#define RSTV_GPIO_CRH           0x44444444//0x004
//MODE:0=Input,1=Out_10M,2=Out_2M,3=Out_50M
//CNF:Input(0=Analog,1=Floating,2=PU/PD,3=Reserved),Output(0=PushPull,1=OpenDrain,2=ALTF_PushPull,3=ALTF_OpenDrain)
struct GPIO_CR_BIT//CRL,CRH
{
  UINT32 MODE0:2;       //00,MODE0[1:0] bits (Port x mode bits, pin 0)
	UINT32 CNF0:2;        //02,CNF0[1:0] bits (Port x configuration bits, pin 0)
  UINT32 MODE1:2;       //04,MODE1[1:0] bits (Port x mode bits, pin 1)
	UINT32 CNF1:2;        //06,CNF1[1:0] bits (Port x configuration bits, pin 1)
  UINT32 MODE2:2;       //08,MODE2[1:0] bits (Port x mode bits, pin 2)
	UINT32 CNF2:2;        //10,CNF2[1:0] bits (Port x configuration bits, pin 2)
  UINT32 MODE3:2;       //12,MODE3[1:0] bits (Port x mode bits, pin 3)
	UINT32 CNF3:2;        //14,CNF3[1:0] bits (Port x configuration bits, pin 3)
  UINT32 MODE4:2;       //16,MODE4[1:0] bits (Port x mode bits, pin 4)
	UINT32 CNF4:2;        //18,CNF4[1:0] bits (Port x configuration bits, pin 4)
  UINT32 MODE5:2;       //20,MODE5[1:0] bits (Port x mode bits, pin 5)
	UINT32 CNF5:2;        //22,CNF5[1:0] bits (Port x configuration bits, pin 5)
  UINT32 MODE6:2;       //24,MODE6[1:0] bits (Port x mode bits, pin 6)
	UINT32 CNF6:2;        //26,CNF6[1:0] bits (Port x configuration bits, pin 6)
  UINT32 MODE7:2;       //28,MODE7[1:0] bits (Port x mode bits, pin 7)
	UINT32 CNF7:2;        //30,CNF7[1:0] bits (Port x configuration bits, pin 7)
};

#define GPIO_MI_Analog          0
#define GPIO_MI_Floating        4
#define GPIO_MI_PUPD            8
#define GPIO_MO_10M_PU          1
#define GPIO_MO_10M_OD          5
#define GPIO_MO_10M_AFPU        9
#define GPIO_MO_10M_AFOD        13
#define GPIO_MO_2M_PU           2
#define GPIO_MO_2M_OD           6
#define GPIO_MO_2M_AFPU         10
#define GPIO_MO_2M_AFOD         14
#define GPIO_MO_50M_PU          3
#define GPIO_MO_50M_OD          7
#define GPIO_MO_50M_AFPU        11
#define GPIO_MO_50M_AFOD        15
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_GPIO_IDR           0x00000000//0x008
#define RSTV_GPIO_ODR           0x00000000//0x00C
struct GPIO_IO_BIT//IDR,ODR
{
  UINT32 B0:1;          //00,Port input/output data, bit 0,1=output
  UINT32 B1:1;          //01,Port input/output data, bit 1
  UINT32 B2:1;          //02,Port input/output data, bit 2
  UINT32 B3:1;          //03,Port input/output data, bit 3
  UINT32 B4:1;          //04,Port input/output data, bit 4
  UINT32 B5:1;          //05,Port input/output data, bit 5
  UINT32 B6:1;          //06,Port input/output data, bit 6
  UINT32 B7:1;          //07,Port input/output data, bit 7
  UINT32 B8:1;          //08,Port input/output data, bit 8
  UINT32 B9:1;          //09,Port input/output data, bit 9
  UINT32 B10:1;         //10,Port input/output data, bit 10
  UINT32 B11:1;         //11,Port input/output data, bit 11
  UINT32 B12:1;         //12,Port input/output data, bit 12
  UINT32 B13:1;         //13,Port input/output data, bit 13
  UINT32 B14:1;         //14,Port input/output data, bit 14
  UINT32 B15:1;         //15,Port input/output data, bit 15
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_GPIO_BSRR          0x00000000//0x010
struct GPIO_BSRR_BIT
{
  UINT32 BS:16;         //00,
  UINT32 BR:16;         //16,
};
#define GPIO_BSRR_BS(i)         GPIO[i].BSRR_BIT.BS
#define GPIO_BSRR_BR(i)         GPIO[i].BSRR_BIT.BR
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_GPIO_BRR           0x00000000//0x014
struct GPIO_BRR_BIT
{
  UINT32 BR:16;         //00,
  UINT32 Reserved0:16;  //16,
};
#define GPIO_BRR_BR(i)          GPIO[i].BRR_BIT.BR
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_GPIO_LCKR          0x00000000//0x018
struct GPIO_LCKR_BIT
{
  UINT32 LCK:16;        //00,Lock Port Config
	UINT32 LCKK:1;        //16,Enable Bit0_15
  UINT32 Reserved0:15;  //17,
};
#define GPIO_LCKR_CLK(i)        GPIO[i].LCKR_BIT.CLK
#define GPIO_LCKR_LCKK(i)       GPIO[i].LCKR_BIT.LCKK
//------------------------------------------------------------------------------------------------------------------------------
#define GPIO_Struct Struct_GPIO
typedef struct Struct_GPIO//GPIOA=0x40010800,Size=0x0400
{
  union{UINT32 CRL;struct GPIO_CR_BIT CRL_BIT;};//0x000(RW),Port configuration register low 
  union{UINT32 CRH;struct GPIO_CR_BIT CRH_BIT;};//0x004(RW),Port configuration register high 
  union{UINT32 IDR;struct GPIO_IO_BIT IDR_BIT;};//0x008(RW),Port input data register 
  union{UINT32 ODR;struct GPIO_IO_BIT ODR_BIT;};//0x00C(RW),Port output data register 
  union{UINT32 BSRR;struct GPIO_BSRR_BIT BSRR_BIT;};//0x010(RW),Port bit set/reset register
  union{UINT32 BRR;struct GPIO_BRR_BIT BRR_BIT;};//0x014(RW),Port bit reset register 
  union{UINT32 LCKR;struct GPIO_LCKR_BIT LCKR_BIT;};//0x018(RW),Port configuration lock register
	UINT32 Reserved0[249];//0x01C(R),
} GPIO_Type,Type_GPIO;
#define PT_GPIOA                ((volatile Type_GPIO *)BASE_GPIOA)
#define PT_GPIOB                ((volatile Type_GPIO *)BASE_GPIOB)
#define PT_GPIOC                ((volatile Type_GPIO *)BASE_GPIOC)
#define PT_GPIOD                ((volatile Type_GPIO *)BASE_GPIOD)
#define PT_GPIOE                ((volatile Type_GPIO *)BASE_GPIOE)
#define PT_GPIOF                ((volatile Type_GPIO *)BASE_GPIOF)
#define PT_GPIOG                ((volatile Type_GPIO *)BASE_GPIOG)
#define PT_GPIO(i)              ((volatile Type_GPIO *)BASE_GPIO(i))//i=0_6
#define GPIOA                   GPIO[0]
#define GPIOB                   GPIO[1]
#define GPIOC                   GPIO[2]
#define GPIOD                   GPIO[3]
#define GPIOE                   GPIO[4]
#define GPIOF                   GPIO[5]
#define GPIOG                   GPIO[6]
//------------------------------------------------------------------------------------------------------------------------------
#define GPIO_CRL(i)             GPIO[i].CRL//i=0_6
#define GPIO_CRH(i)             GPIO[i].CRH//i=0_6
#define GPIO_IDR(i)             GPIO[i].IDR//i=0_6
#define GPIO_ODR(i)             GPIO[i].ODR//i=0_6
#define GPIO_BSRR(i)            GPIO[i].BSRR//i=0_6
#define GPIO_BRR(i)             GPIO[i].BRR//i=0_6
#define GPIO_LCKR(i)            GPIO[i].LCKR//i=0_6
//==============================================================================================================================
#define RSTV_AFIO_EVCR          0x00000000//0x000
struct AFIO_EVCR_BIT
{
  UINT32 PIN:4;         //00,PIN[3:0] bits (Pin selection)
	UINT32 PORT:3;        //04,PORT[2:0] bits (Port selection)
	UINT32 EVOE:1;        //07,Event Output Enable
  UINT32 Reserved0:24;  //08,
};
#define AFIO_EVCR_PIN        AFIO.EVCR_BIT.PIN
#define AFIO_EVCR_PORT       AFIO.EVCR_BIT.PORT
#define AFIO_EVCR_EVOE       AFIO.EVCR_BIT.EVOE

#define AFIO_EVCR_PORT_PA               0//Port A selected
#define AFIO_EVCR_PORT_PB               1//Port B selected
#define AFIO_EVCR_PORT_PC               2//Port C selected
#define AFIO_EVCR_PORT_PD               3//Port D selected
#define AFIO_EVCR_PORT_PE               4//Port E selected
//------------------------------------------------------------------------------------------------------------------------------
//SPI2=fix at NSS/SCK/MISO/MOSI=PB12/PB13/PB14/PB15
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_AFIO_MAPR            0x00000000//0x004
struct AFIO_MAPR_BIT
{
  UINT32 SPI1:1;        //00,SPI1 remapping,NSS/SCK/MISO/MOSI=: 0=PA4/PA5/PA6/PA7,1=PA15/PB3/PB4/PB5
	UINT32 I2C1:1;        //01,I2C1 remapping,SCL/SDA=: 0=PB6/PB7,1=PB8/PB9
	UINT32 USART1:1;      //02,USART1 remapping,TXRX=: 0=PA9/PA10,1=PB6/PB7
  UINT32 USART2:1;      //03,USART2 remapping,TXRX=: 0=PA2/PA3,1=PD5/PD6
	UINT32 USART3:2;      //04,USART3_REMAP[1:0] bits (USART3 remapping),TXRX=: 0=PB10/PB11,1=PC10/PC11,2=no used,3=PD8/PD9
	UINT32 TIM1:2;        //06,TIM1_REMAP[1:0] bits
	UINT32 TIM2:2;        //08,TIM2_REMAP[1:0] bits:0=(PA0_3),1=(PA15,PB3,PA2_3),2=(PA0_1,PB10_11),3=(PA15,PB3,PB10_11)
	UINT32 TIM3:2;        //10,TIM3_REMAP[1:0] bits:0=No remap(PA6,PA7,PB0,PB1),2=partial(PB4,PB5,PB0,PB1),3=full(PC6_9)
  UINT32 TIM4:1;        //12,TIM4_REMAP bit (TIM4 remapping,0=T4C1_4=PB6_9,1=T4C1_4=PD12_15)
	UINT32 CAN1_AL:2;     //13,CAN_REMAP[1:0] bits (CAN Alternate function remapping)RXTX:0=(PA11,PA12),2=(PB8,PB9),3=(PD0,PD1)
	UINT32 PD01:1;        //15,Port D0/Port D1 mapping on OSC_IN/OSC_OUT:1=Enable
	UINT32 TIM5CH4:1;     //16,TIM5 Channel4 Internal Remap
	UINT32 ADC1ETRGINJ:1; //17,ADC 1 External Trigger Injected Conversion remapping
	UINT32 ADC1ETRGREG:1; //18,ADC 1 External Trigger Regular Conversion remapping
	UINT32 ADC2ETRGINJ:1; //19,ADC 2 External Trigger Injected Conversion remapping
	UINT32 ADC2ETRGREG:1; //20,ADC 2 External Trigger Regular Conversion remapping
#if IsDensity(CL)
	UINT32 ETH:1;         //21,SPI3_REMAP bit (Ethernet MAC I/O remapping)
	UINT32 CAN2_AL:1;     //22,CAN2_REMAP bit (CAN2 I/O remapping)
	UINT32 MII:1;         //23,MII_RMII_SEL bit (Ethernet MII or RMII selection)
#else
	UINT32 Reserved0:3;
#endif
  UINT32 SWJCFG:3;      //24,SWJCFG[2:0] bits (Serial Wire JTAG configuration):0=FULL SWJ(reset),1=FULL SWJ but no NJRST,2=JTAG disable and SW enable,4=JTAG and SW disable
	UINT32 Reserved1:1;   //27,
#if IsDensity(CL)
  UINT32 SPI3:1;        //28,SPI3_REMAP bit,(NSS,CK,MISO,MOSI):0=(PA15,PB3,PB4,PB5),1=(PA4,PC10,PC11,PC12)
  UINT32 TIM2ITR1:1;    //29,TIM2ITR1_IREMAP bit (TIM2 internal trigger 1 remapping)
	UINT32 PTPPPS:1;      //30,PTP_PPS_REMAP bit (Ethernet PTP PPS remapping)
	UINT32 Reserved2:1;   //31,
#else
  UINT32 Reserved2:4;   //28,
#endif
};
#define AFIO_MAPR_USART3_NOREMAP        0//No remap (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14)
#define AFIO_MAPR_USART3_PARTIALREMAP   1//Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14)
#define AFIO_MAPR_USART3_FULLREMAP      3//Full remap (TX/PD8, RX/PD9, CK/PD10, CTS/PD11, RTS/PD12)
#define AFIO_MAPR_TIM1_NOREMAP          0//No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
#define AFIO_MAPR_TIM1_PARTIALREMAP     2//Partial remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PA6, CH1N/PA7, CH2N/PB0, CH3N/PB1)
#define AFIO_MAPR_TIM1_FULLREMAP        3//Full remap (ETR/PE7, CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8, CH2N/PE10, CH3N/PE12)
#define AFIO_MAPR_TIM2_NOREMAP          0//No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
#define AFIO_MAPR_TIM2_PARTIALREMAP1    1//Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2, CH4/PA3)
#define AFIO_MAPR_TIM2_PARTIALREMAP2    2//Partial remap (CH1/ETR/PA0, CH2/PA1, CH3/PB10, CH4/PB11)
#define AFIO_MAPR_TIM2_FULLREMAP        3//Full remap (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)
#define AFIO_MAPR_TIM3_NOREMAP          0//No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
#define AFIO_MAPR_TIM3_PARTIALREMAP     2//Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
#define AFIO_MAPR_TIM3_FULLREMAP        3//Full remap (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)
#define AFIO_MAPR_CAN_REMAP1            0//CANRX mapped to PA11, CANTX mapped to PA12
#define AFIO_MAPR_CAN_REMAP2            2//CANRX mapped to PB8, CANTX mapped to PB9
#define AFIO_MAPR_CAN_REMAP3            3//CANRX mapped to PD0, CANTX mapped to PD1
#define AFIO_MAPR_SWJCFG_RESET          0//Full SWJ (JTAG-DP + SW-DP) : Reset State
#define AFIO_MAPR_SWJCFG_NOJNTRST       1//Full SWJ (JTAG-DP + SW-DP) but without JNTRST
#define AFIO_MAPR_SWJCFG_JTAGDISABLE    2//JTAG-DP Disabled and SW-DP Enabled
#define AFIO_MAPR_SWJCFG_DISABLE        4//JTAG-DP Disabled and SW-DP Disabled
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_AFIO_EXTICR1       0x00000000//0x008
#define RSTV_AFIO_EXTICR2       0x00000000//0x00C
#define RSTV_AFIO_EXTICR3       0x00000000//0x010
#define RSTV_AFIO_EXTICR4       0x00000000//0x014
struct AFIO_EXTICR_BIT//0x008=EXTICR1,0x00C=EXTICR2,0x010=EXTICR3,0x014=EXTICR4
{
  UINT32 EXTI0:4;       //00,EXTI 0 configuration,EXTICR1=0_6=PA[0]_PG[0]
  UINT32 EXTI1:4;       //00,EXTI 1 configuration,EXTICR1=0_6=PA[1]_PG[1]
  UINT32 EXTI2:4;       //00,EXTI 2 configuration,EXTICR1=0_6=PA[2]_PG[2]
  UINT32 EXTI3:4;       //00,EXTI 3 configuration,EXTICR1=0_6=PA[3]_PG[3]
	UINT32 Reserved0:16;  //16,
};

#define AFIO_EXTICR_EXTI_PA     0//PA pin
#define AFIO_EXTICR_EXTI_PB     1//PB pin
#define AFIO_EXTICR_EXTI_PC     2//PC pin
#define AFIO_EXTICR_EXTI_PD     3//PD pin
#define AFIO_EXTICR_EXTI_PE     4//PE pin
#define AFIO_EXTICR_EXTI_PF     5//PF pin
#define AFIO_EXTICR_EXTI_PG     6//PG pin
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_AFIO_MAPR2           0x00000000//0x01C
struct AFIO_MAPR2_BIT
{
#if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 TIM15:1;       //00,TIM15 remapping
  UINT32 TIM16:1;       //01,TIM16 remapping
  UINT32 EXT17:1;       //02,TIM17 remapping
  UINT32 CEC:1;         //03,CEC remapping
	UINT32 TIM1_DMA:1;    //04,TIM1_DMA remapping
#else
	UINT32 Reserved0:5;
#endif
#if IsDensity(XL)
	UINT32 TIM9:1;        //05,TIM9 remapping
	UINT32 TIM10:1;       //06,TIM10 remapping
	UINT32 TIM11:1;       //07,TIM11 remapping
#else
  UINT32 Reserved1:3;   //05,
#endif
#if IsDensity(XL)|| IsDensity(HD_VL)
	UINT32 TIM13:1;       //08,TIM13 remapping
	UINT32 TIM14:1;       //09,TIM14 remapping
	UINT32 FSMCNADV:1;    //10,FSMC NADV remapping
#else
  UINT32 Reserved2:3;   //08,
#endif
  UINT32 TIM67DACDMA:1; //11,TIM6/TIM7 and DAC DMA remapping
	UINT32 TIM12:1;       //12,TIM12 remapping
	UINT32 MISC:1;        //13,Miscellaneous remapping
	UINT32 Reserved3:18;  //14,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define AFIO_Struct Struct_AFIO
typedef struct Struct_AFIO//0x40020000
{
  union{UINT32 EVCR;struct AFIO_EVCR_BIT EVCR_BIT;};//0x000(RW),
  union{UINT32 MAPR;struct AFIO_MAPR_BIT MAPR_BIT;};//0x004(RW),
  union{UINT32 EXTICR[4];struct AFIO_EXTICR_BIT EXTICR_BIT[4];struct UINT32_B4P_BIT EXTICR_B4P[4];};//0x008(RW),
  UINT32 Reserved0[1];  //0x018(R),
  union{UINT32 MAPR2;struct AFIO_MAPR2_BIT MAPR2_BIT;};         //0x01C(RW),
} AFIO_Type,Type_AFIO;
#define PT_AFIO                 ((volatile Type_AFIO *)BASE_AFIO)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define AFIO_EVCR               AFIO.EVCR
#define AFIO_MAPR               AFIO.MAPR
#define AFIO_EXTICR(i)          AFIO.EXTICR[i]//i=0_3
#define AFIO_MAPR2              AFIO.MAPR2
//==============================================================================================================================
#define RSTV_I2C_CR1            0x00000000//0x000
struct I2C_CR1_BIT
{
	UINT32 PE:1;          //00,Peripheral Enable:1=Enable
	UINT32 SMBUS:1;       //01,SMBus Mode:0=I2C,1=SMBus
	UINT32 Reserved0:1;   //02,
	UINT32 SMBTYPE:1;     //03,SMBus Type:0=Device,1=Host
	UINT32 ENARP:1;       //04,ARP Enable:1=Enable
	UINT32 ENPEC:1;       //05,PEC Enable:1=Enable
	UINT32 ENGC:1;        //06,General Call Enable:1=Enable
	UINT32 NOSTRETCH:1;   //07,Clock Stretching Disable (Slave mode):0=Enable,1=Disable
	UINT32 START:1;       //08,Start Generation,Master:0=No Start,1=Repeat Start;Slave:0=No Start,1=Start  when the bus is free
	UINT32 STOP:1;        //09,Stop Generation,Master:0=No stop,1=Stop after current;Slave:0=No stop,1=Release the SCL and SDA
	UINT32 ACK:1;         //10,Acknowledge Enable:1=ACK returned
	UINT32 POS:1;         //11,Acknowledge/PEC Position (for data reception):0=Current,1=Next
	UINT32 PEC:1;         //12,Packet Error Checking:1=PEC transfer
	UINT32 ALERT:1;       //13,SMBus Alert:0 Release SMBA pin high(NACK),1=Drive SMBA pin low(ACK)
	UINT32 Reserved1:1;   //14,
	UINT32 SWRST:1;       //15,Software Reset:1=Reset
  UINT32 Reserved2:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_CR2            0x00000000//0x004
struct I2C_CR2_BIT
{
	UINT32 FREQ:6;        //00,FREQ[5:0] bits (Peripheral Clock Frequency):0_1=not allowed,2_50=2_50MHz
	UINT32 Reserved0:2;   //06,
	UINT32 ITERREN:1;     //08,Error Interrupt Enable:1=Enable,interrupt when (BERR,ARLO,AF,OVR,PECERR,TIMEOUT,SMBALERT)=1
	UINT32 ITEVTEN:1;     //09,Event Interrupt Enable:1=Enable,interrupt when (SB(M),ADDR(M/S),ADD10(M),STOPF1(S),BTF,TxE,RxNE)=1
	UINT32 ITBUFEN:1;     //10,Buffer Interrupt Enable,when TxE=1 or RxNE=1,generates event interrupt:1=Enable
	UINT32 DMAEN:1;       //11,DMA Requests Enable:0=disable,1=Enable when TxE=1 or RxNE=1
	UINT32 LAST:1;        //12,DMA Last Transfer:1=Last transfer
	UINT32 Reserved1:3;   //13,
  UINT32 Reserved2:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_OAR1           0x00000000//0x008
struct I2C_OAR1_BIT
{
	UINT32 ADD:10;        //00,Interface Address
	UINT32 Reserved0:5;   //10,
	UINT32 ADDMODE:1;     //15,Addressing Mode (Slave mode):0=7 bit,1=10 bit
  UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_OAR2           0x00000000//0x00C
struct I2C_OAR2_BIT
{
	UINT32 ENDUAL:1;      //00,Dual addressing mode enable:0=only OAR1 in 7bit,1=OAR1 and OAR2 in 7bit
	UINT32 ADD2:7;        //01,Interface address
	UINT32 Reserved0:8;   //08,
  UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_DR             0x00000000//0x010
struct I2C_DR_BIT
{
	UINT32 DR:8;          //00,8-bit Data Register
	UINT32 Reserved0:8;   //08,
  UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_SR1            0x00000000//0x014
struct I2C_SR1_BIT
{
	UINT32 SB:1;          //00,Start Bit (Master mode)
	UINT32 ADDR:1;        //01,Address sent (master mode)/matched (slave mode)
	UINT32 BTF:1;         //02,Byte Transfer Finished
	UINT32 ADD10:1;       //03,10-bit header sent (Master mode)
	UINT32 STOPF:1;       //04,Stop detection (Slave mode)
	UINT32 Reserved0:1;   //05,
	UINT32 RXNE:1;        //06,Data Register not Empty (receivers)
	UINT32 TXE:1;         //07,Data Register Empty (transmitters)
	UINT32 BERR:1;        //08,Bus Error
	UINT32 ARLO:1;        //09,Arbitration Lost (master mode)
	UINT32 AF:1;          //10,Acknowledge Failure
	UINT32 OVR:1;         //11,Overrun/Underrun
	UINT32 PECERR:1;      //12,PEC Error in reception
	UINT32 Reserved1:1;   //13,
	UINT32 TIMEOUT:1;     //14,Timeout or Tlow Error
	UINT32 SMBALERT:1;    //15,SMBus Alert
  UINT32 Reserved2:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_SR2            0x00000000//0x018
struct I2C_SR2_BIT
{
	UINT32 MSL:1;         //00,Master/Slave
	UINT32 BUSY:1;        //01,Bus Busy
	UINT32 TRA:1;         //02,Transmitter/Receiver
	UINT32 Reserved0:1;   //03,
	UINT32 GENCALL:1;     //04,General Call Address (Slave mode)
	UINT32 SMBDEFAULT:1;  //05,SMBus Device Default Address (Slave mode)
	UINT32 SMBHOST:1;     //06,SMBus Host Header (Slave mode)
	UINT32 DUALF:1;       //07,Dual Flag (Slave mode)
	UINT32 PEC:8;         //08,Packet Error Checking Register
  UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
//Event=SR2_Low:SR1_Low

#define I2C_EVENT_MASTER_MODE_SELECT                    0x00030001  //EV5, BUSY, MSL and SB flag
#define I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED      0x00070082  //EV6, BUSY, MSL, ADDR, TXE and TRA flags
#define I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED         0x00030002  //EV6, BUSY, MSL and ADDR flags
#define I2C_EVENT_MASTER_MODE_ADDRESS10                 0x00030008  //EV9, BUSY, MSL and ADD10 flags
#define I2C_EVENT_MASTER_BYTE_RECEIVED                  0x00030040  //EV7,Master receive: BUSY, MSL and RXNE flags
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING              0x00070080  //EV8, Master transmit:TRA, BUSY, MSL, TXE flags
#define I2C_EVENT_MASTER_BYTE_TRANSMITTED               0x00070084  //EV8_2,TRA, BUSY, MSL, TXE and BTF flags

//1,Case of One Single Address managed by the slave
#define  I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED          ((uint32_t)0x00020002) //EV1, BUSY and ADDR flags
#define  I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED       ((uint32_t)0x00060082) //EV1, TRA, BUSY, TXE and ADDR flags

//2,Case of Dual address managed by the slave
#define  I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED    ((uint32_t)0x00820000)  //EV1, DUALF and BUSY flags
#define  I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ((uint32_t)0x00860080)  //EV1, DUALF, TRA, BUSY and TXE flags

//3,Case of General Call enabled for the slave
#define  I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED        ((uint32_t)0x00120000)  //EV1, GENCALL and BUSY flags


#define I2C_EVENT_SLAVE_BYTE_RECEIVED                  0x00020040  //EV2,slave receive: BUSY and RXNE flags
#define I2C_EVENT_SLAVE_STOP_DETECTED                  0x00000010  //EV4,slave receive: STOPF flag
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTED               0x00060084  //EV3,slave transmitter: TRA, BUSY, TXE and BTF flags
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTING              0x00060080  //EV3,slave transmitter: TRA, BUSY and TXE flags
#define I2C_EVENT_SLAVE_ACK_FAILURE                    0x00000400  //EV3_2,slave transmitter: AF flag

//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_CCR            0x00000000//0x01C
struct I2C_CCR_BIT
{
	UINT32 CCR:12;        //00,Clock Control Register in Fast/Standard mode (Master mode):TH
	UINT32 Reserved0:2;   //12,
	UINT32 DUTY:1;        //14,Fast Mode Duty Cycle:0=(TL/TH=2),1=(TL/TH=16/9
	UINT32 FS:1;          //15,I2C Master Mode Selection:0=Slow Mode(SM,TL/TH=1),1=Fast Mode(FM)
  UINT32 Reserved2:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_I2C_TRISE            0x00000002//0x020
struct I2C_TRISE_BIT
{
	UINT32 TRISE:6;       //00,Maximum Rise Time in Fast/Standard mode (Master mode)
	UINT32 Reserved0:10;  //06,
  UINT32 Reserved2:16;  //16,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define I2C_Struct Struct_I2C
typedef struct Struct_I2C//0x40005400=I2C1,0x40005800=I2C2
{
  union{UINT32 CR1;struct I2C_CR1_BIT CR1_BIT;};   //0x000(RW),I2C Control register 1 
  union{UINT32 CR2;struct I2C_CR2_BIT CR2_BIT;};   //0x004(RW),I2C Control register 2 
  union{UINT32 OAR1;struct I2C_OAR1_BIT OAR1_BIT;};//0x008(RW),
  union{UINT32 OAR2;struct I2C_OAR2_BIT OAR2_BIT;};//0x00C(RW),
  union{UINT32 DR;struct I2C_DR_BIT DR_BIT;};      //0x010(RW),
  union{UINT32 SR1;struct I2C_SR1_BIT SR1_BIT;};   //0x014(RW),
  union{UINT32 SR2;struct I2C_SR2_BIT SR2_BIT;};   //0x018(RW),
  union{UINT32 CCR;struct I2C_CCR_BIT CCR_BIT;};   //0x01C(RW),
  union{UINT32 TRISE;struct I2C_TRISE_BIT TRISE_BIT;};//0x020(RW),
	UINT32 Reserved0[247]; //0x024,
} I2C_Type,Type_I2C;
#define PT_I2C1                 ((volatile Type_I2C *)BASE_I2C1)
#define PT_I2C2                 ((volatile Type_I2C *)BASE_I2C2)
#define PT_I2C(i)               ((volatile Type_I2C *)BASE_I2C(i))
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define I2C_CR1(i)              I2C[i].CR1//i=0_1
#define I2C_CR2(i)              I2C[i].CR2
#define I2C_OAR1(i)             I2C[i].OAR1
#define I2C_OAR2(i)             I2C[i].OAR2
#define I2C_DR(i)               I2C[i].DR
#define I2C_SR1(i)              I2C[i].SR1
#define I2C_SR2(i)              I2C[i].SR2
#define I2C_CCR(i)              I2C[i].CCR
#define I2C_TRISE(i)            I2C[i].TRISE
//==============================================================================================================================
#define RSTV_WWDG_CR            0x0000007F//0x000
struct WWDG_CR_BIT
{
	UINT32 T:7;           //00,T[6:0] bits (7-Bit counter (MSB to LSB))
	UINT32 WDGA:1;        //07,Activation bit
	UINT32 Reserved0:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_WWDG_CFR           0x0000007F//0x004
struct WWDG_CFR_BIT
{
	UINT32 W:7;           //00,W[6:0] bits (7-bit window value)
	UINT32 WDGTB:2;       //07,WDGTB[1:0] bits (Timer Base)
	UINT32 EWI:1;         //09,Early Wakeup Interrupt
	UINT32 Reserved0:22;  //10,
};
#define WWDG_CFR_WDGTB_DIV1             0//PCLK1/1
#define WWDG_CFR_WDGTB_DIV2             1//PCLK1/2
#define WWDG_CFR_WDGTB_DIV4             2//PCLK1/4
#define WWDG_CFR_WDGTB_DIV8             3//PCLK1/8
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_WWDG_SR            0x00000000//0x008
struct WWDG_SR_BIT
{
	UINT32 EWIF:1;        //00,Early Wakeup Interrupt Flag
	UINT32 Reserved0:31;  //01,
};
//------------------------------------------------------------------------------------------------------------------------------
#define WWDG_Struct Struct_WWDG
typedef struct Struct_WWDG//0x40002C00
{
  union{UINT32 CR;struct WWDG_CR_BIT CR_BIT;};//0x000(RW),
  union{UINT32 CFR;struct WWDG_CFR_BIT CFR_BIT;};//0x004(RW),
  union{UINT32 SR;struct WWDG_SR_BIT SR_BIT;};//0x008(RW),
} WWDG_Type,Type_WWDG;
#define PT_WWDG                 ((volatile Type_WWDG *)BASE_WWDG)
//------------------------------------------------------------------------------------------------------------------------------
#define WWDG_CR                 WWDG.CR
#define WWDG_CFR                WWDG.CFR
#define WWDG_SR                 WWDG.SR
//==============================================================================================================================
#define RSTV_IWDG_KR              0x00000000//0x000
struct IWDG_KR_BIT
{
	UINT32 KEY:16;        //00,Key value (write only, read 0000h)
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_IWDG_PR              0x00000000//0x004
#define IWDG_PR_DIV4                    0//DIV 4
#define IWDG_PR_DIV8                    1//DIV 8
#define IWDG_PR_DIV16                   2//DIV 16
#define IWDG_PR_DIV32                   3//DIV 32
#define IWDG_PR_DIV64                   4//DIV 64
#define IWDG_PR_DIV128                  5//DIV 128
#define IWDG_PR_DIV256                  6//DIV 256
struct IWDG_PR_BIT
{
	UINT32 PD:3;          //00,PD[2:0] (Prescaler divider)
	UINT32 Reserved0:29;  //03,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_IWDG_RLR             0x00000000//0x008
struct IWDG_RLR_BIT
{
	UINT32 RL:12;         //00,Watchdog counter reload value
	UINT32 Reserved0:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_IWDG_SR              0x00000000//0x00C
struct IWDG_SR_BIT
{
	UINT32 PVU:1;         //00,Watchdog prescaler value update
	UINT32 RVU:1;         //01,Watchdog counter reload value update
	UINT32 Reserved0:30;  //02,
};
//------------------------------------------------------------------------------------------------------------------------------
#define IWDG_Struct Struct_IWDG
typedef struct Struct_IWDG//0x40003000
{
  union{UINT32 KR;struct IWDG_KR_BIT KR_BIT;};   //0x000(RW),
  union{UINT32 PR;struct IWDG_PR_BIT PR_BIT;};   //0x004(RW),
  union{UINT32 RLR;struct IWDG_RLR_BIT RLR_BIT;};//0x008(RW),
  union{UINT32 SR;struct IWDG_SR_BIT SR_BIT;};   //0x00C(RW),
} IWDG_Type,Type_IWDG;
#define PT_IWDG                 ((volatile Type_IWDG *)BASE_IWDG)
//------------------------------------------------------------------------------------------------------------------------------
#define IWDG_KR                 IWDG.KR
#define IWDG_PR                 IWDG.PR
#define IWDG_RLR                IWDG.RLR
#define IWDG_SR                 IWDG.SR
//==============================================================================================================================
#define RSTV_PWR_CR             0x00000000//0x000
struct PWR_CR_BIT
{
  UINT32 LPDS:1;        //00,Low-Power Deepsleep
  UINT32 PDDS:1;        //01,Power Down Deepsleep
  UINT32 CWUF:1;        //02,Clear Wakeup Flag
  UINT32 CSBF:1;        //03,Clear Standby Flag
  UINT32 PVDE:1;        //04,Power Voltage Detector Enable
  UINT32 PLS:3;         //05,PLS[2:0] bits (PVD Level Selection),PLS=0_7=2.2_2.9V
  UINT32 DBP:1;         //08,Disable Backup Domain write protection
  UINT32 Reserved0:23;
};
#define PWR_CR_LPDS             PWR.CR_BIT.LPDS
#define PWR_CR_PDDS             PWR.CR_BIT.PDDS
#define PWR_CR_CWUF             PWR.CR_BIT.CWUF
#define PWR_CR_CSBF             PWR.CR_BIT.CSBF
#define PWR_CR_PVDE             PWR.CR_BIT.PVDE
#define PWR_CR_PLS              PWR.CR_BIT.PLS
#define PWR_CR_DBP              PWR.CR_BIT.DBP
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_PWR_CSR            0x00000000//0x004
struct PWR_CSR_BIT
{
  UINT32 WUF:1;         //00,Wakeup Flag
  UINT32 SBF:1;         //01,Standby Flag
  UINT32 PVDO:1;        //02,PVD Output
  UINT32 Reserved0:5;   //03,
  UINT32 EWUP:1;        //08,Enable WKUP pin
  UINT32 Reserved1:23;
};
#define PWR_CSR_WUF             PWR.CSR_BIT.WUF
#define PWR_CSR_SBF             PWR.CSR_BIT.SBF
#define PWR_CSR_PVDO            PWR.CSR_BIT.PVDO
#define PWR_CSR_EWUP            PWR.CSR_BIT.EWUP
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PWR_Struct Struct_PWR
typedef struct Struct_PWR//0x40007000
{
  union{UINT32 CR;struct PWR_CR_BIT CR_BIT;};//0x000(RW),
  union{UINT32 CSR;struct PWR_CSR_BIT CSR_BIT;};//0x004(RW),
} PWR_Type,Type_PWR;
#define PT_PWR                  ((volatile Type_PWR *)BASE_PWR)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PWR_CR                  PWR.CR
#define PWR_CSR                 PWR.CSR
//==============================================================================================================================
#define RSTV_RCC_CR             0x00000083//0x000
struct RCC_CR_BIT
{
  UINT32 HSION:1;       //00,Internal High Speed clock enable
  UINT32 HSIRDY:1;      //01,Internal High Speed clock ready flag
  UINT32 Reserved0:1;   //02,
  UINT32 HSITRIM:5;     //03,Internal High Speed clock trimming
  UINT32 HSICAL:8;      //08,Internal High Speed clock Calibration
  UINT32 HSEON:1;       //16,External High Speed clock enable,3MHz_25MHz
  UINT32 HSERDY:1;      //17,External High Speed clock ready flag
  UINT32 HSEBYP:1;      //18,External High Speed clock Bypass
  UINT32 CSSON:1;       //19,Clock Security System enable
  UINT32 Reserved1:4;   //20,
  UINT32 PLLON:1;       //24,PLL enable
  UINT32 PLLRDY:1;      //25,PLL clock ready flag
#if IsDensity(CL)
  UINT32 PLL2ON:1;      //26,PLL2 enable
  UINT32 PLL2RDY:1;     //27,PLL2 clock ready flag
  UINT32 PLL3ON:1;      //28,PLL3 enable
  UINT32 PLL3RDY:1;     //29,PLL3 clock ready flag
  UINT32 Reserved2:2;   //30,
#else
  UINT32 Reserved2:6;   //26,
#endif
};
#define RCC_CR_HSION            RCC.CR_BIT.HSION
#define RCC_CR_HSIRDY           RCC.CR_BIT.HSIRDY
#define RCC_CR_HSITRIM          RCC.CR_BIT.HSITRIM
#define RCC_CR_HSICAL           RCC.CR_BIT.HSICAL
#define RCC_CR_HSEON            RCC.CR_BIT.HSEON
#define RCC_CR_HSERDY           RCC.CR_BIT.HSERDY

#define RCC_CR_HSEBYP           RCC.CR_BIT.HSEBYP
#define RCC_CR_CSSON            RCC.CR_BIT.CSSON
#define RCC_CR_PLLON            RCC.CR_BIT.PLLON
#define RCC_CR_PLLRDY           RCC.CR_BIT.PLLRDY
#if IsDensity(CL)
#define RCC_CR_PLL2ON           RCC.CR_BIT.PLL2ON
#define RCC_CR_PLL2RDY          RCC.CR_BIT.PLL2RDY
#define RCC_CR_PLL3ON           RCC.CR_BIT.PLL3ON
#define RCC_CR_PLL3RDY          RCC.CR_BIT.PLL3RDY
#endif
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_CFGR           0x00000000//0x004
#define RCC_CFGR_SW_HSI                 0//HSI selected as system clock
#define RCC_CFGR_SW_HSE                 1//HSE selected as system clock
#define RCC_CFGR_SW_PLL                 2//PLL selected as system clock

#define RCC_CFGR_SWS_HSI                0//HSI oscillator used as system clock
#define RCC_CFGR_SWS_HSE                1//HSE oscillator used as system clock
#define RCC_CFGR_SWS_PLL                2//PLL used as system clock

#define RCC_CFGR_MCO_NOCLOCK            0//No clock
#define RCC_CFGR_MCO_SYSCLK             4//System clock selected as MCO source
#define RCC_CFGR_MCO_HSI                5//HSI clock selected as MCO source
#define RCC_CFGR_MCO_HSE                6//HSE clock selected as MCO source
#define RCC_CFGR_MCO_PLLCLK_Div2        7//PLL clock divided by 2 selected as MCO source
#if IsDensity(CL)
#define RCC_CFGR_MCO_PLL2CLK            8//PLL2 clock selected as MCO source
#define RCC_CFGR_MCO_PLL3CLK_Div2       9//PLL3 clock divided by 2 selected as MCO source
#define RCC_CFGR_MCO_Ext_HSE            0x0A//XT1 external 3-25 MHz oscillator clock selected as MCO source
#define RCC_CFGR_MCO_PLL3CLK            0x0B//PLL3 clock selected as MCO source
#endif
struct RCC_CFGR_BIT
{
  UINT32 SW:2;          //00,SW[1:0] bits (System clock Switch)
  UINT32 SWS:2;         //02,SWS[1:0] bits (System Clock Switch Status)
  UINT32 HPRE:4;        //04,HPRE[3:0] bits (AHB prescaler),divided by: 0_7=1,8_B=2^(HPRE-7),C_F=2^(HPRE-6)
  UINT32 PPRE1:3;       //08,PRE1[2:0] bits (APB1 prescaler),divided by: 0_3=1,4_7=2^(PPRE1-3)
  UINT32 PPRE2:3;       //11,PRE2[2:0] bits (APB2 prescaler),divided by: 0_3=1,4_7=2^(PPRE1-3)
  UINT32 ADCPRE:2;      //14,ADCPRE[1:0] bits (ADC prescaler),PCLK2 divided by:0_3= 2*(ADCPRE+1)
#if IsDensity(CL)
  UINT32 PLLSRC:1;      //16,PLL entry clock source :0=HSI, 1= PREDIV1 clock 
  UINT32 PLLXTPRE:1;    //17,HSE divider for PLL entry:0=not divided, 1=PREDIV1/2
  UINT32 PLLMULL:4;     //18,PLLMUL[3:0] bits (PLL multiplication factor),PLL input clock *: 2_7= 4_9 ,11=6.5
  UINT32 USBPRE:1;      //22,USBPRE=OTGFSPRE,USB OTG FS prescaler,PLLVCO/:0=3,1=2
  UINT32 Reserved0:1;   //23,
  UINT32 MCO:4;         //24,MCO[3:0] bits (Microcontroller Clock Output)
  UINT32 Reserved1:4;   //28,
#elif IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 PLLSRC:1;      //16,PLL entry clock source :0=HSI/2, 1= PREDIV1
  UINT32 PLLXTPRE:1;    //17,HSE divider for PLL entry:0=not divided, 1=PREDIV1/2
  UINT32 PLLMULL:4;     //18,PLLMUL[3:0] bits (PLL multiplication factor),PLL input clock *:0_14=2_16(PLLMULL+2)
  UINT32 USBPRE:1;      //22,USBPRE=OTGFSPRE,USB OTG FS prescaler,PLLVCO/:0=3,1=2
  UINT32 Reserved0:1;   //23,
  UINT32 MCO:3;         //24,MCO[2:0] bits (Microcontroller Clock Output)
  UINT32 Reserved1:5;   //27,
#else
  UINT32 PLLSRC:1;      //16,PLL entry clock source :0=HSI/2, 1=PREDIV1
  UINT32 PLLXTPRE:1;    //17,PREDIV1 divide by:0=not divided, 1= /2
  UINT32 PLLMULL:4;     //18,PLLMUL[3:0] bits (PLL multiplication factor),PLL input clock *:0_14=2_16(PLLMULL+2)
  UINT32 USBPRE:1;      //22,USBPRE=OTGFSPREUSB Device prescaler, PLLVCO/:0=3,1=2
  UINT32 Reserved0:1;   //23,
  UINT32 MCO:3;         //24,MCO[2:0] bits (Microcontroller Clock Output)
  UINT32 Reserved1:5;   //27,
#endif
};
#define RCC_CFGR_SW             RCC.CFGR_BIT.SW
#define RCC_CFGR_SWS            RCC.CFGR_BIT.SWS
#define RCC_CFGR_HPRE           RCC.CFGR_BIT.HPRE
#define RCC_CFGR_PPRE1          RCC.CFGR_BIT.PPRE1
#define RCC_CFGR_PPRE2          RCC.CFGR_BIT.PPRE2
#define RCC_CFGR_ADCPRE         RCC.CFGR_BIT.ADCPRE
#define RCC_CFGR_PLLSRC         RCC.CFGR_BIT.PLLSRC
#define RCC_CFGR_PLLXTPRE       RCC.CFGR_BIT.PLLXTPRE
#define RCC_CFGR_PLLMULL        RCC.CFGR_BIT.PLLMULL
#define RCC_CFGR_USBPRE         RCC.CFGR_BIT.USBPRE
#define RCC_CFGR_MCO            RCC.CFGR_BIT.MCO
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_CIR            0x00000000//0x008
struct RCC_CIR_BIT
{
  UINT32 LSIRDYF:1;     //00,LSI Ready Interrupt flag
  UINT32 LSERDYF:1;     //01,LSE Ready Interrupt flag
  UINT32 HSIRDYF:1;     //02,HSI Ready Interrupt flag
  UINT32 HSERDYF:1;     //03,HSE Ready Interrupt flag
  UINT32 PLLRDYF:1;     //04,PLL Ready Interrupt flag
#if IsDensity(CL)
  UINT32 PLL2RDYF:1;    //05,PLL2 Ready Interrupt flag
  UINT32 PLL3RDYF:1;    //06,PLL3 Ready Interrupt flag
#else
  UINT32 Reserved0:2;   //05,
#endif
  UINT32 CSSF:1;        //07,Clock Security System Interrupt flag
  UINT32 LSIRDYIE:1;    //08,LSI Ready Interrupt Enable
  UINT32 LSERDYIE:1;    //09,LSE Ready Interrupt Enable
  UINT32 HSIRDYIE:1;    //10,HSI Ready Interrupt Enable
  UINT32 HSERDYIE:1;    //11,HSE Ready Interrupt Enable
  UINT32 PLLRDYIE:1;    //12,PLL Ready Interrupt Enable
#if IsDensity(CL)
  UINT32 PLL2RDYIE:1;   //13,PLL2 Ready Interrupt Enable
  UINT32 PLL3RDYIE:1;   //14,PLL3 Ready Interrupt Enable
  UINT32 Reserved1:1;   //15,
#else
  UINT32 Reserved1:3;   //13,
#endif
  UINT32 LSIRDYC:1;     //16,LSI Ready Interrupt Clear
  UINT32 LSERDYC:1;     //17,LSE Ready Interrupt Clear
  UINT32 HSIRDYC:1;     //18,HSI Ready Interrupt Clear
  UINT32 HSERDYC:1;     //19,HSE Ready Interrupt Clear
  UINT32 PLLRDYC:1;     //20,PLL Ready Interrupt Clear
#if IsDensity(CL)
  UINT32 PLL2RDYC:1;    //21,PLL Ready Interrupt Clear
  UINT32 PLL3RDYC:1;    //22,PLL Ready Interrupt Clear
#else
  UINT32 Reserved2:2;   //21,
#endif
  UINT32 CSSC:1;        //23,Clock Security System Interrupt Clear
  UINT32 Reserved3:8;   //24,
};

#define RCC_CIR_LSIRDYF         RCC.CIR_BIT.LSIRDYF
#define RCC_CIR_LSERDYF         RCC.CIR_BIT.LSERDYF
#define RCC_CIR_HSIRDYF         RCC.CIR_BIT.HSIRDYF
#define RCC_CIR_HSERDYF         RCC.CIR_BIT.HSERDYF
#define RCC_CIR_PLLRDYF         RCC.CIR_BIT.PLLRDYF
#if IsDensity(CL)
#define RCC_CIR_PLL2RDYF        RCC.CIR_BIT.PLL2RDYF
#define RCC_CIR_PLL3RDYF        RCC.CIR_BIT.PLL3RDYF
#endif
#define RCC_CIR_CSSF            RCC.CIR_BIT.CSSF
#define RCC_CIR_LSIRDYIE        RCC.CIR_BIT.LSIRDYIE
#define RCC_CIR_LSERDYIE        RCC.CIR_BIT.LSERDYIE
#define RCC_CIR_HSIRDYIE        RCC.CIR_BIT.HSIRDYIE
#define RCC_CIR_HSERDYIE        RCC.CIR_BIT.HSERDYIE
#define RCC_CIR_PLLRDYIE        RCC.CIR_BIT.PLLRDYIE
#if IsDensity(CL)
#define RCC_CIR_PLL2RDYIE       RCC.CIR_BIT.PLL2RDYIE
#define RCC_CIR_PLL3RDYIE       RCC.CIR_BIT.PLL3RDYIE
#endif
#define RCC_CIR_LSIRDYC         RCC.CIR_BIT.LSIRDYC
#define RCC_CIR_LSERDYC         RCC.CIR_BIT.LSERDYC
#define RCC_CIR_HSIRDYC         RCC.CIR_BIT.HSIRDYC
#define RCC_CIR_HSERDYC         RCC.CIR_BIT.HSERDYC
#define RCC_CIR_PLLRDYC         RCC.CIR_BIT.PLLRDYC
#if IsDensity(CL)
#define RCC_CIR_PLL2RDYC        RCC.CIR_BIT.PLL2RDYC
#define RCC_CIR_PLL3RDYC        RCC.CIR_BIT.PLL3RDYC
#endif
#define RCC_CIR_CSSC            RCC.CIR_BIT.CSSC

//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_APB2RSTR       0x00000000//0x00C
struct RCC_APB2RSTR_BIT
{
  UINT32 AFIORST:1;     //00,Alternate Function I/O reset
  UINT32 Reserved0:1;   //01,
  UINT32 IOPARST:1;     //02,I/O port A reset
  UINT32 IOPBRST:1;     //03,I/O port B reset
  UINT32 IOPCRST:1;     //04,I/O port C reset
  UINT32 IOPDRST:1;     //05,I/O port D reset
#if IsDensity(LD) || IsDensity(LD_VL)
  UINT32 Reserved1:3;   //06,
#else
  UINT32 IOPERST:1;     //06,I/O port E reset
#if IsDensity(HD) || IsDensity(XL)
  UINT32 IOPFRST:1;     //07,I/O port F reset
  UINT32 IOPGRST:1;     //08,I/O port G reset
#else
  UINT32 Reserved1:2;   //07,
#endif
#endif

  UINT32 ADC1RST:1;     //09,ADC 1 interface reset
#if !IsDensity(LD_VL) && !IsDensity(MD_VL) && ! IsDensity(HD_VL)
  UINT32 ADC2RST:1;     //10,ADC 2 interface reset
#else
  UINT32 Reserved2:1;   //10,
#endif
  UINT32 TIM1RST:1;     //11,TIM1 Timer reset
  UINT32 SPI1RST:1;     //12,SPI 1 reset
#if IsDensity(HD)||IsDensity(XL)
  UINT32 TIM8RST:1;     //13,TIM8 Timer reset
#else
  UINT32 Reserved3:1;   //13,
#endif  
  UINT32 USART1RST:1;   //14,USART1 reset
#if IsDensity(HD)||IsDensity(XL)
  UINT32 ADC3RST:1;     //15,ADC3 interface reset,<LDY>
#else
  UINT32 Reserved4:1;   //15,
#endif  

#if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 TIM15RST:1;    //16,TIM15 Timer reset,<LDY>
  UINT32 TIM16RST:1;    //17,TIM16 Timer reset,<LDY>
  UINT32 TIM17RST:1;    //18,TIM17 Timer reset,<LDY>
#else
  UINT32 Reserved5:3;   //16,
#endif
#if IsDensity(XL)
  UINT32 TIM9RST        //19,TIM9 Timer reset, <LDY>
  UINT32 TIM10RST       //20,TIM10 Timer reset,<LDY>
  UINT32 TIM11RST       //21,TIM11 Timer reset,<LDY>
#else
  UINT32 Reserved6:3;   //19,
#endif
  UINT32 Reserved7:10;  //22,
};

#define RCC_APB2RSTR_AFIORST    RCC.APB2RSTR_BIT.AFIORST
#define RCC_APB2RSTR_IOPARST    RCC.APB2RSTR_BIT.IOPARST
#define RCC_APB2RSTR_IOPBRST    RCC.APB2RSTR_BIT.IOPBRST
#define RCC_APB2RSTR_IOPCRST    RCC.APB2RSTR_BIT.IOPCRST
#define RCC_APB2RSTR_IOPDRST    RCC.APB2RSTR_BIT.IOPDRST
#if !IsDensity(LD) && !IsDensity(LD_VL)
#define RCC_APB2RSTR_IOPERST    RCC.APB2RSTR_BIT.IOPERST
#if IsDensity(HD) || IsDensity(XL)
#define RCC_APB2RSTR_IOPFRST    RCC.APB2RSTR_BIT.IOPFRST
#define RCC_APB2RSTR_IOPGRST    RCC.APB2RSTR_BIT.IOPGRST
#endif
#endif
#define RCC_APB2RSTR_ADC1RST    RCC.APB2RSTR_BIT.ADC1RST
#if !IsDensity(LD_VL) && !IsDensity(MD_VL) && ! IsDensity(HD_VL)
#define RCC_APB2RSTR_ADC2RST    RCC.APB2RSTR_BIT.ADC2RST
#endif
#define RCC_APB2RSTR_TIM1RST    RCC.APB2RSTR_BIT.TIM1RST
#define RCC_APB2RSTR_SPI1RST    RCC.APB2RSTR_BIT.SPI1RST
#if IsDensity(HD)||IsDensity(XL)
#define RCC_APB2RSTR_TIM8RST    RCC.APB2RSTR_BIT.TIM8RST
#endif
#define RCC_APB2RSTR_USART1RST  RCC.APB2RSTR_BIT.USART1RST
#if IsDensity(HD)||IsDensity(XL)
#define RCC_APB2RSTR_ADC3RST    RCC.APB2RSTR_BIT.ADC3RST
#endif
#if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
#define RCC_APB2RSTR_TIM15RST   RCC.APB2RSTR_BIT.TIM15RST
#define RCC_APB2RSTR_TIM16RST   RCC.APB2RSTR_BIT.TIM16RST
#define RCC_APB2RSTR_TIM17RST   RCC.APB2RSTR_BIT.TIM17RST
#endif
#if IsDensity(XL)
#define RCC_APB2RSTR_TIM9RST    RCC.APB2RSTR_BIT.TIM9RST
#define RCC_APB2RSTR_TIM10RST   RCC.APB2RSTR_BIT.TIM10RST
#define RCC_APB2RSTR_TIM11RST   RCC.APB2RSTR_BIT.TIM11RST
#endif
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_APB1RSTR       0x00000000//0x010
struct RCC_APB1RSTR_BIT
{
  UINT32 TIM2RST:1;     //00,Timer 2 reset 
  UINT32 TIM3RST:1;     //01,Timer 3 reset 
#if !IsDensity(LD) && !IsDensity(LD_VL)
  UINT32 TIM4RST:1;     //02,Timer 4 reset
#else
  UINT32 Reserved0:1;   //02,
#endif
#if IsDensity(HD) ||IsDensity(HD_VL)|| IsDensity(CL) || IsDensity(XL)
  UINT32 TIM5RST:1;     //03,Timer 5 reset
#else
  UINT32 Reserved1:1;   //03,
#endif
#if IsDensity(HD) ||IsDensity(CL) || IsDensity(XL)|| IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 TIM6RST:1;     //04,Timer 6 reset
  UINT32 TIM7RST:1;     //05,Timer 7 reset
#else
  UINT32 Reserved2:2;   //04,
#endif

#if IsDensity(HD_VL) || IsDensity(XL)
  UINT32 TIM12RST:1;    //06,TIM12 Timer reset 
  UINT32 TIM13RST:1;    //07,TIM13 Timer reset 
  UINT32 TIM14RST:1;    //08,TIM14 Timer reset
#else
  UINT32 Reserved3:3;   //06,
#endif
  UINT32 Reserved4:2;   //09,
  UINT32 WWDGRST:1;     //11,Window Watchdog reset
  UINT32 Reserved5:2;   //12,
#if !IsDensity(LD) && !IsDensity(LD_VL)
  UINT32 SPI2RST:1;     //14,SPI 2 reset
#else
  UINT32 Reserved6:1;   //14,
#endif
#if IsDensity(HD)|| IsDensity(HD_VL)|| IsDensity(CL) || IsDensity(XL)
  UINT32 SPI3RST:1;     //15,SPI 3 reset
#else
  UINT32 Reserved7:1;   //15,
#endif
  UINT32 Reserved8:1;   //16,
  UINT32 UART2RST:1;    //17,USART 2 reset
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
  UINT32 UART3RST:1;    //18,USART 3 reset
#else
  UINT32 Reserved9:1;   //18,
#endif
#if IsDensity(HD)|| IsDensity(HD_VL)|| IsDensity(CL) || IsDensity(XL)
  UINT32 UART4RST:1;    //19,UART 4 reset 
  UINT32 UART5RST:1;    //20,UART 5 reset 
#else
  UINT32 Reserved10:2;
#endif
  UINT32 I2C1RST:1;     //21,I2C 1 reset

#if !IsDensity(LD) && !IsDensity(LD_VL)
  UINT32 I2C2RST:1;     //22,I2C 2 reset
#else
  UINT32 Reserved11:1;  //22,
#endif
#if IsDensity(HD) || IsDensity(MD) || IsDensity(LD) || IsDensity(XL)
  UINT32 USBRST:1;      //23,USB Device reset
#else
  UINT32 Reserved12:1;  //23,
#endif
  UINT32 Reserved13:1;  //24,
#if !IsDensity(LD_VL) && !IsDensity(MD_VL) && !IsDensity(HD_VL)
  UINT32 CAN1RST:1;     //25,CAN1 reset
#else
  UINT32 Reserved14:1;  //25,
#endif
#if IsDensity(CL)
  UINT32 CAN2RST:1;     //26,CAN2 reset
#else
  UINT32 Reserved15:1;  //26,
#endif
  UINT32 BKPRST:1;      //27,Backup interface reset
  UINT32 PWRRST:1;      //28,Power interface reset
#if IsDensity(HD) || IsDensity(CL) || IsDensity(XL)|| IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 DACRST:1;      //29,DAC interface reset
#else
  UINT32 Reserved16:1;  //29,
#endif
#if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 CECRST:1;      //30,CEC interface reset
#else
  UINT32 Reserved17:1;  //30,
#endif
  UINT32 Reserved18:1;  //31,
};

#define RCC_APB1RSTR_TIM2RST    RCC.APB1RSTR_BIT.TIM2RST
#define RCC_APB1RSTR_TIM3RST    RCC.APB1RSTR_BIT.TIM3RST
#if !IsDensity(LD) && !IsDensity(LD_VL)
  #define RCC_APB1RSTR_TIM4RST  RCC.APB1RSTR_BIT.TIM4RST
#endif
#if IsDensity(HD) ||IsDensity(HD_VL)|| IsDensity(CL) || IsDensity(XL)
  #define RCC_APB1RSTR_TIM5RST  RCC.APB1RSTR_BIT.TIM5RST  
#endif
#if IsDensity(HD) ||IsDensity(CL) || IsDensity(XL)|| IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  #define RCC_APB1RSTR_TIM6RST  RCC.APB1RSTR_BIT.TIM6RST  
  #define RCC_APB1RSTR_TIM7RST  RCC.APB1RSTR_BIT.TIM7RST  
#endif
#if IsDensity(HD_VL) || IsDensity(XL)
  #define RCC_APB1RSTR_TIM12RST RCC.APB1RSTR_BIT.TIM12RST
  #define RCC_APB1RSTR_TIM13RST RCC.APB1RSTR_BIT.TIM13RST
  #define RCC_APB1RSTR_TIM14RST RCC.APB1RSTR_BIT.TIM14RST
#endif
  #define RCC_APB1RSTR_WWDGRST RCC.APB1RSTR_BIT.WWDGRST
#if !IsDensity(LD) && !IsDensity(LD_VL)
  #define RCC_APB1RSTR_SPI2RST RCC.APB1RSTR_BIT.SPI2RST
#endif
#if IsDensity(HD)|| IsDensity(HD_VL)|| IsDensity(CL) || IsDensity(XL)
  #define RCC_APB1RSTR_SPI3RST RCC.APB1RSTR_BIT.SPI3RST
#endif
  #define RCC_APB1RSTR_UART2RST RCC.APB1RSTR_BIT.UART2RST
#if !defined (STM32F10X_LD) && !defined (STM32F10X_LD_VL)
  #define RCC_APB1RSTR_UART3RST RCC.APB1RSTR_BIT.UART3RST
#endif
#if IsDensity(HD)|| IsDensity(HD_VL)|| IsDensity(CL) || IsDensity(XL)
  #define RCC_APB1RSTR_UART4RST RCC.APB1RSTR_BIT.UART4RST
  #define RCC_APB1RSTR_UART5RST RCC.APB1RSTR_BIT.UART5RST
#endif
  #define RCC_APB1RSTR_I2C1RST RCC.APB1RSTR_BIT.I2C1RST
#if !IsDensity(LD) && !IsDensity(LD_VL)
  #define RCC_APB1RSTR_I2C2RST RCC.APB1RSTR_BIT.I2C2RST
#endif
#if IsDensity(HD) || IsDensity(MD) || IsDensity(LD) || IsDensity(XL)
  #define RCC_APB1RSTR_USBRST  RCC.APB1RSTR_BIT.USBRST
#endif
#if !IsDensity(LD_VL) && !IsDensity(MD_VL) && !IsDensity(HD_VL)
  #define RCC_APB1RSTR_CAN1RST RCC.APB1RSTR_BIT.CAN1RST
#endif
#if IsDensity(CL)
  #define RCC_APB1RSTR_CAN2RST RCC.APB1RSTR_BIT.CAN2RST
#endif
  #define RCC_APB1RSTR_BKPRST  RCC.APB1RSTR_BIT.BKPRST
  #define RCC_APB1RSTR_PWRRST  RCC.APB1RSTR_BIT.PWRRST
#if IsDensity(HD) || IsDensity(CL) || IsDensity(XL)|| IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  #define RCC_APB1RSTR_DACRST  RCC.APB1RSTR_BIT.DACRST
#endif
#if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  #define RCC_APB1RSTR_CECRST  RCC.APB1RSTR_BIT.CECRST
#endif
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_AHBENR         0x00000014//0x014
struct RCC_AHBENR_BIT
{
	UINT32 DMA1EN:1;      //00,DMA1 clock enable
  UINT32 DMA2EN:1;      //01,DMA2 clock enable,only for IsDensity(HD) || IsDensity(CL) || IsDensity(HD_VL)
	UINT32 SRAMEN:1;      //02,SRAM interface clock enable
	UINT32 Reserved1:1;   //03,
	UINT32 FLITFEN:1;     //04,FLITF clock enable
	UINT32 Reserved2:1;   //05,
	UINT32 CRCEN:1;       //06,CRC clock enable
	UINT32 Reserved3:1;   //07,
	UINT32 FSMCEN:1;      //08,FSMC clock enable,only for IsDensity(HD) || IsDensity(XL)||IsDensity(VL)
	UINT32 Reserved5:1;   //09,
  UINT32 SDIOEN:1;      //10,SDIO clock enable,only for IsDensity(HD) || IsDensity(XL)
  UINT32 Reserved7:1;   //11,
  UINT32 OTGFSEN:1;     //12,USB OTG FS clock enable,only for IsDensity(CL)
	UINT32 Reserved8:1;   //13,
	UINT32 ETHMACEN:1;    //14,ETHERNET MAC clock enable,only for IsDensity(CL)
	UINT32 ETHMACTXEN:1;  //15,ETHERNET MAC Tx clock enable,only for IsDensity(CL)
	UINT32 ETHMACRXEN:1;  //16,ETHERNET MAC Rx clock enable,only for IsDensity(CL)
  UINT32 Reserved9:15;  //17,
};
#define RCC_AHBENR_DMA1EN       RCC.AHBENR_BIT.DMA1EN
#define RCC_AHBENR_DMA2EN       RCC.AHBENR_BIT.DMA2EN//IsDensity(HD) || IsDensity(CL) || IsDensity(HD_VL)
#define RCC_AHBENR_SRAMEN       RCC.AHBENR_BIT.SRAMEN
#define RCC_AHBENR_FLITFEN      RCC.AHBENR_BIT.FLITFEN
#define RCC_AHBENR_CRCEN        RCC.AHBENR_BIT.CRCEN
#define RCC_AHBENR_FSMCEN       RCC.AHBENR_BIT.FSMCEN//IsDensity(HD) || IsDensity(XL)||IsDensity(VL)
#define RCC_AHBENR_SDIOEN       RCC.AHBENR_BIT.SDIOEN//IsDensity(HD) || IsDensity(XL)
#define RCC_AHBENR_OTGFSEN      RCC.AHBENR_BIT.OTGFSEN//IsDensity(CL)
#define RCC_AHBENR_ETHMACEN     RCC.AHBENR_BIT.ETHMACEN//IsDensity(CL)
#define RCC_AHBENR_ETHMACTXEN   RCC.AHBENR_BIT.ETHMACTXEN//IsDensity(CL)
#define RCC_AHBENR_ETHMACRXEN   RCC.AHBENR_BIT.ETHMACRXEN//IsDensity(CL)
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_APB2ENR        0x00000000//0x018
struct RCC_APB2ENR_BIT
{
	UINT32 AFIOEN:1;      //00,Alternate Function I/O clock enable
	UINT32 Reserved0:1;   //01,
	UINT32 IOPAEN:1;      //02,I/O port A clock enable
	UINT32 IOPBEN:1;      //03,I/O port B clock enable
	UINT32 IOPCEN:1;      //04,I/O port C clock enable
	UINT32 IOPDEN:1;      //05,I/O port D clock enable
  UINT32 IOPEEN:1;      //06,I/O port E clock enable,only for !IsDensity(LD) && !IsDensity(LD_VL)
	UINT32 IOPFEN:1;      //07,only for IsDensity(HD) || IsDensity(XL) || IsDensity(HD_VL)
	UINT32 IOPGEN:1;      //08,only for IsDensity(HD) || IsDensity(XL) || IsDensity(HD_VL)
	UINT32 ADC1EN:1;      //09,ADC 1 interface clock enable
	UINT32 ADC2EN:1;      //10,ADC 2 interface clock enable
	UINT32 TIM1EN:1;      //11,TIM1 Timer clock enable
	UINT32 SPI1EN:1;      //12,SPI 1 clock enable 
  UINT32 TIM8EN:1;      //13,TIM8 Timer clock enable,only for IsDensity(HD) || IsDensity(XL)
  UINT32 UART1EN:1;     //14,USART1 clock enable
  UINT32 ADC3EN:1;      //15,ADC3 clock enable,only for IsDensity(HD) || IsDensity(XL)
  UINT32 TIM15EN:1;     //16,TIM15 Timer clock enable,only for IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 TIM16EN:1;     //17,TIM16 Timer clock enable,only for IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 TIM17EN:1;     //18,TIM17 Timer clock enable,only for IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
  UINT32 TIM9EN:1;      //19,TIM9  Timer clock enable,only for IsDensity(XL)
  UINT32 TIM10EN:1;     //20,TIM10 Timer clock enable,only for IsDensity(XL)
  UINT32 TIM11EN:1;     //21,TIM11 Timer clock enable,only for IsDensity(XL)
  UINT32 Reserved8:10;  //22,
};
#define RCC_APB2ENR_AFIOEN    RCC.APB2ENR_BIT.AFIOEN
#define RCC_APB2ENR_IOPAEN    RCC.APB2ENR_BIT.IOPAEN
#define RCC_APB2ENR_IOPBEN    RCC.APB2ENR_BIT.IOPBEN
#define RCC_APB2ENR_IOPCEN    RCC.APB2ENR_BIT.IOPCEN
#define RCC_APB2ENR_IOPDEN    RCC.APB2ENR_BIT.IOPDEN
#define RCC_APB2ENR_IOPEEN    RCC.APB2ENR_BIT.IOPEEN //!IsDensity(LD) && !IsDensity(LD_VL)
#define RCC_APB2ENR_IOPFEN    RCC.APB2ENR_BIT.IOPFEN //IsDensity(HD) || IsDensity(XL) || IsDensity(HD_VL)
#define RCC_APB2ENR_IOPGEN    RCC.APB2ENR_BIT.IOPGEN //IsDensity(HD) || IsDensity(XL) || IsDensity(HD_VL)
#define RCC_APB2ENR_ADC1EN    RCC.APB2ENR_BIT.ADC1EN
#define RCC_APB2ENR_TIM1EN    RCC.APB2ENR_BIT.TIM1EN
#define RCC_APB2ENR_SPI1EN    RCC.APB2ENR_BIT.SPI1EN
#define RCC_APB2ENR_TIM8EN    RCC.APB2ENR_BIT.TIM8EN //IsDensity(HD) || IsDensity(XL)
#define RCC_APB2ENR_UART1EN   RCC.APB2ENR_BIT.UART1EN
#define RCC_APB2ENR_ADC3EN    RCC.APB2ENR_BIT.ADC3EN //IsDensity(HD) || IsDensity(XL)
#define RCC_APB2ENR_TIM15EN   RCC.APB2ENR_BIT.TIM15EN//IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
#define RCC_APB2ENR_TIM16EN   RCC.APB2ENR_BIT.TIM16EN//IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
#define RCC_APB2ENR_TIM17EN   RCC.APB2ENR_BIT.TIM17EN//IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
#define RCC_APB2ENR_TIM9EN    RCC.APB2ENR_BIT.TIM9EN //IsDensity(XL)
#define RCC_APB2ENR_TIM10EN   RCC.APB2ENR_BIT.TIM10EN//IsDensity(XL)
#define RCC_APB2ENR_TIM11EN   RCC.APB2ENR_BIT.TIM11EN//IsDensity(XL)
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_APB1ENR        0x00000000//0x01C
struct RCC_APB1ENR_BIT
{
	UINT32 TIM2EN:1;      //00,Timer 2 clock enabled
	UINT32 TIM3EN:1;      //01,Timer 3 clock enabled
	UINT32 TIM4EN:1;      //02,Timer 4 clock enabled,only for !IsDensity(LD) && !IsDensity(LD_VL)
	UINT32 TIM5EN:1;      //03,Timer 5 clock enable,only for IsDensity(HD) || IsDensity(CL) || IsDensity(HD_VL)
	UINT32 TIM6EN:1;      //04,Timer 6 clock enable,only for IsDensity(HD) ||IsDensity(CL)||IsDensity(LD_VL) || defined  (STM32F10X_MD_VL) || IsDensity(HD_VL)
	UINT32 TIM7EN:1;      //05,Timer 7 clock enable,only for IsDensity(HD) ||IsDensity(CL)||IsDensity(LD_VL) || defined  (STM32F10X_MD_VL) || IsDensity(HD_VL)
	UINT32 TIM12EN:1;     //06,Timer 12 clock enable,only for IsDensity(HD_VL)||IsDensity(XL)
	UINT32 TIM13EN:1;     //07,Timer 13 clock enable,only for IsDensity(HD_VL)||IsDensity(XL)
	UINT32 TIM14EN:1;     //08,Timer 14 clock enable,only for IsDensity(HD_VL)||IsDensity(XL)
  UINT32 Reserved4:2;   //09,
  UINT32 WWDGEN:1;      //11,Window Watchdog clock enable
	UINT32 Reserved5:2;   //12,
  UINT32 SPI2EN:1;      //14,SPI 2 clock enable,only for !IsDensity(LD) && !IsDensity(LD_VL)
  UINT32 SPI3EN:1;      //15,SPI 3 clock enable,only for IsDensity(HD) || IsDensity(CL)|| IsDensity(HD_VL)
  UINT32 Reserved8:1;   //16,
  UINT32 USART2EN:1;    //17,USART 2 clock enable
  UINT32 USART3EN:1;    //18,USART 3 clock enable,only for !IsDensity(LD) && !IsDensity(LD_VL)
  UINT32 USART4EN:1;    //19,USART 4 clock enable,only for IsDensity(HD) || IsDensity(CL) 	|| IsDensity(HD_VL)
  UINT32 USART5EN:1;    //20,USART 5 clock enable,only for IsDensity(HD) || IsDensity(CL) 	|| IsDensity(HD_VL)
  UINT32 I2C1EN:1;      //21,I2C 1 clock enable
  UINT32 I2C2EN:1;      //22,I2C 1 clock enable,only for !IsDensity(LD) && !IsDensity(LD_VL)
  UINT32 USBEN:1;       //23,USB Device clock enable,only for  IsDensity(HD) ||IsDensity(MD) || IsDensity(LD)
  UINT32 Reserved12:1;  //24,
  UINT32 CAN1EN:1;      //25,CAN1 clock enable,only for !IsDensity(LD_VL) && !IsDensity(MD_VL) && !IsDensity(HD_VL)
  UINT32 CAN2EN:1;      //26,CAN2 clock enable,only for IsDensity(CL)
  UINT32 BKPEN:1;       //27,Backup interface clock enable
  UINT32 PWREN:1;       //28,Power interface clock enable
  UINT32 DACEN:1;       //29,DAC interface clock enable,only for IsDensity(HD) || IsDensity(CL)||IsDensity(LD_VL) || IsDensity(MD_VL) ||IsDensity(HD_VL)
  UINT32 CECEN:1;       //30,CEC interface clock enable,only for IsDensity(LD_VL) || IsDensity(MD_VL) ||IsDensity(HD_VL)
  UINT32 Reserved17:1;  //31,
};
#define RCC_APB1ENR_TIM2EN    RCC.APB1ENR_BIT.TIM2EN  
#define RCC_APB1ENR_TIM3EN    RCC.APB1ENR_BIT.TIM3EN  
#define RCC_APB1ENR_TIM4EN    RCC.APB1ENR_BIT.TIM4EN  //!IsDensity(LD) && !IsDensity(LD_VL)
#define RCC_APB1ENR_TIM5EN    RCC.APB1ENR_BIT.TIM5EN //IsDensity(HD) || IsDensity(CL) || IsDensity(HD_VL)
#define RCC_APB1ENR_TIM6EN    RCC.APB1ENR_BIT.TIM6EN //IsDensity(HD) ||IsDensity(CL)||IsDensity(LD_VL) || defined  (STM32F10X_MD_VL) || IsDensity(HD_VL)
#define RCC_APB1ENR_TIM7EN    RCC.APB1ENR_BIT.TIM7EN //IsDensity(HD) ||IsDensity(CL)||IsDensity(LD_VL) || defined  (STM32F10X_MD_VL) || IsDensity(HD_VL)
#define RCC_APB1ENR_TIM12EN    RCC.APB1ENR_BIT.TIM12EN //IsDensity(HD_VL)||IsDensity(XL)
#define RCC_APB1ENR_TIM13EN    RCC.APB1ENR_BIT.TIM13EN //IsDensity(HD_VL)||IsDensity(XL)
#define RCC_APB1ENR_TIM14EN    RCC.APB1ENR_BIT.TIM14EN //IsDensity(HD_VL)||IsDensity(XL)
#define RCC_APB1ENR_WWDGEN    RCC.APB1ENR_BIT.WWDGEN
#define RCC_APB1ENR_SPI2EN    RCC.APB1ENR_BIT.SPI2EN//!IsDensity(LD) && !IsDensity(LD_VL)
#define RCC_APB1ENR_SPI3EN    RCC.APB1ENR_BIT.SPI3EN//IsDensity(HD) || IsDensity(CL)|| IsDensity(HD_VL)
#define RCC_APB1ENR_USART2EN  RCC.APB1ENR_BIT.USART2EN
#define RCC_APB1ENR_USART3EN  RCC.APB1ENR_BIT.USART3EN//!IsDensity(LD) && !IsDensity(LD_VL)
#define RCC_APB1ENR_USART4EN  RCC.APB1ENR_BIT.USART4EN//IsDensity(HD) || IsDensity(CL) 	|| IsDensity(HD_VL)
#define RCC_APB1ENR_USART5EN  RCC.APB1ENR_BIT.USART5EN//IsDensity(HD) || IsDensity(CL) 	|| IsDensity(HD_VL)
#define RCC_APB1ENR_I2C1EN  RCC.APB1ENR_BIT.I2C1EN
#define RCC_APB1ENR_I2C2EN  RCC.APB1ENR_BIT.I2C2EN//!IsDensity(LD) && !IsDensity(LD_VL)
#define RCC_APB1ENR_USBEN  RCC.APB1ENR_BIT.USBEN//IsDensity(HD) ||IsDensity(MD) || IsDensity(LD)
#define RCC_APB1ENR_CAN1EN  RCC.APB1ENR_BIT.CAN1EN//!IsDensity(LD_VL) && !IsDensity(MD_VL) && !IsDensity(HD_VL)
#define RCC_APB1ENR_CAN2EN  RCC.APB1ENR_BIT.CAN2EN//IsDensity(CL)
#define RCC_APB1ENR_BKPEN  RCC.APB1ENR_BIT.BKPEN
#define RCC_APB1ENR_PWREN  RCC.APB1ENR_BIT.PWREN
#define RCC_APB1ENR_DACEN  RCC.APB1ENR_BIT.DACEN//IsDensity(HD) || IsDensity(CL)||IsDensity(LD_VL) || IsDensity(MD_VL) ||IsDensity(HD_VL)
#define RCC_APB1ENR_CECEN  RCC.APB1ENR_BIT.CECEN//IsDensity(LD_VL) || IsDensity(MD_VL) ||IsDensity(HD_VL)
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_BDCR             0x00000000//0x020
#define RCC_BDCR_RTCSEL_NOCLOCK         0 //No clock
#define RCC_BDCR_RTCSEL_LSE             1 //LSE oscillator clock used as RTC clock
#define RCC_BDCR_RTCSEL_LSI             2 //LSI oscillator clock used as RTC clock
#define RCC_BDCR_RTCSEL_HSE             3 //HSE oscillator clock divided by 128 used as RTC clock
struct RCC_BDCR_BIT
{
	UINT32 LSEON:1;       //00,External Low Speed oscillator enable
	UINT32 LSERDY:1;      //01,External Low Speed oscillator Ready
	UINT32 LSEBYP:1;      //02,External Low Speed oscillator Bypass
  UINT32 Reserved0:5;   //03,
	UINT32 RTCSEL:2;      //08,RTCSEL[1:0] bits (RTC clock source selection):0=NO,1=LSE,2=LSI,3=HSE/128
	UINT32 Reserved1:5;   //10,
	UINT32 RTCEN:1;       //15,RTC clock enable
	UINT32 BDRST:1;       //16,Backup domain software reset
	UINT32 Reserved2:15;  //17,
};
#define RCC_BDCR_LSEON          RCC.BDCR_BIT.LSEON
#define RCC_BDCR_LSERDY         RCC.BDCR_BIT.LSERDY
#define RCC_BDCR_LSEBYP         RCC.BDCR_BIT.LSEBYP
#define RCC_BDCR_RTCSEL         RCC.BDCR_BIT.RTCSEL
#define RCC_BDCR_RTCEN          RCC.BDCR_BIT.RTCEN
#define RCC_BDCR_BDRST          RCC.BDCR_BIT.BDRST
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_CSR            0x0C000000//0x024
struct RCC_CSR_BIT
{
	UINT32 LSION:1;       //00,Internal Low Speed oscillator enable
	UINT32 LSIRDY:1;      //01,Internal Low Speed oscillator Ready
  UINT32 Reserved0:22;  //02,
	UINT32 RMVF:1;        //24,Remove reset flag
	UINT32 Reserved1:1;   //25,
	UINT32 PINRSTF:1;     //26,PIN reset flag
	UINT32 PORRSTF:1;     //27,POR/PDR reset flag
	UINT32 SFTRSTF:1;     //28,Software Reset flag
	UINT32 IWDGRSTF:1;    //29,Independent Watchdog reset flag
	UINT32 WWDGRSTF:1;    //30,Window watchdog reset flag
	UINT32 LPWRRSTF:1;    //31,Low-Power reset flag
};
#define RCC_CSR_LSION           RCC.CSR_BIT.LSION
#define RCC_CSR_LSIRDY          RCC.CSR_BIT.LSIRDY
#define RCC_CSR_RMVF            RCC.CSR_BIT.RMVF
#define RCC_CSR_PINRSTF         RCC.CSR_BIT.PINRSTF
#define RCC_CSR_PORRSTF         RCC.CSR_BIT.PORRSTF
#define RCC_CSR_SFTRSTF         RCC.CSR_BIT.SFTRSTF
#define RCC_CSR_IWDGRSTF        RCC.CSR_BIT.IWDGRSTF
#define RCC_CSR_WWDGRSTF        RCC.CSR_BIT.WWDGRSTF
#define RCC_CSR_LPWRRSTF        RCC.CSR_BIT.LPWRRSTF
//------------------------------------------------------------------------------------------------------------------------------
#if IsDensity(CL)
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_AHBRSTR          0x0C000000//0x028
struct RCC_AHBRSTR_BIT
{
  UINT32 Reserved0:12;  //00,
	UINT32 OTGFSRST:1;    //12,USB OTG FS reset
	UINT32 Reserved1:1;   //13,
	UINT32 ETHMACRST:1;   //14,ETHERNET MAC reset
	UINT32 Reserved2:17;  //15,
};
union RCC_AHBRSTR_REG//0x028
{
	UINT32                  VAL;
	struct RCC_AHBRSTR_BIT BIT;
};
#define RCC_AHBRSTR_OTGFSRST    RCC.AHBRSTR_BIT.OTGFSRST
#define RCC_AHBRSTR_ETHMACRST   RCC.AHBRSTR_BIT.ETHMACRST
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_CFGR2          0x0C000000//0x02C
struct RCC_CFGR2_BIT
{
  UINT32 PREDIV1:4;     //00,PREDIV1[3:0] bits,PREDIV1 input clock divided: PREDIV1=0_15= by 1_16
	UINT32 PREDIV2:4;     //04,PREDIV2[3:0] bits,PREDIV2 input clock divided: PREDIV2=0_15= by 1_16
	UINT32 PLL2MUL:4;     //08,PLL2MUL[3:0] bits,PLL2 input clock: PLL2MUL=0x06_0x0C= *(PLL2MUL+2),0x0E=*16,0x0F=*20
	UINT32 PLL3MUL:4;     //12,PLL3MUL[3:0] bits,PLL3 input clock: PLL3MUL=0x06_0x0C= *(PLL3MUL+2),0x0E=*16,0x0F=*20 
	UINT32 PREDIV1SRC:1;  //16,PREDIV1 entry clock source:0=HSE,1=PLL2
	UINT32 I2S2SRC:1;     //17,I2S2 entry clock source:0=Sysclk,1=PLL2
	UINT32 I2S3SRC:1;     //18,I2S3 entry clock source:0=Sysclk,1=PLL3
	UINT32 Reserved0:13;  //19,
};
#define RCC_CFGR2_PREDIV1       RCC.CFGR2_BIT.PREDIV1
#define RCC_CFGR2_PREDIV2       RCC.CFGR2_BIT.PREDIV2
#define RCC_CFGR2_PLL2MUL       RCC.CFGR2_BIT.PLL2MUL
#define RCC_CFGR2_PLL3MUL       RCC.CFGR2_BIT.PLL3MUL
#define RCC_CFGR2_PREDIV1SRC    RCC.CFGR2_BIT.PREDIV1SRC
#define RCC_CFGR2_I2S2SRC       RCC.CFGR2_BIT.I2S2SRC
#define RCC_CFGR2_I2S3SRC       RCC.CFGR2_BIT.I2S3SRC
//------------------------------------------------------------------------------------------------------------------------------
#endif
#if IsDensity(LD_VL) || IsDensity(MD_VL) || IsDensity(HD_VL)
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RCC_CFGR2            0x0C000000//0x02C
struct RCC_CFGR2_BIT
{
  UINT32 PREDIV1:4;     //00,PREDIV1[3:0] bits,PREDIV1 input clock divided: PREDIV1=0_15= by 1_16
	UINT32 Reserved0:28;  //04,
};
union RCC_CFGR2_REG//0x02C
{
	UINT32                VAL;
	struct RCC_CFGR2_BIT BIT;
};
#define RCC_CFGR2_PREDIV1       RCC.CFGR2_BIT.PREDIV1
//------------------------------------------------------------------------------------------------------------------------------
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RCC_Struct Struct_RCC
typedef struct Struct_RCC//0x40021000
{
  union{UINT32 CR;struct RCC_CR_BIT CR_BIT;};                  //0x000(RW),
  union{UINT32 CFGR;struct RCC_CFGR_BIT CFGR_BIT;};            //0x004(RW),
  union{UINT32 CIR;struct RCC_CIR_BIT CIR_BIT;};               //0x008(RW),
  union{UINT32 APB2RSTR;struct RCC_APB2RSTR_BIT APB2RSTR_BIT;};//0x00C(RW),
  union{UINT32 APB1RSTR;struct RCC_APB1RSTR_BIT APB1RSTR_BIT;};//0x010(RW),
  union{UINT32 AHBENR;struct RCC_AHBENR_BIT AHBENR_BIT;};      //0x014(RW),
  union{UINT32 APB2ENR;struct RCC_APB2ENR_BIT APB2ENR_BIT;};   //0x018(RW),
  union{UINT32 APB1ENR;struct RCC_APB1ENR_BIT APB1ENR_BIT;};   //0x01C(RW),
  union{UINT32 BDCR;struct RCC_BDCR_BIT BDCR_BIT;};            //0x020(RW),
  union{UINT32 CSR;struct RCC_CSR_BIT CSR_BIT;};               //0x024(RW),
#if IsDensity(CL)  
  union{UINT32 AHBRSTR;struct RCC_AHBRSTR_BIT AHBRSTR_BIT;};   //0x028(RW),
#else
	UINT32 Reserved0[1];  //0x028(R),
#endif
#if IsDensity(CL)||IsDensity(LD_VL)||IsDensity(MD_VL)||IsDensity(HD_VL)
  union{UINT32 CFGR2;struct RCC_CFGR2_BIT CFGR2_BIT;};         //0x02C(RW),
#endif
} RCC_Type,Type_RCC;
#define PT_RCC                  ((volatile Type_RCC *)BASE_RCC)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RCC_CR                  RCC.CR
#define RCC_CFGR                RCC.CFGR
#define RCC_CIR                 RCC.CIR
#define RCC_APB2RSTR            RCC.APB2RSTR
#define RCC_APB1RSTR            RCC.APB1RSTR
#define RCC_AHBENR              RCC.AHBENR
#define RCC_APB2ENR             RCC.APB2ENR
#define RCC_APB1ENR             RCC.APB1ENR
#define RCC_BDCR                RCC.BDCR
#define RCC_CSR                 RCC.CSR
#if IsDensity(CL)
#define RCC_AHBRSTR             RCC.AHBRSTR
#endif
#if IsDensity(CL)||IsDensity(LD_VL)||IsDensity(MD_VL)||IsDensity(HD_VL)
#define RCC_CFGR2               RCC.CFGR2
#endif
//==============================================================================================================================
#define RSTV_RTC_CRH            0x00000000//0x000
struct RTC_CRH_BIT
{
	UINT32 SECIE:1;       //00,Second Interrupt Enable
	UINT32 ALRIE:1;       //01,Alarm Interrupt Enable
	UINT32 OWIE:1;        //02,OverfloW Interrupt Enable
	UINT32 Reserved0:13;  //03,
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_CRL            0x00000020//0x004
struct RTC_CRL_BIT
{
	UINT32 SECF:1;        //00,Second Flag
	UINT32 ALRF:1;        //01,Alarm Flag
	UINT32 OWF:1;         //02,OverfloW Flag
	UINT32 RSF:1;         //03,Registers Synchronized Flag
	UINT32 CNF:1;         //04,Configuration Flag
	UINT32 RTOFF:1;       //05,RTC operation OFF
	UINT32 Reserved0:10;  //06,
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_PRLH           0x00000000//0x008
struct RTC_PRLH_BIT
{
	UINT32 PRL:4;         //00,RTC Prescaler Reload Value High,<LDY>
	UINT32 Reserved0:12;  //04,
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_PRLL           0x00008000//0x00C
struct RTC_PRLL_BIT
{
	UINT32 PRL:16;        //00,RTC Prescaler Reload Value Low
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_DIVH           0x00000000//0x010
struct RTC_DIVH_BIT
{
	UINT32 DIV:4;         //00,RTC Clock Divider High,<LDY>
	UINT32 Reserved0:12;  //04,
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_DIVL           0x00000000//0x014
struct RTC_DIVL_BIT
{
	UINT32 DIV:16;        //00,RTC Clock Divider Low
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_CNTH           0x00000000//0x018
struct RTC_CNTH_BIT
{
	UINT32 CNT:16;        //00,RTC Counter High
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_CNTL           0x00000000//0x01C
struct RTC_CNTL_BIT
{
	UINT32 CNT:16;        //00,RTC Counter Low
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_ALRH           0x00000000//0x020
struct RTC_ALRH_BIT
{
	UINT32 ALR:16;        //00,RTC Alarm High
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_RTC_ALRL           0x00000000//0x024
struct RTC_ALRL_BIT
{
	UINT32 ALR:16;        //00,RTC Alarm Low
	UINT32 Reserved0:16;  //16,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RTC_Struct Struct_RTC
typedef struct Struct_RTC//0x40002800
{
  union{UINT32 CRH;struct RTC_CRH_BIT CRH_BIT;};//0x000(RW),
  union{UINT32 CRL;struct RTC_CRH_BIT CRL_BIT;};//0x004(RW),
  union{UINT32 PRLH;struct RTC_PRLH_BIT PRLH_BIT;};//0x008(RW),
  union{UINT32 PRLL;struct RTC_PRLL_BIT PRLL_BIT;};//0x00C(RW),
  union{UINT32 DIVH;struct RTC_DIVH_BIT DIVH_BIT;};//0x010(RW),
  union{UINT32 DIVL;struct RTC_DIVL_BIT DIVL_BIT;};//0x014(RW),
  union{UINT32 CNTH;struct RTC_CNTH_BIT CNTH_BIT;};//0x018(RW),
  union{UINT32 CNTL;struct RTC_CNTL_BIT CNTL_BIT;};//0x01C(RW),
  union{UINT32 ALRH;struct RTC_ALRH_BIT ALRH_BIT;};//0x020(RW),
  union{UINT32 ALRL;struct RTC_ALRL_BIT ALRL_BIT;};//0x024(RW),
} RTC_Type,Type_RTC;
#define PT_RTC                  ((volatile Type_RTC *)BASE_RTC)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RTC_CRH                 RTC.CRH
#define RTC_CRL                 RTC.CRL
#define RTC_PRLH                RTC.PRLH
#define RTC_PRLL                RTC.PRLL
#define RTC_DIVH                RTC.DIVH
#define RTC_DIVL                RTC.DIVL
#define RTC_CNTH                RTC.CNTH
#define RTC_CNTL                RTC.CNTL
#define RTC_ALRH                RTC.ALRH
#define RTC_ALRL                RTC.ALRL
//==============================================================================================================================
#define RSTV_SDIO_POWER         0x00000000//0x000
struct SDIO_POWER_BIT
{
	UINT32 PWRCTRL:2;     //00,PWRCTRL[1:0] bits (Power supply control bits)
	UINT32 Reserved0:30;  //02,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_CLKCR         0x00000000//0x004
struct SDIO_CLKCR_BIT
{
	UINT32 CLKDIV:8;      //00,Clock divide factor
	UINT32 CLKEN:1;       //08,Clock enable bit
	UINT32 PWRSAV:1;      //09,Power saving configuration bit
	UINT32 BYPASS:1;      //10,Clock divider bypass enable bit
	UINT32 WIDBUS:2;      //11,WIDBUS[1:0] bits (Wide bus mode enable bit)
	UINT32 NEGEDGE:1;     //13,SDIO_CK dephasing selection bit
	UINT32 HWFCEN:1;      //14,HW Flow Control enable
	UINT32 Reserved0:17;  //15,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_ARG           0x00000000//0x008,bit0_31=CMDARG=Command argument
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_CMD           0x00000000//0x00C
struct SDIO_CMD_BIT
{
	UINT32 CMDINDEX:6;    //00,Command Index
	UINT32 WAITRESP:2;    //06,WAITRESP[1:0] bits (Wait for response bits)
	UINT32 WAITINT:1;     //08,CPSM Waits for Interrupt Request
	UINT32 WAITPEND:1;    //09,CPSM Waits for ends of data transfer (CmdPend internal signal)
	UINT32 CPSMEN:1;      //10,Command path state machine (CPSM) Enable bit
	UINT32 SDIOSUSPEND:1; //11,SD I/O suspend command
	UINT32 ENCMDCOMPL:1;  //12,Enable CMD completion
	UINT32 NIEN:1;        //13,Not Interrupt Enable
	UINT32 CEATACMD:1;    //14,CE-ATA command
	UINT32 Reserved0:17;  //15,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_RESPCMD       0x00000000//0x010
struct SDIO_RESPCMD_BIT
{
	UINT32 RESPCMD:6;    //00,Response command index
	UINT32 Reserved0:26; //06,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_RESP1           0x00000000//0x014,bit0_31=CARDSTATUS=Card Status
#define RSTV_SDIO_RESP2           0x00000000//0x018,bit0_31=CARDSTATUS=Card Status
#define RSTV_SDIO_RESP3           0x00000000//0x01C,bit0_31=CARDSTATUS=Card Status
#define RSTV_SDIO_RESP4           0x00000000//0x020,bit0_31=CARDSTATUS=Card Status
#define RSTV_SDIO_RESP            0x00000000
#define RSTV_SDIO_DTIMER          0x00000000//0x024,bit0_31=DATATIME=Data timeout period
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_DLEN            0x00000000//0x028
struct SDIO_DLEN_BIT
{
	UINT32 DATALENGTH:25; //00,Data length value
	UINT32 Reserved0:7;   //25,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_DCTRL           0x00000000//0x02C
struct SDIO_DCTRL_BIT
{
	UINT32 DTEN:1;        //00,Data transfer enabled bit
	UINT32 DTDIR:1;       //01,Data transfer direction selection
	UINT32 DTMODE:1;      //02,Data transfer mode selection
	UINT32 DMAEN:1;       //03,DMA enabled bit
	UINT32 DBLOCKSIZE:4;  //04,DBLOCKSIZE[3:0] bits (Data block size)
	UINT32 RWSTART:1;     //08,Read wait start
	UINT32 RWSTOP:1;      //09,Read wait stop
	UINT32 RWMOD:1;       //10,Read wait mode
	UINT32 SDIOEN:1;      //11,SD I/O enable functions
	UINT32 Reserved0:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_DCOUNT          0x00000000//0x030
struct SDIO_DCOUNT_BIT
{
	UINT32 DATACOUNT:25;  //00,Data count value
	UINT32 Reserved0:7;   //25,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_STA             0x00000000//0x034
#define RSTV_SDIO_ICR             0x00000000//0x038
#define RSTV_SDIO_MASK            0x00000000//0x03C
struct SDIO_INT_BIT//0x034=STA,0x38=ICR(bit11_21=Reserved),0x3C=MASK
{
	UINT32 CCRCFAIL:1;    //00,Command response received (CRC check failed)
	UINT32 DCRCFAIL:1;    //01,Data block sent/received (CRC check failed)
	UINT32 CTIMEOUT:1;    //02,Command response timeout
	UINT32 DTIMEOUT:1;    //03,Data timeout
	UINT32 TXUNDERR:1;    //04,Transmit FIFO underrun error
	UINT32 RXOVERR:1;     //05,Received FIFO overrun error
	UINT32 CMDREND:1;     //06,Command response received (CRC check passed)
	UINT32 CMDSENT:1;     //07,Command sent (no response required)
	UINT32 DATAEND:1;     //08,Data end (data counter, SDIDCOUNT, is zero)
	UINT32 STBITERR:1;    //09,Start bit not detected on all data signals in wide bus mode
	UINT32 DBCKEND:1;     //10,Data block sent/received (CRC check passed)
	UINT32 CMDACT:1;      //11,Command transfer in progress
	UINT32 TXACT:1;       //12,Data transmit in progress
	UINT32 RXACT:1;       //13,Data receive in progress
	UINT32 TXFIFOHE:1;    //14,Transmit FIFO Half Empty: at least 8 words can be written into the FIFO
	UINT32 RXFIFOHF:1;    //15,Receive FIFO Half Full: there are at least 8 words in the FIFO
	UINT32 TXFIFOF:1;     //16,Transmit FIFO full
	UINT32 RXFIFOF:1;     //17,Receive FIFO full
	UINT32 TXFIFOE:1;     //18,Transmit FIFO empty
	UINT32 RXFIFOE:1;     //19,Receive FIFO empty
	UINT32 TXDAVL:1;      //20,Data available in transmit FIFO
	UINT32 RXDAVL:1;      //21,Data available in receive FIFO
	UINT32 SDIOIT:1;      //22,SDIO interrupt received
	UINT32 CEATAEND:1;    //23,CE-ATA command completion signal received for CMD61
	UINT32 Reserved0:8;   //24,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_FIFOCNT         0x00000000//0x048
struct SDIO_FIFOCNT_BIT
{
	UINT32 FIFOCOUNT:24;  //00,Remaining number of words to be written to or read from the FIFO
	UINT32 Reserved0:8;   //24,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SDIO_FIFO            0x00000000//0x080,bit0_31=FIFODATA=Receive and transmit FIFO data
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SDIO_Struct Struct_SDIO
typedef struct Struct_SDIO//0x40018000
{
  union{UINT32 POWER;struct SDIO_POWER_BIT POWER_BIT;};//0x000(RW),
  union{UINT32 CLKCR;struct SDIO_CLKCR_BIT CLKCR_BIT;};//0x004(RW),
  union{UINT32 ARG;Type_BIT32 ARG_BIT;};//0x008(RW),
  union{UINT32 CMD;struct SDIO_CMD_BIT CMD_BIT;};//0x00C(RW),
  union{UINT32 RESPCMD;struct SDIO_RESPCMD_BIT RESPCMD_BIT;};//0x010(R),
  union{UINT32 RESP1;Type_BIT32 RESP1_BIT;};//0x014(R),
  union{UINT32 RESP2;Type_BIT32 RESP2_BIT;};//0x018(R),
  union{UINT32 RESP3;Type_BIT32 RESP3_BIT;};//0x01C(R),
  union{UINT32 RESP4;Type_BIT32 RESP4_BIT;};//0x020(R),
  union{UINT32 DTIMER;Type_BIT32 DTIMER_BIT;};//0x024(RW),
  union{UINT32 DLEN;struct SDIO_DLEN_BIT DLEN_BIT;};//0x028(RW),
  union{UINT32 DCTRL;struct SDIO_DCTRL_BIT DCTRL_BIT;};//0x02C(RW),
  union{UINT32 DCOUNT;struct SDIO_DCOUNT_BIT DCOUNT_BIT;};//0x030(R),
  union{UINT32 STA;struct SDIO_INT_BIT STA_BIT;};//0x034(R),
  union{UINT32 ICR;struct SDIO_INT_BIT ICR_BIT;};//0x038(RW),
  union{UINT32 MASK;struct SDIO_INT_BIT MASK_BIT;};//0x03C(RW),
  UINT32 Reserved0[2];  //0x040(R),
  union{UINT32 FIFOCNT;struct SDIO_FIFOCNT_BIT FIFOCNT_BIT;};//0x048(R),
  UINT32 Reserved1[13]; //0x04C(R),
  union{UINT32 FIFO;Type_BIT32 FIFO_BIT;};//0x080(RW),
} SDIO_Type,Type_SDIO;
#define PT_SDIO                 ((volatile Type_SDIO *)BASE_SDIO)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SDIO_POWER              SDIO.POWER
#define SDIO_CLKCR              SDIO.CLKCR
#define SDIO_ARG                SDIO.ARG
#define SDIO_CMD                SDIO.CMD
#define SDIO_RESPCMD            SDIO.RESPCMD
#define SDIO_RESP1              SDIO.RESP1
#define SDIO_RESP2              SDIO.RESP2
#define SDIO_RESP3              SDIO.RESP3
#define SDIO_RESP4              SDIO.RESP4
#define SDIO_DTIMER             SDIO.DTIMER
#define SDIO_DLEN               SDIO.DLEN
#define SDIO_DCTRL              SDIO.DCTRL
#define SDIO_DCOUNT             SDIO.DCOUNT
#define SDIO_STA                SDIO.STA
#define SDIO_ICR                SDIO.ICR
#define SDIO_MASK               SDIO.MASK
#define SDIO_FIFOCNT            SDIO.FIFOCNT
#define SDIO_FIFO               SDIO.FIFO
//==============================================================================================================================
#define RSTV_SPI_CR1            0x00000000//0x000
struct SPI_CR1_BIT
{
	UINT32 CPHA:1;        //00,Clock Phase:0=first,1=second
	UINT32 CPOL:1;        //01,Clock Polarity,while idle CK level:0=CK_Low,1=CK_High
	UINT32 MSTR:1;        //02,Master Selection:0=Slave,1=Master
	UINT32 BR:3;          //03,BR[2:0] bits (Baud Rate Control)  FCLK div:0_7=/2^(BR+1)
	UINT32 SPE:1;         //06,SPI Enable:1=Enable
	UINT32 LSBFIRST:1;    //07,Frame Format,transfer first at:0=MSB ,1=LSB
	UINT32 SSI:1;         //08,Internal slave select,while SSM=1,PIN_NSS=SSI
	UINT32 SSM:1;         //09,Software slave management:1=Enable
	UINT32 RXONLY:1;      //10,Receive only:0=Full,1=RXonly
	UINT32 DFF:1;         //11,Data Frame Format:0=8bit,1=16bit
	UINT32 CRCNEXT:1;     //12,Transmit CRC next:1=next is CRC,0=next is data
	UINT32 CRCEN:1;       //13,Hardware CRC calculation enable:1=enable
	UINT32 BIDIOE:1;      //14,Output enable in bidirectional mode:0=Rx,1=TX
	UINT32 BIDIMODE:1;    //15,Bidirectional data mode enable:0=2-line unbidirectional,1=1-line bidirectional
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SPI_CR2            0x00000000//0x004
struct SPI_CR2_BIT
{
	UINT32 RXDMAEN:1;     //00,Rx Buffer DMA Enable:1=Enable
	UINT32 TXDMAEN:1;     //01,Tx Buffer DMA Enable:1=Enable
	UINT32 SSOE:1;        //02,SS Output Enable:1=Enable
	UINT32 Reserved0:2;   //03,
	UINT32 ERRIE:1;       //05,Error Interrupt Enable:1=Enable
	UINT32 RXNEIE:1;      //06,RX buffer Not Empty Interrupt Enable:1=Enable
	UINT32 TXEIE:1;       //07,Tx buffer Empty Interrupt Enable:1=Enable
	UINT32 Reserved1:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SPI_SR             0x00000002//0x008
struct SPI_SR_BIT
{
	UINT32 RXNE:1;        //00,Receive buffer Not Empty
	UINT32 TXE:1;         //01,Transmit buffer Empty
	UINT32 CHSIDE:1;      //02,Channel side:0=left,1=right
	UINT32 UDR:1;         //03,Underrun flag
	UINT32 CRCERR:1;      //04,CRC Error flag
	UINT32 MODF:1;        //05,Mode fault
	UINT32 OVR:1;         //06,Overrun flag
	UINT32 BSY:1;         //07,Busy flag
	UINT32 Reserved1:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SPI_DR             0x00000000//0x00C,Data Register
#define RSTV_SPI_CRCPR          0x00000007//0x010,CRC polynomial register
#define RSTV_SPI_RXCRCR         0x00000000//0x014,Rx CRC Register
#define RSTV_SPI_TXCRCR         0x00000000//0x018,Tx CRC Register
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SPI_I2SCFGR        0x00000000//0x01C
struct SPI_I2SCFGR_BIT
{
	UINT32 CHLEN:1;       //00,Channel length (number of bits per audio channel)
	UINT32 DATLEN:2;      //01,DATLEN[1:0] bits (Data length to be transferred)
	UINT32 CKPOL:1;       //03,steady state clock polarity
	UINT32 I2SSTD:2;      //04,I2SSTD[1:0] bits (I2S standard selection)
	UINT32 Reserved0:1;   //06,
	UINT32 PCMSYNC:1;     //07,PCM frame synchronization
	UINT32 I2SCFG:2;      //08,I2SCFG[1:0] bits (I2S configuration mode)
	UINT32 I2SE:1;        //10,I2S Enable
	UINT32 I2SMOD:1;      //11,I2S mode selection
	UINT32 Reserved1:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SPI_I2SPR          0x00000000//0x020,<LDY>
struct SPI_I2SPR_BIT
{
	UINT32 I2SDIV:8;      //00,I2S Linear prescaler
	UINT32 ODD:1;         //08,Odd factor for the prescaler
	UINT32 MCKOE:1;       //09,Master Clock Output Enable
	UINT32 Reserved0:22;  //10,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SPI_Struct Struct_SPI
typedef struct Struct_SPI//0x40013000=SPI1,0x40003800=SPI2,0x40003C00=SPI3
{
  union{UINT32 CR1;struct SPI_CR1_BIT CR1_BIT;};                //0x000(RW),SPI control register 1 (not used in I2S mode)
  union{UINT32 CR2;struct SPI_CR2_BIT CR2_BIT;};                //0x004(RW),SPI control register 2
  union{UINT32 SR;struct SPI_SR_BIT SR_BIT;};                   //0x008(RW),SPI status register
  union{UINT32 DR;Type_UINT32_BIT16 DR_BIT;};                   //0x00C(RW),SPI data register
  union{UINT32 CRCPR;Type_UINT32_BIT16 CRCPR_BIT;};             //0x010(RW),SPI CRC polynomial register (not used in I2S mode)
  union{UINT32 RXCRCR;Type_UINT32_BIT16 RXCRCR_BIT;};           //0x014(RW),SPI RX CRC register (not used in I2S mode)
  union{UINT32 TXCRCR;Type_UINT32_BIT16 TXCRCR_BIT;};           //0x018(RW),SPI TX CRC register (not used in I2S mode)
  union{UINT32 I2SCFGR;struct SPI_I2SCFGR_BIT I2SCFGR_BIT;};    //0x01C(RW),SPI_I2S configuration register
  union{UINT32 I2SPR;struct SPI_I2SPR_BIT I2SPR_BIT;};          //0x020(RW),SPI_I2S prescaler register
} SPI_Type,Type_SPI;
#define PT_SPI1                 ((volatile Type_SPI *)BASE_SPI1)
#define PT_SPI2                 ((volatile Type_SPI *)BASE_SPI2)
#define PT_SPI3                 ((volatile Type_SPI *)BASE_SPI3)
#define PT_SPI(i)               ((volatile Type_SPI *)BASE_SPI[i])
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SPI_CR1(i)              (*SPI[i]).CR1//i=0_2
#define SPI_CR2(i)              (*SPI[i]).CR2
#define SPI_SR(i)               (*SPI[i]).SR
#define SPI_DR(i)               (*SPI[i]).DR
#define SPI_CRCPR(i)            (*SPI[i]).CRCPR
#define SPI_RXCRCR(i)           (*SPI[i]).RXCRCR
#define SPI_TXCRCR(i)           (*SPI[i]).TXCRCR
#define SPI_I2SCFGR(i)          (*SPI[i]).I2SCFGR
#define SPI_I2SPR(i)            (*SPI[i]).I2SPR
//==============================================================================================================================
#define RSTV_TIM_CR1            0x00000000//0x000
struct TIM_CR1_BIT
{
	UINT32 CEN:1;         //00,Counter enable.0= Counter disabled,1= Counter enabled
	UINT32 UDIS:1;        //01,Update disable.0= UEV enabled. The Update (UEV) event is generated by one of the following events:\
                           – Counter overflow/underflow;– Setting the UG bit;– Update generation through the slave mode controller\
                           Buffered registers are then loaded with their preload values.\
                           1= UEV disabled. The Update event is not generated, shadow registers keep their value\
                             (ARR, PSC, CCRx). However the counter and the prescaler are reinitialized if the UG bit is\
                             set or if a hardware reset is received from the slave mode controller.
	UINT32 URS:1;         //02,Update request source.0= Any of the following events generate an update interrupt or DMA request if enabled.\
                             These events can be: – Counter overflow/underflow; – Setting the UG bit; – Update generation through the slave mode controller\
                             1= Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
	UINT32 OPM:1;         //03,One pulse mode.0= Counter is not stopped at update event,1= Counter stops counting at the next update event (clearing the bit CEN)
	UINT32 DIR:1;         //04,Direction.0= Counter used as upcounter,1= Counter used as downcounter
	UINT32 CMS:2;         //05,CMS[1:0] bits (Center-aligned mode selection).\
                           0= Edge-aligned mode. The counter counts up or down depending on the direction bit(DIR).\
                           1= Center-aligned mode 1. The counter counts up and down alternatively. Output compare interrupt flags of channels configured\
                              in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting down.\
                           2= Center-aligned mode 2. The counter counts up and down alternatively. Output compare interrupt flags of channels configured\
                             in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting up.\
                           3= Center-aligned mode 3. The counter counts up and down alternatively. Output compare interrupt flags of channels configured\
                             in output (CCxS=00 in TIMx_CCMRx register) are set both when the counter is counting up or down.
	UINT32 ARPE:1;        //07,Auto-reload preload enable.0= TIMx_ARR register is not buffered,1= TIMx_ARR register is buffered
	UINT32 CKD:2;         //08,CKD[1:0] bits (clock division).0= tDTS=tCK_INT, 1= tDTS=2*tCK_INT,2= tDTS=4*tCK_INT,3= Reserved, do not program this value
	UINT32 Reserved0:22;  //10,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_CR2            0x00000000//0x004
struct TIM_CR2_BIT
{
	UINT32 CCPC:1;        //00,Capture/Compare Preloaded Control
	UINT32 Reserved0:1;   //01,
	UINT32 CCUS:1;        //02,Capture/Compare Control Update Selection
	UINT32 CCDS:1;        //03,Capture/Compare DMA Selection
	UINT32 MMS:3;         //04,MMS[2:0] bits (Master Mode Selection)
	UINT32 TI1S:1;        //07,TI1 Selection
	UINT32 OIS1:1;        //08,Output Idle state 1 (OC1 output)
	UINT32 OIS1N:1;       //09,Output Idle state 1 (OC1N output)
	UINT32 OIS2:1;        //10,Output Idle state 2 (OC1 output)
	UINT32 OIS2N:1;       //11,Output Idle state 2 (OC1N output)
	UINT32 OIS3:1;        //12,Output Idle state 3 (OC1 output)
	UINT32 OIS3N:1;       //13,Output Idle state 3 (OC1N output)
	UINT32 OIS4:1;        //14,Output Idle state 4 (OC1 output)
	UINT32 Reserved1:17;  //15,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_SMCR           0x00000000//0x008
struct TIM_SMCR_BIT
{
	UINT32 SMS:3;         //00,SMS[2:0] bits (Slave mode selection)
	UINT32 Reserved0:1;   //03,
	UINT32 TS:3;          //04,TS[2:0] bits (Trigger selection)
	UINT32 MSM:1;         //07,Master/slave mode
	UINT32 ETF:4;         //08,ETF[3:0] bits (External trigger filter)
	UINT32 ETPS:2;        //12,ETPS[1:0] bits (External trigger prescaler)
	UINT32 ECE:1;         //14,External clock enable
	UINT32 ETP:1;         //15,External trigger polarity
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_DIER           0x00000000//0x00C
struct TIM_DIER_BIT
{
	UINT32 UIE:1;         //00,Update interrupt enable
	UINT32 CC1IE:1;       //01,Capture/Compare 1 interrupt enable
	UINT32 CC2IE:1;       //02,Capture/Compare 2 interrupt enable
	UINT32 CC3IE:1;       //03,Capture/Compare 3 interrupt enable
	UINT32 CC4IE:1;       //04,Capture/Compare 4 interrupt enable
	UINT32 COMIE:1;       //05,COM interrupt enable
	UINT32 TIE:1;         //06,Trigger interrupt enable
	UINT32 BIE:1;         //07,Break interrupt enable
	UINT32 UDE:1;         //08,Update DMA request enable
	UINT32 CC1DE:1;       //09,Capture/Compare 1 DMA request enable
	UINT32 CC2DE:1;       //10,Capture/Compare 2 DMA request enable
	UINT32 CC3DE:1;       //11,Capture/Compare 3 DMA request enable
	UINT32 CC4DE:1;       //12,Capture/Compare 4 DMA request enable
	UINT32 COMDE:1;       //13,COM DMA request enable
	UINT32 TDE:1;         //14,Trigger DMA request enable
	UINT32 Reserved0:17;  //15,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_SR             0x00000000//0x010
struct TIM_SR_BIT
{
	UINT32 UIF:1;         //00,Update interrupt Flag
	UINT32 CC1IF:1;       //01,Capture/Compare 1 interrupt Flag
	UINT32 CC2IF:1;       //02,Capture/Compare 2 interrupt Flag
	UINT32 CC3IF:1;       //03,Capture/Compare 3 interrupt Flag
	UINT32 CC4IF:1;       //04,Capture/Compare 4 interrupt Flag
	UINT32 COMIF:1;       //05,COM interrupt Flag
	UINT32 TIF:1;         //06,Trigger interrupt Flag
	UINT32 BIF:1;         //07,Break interrupt Flag
	UINT32 Reserved0:1;   //08,
	UINT32 CC1OF:1;       //09,Capture/Compare 1 Overcapture Flag
	UINT32 CC2OF:1;       //10,Capture/Compare 2 Overcapture Flag
	UINT32 CC3OF:1;       //11,Capture/Compare 3 Overcapture Flag
	UINT32 CC4OF:1;       //12,Capture/Compare 4 Overcapture Flag
	UINT32 Reserved1:19;  //13,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_EGR            0x00000000//0x014
struct TIM_EGR_BIT
{
	UINT32 UG:1;          //00,Update Generation
	UINT32 CC1G:1;        //01,Capture/Compare 1 Generation
	UINT32 CC2G:1;        //02,Capture/Compare 2 Generation
	UINT32 CC3G:1;        //03,Capture/Compare 3 Generation
	UINT32 CC4G:1;        //04,Capture/Compare 4 Generation
	UINT32 COMG:1;        //05,Capture/Compare Control Update Generation
	UINT32 TG:1;          //06,Trigger Generationag
	UINT32 BG:1;          //07,Break Generation
	UINT32 Reserved0:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_CCMR1          0x00000000//0x018
#define RSTV_TIM_CCMR2          0x00000000//0x01C
struct TIM_CCMR_BITO//0x018=CCMR1,0x01C=CCMR2
{
	UINT32 CC1S:2;        //00,CC1S[1:0] bits (Capture/Compare 1 Selection)
	UINT32 OC1FE:1;       //02,Output Compare 1 Fast enable
	UINT32 OC1PE:1;       //03,Output Compare 1 Preload enable
	UINT32 OC1M:3;        //04,OC1M[2:0] bits (Output Compare 1 Mode)
	UINT32 OC1CE:1;       //07,Output Compare 1Clear Enable
	UINT32 CC2S:2;        //08,CC2S[1:0] bits (Capture/Compare 2 Selection)
	UINT32 OC2FE:1;       //10,Output Compare 2 Fast enable
	UINT32 OC2PE:1;       //11,Output Compare 2 Preload enable
	UINT32 OC2M:3;        //12,OC2M[2:0] bits (Output Compare 2 Mode)
	UINT32 OC2CE:1;       //15,Output Compare 2 Clear Enable
	UINT32 Reserved0:16;  //16,
};
struct TIM_CCMR_BITI//0x018=CCMR1,0x01C=CCMR2
{
	UINT32 CC1S:2;        //00,CC1S[1:0] bits (Capture/Compare 1 Selection)
	UINT32 IC1PSC:2;      //02,IC1PSC[1:0] bits (Input Capture 1 Prescaler)
	UINT32 IC1F:4;        //04,IC1F[3:0] bits (Input Capture 1 Filter)
	UINT32 CC2S:2;        //08,CC2S[1:0] bits (Capture/Compare 2 Selection)
	UINT32 IC2PSC:2;      //10,IC2PSC[1:0] bits (Input Capture 2 Prescaler)
	UINT32 IC2F:4;        //12,IC2F[3:0] bits (Input Capture 2 Filter)
	UINT32 Reserved0:16;  //16,
};
#define TIM_CCMR_OCXM_FROZEN    0
#define TIM_CCMR_OCXM_SETH      1
#define TIM_CCMR_OCXM_SETL      2
#define TIM_CCMR_OCXM_TOGLE     3
#define TIM_CCMR_OCXM_FORCEL    4
#define TIM_CCMR_OCXM_FORCEH    5
#define TIM_CCMR_OCXM_PWM1      6
#define TIM_CCMR_OCXM_PWM2      7
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_CCER           0x00000000//0x020
struct TIM_CCER_BIT
{
	UINT32 CC1E:1;        //00,Capture/Compare 1 output enable
	UINT32 CC1P:1;        //01,Capture/Compare 1 output Polarity
	UINT32 CC1NE:1;       //02,Capture/Compare 1 Complementary output enable
	UINT32 CC1NP:1;       //03,Capture/Compare 1 Complementary output Polarity
	UINT32 CC2E:1;        //04,Capture/Compare 2 output enable
	UINT32 CC2P:1;        //05,Capture/Compare 2 output Polarity
	UINT32 CC2NE:1;       //06,Capture/Compare 2 Complementary output enable
	UINT32 CC2NP:1;       //07,Capture/Compare 2 Complementary output Polarity
	UINT32 CC3E:1;        //08,Capture/Compare 3 output enable
	UINT32 CC3P:1;        //09,Capture/Compare 3 output Polarity
	UINT32 CC3NE:1;       //10,Capture/Compare 3 Complementary output enable
	UINT32 CC3NP:1;       //11,Capture/Compare 3 Complementary output Polarity
	UINT32 CC4E:1;        //12,Capture/Compare 4 output enable
	UINT32 CC4P:1;        //13,Capture/Compare 4 output Polarity
	UINT32 CC4NE:1;       //14,Capture/Compare 4 Complementary output enable,<LDY>
	UINT32 CC4NP:1;       //15,Capture/Compare 4 Complementary output Polarity,<LDY>
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_CNT            0x00000000//0x024
struct TIM_CNT_BIT
{
	UINT32 CNT:16;        //00,Counter Value
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_PSC            0x00000000//0x028
struct TIM_PSC_BIT
{
	UINT32 PSC:16;        //00,Prescaler Value:CLK_TIMx/(PSC+1)
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_ARR            0x00000000//0x02C
struct TIM_ARR_BIT
{
	UINT32 ARR:16;        //00,actual auto-reload Value
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_RCR              0x00000000//0x030
struct TIM_RCR_BIT
{
	UINT32 REP:8;         //00,Repetition Counter Value
	UINT32 Reserved0:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_CCR1             0x00000000//0x034
#define RSTV_TIM_CCR2             0x00000000//0x038
#define RSTV_TIM_CCR3             0x00000000//0x03C
#define RSTV_TIM_CCR4             0x00000000//0x040
#define RSTV_TIM_CCR              0x00000000
struct TIM_CCR_BIT//0x034=CCR1,0x38=CCR2,0x3C=CCR3,0x40=CCR4
{
	UINT32 CCR:16;        //00,Capture/Compare 1_4 Value
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_BDTR             0x00000000//0x044
struct TIM_BDTR_BIT
{
	UINT32 DTG:8;         //00,DTG[0:7] bits (Dead-Time Generator set-up)
	UINT32 LOCK:2;        //08,LOCK[1:0] bits (Lock Configuration)
	UINT32 OSSI:1;        //10,Off-State Selection for Idle mode
	UINT32 OSSR:1;        //11,Off-State Selection for Run mode
	UINT32 BKE:1;         //12,Break enable
	UINT32 BKP:1;         //13,Break Polarity
	UINT32 AOE:1;         //14,Automatic Output enable
	UINT32 MOE:1;         //15,Main Output enable
	UINT32 Reserved0:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_DCR              0x00000000//0x048
struct TIM_DCR_BIT
{
	UINT32 DBA:5;         //00,DBA[4:0] bits (DMA Base Address)
	UINT32 Reserved0:3;   //05,
	UINT32 DBL:5;         //08,DBL[4:0] bits (DMA Burst Length)
	UINT32 Reserved1:19;  //13,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_TIM_DMAR           0x00000000//0x04C,bit0_15=DMA register for burst accesses
struct TIM_DMAR_BIT
{
	UINT32 DMAB:16;       //00,
	UINT32 Reserved0:16;  //16,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define TIM_Struct Struct_TIM
typedef struct Struct_TIM//0x40012C00=TIM1,0x40000000(Step=0x400)=TIM2_7,...
{
  union{UINT32 CR1;struct TIM_CR1_BIT CR1_BIT;};        //0x000(RW),
  union{UINT32 CR2;struct TIM_CR2_BIT CR2_BIT;};        //0x004(RW),
  union{UINT32 SMCR;struct TIM_SMCR_BIT SMCR_BIT;};     //0x008(RW),
  union{UINT32 DIER;struct TIM_DIER_BIT DIER_BIT;};     //0x00C(RW),
  union{UINT32 SR;struct TIM_SR_BIT SR_BIT;};           //0x010(RW),
  union{UINT32 EGR;struct TIM_EGR_BIT EGR_BIT;};        //0x014(RW),
  union{UINT32 CCMR[2];struct TIM_CCMR_BITO CCMR_BITO[2];struct TIM_CCMR_BITI CCMR_BITI[2];}; //0x018(RW),
  union{UINT32 CCER;struct TIM_CCER_BIT CCER_BIT;};     //0x020(RW),
  union{UINT32 CNT;struct TIM_CNT_BIT CNT_BIT;};        //0x024(RW),
  union{UINT32 PSC;struct TIM_PSC_BIT PSC_BIT;};        //0x028(RW),
  union{UINT32 ARR;struct TIM_ARR_BIT ARR_BIT;};        //0x02C(RW),
  union{UINT32 RCR;struct TIM_RCR_BIT RCR_BIT;};        //0x030(RW),
  union{UINT32 CCR[4];struct TIM_CCR_BIT CCR_BIT[4];};  //0x034(RW),
  union{UINT32 BDTR;struct TIM_BDTR_BIT BDTR_BIT;};     //0x044(RW),
  union{UINT32 DCR;struct TIM_DCR_BIT DCR_BIT;};        //0x048(RW),
  union{UINT32 DMAR;struct TIM_DMAR_BIT DMAR_BIT;};     //0x04C(RW),
} TIM_Type,Type_TIM;
#define PT_TIM1                 ((volatile Type_TIM *)BASE_TIM1)
#define PT_TIM2                 ((volatile Type_TIM *)BASE_TIM2)
#define PT_TIM3                 ((volatile Type_TIM *)BASE_TIM3)
#define PT_TIM4                 ((volatile Type_TIM *)BASE_TIM4)
#define PT_TIM5                 ((volatile Type_TIM *)BASE_TIM5)
#define PT_TIM6                 ((volatile Type_TIM *)BASE_TIM6)
#define PT_TIM7                 ((volatile Type_TIM *)BASE_TIM7)
#define PT_TIM8                 ((volatile Type_TIM *)BASE_TIM8)
#define PT_TIM9                 ((volatile Type_TIM *)BASE_TIM9)
#define PT_TIM10                ((volatile Type_TIM *)BASE_TIM10)
#define PT_TIM11                ((volatile Type_TIM *)BASE_TIM11)
#define PT_TIM12                ((volatile Type_TIM *)BASE_TIM12)
#define PT_TIM13                ((volatile Type_TIM *)BASE_TIM13)
#define PT_TIM14                ((volatile Type_TIM *)BASE_TIM14)
#define PT_TIM15                ((volatile Type_TIM *)BASE_TIM15)
#define PT_TIM16                ((volatile Type_TIM *)BASE_TIM16)
#define PT_TIM17                ((volatile Type_TIM *)BASE_TIM17)
#define PT_TIM(i)               ((volatile Type_TIM *)BASE_TIM[i])
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define TIM_CR1(i)              (*TIM[i]).CR1//i=0_16
#define TIM_CR2(i)              (*TIM[i]).CR2//i=0_16
#define TIM_SMCR(i)             (*TIM[i]).SMCR//i=0_16
#define TIM_DIER(i)             (*TIM[i]).DIER//i=0_16
#define TIM_SR(i)               (*TIM[i]).SR//i=0_16
#define TIM_EGR(i)              (*TIM[i]).EGR//i=0_16
#define TIM_CCMR(i,j)           (*TIM[i]).CCMR[j]//i=0_16,j=0_1
#define TIM_CCER(i)             (*TIM[i]).CCER//i=0_16
#define TIM_CNT(i)              (*TIM[i]).CNT//i=0_16
#define TIM_PSC(i)              (*TIM[i]).PSC//i=0_16
#define TIM_ARR(i)              (*TIM[i]).ARR//i=0_16
#define TIM_RCR(i)              (*TIM[i]).RCR//i=0_16
#define TIM_CCR(i,j)            (*TIM[i]).CCR[j]//i=0_16,j=0_3
#define TIM_BDTR(i)             (*TIM[i]).BDTR//i=0_16
#define TIM_DCR(i)              (*TIM[i]).DCR//i=0_16
#define TIM_DMAR(i)             (*TIM[i]).DMAR//i=0_16
//==============================================================================================================================
#define RSTV_USART_SR           0x00000000//0x000
struct USART_SR_BIT
{
	UINT32 PE:1;          //00,Parity Error Flag
	UINT32 FE:1;          //01,Framing Error Flag
	UINT32 NE:1;          //02,Noise Error Flag
	UINT32 ORE:1;         //03,OverRun Error Flag
	UINT32 IDLE:1;        //04,IDLE line detected Flag
	UINT32 RXNE:1;        //05,Read Data Register Not Empty Flag
	UINT32 TC:1;          //06,Transmission Complete Flag
	UINT32 TXE:1;         //07,Transmit Data Register Empty Flag
	UINT32 LBD:1;         //08,LIN Break Detection Flag
	UINT32 CTS:1;         //09,CTS Flag
	UINT32 Reserved0:22;  //10,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USART_DR           0x00000000//0x004
struct USART_DR_BIT
{
	UINT32 DR:9;          //00,Data value
	UINT32 Reserved0:23;  //09,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USART_BRR          0x00000000//0x008
struct USART_BRR_BIT
{
	UINT32 DIVF:4;        //00,Fraction of USARTDIV
	UINT32 DIVM:12;       //04,Mantissa of USARTDIV
	UINT32 Reserved0:16;  //16
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USART_CR1          0x00000000//0x00C
struct USART_CR1_BIT
{
	UINT32 SBK:1;         //00,Send Break
	UINT32 RWU:1;         //01,Receiver wakeup
	UINT32 RE:1;          //02,Receiver Enable
	UINT32 TE:1;          //03,Transmitter Enable
	UINT32 IDLEIE:1;      //04,IDLE Interrupt Enable
	UINT32 RXNEIE:1;      //05,RXNE Interrupt Enable
	UINT32 TCIE:1;        //06,Transmission Complete Interrupt Enable
	UINT32 TXEIE:1;       //07,TXE Interrupt Enable
	UINT32 PEIE:1;        //08,PE Interrupt Enable
	UINT32 PS:1;          //09,Parity Selection
	UINT32 PCE:1;         //10,Parity Control Enable
	UINT32 WAKE:1;        //11,Wakeup method
	UINT32 M:1;           //12,Word length
	UINT32 UE:1;          //13,USART Enable
	UINT32 Reserved0:1;   //14,
	UINT32 OVER8:1;       //15,USART Oversmapling 8-bits
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USART_CR2          0x00000000//0x010
struct USART_CR2_BIT  
{
	UINT32 ADD:4;         //00,Address of the USART node
	UINT32 Reserved0:1;   //04,
	UINT32 LBDL:1;        //05,LIN Break Detection Length
	UINT32 LBDIE:1;       //06,LIN Break Detection Interrupt Enable
	UINT32 Reserved1:1;   //07,
	UINT32 LBCL:1;        //08,Last Bit Clock pulse
	UINT32 CPHA:1;        //09,Clock Phase
	UINT32 CPOL:1;        //10,Clock Polarity
	UINT32 CLKEN:1;       //11,Clock Enable
	UINT32 STOP:2;        //12,STOP[1:0] bits (STOP bits):0=1,1=0.5,2=2,3=1.5
	UINT32 LINEN:1;       //14,LIN mode enable
	UINT32 Reserved2:17;  //15,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USART_CR3          0x00000000//0x014
struct USART_CR3_BIT
{
	UINT32 EIE:1;         //00,Error Interrupt Enable
	UINT32 IREN:1;        //01,IrDA mode Enable
	UINT32 IRLP:1;        //02,IrDA Low-Power
	UINT32 HDSEL:1;       //03,Half-Duplex Selection
	UINT32 NACK:1;        //04,Smartcard NACK enable
	UINT32 SCEN:1;        //05,Smartcard mode enable
	UINT32 DMAR:1;        //06,DMA Enable Receiver
	UINT32 DMAT:1;        //07,DMA Enable Transmitter
	UINT32 RTSE:1;        //08,RTS Enable
	UINT32 CTSE:1;        //09,CTS Enable
	UINT32 CTSIE:1;       //10,CTS Interrupt Enable
	UINT32 ONEBIT:1;      //11,USART One bit method enable,<LDY>
	UINT32 Reserved0:20;  //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USART_GTPR         0x00000000//0x018
struct USART_GTPR_BIT
{
	UINT32 PSC:8;         //00,PSC[7:0] bits (Prescaler value)
	UINT32 GT:8;          //08,Guard time value
	UINT32 Reserved0:16;  //16,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define UART_Struct Struct_UART
typedef struct Struct_UART//UART1=0x40013800,UART2_5=0x40004400,Step=0x400
{
  union{UINT32 SR;struct USART_SR_BIT SR_BIT;};         //0x000(RW),USART Status register
  union{UINT32 DR;struct USART_DR_BIT DR_BIT;};         //0x004(RW),USART Data register
  union{UINT32 BRR;struct USART_BRR_BIT BRR_BIT;};      //0x008(RW),USART Baud rate register
  union{UINT32 CR1;struct USART_CR1_BIT CR1_BIT;};      //0x00C(RW),USART Control register 1
  union{UINT32 CR2;struct USART_CR2_BIT CR2_BIT;};      //0x010(RW),USART Control register 2
  union{UINT32 CR3;struct USART_CR3_BIT CR3_BIT;};      //0x014(RW),USART Control register 3
  union{UINT32 GTPR;struct USART_GTPR_BIT GTPR_BIT;};   //0x018(RW),USART Guard time and prescaler register
} UART_Type,Type_UART;
#define PT_UART1                ((volatile Type_UART *)BASE_UART1)
#define PT_UART2                ((volatile Type_UART *)BASE_UART2)
#define PT_UART3                ((volatile Type_UART *)BASE_UART3)
#define PT_UART4                ((volatile Type_UART *)BASE_UART4)
#define PT_UART5                ((volatile Type_UART *)BASE_UART5)
#define PT_UART(i)              ((volatile Type_UART *)BASE_UART[i])
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define UART_SR(i)              (*UART[i]).SR
#define UART_DR(i)              (*UART[i]).DR
#define UART_BRR(i)             (*UART[i]).BRR
#define UART_CR1(i)             (*UART[i]).CR1
#define UART_CR2(i)             (*UART[i]).CR2
#define UART_CR3(i)             (*UART[i]).CR3
#define UART_GTPR(i)            (*UART[i]).GTPR
//==============================================================================================================================
#define RSTV_USB_EP0R           0x00000000//0x000
#define RSTV_USB_EP1R           0x00000000//0x004
#define RSTV_USB_EP2R           0x00000000//0x008
#define RSTV_USB_EP3R           0x00000000//0x00C
#define RSTV_USB_EP4R           0x00000000//0x010
#define RSTV_USB_EP5R           0x00000000//0x014
#define RSTV_USB_EP6R           0x00000000//0x018
#define RSTV_USB_EP7R           0x00000000//0x01C
#define RSTV_USB_EPR            0x00000000

struct USB_EPR_BIT//0x000=EP0R,0x004=EP1R,...,0x01C=EP7R
{
	UINT32 EA:4;          //00,Endpoint Address
	UINT32 TXSTAT:2;      //04,STAT_TX[1:0] bits (Status bits, for transmission transfers):0=Disable,1=Stall,2=NAK,3=VALID//bit4_5=DTOG1,DTOG2
	UINT32 TXDTOG:1;      //06,Data Toggle, for transmission transfers
	UINT32 TXCTR:1;       //07,Correct Transfer for transmission
	UINT32 KIND:1;        //08,Endpoint Kind
	UINT32 TYPE:2;        //09,EP_TYPE[1:0] bits (Endpoint type):0=BULK,1=CONTROL,2=ISOCHRONOUS,3=INTERRUPT
	UINT32 SETUP:1;       //11,Setup transaction completed
	UINT32 RXSTAT:2;      //12,STAT_RX[1:0] bits (Status bits, for reception transfers):0=Disable,1=Stall,2=NAK,3=VALID//bit12_13=DTOG1,DTOG2
	UINT32 RXDTOG:1;      //14,Data Toggle, for reception transfers
	UINT32 RXCTR:1;       //15,Correct Transfer for reception
	UINT32 Reserved0:16;  //16,
};
#define USB_EPR_TYPE_BULK               0//EndPoint BULK
#define USB_EPR_TYPE_CONTROL            1//EndPoint CONTROL
#define USB_EPR_TYPE_ISOCHRONOUS        2//EndPoint ISOCHRONOUS
#define USB_EPR_TYPE_INTERRUPT          3//EndPoint INTERRUPT
#define USB_EPR_STAT_DIS                0//EndPoint RX/TX DISabled
#define USB_EPR_STAT_STALL              1//EndPoint RX/TX STALLed,DTOG1
#define USB_EPR_STAT_NAK                2//EndPoint RX/TX NAKed,DTOG2
#define USB_EPR_STAT_VALID              3//EndPoint RX/TX VALID
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_CNTR           0x00000003//0x040
struct USB_CNTR_BIT
{
	UINT32 FRES:1;        //00,Force USB Reset
	UINT32 PDWN:1;        //01,Power down
	UINT32 LPMODE:1;      //02,Low-power mode
	UINT32 FSUSP:1;       //03,Force suspend
	UINT32 RESUME:1;      //04,Resume request
	UINT32 Reserved0:3;   //05,
	UINT32 ESOFM:1;       //08,Expected Start Of Frame Interrupt Mask
	UINT32 SOFM:1;        //09,Start Of Frame Interrupt Mask
	UINT32 RSTM:1;        //10,=RESETM,RESET Interrupt Mask
	UINT32 SUSPM:1;       //11,Suspend mode Interrupt Mask,1=Enable
	UINT32 WKUPM:1;       //12,Wakeup Interrupt Mask,1=Enable
	UINT32 ERRM:1;        //13,Error Interrupt Mask,1=Enable
	UINT32 DOVRM:1;       //14,=DOVM,Packet Memory Area Over / Underrun Interrupt Mask,1=Enable
	UINT32 CTRM:1;        //15,Correct Transfer Interrupt Mask,1=Enable
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_ISTR           0x00000000//0x044
struct USB_ISTR_BIT
{
	UINT32 EPID:4;        //00,Endpoint Identifier
	UINT32 DIR:1;         //04,Direction of transaction
	UINT32 Reserved0:3;   //05,
	UINT32 ESOF:1;        //08,Expected Start Of Frame
	UINT32 SOF:1;         //09,Start Of Frame
	UINT32 RST:1;         //10,=RESET,USB RESET request
	UINT32 SUSP:1;        //11,Suspend mode request
	UINT32 WKUP:1;        //12,Wake up
	UINT32 ERR:1;         //13,Error
	UINT32 DOVR:1;        //14,PDMOVR=DOVR,Packet Memory Area Over / Underrun
	UINT32 CTR:1;         //15,Correct Transfer
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_FNR            0x00000000//0x048
struct USB_FNR_BIT
{
	UINT32 FN:11;         //00,Frame Number
	UINT32 LSOF:2;        //11,Lost SOF
	UINT32 LCK:1;         //13,Locked
	UINT32 RXDM:1;        //14,Receive Data - Line Status
	UINT32 RXDP:1;        //15,Receive Data + Line Status
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_DADDR          0x00000000//0x04C
struct USB_DADDR_BIT
{
	UINT32 ADD:7;         //00,ADD[6:0] bits (Device Address),Enable EP0_6
	UINT32 EF:1;          //07,Enable Function
	UINT32 Reserved1:24;  //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_BUFTAB         0x00000000//0x050
struct USB_BUFTAB_BIT
{
	UINT32 Reserved0:3;   //00,
	UINT32 TADDR:13;      //03,Buffer Table
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_TXADDR0        0x00000000//
#define RSTV_USB_TXADDR1        0x00000000//
#define RSTV_USB_TXADDR2        0x00000000//
#define RSTV_USB_TXADDR3        0x00000000//
#define RSTV_USB_TXADDR4        0x00000000//
#define RSTV_USB_TXADDR5        0x00000000//
#define RSTV_USB_TXADDR6        0x00000000//
#define RSTV_USB_TXADDR7        0x00000000//
#define RSTV_USB_TXADDR         0x00000000//

#define RSTV_USB_RXADDR0        0x00000000//Reception Buffer Address 0
#define RSTV_USB_RXADDR1        0x00000000//Reception Buffer Address 1
#define RSTV_USB_RXADDR2        0x00000000//Reception Buffer Address 2
#define RSTV_USB_RXADDR3        0x00000000//Reception Buffer Address 3
#define RSTV_USB_RXADDR4        0x00000000//Reception Buffer Address 4
#define RSTV_USB_RXADDR5        0x00000000//Reception Buffer Address 5
#define RSTV_USB_RXADDR6        0x00000000//Reception Buffer Address 6
#define RSTV_USB_RXADDR7        0x00000000//Reception Buffer Address 7
#define RSTV_USB_RXADDR         0x00000000//
struct USB_ADDR_BIT//TXADDR0_TXADDR7,RXADDR0_RXADDR7
{
	UINT32 Reserved0:1;   //00,
	UINT32 ADDR:15;       //01,Transmission Buffer Address 0
	UINT32 Reserved1:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_TXCOUNT0       0x00000000//
#define RSTV_USB_TXCOUNT1       0x00000000//
#define RSTV_USB_TXCOUNT2       0x00000000//
#define RSTV_USB_TXCOUNT3       0x00000000//
#define RSTV_USB_TXCOUNT4       0x00000000//
#define RSTV_USB_TXCOUNT5       0x00000000//
#define RSTV_USB_TXCOUNT6       0x00000000//
#define RSTV_USB_TXCOUNT7       0x00000000//
#define RSTV_USB_TXCOUNT        0x00000000
struct USB_TXCOUNT_BIT //COUNT0_COUNT7
{
	UINT32 TX0:10;        //00,Transmission Byte Count 0 (low)
	UINT32 Reserved0:6;   //10,
	UINT32 TX1:10;        //16,Transmission Byte Count 0 (high)
	UINT32 Reserved1:6;   //26,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USB_RXCOUNT0       0x00000000//
#define RSTV_USB_RXCOUNT1       0x00000000//
#define RSTV_USB_RXCOUNT2       0x00000000//
#define RSTV_USB_RXCOUNT3       0x00000000//
#define RSTV_USB_RXCOUNT4       0x00000000//
#define RSTV_USB_RXCOUNT5       0x00000000//
#define RSTV_USB_RXCOUNT6       0x00000000//
#define RSTV_USB_RXCOUNT7       0x00000000//
#define RSTV_USB_RXCOUNT        0x00000000
struct USB_RXCOUNT_BIT //RXCOUNT0_RXCOUNT7
{
	UINT32 RX0:10;        //00,Reception Byte Count(low),
	UINT32 NUMBLOCK0:5;   //10,NUM_BLOCK[4:0] (low), while BLSIZE=1, 0_15=32*(NUMBLOCK+1)=32_512;while BLSIZE=0,1_32=2*NUMBLOCK=2_62
	UINT32 BLSIZE0:1;     //15,BLock SIZE(low)
	UINT32 RX1:10;        //16,Reception Byte Count(high)
	UINT32 NUMBLOCK1:5;   //26,NUM_BLOCK[4:0] (high), while BLSIZE=1, 0_15=32*(NUMBLOCK+1)=32_512;while BLSIZE=0,1_32=2*NUMBLOCK=2_62
	UINT32 BLSIZE1:1;     //31,BLock SIZE(high)
};
//------------------------------------------------------------------------------------------------------------------------------
#define USB_EPCount    3
#define USB_EP0_Size   0x40
#define USB_EP1_Size   0x40
#define USB_EP2_Size   0x40
#define USB_EP3_Size   0x20
#define USB_EP4_Size   0x20
#define USB_EP5_Size   0x20
#define USB_EP6_Size   0x20
#define USB_EP7_Size   0x20//Sum of EP0_7_Size <=0x1C0
#define USB_BUFTAB_Value        0x00000000//8*k,bit0_2=0
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Struct_USBCH//0x40006000
{
  union{UINT32 TXADDR;struct USB_ADDR_BIT TXADDR_BIT;};
  union{UINT32 TXCOUNT;struct USB_TXCOUNT_BIT TXCOUNT_BIT;};
  union{UINT32 RXADDR;struct USB_ADDR_BIT RXADDR_BIT;};
  union{UINT32 RXCOUNT;struct USB_RXCOUNT_BIT RXCOUNT_BIT;};
} USBCH_Type,Type_USBCH;
#define PT_USBCH(i)            ((volatile Type_USBCH *)(BASE_USBRAM+USB_BTABLE_Value*2+i*16))//i=0_7
//------------------------------------------------------------------------------------------------------------------------------
#define USB_Struct  Struct_USB
typedef struct Struct_USB//0x40005C00
{
	union{UINT32 EPR[8];struct USB_EPR_BIT EPR_BIT[8];Type_UINT32_LH EPR_LH[8];}; //0x40005C00(RW),USB Endpoint 0_7 register
	UINT32 Reserved0[8];   //0x40005C20
  union{UINT32 CNTR;struct USB_CNTR_BIT CNTR_BIT;Type_UINT32_LH CNTR_LH;};      //0x40005C40(RW),Control register
	union{UINT32 ISTR;struct USB_ISTR_BIT ISTR_BIT;Type_UINT32_LH ISTR_LH;};      //0x40005C44(RW),Interrupt status register
	union{UINT32 FNR;struct USB_FNR_BIT FNR_BIT;Type_UINT32_LH FNR_LH;};          //0x40005C48(RW),Frame number register
	union{UINT32 DADDR;struct USB_DADDR_BIT DADDR_BIT;};                          //0x40005C4C(RW),Device address register
	union{UINT32 BUFTAB;struct USB_BUFTAB_BIT BUFTAB_BIT;};                       //0x40005C50(RW),=BTABLE,Channel table startpos
  UINT32 Reserved1[43+USB_BUFTAB_Value/2];                                      //0x40005C54(R),
	union{UINT32 MDL;};//0x40005D00(RW),Module_Choose,0=USB1(cann't use with can),1=USB2(can use with can)
	UINT32 Reserved2[191];//0x40005D04(R),
  struct Struct_USBCH CH[USB_EPCount];//0x40006000+USB_BUFTAB_Value*2,Channel table register
  UINT32 RXBUF0[USB_EP0_Size/2];//40006030
  UINT32 TXBUF0[USB_EP0_Size/2];
  UINT32 RXBUF1[USB_EP1_Size/2];
  UINT32 TXBUF1[USB_EP1_Size/2];
  UINT32 RXBUF2[USB_EP2_Size/2];
  UINT32 TXBUF2[USB_EP2_Size/2];
} USB_Type,Type_USB;
#define PT_USB                  ((volatile Type_USB *)BASE_USB)
//------------------------------------------------------------------------------------------------------------------------------
#define USB_EPR(i)              USB.EPR[i]//i=0_7
#define USB_CNTR                USB.CNTR
#define USB_ISTR                USB.ISTR
#define USB_FNR                 USB.FNR
#define USB_DADDR               USB.DADDR
#define USB_BUFTAB              USB.BUFTAB
#define USB_MDL                 USB.MDL
#define USB_TXADDR(i)           USB.CH[i].TXADDR//i=0_7
#define USB_TXCOUNT(i)          USB.CH[i].TXCOUNT//i=0_7
#define USB_RXADDR(i)           USB.CH[i].RXADDR//i=0_7
#define USB_RXCOUNT(i)          USB.CH[i].RXCOUNT//i=0_7
//==============================================================================================================================
#define RSTV_USBFS_GOTGCTL      0x00010000//0x000
struct USBFS_GOTGCTL_BIT
{
	UINT32 SRQSCS:1;     //00,
	UINT32 SRQ:1;        //01,
	UINT32 Reserved0:6;  //02,
	UINT32 HNGSCS:1;     //08,
	UINT32 HNPRQ:1;      //09,
	UINT32 HSHNPEN:1;    //10,
	UINT32 DHNPEN:1;     //11,
	UINT32 Reserved1:4;  //12,
	UINT32 CIDSTS:1;     //16,
	UINT32 DBCT:1;       //17,
	UINT32 ASVLD:1;      //18,
	UINT32 BSVLD:1;      //19,
	UINT32 Reserved2:12; //20,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GOTGINT      0x00000000//0x004
struct USBFS_GOTGINT_BIT
{
	UINT32 Reserved0:2;  //00,
	UINT32 SEDET:1;      //02,
	UINT32 Reserved1:5;  //03,
	UINT32 SRSSCHG:1;    //08,
	UINT32 HNSSCHG:1;    //09,
	UINT32 Reserved2:7;  //10,
	UINT32 HNGDET:1;     //17,
	UINT32 ADTOCHG:1;    //18,
	UINT32 DBCDNE:1;     //19,
	UINT32 Reserved3:12; //20,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GAHBCFG      0x00000000//0x008
struct USBFS_GAHBCFG_BIT
{
	UINT32 GINTMSK:1;    //00,
	UINT32 Reserved0:6;  //01,
	UINT32 TXFELVL:1;    //07,
	UINT32 PTXFELVL:1;   //08,
	UINT32 Reserved1:23; //09,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GUSBCFG      0x00001440//0x00C
struct USBFS_GUSBCFG_BIT
{
	UINT32 TOCAL:3;      //00,
	UINT32 Reserved0:3;  //03,
	UINT32 PHYSEL:1;     //06,
	UINT32 Reserved1:1;  //07,
	UINT32 SRPCAP:1;     //08,
	UINT32 HNPCAP:1;     //09,
	UINT32 TRDT:4;       //10,
	UINT32 Reserved2:15; //14,
	UINT32 FHMOD:1;      //29,
	UINT32 FDMOD:1;      //30,
	UINT32 CTXPKT:1;     //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GRSTCTL      0x00000000//0x010
struct USBFS_GRSTCTL_BIT
{
	UINT32 CSRST:1;      //00,
	UINT32 HSRST:1;      //01,
	UINT32 FCRST:1;      //02,
	UINT32 Reserved0:1;  //03,
	UINT32 RXFFLSH:1;    //04,
	UINT32 TXFFLSH:1;    //05,
	UINT32 TXFNUM:5;     //06,
	UINT32 Reserved1:20; //11,
	UINT32 AHBIDL:1;     //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GINTSTS      0x00000000//0x014
#define RSTV_USBFS_GINTMSK      0x00000000//0x018
struct USBFS_GINT_BIT//0x014=GINTSTS,0x18=GINTMSK
{
	UINT32 CMOD:1;       //00, no in  GINTMSK
	UINT32 MMIS:1;       //01,
	UINT32 OTGINT:1;     //02,
	UINT32 SOF:1;        //03,
	UINT32 RXFLVL:1;     //04,
	UINT32 NPTXFE:1;     //05,
	UINT32 GINAKEFF:1;   //06,
	UINT32 GONAKEFF:1;   //07,
	UINT32 Reserved0:2;  //08,
	UINT32 ESUSP:1;      //10,
	UINT32 USBSUSP:1;    //11,
	UINT32 USBRST:1;     //12,
	UINT32 ENUMDNE:1;    //13,
	UINT32 ISOODRP:1;    //14,
	UINT32 EOPF:1;       //15,
	UINT32 Reserved1:2;  //16,
	UINT32 IEPINT:1;     //18,
	UINT32 OEPINT:1;     //19,
	UINT32 IISOIXFR:1;   //20,
	UINT32 IPXFR_INCO:1; //21,also named=IPXFR_INCCOMPISOOUT
	UINT32 Reserved2:2;  //22,
	UINT32 HPRTINT:1;    //24,
	UINT32 HCINT:1;      //25,
	UINT32 PTXFE:1;      //26,
	UINT32 Reserved3:1;  //27,
	UINT32 CIDSCHG:1;    //28,
	UINT32 DISCINT:1;    //29,
	UINT32 SRQINT:1;     //30,
	UINT32 WKUINT:1;     //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GRXSTSR      0x00000000//0x01C
#define RSTV_USBFS_GRXSTSP      0x00000000//0x020
struct USBFS_GRXSTS_BITH//0x01C=GRXSTSR,0x020=GRXSTSP
{
	UINT32 CHNUM:4;      //00,
	UINT32 BCNT:11;      //04,
	UINT32 DPID:2;       //15,
	UINT32 PKTSTS:4;     //17,
	UINT32 Reserved0:11; //21,
};
struct USBFS_GRXSTS_BITD//0x01C=GRXSTSR,0x020=GRXSTSP
{
	UINT32 EPNUM:4;      //00,
	UINT32 BCNT:11;      //04,
	UINT32 DPID:2;       //15,
	UINT32 PKTSTS:4;     //17,
	UINT32 FRMNUM:4;     //21,
	UINT32 Reserved0:7;  //25,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GRXFSIZ      0x00000200//0x024
struct USBFS_GRXFSIZ_BIT
{
	UINT32 RXFD:16;      //00,
	UINT32 Reserved0:16; //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPTXF0     0x00000200//0x028,also named HNPTXFSIZ
struct USBFS_HNPTXFSIZ_BIT
{
	UINT32 NPTXFSA:16;   //00,
	UINT32 NPTXFD:16;    //16,
};
struct USBFS_DIEPTXF0_BIT
{
	UINT32 TX0FSA:16;    //00,
	UINT32 TX0FD:16;     //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HNPTXSTS     0x00040200//0x02C,
struct USBFS_HNPTXSTS_BIT
{
	UINT32 NPTXFSA:16;   //00,
	UINT32 NPTQXSAV:8;   //16,
	UINT32 NPTXQTOP:7;   //24,
	UINT32 Reserved0:1;  //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_GCCFG        0x00000000//0x038,
struct USBFS_GCCFG_BIT
{
	UINT32 Reserved0:16; //00,
	UINT32 PWRDWN:1;     //16,
	UINT32 Reserved1:1;  //17,
	UINT32 VBUSASEN:1;   //18,
	UINT32 VBUSBSEN:1;   //19,
	UINT32 SOFOUTEN:1;   //20,
	UINT32 Reserved2:11; //21,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_CID          0x00001200//0x03C,
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HPTXFSIZ     0x02000400//0x100,
struct USBFS_HPTXFSIZ_BIT
{
	UINT32 PTXSA:16;     //00,
	UINT32 PTXFSIZ:16;   //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPTXF1     0x02000200//0x104,
#define RSTV_USBFS_DIEPTXF2     0x02000400//0x108,
#define RSTV_USBFS_DIEPTXF3     0x02000400//0x10C,
struct USBFS_DIEPTXF_BIT//0x104=DIEPTXF1,0x108=DIEPTXF2,0x10C=DIEPTXF3
{
	UINT32 INEPTXSA:16;  //00,
	UINT32 INEPTXFD:16;  //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HCFG         0x00000000//0x400,
struct USBFS_HCFG_BIT
{
	UINT32 FSLSPCS:2;    //00,
	UINT32 FSLSS:1;      //02,
	UINT32 Reserved0:29; //03,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HFIR         0x0000EA60//0x404,
struct USBFS_HFIR_BIT
{
	UINT32 FRIVL:16;     //00,
	UINT32 Reserved0:16; //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HFNUM        0x00003FFF//0x408,
struct USBFS_HFNUM_BIT
{
	UINT32 FRNUM:16;     //00,
	UINT32 FTREM:16;     //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HPTXSTS      0x00000000//0x410,
struct USBFS_HPTXSTS_BIT
{
	UINT32 PTXFSAVL:16;  //00,
	UINT32 PTXQSAV:8;    //16,
	UINT32 PTXQTOP:8;    //24,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HAINT        0x00000000//0x414,
#define RSTV_USBFS_HAINTMSK     0x00000000//0x418,
struct USBFS_HAINT_BIT//0x414=HAINT,0x418=HAINTMSK
{
	UINT32 HAINT:16;     //00,
	UINT32 Reserved0:16; //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HPRT         0x00000000//0x440,
struct USBFS_HPRT_BIT
{
	UINT32 PCSTS:1;      //00,
	UINT32 PCDET:1;      //01,
	UINT32 PENA:1;       //02,
	UINT32 PENCHNG:1;    //03,
	UINT32 POCA:1;       //04,
	UINT32 POCCHNG:1;    //05,
	UINT32 PRES:1;       //06,
	UINT32 PSUSP:1;      //07,
	UINT32 PRST:1;       //08,
	UINT32 Reserved0:1;  //09,
	UINT32 PLSTS:2;      //10,
	UINT32 PPWR:1;       //12,
	UINT32 PTCTL:4;      //13,
	UINT32 PSPD:2;       //17,
	UINT32 Reserved1:13; //19,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HCCHAR0      0x00000000//0x500,
#define RSTV_USBFS_HCCHAR1      0x00000000//0x520,
#define RSTV_USBFS_HCCHAR2      0x00000000//0x540,
#define RSTV_USBFS_HCCHAR3      0x00000000//0x560,
#define RSTV_USBFS_HCCHAR4      0x00000000//0x580,
#define RSTV_USBFS_HCCHAR5      0x00000000//0x5A0,
#define RSTV_USBFS_HCCHAR6      0x00000000//0x5C0,
#define RSTV_USBFS_HCCHAR7      0x00000000//0x5E0,
#define RSTV_USBFS_HCCHAR       0x00000000
struct USBFS_HCCHAR_BIT//HCCHAR0_HCCHAR7
{
	UINT32 MPSIZ:11;     //00,
	UINT32 EPNUM:4;      //11,
	UINT32 EPDIR:1;      //15,
	UINT32 Reserved0:1;  //16,
	UINT32 LSDEV:1;      //17,
	UINT32 EPTYP:2;      //18,
	UINT32 MCNT:2;       //20,
	UINT32 DAD:7;        //22,
	UINT32 ODDFRM:1;     //29,
	UINT32 CHDIS:1;      //30,
	UINT32 CHENA:1;      //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HCINT0       0x00000000//0x508,
#define RSTV_USBFS_HCINT1       0x00000000//0x528,
#define RSTV_USBFS_HCINT2       0x00000000//0x548,
#define RSTV_USBFS_HCINT3       0x00000000//0x568,
#define RSTV_USBFS_HCINT4       0x00000000//0x588,
#define RSTV_USBFS_HCINT5       0x00000000//0x5A8,
#define RSTV_USBFS_HCINT6       0x00000000//0x5C8,
#define RSTV_USBFS_HCINT7       0x00000000//0x5E8,
#define RSTV_USBFS_HCINT        0x00000000
#define RSTV_USBFS_HCINTMSK0    0x00000000//0x50C,
#define RSTV_USBFS_HCINTMSK1    0x00000000//0x52C,
#define RSTV_USBFS_HCINTMSK2    0x00000000//0x54C,
#define RSTV_USBFS_HCINTMSK3    0x00000000//0x56C,
#define RSTV_USBFS_HCINTMSK4    0x00000000//0x58C,
#define RSTV_USBFS_HCINTMSK5    0x00000000//0x5AC,
#define RSTV_USBFS_HCINTMSK6    0x00000000//0x5CC,
#define RSTV_USBFS_HCINTMSK7    0x00000000//0x5EC,
#define RSTV_USBFS_HCINTMSK     0x00000000
struct USBFS_HCINT_BIT//0x508=HCINT0,Step=0x20;0x50C=HCINTMSK0,Step=0x20
{
	UINT32 XFRC:1;       //00,
	UINT32 CHH:1;        //01,
	UINT32 Reserved0:1;  //02,
	UINT32 STALL:1;      //03,
	UINT32 NAK:1;        //04,
	UINT32 ACK:1;        //05,
	UINT32 Reserved1:1;  //06,
	UINT32 TXERR:1;      //07,
	UINT32 BBERR:1;      //08,
	UINT32 FRMOR:1;      //09,
	UINT32 DTERR:1;      //10,
	UINT32 Reserved2:21; //11,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_HCTSIZ0      0x00000000//0x510,
#define RSTV_USBFS_HCTSIZ1      0x00000000//0x530,
#define RSTV_USBFS_HCTSIZ2      0x00000000//0x550,
#define RSTV_USBFS_HCTSIZ3      0x00000000//0x570,
#define RSTV_USBFS_HCTSIZ4      0x00000000//0x590,
#define RSTV_USBFS_HCTSIZ5      0x00000000//0x5B0,
#define RSTV_USBFS_HCTSIZ6      0x00000000//0x5D0,
#define RSTV_USBFS_HCTSIZ7      0x00000000//0x5F0,
#define RSTV_USBFS_HCTSIZ       0x00000000
struct USBFS_HCTSIZ_BIT//0x508=HCTSIZ0,Step=0x20
{
	UINT32 XFRSIZ:19;    //00,
	UINT32 PKTCNT:10;    //19,
	UINT32 DPID:2;       //29,
	UINT32 Reserved0:1;  //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DCFG         0x00000000//0x800
struct USBFS_DCFG_BIT
{
	UINT32 DSPD:2;       //00,
	UINT32 NZLSOHSK:1;   //02,
	UINT32 Reserved0:1;  //03,
	UINT32 DAD:7;        //04,
	UINT32 PFVL:2;       //11,
	UINT32 Reserved1:19; //13,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DCTL         0x00000000//0x804
struct USBFS_DCTL_BIT
{
	UINT32 RWUSIG:1;     //00,
	UINT32 SDIS:1;       //01,
	UINT32 GINSTS:1;     //02,
	UINT32 GONSTS:1;     //03,
	UINT32 TCTL:3;       //04,
	UINT32 SGINAK:1;     //07,
	UINT32 CGINAK:1;     //08,
	UINT32 SGONAK:1;     //09,
	UINT32 CGONAK:1;     //10,
	UINT32 POPRGDNE:1;   //11,
	UINT32 Reserved0:20; //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DSTS         0x00000000//0x808
struct USBFS_DSTS_BIT
{
	UINT32 SUSPSTS:1;    //00,
	UINT32 ENUMSPD:2;    //01,
	UINT32 EERR:1;       //03,
	UINT32 Reserved0:4;  //04,
	UINT32 FNSOF:14;     //08,
	UINT32 Reserved1:10; //22,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPMSK      0x00000000//0x810
struct USBFS_DIEPMSK_BIT
{
	UINT32 XFRCM:1;      //00,
	UINT32 EPDM:1;       //01,
	UINT32 Reserved0:1;  //02,
	UINT32 TOM:1;        //03,
	UINT32 ITTXFEM:1;    //04,
	UINT32 INEPNMM:1;    //05,
	UINT32 INEPNEM:1;    //06,
	UINT32 Reserved1:6;  //07,
	UINT32 NAKM:1;       //13,
	UINT32 Reserved2:18; //14,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DOEPMSK      0x00000000//0x814
struct USBFS_DOEPMSK_BIT
{
	UINT32 XFRCM:1;      //00,
	UINT32 EPDM:1;       //01,
	UINT32 Reserved0:1;  //02,
	UINT32 STUPM:1;      //03,
	UINT32 OTEPDM:1;     //04,
	UINT32 STSPHSRXM:1;  //05,
	UINT32 Reserved1:2;  //06,
	UINT32 OUTPKTERRM:1; //08,
	UINT32 Reserved2:3;  //09,
	UINT32 BERRM:1;      //12,
	UINT32 NAKM:1;       //13,
	UINT32 Reserved3:18; //14,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DAINT        0x00000000//0x818
#define RSTV_USBFS_DAINTMSK     0x00000000//0x81C
struct USBFS_DAINT_BIT//0x818=DAINT,0x81C=DAINMSK
{
	UINT32 IEPINT:16;    //00,
	UINT32 OEPINT:16;    //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DVBUSDIS     0x000017D7//0x828
struct USBFS_DVBUSDIS_BIT
{
	UINT32 VBUSDT:16;    //00,
	UINT32 Reserved0:16; //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DVBUSPULSE   0x000005B8//0x82C
struct USBFS_DVBUSPULSE_BIT
{
	UINT32 DVBUSP:12;    //00,
	UINT32 Reserved0:20; //12,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPEMPMSK   0x00000000//0x834
struct USBFS_DIEPEMPMSK_BIT
{
	UINT32 INEPTXFEM:16; //00,
	UINT32 Reserved0:16; //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPCTL0     0x00008000//0x900
#define RSTV_USBFS_DIEPCTL1     0x00000000//0x920
#define RSTV_USBFS_DIEPCTL2     0x00000000//0x940
#define RSTV_USBFS_DIEPCTL3     0x00000000//0x960
#define RSTV_USBFS_DIEPCTL      0x00000000
struct USBFS_DIEPCTL_BITA//DIEPCTL0
{
	UINT32 MPSIZ:2;      //00,
	UINT32 Reserved0:13; //12,
	UINT32 USBAEP:1;     //15,
	UINT32 Reserved1:1;  //16,
	UINT32 NAKSTS:1;     //17,
	UINT32 EPTYP:2;      //18,
	UINT32 Reserved2:1;  //20,
	UINT32 STALL:1;      //21,
	UINT32 TXFNUM:4;     //22,
	UINT32 CNAK:1;       //26,
	UINT32 SNAK:1;       //27,
	UINT32 Reserved3:2;  //28,
	UINT32 EPDIS:1;      //30,
	UINT32 EPENA:1;      //31,
};
struct USBFS_DIEPCTL_BITB//DIEPCTL1_DIEPCTL3
{
	UINT32 MPSIZ:11;     //00,w=2 in DIEPCTL0
	UINT32 Reserved0:4;  //11,
	UINT32 USBAEP:1;     //15,
	UINT32 EONUM_DPID:1; //16,no in DIEPCTL0
	UINT32 NAKSTS:1;     //17,
	UINT32 EPTYP:2;      //18,
	UINT32 Reserved2:1;  //20,
	UINT32 STALL:1;      //21,
	UINT32 TXFNUM:4;     //22,
	UINT32 CNAK:1;       //26,
	UINT32 SNAK:1;       //27,
	UINT32 SD0PID:1;     //28,no in DIEPCTL0
	UINT32 SODDFR:1;     //29,no in DIEPCTL0
	UINT32 EPDIS:1;      //30,
	UINT32 EPENA:1;      //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPINT0      0x00000080//0x908
#define RSTV_USBFS_DIEPINT1      0x00000080//0x928
#define RSTV_USBFS_DIEPINT2      0x00000080//0x948
#define RSTV_USBFS_DIEPINT3      0x00000080//0x968
#define RSTV_USBFS_DIEPINT       0x00000080
struct USBFS_DIEPINT_BIT//0x908=DIEPINT0,0x928=DIEPINT1,0x948=DIEPINT2,0x968=DIEPINT3
{
	UINT32 XFRC:1;       //00,
	UINT32 EPDISD:1;     //01,
	UINT32 Reserved0:1;  //02,
	UINT32 TOC:1;        //03,
	UINT32 ITTXFE:1;     //04,
	UINT32 INEPNM:1;     //05,
	UINT32 INEPNE:1;     //06,
	UINT32 TXFE:1;       //07,
	UINT32 Reserved1:3;  //08,
	UINT32 PKDTRPSTS:1;  //11,
	UINT32 Reserved2:1;  //12,
	UINT32 NAK:1;        //13,
	UINT32 Reserved3:18; //14,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DIEPTSIZ0     0x00000000//0x910
#define RSTV_USBFS_DIEPTSIZ1     0x00000000//0x930
#define RSTV_USBFS_DIEPTSIZ2     0x00000000//0x950
#define RSTV_USBFS_DIEPTSIZ3     0x00000000//0x970
#define RSTV_USBFS_DIEPTSIZ      0x00000000
struct USBFS_DIEPTSIZ_BITA//0x910=DIEPTSIZ0
{
	UINT32 XFRSIZ:7;     //00,
	UINT32 Reserved0:12; //07,
	UINT32 PKTCNT:2;     //19,
	UINT32 Reserved3:11; //21,
};
struct USBFS_DIEPTSIZ_BITB//0x930=DIEPTSIZ1,0x950=DIEPTSIZ2,0x970=DIEPTSIZ3
{
	UINT32 XFRSIZ:19;    //00,
	UINT32 PKTCNT:10;    //19,
	UINT32 Reserved0:3; //29,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DTXFSTS0      0x00000200//0x918
#define RSTV_USBFS_DTXFSTS1      0x00000200//0x938
#define RSTV_USBFS_DTXFSTS2      0x00000200//0x958
#define RSTV_USBFS_DTXFSTS3      0x00000200//0x978
#define RSTV_USBFS_DTXFSTS       0x00000200
struct USBFS_DTXFSTS_BIT//0x918=DTXFSTS0,0x938=DTXFSTS1,0x958=DTXFSTS2,0x978=DTXFSTS3
{
	UINT32 INEPTFSAV:16; //00,
	UINT32 Reserved0:16; //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DOEPCTL0      0x00008000//0xB00
#define RSTV_USBFS_DOEPCTL1      0x00000000//0xB20
#define RSTV_USBFS_DOEPCTL2      0x00000000//0xB40
#define RSTV_USBFS_DOEPCTL3      0x00000000//0xB60
#define RSTV_USBFS_DOEPCTL       0x00000000
struct USBFS_DOEPCTL_BITA//0xB00=DOEPCTL0
{
	UINT32 MPSIZ:2;      //00,
	UINT32 Reserved0:13; //02,
	UINT32 USBAEP:1;     //15,
	UINT32 Reserved1:1;  //16,
	UINT32 NAKSTS:1;     //17,
	UINT32 EPTYP:2;      //18,
	UINT32 SNPM:1;       //20,
	UINT32 STALL:1;      //21,
	UINT32 Reserved2:4;  //22,
	UINT32 CNAK:1;       //26,
	UINT32 SNAK:1;       //27,
	UINT32 Reserved3:2;  //28,
	UINT32 EPDIS:1;      //30,
	UINT32 EPENA:1;      //31,
};
struct USBFS_DOEPCTL_BITB//0xB20=DOEPCTL1,0xB40=DOEPCTL2,0xB60=DOEPCTL3
{
	UINT32 MPSIZ:11;     //00,w=2 in DOEPCTL0
	UINT32 Reserved0:4;  //11,
	UINT32 USBAEP:1;     //15,
	UINT32 EONUM_DPID:1; //16,no in DOEPCTL0
	UINT32 NAKSTS:1;     //17,
	UINT32 EPTYP:2;      //18,
	UINT32 SNPM:1;       //20,
	UINT32 STALL:1;      //21,
	UINT32 Reserved2:4;  //22,
	UINT32 CNAK:1;       //26,
	UINT32 SNAK:1;       //27,
	UINT32 SD0PID:1;     //28,,no in DOEPCTL0
	UINT32 SODDFRM:1;    //29,,no in DOEPCTL0,also named SEVNFRM
	UINT32 EPDIS:1;      //30,
	UINT32 EPENA:1;      //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DOEPINT0      0x00008000//0xB08
#define RSTV_USBFS_DOEPINT1      0x00000000//0xB28
#define RSTV_USBFS_DOEPINT2      0x00000000//0xB48
#define RSTV_USBFS_DOEPINT3      0x00000000//0xB68
#define RSTV_USBFS_DOEPINT       0x00000000
struct USBFS_DOEPINT_BIT//0xB08=DOEPINT0,0xB28=DOEPINT1,0xB48=DOEPINT2,0xB68=DOEPINT3
{
	UINT32 XFRC:1;       //00,
	UINT32 EPDISD:1;     //01,
	UINT32 Reserved0:1;  //02,
	UINT32 STUP:1;       //03,
	UINT32 OTEPDIS:1;    //04,
	UINT32 STSPHSRX:1;   //05,
	UINT32 Reserved1:2;  //06,
	UINT32 OUTPKTERR:1;  //08,
	UINT32 Reserved2:3;  //09,
	UINT32 BERR:1;       //12,
	UINT32 NAK:1;        //13,
	UINT32 Reserved3:18; //14,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_DOEPTSIZ0     0x00008000//0xB10
#define RSTV_USBFS_DOEPTSIZ1     0x00000000//0xB30
#define RSTV_USBFS_DOEPTSIZ2     0x00000000//0xB50
#define RSTV_USBFS_DOEPTSIZ3     0x00000000//0xB70
#define RSTV_USBFS_DOEPTSIZ      0x00000000
struct USBFS_DOEPTSIZ_BITA//0xB10=DOEPTSIZ0
{
	UINT32 XFRSIZ:7;     //00,
	UINT32 Reserved0:12; //07,
	UINT32 PKTCNT:1;     //19,
	UINT32 Reserved1:9;  //20,
	UINT32 STUPCNT:2;    //29,
	UINT32 Reserved2:1;  //31,
};
struct USBFS_DOEPTSIZ_BITB//0xB30=DOEPTSIZ1,0xB50=DOEPTSIZ2,0xB70=DOEPTSIZ3
{
	UINT32 XRFSIZ:19;    //00,w=7 in DOEPTSIZ0
	UINT32 PKTCNT:10;    //19,
	UINT32 STUPCNT:1;    //29,
	UINT32 RXDPID:1;     //30,
	UINT32 Reserved0:1;  //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_USBFS_PCGCCTL       0x00000000//0xE00
struct USBFS_PCGCCTL_BIT
{
	UINT32 STPPCLK:1;    //00,
	UINT32 GATEHCLK:1;   //01,
	UINT32 Reserved0:2;  //02,
	UINT32 PHYSUSP:1;    //04,
	UINT32 Reserved1:27; //05,
};
//------------------------------------------------------------------------------------------------------------------------------
struct Struct_USBFS_HC//HC[0]=0x500,HC[1]=0x520,...,HC[7]=0x5E0
{
	union{UINT32 HCCHAR;struct USBFS_HCCHAR_BIT HCCHAR_BIT;};
	UINT32 Reserved0[1];
	union{UINT32 HCINT;struct USBFS_HCINT_BIT HCINT_BIT;};
	union{UINT32 HCINTMSK;struct USBFS_HCINT_BIT HCINTMSK_BIT;};
	union{UINT32 HCTSIZ;struct USBFS_HCTSIZ_BIT HCTSIZ_BIT;};
	UINT32 Reserved1[3];
};
//------------------------------------------------------------------------------------------------------------------------------
struct Struct_USBFS_DINEPS//0x900
{
  union{UINT32 DIEPCTL;struct USBFS_DIEPCTL_BITA DIEPCTL_BITA;struct USBFS_DIEPCTL_BITB DIEPCTL_BITB;};     //0x00,dev IN EP Ctl Reg
  UINT32 Reserved0[1];  //0x04,Reserved 
  union{UINT32 DIEPINT;struct USBFS_DIEPINT_BIT DIEPINT_BIT;};//0x08,dev IN EP Itr Reg
  UINT32 Reserved1[1];  //0x0C,Reserved
  union{UINT32 DIEPTSIZ;struct USBFS_DIEPTSIZ_BITA DIEPTSIZ_BITA;struct USBFS_DIEPTSIZ_BITB DIEPTSIZ_BITB;};//0x10,dev IN EP Tx Size
  UINT32 Reserved2[1];  //0x14,Reserved
  union{UINT32 DTXFSTS;struct USBFS_DTXFSTS_BIT DTXFSTS_BIT;};//0x18,IN EP TxFIFO Sts
  UINT32 Reserved3[1];  //0x1C,Reserved
};
//------------------------------------------------------------------------------------------------------------------------------
struct Struct_USBFS_DOUTEPS//0xB00
{
  union{UINT32 DOEPCTL;struct USBFS_DOEPCTL_BITA DOEPCTL_BITA;struct USBFS_DOEPCTL_BITA DOEPCTL_BITB;};//0x00,OUT EP Ctl Reg
  UINT32 Reserved0[1];  //0x04,Reserved
  union{UINT32 DOEPINT;struct USBFS_DOEPINT_BIT DOEPINT_BIT;};//0x08,OUT EP Itr Reg
  UINT32 Reserved1[1];  //0x0C,Reserved
  union{UINT32 DOEPTSIZ;struct USBFS_DOEPTSIZ_BITA DOEPTSIZ_BITA;struct USBFS_DOEPTSIZ_BITB DOEPTSIZ_BITB;}; //0x10,OUT EP Tx Size
  UINT32 Reserved2[3];  //0x14,Reserved
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define USBFS_Struct Struct_USBFS
typedef struct Struct_USBFS//0x50000000
{
  union{UINT32 GOTGCTL;struct USBFS_GOTGCTL_BIT GOTGCTL_BIT;};  //0x000,USB_OTG Control and Status reg
  union{UINT32 GOTGINT;struct USBFS_GOTGINT_BIT GOTGINT_BIT;};  //0x004,USB_OTG Interrupt Register
  union{UINT32 GAHBCFG;struct USBFS_GAHBCFG_BIT GAHBCFG_BIT;};  //0x008,Core AHB Configuration Register
  union{UINT32 GUSBCFG;struct USBFS_GUSBCFG_BIT GUSBCFG_BIT;};  //0x00C,Core USB Configuration Register
  union{UINT32 GRSTCTL;struct USBFS_GRSTCTL_BIT GRSTCTL_BIT;};  //0x010,Core Reset Register
  union{UINT32 GINTSTS;struct USBFS_GINT_BIT GINTSTS_BIT;};     //0x014,Core Interrupt Register
  union{UINT32 GINTMSK;struct USBFS_GINT_BIT GINTMSK_BIT;};     //0x018,Core Interrupt Mask Register
  union{UINT32 GRXSTSR;struct USBFS_GRXSTS_BITH GRXSTSR_BITH;struct USBFS_GRXSTS_BITD GRXSTSR_BITD;};   //0x01C,Receive Sts Q Read Register
  union{UINT32 GRXSTSP;struct USBFS_GRXSTS_BITH GRXSTSP_BITH;struct USBFS_GRXSTS_BITD GRXSTSP_BITD;};   //0x020,Receive Sts Q Read & POP Register
  union{UINT32 GRXFSIZ;struct USBFS_GRXFSIZ_BIT GRXFSIZ_BIT;};  //0x024,Receive FIFO Size Register
  union{UINT32 DIEPTXF0;struct USBFS_HNPTXFSIZ_BIT HNPTXFSIZ_BIT;struct USBFS_DIEPTXF0_BIT DIEPTXF0_BIT;};//0x028,EP0 Tx FIFO Size Register
  union{UINT32 HNPTXSTS;struct USBFS_HNPTXSTS_BIT HNPTXSTS_BIT;};//0x02C,Non Periodic Tx FIFO/Queue Sts reg
  UINT32 Reserved0[2];  //0x030,Reserved
  union{UINT32 GCCFG;struct USBFS_GCCFG_BIT GCCFG_BIT;};                //0x038,General Core configuration reg
  union{UINT32 CID;Type_BIT32 CID_BIT;};                                //0x03C,User ID Register
  UINT32 Reserved1[48]; //0x040,Reserved
  union{UINT32 HPTXFSIZ;struct USBFS_HPTXFSIZ_BIT HPTXFSIZ_BIT;};       //0x100,Host Periodic Tx FIFO Size Reg
  union{UINT32 DIEPTXF[3];struct USBFS_DIEPTXF_BIT DIEPTXF_BIT[3];};    //0x104,dev Transmit FIFO
	UINT32 Reserved2[188];//0x110,
	union{UINT32 HCFG;struct USBFS_HCFG_BIT HCFG_BIT;};           //0x400,
	union{UINT32 HFIR;struct USBFS_HFIR_BIT HFIR_BIT;};           //0x404,
	union{UINT32 HFNUM;struct USBFS_HFNUM_BIT HFNUM_BIT;};        //0x408,
	UINT32 Reserved3[1];  //0x40C,
	union{UINT32 HPTXSTS;struct USBFS_HPTXSTS_BIT HPTXSTS_BIT;};  //0x410,
	union{UINT32 HAINT;struct USBFS_HAINT_BIT HAINT_BIT;};        //0x414,
	union{UINT32 HAINTMSK;struct USBFS_HAINT_BIT HAINTMSK_BIT;};  //0x418,
	UINT32 Reserved4[9];  //0x41C,
	union{UINT32 HPRT;struct USBFS_HPRT_BIT HPRT_BIT;};           //0x440,
	UINT32 Reserved5[47]; //0x444,
	struct Struct_USBFS_HC HC[8]; //0x500,
	UINT32 Reserved6[128];//0x600,
  union{UINT32 DCFG;struct USBFS_DCFG_BIT DCFG_BIT;};           //0x800,dev Configuration Register
  union{UINT32 DCTL;struct USBFS_DCTL_BIT DCTL_BIT;};           //0x804,dev Control Register
  union{UINT32 DSTS;struct USBFS_DSTS_BIT DSTS_BIT;};           //0x808,dev Status Register (RO)
  UINT32 Reserved7[1];  //0x80C,Reserved
  union{UINT32 DIEPMSK;struct USBFS_DIEPMSK_BIT DIEPMSK_BIT;};  //0x810,dev IN Endpoint Mask
  union{UINT32 DOEPMSK;struct USBFS_DOEPMSK_BIT DOEPMSK_BIT;};  //0x814,dev OUT Endpoint Mask
  union{UINT32 DAINT;struct USBFS_DAINT_BIT DAINT_BIT;};        //0x818,dev All Endpoints Itr Reg
  union{UINT32 DAINTMSK;struct USBFS_DAINT_BIT DAINTMSK_BIT;};  //0x81C,dev All Endpoints Itr Mask
  UINT32 Reserved8[2];  //0x820,Reserved
  union{UINT32 DVBUSDIS;struct USBFS_DVBUSDIS_BIT DVBUSDIS_BIT;};       //0x828,dev VBUS discharge Register
  union{UINT32 DVBUSPULSE;struct USBFS_DVBUSPULSE_BIT DVBUSPULSE_BIT;}; //0x82C,dev VBUS Pulse Register
  UINT32 Reserved9[1];  //0x830,Reserved
  union{UINT32 DIEPEMPMSK;struct USBFS_DIEPEMPMSK_BIT DIEPEMPMSK_BIT;}; //0x834,IN EP FIFO empty int mask	
	UINT32 Reserved10[50];//0x838,
	struct Struct_USBFS_DINEPS    DI[4];//0x900,
	UINT32 Reserved11[96];//0x980,
	struct Struct_USBFS_DOUTEPS   DO[4];//0xB00,
	UINT32 Reserved12[160];//0xB80,
	union{UINT32 PCGCCTL;struct USBFS_PCGCCTL_BIT PCGCCTL_BIT;};  //0xE00,
} USBFS_Type,Type_USBFS;
#define PT_USBFS                ((volatile Type_USBFS *)BASE_USBFS) 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define USBFS_GOTGCTL           USBFS.GOTGCTL
#define USBFS_GOTGINT           USBFS.GOTGINT
#define USBFS_GAHBCFG           USBFS.GAHBCFG
#define USBFS_GUSBCFG           USBFS.GUSBCFG
#define USBFS_GRSTCTL           USBFS.GRSTCTL
#define USBFS_GINTSTS           USBFS.GINTSTS
#define USBFS_GINTMSK           USBFS.GINTMSK
#define USBFS_GRXSTSR           USBFS.GRXSTSR
#define USBFS_GRXSTSP           USBFS.GRXSTSP
#define USBFS_GRXFSIZ           USBFS.GRXFSIZ
#define USBFS_DIEPTXF0          USBFS.DIEPTXF0
#define USBFS_HNPTXSTS          USBFS.HNPTXSTS
#define USBFS_GCCFG             USBFS.GCCFG
#define USBFS_CID               USBFS.CID
#define USBFS_HPTXFSIZ          USBFS.HPTXFSIZ
#define USBFS_DIEPTXF(i)        USBFS.DIEPTXF[i]//i=0_2
#define USBFS_HCFG              USBFS.HCFG
#define USBFS_HFIR              USBFS.HFIR
#define USBFS_HFNUM             USBFS.HFNUM
#define USBFS_HPTXSTS           USBFS.HPTXSTS
#define USBFS_HAINT             USBFS.HAINT
#define USBFS_HAINTMSK          USBFS.HAINTMSK
#define USBFS_HPRT              USBFS.HPRT
#define USBFS_HCCHAR(i)         USBFS.HC[i].HCCHAR//i=0_7
#define USBFS_HCINT(i)          USBFS.HC[i].HCINT//i=0_7
#define USBFS_HCINTMSK(i)       USBFS.HC[i].HCINTMSK//i=0_7
#define USBFS_HCTSIZ(i)         USBFS.HC[i].HCTSIZ//i=0_7
#define USBFS_DCFG              USBFS.DCFG
#define USBFS_DCTL              USBFS.DCTL
#define USBFS_DSTS              USBFS.DSTS
#define USBFS_DIEPMSK           USBFS.DIEPMSK
#define USBFS_DOEPMSK           USBFS.DOEPMSK
#define USBFS_DAINT             USBFS.DAINT
#define USBFS_DAINTMSK          USBFS.DAINTMSK
#define USBFS_DVBUSDIS          USBFS.DVBUSDIS
#define USBFS_DVBUSPULSE        USBFS.DVBUSPULSE
#define USBFS_DIEPEMPMSK        USBFS.DIEPEMPMSK
#define USBFS_DIEPCTL(i)        USBFS.DI[i].DIEPCTL//i=0_3
#define USBFS_DIEPINT(i)        USBFS.DI[i].DIEPINT//i=0_3
#define USBFS_DIEPTSIZ(i)       USBFS.DI[i].DIEPTSIZ//i=0_3
#define USBFS_DTXFSTS(i)        USBFS.DI[i].DTXFSTS//i=0_3
#define USBFS_DOEPCTL(i)        USBFS.DO[i].DOEPCTL//i=0_3
#define USBFS_DOEPINT(i)        USBFS.DO[i].DOEPINT//i=0_3
#define USBFS_DOEPTSIZ(i)       USBFS.DO[i].DOEPTSIZ//i=0_3
#define USBFS_PCGCCTL           USBFS.PCGCCTL
//==============================================================================================================================
#define RSTV_DES_FLASHSIZE        0x00000000//0x1FFFF7E0,FLASH Size in kbytes
struct DES_FLASHSIZE_BIT
{
	UINT32 SIZE:16;      //00,FLASH memory Size of the device in Kbytes
	UINT32 Reserved0:16; //04,
};
//------------------------------------------------------------------------------------------------------------------------------
#define DES_Struct Struct_DES
typedef struct Struct_DES//0x1FFFF7E0,Device electronic signature
{
  union{UINT32 FLASHSIZE;struct DES_FLASHSIZE_BIT FLASHSIZE_BIT;};//0x000(R),Flash size
  UINT32 Reserved0[1];      //0x004(R),
  union{UINT32 UID[3];};    //0x008(R),96 bits
} DES_Type,Type_DES;
#define PT_DES                  ((volatile Type_DES *)BASE_DES)
//------------------------------------------------------------------------------------------------------------------------------
#define DES_FLASHSIZE           DES.FLASHSIZE
#define DES_UID(i)              DES.UID[i]
//==============================================================================================================================
//Core_CM3 CPU
//CPU Register
#define RSTV_APSR               0x00000000
typedef union CPU_APSR_REG//0x000
{
  struct CPU_APSR_BIT
  {
    UINT32 Reserved0:27;  //
    UINT32 Q:1;           //27,粘着饱和状态(sticky saturation)
    UINT32 V:1;           //28,溢出
    UINT32 C:1;           //02,进位/借位
    UINT32 Z:1;           //03,零
    UINT32 N:1;           //04,负数
  }BIT;
  UINT32 VAL;
} APSR_Type,Type_APSR;
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_IPSR               0x00000000
typedef union CPU_IPSR_REG//0x000
{
  struct CPU_IPSR_BIT
  {
    UINT32 IRQN:9;        //中断号:基础=0，NMI=2，SVCall=11,INTISR[0]=16,INTISR[1]=17,...
    UINT32 Reserved0:23;  //
  }BIT;
  UINT32 VAL;
} IPSR_Type,Type_IPSR;
//------------------------------------------------------------------------------------------------------------------------------
typedef union CPU_EPSR_REG//0x000
{
  struct CPU_EPSR_BIT//ICI
  {
    UINT32 Reserved0:10;  //0,
    UINT32 ICT_IT:6;      //10,ICT_IT：ICI_IT=if-then,包含指令数目与执行条件
    UINT32 Reserved1:8;   //16,
    UINT32 T:1;           //24,使用一条相互作用的指令来清零，当T=0时，引起INVSTATE异常
    UINT32 ICI_IT:2;      //25,
    UINT32 Reserved2:5;   //27,
  }BIT;
	UINT32               VAL;
} EPSR_Type,Type_EPSR;
//==============================================================================================================================
#define RSTV_ITM_PORT           0x00000000//0x000,
#define RSTV_ITM_TER            0x00000000//0x000,
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_TPR            0x00000000//0xE00,
struct ITM_TPR_BIT
{
	UINT32 PRIVMASK:4;   //00,PRIVMASK
	UINT32 Reserved0:28; //04,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_TCR            0x00000000//0xE80,ITM Trace Control Register Definitions
struct ITM_TCR_BIT
{
	UINT32 ITMENA:1;     //00,ITM Enable bit
	UINT32 TSENA:1;      //01,
	UINT32 SYNCENA:1;    //02,
	UINT32 DWTENA:1;     //03,
	UINT32 SWOENA:1;     //04,
	UINT32 Reserved0:3;  //05,
	UINT32 TSPrescale:2; //08,
	UINT32 Reserved1:6;  //10,
	UINT32 ATBID:3;      //16,
	UINT32 Reserved2:4;  //19,
	UINT32 BUSY:1;       //23,
	UINT32 Reserved3:8;  //24,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_IWR            0x00000000//0xEF8,ITM Integration Write Register Definitions
struct ITM_IWR_BIT
{
	UINT32 ATVALIDM:1;   //00,
	UINT32 Reserved0:31; //01,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_IRR            0x00000000//0xEFC,ITM Integration Read Register Definitions
struct ITM_IRR_BIT
{
	UINT32 ATREADYM:1;   //00,
	UINT32 Reserved0:31; //01,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_IMCR           0x00000000//0xF00,ITM Integration Mode Control Register Definitions
struct ITM_IMCR_BIT
{
	UINT32 NTEGRATION:1; //00,
	UINT32 Reserved0:31; //01,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_LAR            0x00000000//0xFB0,
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ITM_LSR            0x00000003//0xFB4,ITM Lock Status Register Definitions
struct ITM_LSR_BIT
{
	UINT32 Present:1;    //00,
	UINT32 Access:1;     //01,
	UINT32 ByteAcc:1;    //02,
	UINT32 Reserved0:29; //03,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ITM_Struct Struct_ITM
typedef struct Struct_ITM//0xE0000000
{
  union{UINT32 PORT[32];Type_BIT32 PORT_BIT[32];Type_UINT32_BIT8 PORT_B8[32];Type_UINT32_BIT16 PORT_B16[32];};//0x000(W),ITM Stimulus Port Registers
  UINT32 Reserved0[864]; //0x080(R),                                
  union{UINT32 TER;Type_BIT32 TER_BIT;};//0xE00(RW),ITM Trace Enable Register
  UINT32 Reserved1[15];  //0xE04(R),                                
  union{UINT32 TPR;struct ITM_TPR_BIT TPR_BIT;};//0xE40(RW),ITM Trace Privilege Register
  UINT32 Reserved2[15];  //0xE44(R),                                
  union{UINT32 TCR;struct ITM_TCR_BIT TCR_BIT;};//0xE80,ITM Trace Control Register
  UINT32 Reserved3[29];  //0xE84(R),                          
  union{UINT32 IWR;struct ITM_IWR_BIT IWR_BIT;};//0xEF8(RW),ITM Integration Write Register
  union{UINT32 IRR;struct ITM_IRR_BIT IRR_BIT;};//0xEFC(RW),ITM Integration Read Register
  union{UINT32 IMCR;struct ITM_IMCR_BIT IMCR_BIT;};//0xF00(RW),ITM Integration Mode Control Register
  UINT32 Reserved4[43];  //0xF04(R),                             
  union{UINT32 LAR;Type_BIT32 LAR_BIT;};        //0xFB0(RW),ITM Lock Access Register
  union{UINT32 LSR;struct ITM_LSR_BIT LSR_BIT;};//0xFB4(RW),ITM Lock Status Register
  UINT32 Reserved5[6];  //0xFB8(R),
  union{UINT32 PID4;};//0xFD0(R),ITM Peripheral Identification Register #4
  union{UINT32 PID5;};//0xFD4(R),ITM Peripheral Identification Register #5
  union{UINT32 PID6;};//0xFD8(R),ITM Peripheral Identification Register #6
  union{UINT32 PID7;};//0xFDC(R),ITM Peripheral Identification Register #7
  union{UINT32 PID0;};//0xFE0(R),ITM Peripheral Identification Register #0
  union{UINT32 PID1;};//0xFE4(R),ITM Peripheral Identification Register #1
  union{UINT32 PID2;};//0xFE8(R),ITM Peripheral Identification Register #2
  union{UINT32 PID3;};//0xFEC(R),ITM Peripheral Identification Register #3
  union{UINT32 CID0;};//0xFF0(R),ITM Component  Identification Register #0
  union{UINT32 CID1;};//0xFF4(R),ITM Component  Identification Register #1
  union{UINT32 CID2;};//0xFF8(R),ITM Component  Identification Register #2
  union{UINT32 CID3;};//0xFFC(R),ITM Component  Identification Register #3
} ITM_Type,Type_ITM;
#define PT_M3ITM                ((volatile Type_ITM *)BASE_ITM)        
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ITM_PORT(i)             ITM.PORT[i]
#define ITM_TER                 ITM.TER
#define ITM_TPR                 ITM.TPR
#define ITM_TCR                 ITM.TCR
#define ITM_IWR                 ITM.IWR
#define ITM_IRR                 ITM.IRR
#define ITM_IMCR                ITM.IMCR
#define ITM_LAR                 ITM.LAR
#define ITM_LSR                 ITM.LSR
#define ITM_PID4                ITM.PID4
#define ITM_PID5                ITM.PID5
#define ITM_PID6                ITM.PID6
#define ITM_PID7                ITM.PID7
#define ITM_PID0                ITM.PID0
#define ITM_PID1                ITM.PID1
#define ITM_PID2                ITM.PID2
#define ITM_PID3                ITM.PID3
#define ITM_CID0                ITM.CID0
#define ITM_CID1                ITM.CID1
#define ITM_CID2                ITM.CID2
#define ITM_CID3                ITM.CID3
//==============================================================================================================================
#define RSTV_DWT_CTRL           0x40000000//0x000,DWT
struct DWT_CTRL_BIT
{
	UINT32 Reserved0:1;  //00,
	UINT32 POSTPRST:4;   //01,
	UINT32 POSTCNT:4;    //05,
	UINT32 CYCTAP:1;     //09,
	UINT32 SYNCTAP:2;    //10,
	UINT32 PCSAMPLENA:1; //12,
	UINT32 Reserved1:3;  //13,
	UINT32 EXCTRCENA:1;  //16,
	UINT32 CPIEVTENA:1;  //17,
	UINT32 EXCEVTENA:1;  //18,
	UINT32 SLEEPEVTENA:1;//19,
	UINT32 LSUEVTENA:1;  //20,
	UINT32 FOLDEVTENA:1; //21,
	UINT32 CYCEVTENA:1;  //22,
	UINT32 Reserved2:5;  //23,
	UINT32 NUMCOMP:4;    //28,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_CYCCNT         0x00000000//0x004,DWT,采样器周期计数器
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_CPICNT         0x00000000//0x008,DWT
struct DWT_CPICNT_BIT
{
	UINT32 CPICNT:8;     //00,
	UINT32 Reserved0:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_EXCCNT         0x00000000//0x00C,DWT
struct DWT_EXCCNT_BIT
{
	UINT32 EXCCNT:8;     //00,
	UINT32 Reserved0:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_SLEEPCNT       0x00000000//0x010,DWT
struct DWT_SLEEPCNT_BIT
{
	UINT32 SLEEPCNT:8;   //00,
	UINT32 Reserved0:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_LSUCNT         0x00000000//0x014,WDT
struct DWT_LSUCNT_BIT
{
	UINT32 LSUCNT:8;     //00,
	UINT32 Reserved0:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_FOLDCNT        0x00000000//0x018,DWT
struct DWT_FOLDCNT_BIT
{
	UINT32 FOLDCNT:8;    //00,
	UINT32 Reserved0:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_COMP0          0x00000000//0x020,DWT
#define RSTV_DWT_COMP1          0x00000000//0x030,DWT
#define RSTV_DWT_COMP2          0x00000000//0x040,DWT
#define RSTV_DWT_COMP3          0x00000000//0x050,DWT
#define RSTV_DWT_COMP           0x00000000
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_MASK0          0x00000000//0x024,WDT
#define RSTV_DWT_MASK1          0x00000000//0x034,WDT
#define RSTV_DWT_MASK2          0x00000000//0x044,WDT
#define RSTV_DWT_MASK3          0x00000000//0x054,WDT
#define RSTV_DWT_MASK           0x00000000
struct DWT_MASK_BIT//MASK0,MASK1,MASK2,MASK3
{
	UINT32 MASK:4;       //00,
	UINT32 Reserved0:28; //04,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_FUNC0          0x00000000//0x028,DWT
#define RSTV_DWT_FUNC1          0x00000000//0x038,DWT
#define RSTV_DWT_FUNC2          0x00000000//0x048,DWT
#define RSTV_DWT_FUNC3          0x00000000//0x058,DWT
#define RSTV_DWT_FUNC           0x00000000
struct DWT_FUNC_BIT//FUNC0,FUNC1,FUNC2,FUNC3
{
	UINT32 FUNC:4;       //00,
	UINT32 Reserved0:1;  //04,
	UINT32 EMITRANGE:1;  //05,
	UINT32 Reserved1:1;  //06,
	UINT32 CYCMATCH:1;   //07,
	UINT32 Reserved2:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DWT_PID4           0x00000004//0xFD0,
#define RSTV_DWT_PID5           0x00000000//0xFD4,
#define RSTV_DWT_PID6           0x00000000//0xFD8,
#define RSTV_DWT_PID7           0x00000000//0xFDC,
#define RSTV_DWT_PID0           0x00000002//0xFE0,
#define RSTV_DWT_PID1           0x000000B0//0xFE4,
#define RSTV_DWT_PID2           0x0000000B//0xFE8,
#define RSTV_DWT_PID3           0x00000000//0xFEC,
#define RSTV_DWT_PID            0x00000000
#define RSTV_DWT_CID0           0x0000000D//0xFF0,
#define RSTV_DWT_CID1           0x000000E0//0xFF4,
#define RSTV_DWT_CID2           0x00000005//0xFF8,
#define RSTV_DWT_CID3           0x000000B1//0xFFC,
#define RSTV_DWT_CID            0x00000000
//------------------------------------------------------------------------------------------------------------------------------
struct Struct_DWT_CMF
{
	union{UINT32 COMP;Type_BIT32 COMP_BIT;};//比较
	union{UINT32 MASK;struct DWT_MASK_BIT MASK_BIT;};//屏蔽
	union{UINT32 FUNC;struct DWT_FUNC_BIT FUNC_BIT;};//功能
	UINT32 Reserved0[1];
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DWT_Struct Struct_DWT
typedef struct Struct_DWT//0xE0001000
{
  union{UINT32 CTRL;struct DWT_CTRL_BIT CTRL_BIT;};//0x000(RW),DWT
  union{UINT32 CYCCNT;Type_BIT32 CYCCNT_BIT;};  //0x004(RW),DWT
  union{UINT32 CPICNT;struct DWT_CPICNT_BIT CPICNT_BIT;};//0x008(RW),DWT
  union{UINT32 EXCCNT;struct DWT_EXCCNT_BIT EXCCNT_BIT;};//0x00C(RW),DWT
  union{UINT32 SLEEPCNT;struct DWT_SLEEPCNT_BIT SLEEPCNT_BIT;};//0x010(RW),DWT
  union{UINT32 LSUCNT;struct DWT_LSUCNT_BIT LSUCNT_BIT;};//0x014(RW),DWT
  union{UINT32 FOLDCNT;struct DWT_FOLDCNT_BIT FOLDCNT_BIT;};//0x018(RW),DWT
	UINT32 Reserved6[1];      //0x01C(R),
  struct Struct_DWT_CMF CMF[4]; //0x020(RW),DWT
	UINT32 Reserved7[988]; //0x060(R),
  union{UINT32 PID4;};//0xFD0(RW),ITM Peripheral Identification Register
  union{UINT32 PID5;};//0xFD4(RW),ITM Peripheral Identification Register
  union{UINT32 PID6;};//0xFD8(RW),ITM Peripheral Identification Register
  union{UINT32 PID7;};//0xFDC(RW),ITM Peripheral Identification Register
  union{UINT32 PID0;};//0xFE0(RW),ITM Peripheral Identification Register
  union{UINT32 PID1;};//0xFE4(RW),ITM Peripheral Identification Register
  union{UINT32 PID2;};//0xFE8(RW),ITM Peripheral Identification Register
  union{UINT32 PID3;};//0xFEC(RW),ITM Peripheral Identification Register
  union{UINT32 CID0;};//0xFF0(RW),ITM Component  Identification Register
  union{UINT32 CID1;};//0xFF4(RW),ITM Component  Identification Register
  union{UINT32 CID2;};//0xFF8(RW),ITM Component  Identification Register
  union{UINT32 CID3;};//0xFFC(RW),ITM Component  Identification Register
} DWT_Type,Type_DWT;                                                
#define PT_M3DWT                ((volatile Type_DWT *)BASE_DWT)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DWT_CTRL                DWT.CTRL
#define DWT_CYCCNT              DWT.CYCCNT
#define DWT_CPICNT              DWT.CPICNT
#define DWT_EXCCNT              DWT.EXCCNT
#define DWT_SLEEPCNT            DWT.SLEEPCNT
#define DWT_LSUCNT              DWT.LSUCNT
#define DWT_FOLDCNT             DWT.FOLDCNT
#define DWT_CMF_COMP(i)         DWT.CMF[i].COMP//i=0_3
#define DWT_CMF_MASK(i)         DWT.CMF[i].MASK//i=0_3
#define DWT_CMF_FUNC(i)         DWT.CMF[i].FUNC//i=0_3
#define DWT_PID4                DWT.PID4
#define DWT_PID5                DWT.PID5
#define DWT_PID6                DWT.PID6
#define DWT_PID7                DWT.PID7
#define DWT_PID0                DWT.PID0
#define DWT_PID1                DWT.PID1
#define DWT_PID2                DWT.PID2
#define DWT_PID3                DWT.PID3
#define DWT_CID0                DWT.CID0
#define DWT_CID1                DWT.CID1
#define DWT_CID2                DWT.CID2
#define DWT_CID3                DWT.CID3
//==============================================================================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FPB_Struct Struct_FPB
typedef struct Struct_FPB//0xE0002000
{
  union{UINT32 CTRL;};   //0xE0002000(RW),修补控制
	union{UINT32 REMAP;};  //0xE0002004(RW),修补重映射
	union{UINT32 COMP[8];};//0xE0002008(RW),修补比较
	UINT32 Reserved0[1002];//0xE0002028(R),
  union{UINT32 PID4;};//0xE0002FD0(RW),Value=0x04,FP Peripheral Identification Register
  union{UINT32 PID5;};//0xE0002FD4(RW),Value=0x00,FP Peripheral Identification Register
  union{UINT32 PID6;};//0xE0002FD8(RW),Value=0x00,FP Peripheral Identification Register
  union{UINT32 PID7;};//0xE0002FDC(RW),Value=0x00,FP Peripheral Identification Register
  union{UINT32 PID0;};//0xE0002FE0(RW),Value=0x30,FP Peripheral Identification Register
  union{UINT32 PID1;};//0xE0002FE4(RW),Value=0xB0,FP Peripheral Identification Register
  union{UINT32 PID2;};//0xE0002FE8(RW),Value=0x0B,FP Peripheral Identification Register
  union{UINT32 PID3;};//0xE0002FEC(RW),Value=0x00,FP Peripheral Identification Register
  union{UINT32 CID0;};//0xE0002FF0(RW),Value=0x0D,FP Component  Identification Register
  union{UINT32 CID1;};//0xE0002FF4(RW),Value=0xE0,FP Component  Identification Register
  union{UINT32 CID2;};//0xE0002FF8(RW),Value=0x05,FP Component  Identification Register
  union{UINT32 CID3;};//0xE0002FFC(RW),Value=0xB1,FP Component  Identification Register	
} FPB_Type,Type_FPB;  
#define PT_M3FPB                ((volatile Type_FPB *)BASE_FPB)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FPB_CTRL                M3FPB.CTRL
#define FPB_REMAP               M3FPB.REMAP
#define FPB_COMP(i)             M3FPB.COMP[i]
#define FPB_PID4                M3FPB.PID4
#define FPB_PID5                M3FPB.PID5
#define FPB_PID6                M3FPB.PID6
#define FPB_PID7                M3FPB.PID7
#define FPB_PID0                M3FPB.PID0
#define FPB_PID1                M3FPB.PID1
#define FPB_PID2                M3FPB.PID2
#define FPB_PID3                M3FPB.PID3
#define FPB_CID0                M3FPB.CID0
#define FPB_CID1                M3FPB.CID1
#define FPB_CID2                M3FPB.CID2
#define FPB_CID3                M3FPB.CID3
//==============================================================================================================================
#define RSTV_SYS_ICTR           0x00000000//0x004,Interrupt Controller Type Register Definitions
struct SYS_ICTR_BIT
{
	UINT32 INTLINESNUM:5;//00,
	UINT32 Reserved0:27; //05,
};
#define SYS_ICTR_INTLINESNUM    M3SYS.ICTR_BIT.INTLINESNUM
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_ACTLR          0x00000000//0x008,Auxiliary Control Register Definitions
struct SYS_ACTLR_BIT
{
	UINT32 DISMCYCINT:1; //00,
	UINT32 DISDEFWBUF:1; //01,
	UINT32 DISFOLD:1;    //02,
	UINT32 Reserved0:29; //03,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_STCTRL         0x00000000//0xE000E010
struct SYS_STCTRL_BIT
{
  UINT32 EN:1;         //00,Counter enable:1=enable
  UINT32 TICKINT:1;    //01,interrupt enable,Counting down to 0 pends the SysTick handler:1=enable
  UINT32 CLKSOURCE:1;  //02,Clock source:0=Extenal reference clock,1=core clock
	UINT32 Reserved0:13; //03,
  UINT32 COUNTFLAG:1;  //16,Count Flag
	UINT32 Reserved1:15; //17,
};
#define SYS_STCTRL_ENABLE       M3SYS.STCTRL_BIT.ENABLE
#define SYS_STCTRL_TICKINT      M3SYS.STCTRL_BIT.TICKINT
#define SYS_STCTRL_CLKSOURCE    M3SYS.STCTRL_BIT.CLKSOURCE
#define SYS_STCTRL_COUNTFLAG    M3SYS.STCTRL_BIT.COUNTFLAG
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_STLOAD         0x00000000//0xE000E014
struct SYS_STLOAD_BIT
{
  UINT32 RELOAD:24;    //00,Value to load into the SysTick Current Value Register when the counter reaches 0
	UINT32 Reserved0:8;  //24,
};
#define SYS_STLOAD_RELOAD       M3SYS.STLOAD_BIT.RELOAD
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_STVAL          0x00000000//0xE000E018
struct SYS_STVAL_BIT
{
  UINT32 CURRENT:24;   //00,Current value at the time the register is accessed
	UINT32 Reserved0:8;  //24,
};
#define SYS_STVAL_CURRENT       M3SYS.STVAL_BIT.CURRENT
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_STCALIB        0x00000000//0xE000E01C
struct SYS_STCALIB_BIT
{
  UINT32 TENMS:24;     //00,Reload value to use for 10ms timing
	UINT32 Reserved0:6;  //24,
	UINT32 SKEW:1;       //30,Calibration value is not exactly 10 ms
	UINT32 NOREF:1;      //31,The reference clock is not provided
};
#define SYS_STCALIB_TENMS       M3SYS.STCALIB_BIT.TENMS
#define SYS_STCALIB_SKEW        M3SYS.STCALIB_BIT.SKEW
#define SYS_STCALIB_NOREF       M3SYS.STCALIB_BIT.NOREF
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_ISER           0x00000000//Interrupt set enable bits
#define RSTV_SYS_ICER           0x00000000//Interrupt clear-enable bits
#define RSTV_SYS_ISPR           0x00000000//Interrupt set-pending bits
#define RSTV_SYS_ICPR           0x00000000//Interrupt clear-pending bits
#define RSTV_SYS_IABR           0x00000000//Interrupt active flags
#define RSTV_SYS_IPR            0x00;     //Interrupt Priority Register (8Bit wide)
//------------------------------------------------------------------------------------------------------------------------------
//SCB_Start
#define RSTV_SYS_CPUID           0x410FC230//0xE000ED00,
struct SYS_CPUID_BIT
{
	UINT32 REVISION:4;   //00,Implementation defined revision number
	UINT32 PARTNO:12;    //04,Number of processor within family
	UINT32 Constant:4;   //16,Reads as 0x0F
	UINT32 VARIANT:4;    //20,Implementation defined variant number
	UINT32 IMPLEMENTER:8;//24,Implementer code. ARM is 0x41
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_ICSR            0x00000000//0xE000ED04
struct SYS_ICSR_BIT
{
	UINT32 VECTACTIVE:9;   //00,Active ISR number field
	UINT32 Reserved0:2;    //09,
	UINT32 RETTOBASE:1;    //11,All active exceptions minus the IPSR_current_exception yields the empty set
	UINT32 VECTPENDING:10; //12,Pending ISR number field
	UINT32 ISRPENDING:1;   //22,Interrupt pending flag
	UINT32 ISRPREEMPT:1;   //23,It indicates that a pending interrupt becomes active in the next running cycle
	UINT32 Reserved1:1;    //24,
	UINT32 PENDSTCLR:1;    //25,Clear pending SysTick bit
	UINT32 PENDSTSET:1;    //26,Set pending SysTick bit
	UINT32 PENDSVCLR:1;    //27,Clear pending pendSV bit
	UINT32 PENDSVSET:1;    //28,Set pending pendSV bit
	UINT32 NMIPENDSET:1;   //29,Set pending NMI bit
	UINT32 Reserved2:2;    //30,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_VTOR           0x00000000//0xE000ED08
struct SYS_VTOR_BIT
{
	UINT32 Reserved0:7;    //00,
	UINT32 TBLOFF:22;      //07,Vector table base offset field
	UINT32 TBLBASE:1;      //29,Table base in code(0) or RAM(1)
	UINT32 Reserved1:2;    //30,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_AIRCR          0x00000000//E000ED0C
struct SYS_AIRCR_BIT
{
	UINT32 VECTRESET:1;    //00,System Reset bit
	UINT32 VECTCLRACTIVE:1;//01,Clear active vector bit
	UINT32 SYSRESETREQ:1;  //02,Requests chip control logic to generate a reset
	UINT32 Reserved0:5;    //03,
	UINT32 PRIGROUP:3;     //08,PRIGROUP[2:0] bits (Priority group),0_7=(7-x bits of pre-emption priority, x-3 bit of subpriority)
	UINT32 Reserved1:4;    //11,
	UINT32 ENDIANESS:1;    //15,Data endianness bit
	UINT32 VECTKEY:16;     //16,Register key (VECTKEY) - Reads as 0xFA05 (VECTKEYSTAT)
};

#define PRIGROUP_0              0x07//0 bits for pre-emption priority,4 bits for subpriority
#define PRIGROUP_1              0x06//1 bits for pre-emption priority,3 bits for subpriority
#define PRIGROUP_2              0x05//2 bits for pre-emption priority,2 bits for subpriority
#define PRIGROUP_3              0x04//3 bits for pre-emption priority,1 bits for subpriority
#define PRIGROUP_4              0x03//4 bits for pre-emption priority,0 bits for subpriority
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_SCR             0x00000000//E000ED10
struct SYS_SCR_BIT
{
	UINT32 Reserved0:1;    //00,
	UINT32 SLEEPONEXIT:1;  //01,Sleep on exit bit
	UINT32 SLEEPDEEP:1;    //02,Sleep deep bit
	UINT32 Reserved1:1;    //03,
	UINT32 SEVONPEND:1;    //04,Wake up from WFE
	UINT32 Reserved2:27;   //05,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_CCR            0x00000000//0xE000ED14
struct SYS_CCR_BIT
{
	UINT32 NONBASETHRDENA:1;    //00,Thread mode can be entered from any level in Handler mode by controlled return value
	UINT32 USERSETMPEND:1; //01,Enables user code to write the Software Trigger Interrupt register to trigger (pend) a Main exception
	UINT32 Reserved0:1;    //02,
	UINT32 UNALIGNTRP:1;   //03,Trap for unaligned access
	UINT32 DIV_0_TRP:1;    //04,Trap on Divide by 0
	UINT32 Reserved1:3;    //05,
	UINT32 BFHFNMIGN:1;    //08,Handlers running at priority -1 and -2
	UINT32 STKALIGN:1;     //09,On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned
	UINT32 Reserved2:22;   //10,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_SHPR           0x00000000//E000ED18
struct SYS_SHPR_BIT
{
	UINT32 PRI0:8;         //00,Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor
	UINT32 PRI1:8;         //08,Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved 
	UINT32 PRI2:8;         //16,Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV
	UINT32 PRI3:8;         //24,Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick

};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_SHCSR          0x00000000//0xE000ED24
struct SYS_SHCSR_BIT
{
	UINT32 MEMFAULTACT:1;  //00,MemManage is active
	UINT32 BUSFAULTACT:1;  //01,BusFault is active
	UINT32 Reserved0:1;    //02,
	UINT32 USGFAULTACT:1;  //03,UsageFault is active
	UINT32 Reserved1:3;    //04,
	UINT32 SVCALLACT:1;    //07,SVCall is active
  UINT32 MONITORACT:1;   //08,Monitor is active
	UINT32 Reserved2:1;    //09,	
	UINT32 PENDSVACT:1;    //10,PendSV is active
	UINT32 SYSTICKACT:1;   //11,SysTick is active
	UINT32 USGFAULTPENDED:1;//12,Usage Fault is pended
	UINT32 MEMFAULTPENDED:1;//13,MemManage is pended
	UINT32 BUSFAULTPENDED:1;//14,Bus Fault is pended
	UINT32 SVCALLPENDED:1;  //15,SVCall is pended
	UINT32 MEMFAULTENA:1;   //16,MemManage enable
	UINT32 BUSFAULTENA:1;   //17,Bus Fault enable
	UINT32 USGFAULTENA:1;   //18,UsageFault enable
	UINT32 Reserved3:13;    //19,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_CFSR           0x00000000//0xE000ED28
struct SYS_CFSR_BIT
{
	UINT32 IACCVIOL:1;   //00,Instruction access violation
	UINT32 DACCVIOL:1;   //01,Data access violation
	UINT32 Reserved0:1;  //02,
	UINT32 MUNSTKERR:1;  //03,Unstacking error
	UINT32 MSTKERR:1;    //04,Stacking error
	UINT32 Reserved1:2;  //05,
  UINT32 MMARVALID:1;  //07,Memory Manage Address Register address valid flag
	UINT32 IBUSERR:1;    //08,Instruction bus error flag
	UINT32 PRECISERR:1;  //09,Precise data bus error
	UINT32 IMPRECISERR:1;//10,Imprecise data bus error
	UINT32 UNSTKERR:1;   //11,Unstacking error
	UINT32 STKERR:1;     //12,Stacking error
	UINT32 Reserved2:2;  //13,
	UINT32 BFARVALID:1;  //15,Bus Fault Address Register address valid flag
	UINT32 UNDEFINSTR:1; //16,The processor attempt to execute an undefined instruction
	UINT32 INVSTATE:1;   //17,Invalid combination of EPSR and instruction
	UINT32 INVPC:1;      //18,Attempt to load EXC_RETURN into pc illegally
	UINT32 NOCP:1;       //19,Attempt to use a coprocessor instruction
	UINT32 Reserved3:4;  //20,
	UINT32 UNALIGNED:1;  //24,Fault occurs when there is an attempt to make an unaligned memory access
	UINT32 DIVBYZERO:1;  //25,Fault occurs when SDIV or DIV instruction is used with a divisor of 0
	UINT32 Reserved4:6;  //26;
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_HFSR           0x00000000//0xE000ED2C
struct SYS_HFSR_BIT
{
	UINT32 Reserved0:1;  //00,
	UINT32 VECTTBL:1;    //01,Fault occurs because of vector table read on exception processing
	UINT32 Reserved1:28; //02,
	UINT32 FORCED:1;     //30,Hard Fault activated when a configurable Fault was received and cannot activate
	UINT32 DEBUGEVT:1;   //31,Fault related to debug
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_DFSR           0x00000000//0xE000ED30
struct SYS_DFSR_BIT
{
	UINT32 HALTED:1;     //00,Halt request flag
	UINT32 BKPT:1;       //01,BKPT flag
	UINT32 DWTTRAP:1;    //02,Data Watchpoint and Trace (DWT) flag
	UINT32 VCATCH:1;     //03,Vector catch flag
	UINT32 EXTERNAL:1;   //04,External debug request flag
	UINT32 Reserved0:27; //05,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_MMFAR          0x00000000//0xE000ED34,Mem Manage fault address field
#define RSTV_SYS_BFAR           0x00000000//0xE000ED38,Bus fault address field
#define RSTV_SYS_AFSR           0x00000000//0xE000ED3C,Auxiliary Fault Status Register
#define RSTV_SYS_PFR            0x00000000//0xE000ED40,Processor Feature Register
#define RSTV_SYS_DFR            0x00000000//0xE000ED48,Debug Feature Register
#define RSTV_SYS_AFR            0x00000000//0xE000ED4C,Auxiliary Feature Register
#define RSTV_SYS_MMFR           0x00000000//0xE000ED50,Memory Model Feature Register
#define RSTV_SYS_ISAR           0x00000000//0xE000ED60,ISA Feature Register
//------------------------------------------------------------------------------------------------------------------------------
//MPU_Start
#define RSTV_SYS_TYPE           0x00000000//0xE000ED90,MPU Type Register
struct SYS_TYPE_BIT
{
	UINT32 SEPARATE:1;   //00,This is always 0 because the MPU is always unified
	UINT32 Reserved0:7;  //01,
	UINT32 DREGION:8;    //08,Number of regions supported by this MPU
	UINT32 IREGION:8;    //16,Number Instruction region; because ARM v7-M architecture uses a unifi ed MPU, this is always 0
	UINT32 Reserved1:8;  //24,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_CTRL           0x00000000//0xE000ED94,MPU Control Register
struct SYS_CTRL_BIT
{
	UINT32 EN:1;         //00,Enable the MPU if set to 1:1=Enable
	UINT32 HFNMIENA:1;   //01,If set to 1, enable MPU during hard fault handler and NMI handler; otherwise, the MPU is not enabled for the hard fault handler and NMI
	UINT32 PRIVDEFENA:1; //02,Privileged default memory map enable
	UINT32 Reserved1:29; //03,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_RNR            0x00000000//0xE000ED98,MPU Region Number Register
struct SYS_RNR_BIT
{
	UINT32 REGION:8;     //00,
	UINT32 Reserved1:24; //08,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_RBAR           0x00000000//0x00C,MPU Region Base Address Register
struct SYS_RBAR_BIT
{
	UINT32 REGION:4;     //00,
	UINT32 VALID:1;      //04,
	UINT32 ADDR:27;      //05,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_RASR           0x00000000//0x010,MPU Region Attribute and Size Register
struct SYS_RASR_BIT
{
	UINT32 ENA:1;        //00,Region enable bit
	UINT32 SIZE:5;       //01,Region Size Field
	UINT32 Reserved0:2;  //06,
	UINT32 SRD:8;        //08,Sub-Region Disable
	UINT32 B:1;          //16,Bufferable
	UINT32 C:1;          //17,Cacheable
	UINT32 S:1;          //18,Shareable
	UINT32 TEX:3;        //19,
	UINT32 Reserved1:2;  //22,
	UINT32 AP:3;         //24,
	UINT32 Reserved2:1;  //27,
	UINT32 XN:1;         //28,
	UINT32 Reserved3:3;  //29,
};
//MPU_END
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_DHCSR          0x00000000//0xe000edf0,Debug Halting Control and Status Register
struct SYS_DHCSR_BIT
{
	UINT32 C_DEBUGEN:1;  //00,
	UINT32 C_HALT:1;     //01,
	UINT32 C_STEP:1;     //02,
	UINT32 C_MASKINTS:1; //03,
	UINT32 Reserved0:1;  //04,
	UINT32 C_SNAPSTALL:1;//05,
	UINT32 Reserved1:10; //06,
	UINT32 S_REGRDY:1;   //16,
	UINT32 S_HALT:1;     //17,
	UINT32 S_SLEEP:1;    //18,
	UINT32 S_LOCKUP:1;   //19,
	UINT32 Reserved2:4;  //20,
	UINT32 S_RETIRE_ST:1;//24,
	UINT32 S_RESET_ST:1; //25,
	UINT32 DBGKEY:6;     //26,<LDY>
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_DCRSR          0x00000000//0x004,Debug Core Register Selector Register
struct SYS_DCRSR_BIT
{
	UINT32 REGSEL:5;     //00,
	UINT32 Reserved0:11; //05,
	UINT32 REGWNR:1;     //16,
	UINT32 Reserved1:15; //17,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_DEMCR          0x00000000//0x00C,Debug Exception and Monitor Control Register
struct SYS_DEMCR_BIT
{
	UINT32 VC_CORERST:1; //00,VC_CORERESET
	UINT32 Reserved0:3;  //01,
	UINT32 VC_MMERR:1;   //04,
	UINT32 VC_NOCPERR:1; //05,
	UINT32 VC_CHKERR:1;  //06,
	UINT32 VC_STATERR:1; //07,
	UINT32 VC_BUSERR:1;  //08,
	UINT32 VC_INTERR:1;  //09,
	UINT32 VC_HARDERR:1; //10,
	UINT32 Reserved1:5;  //11,
	UINT32 MON_EN:1;     //16,
	UINT32 MON_PEND:1;   //17,
	UINT32 MON_STEP:1;   //18,
	UINT32 MON_REQ:1;    //19,
	UINT32 Reserved2:4;  //20,
	UINT32 TRCENA:1;     //24,
	UINT32 Reserved3:7;  //25,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_SYS_STIR           0x00000000//0xE000EF00,Software Trigger Interrupt Register
struct SYS_STIR_BIT
{
	UINT32 INTID:9;      //00,Halt request flag
	UINT32 Reserved0:23; //09,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
#define SYS_Struct Struct_SYS
typedef struct Struct_SYS//0xE000E000
{
  //SYS_Start,SCS_Start
  UINT32 Reserved0[1];//0xE000E000,
  union{UINT32 ICTR;struct SYS_ICTR_BIT ICTR_BIT;};      //0xE000E004(R),Interrupt Control Type Register
  union{UINT32 ACTLR;struct SYS_ACTLR_BIT ACTLR_BIT;};   //0xE000E008(RW),Auxiliary Control Register ,for __CM3_REV >= 0x200
	UINT32 Reserved1[1];//0xE000E00C,
  //Systick_Start,SCS_End
  union{UINT32 STCTRL;struct SYS_STCTRL_BIT STCTRL_BIT;};   //0xE000E010(RW),SysTick Control and Status Register
  union{UINT32 STLOAD;struct SYS_STLOAD_BIT STLOAD_BIT;};   //0xE000E014(RW),SysTick Reload Value Register
  union{UINT32 STVAL;struct SYS_STVAL_BIT STVAL_BIT;};      //0xE000E018(RW),SysTick Current Value Register
  union{UINT32 STCALIB;struct SYS_STCALIB_BIT STCALIB_BIT;};//0xE000E01C(R),SysTick Calibration Register
	//Systick_End
	UINT32 Reserved2[0x38];//0xE000E020(R),
  //Interrupt_Start
  union{UINT32 ISER[8];Type_BIT32 ISER_BIT[8];};    //0xE000E100,  Interrupt Set Enable Register
  UINT32 Reserved3[24];//0xE000E120(R),                                   
  union{UINT32 ICER[8];Type_BIT32 ICER_BIT[8];};    //0xE000E180,  Interrupt Clear Enable Register
  UINT32 Reserved4[24];//0xE000E1A0(R),                                    
  union{UINT32 ISPR[8];Type_BIT32 ISPR_BIT[8];};    //0xE000E200,  Interrupt Set Pending Register
  UINT32 Reserved5[24];//0xE000E220(R),                                   
  union{UINT32 ICPR[8];Type_BIT32 ICPR_BIT[8];};    //0xE000E280,  Interrupt Clear Pending Register
  UINT32 Reserved6[24];//0xE000E2A0(R),                                   
  union{UINT32 IABR[8];Type_BIT32 IABR_BIT[8];};   //0xE000E300,  Interrupt Active bit Register
  UINT32 Reserved7[56];//0xE000E320(R),                                   
  union{UINT8 IPR[240];};//0xE000E400,  Interrupt Priority Register (8Bit wide)
  UINT32 Reserved8[516];
	//SCB_Start,Interrupt_End
  union{UINT32 CPUID;struct SYS_CPUID_BIT CPUID_BIT;};//0xE000ED00(R),CPU ID Base Register
  union{UINT32 ICSR;struct SYS_ICSR_BIT ICSR_BIT;};   //0xE000ED04(RW),Interrupt Control State Register
  union{UINT32 VTOR;struct SYS_VTOR_BIT VTOR_BIT;};   //0xE000ED08(RW),Vector Table Offset Register
  union{UINT32 AIRCR;struct SYS_AIRCR_BIT AIRCR_BIT;};//0xE000ED0C(RW),Application Interrupt / Reset Control Register
  union{UINT32 SCR;struct SYS_SCR_BIT SCR_BIT;};      //0xE000ED10(RW),System Control Register
  union{UINT32 CCR;struct SYS_CCR_BIT CCR_BIT;};      //0xE000ED14(RW),Configuration Control Register
  union{UINT8  SHPR[12];};                            //0xE000ED18(RW),System Handlers Priority Registers (4-7, 8-11, 12-15)
  union{UINT32 SHCSR;struct SYS_SHCSR_BIT SHCSR_BIT;};//0xE000ED24(RW),System Handler Control and State Register
  union{UINT32 CFSR;struct SYS_CFSR_BIT CFSR_BIT;};   //0xE000ED28(RW),Configurable Fault Status Register
  union{UINT32 HFSR;struct SYS_HFSR_BIT HFSR_BIT;};   //0xE000ED2C(RW),Hard Fault Status Register
  union{UINT32 DFSR;struct SYS_DFSR_BIT DFSR_BIT;};   //0xE000ED30(RW),Debug Fault Status Register
  union{UINT32 MMFAR;};  //0xE000ED34(R),Mem Manage Address Register
  union{UINT32 BFAR;};   //0xE000ED38(R),Bus Fault Address Register
  union{UINT32 AFSR;};   //0xE000ED3C(RW),Auxiliary Fault Status Register
  union{UINT32 PFR[2];}; //0xE000ED40(R),Processor Feature Register
  union{UINT32 DFR;};    //0xE000ED48(R),Debug Feature Register
  union{UINT32 AFR;};    //0xE000ED4C(R),Auxiliary Feature Register
  union{UINT32 MMFR[4];};//0xE000ED50(R),Memory Model Feature Register
  union{UINT32 ISAR[5];};//0xE000ED60(R),ISA Feature Register
	UINT32 Reserved9[7];   //0xE000ED74,
  //MPU_Start,only for IsDensity(XL)
  union{UINT32 TYPE;struct SYS_TYPE_BIT TYPE_BIT;};   //0xE000ED90(R), MPU Type Register
  union{UINT32 CTRL;struct SYS_CTRL_BIT CTRL_BIT;};   //0xE000ED94(RW), MPU Control Register
  union{UINT32 RNR;struct SYS_RNR_BIT RNR_BIT;};      //0xE000ED98(RW), MPU Region RNRber Register 
  union{UINT32 RBAR;struct SYS_RBAR_BIT RBAR_BIT;};   //0xE000ED9C(RW), MPU Region Base Address Register
  union{UINT32 RASR;struct SYS_RASR_BIT RASR_BIT;};   //0xE000EDA0(RW), MPU Region Attribute and Size Register
  union{UINT32 RBARA1;};//0xE000EDA4(RW), MPU Alias 1 Region Base Address Register
  union{UINT32 RASRA1;};//0xE000EDA8(RW), MPU Alias 1 Region Attribute and Size Register
  union{UINT32 RBARA2;};//0xE000EDAC(RW), MPU Alias 2 Region Base Address Register
  union{UINT32 RASRA2;};//0xE000EDB0(RW), MPU Alias 2 Region Attribute and Size Register
  union{UINT32 RBARA3;};//0xE000EDB4(RW), MPU Alias 3 Region Base Address Register
  union{UINT32 RASRA3;};//0xE000EDB8(RW), MPU Alias 3 Region Attribute and Size Register
  //MPU_END	
	UINT32 Reserved10[13];  //0xE000EDBC
	//CDB_Start
  union{UINT32 DHCSR;struct SYS_DHCSR_BIT DHCSR_BIT;}; //0xE000EDF0(RW),Debug Halting Control and Status Register
  union{UINT32 DCRSR;struct SYS_DCRSR_BIT DCRSR_BIT;}; //0xE000EDF4(W),Debug Core Register Selector Register
  union{UINT32 DCRDR;Type_BIT32 DCRDR_BIT;};           //0xE000EDF8(RW),Debug Core Register Data Register
  union{UINT32 DEMCR;struct SYS_DEMCR_BIT DEMCR_BIT;}; //0xE000EDFC(RW),Debug Exception and Monitor Control Register
	//CDB_End
	union{UINT32 SOFTTRIG;Type_BIT32 SOFTTRIG_BIT;};//0xE000EE00(RW),Soft trig interrupt
	UINT32 Reserved11[51];  //0xE000EE04(R),
  union{UINT32 PERIPHID4;};//0xE000EED0(RW),外设识别
  union{UINT32 PERIPHID5;};//0xE000EED4(RW),外设识别	
  union{UINT32 PERIPHID6;};//0xE000EED8(RW),外设识别	
  union{UINT32 PERIPHID7;};//0xE000EEDC(RW),外设识别	
  union{UINT32 PERIPHID0;};//0xE000EEE0(RW),外设识别位7:0
  union{UINT32 PERIPHID1;};//0xE000EEE4(RW),外设识别位15:8
  union{UINT32 PERIPHID2;};//0xE000EEE8(RW),外设识别位23:16	
  union{UINT32 PERIPHID3;};//0xE000EEEC(RW),外设识别位31:24
  union{UINT32 PCELLID0;}; //0xE000EEF0(RW),元件识别位7:0
  union{UINT32 PCELLID1;}; //0xE000EEF4(RW),元件识别位15:8
  union{UINT32 PCELLID2;}; //0xE000EEF8(RW),元件识别位23:16
  union{UINT32 PCELLID3;}; //0xE000EEFC(RW),元件识别位31:24
  //SCB_END	
  union{UINT32 STIR;struct SYS_STIR_BIT STIR_BIT;};//0xE000EF00(RW),  Software Trigger Interrupt Register
  UINT32 Reserved12[63];//0xE000EF04(R),
} SYS_Type,Type_SYS; 
#define PT_M3SYS                ((volatile Type_SYS *)BASE_SYS)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
#define SYS_ICTR                M3SYS.ICTR
#define SYS_ACTLR               M3SYS.ACTLR
#define SYS_STCTRL              M3SYS.STCTRL
#define SYS_STLOAD              M3SYS.STLOAD
#define SYS_STVAL               M3SYS.STVAL
#define SYS_STCALIB             M3SYS.STCALIB

#define SYS_ISER(i)             M3SYS.ISER[i]//i=0_7
#define SYS_ICER(i)             M3SYS.ICER[i]//i=0_7
#define SYS_ISPR(i)             M3SYS.ISPR[i]//i=0_7
#define SYS_ICPR(i)             M3SYS.ICPR[i]//i=0_7
#define SYS_IABR(i)             M3SYS.IABR[i]//i=0_7
#define SYS_IP(i)               M3SYS.IPR[i] //i=0_239
//SCB_Start
#define SYS_CPUID               M3SYS.CPUID
#define SYS_ICSR                M3SYS.ICSR
#define SYS_VTOR                M3SYS.VTOR
#define SYS_AIRCR               M3SYS.AIRCR
#define SYS_SCR                 M3SYS.SCR
#define SYS_CCR                 M3SYS.CCR
#define SYS_SHPR(i)             M3SYS.SHPR[i]//i=0_11
#define SYS_SHCSR               M3SYS.SHCSR
#define SYS_CFSR                M3SYS.CFSR
#define SYS_HFSR                M3SYS.HFSR
#define SYS_DFSR                M3SYS.DFSR
#define SYS_MMFAR               M3SYS.MMFAR
#define SYS_BFAR                M3SYS.BFAR
#define SYS_AFSR                M3SYS.AFSR
#define SYS_PFR(i)              M3SYS.PFR[i]//i=0_2
#define SYS_DFR                 M3SYS.DFR
#define SYS_AFR                 M3SYS.AFR
#define SYS_MMFR(i)             M3SYS.MMFR[i]//i=0_3
#define SYS_ISAR(i)             M3SYS.ISAR[i]//i=0_4
//MPU_Start
#define SYS_TYPE                M3SYS.TYPE
#define SYS_CTRL                M3SYS.CTRL
#define SYS_RNR                 M3SYS.RNR
#define SYS_RBAR                M3SYS.RBAR
#define SYS_RASR                M3SYS.RASR
#define SYS_RBARA1              M3SYS.RBARA1
#define SYS_RASRA1              M3SYS.RASRA1
#define SYS_RBARA2              M3SYS.RBARA2
#define SYS_RASRA2              M3SYS.RASRA2
#define SYS_RBARA3              M3SYS.RBARA3
#define SYS_RASRA3              M3SYS.RASRA3
//MPU_END	
//CDB_Start
#define SYS_DHCSR               M3SYS.DHCSR
#define SYS_DCRSR               M3SYS.DCRSR
#define SYS_DCRDR               M3SYS.DCRDR
#define SYS_DEMCR               M3SYS.DEMCR
//CDB_End
#define SYS_SOFTTRIG            M3SYS.SOFTTRIG
#define SYS_PERIPHID4           M3SYS.PERIPHID4
#define SYS_PERIPHID5           M3SYS.PERIPHID5
#define SYS_PERIPHID6           M3SYS.PERIPHID6
#define SYS_PERIPHID7           M3SYS.PERIPHID7
#define SYS_PERIPHID0           M3SYS.PERIPHID0
#define SYS_PERIPHID1           M3SYS.PERIPHID1
#define SYS_PERIPHID2           M3SYS.PERIPHID2
#define SYS_PERIPHID3           M3SYS.PERIPHID3
#define SYS_PCELLID0            M3SYS.PCELLID0
#define SYS_PCELLID1            M3SYS.PCELLID1
#define SYS_PCELLID2            M3SYS.PCELLID2
#define SYS_PCELLID3            M3SYS.PCELLID3
#define SYS_STIR                M3SYS.STIR
//==============================================================================================================================
struct TPI_PROTOCAL_BIT
{
  UINT32 PRO:2;           //00,：0=跟踪端口模式,1=串行写输出（曼彻斯特）,它为复位值 2=串行写输出（NRZ）,3=保留 
  UINT32 Reserved0:30;  //02,
};
//------------------------------------------------------------------------------------------------------------------------------
struct TPI_STATE_BIT
{
  UINT32 FIInProg:1;    //00,读取该位时总是为 0 
  UINT32 FtStopped:1;   //01,读取该位时总是为 0 
  UINT32 TCPresent:1;   //02,读取该位时总是为 0 
  UINT32 FtNonStop:1;   //03,格式器不能停止 
  UINT32 Reserved0:28;  //04  
};
//------------------------------------------------------------------------------------------------------------------------------
struct TPI_ITATBCTR2_BIT
{
  UINT32 ATREADY:1;     //00,该位读取或设置 ATREADYS1 和 ATREADYS2 的值 
  UINT32 Reserved0:31;  //01,
};
//------------------------------------------------------------------------------------------------------------------------------
struct TPI_ITATBCTR0_BIT
{
  UINT32 ATVALID:1;     //00,该位读取或设置 ATVALIDS1 和 ATVALIDS2 的值 
  UINT32 Reserved0:31;  //01,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
#define TPI_Struct Struct_TPI
typedef struct Struct_TPI//0xE0040000
{
	union{UINT32 CLASS;Type_UINT32_BIT4 CLASS_BIT;};          //0xE0040000(R),支持端口类型
	union{UINT32 NUM;Type_UINT32_BIT4 NUM_BIT;};              //0xE0040004(RW),当前端口类型,(NUM=1,2,4,8)
	UINT32 Reserved0[2];   //0xE0040008(R),
	union{UINT32 PRESCALER;Type_UINT32_BIT13 PRESCALER_BIT;}; //0xE0040010(RW),当前端口输出速度
	UINT32 Reserved1[55];  //0xE0040014(R),
	union{UINT32 PROTOCAL;struct TPI_PROTOCAL_BIT PROTOCAL_BIT;};    //0xE00400F0(RW),所选管脚
	UINT32 Reserved2[131]; //0xE00400F4(R),
	union{UINT32 STATE;struct TPI_STATE_BIT STATE_BIT;};  //0xE0040300(RW),所选管脚
	union{UINT32 CTRL;};   //0xE0040304(R),所选管脚
	union{UINT32 CNT;};    //0xE0040308(R),所选管脚
	UINT32 Reserved3[761];    //0xE004030C(R),
	union{UINT32 ITATBCTR2;struct TPI_ITATBCTR2_BIT ITATBCTR2_BIT;}; //0xE0040EF0(R),综合寄存器
	UINT32 Reserved4[1];      //0xE0040EF4(R),
	union{UINT32 ITATBCTR0;struct TPI_ITATBCTR0_BIT ITATBCTR0_BIT;}; //0xE0040EF8(R),综合寄存器
	UINT32 Reserved5[65];     //0xE0040EFC(R),
} TPI_Type,Type_TPI;
#define PT_M3TPI                ((volatile Type_TPI *)BASE_TPI)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
#define TPI_CLASS               M3TPI.CLASS
#define TPI_NUM                 M3TPI.NUM
#define TPI_SP                  M3TPI.SP
#define TPI_PIN                 M3TPI.PIN
#define TPI_STATE               M3TPI.STATE
#define TPI_CTRL                M3TPI.CTRL
#define TPI_CNT                 M3TPI.CNT
#define TPI_ITATBCTR2           M3TPI.ITATBCTR2
#define TPI_ITATBCTR0           M3TPI.ITATBCTR0
#define TPI_CNT                 M3TPI.CNT
#define TPI_CNT                 M3TPI.CNT
//==============================================================================================================================
#define RSTV_ETM_CTRL           0x00002411
struct ETM_CTRL_BIT
{
  UINT32 P1:1;          //00,
  UINT32 Reserved0:3;   //01,
  UINT32 P2:8;          //04,
  UINT32 Reserved1:1;   //12,
  UINT32 P3:1;          //13,
  UINT32 Reserved2:2;   //14,
  UINT32 P4:2;          //16,
  UINT32 Reserved3:3;   //18,
  UINT32 P5:1;          //21,
  UINT32 Reserved4:10;  //22,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_ETM_CODE           0x8C800000 
struct ETM_CODE_BIT
{
  UINT32 Reserved0:17;  //00,
  UINT32 MAXEXTIN:2;    //17,
  UINT32 Reserved1:1;   //19,
  UINT32 P1:3;          //20,固定为 0
  UINT32 Reserved2:9;   //23,
};
//------------------------------------------------------------------------------------------------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
#define ETM_Struct Struct_ETM
typedef struct Struct_ETM//0xE0041000
{
	union{UINT32 CTRL;struct ETM_CTRL_BIT CTRL_BIT;};  //0xE0041000,控制
	union{UINT32 CODE;struct ETM_CODE_BIT CODE_BIT;};  //0xE0041004,可配置代码
	union{UINT32 EVENT;}; //0xE0041008,触发事件
	union{UINT32 ASIC;};  //0xE004100C,当前端口输出速度
	union{UINT32 STAT;};  //0xE0041010,状态
	union{UINT32 SYS;};   //0xE0041014,系统配置
	union{UINT32 TEN[2];};//0xE0041018,跟踪使能
	union{UINT32 TEVENT;};//0xE0041020,跟踪事件
	union{UINT32 TCTRL;}; //0xE0041024,跟踪控制
	union{UINT32 FIFOAREA;}; //0xE0041028,FIFOFULL区域
	union{UINT32 FIFOGRADE;};//0xE004102C,FIFOFULL级别
	union{UINT32 DATA[4];};  //0xE0041030,数据
	union{UINT32 ADDR[64];}; //0xE0041040,地址比较器
	union{UINT32 CNT[16];};  //0xE0041140,计数器
	union{UINT32 SEQ[8];};   //0xE0041180,定序器
	union{UINT32 EXTOUT[4];};//0xE00411A0,外部输出
	union{UINT32 CID[4];};//0xE00411B0,CID比较器
	union{UINT32 SPD[8];};//0xE00411C0,特定实现
	union{UINT32 FRQ;};   //0xE00411E0,同步频率
	union{UINT32 ID;};    //0xE00411E4,ETM ID
	union{UINT32 EXCODE;};//0xE00411E8,配置代码扩展
	union{UINT32 EXIN;};  //0xE00411EC,外部输入
	union{UINT32 ICEBE;}; //0xE00411F0,ICE启停
	union{UINT32 ICEACT;};//0xE00411F4,ICE行为控制
	UINT32 Reserved0[2];  //0xE00411F8,
	union{UINT32 CSID;};       //0xE0041200,Core Sight跟踪ID
	UINT32 Reserved1[64];      //0xE0041204,
	union{UINT32 OSRW[2];};    //0xE0041304,OS保存与恢复(0xE0041304-0xE0041308)
	UINT32 Reserved2[757];     //0xE004130C,
	union{UINT32 ITMISCIN;};   //0xE0041EE0,
	UINT32 Reserved3[3];       //0xE0041EE4,
	union{UINT32 ITATBCTR2;};  //0xE0041EF0,
	UINT32 Reserved4[1];       //0xE0041EF4,
	union{UINT32 ITATBCTR0;};  //0xE0041EF8,
	UINT32 Reserved5[1];       //0xE0041EFC,
	union{UINT32 MODECTRL;};   //0xE0041F00,综合模式控制
	UINT32 Reserved6[39];      //0xE0041F04,
	union{UINT32 TAG[2];};     //0xE0041FA0,申明标签(0xE0041FA0-0xE0041FA4)
	UINT32 Reserved7[2];       //0xE0041FA8,
	union{UINT32 LOCK[2];};    //0xE0041FB0,锁定访问(0xE0041FB0-0xE0041FB4)
	union{UINT32 DEVICESTATE;};//0xE0041FB8,鉴别状态
	UINT32 Reserved8[4];       //0xE0041FBC,
	union{UINT32 DEVICETYPE;}; //0xE0041FCC,设备类型
  union{UINT32 PID4;};       //0xE0041FD0,外设ID
  union{UINT32 PID5;};       //0xE0041FD4,外设ID
  union{UINT32 PID6;};       //0xE0041FD8,外设ID
  union{UINT32 PID7;};       //0xE0041FDC,外设ID
  union{UINT32 PID0;};       //0xE0041FE0,外设ID
  union{UINT32 PID1;};       //0xE0041FE4,外设ID
  union{UINT32 PID2;};       //0xE0041FE8,外设ID
  union{UINT32 PID3;};       //0xE0041FEC,外设ID
  union{UINT32 GID0;};       //0xE0041FF0,组件ID
  union{UINT32 GID1;};       //0xE0041FF4,组件ID
  union{UINT32 GID2;};       //0xE0041FF8,组件ID
  union{UINT32 GID3;};       //0xE0041FFC,组件ID
} ETM_Type,Type_ETM;
#define PT_M3ETM                ((volatile Type_ETM *)BASE_ETM)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
#define ETM_CTRL                M3ETM.CTRL
#define ETM_CODE                M3ETM.CODE
#define ETM_EVENT               M3ETM.EVENT
#define ETM_ASIC                M3ETM.ASIC
#define ETM_STAT                M3ETM.STAT
#define ETM_SYS                 M3ETM.SYS
#define ETM_TEN(i)              M3ETM.TEN[i]//i=0_1
#define ETM_TEVENT              M3ETM.TEVENT
#define ETM_TCTRL               M3ETM.TCTRL
#define ETM_FIFOAREA            M3ETM.FIFOAREA
#define ETM_FIFOGRADE           M3ETM.FIFOGRADE
#define ETM_DATA(i)             M3ETM.DATA[i]//i=0_3
#define ETM_ADDR(i)             M3ETM.ADDR[i]//i=0_63
#define ETM_CNT(i)              M3ETM.CNT[i]//i=0_15
#define ETM_SEQ(i)              M3ETM.SEQ[i]//i=0_7
#define ETM_EXTOUT(i)           M3ETM.EXTOUT[i]//i=0_3
#define ETM_CID(i)              M3ETM.CID[i]//i=0_3
#define ETM_SPD(i)              M3ETM.SPD[i]//i=0_7
#define ETM_FRQ                 M3ETM.FRQ
#define ETM_ID                  M3ETM.ID
#define ETM_EXCODE              M3ETM.EXCODE
#define ETM_EXIN                M3ETM.EXIN
#define ETM_ICEBE               M3ETM.ICEBE
#define ETM_ICEACT              M3ETM.ICEACT
#define ETM_CSID                M3ETM.CSID
#define ETM_OSRW(i)             M3ETM.OSRW[i]//i=0_1
#define ETM_ITMISCIN            M3ETM.ITMISCIN
#define ETM_ITATBCTR2           M3ETM.ITATBCTR2
#define ETM_ITATBCTR0           M3ETM.ITATBCTR0
#define ETM_MODECTRL            M3ETM.MODECTRL
#define ETM_TAG(i)              M3ETM.TAG[i]
#define ETM_LOCK(i)             M3ETM.LOCK[i]
#define ETM_DEVICESTATE         M3ETM.DEVICESTATE
#define ETM_DEVICETYPE          M3ETM.DEVICETYPE
#define ETM_PID4                M3ETM.PID4
#define ETM_PID5                M3ETM.PID5
#define ETM_PID6                M3ETM.PID6
#define ETM_PID7                M3ETM.PID7
#define ETM_PID0                M3ETM.PID0
#define ETM_PID1                M3ETM.PID1
#define ETM_PID2                M3ETM.PID2
#define ETM_PID3                M3ETM.PID3
#define ETM_GID0                M3ETM.GID0
#define ETM_GID1                M3ETM.GID1
#define ETM_GID2                M3ETM.GID2
#define ETM_GID3                M3ETM.GID3
//==============================================================================================================================
#define RSTV_DBG_ID             0x00000000//0x000
struct DBG_ID_BIT
{
	UINT32 DEVID:12;      //00,Device Identifier
	UINT32 Reserved0:4;   //12,
	UINT32 REVID:16;      //16,
};
//------------------------------------------------------------------------------------------------------------------------------
#define RSTV_DBG_CR             0x00000000//0x004
struct DBG_CR_BIT
{
	UINT32 DBG_SLEEP:1;   //00,Debug Sleep Mode
	UINT32 DBG_STOP:1;    //01,Debug Stop Mode
	UINT32 DBG_STANDBY:1; //02,Debug Standby mode
	UINT32 Reserved0:2;   //03,
	UINT32 TRACE_IOEN:1;  //05,Trace Pin Assignment Control
	UINT32 MODE:2;        //06,TRACE_MODE[1:0] bits (Trace Pin Assignment Control)
	UINT32 IWDG_STOP:1;   //08,Debug Independent Watchdog stopped when Core is halted
	UINT32 WWDG_STOP:1;   //09,Debug Window Watchdog stopped when Core is halted
	UINT32 TIM1_STOP:1;   //10,TIM1 counter stopped when core is halted
	UINT32 TIM2_STOP:1;   //11,TIM1 counter stopped when core is halted
	UINT32 TIM3_STOP:1;   //12,TIM1 counter stopped when core is halted
	UINT32 TIM4_STOP:1;   //13,TIM1 counter stopped when core is halted
	UINT32 CAN1_STOP:1;   //14,Debug CAN1 stopped when Core is halted
	UINT32 I2C1_SMBUS_TIMEOUT:1; //15,SMBUS timeout mode stopped when Core is halted
	UINT32 I2C2_SMBUS_TIMEOUT:1; //16,SMBUS timeout mode stopped when Core is halted
	UINT32 TIM8_STOP:1;   //17,TIM8 counter stopped when core is halted
	UINT32 TIM5_STOP:1;   //18,TIM5 counter stopped when core is halted
	UINT32 TIM6_STOP:1;   //19,TIM6 counter stopped when core is halted
	UINT32 TIM7_STOP:1;   //20,TIM7 counter stopped when core is halted
	UINT32 CAN2_STOP:1;   //21,Debug CAN2 stopped when Core is halted
	UINT32 TIM15_STOP:1;  //22,Debug TIM15 stopped when Core is halted,<LDY>
	UINT32 TIM16_STOP:1;  //23,Debug TIM16 stopped when Core is halted,<LDY>
	UINT32 TIM17_STOP:1;  //24,Debug TIM17 stopped when Core is halted,<LDY>
	UINT32 TIM12_STOP:1;  //25,Debug TIM12 stopped when Core is halted,<LDY>
	UINT32 TIM13_STOP:1;  //26,Debug TIM13 stopped when Core is halted,<LDY>
	UINT32 TIM14_STOP:1;  //27,Debug TIM14 stopped when Core is halted,<LDY>
	UINT32 TIM9_STOP:1;   //28,Debug TIM9 stopped when Core is halted,<LDY>
	UINT32 TIM10_STOP:1;  //29,Debug TIM10 stopped when Core is halted,<LDY>
	UINT32 TIM11_STOP:1;  //30,Debug TIM11 stopped when Core is halted,<LDY>
  UINT32 Reserved1:1;   //31,
};
//------------------------------------------------------------------------------------------------------------------------------
#define DBG_Struct Struct_DBG
typedef struct Struct_DBG//0xE0042000
{
  union{UINT32 ID;struct DBG_ID_BIT ID_BIT;}; //0x000(RW),
  union{UINT32 CR;struct DBG_CR_BIT CR_BIT;}; //0x004(RW),
} DBG_Type,Type_DBG;
#define PT_DBG    ((volatile Type_DBG *)BASE_DBG)
#define DBG_ID                  DBG.ID
#define DBG_CR                  DBG.CR
//==============================================================================================================================
//------------------------------------------------------------------------------------------------------------------------------
#define TAB_Struct Struct_TAB
typedef struct Struct_TAB
{
  union{UINT32 NVIC;};//0x000(R),
  union{UINT32 DWT;}; //0x004(R),
  union{UINT32 FPB;}; //0x008(R),
  union{UINT32 ITM;}; //0x00C(R),
  union{UINT32 TPI;}; //0x010(R),
  union{UINT32 ETM;}; //0x014(R),
  union{UINT32 END;}; //0x018(R),
  UINT32 Reserved0[1004]; //0x01C(R),
  union{UINT32 MEMType;}; //0xFCC(R),
  union{UINT32 PID4;};//0xFD0,Peripheral ID space; reserved 
  union{UINT32 PID5;};//0xFD4,Peripheral ID space; reserved 
  union{UINT32 PID6;};//0xFD8,Peripheral ID space; reserved 
  union{UINT32 PID7;};//0xFDC,Peripheral ID space; reserved 
  union{UINT32 PID0;};//0xFE0,Peripheral ID space; reserved 
  union{UINT32 PID1;};//0xFE4,Peripheral ID space; reserved 
  union{UINT32 PID2;};//0xFE8,Peripheral ID space; reserved 
  union{UINT32 PID3;};//0xFEC,Peripheral ID space; reserved 
  union{UINT32 CID0;};//0xFF0,Component ID space; reserved 
  union{UINT32 CID1;};//0xFF4,Component ID space; reserved 
  union{UINT32 CID2;};//0xFF8,Component ID space; reserved 
  union{UINT32 CID3;};//0xFFC,Component ID space; reserved  
} TAB_Type,Type_TAB;
#define PT_M3TAB                ((volatile Type_TAB *)BASE_TAB)
//------------------------------------------------------------------------------------------------------------------------------
#define TAB_NVIC                M3TAB.NVIC
#define TAB_DWT                 M3TAB.DWT
#define TAB_FPB                 M3TAB.FPB
#define TAB_ITM                 M3TAB.ITM
#define TAB_TPI                 M3TAB.TPI
#define TAB_ETM                 M3TAB.ETM
#define TAB_END                 M3TAB.END
#define TAB_MEMType             M3TAB.MEMType
#define TAB_PID4                M3TAB.PID4
#define TAB_PID5                M3TAB.PID5
#define TAB_PID6                M3TAB.PID6
#define TAB_PID7                M3TAB.PID7
#define TAB_PID0                M3TAB.PID0
#define TAB_PID1                M3TAB.PID1
#define TAB_PID2                M3TAB.PID2
#define TAB_PID3                M3TAB.PID3
#define TAB_CID0                M3TAB.CID0
#define TAB_CID1                M3TAB.CID1
#define TAB_CID2                M3TAB.CID2
#define TAB_CID3                M3TAB.CID3
//==============================================================================================================================
#define AHBAP_Struct Struct_AHBAP
typedef struct Struct_AHBAP
{
	UINT32                        CSW;
	UINT32                        TRANSADDR;
	UINT32                        Reserved0;
	UINT32                        DATA;
	UINT32                        BD[4];
	UINT32                        Reserved1[54];
	UINT32                        ROMADDR;  //RSTV=0xE000E000
	UINT32                        IDR;      //RSTV=0x04770011
} AHBAP_Type,Type_AHBAP;
//==============================================================================================================================
#define JTAG_Struct Struct_JTAG
typedef struct Struct_JTAG
{
	UINT32                        ABORT;
	UINT32                        IDCODE;
	UINT32                        CTRL_STAT;
	UINT32                        SELECT;
	UINT32                        RDBUFF;
	UINT32                        WCR;
	UINT32                        RESEND;
} JTAG_Type,Type_JTAG;
//==============================================================================================================================
#define GPIO_Pin_0                 ((uint16_t)0x0001)  //Pin 0 selected
#define GPIO_Pin_1                 ((uint16_t)0x0002)  //Pin 1 selected
#define GPIO_Pin_2                 ((uint16_t)0x0004)  //Pin 2 selected
#define GPIO_Pin_3                 ((uint16_t)0x0008)  //Pin 3 selected
#define GPIO_Pin_4                 ((uint16_t)0x0010)  //Pin 4 selected
#define GPIO_Pin_5                 ((uint16_t)0x0020)  //Pin 5 selected
#define GPIO_Pin_6                 ((uint16_t)0x0040)  //Pin 6 selected
#define GPIO_Pin_7                 ((uint16_t)0x0080)  //Pin 7 selected
#define GPIO_Pin_8                 ((uint16_t)0x0100)  //Pin 8 selected
#define GPIO_Pin_9                 ((uint16_t)0x0200)  //Pin 9 selected
#define GPIO_Pin_10                ((uint16_t)0x0400)  //Pin 10 selected
#define GPIO_Pin_11                ((uint16_t)0x0800)  //Pin 11 selected
#define GPIO_Pin_12                ((uint16_t)0x1000)  //Pin 12 selected
#define GPIO_Pin_13                ((uint16_t)0x2000)  //Pin 13 selected
#define GPIO_Pin_14                ((uint16_t)0x4000)  //Pin 14 selected
#define GPIO_Pin_15                ((uint16_t)0x8000)  //Pin 15 selected
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  //All pins selected

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz=2, 
  GPIO_Speed_50MHz=3,
}GPIOSpeed_TypeDef;
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz) || ((SPEED) == GPIO_Speed_50MHz))

typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || ((MODE) == GPIO_Mode_IPD) || ((MODE) == GPIO_Mode_IPU) || \
                            ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP) || ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))
typedef struct
{
  uint16_t GPIO_Pin;             //Specifies the GPIO pins to be configured. This parameter can be any value of @ref GPIO_pins_define
  GPIOSpeed_TypeDef GPIO_Speed;  //Specifies the speed for the selected pins. This parameter can be a value of @ref GPIOSpeed_TypeDef
  GPIOMode_TypeDef GPIO_Mode;    //Specifies the operating mode for the selected pins. This parameter can be a value of @ref GPIOMode_TypeDef
}GPIO_InitTypeDef;

typedef struct
{
  uint8_t NVIC_IRQChannel;
  uint8_t NVIC_IRQChannelPreemptionPriority;
  uint8_t NVIC_IRQChannelSubPriority;
  bool NVIC_IRQChannelCmd;//ENABLE or DISABLE
} NVIC_InitTypeDef;
//==============================================================================================================================
//register memory
extern volatile Type_ADC        ADC1    __attribute__((at(BASE_ADC1)));
extern volatile Type_ADC        ADC2    __attribute__((at(BASE_ADC2)));
extern volatile Type_ADC        ADC3    __attribute__((at(BASE_ADC3)));
extern volatile Type_ADC        *ADC[];//Array
extern volatile Type_BKP        BKP     __attribute__((at(BASE_BKP)));
extern volatile Type_CAN        CAN[2]  __attribute__((at(BASE_CAN1)));//array
extern volatile Type_CEC        CEC     __attribute__((at(BASE_CEC)));
extern volatile Type_CRC        CRC     __attribute__((at(BASE_CRC)));
extern volatile Type_DAC        DAC     __attribute__((at(BASE_DAC)));
extern volatile Type_DMA        DMA[2]  __attribute__((at(BASE_DMA1)));//array
extern volatile Type_ETH        ETH     __attribute__((at(BASE_ETH)));
extern volatile Type_EXTI       EXTI    __attribute__((at(BASE_EXTI)));
extern volatile Type_FLASH      FLASH   __attribute__((at(BASE_FLASHR)));
extern volatile Type_OB         OB      __attribute__((at(BASE_OB)));
extern volatile Type_FSMC       FSMC    __attribute__((at(BASE_FSMC)));
extern volatile Type_LCD        LCD     __attribute__((at(BASE_LCD)));//FSMC LCD
extern volatile Type_GPIO       GPIO[7] __attribute__((at(BASE_GPIOA)));//array
extern volatile Type_AFIO       AFIO    __attribute__((at(BASE_AFIO)));
extern volatile Type_I2C        I2C[2]  __attribute__((at(BASE_I2C1)));//array
extern volatile Type_WWDG       WWDG    __attribute__((at(BASE_WWDG)));
extern volatile Type_IWDG       IWDG    __attribute__((at(BASE_IWDG)));
extern volatile Type_PWR        PWR     __attribute__((at(BASE_PWR)));
extern volatile Type_RCC        RCC     __attribute__((at(BASE_RCC)));
extern volatile Type_RTC        RTC     __attribute__((at(BASE_RTC)));
extern volatile Type_SDIO       SDIO    __attribute__((at(BASE_SDIO)));
extern volatile Type_SPI        SPI1    __attribute__((at(BASE_SPI1)));
extern volatile Type_SPI        SPI2    __attribute__((at(BASE_SPI2)));
extern volatile Type_SPI        SPI3    __attribute__((at(BASE_SPI3)));
extern volatile Type_SPI        *SPI[];//array
extern volatile Type_TIM        TIM1    __attribute__((at(BASE_TIM1)));
extern volatile Type_TIM        TIM2    __attribute__((at(BASE_TIM2)));
extern volatile Type_TIM        TIM3    __attribute__((at(BASE_TIM3)));
extern volatile Type_TIM        TIM4    __attribute__((at(BASE_TIM4)));
extern volatile Type_TIM        TIM5    __attribute__((at(BASE_TIM5)));
extern volatile Type_TIM        TIM6    __attribute__((at(BASE_TIM6)));
extern volatile Type_TIM        TIM7    __attribute__((at(BASE_TIM7)));
extern volatile Type_TIM        TIM8    __attribute__((at(BASE_TIM8)));
extern volatile Type_TIM        TIM9    __attribute__((at(BASE_TIM9)));
extern volatile Type_TIM        TIM10   __attribute__((at(BASE_TIM10)));
extern volatile Type_TIM        TIM11   __attribute__((at(BASE_TIM11)));
extern volatile Type_TIM        TIM12   __attribute__((at(BASE_TIM12)));
extern volatile Type_TIM        TIM13   __attribute__((at(BASE_TIM13)));
extern volatile Type_TIM        TIM14   __attribute__((at(BASE_TIM14)));
extern volatile Type_TIM        TIM15   __attribute__((at(BASE_TIM15)));
extern volatile Type_TIM        TIM16   __attribute__((at(BASE_TIM16)));
extern volatile Type_TIM        TIM17   __attribute__((at(BASE_TIM17)));
extern volatile Type_TIM        *TIM[];//array(17)
extern volatile Type_UART       UART1   __attribute__((at(BASE_UART1)));
extern volatile Type_UART       UART2   __attribute__((at(BASE_UART2)));
extern volatile Type_UART       UART3   __attribute__((at(BASE_UART3)));
extern volatile Type_UART       UART4   __attribute__((at(BASE_UART4)));
extern volatile Type_UART       UART5   __attribute__((at(BASE_UART5)));
extern volatile Type_UART       *UART[];//array(5)
extern volatile Type_USB        USB     __attribute__((at(BASE_USB)));
extern volatile Type_USBFS      USBFS   __attribute__((at(BASE_USBFS)));
extern volatile Type_DES        DES     __attribute__((at(BASE_DES)));
//------------------------------------------------------------------------------------------------------------------------------
extern volatile Type_ITM        M3ITM   __attribute__((at(BASE_ITM)));
extern volatile Type_DWT        M3DWT   __attribute__((at(BASE_DWT)));
extern volatile Type_FPB        M3FPB   __attribute__((at(BASE_FPB)));
extern volatile Type_SYS        M3SYS   __attribute__((at(BASE_SYS)));
extern volatile Type_TPI        M3TPI   __attribute__((at(BASE_TPI)));//TPIU
extern volatile Type_ETM        M3ETM   __attribute__((at(BASE_ETM)));
extern volatile Type_DBG        M3DBG   __attribute__((at(BASE_DBG)));//DBGMCU
extern volatile Type_TAB        M3TAB   __attribute__((at(BASE_TAB)));
//------------------------------------------------------------------------------------------------------------------------------
#define SIZE_REGS       (sizeof(Type_ADC)*3+sizeof(Type_BKP)+sizeof(Type_CAN)*2+sizeof(Type_CEC)+sizeof(Type_CRC)+\
                        sizeof(Type_DAC)+sizeof(Type_DMA)*2+sizeof(Type_ETH)+sizeof(Type_EXTI)+sizeof(Type_FLASH)+\
                        sizeof(Type_OB)+sizeof(Type_FSMC)+sizeof(Type_LCD)+sizeof(Type_GPIO)*7+sizeof(Type_AFIO)+\
                        sizeof(Type_I2C)*2+sizeof(Type_WWDG)+sizeof(Type_IWDG)+sizeof(Type_PWR)+sizeof(Type_RCC)+\
                        sizeof(Type_RTC)+sizeof(Type_SDIO)+sizeof(Type_SPI)*3+sizeof(Type_TIM)*17+sizeof(Type_UART)*5+\
                        sizeof(Type_USB)+sizeof(Type_USBFS)+sizeof(Type_DES)+sizeof(Type_ITM)+sizeof(Type_DWT)+\
                        sizeof(Type_FPB)+sizeof(Type_SYS)+sizeof(Type_TPI)+sizeof(Type_ETM)+sizeof(Type_DBG)+sizeof(Type_TAB))
//==============================================================================================================================
//[PortIndex]
#define PortIndex_USB1          0
#define PortIndex_USB2          1
#define PortIndex_CAN1          2
#define PortIndex_CAN2          3
#define PortIndex_Uart1         4
#define PortIndex_Uart2         5
#define PortIndex_Uart3         6
#define PortIndex_Uart4         7
#define PortIndex_Uart5         8
#define PortIndex_SPI1          9
#define PortIndex_SPI2          10
#define PortIndex_SPI3          11
#define PortIndex_Count         12
//==============================================================================================================================
//[AppPara]
#define AppPara_Area_ROM        0
#define AppPara_Area_IIC        1
#define AppPara_Area_Count      2
//==============================================================================================================================
//[INTF],interface
typedef struct Data_INTF
{
  void (*IMM_Event)(void);
  void (*INT_Event)(void);
  void (*TMR_Event)(void);
  void (*Init)(UINT8 IsAfter);
  void (*IRQ_RTC)(UINT8 Index);
  void (*IRQ_TIM)(UINT8 Index);//TIM2=100us
  void (*TMR)(UINT8 Index);//0=1ms,1=5ms,2=10ms,3=100ms,4=1000ms
  void (*ADC_Control)(UINT8 Index);
  void (*DMA_Control)(UINT8 Index,UINT8 CHIndex);
  void (*EXTI_Control)(UINT8 Index);
  void (*COM_ReadPacket)(UINT16 Index,UINT8* s,UINT16 Count);
  void (*COM_ReadParameter)(UINT16 Index,UINT8* s,UINT16 Count);
} Type_INTF;
//==============================================================================================================================
//[APPV]
typedef struct Data_APPV
{
  UINT8                   Var[4],IRQVar[4];//公用8位变量（分中断内外)
  UINT16                  INT[4],IRQINT[4];//公用16位变量（分中断内外)
  UINT32                  LNG[4],IRQLNG[4];//公用32位变量（分中断内外)
  union UINT32_REG        U32V[2],IRQU32V[2];//公用32位结构变量（分中断内外)
  union UINT64_REG        U64V[2],IRQU64V[2];//公用64位结构变量（分中断内外)

  union UINT8_REG         SystemST;//系统3大事件状态，如果建立成数组或制作成芯片，可以做成最快的操作系统
  union UINT32_REG        ST[4];//设备通用状态
  
  UINT8  TMRCount[4],MicroTimeCount,LGIndex,LGCount;
  UINT32 SysTimeCount,SleepTimeCount,Para_Save_TimeCount;
  UINT32 PSP,MSP;//堆栈备份，用于升级
  UINT64 Dentify;
} Type_APPV;
//==============================================================================================================================
//[GPIO]
#define SDK_GPIO_MAXCOUNT       7
#define PN_EMPTY                0xFFFFFFFF//PIN
//==============================================================================================================================
//[EXTI]
#define SDK_EXT_MAXCOUNT        16
typedef struct Setup_EXT
{
	UINT16 PN:10;//PN=PortNumber=Port*32+Pin: for Port  0=GIOA,1=GPIOB,...;for Pin 0_15=PIN0_15
	UINT16 Falling:1;
	UINT16 Rising:1;
	UINT16 Reserved0:3;
  UINT16 EN:1;
} Setup_EXT_Type,Type_Setup_EXT;
typedef struct Data_EXTItem
{
	Type_Setup_EXT Setup;
} Type_EXTItem;
//==============================================================================================================================
//[ADC]
#define SDK_ADC_MAXCOUNT        3
typedef struct Data_ADCItem
{
  UINT8  HWIndex,Count,Index;
  UINT32 *V;
} Type_ADCItem;
//==============================================================================================================================
//[DAC]
#define SDK_DAC_MAXCOUNT        1
typedef struct Data_DACItem
{
  UINT8  HWIndex,Count,Index;
  UINT32 *V;
} Type_DACItem;
//==============================================================================================================================
//[SPI]
#define SDK_SPI_MAXCOUNT        3
typedef struct Setup_SPI
{
	UINT8 BR:3;//BR: SPI1=72M,SP2/SP3=36M div by :0=/2=18M,1=/4=9MHz,2=/8=4.5MHz
	UINT8 CPHA:1;//phase:相位:0=first,1=second
	UINT8 CPOL:1;//Level:稳态电压,0=Low,1=High
	UINT8 BIDMode:1;//BIDMode=1 for 3 wire
	UINT8 ALF:1;//ALF for SPI1,SPI3
	UINT8 EN:1;
} Type_Setup_SPI;
typedef struct Data_SPIItem
{
  UINT8 HWIndex,BaudIndex;
	Type_Setup_SPI Setup;
} Type_SPIItem;
//==============================================================================================================================
//[I2S]
#define SDK_I2S_MAXCOUNT        3
typedef struct Setup_I2S
{
  UINT8 EN:1;
} Type_Setup_I2S;
typedef struct Data_I2SItem
{
	UINT8 HWIndex,BaudIndex;
  Type_Setup_I2S Setup;
} Type_I2SItem;
//==============================================================================================================================
//[I2C]
#define SDK_I2C_MAXCOUNT        2
typedef struct Setup_I2C
{
  UINT8 EN:1;
} type_Setup_I2C;
typedef struct Data_I2CItem
{
  UINT8 HWIndex,BaudIndex;
  type_Setup_I2C Setup;
} Type_I2CItem;
//==============================================================================================================================
//[UART],BAUD={1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,500000,1000000,2000000}
#define SDK_UART_MAXCOUNT       5
typedef struct Data_UARTItem
{
  UINT8 HWIndex,BaudIndex,BitCount;//硬件索引，波特率索引,位数
} Type_UARTItem;
//==============================================================================================================================
//[CAN]
#define SDK_CAN_MAXCOUNT        2
typedef struct Data_CANItem
{
  union  UINT8_REG State;
  union  UINT32_REG SAD,TAD;//CAN 源地址，目标地址  
  UINT8 HWIndex,BaudIndex;//硬件索引，波特率索引
} Type_CANItem;
//==============================================================================================================================
//[ETH]
#define SDK_ETH_MAXCOUNT        1
typedef struct Data_ETHItem
{
  UINT8 HWIndex,BaudIndex;//硬件索引，波特率索引
} Type_ETHItem;
//==============================================================================================================================
//[USB]
#define SDK_USB_MAXCOUNT        1
typedef enum ENUM_USBRESULT
{
  USB_SUCCESS = 0, 
  USB_ERROR=1,
  USB_UNSUPPORT=2,
  USB_NOT_READY=3//The process has not been finished, endpoint will be NAK to further request
} USB_RESULT;

typedef enum ENUM_USBRESUMESTATE
{
  USB_RESUME_EXTERNAL=0,
  USB_RESUME_INTERNAL=1,
  USB_RESUME_LATER=2,
  USB_RESUME_WAIT=3,
  USB_RESUME_START=4,
  USB_RESUME_ON=5,
  USB_RESUME_OFF=6,
  USB_RESUME_SOF=7,
  USB_RESUME_ESOF=8
} USB_RESUME_STATE;

typedef enum ENUM_USBDEVICESTATE
{
  USB_STATE_UNCONNECTED=0,
  USB_STATE_ATTACHED=1,
  USB_STATE_POWERED=2,
  USB_STATE_SUSPENDED=3,
  USB_STATE_ADDRESSED=4,
  USB_STATE_CONFIGURED=5
} USB_DEVICE_STATE;

typedef enum ENUM_USBControlStatus
{
  WAIT_SETUP=0,
  SETTING_UP=1,
  IN_DATA=2,
  OUT_DATA=3,
  LAST_IN_DATA=4,
  LAST_OUT_DATA=5,
  WAIT_STATUS_IN=7, 
  WAIT_STATUS_OUT=8,
  STALLED=9,
  PAUSE=10
} USB_CONTROL_STATE;//The state machine states of a control pipe

typedef struct OneDescriptor
{
  UINT8 *Descriptor;
  UINT16 Descriptor_Size;
}ONE_DESCRIPTOR, *PONE_DESCRIPTOR;

typedef struct _ENDPOINT_INFO
{
  uint16_t  Usb_wLength;
  uint16_t  Usb_wOffset;
  uint16_t  PacketSize;
  UINT8   *(*CopyData)(uint16_t Length);
}ENDPOINT_INFO;

typedef struct _DEVICE_INFO
{
  UINT8 USBbmRequestType; //bmRequestType
  UINT8 USBbRequest;            //bRequest
  union UINT16_REG USBwValues;         //wValue
  union UINT16_REG USBwIndexs;         //wIndex
  union UINT16_REG USBwLengths;        //wLength

  UINT8 ControlState;           //USB_CONTROL_STATE
  UINT8 Current_Feature;
  UINT8 Current_Configuration;   //Selected configuration  //CONFIGURATION是怎么取值的，代表什么意义？
  UINT8 Current_Interface;       //Selected interface of current configuration 
  UINT8 Current_AlternateSetting;//Selected Alternate Setting of current interface
  ENDPOINT_INFO Ctrl_Info;
}DEVICE_INFO;

typedef struct Data_ResumeState
{
  USB_RESUME_STATE eState;
  UINT8 bESOFcnt;
} USB_ResumeState;

//RequestType
#define USB_REQUEST_TYPE      0x60
#define USB_STANDARD_REQUEST  0x00
#define USB_CLASS_REQUEST     0x20
#define USB_VENDOR_REQUEST    0x40
#define USB_RECIPIENT         0x1F

#define USB_DEVICE_CLASS_RESERVED           0x00
#define USB_DEVICE_CLASS_AUDIO              0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS     0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE    0x03
#define USB_DEVICE_CLASS_MONITOR            0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE 0x05
#define USB_DEVICE_CLASS_POWER              0x06
#define USB_DEVICE_CLASS_PRINTER            0x07
#define USB_DEVICE_CLASS_STORAGE            0x08
#define USB_DEVICE_CLASS_HUB                0x09
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC    0xFF
//STANDARD_REQUESTS
#define USB_GET_STATUS 0
#define USB_CLEAR_FEATURE 1
#define USB_RESERVED1 2
#define USB_SET_FEATURE 3
#define USB_RESERVED2 4
#define USB_SET_ADDRESS 5
#define USB_GET_DESCRIPTOR 6
#define USB_SET_DESCRIPTOR 7
#define USB_GET_CONFIGURATION 8
#define USB_SET_CONFIGURATION 9
#define USB_GET_INTERFACE 10
#define USB_SET_INTERFACE 11
#define USB_SYNCH_FRAME 12//Total number of Standard request

//Feature selector of a SET_FEATURE or CLEAR_FEATURE
#define USB_ENDPOINT_STALL  0
#define USB_DEVICE_REMOTE_WAKEUP 1

#define USB_DEVICE_DESCRIPTOR 1
#define USB_CONFIG_DESCRIPTOR 2
#define USB_STRING_DESCRIPTOR 3
#define USB_INTERFACE_DESCRIPTOR 4
#define USB_ENDPOINT_DESCRIPTOR	5

#define USB_STALLED 0x00
#define USB_WAIT_STATUS_IN 0x01
#define USB_WAIT_STATUS_OUT 0x02
#define USB_WAIT_Data_IN 0x04
#define USB_WAIT_Data_OUT 0x08
#define USB_WAIT_SET_ADDRESS 0x10
#define USB_RESET 0x20

#define USB_STANDARD_REQUEST    0x00//Standard request
#define USB_CLASS_REQUEST       0x20//Class request
#define USB_VENDOR_REQUEST      0x40//Vendor request

#define USB_DEVICE_RECIPIENT    0x00//Recipient device
#define USB_INTERFACE_RECIPIENT 0x01//Recipient interface
#define USB_ENDPOINT_RECIPIENT  0x02//Recipient endpoint
#define USB_OTHER_RECIPIENT     0x03

#define USB_REPORT_DESCRIPTOR	  0x22
#define USB_HID_DESCRIPTOR_TYPE	0x21
//HID_REQUESTS
#define USB_GET_REPORT	1
#define USB_GET_IDLE	2
#define USB_GET_PROTOCOL	3
#define USB_SET_REPORT	9
#define USB_SET_IDLE	10
#define USB_SET_PROTOCOL	11

#define USB_MDL_USB1            0x00
#define USB_MDL_USB2            0x01
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Data_USBItem
{
  UINT8 HWIndex,BaudIndex;//硬件索引，波特率索引
} Type_USBItem;
//==============================================================================================================================
//[FLASH]
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG=2,
  FLASH_ERROR_WRP=3,
  FLASH_COMPLETE=4,
  FLASH_TIMEOUT=5,
}Flash_Status;
//FLASH Keys for OPTKEYR
#define RDP_Key                 ((UINT16)0x00A5)
#define FLASH_KEY1              ((UINT32)0x45670123)
#define FLASH_KEY2              ((UINT32)0xCDEF89AB)
//FLASH BANK address
#define FLASH_BANK1_END_ADDRESS ((UINT32)0x0807FFFF)
#define FLASH_EraseTimeout      0x000B0000
#define FLASH_ProgramTimeout    0x00002000

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x080FFFFF))
#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806))

#define FLASH_BACKUP_NONE               0
#define FLASH_BACKUP_ROM                1
#define FLASH_BACKUP_RAM                2
#define FLASH_BACKUP_MODE               FLASH_BACKUP_RAM//1=ROM,2=RAM
typedef struct Data_Flash
{
	UINT8  Item[SIZE_FLASHPAGE];
	UINT16 Index,Count;
} Type_DFLA;
//==============================================================================================================================
//[COM]
#define SIZE_NSN_LEN            8
#define SIZE_COM_MT             8
#define SIZE_ADR_LEN            0x20
typedef struct Data_COM_PRTC
{
  UINT16 Index,Count,TimeIndex,TimeCount,*Item;
} Type_COMPRTC;
typedef struct Data_COM_PortIndex
{
  UINT16 I,O,App;
} Type_COMPort;

struct Data_COM_Port
{
	UINT8  Type,Index,BaudIndex,Name[8]; UINT32 Baud;
};
struct DATA_COM_BUS
{
  UINT8  Size,Count,Index,*Item;//总线子设备缓冲大小，子设备个数，子设备索引，子设备列表
  UINT8  NSN[SIZE_NSN_LEN],NSNLen;//主设备
};
struct Data_AddressPos
{
  UINT8 Len,Port,Addr;
};
struct Data_Address
{
  UINT8 Layer,LayerLen[2],LayerAddrIndex,LayerAddrCount,AddrIndex;//层索引，当前层单个地址长度，层地址索引与个数，地址索引
  UINT8 RelayLayer;struct Data_AddressPos NextAP,LocalAP;//中继位置
	UINT8 Len,Item[SIZE_ADR_LEN];//地址总长度,Item=地址头+地址列表, Index:0_3=发送者个数，路径个数，接收者个数,中继层索引
};

struct Data_MessTime
{
  UINT16 Pos;UINT32 Time;//位置，时间
};

struct Data_MultiMessTime
{
  UINT8 Size,Count,Index;
  struct Data_MessTime Item[SIZE_COM_MT];
};
struct COM_Control_BIT
{
  UINT8 RW:2;           //0=W,1=R,2=WR,3=RW;
  UINT8 BG:1;           //2,
  UINT8 SF:1;           //3,
  UINT8 PW:1;           //4,
  UINT8 AD:1;           //5,
  UINT8 AP:1;           //6,
  UINT8 BC:1;           //7,
};

struct Data_TXItem
{
  UINT8 TimeOut_Time,TimeOut_TimeCount,TimeOut_Count;//超时控制
  UINT16 Pos,Len,Index;//项内字符控制
};

typedef struct Data_COM_TXFrame
{
  union{UINT8 Control;struct COM_Control_BIT Control_BIT;};
  UINT8  *Item,Command,Verify;
	UINT16 Size,Count,Index,ParaCount,PortIndex;UINT32 Time;
  struct Data_TXItem TXI;
  struct Data_MultiMessTime MMT;
} Type_COM_TXFrame;
typedef struct Data_COM_RXFrame
{
  union{UINT8 Control;struct COM_Control_BIT Control_BIT;};
	UINT8  *Item,Command,Verify;
	UINT16 Size,Count,Index,ParaCount,PortIndex;UINT32 Time;
  UINT16 PacketTimeCount,PacketIndex,LFParaCount,LFSubParaCount;
	struct Data_Address ADR;
} Type_COM_RXFrame;

typedef struct Data_COMItem//Communication
{
	union  UINT32_REG State;//状态
  UINT32 RXTime,TXTime;//最后的收发时间
	struct Data_Array_UINT8   TPW;//传输密码
  struct Data_COM_PRTC      PRTC;//Protocol,协议，
  struct Data_COM_PortIndex PORT;//当前输出端口，多任务端口
  struct Data_COM_RXFrame   RF;//接收包
	struct Data_COM_TXFrame   TF;//发送包
  struct DATA_COM_BUS       BUS;//总线
} Type_COMItem;
//==============================================================================================================================
//setup register
//------------------------------------------------------------------------------------------------------------------------------
//WWDG and IWDG
#define SET_WWDG_CFR_WDGTB      WWDG_CFR_WDGTB_DIV8
#define SET_WWDG_CFR_W          0x7F
#define SET_IWDG_PR_DIV         IWDG_PR_DIV256
//------------------------------------------------------------------------------------------------------------------------------
//NVIC
#define SET_PRIGROUP            PRIGROUP_2//0_4
#define VECTTAB_FLASH           0
#define VECTTAB_SRAM            1
#define SDK_VECTTAB             VECTTAB_FLASH
//------------------------------------------------------------------------------------------------------------------------------
//RCC
#define SET_SW                  RCC_CFGR_SW_PLL//Sysclk source
#define SET_HPRE                0//AHB prescaler,Sysclk divided by: 0_7=1,8_B=2^(HPRE-7),C_F=2^(HPRE-6)
#define SET_PPRE1               4//APB1,0_3=/1,4_7=CLK_AHB/(1<<(PPRE1-3))
#define SET_PPRE2               0//APB2,0_3=/1,4_7=CLK_AHB/(1<<(PPRE2-3))
#define SET_ADCPRE              1//0_3= PCLK2/((ADCPRE+1)*2)
#define SET_PLLSRC              1//PLL entry clock source:0=HSI/2,1=PREDIV1
#define SET_PLLMULL             7//2_7=*(PLLMULL+2)=*4_9,11=*6.5
#define SET_MCO                 0//MCO:0=No CLK,4=SysCLK

#define SET_PREDIV1             0// PLL2CLK/1
#define SET_PREDIV2             0// HSE/1
#define SET_PLL2MUL             7// 6_12= *(PLL2MUL+2)=*8_14,14=*16,15=*20
#define SET_PLL3MUL             7// 6_12= *(PLL2MUL+2)=*8_14,14=*16,15=*20
#define SET_PREDIV1SRC          0//0=HSE,1=PLL2
#define SET_I2S2SRC             0//
#define SET_I2S3SRC             0//

#define CLK_LSI                 24000//Internal slow OSC
#define CLK_LSE                 32000//External slow OSC
#define CLK_HSI                 8000000//Internal OSC
#if IsDensity(CL)
  #define CLK_HSE               25000000//External OSC
#else
  #define CLK_HSE               8000000//External OSC
#endif
#define CLK_USBFS               48000000//USB OTGFS
#define CLK_PREDIV2             (CLK_HSE/(SET_PREDIV2+1))

#if SET_PLL2MUL>=6 && SET_PLL2MUL<=12
#define CLK_PLL2                ((SET_PLL2MUL+2)*CLK_PREDIV2)
#elif SET_PLL2MUL==14
#define CLK_PLL2                (16*CLK_PREDIV2)
#elif SET_PLL2MUL==15
#define CLK_PLL2                (20*CLK_PREDIV2)
#else
#define CLK_PLL2                CLK_PREDIV2
#endif

#if SET_PLL3MUL>=6 && SET_PLL3MUL<=12
#define CLK_PLL3                ((SET_PLL3MUL+2)*CLK_PREDIV2)
#elif SET_PLL3MUL==14
#define CLK_PLL3                (16*CLK_PREDIV2)
#elif SET_PLL3MUL==15
#define CLK_PLL3                (20*CLK_PREDIV2)
#else
#define CLK_PLL3                CLK_PREDIV2	
#endif

#define CLK_PREDIV1             (SET_PREDIV1SRC==0 ? CLK_HSE/(SET_PREDIV1+1) : CLK_PLL2/(SET_PREDIV1+1))
#define CLK_PLLIN               (SET_PLLSRC==0 ? CLK_HSI/2:CLK_PREDIV1)

#if SET_PLLMULL>=2 && SET_PLLMULL<=7
#define CLK_PLL                 (CLK_PLLIN*(SET_PLLMULL+2))
#elif SET_PLLMULL==11
#define CLK_PLL                 (CLK_PLLIN*6.5)
#endif

#define CLK_PLLVCO              (2*CLK_PLL)
#define SET_OTGFSPRE            (CLK_PLL==72000000 ? 0:1)//0=2*PLLCLK/3(PLLCLK=72M),1=2*PLLCLK/2(PLLCLK=48MHz)
#define SET_PLLXTPRE            (SET_PREDIV1&1)

#if     SET_SW==0 
#define CLK_SYS                 CLK_HSI
#elif   SET_SW==1
#define CLK_SYS                 CLK_HSE
#else
#define CLK_SYS                 CLK_PLL//Max 72MHz 
#endif

//#define CLK_AHB                 CLK_SYS/(SET_HPRE<8 ? 1:1<<(SET_HPRE-(SET_HPRE<12 ? 7:6))) //HCLK
#if SET_HPRE<8
#define CLK_AHB                 CLK_SYS//Max 72MHz
#elif SET_HPRE<12
#define CLK_AHB                 (CLK_SYS/(1<<(SET_HPRE-7)))
#else
#define CLK_AHB                 (CLK_SYS/(1<<(SET_HPRE-6)))
#endif

//#define CLK_APB1                (CLK_AHB/(SET_PPRE1<4 ?  1: 1<<(SET_PPRE1-3)))//Max 36MHz
#if SET_PPRE1<4
#define CLK_APB1                CLK_AHB
#else
#define CLK_APB1                (CLK_AHB/(1<<(SET_PPRE1-3)))
#endif

//#define CLK_APB2                (CLK_AHB/(SET_PPRE2<4 ?  1: 1<<(SET_PPRE2-3)))//Max 72MHz
#if SET_PPRE2<4
#define CLK_APB2                CLK_AHB
#else
#define CLK_APB2                (CLK_AHB/(1<<(SET_PPRE2-3)))
#endif


#define CLK_ADC                 CLK_APB2/(SET_ADCPRE+1)//Max 14MHz
#define CLK_TIM234567           (SET_PPRE1<4 ? CLK_APB1:2*CLK_APB1)//Max 36MHz
#define CLK_TIM1                CLK_APB2//Max 72MHz
#define CLK_DMA                 CLK_AHB
#define CLK_CORE                CLK_AHB

#define SET_RCC_CFGR            SET_MCO<<24|SET_OTGFSPRE<<22|SET_PLLMULL<<18|SET_PLLXTPRE<<17|SET_PLLSRC<<16\
                                |SET_ADCPRE<<14|SET_PPRE2<<11|SET_PPRE1<<8|SET_HPRE<<4|SET_SW
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define SET_RCC_CFGR2           SET_PREDIV1|SET_PREDIV2<<4|SET_PLL2MUL<<8|SET_PLL3MUL<<12\
                                |SET_PREDIV1SRC<<16|SET_I2S2SRC<<17|SET_I2S3SRC<<18
//==============================================================================================================================
//asm function macro
static __inline void __EIRQ()   { __asm volatile ("cpsie i"); }//__enable_irq()
static __inline void __DIRQ()   { __asm volatile ("cpsid i"); }//__disable_irq()
static __inline void __EFIRQ()  { __asm volatile ("cpsie f"); }//__enable_fault_irq()
static __inline void __DFIRQ()  { __asm volatile ("cpsid f"); }//__disable_fault_irq() 
static __inline void __NOP()    { __asm volatile ("nop"); }
static __inline void __WFI()    { __asm volatile ("wfi"); }
static __inline void __WFE()    { __asm volatile ("wfe"); }
static __inline void __SEV()    { __asm volatile ("sev"); }
static __inline void __ISB()    { __asm volatile ("isb"); }
static __inline void __DSB()    { __asm volatile ("dsb"); }
static __inline void __DMB()    { __asm volatile ("dmb"); }
static __inline void __CLREX()  { __asm volatile ("clrex"); }

#define EIRQ()                  { __asm volatile ("cpsie i"); }
#define DIRQ()                  { __asm volatile ("cpsid i"); }
#define EFIRQ()                 { __asm volatile ("cpsie f"); }
#define DFIRQ()                 { __asm volatile ("cpsid f"); }
#define NOP()                   { __asm volatile ("nop"); }
#define WFI()                   { __asm volatile ("wfi"); }
#define WFE()                   { __asm volatile ("wfe"); }
#define SEV()                   { __asm volatile ("sev"); }
#define ISB()                   { __asm volatile ("isb"); }
#define DSB()                   { __asm volatile ("dsb"); }
#define DMB()                   { __asm volatile ("dmb"); }
#define CLREX()                 { __asm volatile ("clrex"); }
//==============================================================================================================================
#define ITM_RXBUFFER_EMPTY   0x5AA55AA5U     //Value identifying \ref ITM_RxBuffer is ready for next character.
extern volatile UINT32 ITM_RxBuffer;         //External variable to receive characters.

__STATIC_INLINE UINT32 ITM_SendChar (UINT32 ch)
{
  if (M3ITM.TCR_BIT.ITMENA && M3ITM.TER_BIT.B0) {while (M3ITM.PORT[0] == 0)NOP(); M3ITM.PORT_B8[0].V = (UINT8)ch;}//ITM enabled and ITM Port #0 enabled */
  return (ch);
}
__STATIC_INLINE INT32 ITM_ReceiveChar (void)
{
  INT32 ch = -1;//no character available 
  if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY){ch = ITM_RxBuffer; ITM_RxBuffer = ITM_RXBUFFER_EMPTY;} //ready for next character
  return (ch);
}
__STATIC_INLINE UINT32 ITM_CheckChar (void)
{
  return (ITM_RxBuffer == ITM_RXBUFFER_EMPTY ? 0:1);
}
//------------------------------------------------------------------------------------------------------------------------------
__STATIC_INLINE void SystemReset(void)
{
  __DSB(); M3SYS.AIRCR  =0x05FA0001| (M3SYS.AIRCR&0x700);// Keep priority group unchanged
};
//------------------------------------------------------------------------------------------------------------------------------
__STATIC_INLINE UINT32 CPUGet_CONTROL(void)
{
  register UINT32 __regControl         __ASM("control");
  return(__regControl);
}
__STATIC_INLINE void CPUSet_CONTROL(UINT32 control)
{
  register UINT32 __regControl         __ASM("control");
  __regControl = control;
}
__STATIC_INLINE UINT32 CPUGet_IPSR(void)
{
  register UINT32 __regIPSR          __ASM("ipsr");
  return(__regIPSR);
}
__STATIC_INLINE UINT32 CPUGet_APSR(void)
{
  register UINT32 __regAPSR          __ASM("apsr");
  return(__regAPSR);
}
__STATIC_INLINE UINT32 CPUGet_xPSR(void)
{
  register UINT32 __regXPSR          __ASM("xpsr");
  return(__regXPSR);
}
__STATIC_INLINE UINT32 CPUGet_PSP(void)
{
  register UINT32 __regProcessStackPointer  __ASM("psp");
  return(__regProcessStackPointer);
}
__STATIC_INLINE void CPUSet_PSP(UINT32 topOfProcStack)
{
  register UINT32 __regProcessStackPointer  __ASM("psp");
  __regProcessStackPointer = topOfProcStack;
}
__STATIC_INLINE UINT32 CPUGet_MSP(void)
{
  register UINT32 __regMainStackPointer     __ASM("msp");
  return(__regMainStackPointer);
}
__STATIC_INLINE void CPUSet_MSP(UINT32 topOfMainStack)
{
  register UINT32 __regMainStackPointer     __ASM("msp");
  __regMainStackPointer = topOfMainStack;
}
__STATIC_INLINE UINT32 CPUGet_PRIMASK(void)
{
  register UINT32 __regPriMask         __ASM("primask");
  return(__regPriMask);
}
__STATIC_INLINE void CPUSet_PRIMASK(UINT32 priMask)
{
  register UINT32 __regPriMask         __ASM("primask");
  __regPriMask = (priMask);
}
__STATIC_INLINE UINT32  CPUGet_BASEPRI(void)
{
  register UINT32 __regBasePri         __ASM("basepri");
  return(__regBasePri);
}
__STATIC_INLINE void CPUSet_BASEPRI(UINT32 basePri)
{
  register UINT32 __regBasePri         __ASM("basepri");
  __regBasePri = (basePri & 0xFFU);
}
__STATIC_INLINE void CPUSet_BASEPRI_MAX(UINT32 basePri)
{
  register UINT32 __regBasePriMax      __ASM("basepri_max");
  __regBasePriMax = (basePri & 0xFFU);
}
__STATIC_INLINE UINT32 CPUGet_FAULTMASK(void)
{
  register UINT32 __regFaultMask       __ASM("faultmask");
  return(__regFaultMask);
}
__STATIC_INLINE void CPUSet_FAULTMASK(UINT32 faultMask)
{
  register UINT32 __regFaultMask       __ASM("faultmask");
  __regFaultMask = (faultMask & 1);
}

#define GETSP()        __current_sp()
//==============================================================================================================================
//c function macro
#define IWDG_Enable(EN)         {if(EN)IWDG.KR=0xCCCC; else DBG.CR_BIT.IWDG_STOP=1;}//0=Disable,1=Enable
#define IWDG_CLR()              IWDG.KR=0xAAAA
#define WWDG_Enable(EN)         WWDG.CR_BIT.WDGA=EN//1=Enable,0=Disable
#define WWDG_CLR()              WWDG.CR_BIT.T=0x7F
#define WDT_Enable(EN)          IWDG_Enable(EN);//WWDG_Enable(EN)
#define WDT_CLR()               IWDG_CLR();//WWDG_CLR()
#define SETIRQPR(IRQN,PP,SP)    {M3SYS.IPR[(IRQN)]= ((PP&(0x0f>>(SET_PRIGROUP-3)))<<(SET_PRIGROUP+1)|(SP&(0x0f>>(7-SET_PRIGROUP)))<<4);}//PP=0_15,SP=0_15
#define SETIRQEN(IRQN,EN)       {if(EN) M3SYS.ISER[(IRQN)>>5] = (1<<((IRQN)&0x1F));else M3SYS.ICER[(IRQN)>>5] = (1<<((IRQN)&0x1F));}//bit=interrupt enable:1= enable ,0=disable
#define SETIRQ(IRQN,PP,SP)      SETIRQPR(IRQN,PP,SP);SETIRQEN(IRQN,1);

#define SETPINMODE(PN,Mode)     {if(PN&0x18)GPIO[(PN>>5)].CRH=(GPIO[(PN>>5)].CRH&~((UINT32)0x0F<<((PN&7)*4)))|((UINT32)Mode<<((PN&7)*4)); \
                                       else GPIO[(PN>>5)].CRL=(GPIO[(PN>>5)].CRL&~((UINT32)0x0F<<((PN&7)*4)))|((UINT32)Mode<<((PN&7)*4));}

#define SETPINEXTI(PN)          {AFIO.EXTICR[(PN>>2)&3]&=(0xFFFF-(0x0F<<((PN&3)*4)));AFIO.EXTICR[(PN>>2)&3]|=((PN>>5)<<((PN&3)*4));}
//------------------------------------------------------------------------------------------------------------------------------
#define Device_Reset()          SystemReset()
//==============================================================================================================================
#endif
//==============================================================================================================================
