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
#define Control_AppPort         Control_AP//AppPort,当位1时，参数前两个字节是APP端口，应用于多任务系统，单任务不需要
#define Control_BC              0x80
#define Control_Broadcast       Control_BC//broadcast
//-----------------------------------------------------------------------------------------------------------------------------
//Common Command
#define Command_HS                      0x00//HandShake(一级命令,其他类似,名字中'_'多少代表几级)

#define Command_DP                      0x01 //Device Property (一级命令)
#define Command_DP_STR                    0x00 //Device string descryption(二级命令),用于设备快速安装
#define Command_DP_ST                     0x01 //Device State
#define Command_DP_ID                     0x02 //DCCL,DCSN,DCCP,DCID,CPUCP,CPUID
#define Command_DP_CP                     0x03 //Device CompanyName
#define Command_DP_NV                     0x04 //Device NameVer
#define Command_DP_NSN                    0x05 //Device Net SN
#define Command_DP_BATPercent             0x06 //Device percent of Batery energy,Parameters=2bytes(只读)，设备电池电量百分比（数值/100表示百分数）
#define Command_DP_Temprature             0x07 //Device Temprature(只读), Parameters=2bytes, 设备温度(0.01度个数)
#define Command_DP_FrameSize              0x08 //Comm frame buf size(只读),Parameters=rbuf(2bytes)+tbuf(2bytes)
#define Command_DP_POS                    0x09 //Device Position
#define Command_DP_POS_Made                 0x00 //Device Made Position
#define Command_DP_POS_Run                  0x01 //Device Run Position
#define Command_DP_PW                     0x0A //Device Password
#define Command_DP_PW_CTL                   0x00 //Control
#define Command_DP_PW_TRS                   0x01 //Transmit

#define Command_DP_DT                     0x0B //Device DateTime
#define Command_DP_DT_BDT                   0x00 //Device Base DateTime，基准时间
#define Command_DP_DT_MDT                   0x01 //Device Made DateTime，出厂时间
#define Command_DP_DT_CDT                   0x02 //Device Current DateTime，当前时间

#define Command_DP_HW                     0x0C //Device Setup(RW),设备配置
#define Command_DP_HW_G0                    0x00//硬件参数0,
#define Command_DP_HW_G1                    0x01//硬件参数1,
#define Command_DP_HW_G2                    0x02//硬件参数2,

#define Command_DP_BUS                    0x0D//总线
#define Command_DP_BUS_ClrJoin              0x00//清除加入标记
#define Command_DP_BUS_SetJoin              0x01//设置加入标记
#define Command_DP_BUS_ClrRel               0x02//清除无线关联(解绑) 
#define Command_DP_BUS_SetRel               0x03//设置无线关联(绑定)          
#define Command_DP_BUS_GetFree              0x04//查询,获取总线上的自由设备,子设备随机延迟返回(无线注意全频道扫描)

#define Command_DP_AT                     0x0E //Device Action
#define Command_DP_AT_PW                    0x00//热启动与热关机
#define Command_DP_AT_PW_Off                  0x00
#define Command_DP_AT_PW_On                   0x01
#define Command_DP_AT_Reset                 0x01//Device Reset

#define Command_DP_APP                    0x0F//App
#define Command_DP_APP_List                 0x00//All App in the device
#define Command_DP_APP_SetIndex             0x01//参数是APP编号(2byte)

#define Command_DP_String               Command_DP_STR
#define Command_DP_State                Command_DP_ST
#define Command_DP_Company              Command_DP_CP
#define Command_DP_CompanyName          Command_DP_CP
#define Command_DP_NameVer              Command_DP_NV
#define Command_DP_NetSN                Command_DP_NSN
#define Command_DP_DT_BaseDateTime      Command_DP_DT_BDT
#define Command_DP_DT_MadeDateTime      Command_DP_DT_MDT
#define Command_DP_DT_CurrentDateTime   Command_DP_DT_CDT

#define Command_UG                      0x02//Device UpGrade(一级命令)
#define Command_UG_EAD                    0x00  //要写入的程序的结束地址
#define Command_UG_WAD                    0x01  //最后写入的程序的代码地址
#define Command_UG_GAD                    0x02  //升级程序提供的起始地址及长度
#define Command_UG_RAD                    0x03  //升级程序的复位地址
#define Command_UG_ER                     0x04  //升级程序擦除数据
#define Command_UG_CD                     0x05  //升级程序读写数据

#define Command_UpGrade                 Command_UG
#define Command_UG_EndAddress           Command_UG_EAD
#define Command_UG_WritedAddress        Command_UG_WAD
#define Command_UG_UpGradeAddress       Command_UG_GAD
#define Command_UG_ResetAddress         Command_UG_RAD
#define Command_UG_Erase                Command_UG_ER
#define Command_UG_Code                 Command_UG_CD

#define Command_DISK                    0x03//磁盘操作
#define Command_DISK_FileList             0x00//文件清单(读)，参数是筛选(如 *.*,*.WAVE)
#define Command_DISK_FileDelete           0x01//删除文件,Parameter=FileName1(0x00结尾)+FileName2+...
#define Command_DISK_FileOpen             0x02//文件打开(写),Parameters=Flag+FileFlag(1bytes)+FileName
#define Command_DISK_FileOpen_Common        0x00//普通文件
#define Command_DISK_FileOpen_Current       0x01//当前文件,写时后面参数是DT(4)+DID(4)+UserID(12)
#define Command_DISK_FileData             0x03//文件数据,Parameters：读=Flag+(Pos,Len)，写=Flag+(Pos)+Data
#define Command_DISK_FileData_Common        0x00//普通文件,
#define Command_DISK_FileData_Current       0x01//当前文件
#define Command_DISK_FileClose            0x04
#define Command_DISK_FileClose_Common       0x00
#define Command_DISK_FileClose_Current      0x01
#define Command_DISK_FreeSize             0x05//只读,返回磁盘剩余空间，8字节。
#define Command_DISK_Format               0x06//磁盘格式化

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

#define Command_KEY                     0x04 //按键,R/W=KeyLen+Vale1(4bytes)+Value2(4bytes)+...

//APP(Command_ADC读与Command_RP读写的参数都是当前文件补传数据列表,(Pos,Len),Pos与Len都是4字节)
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
#define Command_Addr_DMX                  0x00//DMX512地址(2bytes)
#define Command_Addr_CTL                  0x01//控制器地址通道(2 bytes)
#define Command_Addr_FCH                  0x02//频道号(2bytes)
//==============================================================================================================================
#endif
//==============================================================================================================================
