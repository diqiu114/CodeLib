#ifndef __DE_PROTOCOL_H_
#define __DE_PROTOCOL_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
#include <stdint.h>
#include "debug.h"


#define PROTOCOL_RX_MAX_SIZE          1024
#define PROTOCOL_COMMU_TIME_OUT       50
#define PROTOCOL_COMMU_RESP_TIME_OUT  1000


#define  SER_EOF           (1 << 7)
#define  SER_SOF           (1 << 6)
#define  SER_SINGLE        (SER_EOF | SER_SOF)

#define  CTRL_MustAck      (1 << 7)
     
#define  CTRL_Response     (1 << 6)
#define  CTRL_Request      (0 << 6)

#define  CTRL_WriteAck     (1 << 5)  
#define  CTRL_Encryption   (1 << 4)




typedef enum {
	TAG_NONE         = 0x00,
	TAG_Query        = 0x02,
	TAG_Control      = 0x03,
	TAG_Config       = 0x04,
	TAG_Status       = 0x05,
    TAG_Logger       = 0x06,
    TAG_Upgrade      = 0x0E,
    TAG_TransferData = 0x0F,
	
    
}TAG_t;

#define TAG_MASK_Query            (1 << TAG_Query)
#define TAG_MASK_Control          (1 << TAG_Control)
#define TAG_MASK_Config           (1 << TAG_Config)
#define TAG_MASK_Status           (1 << TAG_Status)
#define TAG_MASK_Logger           (1 << TAG_Logger)
#define TAG_MASK_Upgrade          (1 << TAG_Upgrade)
#define TAG_MASK_Transfer         (1 << TAG_TransferData)

typedef enum {

	QueryControl = 3,
	QueryConfig = 4,
	QueryStatus = 5,
}DataId_Query_t;

typedef enum {

	DataId_Upgrade_Header = 1,
	DataId_Upgrade_FileData,


}DataId_Upgrade_t;

typedef enum {
    DataId_Alarm_Header = 0,
    DataId_Alarm_Data,
    
    DataId_Hist_Header = 4,
    DataId_Hist_Data = 5,
    
    
    
    DataId_Reset = 100,
}DataId_Logger_t;


 typedef enum  { 
            
	DataId_SetId = 1,//设置编号
	DataId_TrainLine,//线路
	DataId_Cap,//额定容量（AH）
	DataId_Group,//采集器个数
	DataId_TotalVoltage,//电池组总电压
	DataId_MCVersion,//主控版本
	DataId_CellVersion,//采集器版本
	DataId_SocInitFlag,//SOC初始化标志
	DataId_Soc,//SOC容量值
	DataId_CellPackNumber,//采集器配置电池包个数
	DataId_CellTempNumber,//采集器配置温度组数
	DataId_MCSamplePeriod,//主控采集周期
	DataId_CellCommPeriod,//采集板通讯周期
	DataId_StorePeriod,//数据存储周期
    DataId_SoH,//SOH

	DataId_Fast2Float = 30,//快充转浮充阈值
	DataId_Float2Fast,//浮充转快充阈值
	DataId_Charge2DisCharge,//充电转放电阈值
	DataId_Discharge2Charge,//放电转充电阈值

	DataId_VolageAlarmConfig = 40,//总电压告警配置
	DataId_TempAlarmConfig,//温度告警配置
	DataId_ChargeCurrentAlarmConfig,//充电电流告警配置
	DataId_DischarageCurrentAlarmConfig,//放电电流告警配置
	DataId_SOCLowAlarmConfig,//SOC过低告警配置
	DataId_SOHLowAlarmConfig,//SOH过低告警配置
	DataId_CellVoltageAlarmConfig,//单体电压告警配置
	DataId_CellCommErrAlarmConfig,//单体通讯告警配置
    DataId_CellTempDiffConfig,
    
    
    DataId_CalibKBConfig = 60,//KB值校准
    DataId_CalibTime,//校准时间

}DATA_ID_Config_MC_t;


typedef enum {
    Result_OK = 0,
    Result_MsgErr,
    Result_NotSupport,
    Result_HandleFailed,
	Result_SerErr,
	Result_FileCheckErr,
	Result_FileTooLarge,
	Result_VersionErr,
	Result_WriteErr,
	Result_Busy,
}CodeResult_t;

typedef struct {
	uint8_t      DataId;
	CodeResult_t result;
	uint8_t      extLength;
	uint8_t      extData[4];
}HandleResult;





typedef struct {
	uint8_t  tag;
	uint8_t  lh;
	uint8_t  ll;
	uint8_t  *pv;
}tlv_t;



typedef struct {
	uint32_t rx_tick;
	uint16_t length;
	uint8_t  buffer[PROTOCOL_RX_MAX_SIZE];
}protocol_msg_t;

typedef struct {
	TAG_t       tag;
	uint8_t     ser;
	errStatus_t err;
	union {
		void     *p;
		uint32_t  v;
	}arg;
}ModuleRxMsg_t;

typedef struct {
    uint8_t *pdata;
    uint16_t length;
}ModuleTxMsg_t;

typedef struct {
    uint8_t logger_type;
    uint8_t alarm_type;
    uint8_t alarm_lvl;
    uint32_t logger_start_time;
    uint32_t logger_end_time;
}alarm_infor_t;


typedef struct {
    uint8_t  logger_type;
    uint8_t  para8_1;
    uint8_t  para8_2;
    uint8_t  para8_3;
 
    uint32_t para32_1;
    uint32_t para32_2;
    uint32_t para32_3;
}Logger_Msg_t;


uint16_t de_protocol_master_package(uint8_t       *p,
							         uint8_t        ctrl,
		                             uint8_t        src,
					                 uint8_t        dest,
					                 uint8_t        ser,
					                 uint32_t       tag_mask,
									 uint8_t        query_detail,
									 uint8_t       *p_content,
									 uint16_t       p_length,
						             HandleResult  *result,
						             uint8_t        resultcnt);

uint16_t de_protocol_slave_package_fill(uint8_t  *p,
							  uint8_t        ctrl,
		                      uint8_t        src,
					          uint8_t        dest,
					          uint8_t        ser,
					          uint16_t       tag_mask,
                              uint8_t        *pdata,
                              uint16_t       length);

void Bsp_Rs485SendBytes(uint8_t *pdata,uint16_t length);
void eth_sendbytes(uint8_t *pdata,uint16_t length);
//errStatus_t rs485_2_sendData(uint8_t *buffer, int bytes);
//#define protocol_send_bytes  Bsp_Rs485SendBytes
void protocol_send_bytes(COMM_TYPE_t type,uint8_t *pdata,uint16_t length);
#ifdef __cplusplus
}
#endif

#endif
