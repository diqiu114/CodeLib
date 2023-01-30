//==============================================================================================================================
#ifndef APP_MEM_V01_H
#define APP_MEM_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
//Device
#define DC_DCCL                 CL_DANCE
#define DC_DCID                 0x00000001
#define DC_DCSN                 0x00000001
#define DC_DCCP                 CP_SHENZHEN_YY
#define DC_CPUCP                CP_Nation
#define DC_CPUID                CPU_N32G45X

#define DC_NSN                  (UINT64)0x0000000001020304
#define DC_Company              "深圳影越"
#define DC_NameVer              "Product_V01"
#define DC_FirstRun             DC_NameVer
#define DC_MadePos              "中国深圳"
#define DC_RunPos               "中国深圳"

#define SIZE_DC_Company         0x20
#define SIZE_DC_NameVer         0x20//Name+Ver
#define SIZE_DC_NP              0x20//Name+Password
#define SIZE_DC_TPW             0x20
#define SIZE_DC_MadePos         0x80
#define SIZE_DC_RunPos          0x80

#define SIZE_DC_NSN             0x08
#define SIZE_DC_RBUF            0x80
#define SIZE_DC_TBUF            0x80
#define SIZE_DC_PBUF            0x80
//==============================================================================================================================
//TIM
#define TIM2_ReloadValue        100//us,[0,65535]
#define TIM3_ReloadValue        0x0120//8us
#define TIM4_ReloadValue        200//us,[0,65535]
//==============================================================================================================================
//setup function block on/off
#define SDK_WWDG_ON             0
#define SDK_IWDG_ON             0
#define SDK_FSMC_ON             0
//==============================================================================================================================
//GPIO
#define SDK_GPIO_COUNT          3
//==============================================================================================================================
//EXTI
#define SDK_EXT_COUNT           0
typedef struct Data_EXT
{
	union UINT8_REG State;
  #if SDK_EXT_COUNT
  Type_EXTItem Item[SDK_EXT_COUNT];
  #endif
} Type_DEXT;
//==============================================================================================================================
//ADC
#define SDK_ADC_COUNT           0
#define SDK_ADC_ON              0x07//bit0_2=ADC1_ON,ADC2_ON,ADC3_ON
#define SDK_ADC1_CHCOUNT        3
#define SDK_ADC1_AVCOUNT        1
typedef struct Data_ADC//ADC
{
  union UINT8_REG State;
  #if SDK_ADC_COUNT
  UINT8  Count,Index;
  UINT32 ADC1_V[SDK_ADC1_AVCOUNT][SDK_ADC1_CHCOUNT];//convert value
  Type_ADCItem Item[SDK_ADC_COUNT];
  #endif
} Type_DADC;
//==============================================================================================================================
//DAC
#define SDK_DAC_COUNT           0
#define SDK_DAC_ON              0x01//bit0_1=DAC1_ON
#define SDK_DAC1_CHCOUNT        2
typedef struct Data_DAC
{
  union UINT8_REG State;
  #if SDK_DAC_COUNT
  UINT8 Count,Index;
  UINT32 DAC_V[SDK_DAC_COUNT][SDK_DAC1_CHCOUNT];
  Type_DACItem Item[SDK_DAC_COUNT];
  #endif
} Type_DDAC;
//==============================================================================================================================
//SPI
#define SDK_SPI_COUNT           0
#define SDK_SPI_ON              0x07//bit0=SPI1_On,bit1=SPI2_On,bit2=SPI3_On
typedef struct Data_SPI
{
	union  UINT16_REG State;
  #if SDK_SPI_COUNT
  UINT16 Count,Index;//通讯个数与首索引
  Type_SPIItem Item[SDK_SPI_COUNT];
  #endif
} Type_DSPI;
//------------------------------------------------------------------------------------------------------------------------------
//I2S
#define SDK_I2S_COUNT           0
#define SDK_I2S_ON              0x07//bit0=I2S1_On,bit1=I2S2_On,bit2=I2S3_On
typedef struct Data_I2S
{
	union  UINT16_REG State;
  #if SDK_I2S_COUNT
  UINT16 Count,Index;//通讯个数与首索引
  Type_I2SItem Item[SDK_I2S_COUNT];
  #endif
} Type_DI2S;
//------------------------------------------------------------------------------------------------------------------------------
//I2C
#define SDK_I2C_COUNT           0
#define SDK_I2C_ON              0x03//bit0=I2C1_On,bit1=I2C2_On
typedef struct Data_I2C
{
	union  UINT16_REG State;
  #if SDK_I2C_COUNT
  UINT16 Count,Index;//通讯个数与首索引
  Type_I2CItem Item[SDK_I2C_COUNT];
  #endif
} Type_DI2C;
//------------------------------------------------------------------------------------------------------------------------------
//UART,BAUD={1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,500000,1000000,2000000}
#define SDK_UART_COUNT          2
#define SDK_UART_ON             0x1F//bit0_4=UART1_5_On，可以计算出HWIndex
#define SDK_UART_LoopBack       0x00
#define SIZE_UART_RBUF          0x80
#define SIZE_UART_TBUF          0x80
typedef struct Data_UART
{
  UINT16 COMIndex[SDK_UART_MAXCOUNT];//统一通讯索引,可以根据具体项目定义成常数,需要自己计算
  #if SDK_UART_COUNT
  UINT16 Count,Index;//个数与通讯索引
  UINT8  RBUF[SDK_UART_COUNT][SIZE_UART_RBUF],TBUF[SDK_UART_COUNT][SIZE_UART_TBUF];
  Type_UARTItem Item[SDK_UART_COUNT];
  #endif
} Type_DUART;
//------------------------------------------------------------------------------------------------------------------------------
//CAN
#define SDK_CAN_COUNT           0
#define SDK_CAN_ON              0x03//bit0=CAN1_On,bit1=CAN2_On，可以计算出HWIndex
#define SDK_CAN_LoopBack        0x03
#define SIZE_CAN_RBUF           0x80
#define SIZE_CAN_TBUF           0x80
//TAD+SAD+Rsvd(1bit)=29bits，align low bit
#define CAN_TAD_BitCount        14
#define CAN_SAD_BitCount        14
typedef struct Data_CAN
{
  UINT16 COMIndex[SDK_CAN_MAXCOUNT];//统一通讯索引,可以根据具体项目定义成常数,需要自己计算
  #if SDK_CAN_COUNT
  UINT16 Count,Index;//个数与通讯索引
  UINT8  RBUF[SDK_CAN_COUNT][SIZE_CAN_RBUF],TBUF[SDK_CAN_COUNT][SIZE_CAN_TBUF];
  Type_CANItem Item[SDK_CAN_COUNT];
  #endif
} Type_DCAN;
//------------------------------------------------------------------------------------------------------------------------------
//ETH
#define SDK_ETH_COUNT           0
#define SDK_ETH_ON              0x01//bit0=ETH1_On,可以计算出HWIndex
#define SDK_ETH_LoopBack        0x01
#define SIZE_ETH_RBUF           0x80
#define SIZE_ETH_TBUF           0x80
typedef struct Data_ETH
{
  UINT16 COMIndex[SDK_ETH_MAXCOUNT];//统一通讯索引,可以根据具体项目定义成常数,需要自己计算
  #if SDK_ETH_COUNT
  UINT16 Count,Index;//个数与通讯索引
  UINT8  RBUF[SDK_ETH_COUNT][SIZE_ETH_RBUF],TBUF[SDK_ETH_COUNT][SIZE_ETH_TBUF];
  Type_ETHItem Item[SDK_ETH_COUNT];
  #endif
} Type_DETH;
//------------------------------------------------------------------------------------------------------------------------------
//USB
#define SDK_USB_COUNT           1
#define SDK_USB_ON              0x01//bit0=USB1_On,bit1=USB2_On，可以计算出HWIndex
#define SDK_USB_VID             0x0483
#define SDK_USB_PID             0x5770
#define SIZE_USB_RBUF           0x40
#define SIZE_USB_TBUF           0x1000
#define USB_RXEPIndex           1
#define USB_TXEPIndex           2
#define USB_Suspend_EN          1//Suspend Enable
#define USB_DMLenth_EN          1//Dynamic lenth enable

#define HID_DESCRIPTOR_TYPE             0x21
#define CUSTOMHID_SIZ_HID_DESC          0x09
#define CUSTOMHID_OFF_HID_DESC          0x12
#define CUSTOMHID_SIZ_DEVICE_DESC       18
#define CUSTOMHID_SIZ_CONFIG_DESC       41
#define CUSTOMHID_SIZ_REPORT_DESC       33	  //原鼠标74
#define CUSTOMHID_SIZ_STRING_LANGID     4
#define CUSTOMHID_SIZ_STRING_VENDOR     40		//原鼠标36
#define CUSTOMHID_SIZ_STRING_PRODUCT    32		//原鼠标70
#define CUSTOMHID_SIZ_STRING_SERIAL     26		//原鼠标26
#define STANDARD_ENDPOINT_DESC_SIZE     0x09
typedef struct Data_USB
{
	union  UINT8_REG  State;
  union  UINT16_REG StatusInfo;
	UINT32 RXADDR[USB_EPCount];
	UINT32 TXADDR[USB_EPCount];
	UINT16 EPSIZE[USB_EPCount];
  
	UINT8  EPIndex,RXSTAT,TXSTAT,DEVADDR;
	USB_DEVICE_STATE DEVState;
  USB_ResumeState  ResumeS;
  DEVICE_INFO	 Device_Info;
  UINT32 ProtocolValue,REP;//REP=Related_Endpoint
  #if SDK_USB_COUNT
  UINT16 Count,Index;//个数与通讯索引
  UINT8 RBUF[SDK_USB_COUNT][SIZE_USB_RBUF],TBUF[SDK_USB_COUNT][SIZE_USB_TBUF];
  Type_USBItem Item[SDK_USB_COUNT];
  #endif
} Type_DUSB;
//==============================================================================================================================
//融合通讯
#define COM_Packet_TimeOut      10//10ms,无协议数据包超时

#define SDK_COM_COUNT           (SDK_UART_COUNT+SDK_CAN_COUNT+SDK_ETH_COUNT+SDK_USB_COUNT)
#define SDK_UART_Index          0
#define SDK_CAN_Index           (SDK_UART_COUNT)
#define SDK_ETH_Index           (SDK_UART_COUNT+SDK_CAN_COUNT)
#define SDK_USB_Index           (SDK_UART_COUNT+SDK_CAN_COUNT+SDK_ETH_COUNT)
#define COMIDX_UART1            0
#define COMIDX_UART2            1
#define COMIDX_CAN1             2
#define COMIDX_USB1             3 
#define COMIDX_MAIN             COMIDX_USB1

typedef struct Data_COM
{
	union  UINT16_REG State;//状态
  #if SDK_COM_COUNT
  UINT16 Count,Index;
  Type_COMItem Item[SDK_COM_COUNT];
  #endif
} Type_DCOM;
//==============================================================================================================================
#define RSTV_BaseDT             {0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x14}//2000/1/1_00:00:00:00
#define RSTV_MadeDT             {0x32,0x20,0x1E,0x08,0x01,0x0A,0x15,0x14}//2021/10/1_08:30:32:50

#define RSTV_UGSpaceOn          1//升级-空白模式
#define RSTV_UGInsertOn         0//升级-插入模式
#define RSTV_UGEndAddressOn     1//升级-结束地址
#define RSTV_AutoPowerOn        0//自动开机
#define RSTV_AutoSaveOn         1//自动存盘
#define RSTV_CircleSaveOn       1//循环存储
#define RSTV_CPWOn              0//控制密码
#define RSTV_TPWOn              0//传输密码
#define RSTV_APPCount           2//APP个数
#define RSTV_APPIndex           0//APPIndex
#define RSTV_UGAPPIndex         1//UGAPPIndex
#define RSTV_UGEndAddress       ((UINT32)0x00000000)

#define SIZE_User_Name          32
#define SIZE_User_PW            32
#define LG_Count                2
#define SIZE_LGName             16

typedef struct Data_User
{
  UINT8 Name[SIZE_User_Name],NameLen;//用户名
  UINT8 PW[4][SIZE_User_PW],PWLen[4];//密码,密码可以多个，例:"abcd,1234"
} Type_User;

struct Device_SetupState_BIT//硬件配置
{
  UINT32 UGSpaceOn:1;//0,升级-空白模式
  UINT32 UGInsertOn:1;//1,升级-插入模式
  UINT32 UGEndAddressOn:1;//2,升级-结束地址
	UINT32 AutoPowerOn:1;//3,自动开机
	UINT32 AutoSaveOn:1;//4,自动存盘
	UINT32 CircleSave:1;//5,循环存储
  UINT32 CPWOn:1;//6,控制密码
  UINT32 TPWOn:1;//7,传输密码
	UINT32 APPCount:8;//8,APP个数
  UINT32 APPIndex:8;//16,当前App
  UINT32 UGAppIndex:8;//24,升级App
};

typedef union Device_SetupState_REG
{
	UINT32 VAL;UINT8 Byte[4];
	struct Device_SetupState_BIT BIT;
}Type_Device_SetupState;

typedef struct Device_Setup//硬件配置,Size=8
{
  Type_Device_SetupState ST;
  UINT32 UGEndAddress;
  UINT8 BUSM[SIZE_NSN_LEN],BUSMLen;
} Type_Device_Setup;

struct Device_State_BIT//设备运行状态,统一成复位值0，方便初始化
{
	UINT32 DeviceOn:1;           //0,待机状态
  UINT32 SleepOn:1;            //1,睡眠状态
	UINT32 ConnectOn:1;          //2,链接状态
	UINT32 ServiceOn:1;          //3,链接服务
  UINT32 CPUOn:1;              //4,是否CPU运行
	UINT32 DTSyncOn:1;           //5,DT同步
  UINT32 CPWOK:1;              //6,控制密码是否通过
	UINT32 Inited:1;             //7,外围芯片是否初始化
  UINT32 BATPercentOn:1;       //8,电池百分比
	UINT32 TempratureOn:1;       //9,温度
	UINT32 CameraOn:1;           //10,
	UINT32 LCDOn:1;              //11,
	UINT32 SIMOn:1;              //12,
  UINT32 Reserved0:19;         //13,
};
typedef union Device_State_REG
{
	UINT32 VAL;UINT8 Byte[4];
	struct Device_State_BIT BIT;
} Type_Device_State;

struct Data_BAT
{
  UINT16 V,P;float R,RL;
};
struct Data_Device_T
{
  INT16 V;
};
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Data_DeviceItem
{
  INT32 LastOB;struct Data_Array_UINT32 SubOB;struct Data_COM_Port PORT;
  
  struct Data_BAT      BAT;//电池
	struct Data_Device_T T;//温度  
  
  UINT8  NSNBUF[SIZE_DC_NSN]; 
	UINT16 MainPort;//连接口（用于中断外发送），主口（用于中继,必须主口使能才有用）
	UINT32 RunTime,RunCount;
	struct Data_User  User;//控制密码
	struct Data_Array_UINT8  NSN;
	Type_Device_Setup HS;//硬件配置,需要存盘
	Type_Device_State RunST;//设备运行状态
} Type_DEVItem;
//------------------------------------------------------------------------------------------------------------------------------
#define SDK_Device_Count     1
typedef struct Data_DeviceTree
{
  UINT32 Count,Index;
  Type_DEVItem Item[SDK_Device_Count];
} Type_DDEV;
//==============================================================================================================================
typedef struct Data_APP//interface function name=APP_ ,芯片无关性编程接口
{
  UINT8  TBUF[SIZE_DC_TBUF];//中断外发送
  #if SDK_COM_COUNT
  UINT8  PBUF[SIZE_DC_PBUF],IRQTBUF[SIZE_DC_TBUF];//中断参数传递，中断内发送
	struct Data_Array_UINT8  PF;//中断参数传递
  struct Data_COM_TXFrame  TF,IRQTF;//全局之发送包与中断发送包
  #endif

  Type_DateTime BaseDT,MadeDT,DT;//基准时间，制造日期，当前时间
    
  Type_APPV               V;//通用变量
  Type_INTF               INTF;//接口
} Type_DAPP;
//==============================================================================================================================
#define SDK_KeyEV_On            1//事件缓冲使能
#define SDK_KeyEV_Time_On       1//事件是否带时间
#define SIZE_SDK_KeyEV          0x08//事件缓冲大小
#define Key_EV_Up               0
#define Key_EV_Down             1
#define Key_EV_Press            2
#define Key_EV_DoubleClick      3
#define Key_EV_CUp              4
#define Key_EV_CDown            5
#define Key_EV_CLongUp          6
#define Key_EV_CLongDown        7
#define Key_EV_ScrollUp         8
#define Key_EV_ScrollDown       9
#define Key_EV_LongUp           10
#define Key_EV_LongDown         16//16_32=longdown

#define SDK_KB_On               0//矩阵
#define SDK_KB_LongDown_EN      1
#define SDK_KB_Repeat_EN        1
#define SDK_KB_RowCount         5//键盘行数
#define SDK_KB_ColCount         7//键盘列数
#define SDK_KB_KeyCount         (SDK_KB_RowCount*SDK_KB_ColCount)

#define SDK_Key_Count           4//独立键个数
#define Key_DebounceTime        5//5*5=25ms
#define Key_LongDown_EN         0x0030
#define Key_Repeat_EN           0x0000//自动重复使能
#define Key_Repeat_Time         5//5*5=25ms
#define Key_Repeat_FirstTime    160//160*5=0.8s

#define Key_LongTime_Count      4//长按时间个数
#define Key_CC_Count            1//组合键个数
#define Key_CC_LongDown_EN      0x01

#define SDK_PVR_Count           0x00
#define SDK_PVR_UDCount         0x02//贴片=8，插件=2
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Data_KeyEvent
{
  UINT8 Code;
  UINT8 EV;//0=Up,1=Down,2=Press,3=LongPress,4=DoubleClick,5=ThreeClick,6=ScrollUp,7=ScrollDown
  #if SDK_KeyEV_Time_On
  UINT32 Time;//毫秒数
  #endif
} Type_KeyEvent;
//------------------------------------------------------------------------------------------------------------------------------
typedef struct Data_KEY//可存16个独立按键+8*8键盘+独立键组合键+键盘事件缓冲
{
  union  UINT8_REG State; UINT8  Init_TimeCount;
#if SDK_Key_Count  
	UINT16 TempState,ScanState,UpState,DownState,LongDowned,LongDownState,RepeatState;//UpState=常态，可支持16个独立按键,8个PVR
  UINT8  Code,TimeCount[SDK_Key_Count],RepeatTimeCount[SDK_Key_Count],LongTimeIndex[SDK_Key_Count];UINT16 LongTimeCount[SDK_Key_Count];
#endif
#if Key_CC_Count
  UINT8 CEN[Key_CC_Count];UINT16 CTimeCount[Key_CC_Count],CLongTimeCount[Key_CC_Count],CLongTimeIndex[Key_CC_Count];
#endif
#if SDK_PVR_Count
  UINT8 PVR_State[SDK_PVR_Count],PVR_TimeCount[SDK_PVR_Count]; UINT16 PVR_TempState,PVR_AllState;
#endif
#if SDK_KB_On
  UINT8 KB_Code,KB_TimeCount,KB_RepeatTimeCount,KB_LongTimeIndex;UINT16 KB_TempState,KB_ScanState,KB_UpState,KB_LongTimeCount;
#endif
#if SDK_KeyEV_On
  UINT8 Count,Index;Type_KeyEvent Item[SIZE_SDK_KeyEV];
#endif
} Type_DKEY;
//==============================================================================================================================
#define SDK_LED_Count           2
typedef struct Data_LED
{
#if SDK_LED_Count 
	UINT8 FlashTimeCount[SDK_LED_Count],FlashCount[SDK_LED_Count],TimeCount[SDK_LED_Count];
#endif
	union UINT16_REG State;
} Type_DLED;
//==============================================================================================================================
//Var Memory
extern const UINT8              Device_BaseDT[],Device_MadeDT[],Device_HS[],Device_NSN[],Device_ID[];
extern const UINT8              Device_CP[],Device_NV[],Device_FirstRun[],Device_MadePos[],Device_RunPos[];

extern const UINT16             BAT_SV[][2],BAT_VP[][2];
extern const UINT32             BAT_SV_Count,BAT_VP_Count,CPU_TPCount,FAN_TPCount,TPCount1,TPCount2;  
extern const INT16              CPU_TP[][2],FAN_TP[][2];  
extern const UINT8              Device_BKP[],AppPara[];

extern const UINT32             SET_GPIO[][3];
extern const UINT16             AppPara_Area_DelayTime[],Key_CC[],Key_LongTime[],PVR_UD[][8];
extern const UINT32             SPI_BAUD[],UART_BAUD[];
extern const UINT8              SPI_BAUD_COUNT,SPI_BaudIndex[],UART_BAUD_COUNT,UART_BaudIndex[],ADC1_CH[],DAC1_CH[];
extern const UINT16             PRTC_Time[][2],PRTC[],PRTC_UART1[],PRTC_UART2[];

#define AppPara_Area            AppPara_Area_ROM//AppPara_Area_IIC//
#define AppPara_RunTime         0         
#define AppPara_RunCount        4
#define AppPara_Len             8
//==============================================================================================================================
extern Type_DAPP  DAPP;
extern Type_DDEV  DDEV;
extern Type_DEXT  DEXT;
extern Type_DADC  DADC;
extern Type_DDAC  DDAC;
extern Type_DKEY  DKEY;
extern Type_DLED  DLED;
extern Type_DFLA  DFLA;
extern Type_DSPI  DSPI;
extern Type_DI2S  DI2S;
extern Type_DI2C  DI2C;
extern Type_DUART DUART;
extern Type_DCAN  DCAN;
extern Type_DETH  DETH;
extern Type_DUSB  DUSB;
extern Type_DCOM  DCOM;//UART+CAN+ETH+USB
//------------------------------------------------------------------------------------------------------------------------------
#define Var                     DAPP.V.Var
#define IRQVar                  DAPP.V.IRQVar
#define INT                     DAPP.V.INT
#define IRQINT                  DAPP.V.IRQINT
#define LNG                     DAPP.V.LNG
#define IRQLNG                  DAPP.V.IRQLNG
#define U32V                    DAPP.V.U32V
#define IRQU32V                 DAPP.V.IRQU32V
#define U64V                    DAPP.V.U64V
#define IRQU64V                 DAPP.V.IRQU64V
#define TMRCount                DAPP.V.TMRCount
#define SysTimeCount            DAPP.V.SysTimeCount
#define MicroTimeCount          DAPP.V.MicroTimeCount
#define SleepTimeCount          DAPP.V.SleepTimeCount
#define Para_Save_TimeCount     DAPP.V.Para_Save_TimeCount
#define LGIndex                 DAPP.V.LGIndex
#define LGCount                 DAPP.V.LGCount
#define Dentify                 DAPP.V.Dentify
#define SystemST                DAPP.V.SystemST
#define DMXAddr                 DAPP.V.DMXAddr
#define CTLAddr                 DAPP.V.CTLAddr
#define OPTAddr                 DAPP.V.OPTAddr
#define DMX_TimeCount           DAPP.V.DMX_TimeCount
#define BLT_TimeCount           DAPP.V.BLT_TimeCount
#define NRF_TimeCount           DAPP.V.NRF_TimeCount
#define CH_Off_TimeCount        DAPP.V.CH_Off_TimeCount
#define GR_Off_TimeCount        DAPP.V.GR_Off_TimeCount
#define LG_Off_TimeCount        DAPP.V.LG_Off_TimeCount
//==============================================================================================================================
//bit
#define IMM_Event_On            SystemST.BIT.B0
#define INT_Event_On            SystemST.BIT.B1
#define TMR_Event_On            SystemST.BIT.B2

#define SendState_On            DAPP.V.ST[0].BIT.B0
#define Write_BaseDT_On         DAPP.V.ST[0].BIT.B1
#define Write_MadeDT_On         DAPP.V.ST[0].BIT.B2
#define Write_HS_On             DAPP.V.ST[0].BIT.B3
#define Write_NSN_On            DAPP.V.ST[0].BIT.B4
#define Device_Reset_On         DAPP.V.ST[0].BIT.B5
#define Device_PWSet_On         DAPP.V.ST[0].BIT.B6
#define Read_DPStr_On           DAPP.V.ST[0].BIT.B7
#define USB_IRQTFSend_On        DAPP.V.ST[0].BIT.B8
#define Key_Read_On             DAPP.V.ST[0].BIT.B9
#define Flash_WriteCode_On      DAPP.V.ST[0].BIT.B10//是否是写代码
#define DC_MainPort_On          DAPP.V.ST[0].BIT.B11
#define DC_MainPort_State       DAPP.V.ST[0].BIT.B12

#define ADC_Data_On             DAPP.V.ST[0].BIT.B16
#define DC_Protect_On           DAPP.V.ST[0].BIT.B17
#define Para_Save_On            DAPP.V.ST[0].BIT.B18
#define DMX_Connect_On          DAPP.V.ST[0].BIT.B19
#define BLT_Connect_On          DAPP.V.ST[0].BIT.B20
#define NRF_Connect_On          DAPP.V.ST[0].BIT.B21
#define NRF_HW_On               DAPP.V.ST[0].BIT.B22
#define BATLP_Flash_On          DAPP.V.ST[0].BIT.B23
#define Test_On                 DAPP.V.ST[0].BIT.B24

#define TempFlag0               DAPP.V.ST[1].BIT.B0
#define TempFlag1               DAPP.V.ST[1].BIT.B1
#define TempFlag2               DAPP.V.ST[1].BIT.B2
#define TempFlag3               DAPP.V.ST[1].BIT.B3
#define TempFlag4               DAPP.V.ST[1].BIT.B4
#define TempFlag5               DAPP.V.ST[1].BIT.B5
#define TempFlag6               DAPP.V.ST[1].BIT.B6
#define TempFlag7               DAPP.V.ST[1].BIT.B7
#define IRQTempFlag0            DAPP.V.ST[1].BIT.B8
#define IRQTempFlag1            DAPP.V.ST[1].BIT.B9
#define IRQTempFlag2            DAPP.V.ST[1].BIT.B10
#define IRQTempFlag3            DAPP.V.ST[1].BIT.B11
#define IRQTempFlag4            DAPP.V.ST[1].BIT.B12
#define IRQTempFlag5            DAPP.V.ST[1].BIT.B13
#define IRQTempFlag6            DAPP.V.ST[1].BIT.B14
#define IRQTempFlag7            DAPP.V.ST[1].BIT.B15
//------------------------------------------------------------------------------------------------------------------------------
#define HWST_SpaceMode          DDEV.Item[0].HWST.BIT.SpaceMode
#define HWST_InsertMode         DDEV.Item[0].HWST.BIT.InsertMode
#define HWST_EndAddress         DDEV.Item[0].HWST.BIT.EndAddress
#define HWST_ProgMode           DDEV.Item[0].HWST.BIT.ProgMode
#define HWST_CPWOn              DDEV.Item[0].HWST.BIT.CPWOn
#define HWST_TPWOn              DDEV.Item[0].HWST.BIT.TPWOn
#define HWST_AutoPowerOn        DDEV.Item[0].HWST.BIT.AutoPowerOn
#define HWST_AutoSaveOn         DDEV.Item[0].HWST.BIT.AutoSaveOn

#define Device_On               DDEV.Item[0].RunST.BIT.DeviceOn//0,待机状态
#define Sleep_On                DDEV.Item[0].RunST.BIT.SleepOn//1,睡眠状态
#define Connect_On              DDEV.Item[0].RunST.BIT.ConnectOn//2,链接状态
#define Service_On              DDEV.Item[0].RunST.BIT.ServiceOn//3,链接服务
#define CPU_On                  DDEV.Item[0].RunST.BIT.CPUOn//4,是否CPU运行
#define DTSync_On               DDEV.Item[0].RunST.BIT.DTSyncOn//5,DT同步
#define CPW_OK                  DDEV.Item[0].RunST.BIT.CPWOK//6,控制密码是否通过
#define DC_Inited               DDEV.Item[0].RunST.BIT.Inited//7,外围芯片是否初始化
#define BATPercent_On           DDEV.Item[0].RunST.BIT.BATPercentOn//8,电池百分比
#define Temprature_On           DDEV.Item[0].RunST.BIT.TempratureOn//9,温度
#define Camera_On               DDEV.Item[0].RunST.BIT.CameraOn//10,CameraOn
#define LCD_On                  DDEV.Item[0].RunST.BIT.LCDOn//11,LCDOn
#define SIM_On                  DDEV.Item[0].RunST.BIT.SIMOn//12,SIMOn
//------------------------------------------------------------------------------------------------------------------------------
#define COM_Head_On             DCOM.State.BIT.B0
#define COM_MMTTime_On          DCOM.State.BIT.B1
#define COM_Frame_Received      DCOM.State.BIT.B2
#define COM_Frame_Sended        DCOM.State.BIT.B3

#define COM_RBUF_HeadOn(i)      DCOM.Item[i].State.BIT.B0
#define COM_RBUF_ParaCountOn(i) DCOM.Item[i].State.BIT.B1
#define COM_RBUF_LFOn(i)        DCOM.Item[i].State.BIT.B2
#define COM_RBUF_AddrOn(i)      DCOM.Item[i].State.BIT.B3
#define COM_RBUF_AddrHeadOn(i)  DCOM.Item[i].State.BIT.B4
#define COM_RBUF_TPWOn(i)       DCOM.Item[i].State.BIT.B5
#define COM_RBUF_LocalEN(i)     DCOM.Item[i].State.BIT.B6
#define COM_RBUF_LocalOn(i)     DCOM.Item[i].State.BIT.B7
#define COM_RBUF_NextOn(i)      DCOM.Item[i].State.BIT.B8
#define COM_RBUF_AddrLenOn(i)   DCOM.Item[i].State.BIT.B9
#define COM_BUS_On(i)           DCOM.Item[i].State.BIT.B10//总线状态
#define COM_BUSL_On(i)          DCOM.Item[i].State.BIT.B11//总线子设备锁定,BusLock
#define COM_BUSM_On(i)          DCOM.Item[i].State.BIT.B12//总线主设备状态,BusMaster
#define COM_BUS_Joined(i)       DCOM.Item[i].State.BIT.B13//本节点是否加入总线
#define COM_BUS_Changed(i)      DCOM.Item[i].State.BIT.B14//总线绑定关系是否变化
#define COM_HPacket_On(i)       DCOM.Item[i].State.BIT.B15//是否具有硬件打包器
#define COM_RelayPortOn(i)      DCOM.Item[i].State.BIT.B16//是否找到中继端口
#define COM_TX_On(i)            DCOM.Item[i].State.BIT.B17//是否正在发送
#define COM_TXItem_On(i)        DCOM.Item[i].State.BIT.B18//是否正在发送消息条
#define COM_TXChar_On(i)        DCOM.Item[i].State.BIT.B19//是否正在发送字符
#define COM_TX_InIRQ(i)         DCOM.Item[i].State.BIT.B20//是否正在中断中发送
#define COM_TXContinue_On(i)    DCOM.Item[i].State.BIT.B21//是否是发送包的持续
#define COM_TXWaitReturn_On(i)  DCOM.Item[i].State.BIT.B22//发送完是否需要等待响应
#define COM_TXWait_On(i)        DCOM.Item[i].State.BIT.B23//发送消息是否需要等待
#define COM_Bit9(i)             DCOM.Item[i].State.BIT.B24//串口的第9 bit
#define COM_Connect_On(i)       DCOM.Item[i].State.BIT.B25//是否已经连接目标
#define COM_Service_On(i)       DCOM.Item[i].State.BIT.B26//是否已经打开服务
//------------------------------------------------------------------------------------------------------------------------------
#define CAN_RTR(i)          DCAN.Item[i].State.BIT.B0
#define CAN_IDE(i)          DCAN.Item[i].State.BIT.B1
//------------------------------------------------------------------------------------------------------------------------------
#define SPI_On(i)               DSPI[i].State.BIT.B0

#define USB_On                  DUSB.State.BIT.B0
#define USB_Suspend_On          DUSB.State.BIT.B1
#define USB_Reset_On            DUSB.State.BIT.B2
#define USB_MulMaxPacketSize    DUSB.State.BIT.B3
#define USB_Type_Recipient      (DUSB.Device_Info.USBbmRequestType & (USB_REQUEST_TYPE | USB_RECIPIENT))

#define LED_RX_On               DLED.State.BIT.B0
#define LED_TX_On               DLED.State.BIT.B1
//------------------------------------------------------------------------------------------------------------------------------
#define Key_Inited              DKEY.State.BIT.B0
#define Key_PVR_Inited          DKEY.State.BIT.B1
#define Key_KB_Down_On          DKEY.State.BIT.B2
#define Key_KB_LongDown_On      DKEY.State.BIT.B3
#define Key_KB_LongDowned       DKEY.State.BIT.B4
#define Key_KB_Repeat_State     DKEY.State.BIT.B5
//==============================================================================================================================
#endif
//==============================================================================================================================
