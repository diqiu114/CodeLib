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

    #define __NET_FORMAT_USB_HID__      0x8080                  /* ���ڶ���Э��ջ������ӿ� */
    #define __NET_FORMAT_CAN__          0x9090
    #define __NET_FORMAT_USART__        0xa0a0

    #define __NET_FORMAT__    __NET_FORMAT_USB_HID__            /* ���ڶ���Э��ջ������ӿ� */

    #define __CAN_DIVER_ROUTE__         0xed3c                  /* CAN�豸����Ϊ·���豸 */
    #define __CAN_DIVER_NODE__          0xdec3                  /* CAN�豸����Ϊ�ڵ��豸 */
    #define __CAN_DIVER_TYPE__   __CAN_DIVER_ROUTE__            /* ���嵱ǰCAN�豸Ϊ·���豸 */



    #define SYSTEM_PILOT_LIGHT          GPIOB_Pin4_OUT
    #define SYSTEM_RUN_LIGHT            GPIOB_Pin5_OUT
    #define SYSTEM_ERR_LIGHT            GPIOB_Pin6_OUT
    
    #define SYSTEM_ENABLE_PIN               GPIOB_Pin8_OUT

    #define SYSTEM_INITIAL_CODE             0x5a5aa5a5
    #define SYSTEM_TEST_CODE                0x796845a5      // ���Ի������д���
    #define SYSTEM_RUN_CODE                 0xf9453289      // ϵͳ�������еĴ���

    #define __SYSTEM_BOOT__
    

    #define G16(X)  0x11021                 //CRC16У�����ʽ X16+X12+x5+1

    #define LOCAL_CAN_ROUTE_ADDR            0x00a0          /* CAN·�ɽڵ��ַ */
    #define LOCAL_CAN_ROUTE_ADDR_MIN        0x00a0
    #define LOCAL_CAN_ROUTE_ADDR_MAX        0x00af
    #define CAN_RADIO_ADDR                  0xffff          /* CAN�㲥��ַ */
    #define USART_STACK_ADDR                0x0050          /* �����ϵĴ��ڵ�ַ */
    #define USART_STACK_ROUTE_ADDR_MIN      0x0050
    #define USART_STACK_ROUTE_ADDR_MAX      0x005f

    typedef enum
    {
        FRAME_ERROR_HEADER  = 0x20,                         /* û���ҵ�����ͷ */
        FRAME_ERROR_DATA_LENGTH = 0x21,                     /* ���ݳ��ȴ��� */
        FRAME_ERROR_CAN_PACKET_LOSS = 0x22,                 /* CAN�������ݰ���ʧ */
        FRAME_ERROR_PACKET_LOSS = 0x23,                     /* Э��ջ���ݰ���ʧ */
        FRAME_ERROR_CHECK_SUM = 0x24,                       /* У��ʹ��� */
        FRAME_ERROR_DEVICE_MAX = 0x25,                      /* �豸���������������߼��� */
        FRAME_ERROR_DEVICE_ADDR = 0x26,                     /* �豸��ַ���� */
        FRAME_ERROR_DEVICE_BUF_FULL = 0x27,                 /* �豸���������� */
        FRAME_ERROR_DEVICE_OVER = 0x28,                     /* �豸��ַ�����豸���������� */
    }ProtocolStack_Error_Enum;
    typedef enum
    {
        BASIC_COMMAND_HANDSHAKE = 0xa0,                     /* �豸���� */
        BASIC_COMMAND_GET_DEVICE_INFO = 0xa1,               /* ��ȡ�豸��Ϣ */
        BASIC_COMMAND_GET_DEVICE_PIDCODE = 0xa2,            /* ��ȡоƬPID�� */
        BASIC_COMMAND_GET_DEVICE_ADDR = 0xa3,               /* ��ȡcan������ʱ��ַ */
        BASIC_COMMAND_SET_DEVICE_CAN_ADDR = 0xa4,           /* ��λ�豸 */
        BASIC_COMMAND_DEVIEC_AUTO_REQ_ADDR = 0xa5,          /* �Զ�����CAN�豸��ַ */
        BASIC_COMMAND_PUBLIC_STAUTS = 0xa6,                 /* ����״̬���� */
        BASIC_COMMAND_SYNC_TIME = 0xa7,                     /* ͬ������ʱ�� */
        BASIC_COMMAND_INIT_NET = 0xa8,                      /* �����ʼ�� */
        BASIC_COMMAND_GET_NODE_INFO = 0xa9,                 /* ��ȡ�ڵ㹦�� */
        BASIC_COMMAND_SET_NODE_INFO = 0xaa,                 /* ���ýڵ㹦�� */
        BASIC_COMMAND_DISABLE_NODE = 0xab,                  /* ��ֹ�ڵ� */
        BASIC_COMMAND_ENABLE_NODE = 0xac,                   /* ʹ�ܽڵ� */
        BASIC_COMMAND_SET_PASSWORD = 0xad,                  /* �������� */
        BASIC_COMMAND_HEART_FRAME = 0xae,                   /* ����֡ */
        BASIC_COMMAND_GET_NET_TYPE = 0xaf,                  /* ��ȡ�ڵ��������� */
        BASIC_COMMAND_DEVICE_ENROLLING = 0xb0,              /* ��ȡ����Э��汾 */
        BASIC_COMMAND_DEVICE_ENROLLING_OK = 0xb2,           /* �豸ע��ͨ�� */

        BASIC_COMMAND_DEVICE_START_UPGRADE = 0xe0,          /* �豸��������״̬ */
        BASIC_COMMAND_GET_DEVICE_SINFO = 0xe1,              /* ��ѯ�豸������Ϣ */
        BASIC_COMMAND_GET_DEVICE_UP_ADDRES = 0xe2,          /* ��ѯ������ַ */
        BASIC_COMMAND_DEVICE_UPGRADE_INVC = 0xe3,           /* �����豸������ */
        BASIC_COMMAND_GET_VEC_ADDR = 0xe4,                  /* ��ȡ�����жϵ�ַ */
        BASIC_COMMAND_GET_APP_ADDR = 0xe5,                  /* ��ȡ����Ӧ�õ�ַ */
        BASIC_COMMAND_DEVICE_UPGRADE_APP = 0xe6,            /* ����Ӧ�ô����� */
        BASIC_COMMAND_DEVICE_CONT_TRANS_ADDR = 0xe7,        /* �ϵ��������� */
        BASIC_COMMAND_DEVICE_UPGRADE_QUIT = 0xe8            /* �����˳� */
    }BasicCommand_FrameNet;
    typedef enum
    {
        FRAMT_RADIO_ADDR    = 0xffff,                       /* �㲥��ַ */
        MAX_RECEIVE_DEVICE = 0x02,                          /* ���������ɵ��豸ͨ����,MAX_RECEIVE_DEVICE����HID,MAX_RECEIVE_DEVICE + 1���ڴ������� */
        MAX_RECEIVE_DEVICE_ADDR = MAX_RECEIVE_DEVICE << 1,  /* ��ַ�б���ַ���� */
        HID_RECEVIE_INX = 0,
        WIFI_RECEVIE_INX = 1,
        USART_RECEVIE_INX = MAX_RECEIVE_DEVICE + 1,
        SYSETME_DEVICE_NUMBER = 0,                          /* ϵͳ��ȥ����CANͨѶ������ͨѶ�豸���� */
        FRAME_RECEIVE_BUF_MAX    = 0x200,                   /* Э������ջ������ռ��С */
        FRAME_SEND_BUF_MAX = 0x0c0,                         /* Э������ͻ�������С */

        FRAMEFRAME_CONTROL_HEAD = 0x55aa,
        FRAME_FRAMEHEAD_SIZE = 0x02,
        FRAME_CONTWORD_SIZE = 0x03,
        FRAM_PASSWORD_SIZE = 0x08,                          /* ���볤�� */

        FRAME_HEAD_SIZE = FRAME_FRAMEHEAD_SIZE + FRAME_CONTWORD_SIZE,
        FRAM_CAN_SEND_MAX = 0x08,                           /* CAN���һ֡���ݵĳ��� */
        FRAM_HID_SEND_MAX = 0x40,                           /* HID �����һ֡���ݵĳ��� */
        FRAM_WIFI_SEND_MAX = 0x40,                          /* WIFI�ܴ�������һ֡���� */
        FRAME_ADDR_LENGTH = 0x01,                           /* ��ַ���� */
        FRAME_DIVER_TYPE_HID = 0x50,                        /* �豸������HID */
        FRAME_DIVER_TYPE_CAN = 0x53,                        /* �豸������CAN */
        FRAME_DIVER_TYPE_USART = 0x59,                      /* �豸������USART */

        FRAME_NODE_TYPE_ROUTE = 0xc5,                       /* �ڵ�������·�ɽڵ� */
        FRAME_NODE_TYPE_ENDPOINT = 0xb7,                    /* �ڵ������Ƕ˵� */

        FRAME_NODE_ADDR_LENGTH = 0x02,                      /* �ڵ��ַ���� */
    }ProtocolStack_Enum;

    typedef enum
    {
        UPCODE_STATUS_OK = 0,                   /* ����OK */
        UPCODE_STATUS_ERR = 0x51,               /* ͨѶЭ�����ݰ�����(ͷ\����\��ַ\����......)*/
        UPCODE_STATUS_VER_ERR = 0x52,           /* ͨѶЭ�����ݰ�У����� */
        UPCODE_STATUS_CRC_ERR = 0x53,           /* CRC ����*/
        UPCODE_STATUS_DEVICE_BUSY = 0x55,       /* �豸æ */
        UPCODE_STATUS_CMMD_ERR = 0xa5,          /* ������� */

        UPCODE_STATUS_PAK_ERR = 0x54,           /* ���ݰ��������� */
        UPCODE_STATUS_ERASE_ERR = 0x55,         /* FLASH �������� */
        UPCODE_STATUS_PROGRAM_ERR = 0x56,       /* FLASH ��̴��� */
        UPCODE_STATUS_ADDR_ERR = 0x57,          /* ����FLASH��ַ���� */
        UPCODE_STATUS_DIVERADDR_ERR = 0x58,     /* �����豸ͨѶ��ַ����*/

        UPCODE_QUIT_OK = 0x00,                  /* ���������˳� */
        UPCODE_QUIT_ERR = 0x61,                 /* ���������˳� */
        UPCODE_QUIT_NO_UPCODE = 0x62,           /* û�����κδ������� */
        UPCODE_QUIT_FIRST_UPCODE = 0x82         /* ����ģ���һ�����д��� */


    }UPCDE_ERR;
    //typedef enum
    //{

    #ifdef  __SYSTEM_BOOT__
        #define SYSTEM_NVIC_BOOT_ADDR                   ((unsigned long int)0x08000000)
        #define SYSTEM_NVIC_APP_ADDR                    ((unsigned long int)0x08011800)
    #else
        #define SYSTEM_NVIC_APP_ADDR                    ((unsigned long int)0x08000000)
    #endif

        #define UPCODE_BACKUP_BLOCK_START_ADDR  0x08008000   /* ���ݿ����ʼ��ַ */
        #define UPCODE_BACKUP_BLOCK_END_ADDR  0x08011800     /* ���ݿ�Ľ�����ַ */
        #define UPCODE_SYSTEM_INVC_START_ADDR  0x08011800    /* �ж�������ʼ��ַ */
        #define UPCODE_SYSTEM_INVC_END_ADDR  0x08012000      /* �ж������Ľ�����ַ */
        #define UPCODE_SYSTEM_APP_START_ADDR  0x08012000     /* Ӧ�ó������ʼ��ַ */
        #define UPCODE_SYSTEM_APP_END_ADDR  0x0801f000       /* Ӧ�ó���Ľ�����ַ*/
        #define UPCODE_SYSTEM_PRODUCT_START_ADDR  0x0801f800 /* ��Ʒ�ı��ݵ�ַ */
        #define UPCODE_SYSTEM_EDITION_START_ADDR  0x0801f900 /* �汾�ı��ݵ�ַ */
        #define UPCODE_SYSTEM_DATA_START_ADDR  0x0801fa00    /* �汾�ı��ݵ�ַ */
        #define UPCODE_FLASH_PAGE_SIZE_2K  0x0800            /* оƬ��ҳ�ߴ� */
        #define UPCODE_FLASH_PAGE_SIZE_1K  0x0400            /* оƬ��ҳ�ߴ� */
        #define UPCODE_FLASH_PAGE_INFO_1K  0x01              /* оƬҳ�ߴ�1K */
        #define UPCODE_FLASH_PAGE_INFO_2K  0x02              /* оƬҳ�ߴ�2K */
        #define UPCODE_FLASH_PROODUCT_LENTH  0x20            /* ��Ʒ�ַ����� */

        #define UPCODE_EEPROM_HARDWARE_ADDR 0x0a0            /* IIC��Ӳ����ַ */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR0 0x00       /* ��������״̬���׵�ַ */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR1 0x01       /* ��������״̬���׵�ַ */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR2 0x02       /* ��������״̬���׵�ַ */
        #define UPCODE_EEPROM_RUNCODE_FIRST_ADDR3 0x03       /* ��������״̬���׵�ַ */
        #define UPCODE_EEPROM_BAKPROGRAM_STATE_ADD0 0x04     /* ��������״̬���׵�ַ */
        #define UPCODE_EEPROM_BAKPROGRAM_STATE_ADD1 0x05     /* ��������״̬���׵�ַ */
        #define UPCODE_EEPROM_CAN_ID_ADDR0        0x06       /* ���õ�CANͨѶID��ַ�ߵ�ַ */
        #define UPCODE_EEPROM_CAN_ID_ADDR1        0x07       /* ���õ�CANͨѶID��ַ�͵�ַ */

        #define UPCODE_BAKPROGRAM_STATE_OK  0x85a5           /* �������򱸷�OK,����ʹ�ñ����� */
        #define UPCODE_BAKPROGRAM_STATE_ERR 0xfa5a           /* �������򱸷�ERR,����ʹ�ñ����� */

        #define UPCODE_SYTEM_STATE_FLASH_INX   0x08          /* ϵͳ����״̬���ݵĴ洢λ�� */
        #define UPCODE_INT_ADDR_STATE_INX  0x09              /* ϵͳ���ڴ���жϱ�̵�ַ��״̬ */
        #define UPCODE_INT_ADDR_INX  0x0a                    /* ϵͳ���ڴ���жϱ�̵ĵ�ֵַ */
        #define UPCODE_SYSTEM_EEROM_FIRST_RUN0  0xffffffff   /* EPROM��һ�β��� */
        #define UPCODE_SYSTEM_EEROM_FIRST_RUN1  0x00000000   /* EPROM��һ�β��� */
        #define UPCODE_SYSTEM_FIRST_RUN  0xee6633aa          /* ϵͳ�״����� */
        #define UPCODE_SYSTEM_STATE_NORMAL  0xddaacc55       /* ϵͳ������������״̬ */
        #define UPCODE_SYSTEM_STATE_UPGRADE  0x5a66a522      /* ϵͳ��������״̬ */
        #define UPCODE_SYSTEM_STATE_WRITE_CODE  0x85ef89b5   /* ϵͳ��������״̬��д����״̬ */
        #define UUCODE_INT_ADDR_STATE_NORMAL  0x55ccaadd     /* ϵͳ������������״̬ */
        #define UPCODE_INT_ADDR_STATE_ADDR  0xEFFEA55A       /* ϵͳ���ڱ���ж�,��ַ�Ĵ����д�ŵ����жϵ�ַ */
        #define UPCODE_SYSTEM_UPGRADE_ERR  0x99775aa5        /* �������� */

        #define UPCODE_WAITING_TIME  0x168                   /* ��������ģʽ��,UPCODE_WAITING_TIME��ô����,�����û�п�ʼ����,���˳�����״̬������������ģʽ */
        #define UPCODE_ERR_TIME  0x258                       /* ���������������������ߴ���,�ȴ�10���Ӻ��˳� */
        #define UPCODE_REPEATS_VALUE  0x0a                   /* �������ظ�������� */

        #define FLASH_WRITE_DATA_LENTH  0x0c
        #define FLASH_WRITE_INX_VAR  0x0b
        #define FLASH_WRITE_FLAG_VAR  0x5a5aa5a5

    //}UpCode_System;

/* ����Ϊ�����Ʒ��Э�� */
    typedef enum
    {
        TP_PEDAL_PVID_CODE = 0x20,                           /* ̤������ID */
        CONTROL_PEADL_PVID_CODE = 0x30,                      /* ��̨������ID */
        IO_PEDAL_PVID_CODE = 0x40,                           /* IO������ID */
        RADIO_PVID_CODE = 0xff,                              /* ����Ĺ㲥ID */
    }SYSTEM_HARDWARE_PVID_ENUM;
    typedef enum 
    {
        DONCE_STATUS_KEY = 0xe0,                            /* ��Ϸ״̬ */
        PC_GET_RESOURCE_PUBLIC_KEY = 0xea,                  /* PC��ȡ��Դ��Կ */
    }SYSTEM_COMMD_ENUM;
    typedef enum
    {
        PEDAL_DEIVER_CODE_RIGHT_UP = 0x02005,
        PEDAL_DEIVER_CODE_LEFT_UP = 0x02001,
        PEDAL_DEIVER_CODE_MIDDLE = 0x02003,
        PEDAL_DEIVER_CODE_RIGHT_DN = 0x02004,
        PEDAL_DEIVER_CODE_LEFT_DN = 0x02002,
    }Pedal_DeiverCode;
    
    #define KEY_PRESSTIME                   5                /*��������*/
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
            unsigned long int System_Init_Flag:1;                       /* ϵͳ��ʼ�� */
            unsigned long int ReceiverData_Pack_Ok:1;                   /* ���ݰ�׼���ñ�־ */
            unsigned long int SendData_DlayTime_Flag:1;                 /* �ӳ����ݷ��ͱ�־ */
            unsigned long int UartStart_SendData_Flag:1;                /* USART��ʼ�������ݱ�־ */
            unsigned long int System_Verification_OK:1;                 /* ��֤ͨ����־ */
            unsigned long int HID_Init_OK_Flag:1;                       /* HID ��ʼ����� */
            unsigned long int PassWord_Settings_Flag:1;                 /* ���뱻���õı�־λ */
            unsigned long int System_Blue_Receive_OK_Flag:1;            /* ������������OK��־ */
            unsigned long int System_Blue_Commd_OK_Flag:1;              /* �����������OK��־ */
					  unsigned long int Pack_Received:1;
        }Bit;

        unsigned char Music_Vol;                                        /* ϵͳ�������� */
        unsigned char Phone_Vol;                                        /* ϵͳ�������� */
        unsigned char Diver_NodeType;                                   /* �豸���� */
        unsigned char Password_Val[FRAM_PASSWORD_SIZE];                 /* �������Ļ����� */
        unsigned short int Destination_CanAddr;                         /* Ŀ�����ַ */
        unsigned short int Local_CanAddr;                               /* ����Can��ַ������ */
        unsigned short int PowerTime;                                   /* ��ʱ������ʱ�� */
        unsigned short int Frame_OverTime;                              /* ����ϵͳЭ��֡��ʱ���� */
        unsigned short int System_WorkMode_Code;                        /* ϵͳ����״̬�� */
        unsigned short int TransmitterAddr_List[MAX_RECEIVE_DEVICE + 1];/* ��̬�豸��ַ�б�,�׵�ַ��ŵ���һ���ж����豸���ڵ��豸��,�����豸�б�����ŵ�EPROM�� */
        unsigned long int DiverFrame_Receive_OK;                        /* ��������OK�ı�־ ���֧��32���豸 */
        unsigned long int DiverFrame_Receive_Error;                     /* �������մ���ı�־ ���֧��32���豸 */
        unsigned long int StackCommand_Flag;
        unsigned long int FrameCommand_Flag;
        unsigned long int DelayTime;
				unsigned long int LED1_TimeCount;
    }System_Struct;

    typedef struct
    {
        struct
        {
            unsigned long int System_Boot_1msFlag_On:1;         /* ������������ĺ��ĳ��� */
            unsigned long int System_Boot_Int_Event_Flag_On:1;
            unsigned long int System_Boot_Imd_Event_Flag_On:1;
            unsigned long int SendData_Boot_DlayTime_Flag:1;    /* �ӳ����ݷ��ͱ�־ */
            unsigned long int HID_Init_OK_Boot_Flag:1;          /* HID ��ʼ����� */
            unsigned long int IIC_Error_Boot_Flag:1;
            unsigned long int Up_StartUp_Flag_On:1;
            unsigned long int Up_Over_Flag_On:1;
            unsigned long int Up_Error_Flag_On:1;
            unsigned long int Up_OK_Flag_On:1;
            unsigned long int Up_Moede_On:1;
            unsigned long int Up_DlayTime_Flag_On:1;
            unsigned long int Up_Online_OK_Flag:1;
            unsigned long int Up_Continue_Trans_Flag:1;         /* �ж�������־ */
            unsigned long int Up_StartTrans_IntVecCode_Flag:1;  /* ��ʼ������� */
            unsigned long int Up_StartTrans_AppCode_Flag:1;     /* ��ʼ������� */
        }Bit;
        unsigned long int DiverFrame_Boot_Receive_OK;           /* ��������OK�ı�־ ���֧��32���豸 */
        unsigned long int DiverFrame_Boot_Receive_Error;        /* �������մ���ı�־ ���֧��32���豸 */
        unsigned long int StackCommand_Boot_Flag;
        unsigned long int FrameCommand_Boot_Flag;
        unsigned long int System_RunningState_Code;             /* ����״̬�Ĵ��� */
        unsigned long int UpGram_Addr;                          /* ��̵�ַ */
        unsigned long int UpGram_ContTrans_Addr;                /* ������ַ */
        unsigned long int UpGram_Code_Lenth;                    /* �·��Ĵ��볤�� */
        unsigned long int TimeVal;
        unsigned short int Frame_Boot_OverTime;
        unsigned short int Packet_No;
        unsigned short int Packet_No_Bak;
        unsigned short int MaxPacket_No;
        unsigned short int Packet_CRC;
        unsigned short int Local_CanAddr;                       /* ����Can��ַ������ */
        unsigned char Diver_NodeType;                           /* �豸���� */
        unsigned char DelayTime;                                /* ����HID���������ӳ� */
        unsigned char Packet_Length;
        unsigned char UpGram_Err_Count;                         /* ����������� */
        unsigned char SendBuf[FRAME_SEND_BUF_MAX];
    }Upgram_Struct;




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
  uint8_t Current_Configuration;   //Selected configuration  //CONFIGURATION����ôȡֵ�ģ�����ʲô���壿
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

static void DataStageOut(void);
static void DataStageIn(void);
static void NoData_Setup0(void);
static void Data_Setup0(void);
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
void Set_System(void);
void Set_USBClock(void);
void GPIO_AINConfig(void);
//void TIM_Configuration(void);
//void NVIC_Configuration(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(unsigned char UsbModule);
void Get_SerialNum(void);

extern System_Struct System_Markf;
//------------------------------------------------------------------------------------------------------------------------------
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
#define CUSTOMHID_SIZ_REPORT_DESC                33	//ԭ���74
#define CUSTOMHID_SIZ_STRING_LANGID              4
#define CUSTOMHID_SIZ_STRING_VENDOR              40		//ԭ���36
#define CUSTOMHID_SIZ_STRING_PRODUCT             32		//ԭ���70
#define CUSTOMHID_SIZ_STRING_SERIAL              26		//ԭ���26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC];
extern const uint8_t CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC];
extern const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC];
extern const uint8_t CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID];
extern const uint8_t CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR];
extern const uint8_t CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT];
extern uint8_t CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL];
//------------------------------------------------------------------------------------------------------------------------------
//<usb_istr.h>
#if  !IsDensity(CL)
 void USB_Istr(void);
#else 
 UINT32 STM32_PCD_OTG_ISR_Handler(void);
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
void USB_WaitSend(void);//�ȴ�������ϣ��ж�����ã�,��ʱ1��
void USB_SendString_HW(UINT8 *s,UINT16 Len);//���͵�Ӳ�����ж�����ã�
void USB_SendString(UINT8 *s,UINT16 Len);//���͵����У��ж�����ã�
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