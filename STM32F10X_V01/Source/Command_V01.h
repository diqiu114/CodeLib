//==============================================================================================================================
#ifndef Command_V01_H
#define Command_V01_H
//==============================================================================================================================
#define COM_HeadStr_LDY         "55AA0D0A"
#define COM_HeadFStr_LDY        "55AA"
#define COM_HeadStr_LS          "5AA50D0A"
#define COM_HeadFStr_LS         "5AA5"
#define COM_HeadStr_YY          "7F0A"
#define SIZE_COM_HeadF_LDY      0x02
#define SIZE_COM_HeadF_LS       0x02
//==============================================================================================================================
#define PortType_485            0x00
#define PortType_UART           0x01
#define PortType_232            PortType_UART
#define PortType_SCI            PortType_UART
#define PortType_COM            PortType_UART
#define PortType_LPT            0x02
#define PortType_SPI            0x03
#define PortType_I2S            0x04
#define PortType_CAN            0x05
#define PortType_IIC            0x06
#define PortType_I2C            PortType_IIC
#define PortType_FIR            0x07
#define PortType_RF             0x08
#define PortType_USB            0x09
#define PortType_BLE            0x0a
#define PortType_WIFI           0x0b
#define PortType_LAN            0x0c
#define PortType_OPTIC          0x0d
//==============================================================================================================================
#define COM_Protocol_EMPTY      0
#define COM_Protocol_LDY_V1     1
#define COM_Protocol_LDY_V2     2
#define COM_Protocol_LDY_V3     3
#define COM_Protocol_SIM_4G     0x08
#define COM_Protocol_DMX512     0x10
#define COM_Protocol_YY_NRF     0x11
#define COM_Protocol_YY_BLT     0x12
#define COM_Protocol_LS_V1      0x20
#define COM_Protocol_LS_V2      0x21
#define COM_Protocol_Count      10
//==============================================================================================================================
#define COM_OB_PC               0
#define COM_OB_RF               1
#define COM_OB_BT               2
//==============================================================================================================================
//Ldy_V2
#define Control_W               0
#define Control_R               1
#define Control_WR              2
#define Control_RW              3
#define Control_ReadWrite       Control_RW
#define Control_BG              0x04
#define Control_BackGo          Control_BG
#define Control_SF              0x08
#define Control_ShortFrame      Control_SF
#define Control_PW              0x10//translate password
#define Control_Password        Control_PW
#define Control_AD              0x20
#define Control_Address         Control_AD//Address
#define Control_AP              0x40
#define Control_AppPort         Control_AP//AppPort,��λ1ʱ������ǰ�����ֽ���APP�˿ڣ�Ӧ���ڶ�����ϵͳ����������Ҫ
#define Control_BC              0x80
#define Control_Broadcast       Control_BC//broadcast
//-----------------------------------------------------------------------------------------------------------------------------
//Common Command
#define Command_HS                      0x00//HandShake(һ������,��������,������'_'���ٴ�����)

#define Command_DP                      0x01 //Device Property (һ������)
#define Command_DP_STR                    0x00 //Device string descryption(��������),�����豸���ٰ�װ
#define Command_DP_ST                     0x01 //Device State
#define Command_DP_ID                     0x02 //DCCL,DCSN,DCCP,DCID,CPUCP,CPUID
#define Command_DP_CP                     0x03 //Device CompanyName
#define Command_DP_NV                     0x04 //Device NameVer
#define Command_DP_NSN                    0x05 //Device Net SN
#define Command_DP_BATPercent             0x06 //Device percent of Batery energy,Parameters=2bytes(ֻ��)���豸��ص����ٷֱȣ���ֵ/100��ʾ�ٷ�����
#define Command_DP_Temprature             0x07 //Device Temprature(ֻ��), Parameters=2bytes, �豸�¶�(0.01�ȸ���)
#define Command_DP_FrameSize              0x08 //Comm frame buf size(ֻ��),Parameters=rbuf(2bytes)+tbuf(2bytes)
#define Command_DP_POS                    0x09 //Device Position
#define Command_DP_POS_Made                 0x00 //Device Made Position
#define Command_DP_POS_Run                  0x01 //Device Run Position
#define Command_DP_PW                     0x0A //Device Password
#define Command_DP_PW_CTL                   0x00 //Control
#define Command_DP_PW_TRS                   0x01 //Transmit

#define Command_DP_DT                     0x0B //Device DateTime
#define Command_DP_DT_BDT                   0x00 //Device Base DateTime����׼ʱ��
#define Command_DP_DT_MDT                   0x01 //Device Made DateTime������ʱ��
#define Command_DP_DT_CDT                   0x02 //Device Current DateTime����ǰʱ��

#define Command_DP_HW                     0x0C //Device Setup(RW),�豸����
#define Command_DP_HW_G0                    0x00//Ӳ������0,
#define Command_DP_HW_G1                    0x01//Ӳ������1,
#define Command_DP_HW_G2                    0x02//Ӳ������2,

#define Command_DP_BUS                    0x0D//����
#define Command_DP_BUS_ClrJoin              0x00//���������
#define Command_DP_BUS_SetJoin              0x01//���ü�����
#define Command_DP_BUS_ClrRel               0x02//������߹���(���) 
#define Command_DP_BUS_SetRel               0x03//�������߹���(��)          
#define Command_DP_BUS_GetFree              0x04//��ѯ,��ȡ�����ϵ������豸,���豸����ӳٷ���(����ע��ȫƵ��ɨ��)

#define Command_DP_AT                     0x0E //Device Action
#define Command_DP_AT_PW                    0x00//���������ȹػ�
#define Command_DP_AT_PW_Off                  0x00
#define Command_DP_AT_PW_On                   0x01
#define Command_DP_AT_Reset                 0x01//Device Reset

#define Command_DP_APP                    0x0F//App
#define Command_DP_APP_List                 0x00//All App in the device
#define Command_DP_APP_SetIndex             0x01//������APP���(2byte)

#define Command_DP_String               Command_DP_STR
#define Command_DP_State                Command_DP_ST
#define Command_DP_Company              Command_DP_CP
#define Command_DP_CompanyName          Command_DP_CP
#define Command_DP_NameVer              Command_DP_NV
#define Command_DP_NetSN                Command_DP_NSN
#define Command_DP_DT_BaseDateTime      Command_DP_DT_BDT
#define Command_DP_DT_MadeDateTime      Command_DP_DT_MDT
#define Command_DP_DT_CurrentDateTime   Command_DP_DT_CDT

#define Command_UG                      0x02//Device UpGrade(һ������)
#define Command_UG_EAD                    0x00  //Ҫд��ĳ���Ľ�����ַ
#define Command_UG_WAD                    0x01  //���д��ĳ���Ĵ����ַ
#define Command_UG_GAD                    0x02  //���������ṩ����ʼ��ַ������
#define Command_UG_RAD                    0x03  //��������ĸ�λ��ַ
#define Command_UG_ER                     0x04  //���������������
#define Command_UG_CD                     0x05  //���������д����

#define Command_UpGrade                 Command_UG
#define Command_UG_EndAddress           Command_UG_EAD
#define Command_UG_WritedAddress        Command_UG_WAD
#define Command_UG_UpGradeAddress       Command_UG_GAD
#define Command_UG_ResetAddress         Command_UG_RAD
#define Command_UG_Erase                Command_UG_ER
#define Command_UG_Code                 Command_UG_CD

#define Command_DISK                    0x03//���̲���
#define Command_DISK_FileList             0x00//�ļ��嵥(��)��������ɸѡ(�� *.*,*.WAVE)
#define Command_DISK_FileDelete           0x01//ɾ���ļ�,Parameter=FileName1(0x00��β)+FileName2+...
#define Command_DISK_FileOpen             0x02//�ļ���(д),Parameters=Flag+FileFlag(1bytes)+FileName
#define Command_DISK_FileOpen_Common        0x00//��ͨ�ļ�
#define Command_DISK_FileOpen_Current       0x01//��ǰ�ļ�,дʱ���������DT(4)+DID(4)+UserID(12)
#define Command_DISK_FileData             0x03//�ļ�����,Parameters����=Flag+(Pos,Len)��д=Flag+(Pos)+Data
#define Command_DISK_FileData_Common        0x00//��ͨ�ļ�,
#define Command_DISK_FileData_Current       0x01//��ǰ�ļ�
#define Command_DISK_FileClose            0x04
#define Command_DISK_FileClose_Common       0x00
#define Command_DISK_FileClose_Current      0x01
#define Command_DISK_FreeSize             0x05//ֻ��,���ش���ʣ��ռ䣬8�ֽڡ�
#define Command_DISK_Format               0x06//���̸�ʽ��

#define File_OpenError_IDExistCurrent   1
#define File_OpenError_NOADS            2
#define File_OpenError_NOSD             3
#define File_OpenError_DiskError        4
#define File_OpenError_IDExist          5 
//FileFlag
#define	FileFlag_READ				            0x01
#define	FileFlag_WRITE			            0x02
#define	FileFlag_OPEN_EXISTING	        0x00
#define	FileFlag_CREATE_NEW		          0x04
#define	FileFlag_CREATE_ALWAYS	        0x08
#define	FileFlag_OPEN_ALWAYS	          0x10
#define	FileFlag_OPEN_APPEND	          0x30

#define Command_KEY                     0x04 //����,R/W=KeyLen+Vale1(4bytes)+Value2(4bytes)+...

//APP(Command_ADC����Command_RP��д�Ĳ������ǵ�ǰ�ļ����������б�,(Pos,Len),Pos��Len����4�ֽ�)
#define Command_ADC                     0x05
#define Command_ADC_CH                    0x00
#define Command_ADC_Head                  0x01
#define Command_ADC_Data                  0x02
//-----------------------------------------------------------------------------------------------------------------------------
#define Command_LP                      0x10
#define Command_TC                      0x11
#define Command_Color                   0x12
#define Command_Color_Current             0x00
#define Command_Color_Struct              0x01
#define Command_ColorSport              0x13
#define Command_Addr                    0x14
#define Command_Addr_DMX                  0x00//DMX512��ַ(2bytes)
#define Command_Addr_CTL                  0x01//��������ַͨ��(2 bytes)
#define Command_Addr_FCH                  0x02//Ƶ����(2bytes)
//==============================================================================================================================
#endif
//==============================================================================================================================
