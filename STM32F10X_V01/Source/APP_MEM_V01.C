//==============================================================================================================================
#include "global.h"
//LDY万能程序模板，版权所有，违法必究！
//By LDY,mobile:15361844952,2022/4/1
//==============================================================================================================================
//Device
const UINT8             Device_BaseDT[8]  __attribute__((at(BASE_DEVICE+0x000)))=RSTV_BaseDT; 									 
const UINT8             Device_MadeDT[8]  __attribute__((at(BASE_DEVICE+0x008)))=RSTV_MadeDT; 									 
const UINT8             Device_HS[8]      __attribute__((at(BASE_DEVICE+0x010)))={
								        (RSTV_UGSpaceOn<<0)+(RSTV_UGInsertOn<<1)+(RSTV_UGEndAddressOn<<2)+(RSTV_AutoPowerOn<<3)
                        +(RSTV_AutoSaveOn<<4)+(RSTV_CircleSaveOn<<5)+(RSTV_CPWOn<<6)+(RSTV_TPWOn<<7),
                        RSTV_APPCount,RSTV_APPIndex,RSTV_UGAPPIndex,
                        RSTV_UGEndAddress&0xff,RSTV_UGEndAddress>>8,RSTV_UGEndAddress>>16,RSTV_UGEndAddress>>24
                        };
const UINT8             Device_NSN[0x10] __attribute__((at(BASE_DEVICE+0x018))) ={
                        0x04,DC_NSN&0xff,(DC_NSN>>8)&0xff,(DC_NSN>>16)&0xff,(DC_NSN>>24)&0xff,(DC_NSN>>32)&0xff,
                        (DC_NSN>>40)&0xff,(DC_NSN>>48)&0xff,
                        };
const UINT8             Device_ID[24] __attribute__((at(BASE_DEVICE+0x28))) ={//DCCL,DCID,DCSN,DCCP,CPUCP,CPUID
	                      DC_DCCL&0xff,(DC_DCCL>>8)&0xff,(DC_DCCL>>16)&0xff,(DC_DCCL>>24)&0xff,
	                      DC_DCID&0xff,(DC_DCID>>8)&0xff,(DC_DCID>>16)&0xff,(DC_DCID>>24)&0xff,
	                      DC_DCSN&0xff,(DC_DCSN>>8)&0xff,(DC_DCSN>>16)&0xff,(DC_DCSN>>24)&0xff,
                        DC_DCCP&0xff,(DC_DCCP>>8)&0xff,(DC_DCCP>>16)&0xff,(DC_DCCP>>24)&0xff,
                        DC_CPUCP&0xff,(DC_CPUCP>>8)&0xff,(DC_CPUCP>>16)&0xff,(DC_CPUCP>>24)&0xff,
	                      DC_CPUID&0xff,(DC_CPUID>>8)&0xff,(DC_CPUID>>16)&0xff,(DC_CPUID>>24)&0xff
                        };
const UINT8             Device_CP[0x40] __attribute__((at(BASE_DEVICE+0x40))) ={DC_Company};
const UINT8             Device_NV[0x40] __attribute__((at(BASE_DEVICE+0x80))) ={DC_NameVer};
const UINT8             Device_FirstRun[0x40] __attribute__((at(BASE_DEVICE+0xC0)))={0x00};
const UINT8             Device_MadePos[0x80]  __attribute__((at(BASE_DEVICE+0x100))) ={DC_MadePos};
const UINT8             Device_RunPos[0x80] __attribute__((at(BASE_DEVICE+0x180))) ={DC_RunPos};

const UINT32            BAT_SV_Count __attribute__((at(BASE_DEVICE+0x200)))=12;//BAT采样值_电压曲线       
const UINT16            BAT_SV[31][2] __attribute__((at(BASE_DEVICE+0x204)))={
                        {0,0},{0x836,1100},{0x8A0,1150},{0x906,1200},{0x96E,1250},
                        {0x9D6,1300},{0xA3E,1350}, {0xAA4,1400}, {0xB0A,1450},{0xB62,1500},
                        {0xBDA,1550},{0xC3E,1600},
                        };
const UINT32            BAT_VP_Count  __attribute__((at(BASE_DEVICE+0x280)))=10;//BAT电压_容量曲线
const UINT16            BAT_VP[31][2] __attribute__((at(BASE_DEVICE+0x284)))={
                        {0,0},{1100,10},{1150,40},{1200,80},{1250,200},
                        {1300,430},{1350,630},{1400,780},{1450,900},{1500,1000},
                        };
const UINT32            CPU_TPCount __attribute__((at(BASE_DEVICE+0x300)))=32;//Vsense温度曲线
const INT16             CPU_TP[63][2] __attribute__((at(BASE_DEVICE+0x304)))={
                        {0x51A,880},{0x560,830},{0x5B0,780},{0x60C,760},{0x652,740},{0x6AE,720},{0x70C,700},{0x760,680},{0x7B6,660},{0x812,640},
                        {0x866,620},{0x8CE,600},{0x91C,580},{0x976,560},{0x9C6,540},{0xA26,520},{0xA7E,500},{0xAD6,480},{0xB32,460},{0xB86,440},
                        {0xBDA,420},{0xC26,400},{0xC76,380},{0xCD6,360},{0xD36,340},{0xD86,320},{0xDC6,300},{0xE06,280},{0xE4E,260},{0xE87,240},
                        {0xEBF,220},{0xEF7,200},
                        };

                        
#if FLASH_BACKUP_MODE==FLASH_BACKUP_ROM
const UINT8             Device_BKP[SIZE_FLASHPAGE] __attribute__((at(BASE_DEVICE+0x400)))={0x00};
#endif
//==============================================================================================================================
const UINT32            SET_GPIO[SDK_GPIO_COUNT][3]={
	                       {V_GPIOACRL,V_GPIOACRH,V_GPIOAODR},
	                       {V_GPIOBCRL,V_GPIOBCRH,V_GPIOBODR},
	                       {V_GPIOCCRL,V_GPIOCCRH,V_GPIOCODR},
										    };//CRL,CRH,ODR
//==============================================================================================================================
//AppPara
const UINT8             AppPara[0x40]={0x00};
const UINT16            AppPara_Area_DelayTime[]={100,5};
//KEY_CC
const UINT16            Key_CC[]={0x0003}, Key_LongTime[Key_LongTime_Count]={200,400,600,1600};
const UINT16            PVR_UD[][8]={{0x087,0x14B,0x078,0x0B8,0x047,0x1B4,0x174,0x18B},{0x087,0x14B,0x078,0x0B8,0x047,0x1B4,0x174,0x18B}};//bit8=DownUp
//SPI
const UINT32            SPI_BAUD[]={8000,16000,32000,48000,96000,250000,500000,1000000,2000000,4000000,8000000,16000000};
const UINT8             SPI_BAUD_COUNT=sizeof(SPI_BAUD)/sizeof(SPI_BAUD[0]),SPI_BaudIndex[]={9,9,9};
//ADC
const UINT8             ADC1_CH[SDK_ADC1_CHCOUNT]={0,1,12};
//DAC
const UINT8             DAC1_CH[SDK_DAC1_CHCOUNT]={0,1};
//UART
const UINT32            UART_BAUD[]={1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,250000,500000,1000000,2000000};
const UINT8             UART_BAUD_COUNT=sizeof(UART_BAUD)/sizeof(UART_BAUD[0]),UART_BaudIndex[]={10,7,9,9,9,9};
//PRTC
const UINT16            PRTC_Time[64][2]={{10,10},{30,30},{100,30},{100,30},{30,100},{10,10},{30,30},{30,30}};
const UINT16            PRTC[64]={8,
                          COM_Protocol_EMPTY,COM_Protocol_LDY_V1,COM_Protocol_LDY_V2,COM_Protocol_LDY_V3,
                          COM_Protocol_LS_V1,COM_Protocol_DMX512,COM_Protocol_YY_NRF,COM_Protocol_YY_BLT
                        };
const UINT16            PRTC_UART1[]={2,COM_Protocol_DMX512,COM_Protocol_LDY_V2},PRTC_UART2[]={1,COM_Protocol_YY_BLT};
//==============================================================================================================================
Type_DAPP  DAPP;
Type_DDEV  DDEV;
Type_DEXT  DEXT;
Type_DADC  DADC;
Type_DDAC  DDAC;
Type_DKEY  DKEY;
Type_DLED  DLED;
Type_DFLA  DFLA;
Type_DSPI  DSPI;
Type_DI2S  DI2S;
Type_DI2C  DI2C;
Type_DUART DUART;
Type_DCAN  DCAN;
Type_DETH  DETH;
Type_DUSB  DUSB;
Type_DCOM  DCOM;//UART+CAN+ETH+USB
//==============================================================================================================================
//void APP_Init(UINT8 IsAfter){DDEV.Dentify=0xA2F280EE930E07A9;}
//==============================================================================================================================
