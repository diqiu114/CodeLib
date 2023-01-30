//==============================================================================================================================
#include "global.h"
//LDY万能程序模板，版权所有，违法必究！
//By LDY,mobile:15361844952,2022/4/1
//==============================================================================================================================
const UINT8             UG_Device_BaseDT[8]  __attribute__((at(UG_BASE_DEVICE+0x000)))=RSTV_BaseDT; 									 
const UINT8             UG_Device_MadeDT[8]  __attribute__((at(UG_BASE_DEVICE+0x008)))=RSTV_MadeDT; 									 
const UINT8             UG_Device_HS[8]      __attribute__((at(UG_BASE_DEVICE+0x010)))={
								        (RSTV_UGSpaceOn<<0)+(RSTV_UGInsertOn<<1)+(RSTV_UGEndAddressOn<<2)+(RSTV_AutoPowerOn<<3)
                        +(RSTV_AutoSaveOn<<4)+(RSTV_CircleSaveOn<<5)+(RSTV_CPWOn<<6)+(RSTV_TPWOn<<7),
                        RSTV_APPCount,RSTV_APPIndex,RSTV_UGAPPIndex,
                        RSTV_UGEndAddress&0xff,RSTV_UGEndAddress>>8,RSTV_UGEndAddress>>16,RSTV_UGEndAddress>>24
                        };
const UINT8             UG_Device_NSN[0x10] __attribute__((at(UG_BASE_DEVICE+0x018))) ={
                        0x04,DC_NSN&0xff,(DC_NSN>>8)&0xff,(DC_NSN>>16)&0xff,(DC_NSN>>24)&0xff,(DC_NSN>>32)&0xff,
                        (DC_NSN>>40)&0xff,(DC_NSN>>48)&0xff,
                        };
const UINT8             UG_Device_ID[24] __attribute__((at(UG_BASE_DEVICE+0x28))) ={//DCCL,DCID,DCSN,DCCP,CPUCP,CPUID
	                      DC_DCCL&0xff,(DC_DCCL>>8)&0xff,(DC_DCCL>>16)&0xff,(DC_DCCL>>24)&0xff,
	                      DC_DCID&0xff,(DC_DCID>>8)&0xff,(DC_DCID>>16)&0xff,(DC_DCID>>24)&0xff,
	                      DC_DCSN&0xff,(DC_DCSN>>8)&0xff,(DC_DCSN>>16)&0xff,(DC_DCSN>>24)&0xff,
                        DC_DCCP&0xff,(DC_DCCP>>8)&0xff,(DC_DCCP>>16)&0xff,(DC_DCCP>>24)&0xff,
                        DC_CPUCP&0xff,(DC_CPUCP>>8)&0xff,(DC_CPUCP>>16)&0xff,(DC_CPUCP>>24)&0xff,
	                      DC_CPUID&0xff,(DC_CPUID>>8)&0xff,(DC_CPUID>>16)&0xff,(DC_CPUID>>24)&0xff
                        };
const UINT8             UG_Device_CP[0x40] __attribute__((at(UG_BASE_DEVICE+0x40))) ={DC_Company};
const UINT8             UG_Device_NV[0x40] __attribute__((at(UG_BASE_DEVICE+0x80))) ={UG_DC_NameVer};
const UINT8             UG_Device_FirstRun[0x40] __attribute__((at(UG_BASE_DEVICE+0xC0)))={0x00};
const UINT8             UG_Device_MadePos[0x80]  __attribute__((at(UG_BASE_DEVICE+0x100))) ={DC_MadePos};
const UINT8             UG_Device_RunPos[0x80] __attribute__((at(UG_BASE_DEVICE+0x180))) ={DC_RunPos};

#if FLASH_BACKUP_MODE==FLASH_BACKUP_ROM
const UINT8             UG_Device_BKP[SIZE_FLASHPAGE] __attribute__((at(UG_BASE_DEVICE+0x1000)))={0x00};
#endif
//==============================================================================================================================
const UINT32            UG_SET_GPIO[SDK_GPIO_COUNT][3]={
	                       {V_GPIOACRL,V_GPIOACRH,V_GPIOAODR},
	                       {V_GPIOBCRL,V_GPIOBCRH,V_GPIOBODR},
	                       {V_GPIOCCRL,V_GPIOCCRH,V_GPIOCODR},
										    };//CRL,CRH,ODR
//==============================================================================================================================
//AppPara
const UINT8             UG_AppPara[0x40]={0x00};   
const UINT16            UG_AppPara_Area_DelayTime[]={100,5};
//KEY_CC
const UINT16            UG_Key_CC[]={0x0003}, UG_Key_LongTime[Key_LongTime_Count]={200,400,600,1600};
const UINT16            UG_PVR_UD[][8]={{0x087,0x14B,0x078,0x0B8,0x047,0x1B4,0x174,0x18B},{0x087,0x14B,0x078,0x0B8,0x047,0x1B4,0x174,0x18B}};//bit8=DownUp
//SPI
const UINT32            UG_SPI_BAUD[]={8000,16000,32000,48000,96000,250000,500000,1000000,2000000,4000000,8000000,16000000};
const UINT8             UG_SPI_BAUD_COUNT=sizeof(UG_SPI_BAUD)/sizeof(UG_SPI_BAUD[0]),UG_SPI_BaudIndex[]={9,9,9};
//ADC
const UINT8             UG_ADC1_CH[SDK_ADC1_CHCOUNT]={0,1,12};
//DAC
const UINT8             UG_DAC1_CH[SDK_DAC1_CHCOUNT]={0,1};
//UART
const UINT32            UG_UART_BAUD[]={1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,250000,500000,1000000,2000000};
const UINT8             UG_UART_BAUD_COUNT=sizeof(UG_UART_BAUD)/sizeof(UG_UART_BAUD[0]),UG_UART_BaudIndex[]={10,7,9,9,9,9};
//PRTC
const UINT16            UG_PRTC_Time[64][2]={{10,10},{30,30},{100,30},{100,30},{30,100},{10,10},{30,30},{30,30}};
const UINT16            UG_PRTC[64]={8,
                          COM_Protocol_EMPTY,COM_Protocol_LDY_V1,COM_Protocol_LDY_V2,COM_Protocol_LDY_V3,
                          COM_Protocol_LS_V1,COM_Protocol_DMX512,COM_Protocol_YY_NRF,COM_Protocol_YY_BLT
                        };
const UINT16            UG_PRTC_UART1[]={2,COM_Protocol_DMX512,COM_Protocol_LDY_V2},UG_PRTC_UART2[]={1,COM_Protocol_YY_BLT};
//==============================================================================================================================
//void UG_APP_Init(UINT8 IsAfter){Dentify=0xA2F280EE930E07A9;}
//==============================================================================================================================
