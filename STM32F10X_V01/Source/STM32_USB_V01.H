//==============================================================================================================================
#ifndef STM32_USB_V01_H
#define STM32_USB_V01_H
//==============================================================================================================================
#include "STM32F10X_V01.h"
//==============================================================================================================================
//<System_const.h>
#ifndef _SYSTEM_CONST_
#define _SYSTEM_CONST_

    //#define _DSP_COMMD_TEST_

    #define System_TestFlag

    #define ADC1_DR_Address                 ((u32)0x4001244C)

    #define __NET_FORMAT_USB_HID__      0x8080                  /* 用于定义协议栈的网络接口 */
    #define __NET_FORMAT_CAN__          0x9090
    #define __NET_FORMAT_USART__        0xa0a0

    #define __NET_FORMAT__    __NET_FORMAT_USB_HID__            /* 用于定义协议栈的网络接口 */

    #define __CAN_DIVER_ROUTE__         0xed3c                  /* CAN设备类型为路由设备 */
    #define __CAN_DIVER_NODE__          0xdec3                  /* CAN设备类型为节点设备 */
    #define __CAN_DIVER_TYPE__   __CAN_DIVER_ROUTE__            /* 定义当前CAN设备为路由设备 */

    /*定义使用的管脚*/
    #define USB_DISCONNECT                  GPIOA
    #define USB_DISCONNECT_PIN              GPIO_Pin_10

    #define A7196_SCS					GPIOA_Pin5_OUT
    #define A7196_SCK					GPIOA_Pin4_OUT
    #define A7196_SDIO_OUT				GPIOA_Pin3_OUT
    #define A7196_SDIO_IN               GPIOA_Pin3_INPUT
    #define A7196_CKO					GPIOA_Pin0_OUT
    #define A7196_GIO1					GPIOA_Pin2_INPUT
    #define A7196_GIO2					GPIOA_Pin1_INPUT
		
    #define A7196_SDIO_IN_P             GPIO_Pin_3
    #define A7196_SDIO_EDP              GPIOA
/*		
#define PO_A719X_SCS            GPIOA_Pin5_OUT
#define PO_A719X_SCK            GPIOA_Pin4_OUT
#define PO_A719X_CKO            GPIOA_Pin0_OUT
#define PO_A719X_GPIO1          GPIOA_Pin2_OUT
#define PI_A719X_GPIO1          GPIOA_Pin2_INPUT
#define PO_A719X_GPIO2          GPIOA_Pin1_OUT
#define PI_A719X_GPIO2          GPIOA_Pin1_INPUT
#define PO_A719X_SDIO           GPIOA_Pin3_OUT
#define PI_A719X_SDIO           GPIOA_Pin3_INPUT
#define PO_TXS0108_OE           GPIOB_Pin11_OUT
#define PO_LED1                 GPIOB_Pin4_OUT
		
#define A719X_SCS_SET(V)        PO_A719X_SCS=V
#define A719X_SCK_SET(V)        PO_A719X_SCK=V
#define A719X_CKO_SET(V)        PO_A719X_CKO=V
#define A719X_GPIO1_SET(V)      PO_A719X_GPIO1=V
#define A719X_GPIO2_SET(V)      PO_A719X_GPIO2=V
#define A719X_SDIO_SET(V)       PO_A719X_SDIO=V
#define TXS0108_OS_SET(V)       PO_TXS0108_OE=V
#define A719X_SDIO_SETDIR(V)    if(V) GPIOA->CRL=GPIOA->CRL&0xFFFF0FFF|0x00003000; else GPIOA->CRL=GPIOA->CRL&0xFFFF0FFF|0x00008000;
		
#define V_GPIOACRL      0x44333883//config
#define V_GPIOACRH      0x38844344//config
#define V_GPIOAODR      0x0000A027//output

#define V_GPIOBCRL      0x43334444
#define V_GPIOBCRH      0x44443444
#define V_GPIOBODR      0x00000810

#define V_GPIOCCRL      0x44444444
#define V_GPIOCCRH      0x44444444
#define V_GPIOCODR      0x00000000
*/

    #define SYSTEM_PILOT_LIGHT          GPIOB_Pin4_OUT
    #define SYSTEM_RUN_LIGHT            GPIOB_Pin5_OUT
    #define SYSTEM_ERR_LIGHT            GPIOB_Pin6_OUT
    
    #define SYSTEM_ENABLE_PIN               GPIOB_Pin8_OUT

    #define SYSTEM_INITIAL_CODE             0x5a5aa5a5
    #define SYSTEM_TEST_CODE                0x796845a5      // 测试机的运行代码
    #define SYSTEM_RUN_CODE                 0xf9453289      // 系统正常运行的代码

    #define __SYSTEM_BOOT__
    
    #define USB1 0x0
    #define USB2 0x1

    #define G16(X)  0x11021                 //CRC16校验多项式 X16+X12+x5+1

    #define LOCAL_CAN_ROUTE_ADDR            0x00a0          /* CAN路由节点地址 */
    #define LOCAL_CAN_ROUTE_ADDR_MIN        0x00a0
    #define LOCAL_CAN_ROUTE_ADDR_MAX        0x00af
    #define CAN_RADIO_ADDR                  0xffff          /* CAN广播地址 */
    #define USART_STACK_ADDR                0x0050          /* 总线上的串口地址 */
    #define USART_STACK_ROUTE_ADDR_MIN      0x0050
    #define USART_STACK_ROUTE_ADDR_MAX      0x005f

    typedef enum
    {
        FRAME_ERROR_HEADER  = 0x20,                         /* 没有找到数据头 */
        FRAME_ERROR_DATA_LENGTH = 0x21,                     /* 数据长度错误 */
        FRAME_ERROR_CAN_PACKET_LOSS = 0x22,                 /* CAN总线数据包丢失 */
        FRAME_ERROR_PACKET_LOSS = 0x23,                     /* 协议栈数据包丢失 */
        FRAME_ERROR_CHECK_SUM = 0x24,                       /* 校验和错误 */
        FRAME_ERROR_DEVICE_MAX = 0x25,                      /* 设备挂在数量超过总线极限 */
        FRAME_ERROR_DEVICE_ADDR = 0x26,                     /* 设备地址错误 */
        FRAME_ERROR_DEVICE_BUF_FULL = 0x27,                 /* 设备缓缓从区满 */
        FRAME_ERROR_DEVICE_OVER = 0x28,                     /* 设备地址超出设备缓冲区容量 */
    }ProtocolStack_Error_Enum;
    typedef enum
    {
        BASIC_COMMAND_HANDSHAKE = 0xa0,                     /* 设备握手 */
        BASIC_COMMAND_GET_DEVICE_INFO = 0xa1,               /* 获取设备信息 */
        BASIC_COMMAND_GET_DEVICE_PIDCODE = 0xa2,            /* 获取芯片PID码 */
        BASIC_COMMAND_GET_DEVICE_ADDR = 0xa3,               /* 获取can总线临时地址 */
        BASIC_COMMAND_SET_DEVICE_CAN_ADDR = 0xa4,           /* 复位设备 */
        BASIC_COMMAND_DEVIEC_AUTO_REQ_ADDR = 0xa5,          /* 自动请求CAN设备地址 */
        BASIC_COMMAND_PUBLIC_STAUTS = 0xa6,                 /* 公共状态命令 */
        BASIC_COMMAND_SYNC_TIME = 0xa7,                     /* 同步网络时间 */
        BASIC_COMMAND_INIT_NET = 0xa8,                      /* 网络初始化 */
        BASIC_COMMAND_GET_NODE_INFO = 0xa9,                 /* 获取节点功能 */
        BASIC_COMMAND_SET_NODE_INFO = 0xaa,                 /* 设置节点功能 */
        BASIC_COMMAND_DISABLE_NODE = 0xab,                  /* 禁止节点 */
        BASIC_COMMAND_ENABLE_NODE = 0xac,                   /* 使能节点 */
        BASIC_COMMAND_SET_PASSWORD = 0xad,                  /* 设置密码 */
        BASIC_COMMAND_HEART_FRAME = 0xae,                   /* 心跳帧 */
        BASIC_COMMAND_GET_NET_TYPE = 0xaf,                  /* 获取节点网络类型 */
        BASIC_COMMAND_DEVICE_ENROLLING = 0xb0,              /* 获取网络协议版本 */
        BASIC_COMMAND_DEVICE_ENROLLING_OK = 0xb2,           /* 设备注册通过 */

        BASIC_COMMAND_DEVICE_START_UPGRADE = 0xe0,          /* 设备进入升级状态 */
        BASIC_COMMAND_GET_DEVICE_SINFO = 0xe1,              /* 查询设备软件信息 */
        BASIC_COMMAND_GET_DEVICE_UP_ADDRES = 0xe2,          /* 查询升级地址 */
        BASIC_COMMAND_DEVICE_UPGRADE_INVC = 0xe3,           /* 升级设备向量区 */
        BASIC_COMMAND_GET_VEC_ADDR = 0xe4,                  /* 获取升级中断地址 */
        BASIC_COMMAND_GET_APP_ADDR = 0xe5,                  /* 获取升级应用地址 */
        BASIC_COMMAND_DEVICE_UPGRADE_APP = 0xe6,            /* 升级应用代码区 */
        BASIC_COMMAND_DEVICE_CONT_TRANS_ADDR = 0xe7,        /* 断点续传命令 */
        BASIC_COMMAND_DEVICE_UPGRADE_QUIT = 0xe8            /* 升级退出 */
    }BasicCommand_FrameNet;
    typedef enum
    {
        FRAMT_RADIO_ADDR    = 0xffff,                       /* 广播地址 */
        MAX_RECEIVE_DEVICE = 0x02,                          /* 最多可以容纳的设备通道数,MAX_RECEIVE_DEVICE用于HID,MAX_RECEIVE_DEVICE + 1用于串口总线 */
        MAX_RECEIVE_DEVICE_ADDR = MAX_RECEIVE_DEVICE << 1,  /* 地址列表地址长度 */
        HID_RECEVIE_INX = 0,
        WIFI_RECEVIE_INX = 1,
        USART_RECEVIE_INX = MAX_RECEIVE_DEVICE + 1,
        SYSETME_DEVICE_NUMBER = 0,                          /* 系统除去用于CAN通讯的其他通讯设备数量 */
        FRAME_RECEIVE_BUF_MAX    = 0x200,                   /* 协议包接收缓冲区空间大小 */
        FRAME_SEND_BUF_MAX = 0x0c0,                         /* 协议包发送缓冲区大小 */

        FRAMEFRAME_CONTROL_HEAD = 0x55aa,
        FRAME_FRAMEHEAD_SIZE = 0x02,
        FRAME_CONTWORD_SIZE = 0x03,
        FRAM_PASSWORD_SIZE = 0x08,                          /* 密码长度 */

        FRAME_HEAD_SIZE = FRAME_FRAMEHEAD_SIZE + FRAME_CONTWORD_SIZE,
        FRAM_CAN_SEND_MAX = 0x08,                           /* CAN最大一帧数据的长度 */
        FRAM_HID_SEND_MAX = 0x40,                           /* HID 的最大一帧数据的长度 */
        FRAM_WIFI_SEND_MAX = 0x40,                          /* WIFI能传输的最大一帧数据 */
        FRAME_ADDR_LENGTH = 0x01,                           /* 地址长度 */
        FRAME_DIVER_TYPE_HID = 0x50,                        /* 设备类型是HID */
        FRAME_DIVER_TYPE_CAN = 0x53,                        /* 设备类型是CAN */
        FRAME_DIVER_TYPE_USART = 0x59,                      /* 设备类型是USART */

        FRAME_NODE_TYPE_ROUTE = 0xc5,                       /* 节点类型是路由节点 */
        FRAME_NODE_TYPE_ENDPOINT = 0xb7,                    /* 节点类型是端点 */

        FRAME_NODE_ADDR_LENGTH = 0x02,                      /* 节点地址长度 */
    }ProtocolStack_Enum;

    typedef enum
    {
        UPCODE_STATUS_OK = 0,                   /* 操作OK */
        UPCODE_STATUS_ERR = 0x51,               /* 通讯协议数据包错误(头\长度\地址\操作......)*/
        UPCODE_STATUS_VER_ERR = 0x52,           /* 通讯协议数据包校验错误 */
        UPCODE_STATUS_CRC_ERR = 0x53,           /* CRC 错误*/
        UPCODE_STATUS_DEVICE_BUSY = 0x55,       /* 设备忙 */
        UPCODE_STATUS_CMMD_ERR = 0xa5,          /* 命令错误 */

        UPCODE_STATUS_PAK_ERR = 0x54,           /* 数据包丢包错误 */
        UPCODE_STATUS_ERASE_ERR = 0x55,         /* FLASH 擦除错误 */
        UPCODE_STATUS_PROGRAM_ERR = 0x56,       /* FLASH 编程错误 */
        UPCODE_STATUS_ADDR_ERR = 0x57,          /* 升级FLASH地址错误 */
        UPCODE_STATUS_DIVERADDR_ERR = 0x58,     /* 升级设备通讯地址错误*/

        UPCODE_QUIT_OK = 0x00,                  /* 升级正常退出 */
        UPCODE_QUIT_ERR = 0x61,                 /* 升级错误退出 */
        UPCODE_QUIT_NO_UPCODE = 0x62,           /* 没有做任何代码升级 */
        UPCODE_QUIT_FIRST_UPCODE = 0x82         /* 测试模拟第一次运行代码 */


    }UPCDE_ERR;
    //typedef enum
    //{

    #ifdef  __SYSTEM_BOOT__
        #define SYSTEM_NVIC_BOOT_ADDR                   ((unsigned long int)0x08000000)
        #define SYSTEM_NVIC_APP_ADDR                    ((unsigned long int)0x08011800)
    #else
        #define SYSTEM_NVIC_APP_ADDR                    ((unsigned long int)0x08000000)
    #endif

        #define UPCODE_BACKUP_BLOCK_START_ADDR  0x08008000   /* 备份块的起始地址 */
        #define UPCODE_BACKUP_BLOCK_END_ADDR  0x08011800     /* 备份块的结束地址 */
        #define UPCODE_SYSTEM_INVC_START_ADDR  0x08011800    /* 中断向量起始地址 */
        #define UPCODE_SYSTEM_INVC_END_ADDR  0x08012000      /* 中断向量的结束地址 */
        #define UPCODE_SYSTEM_APP_START_ADDR  0x08012000     /* 应用程序的起始地址 */
        #define UPCODE_SYSTEM_APP_END_ADDR  0x0801f000       /* 应用程序的结束地址*/
        #define UPCODE_SYSTEM_PRODUCT_START_ADDR  0x0801f800 /* 产品的备份地址 */
        #define UPCODE_SYSTEM_EDITION_START_ADDR  0x0801f900 /* 版本的备份地址 */
        #define UPCODE_SYSTEM_DATA_START_ADDR  0x0801fa00    /* 版本的备份地址 */
        #define UPCODE_FLASH_PAGE_SIZE_2K  0x0800            /* 芯片的页尺寸 */
        #define UPCODE_FLASH_PAGE_SIZE_1K  0x0400            /* 芯片的页尺寸 */
        #define UPCODE_FLASH_PAGE_INFO_1K  0x01              /* 芯片页尺寸1K */
        #define UPCODE_FLASH_PAGE_INFO_2K  0x02              /* 芯片页尺寸2K */
        #define UPCODE_FLASH_PROODUCT_LENTH  0x20            /* 产品字符长度 */

        #define UPCODE_EEPROM_HARDWARE_ADDR 0x0a0            /* IIC的硬件地址 */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR0 0x00       /* 升级运行状态码首地址 */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR1 0x01       /* 升级运行状态码首地址 */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR2 0x02       /* 升级运行状态码首地址 */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR3 0x03       /* 升级运行状态码首地址 */
        #define UPCODE_EEPROM_BAKPROGRAM_STATE_ADD0 0x04     /* 升级备份状态码首地址 */
        #define UPCODE_EEPROM_BAKPROGRAM_STATE_ADD1 0x05     /* 升级备份状态码首地址 */
        #define UPCODE_EEPROM_CAN_ID_ADDR0        0x06       /* 配置的CAN通讯ID地址高地址 */
        #define UPCODE_EEPROM_CAN_ID_ADDR1        0x07       /* 配置的CAN通讯ID地址低地址 */

        #define UPCODE_BAKPROGRAM_STATE_OK  0x85a5           /* 升级程序备份OK,可以使用备份区 */
        #define UPCODE_BAKPROGRAM_STATE_ERR 0xfa5a           /* 升级程序备份ERR,不可使用备份区 */

        #define UPCODE_SYTEM_STATE_FLASH_INX   0x08          /* 系统运行状态数据的存储位置 */
        #define UPCODE_INT_ADDR_STATE_INX  0x09              /* 系统用于存放中断编程地址的状态 */
        #define UPCODE_INT_ADDR_INX  0x0a                    /* 系统用于存放中断编程的地址值 */
        #define UPCODE_SYSTEM_EEROM_FIRST_RUN0  0xffffffff   /* EPROM第一次操作 */
        #define UPCODE_SYSTEM_EEROM_FIRST_RUN1  0x00000000   /* EPROM第一次操作 */
        #define UPCODE_SYSTEM_FIRST_RUN  0xee6633aa          /* 系统首次运行 */
        #define UPCODE_SYSTEM_STATE_NORMAL  0xddaacc55       /* 系统处于正常工作状态 */
        #define UPCODE_SYSTEM_STATE_UPGRADE  0x5a66a522      /* 系统处于升级状态 */
        #define UPCODE_SYSTEM_STATE_WRITE_CODE  0x85ef89b5   /* 系统处于升级状态的写代码状态 */
        #define UUCODE_INT_ADDR_STATE_NORMAL  0x55ccaadd     /* 系统处于正常运行状态 */
        #define UPCODE_INT_ADDR_STATE_ADDR  0xEFFEA55A       /* 系统处于编程中断,地址寄存器中存放的是中断地址 */
        #define UPCODE_SYSTEM_UPGRADE_ERR  0x99775aa5        /* 升级错误 */

        #define UPCODE_WAITING_TIME  0x168                   /* 进入升级模式后,UPCODE_WAITING_TIME这么多秒,如果还没有开始升级,就退出升级状态进入正常工作模式 */
        #define UPCODE_ERR_TIME  0x258                       /* 升级过程中遇到阻塞或者错误,等待10分钟后退出 */
        #define UPCODE_REPEATS_VALUE  0x0a                   /* 编程最大重复错误次数 */

        #define FLASH_WRITE_DATA_LENTH  0x0c
        #define FLASH_WRITE_INX_VAR  0x0b
        #define FLASH_WRITE_FLAG_VAR  0x5a5aa5a5

    //}UpCode_System;

/* 以下为具体产品的协议 */
    typedef enum
    {
        TP_PEDAL_PVID_CODE = 0x20,                           /* 踏板虚拟ID */
        CONTROL_PEADL_PVID_CODE = 0x30,                      /* 控台板虚拟ID */
        IO_PEDAL_PVID_CODE = 0x40,                           /* IO板虚拟ID */
        RADIO_PVID_CODE = 0xff,                              /* 虚拟的广播ID */
    }SYSTEM_HARDWARE_PVID_ENUM;
    typedef enum 
    {
        DONCE_STATUS_KEY = 0xe0,                            /* 游戏状态 */
        PC_GET_RESOURCE_PUBLIC_KEY = 0xea,                  /* PC获取资源公钥 */
    }SYSTEM_COMMD_ENUM;
    typedef enum
    {
        PEDAL_DEIVER_CODE_RIGHT_UP = 0x02005,
        PEDAL_DEIVER_CODE_LEFT_UP = 0x02001,
        PEDAL_DEIVER_CODE_MIDDLE = 0x02003,
        PEDAL_DEIVER_CODE_RIGHT_DN = 0x02004,
        PEDAL_DEIVER_CODE_LEFT_DN = 0x02002,
    }Pedal_DeiverCode;
    
    #define KEY_PRESSTIME                   5                /*按键防抖*/
    #define KEY_DOWNCODE                    0x00
    #define KEY_UPCODE                      0x01
    #define KEY_DOWNDOWNCODE                0x02
    #define KEY_NUMBER_MAX                  0x05
		
		#define PC_PACK_MAX_LEN                 10
		#define A7196_PACK_MAX_LEN	                200
		
				#define StartAddr  ((unsigned long int )0x0800C000)

#define ADC_SWITCH0_Addr  ((unsigned long int )0x0800C000)
#define A7196_CHANNEL_Addr  ((unsigned long int )0x0800C000)	
#endif
//------------------------------------------------------------------------------------------------------------------------------

//<Staruct.h>
    typedef struct
    {
        struct
        {
            unsigned long int System_1msFlag_On:1;
            unsigned long int System_Int_Event_Flag_On:1;
            unsigned long int System_Imd_Event_Flag_On:1;
            unsigned long int IIC_Error_Flag:1;
            unsigned long int System_Init_Flag:1;                       /* 系统初始化 */
            unsigned long int ReceiverData_Pack_Ok:1;                   /* 数据包准备好标志 */
            unsigned long int SendData_DlayTime_Flag:1;                 /* 延迟数据发送标志 */
            unsigned long int UartStart_SendData_Flag:1;                /* USART开始发送数据标志 */
            unsigned long int System_Verification_OK:1;                 /* 验证通过标志 */
            unsigned long int HID_Init_OK_Flag:1;                       /* HID 初始化完成 */
            unsigned long int PassWord_Settings_Flag:1;                 /* 密码被设置的标志位 */
            unsigned long int System_Blue_Receive_OK_Flag:1;            /* 蓝牙接收数据OK标志 */
            unsigned long int System_Blue_Commd_OK_Flag:1;              /* 蓝牙命令接收OK标志 */
					  unsigned long int Pack_Received:1;
        }Bit;

        unsigned char Music_Vol;                                        /* 系统音乐音量 */
        unsigned char Phone_Vol;                                        /* 系统耳机音量 */
        unsigned char Diver_NodeType;                                   /* 设备类型 */
        unsigned char Password_Val[FRAM_PASSWORD_SIZE];                 /* 存放密码的缓冲区 */
        unsigned short int Destination_CanAddr;                         /* 目标机地址 */
        unsigned short int Local_CanAddr;                               /* 本机Can地址接收器 */
        unsigned short int PowerTime;                                   /* 延时开机定时器 */
        unsigned short int Frame_OverTime;                              /* 用于系统协议帧超时计数 */
        unsigned short int System_WorkMode_Code;                        /* 系统工作状态码 */
        unsigned short int TransmitterAddr_List[MAX_RECEIVE_DEVICE + 1];/* 动态设备地址列表,首地址存放的是一共有多少设备挂在到设备上,最终设备列表将存放到EPROM中 */
        unsigned long int DiverFrame_Receive_OK;                        /* 器件接收OK的标志 最多支持32个设备 */
        unsigned long int DiverFrame_Receive_Error;                     /* 器件接收错误的标志 最多支持32个设备 */
        unsigned long int StackCommand_Flag;
        unsigned long int FrameCommand_Flag;
        unsigned long int DelayTime;
				unsigned long int LED1_TimeCount;
    }System_Struct;

    typedef struct
    {
        struct
        {
            unsigned long int System_Boot_1msFlag_On:1;         /* 用于升级程序的核心程序 */
            unsigned long int System_Boot_Int_Event_Flag_On:1;
            unsigned long int System_Boot_Imd_Event_Flag_On:1;
            unsigned long int SendData_Boot_DlayTime_Flag:1;    /* 延迟数据发送标志 */
            unsigned long int HID_Init_OK_Boot_Flag:1;          /* HID 初始化完成 */
            unsigned long int IIC_Error_Boot_Flag:1;
            unsigned long int Up_StartUp_Flag_On:1;
            unsigned long int Up_Over_Flag_On:1;
            unsigned long int Up_Error_Flag_On:1;
            unsigned long int Up_OK_Flag_On:1;
            unsigned long int Up_Moede_On:1;
            unsigned long int Up_DlayTime_Flag_On:1;
            unsigned long int Up_Online_OK_Flag:1;
            unsigned long int Up_Continue_Trans_Flag:1;         /* 中断续传标志 */
            unsigned long int Up_StartTrans_IntVecCode_Flag:1;  /* 开始传输代码 */
            unsigned long int Up_StartTrans_AppCode_Flag:1;     /* 开始传输代码 */
        }Bit;
        unsigned long int DiverFrame_Boot_Receive_OK;           /* 器件接收OK的标志 最多支持32个设备 */
        unsigned long int DiverFrame_Boot_Receive_Error;        /* 器件接收错误的标志 最多支持32个设备 */
        unsigned long int StackCommand_Boot_Flag;
        unsigned long int FrameCommand_Boot_Flag;
        unsigned long int System_RunningState_Code;             /* 运行状态寄存器 */
        unsigned long int UpGram_Addr;                          /* 编程地址 */
        unsigned long int UpGram_ContTrans_Addr;                /* 续传地址 */
        unsigned long int UpGram_Code_Lenth;                    /* 下发的代码长度 */
        unsigned long int TimeVal;
        unsigned short int Frame_Boot_OverTime;
        unsigned short int Packet_No;
        unsigned short int Packet_No_Bak;
        unsigned short int MaxPacket_No;
        unsigned short int Packet_CRC;
        unsigned short int Local_CanAddr;                       /* 本机Can地址接收器 */
        unsigned char Diver_NodeType;                           /* 设备类型 */
        unsigned char DelayTime;                                /* 用于HID发送数据延迟 */
        unsigned char Packet_Length;
        unsigned char UpGram_Err_Count;                         /* 升级错误计数 */
        unsigned char SendBuf[FRAME_SEND_BUF_MAX];
    }Upgram_Struct;

    typedef struct
    {
        union
        {
            unsigned char FrameCommand;
            struct
            {
                unsigned char ReadWrite_On_Flag:1;                          /* Bit:0 读写标志: 1是写控制, 0是读控制 */
                unsigned char ReturnControl_Flag:1;                         /* Bit:1 返回控制位: 1设备被动返回信息, 0设备主动返回信息 */
                unsigned char DestinationAddr_On_Flag:1;                    /* Bit:2 目的地址传输开关: 1报文带目的地址, 0报文不带目的地址 */
                unsigned char SourceAddr_On_Flag:1;                         /* Bit:3 源地址传输开关: 1报文带源地址, 0报文不带源地址 */
                unsigned char Encryption_Flag:1;                            /* Bit:4 0加密传输标志位: 1报文加密, 0报文不明码 */
                unsigned char LongFrame_Flag:1;                             /* Bit:5 长/短帧标志位: 1长帧, 0短帧 */
                unsigned char BrodcastingFrame_Flag:1;                      /* Bit:6 广播/单帧标志位: 1 广播帧, 0单帧 */
                unsigned char Frame_Format_Flag:1;                          /* Bit:7 帧格式: 1为控制协议帧, 0为数据协议帧 */
            }Bit;
        }Frame;

        union
        {
            unsigned short int ReceiveFlag;
            struct
            {
                unsigned short int Receive_StartFlag:1;                 /* 开始接收数据标志 */
                unsigned short int ReceiveHad_OkFlag:1;                 /* 头接收OK标志 */
                unsigned short int PakHad_OKFlag:1;                     /* 数据头OK标志 */
                unsigned short int Receive_OK_Flag:1;                   /* 接收数据OK标志 */
                unsigned short int ReceiveBuf_Fill_Flag:1;              /* 接收缓冲区满标志 */
                unsigned short int LongFrame_OK_Flag:1;                 /* 长帧标志 */
                unsigned short int LongFramw_IDERR_Flag:1;              /* 长帧错误标志 */
                unsigned short int Startup_SendData_Flag:1;             /* 启动发送数据标志 */
                unsigned short int SendData_TimeOver_Flag:1;            /* 发送数据超时标志 */
                unsigned short int SendData_DlayTime_Flag:1;            /* HID协议延时标志 ,0可以启动数据传输 */
                unsigned short int Long_Frame_OverTime_Flag:1;          /* 长帧接收超时标志 */
            }Bit;
        }ReceiveFlag;

        unsigned char Frame_DelayTime;
        unsigned char ReceiveVerify;
        unsigned char Frame_ReceiveErr;
        unsigned short int CanBus_PackID;                               /* CAN总线的长帧的处理包号存储器 */
        unsigned short int Fram_PackID;                                 /* 长帧的处理包号存储器 */
        unsigned short int Frame_OverTime;                              /* 长帧超时定时器 */
        unsigned short int Receive_Inx;                                 /* 接收指针*/
        unsigned short int Receive_CaleInx;                             /* 历遍接收缓冲区指针*/
        unsigned short int Receive_DLenth;
        unsigned char FramReceive_Buf[FRAME_RECEIVE_BUF_MAX];           /* 接收缓冲区 */
    }ProtocolStack_Receive_Struct;

    typedef struct
    {
        union
        {
            unsigned char FrameCommand;
            struct
            {
                unsigned char ReadWrite_On_Flag:1;                          /* Bit:0 读写标志: 1是写控制, 0是读控制 */
                unsigned char ReturnControl_Flag:1;                         /* Bit:1 返回控制位: 1设备被动返回信息, 0设备主动返回信息 */
                unsigned char DestinationAddr_On_Flag:1;                    /* Bit:2 目的地址传输开关: 1报文带目的地址, 0报文不带目的地址 */
                unsigned char SourceAddr_On_Flag:1;                         /* Bit:3 源地址传输开关: 1报文带源地址, 0报文不带源地址 */
                unsigned char Encryption_Flag:1;                            /* Bit:4 0加密传输标志位: 1报文加密, 0报文不明码 */
                unsigned char LongFrame_Flag:1;                             /* Bit:5 长/短帧标志位: 1长帧, 0短帧 */
                unsigned char BrodcastingFrame_Flag:1;                      /* Bit:6 广播/单帧标志位: 1 广播帧, 0单帧 */
                unsigned char Frame_Format_Flag:1;                          /* Bit:7 帧格式: 1为控制协议帧, 0为数据协议帧 */
            }Bit;
        }Frame;

        union
        {
            unsigned short int SendFlag;
            struct
            {
                unsigned short int CanSen_StartFlag:1;                  /* CAN开始发送数据标志 */
                unsigned short int ReceiveHad_OkFlag:1;                 /* 头接收OK标志 */
                unsigned short int PakHad_OKFlag:1;                     /* 数据头OK标志 */
                unsigned short int Receive_OK_Flag:1;                   /* 接收数据OK标志 */
                unsigned short int ReceiveBuf_Fill_Flag:1;              /* 接收缓冲区满标志 */
                unsigned short int LongFrame_Flag:1;                    /* 长帧标志 */
                unsigned short int LongFramw_IDERR_Flag:1;              /* 长帧错误标志 */
                unsigned short int Startup_SendData_Flag:1;             /* 启动发送数据标志 */
                unsigned short int SendData_TimeOver_Flag:1;            /* 发送数据超时标志 */
                unsigned short int SendData_DlayTime_Flag:1;            /* HID协议延时标志 ,0可以启动数据传输 */
                unsigned short int Long_Frame_OverTime_Flag:1;          /* 长帧接收超时标志 */

            }Bit;
        }SendFlag;
        unsigned char Stack_DiverType;                                  /* 通讯的设备类型 */
        unsigned short int Send_PacketNuber;                            /* 发送的数据包号 */
        unsigned short int DestinationAddr;                             /* CAN模式下需要知道接收设备的硬件地址 */
        unsigned short int SourceAddr;                                  /* 发射端的设备地址,在这个设备中是固定不变的 */
        unsigned short int Send_InPush_Inx;                             /* 发送缓冲区的入栈直针 */
        unsigned short int Send_Out_Inx;                                /* 发送缓冲区的出栈直针 */
        unsigned short int Send_DataLenth;                              /* 发送的数据包长度 */
        unsigned char FramSend_Buf[FRAME_SEND_BUF_MAX];                 /* 发送缓冲区 */
    }ProtocolStack_Send_Struct;
    typedef struct
    {
        union
        {
            unsigned char CommdFlag;
            struct
            {
                unsigned char StackCommand_Flag:1;                      /* 控制帧命令标志 */
                unsigned char FrameCommand_Flag:1;                      /* 协议帧命令标志 */
                unsigned char DestinationAddr_Sta_Flag:1;
                unsigned char SourceAddr_Sta_Flag:1;
                unsigned char DataReceive_Sta_Flag:1;
            }Bit;
        }CommdFlag;
        union
        {
            unsigned char FrameCommand;
            struct
            {
                unsigned char ReadWrite_On_Flag:1;                          /* Bit:0 读写标志: 1是写控制, 0是读控制 */
                unsigned char ReturnControl_Flag:1;                         /* Bit:1 返回控制位: 1设备被动返回信息, 0设备主动返回信息 */
                unsigned char DestinationAddr_On_Flag:1;                    /* Bit:2 目的地址传输开关: 1报文带目的地址, 0报文不带目的地址 */
                unsigned char SourceAddr_On_Flag:1;                         /* Bit:3 源地址传输开关: 1报文带源地址, 0报文不带源地址 */
                unsigned char Encryption_Flag:1;                            /* Bit:4 0加密传输标志位: 1报文加密, 0报文不明码 */
                unsigned char LongFrame_Flag:1;                             /* Bit:5 长/短帧标志位: 1长帧, 0短帧 */
                unsigned char BrodcastingFrame_Flag:1;                      /* Bit:6 广播/单帧标志位: 1 广播帧, 0单帧 */
                unsigned char Frame_Format_Flag:1;                          /* Bit:7 帧格式: 1为控制协议帧, 0为数据协议帧 */
            }Bit;
        }FrameCommand_Bak;
        unsigned char MasterCommd;                                      /* 存放主命令 */
        unsigned char SlaveCommd;                                       /* 存从命令 */
        unsigned char Frame_DelayTime;                                  /* 帧延迟时间 */
        unsigned short int Inx;
        unsigned char Addr_Inx;
        unsigned short int Frame_DLenth;                                /* 有效数据长度 */
        unsigned short int Commd_DLenth;
        unsigned short int DestinationAddr_DLenth;
        unsigned short int SourceAddr_DLenth;
        unsigned char Stack_DiverType;                                  /* 命令的设备类型 */
        unsigned char CommdData[FRAME_SEND_BUF_MAX];                    /* 命令数据 */
        unsigned char DestinationAddr_List[MAX_RECEIVE_DEVICE_ADDR];    /* 目的地址列表 */
        unsigned char SourceAddr_List[MAX_RECEIVE_DEVICE_ADDR];         /* 源地址列表 */
    }FrameStack_Struct;

    typedef struct
    {
        unsigned char PEQ_ID;                                               /* EQ编号 */
        unsigned char PEQ_Type;                                             /* 滤波器类型 */
        float PEQ_Fs;                                                       /* 采样率 */
        float PEQ_F0;                                                       /* 中心频率 */
        float PEQ_Q;                                                        /* Q值 */
        float PEQ_Boost;                                                    /* 频点增益 */
        float PEQ_Gain;                                                     /* 整体提升增益 */

        float B0;
        float B1;
        float B2;
        float A1;
        float A2;

        unsigned long int Coefficient_B0;
        unsigned long int Coefficient_B1;
        unsigned long int Coefficient_B2;
        unsigned long int Coefficient_A1;
        unsigned long int Coefficient_A2;

        unsigned char SendData_B0[4];
        unsigned char SendData_B1[4];
        unsigned char SendData_B2[4];
        unsigned char SendData_A1[4];
        unsigned char SendData_A2[4];
    }ParmetricEQ_Struct;

    typedef struct
    {
        struct
        {
            unsigned short int EV20_Power_OnFlag:1;
            unsigned short int EV20_Diver0_Init_Flag:1;
            unsigned short int EV20_Diver0_Pairing_OKFlag:1;
            unsigned short int EV20_Diver0_Startup_PairFlaga:1;
            unsigned short int EV20_Diver0_OffLine;

        }BitFlag;

        unsigned char EV20_Diver0_System_DlayTime;
        unsigned char EV20_Commad;
        unsigned char EV20_DiverNumber;
        unsigned char EV20_Parameter;
        unsigned char EV20_Diver0_Volume;
        unsigned char EV20_Diver0_Power;
        unsigned char EV20_Diver0_Badn;
        unsigned char EV20_Diver0_ErrCion;
        unsigned short int EV20_Pairing_Status;
    }EV2_Sturct;
		
				 typedef struct
    {
			unsigned char RE_A7196_Data[A7196_PACK_MAX_LEN];
			unsigned char RE_A7196_TX_Buf;
			unsigned char RE_A7196_TX_LEN;
			unsigned char RE_A7196_RX_Buf;
			unsigned char HEAD_Inx;
		}A7196_Sturct;
			 typedef struct
    {
			unsigned char PC_Data[PC_PACK_MAX_LEN][64];
			unsigned char PC_Data_LEN[PC_PACK_MAX_LEN];
			unsigned char PC_TX_Buf;
			unsigned char PC_RX_Buf;
		}PC_Sturct;

//------------------------------------------------------------------------------------------------------------------------------
//<USBFS.h>
//<usb_core.h>
typedef struct OneDescriptor
{
  UINT8 *Descriptor;
  UINT16 Descriptor_Size;
}
ONE_DESCRIPTOR, *PONE_DESCRIPTOR;
// All the request process routines return a value of this type   If the return value is not SUCCESS or NOT_READY,  the software will STALL the correspond endpoint 

// When send data out of the device,CopyData() is used to get data buffer 'Length' bytes data
//if Length is 0, CopyData() returns the total length of the data
//if the request is not supported, returns 0  (NEW Feature )
//if CopyData() returns -1, the calling routine should not proceed further and will resume the SETUP process by the class device
//if Length is not 0, CopyData() returns a pointer to indicate the data location Usb_wLength is the data remain to be sent,
// Usb_wOffset is the Offset of original data When receive data from the host,
// CopyData() is used to get user data buffer which is capable  of Length bytes data to copy data from the endpoint buffer.
//if Length is 0, CopyData() returns the available data length,
//if Length is not 0, CopyData() returns user buffer address  Usb_rLength is the data remain to be received,  Usb_rPointer is the Offset of data buffer
typedef struct _ENDPOINT_INFO
{
  uint16_t  Usb_wLength;
  uint16_t  Usb_wOffset;
  uint16_t  PacketSize;
  uint8_t   *(*CopyData)(uint16_t Length);
}ENDPOINT_INFO;

typedef struct _DEVICE
{
  uint8_t Total_Endpoint;     //Number of endpoints that are used
  uint8_t Total_Configuration;//Number of configuration available
}DEVICE;

typedef union
{
  uint16_t w;
  struct BW
  {
    uint8_t bb1;
    uint8_t bb0;
  }
  bw;
} uint16_t_uint8_t;

typedef struct _DEVICE_INFO
{
  uint8_t USBbmRequestType; //bmRequestType
  uint8_t USBbRequest;            //bRequest
  uint16_t_uint8_t USBwValues;         //wValue
  uint16_t_uint8_t USBwIndexs;         //wIndex
  uint16_t_uint8_t USBwLengths;        //wLength

  uint8_t ControlState;           //USB_CONTROL_STATE
  uint8_t Current_Feature;
  uint8_t Current_Configuration;   //Selected configuration  //CONFIGURATION是怎么取值的，代表什么意义？
  uint8_t Current_Interface;       //Selected interface of current configuration 
  uint8_t Current_AlternateSetting;//Selected Alternate Setting of current interface

  ENDPOINT_INFO Ctrl_Info;
}DEVICE_INFO;

typedef struct _DEVICE_PROP
{
  void (*Init)(void);        //Initialize the device
  void (*Reset)(void);       //Reset routine of this device

  //Device dependent process after the status stage
  void (*Process_Status_IN)(void);
  void (*Process_Status_OUT)(void);

  //Procedure of process on setup stage of a class specified request with data stage\
    All class specified requests with data stage are processed in Class_Data_Setup Class_Data_Setup()\
    responses to check all special requests and fills ENDPOINT_INFO  according to the request\
    If IN tokens are expected, then wLength & wOffset will be filled  with the total transferring bytes and the starting position\
    If OUT tokens are expected, then rLength & rOffset will be filled  with the total expected bytes and the starting position in the buffer\
    If the request is valid, Class_Data_Setup returns SUCCESS, else UNSUPPORT CAUTION:\
    Since GET_CONFIGURATION & GET_INTERFACE are highly related to the individual classes, they will be checked and processed here.
  
  USB_RESULT (*Class_Data_Setup)(uint8_t RequestNo);

  //Procedure of process on setup stage of a class specified request without data stage \
    All class specified requests without data stage are processed in Class_NoData_Setup  Class_NoData_Setup\
    responses to check all special requests and perform the request  CAUTION:\
    Since SET_CONFIGURATION & SET_INTERFACE are highly related to the individual classes, they will be checked and processed here.
  
  USB_RESULT (*Class_NoData_Setup)(uint8_t RequestNo);

  //Class_Get_Interface_Setting This function is used by the file usb_core.c to test if the selected Interface\
    and Alternate Setting (uint8_t Interface, uint8_t AlternateSetting) are supported by  the application.\
    This function is writing by user. It should return "SUCCESS" if the Interface\
    and Alternate Setting are supported by the application or "UNSUPPORT" if they  are not supported.

  USB_RESULT (*Class_Get_Interface_Setting)(uint8_t Interface, uint8_t AlternateSetting);

  uint8_t* (*GetDeviceDescriptor)(uint16_t Length);
  uint8_t* (*GetConfigDescriptor)(uint16_t Length);
  uint8_t* (*GetStringDescriptor)(uint16_t Length);

  //This field is not used in current library version. It is kept only for compatibility with previous versions
  void* RxEP_buffer;
  uint8_t MaxPacketSize;
}DEVICE_PROP;

typedef struct _USER_STANDARD_REQUESTS
{
  void (*User_GetConfiguration)(void);       //Get Configuration
  void (*User_SetConfiguration)(void);       // Set Configuration
  void (*User_GetInterface)(void);           // Get Interface
  void (*User_SetInterface)(void);           // Set Interface
  void (*User_GetStatus)(void);              // Get Status
  void (*User_ClearFeature)(void);           // Clear Feature
  void (*User_SetEndPointFeature)(void);     // Set Endpoint Feature
  void (*User_SetDeviceFeature)(void);       // Set Device Feature
}
USER_STANDARD_REQUESTS;

#define Type_Recipient (pInformation->USBbmRequestType & (REQUEST_TYPE | RECIPIENT))

#define Usb_rLength Usb_wLength
#define Usb_rOffset Usb_wOffset

#define USBwValue USBwValues.w
#define USBwValue0 USBwValues.bw.bb0
#define USBwValue1 USBwValues.bw.bb1
#define USBwIndex USBwIndexs.w
#define USBwIndex0 USBwIndexs.bw.bb0
#define USBwIndex1 USBwIndexs.bw.bb1
#define USBwLength USBwLengths.w
#define USBwLength0 USBwLengths.bw.bb0
#define USBwLength1 USBwLengths.bw.bb1

uint8_t Setup0_Process(void);
uint8_t Post0_Process(void);
uint8_t Out0_Process(void);
uint8_t In0_Process(void);

USB_RESULT Standard_SetEndPointFeature(void);
USB_RESULT Standard_SetDeviceFeature(void);

uint8_t *Standard_GetConfiguration(uint16_t Length);
USB_RESULT Standard_SetConfiguration(void);
uint8_t *Standard_GetInterface(uint16_t Length);
USB_RESULT Standard_SetInterface(void);
uint8_t *Standard_GetDescriptorData(uint16_t Length, PONE_DESCRIPTOR pDesc);

uint8_t *Standard_GetStatus(uint16_t Length);
USB_RESULT Standard_ClearFeature(void);
void NOP_Process(void);

extern  DEVICE_PROP Device_Property;
extern  USER_STANDARD_REQUESTS User_Standard_Requests;
extern  DEVICE  Device_Table;
extern  DEVICE_INFO Device_Info;

/* cells saving status during interrupt servicing */
//extern uint16_t SaveRState,SaveTState;

#define ValBit(VAR,Place)    (VAR & (1 << Place))
#define SetBit(VAR,Place)    (VAR |= (1 << Place))
#define ClrBit(VAR,Place)    (VAR &= ((1 << Place) ^ 255))

#ifdef STM32F10X_CL
 #define SendZeroLength()  {PCD_EP_Write (0, 0, 0) ; DUSB.TXSTAT=USB_EPR_STAT_VALID;}//SaveTState=EP_TX_VALID;
#else
  #define SendZeroLength() {USB.CH[0].TXCOUNT=0x00; DUSB.TXSTAT=USB_EPR_STAT_VALID;}//SaveTState=EP_TX_VALID;
#endif


#define StatusInfo0 StatusInfo.bw.bb1//Reverse bb0 & bb1
#define StatusInfo1 StatusInfo.bw.bb0

//------------------------------------------------------------------------------------------------------------------------------
//<usb_def.h>
typedef enum _RECIPIENT_TYPE
{
  DEVICE_RECIPIENT,     //Recipient device
  INTERFACE_RECIPIENT,  //Recipient interface
  ENDPOINT_RECIPIENT,   //Recipient endpoint
  OTHER_RECIPIENT
} RECIPIENT_TYPE;

typedef enum _STANDARD_REQUESTS
{
  GET_STATUS = 0,
  CLEAR_FEATURE,
  RESERVED1,
  SET_FEATURE,
  RESERVED2,
  SET_ADDRESS,
  GET_DESCRIPTOR,
  SET_DESCRIPTOR,
  GET_CONFIGURATION,
  SET_CONFIGURATION,
  GET_INTERFACE,
  SET_INTERFACE,
  TOTAL_sREQUEST,  //Total number of Standard request
  SYNCH_FRAME = 12
} STANDARD_REQUESTS;

//Definition of "USBwValue"
typedef enum _DESCRIPTOR_TYPE
{
  DEVICE_DESCRIPTOR = 1,
  CONFIG_DESCRIPTOR,
  STRING_DESCRIPTOR,
  INTERFACE_DESCRIPTOR,
  ENDPOINT_DESCRIPTOR
} DESCRIPTOR_TYPE;

//Feature selector of a SET_FEATURE or CLEAR_FEATURE
typedef enum _FEATURE_SELECTOR
{
  ENDPOINT_STALL,
  DEVICE_REMOTE_WAKEUP
} FEATURE_SELECTOR;

//Definition of "USBbmRequestType"
#define REQUEST_TYPE      0x60  //Mask to get request type
#define STANDARD_REQUEST  0x00  //Standard request
#define CLASS_REQUEST     0x20  //Class request
#define VENDOR_REQUEST    0x40  //Vendor request

#define RECIPIENT         0x1F  //Mask to get recipient
//------------------------------------------------------------------------------------------------------------------------------
//<usb_init.h>
void USB_Init(void);
//extern uint8_t	EPindex;
extern DEVICE_INFO*	pInformation;
extern DEVICE_PROP*	pProperty;
extern USER_STANDARD_REQUESTS *pUser_Standard_Requests;
extern uint16_t	SaveState ;
extern uint16_t wInterrupt_Mask;
//------------------------------------------------------------------------------------------------------------------------------
//<usb_int.h>
void CTR_LP(void);
void CTR_HP(void);
//------------------------------------------------------------------------------------------------------------------------------
//<usb_type.h>
#ifndef NULL
#define NULL ((void *)0)
#endif

#if !defined (__STM32F10x_H) && !defined(__STM32L1XX_H)
#if 0
typedef signed long      s32;
typedef signed short     s16;
typedef signed char      s8;

typedef volatile signed long      vs32;
typedef volatile signed short     vs16;
typedef volatile signed char      vs8;

typedef unsigned long       u32;
typedef unsigned short      u16;
typedef unsigned char       u8;

typedef unsigned long  const    uc32;  /* Read Only */
typedef unsigned short const    uc16;  /* Read Only */
typedef unsigned char  const    uc8;   /* Read Only */

typedef volatile unsigned long      vu32;
typedef volatile unsigned short     vu16;
typedef volatile unsigned char      vu8;

typedef volatile unsigned long  const    vuc32;  /* Read Only */
typedef volatile unsigned short const    vuc16;  /* Read Only */
typedef volatile unsigned char  const    vuc8;   /* Read Only */

typedef enum { RESET = 0, SET   = !RESET } FlagStatus, ITStatus;

typedef enum { ERROR = 0, SUCCESS  = !ERROR} ErrorStatus;
#endif
#endif /* __STM32F10x_H && __STM32L15x_H */

//------------------------------------------------------------------------------------------------------------------------------
//<USB.H>
//<hw_config.h>
#define USB1 0x0
#define USB2 0x1

void Set_System(void);
void GPIO_AINConfig(void);
//void TIM_Configuration(void);
//void NVIC_Configuration(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(unsigned char UsbModule);
void Get_SerialNum(void);

extern System_Struct System_Markf;
//------------------------------------------------------------------------------------------------------------------------------
//<usb_conf.h>
/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_conf.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : CustomHID demo configuration file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF_H
#define __USB_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/
/*-------------------------------------------------------------*/
/* EP_NUM */
/* defines how many endpoints are used by the device */
/*-------------------------------------------------------------*/
#define EP_NUM     (3)

#ifndef STM32F10X_CL
/*-------------------------------------------------------------*/
/* --------------   Buffer Description Table  -----------------*/
/*-------------------------------------------------------------*/
/* buffer table base address */
/* buffer table base address */
#define BTABLE_ADDRESS      (0x00)

// rx/tx buffer base address

//#define ENDP0_RXADDR        (0x18)
//#define ENDP0_TXADDR        (0x58)
//#define ENDP1_RXADDR        0x98
//#define ENDP1_TXADDR        0xD8
//#define ENDP2_RXADDR        0x118
//#define ENDP2_TXADDR        0x18C  //0x18C

/*-------------------------------------------------------------*/
/* -------------------   ISTR events  -------------------------*/
/*-------------------------------------------------------------*/
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_WKUPM | CNTR_SUSPM | CNTR_ERRM  | CNTR_SOFM \
                 | CNTR_ESOFM | CNTR_RESETM )
#endif /* STM32F10X_CL */  




#endif /*__USB_CONF_H*/

//------------------------------------------------------------------------------------------------------------------------------
//<usb_desc.h>
/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_desc.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Descriptor Header for CustomHID Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                      0x21
#define CUSTOMHID_SIZ_HID_DESC                   0x09
#define CUSTOMHID_OFF_HID_DESC                   0x12

#define CUSTOMHID_SIZ_DEVICE_DESC                18
#define CUSTOMHID_SIZ_CONFIG_DESC                41
#define CUSTOMHID_SIZ_REPORT_DESC                33	//原鼠标74
#define CUSTOMHID_SIZ_STRING_LANGID              4
#define CUSTOMHID_SIZ_STRING_VENDOR              40		//原鼠标36
#define CUSTOMHID_SIZ_STRING_PRODUCT             32		//原鼠标70
#define CUSTOMHID_SIZ_STRING_SERIAL              26		//原鼠标26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC];
extern const uint8_t CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC];
extern const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC];
extern const uint8_t CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID];
extern const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR];
extern const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT];
extern uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */

//------------------------------------------------------------------------------------------------------------------------------
//<usb_endp.h>
extern void StackUsb_Receive(void);
//------------------------------------------------------------------------------------------------------------------------------
//<usb_istr.h>

#if  !IsDensity(CL)
 void USB_Istr(void);
#else /* STM32F10X_CL */
 UINT32 STM32_PCD_OTG_ISR_Handler(void);
#endif /* STM32F10X_CL */

/* function prototypes Automatically built defining related macros */

void EP1_IN_Callback(void);
void EP2_IN_Callback(void);
void EP3_IN_Callback(void);
void EP4_IN_Callback(void);
void EP5_IN_Callback(void);
void EP6_IN_Callback(void);
void EP7_IN_Callback(void);

void EP1_OUT_Callback(void);
void EP2_OUT_Callback(void);
void EP3_OUT_Callback(void);
void EP4_OUT_Callback(void);
void EP5_OUT_Callback(void);
void EP6_OUT_Callback(void);
void EP7_OUT_Callback(void);

#ifndef STM32F10X_CL

#ifdef CTR_CALLBACK
void CTR_Callback(void);
#endif

#ifdef DOVR_CALLBACK
void DOVR_Callback(void);
#endif

#ifdef ERR_CALLBACK
void ERR_Callback(void);
#endif

#ifdef WKUP_CALLBACK
void WKUP_Callback(void);
#endif

#ifdef SUSP_CALLBACK
void SUSP_Callback(void);
#endif

#ifdef RESET_CALLBACK
void RESET_Callback(void);
#endif

#ifdef SOF_CALLBACK
void SOF_Callback(void);
#endif

#ifdef ESOF_CALLBACK
void ESOF_Callback(void);
#endif

#else /* STM32F10X_CL */

/* Interrupt subroutines user callbacks prototypes.
   These callbacks are called into the respective interrupt sunroutine functinos
   and can be tailored for various user application purposes.
     Note: Make sure that the correspondant interrupt is enabled through the 
     definition in usb_conf.h file */ 
void INTR_MODEMISMATCH_Callback(void);
void INTR_SOFINTR_Callback(void);
void INTR_RXSTSQLVL_Callback(void);
void INTR_NPTXFEMPTY_Callback(void);
void INTR_GINNAKEFF_Callback(void);
void INTR_GOUTNAKEFF_Callback(void);
void INTR_ERLYSUSPEND_Callback(void);
void INTR_USBSUSPEND_Callback(void);
void INTR_USBRESET_Callback(void);
void INTR_ENUMDONE_Callback(void);
void INTR_ISOOUTDROP_Callback(void);
void INTR_EOPFRAME_Callback(void);
void INTR_EPMISMATCH_Callback(void);
void INTR_INEPINTR_Callback(void);
void INTR_OUTEPINTR_Callback(void);
void INTR_INCOMPLISOIN_Callback(void);
void INTR_INCOMPLISOOUT_Callback(void);
void INTR_WKUPINTR_Callback(void);

/* Isochronous data update */
void INTR_RXSTSQLVL_ISODU_Callback(void); 

#endif
//------------------------------------------------------------------------------------------------------------------------------
//<usb_prop.h>
extern System_Struct System_Markf;
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;

void CustomHID_Init(void);
void CustomHID_Reset(void);
void CustomHID_SetConfiguration(void);
void CustomHID_Status_In (void);
void CustomHID_Status_Out (void);

USB_RESULT CustomHID_Data_Setup(uint8_t);
USB_RESULT CustomHID_NoData_Setup(uint8_t);
USB_RESULT CustomHID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *CustomHID_GetDeviceDescriptor(uint16_t );
uint8_t *CustomHID_GetConfigDescriptor(uint16_t);
uint8_t *CustomHID_GetStringDescriptor(uint16_t);
USB_RESULT CustomHID_SetProtocol(void);
uint8_t *CustomHID_GetProtocolValue(uint16_t Length);
USB_RESULT CustomHID_SetProtocol(void);
uint8_t *CustomHID_GetReportDescriptor(uint16_t Length);
uint8_t *CustomHID_GetHIDDescriptor(uint16_t Length);

#define CustomHID_GetConfiguration          NOP_Process
#define CustomHID_GetInterface              NOP_Process
#define CustomHID_SetInterface              NOP_Process
#define CustomHID_GetStatus                 NOP_Process
#define CustomHID_ClearFeature              NOP_Process
#define CustomHID_SetEndPointFeature        NOP_Process
#define CustomHID_SetDeviceFeature          NOP_Process
#define REPORT_DESCRIPTOR                  0x22
//------------------------------------------------------------------------------------------------------------------------------
//<usb_pwr.h>
void Suspend(void);
void Resume_Init(void);
void USB_Resume(USB_RESUME_STATE eResumeSetVal);
void USB_PowerOn(void);
void USB_PowerOff(void);
//------------------------------------------------------------------------------------------------------------------------------
extern System_Struct System_Markf;

void USB_ReadBUF(UINT8 EPIndex);
void USB_SendBUF(UINT8 EPIndex);
void USB_StartSend(void);
void USB_EndSend(void);
void USB_WaitSend(void);//等待发送完毕（中断外调用）,超时1秒
void USB_SendString_HW(UINT8 *s,UINT16 Len);//发送到硬件（中断外调用）
void USB_SendString(UINT8 *s,UINT16 Len);//发送到队列（中断外调用）
void USB_TXTimeOut_Timer(void);//every 100us,send timeout control;
void USB_Send_IMM(void);
//------------------------------------------------------------------------------------------------------------------------------
#if IsDensity(CL)
 #include "otgd_fs_cal.h"
 #include "otgd_fs_pcd.h"
 #include "otgd_fs_dev.h"
 #include "otgd_fs_int.h"
#endif
//==============================================================================================================================
#endif
//==============================================================================================================================
