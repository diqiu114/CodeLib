#include "proj_paras.h"

#if S07S
#define CONVERSION_VOLT_K     (0.065)
#elif S07R
#define CONVERSION_VOLT_K     (0.066667)
#endif

Sys_paras_t Sys_paras = {
    0,
    // battery infomation
		{
#if S07Y
     SHAOXING_2,       
#elif S07T
    SHENZHEN_16, 
#elif S07R
    CHANGSHA_6,
#elif S07S
    SHENZHEN_16,
#endif          
    100, CELL_CNT, 100},
  
    {
     //Master software ver
     1, 0, 
#if S07Y
      2,
#elif S07T
      0,      
#elif S07S
      3,
#elif S07R
      1,
#endif
     //Master hardware ver
     1, 0, 0,
     //Extern software vera
     1, 0, 0,
     // cell node software ver
     1, 0, 0,
     // cell node hardware ver
     1, 0, 0},
};

Dev_paras_t Dev_paras = {
#if USE_MVB
 {
   // device addr 
  0x31,
  // dest port count 
     
  0x01,
  // dest port 
  0x1, 0x8D, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0x1, 0xB7, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0x1, 0xB8, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0x1, 0xB9, MVB_MODULE_DATA_LEN_16BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
     
  0x0, 0x00, 0, 0,
  0x0, 0x00, 0, 0,
  0x0, 0x00, 0, 0,
  0x0, 0x00, 0, 0,

  // source port count
  0x01,
  // source port
  0x0, 0x01, MVB_MODULE_DATA_LEN_16BYTES, MVB_MODULE_PORT_PERIOD_16MS,
  0x0, 0x00, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_128MS,
  0x0, 0x00, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  
  //
  // device addr 
  0x41,
  // dest port count 
  
  0x01,
  // dest port 
  0x05, 0x8D, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0x05, 0xB7, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0x05, 0xB8, MVB_MODULE_DATA_LEN_32BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  0x05, 0xB9, MVB_MODULE_DATA_LEN_16BYTES, MVB_MODULE_PORT_PERIOD_1024MS,
  
  0x00, 0x00, 0, 0,
  0x00, 0x00, 0, 0,
  0x00, 0x00, 0, 0,
  0x00, 0x00, 0, 0,
  
  // source port count
  0x01,
  // source port
  0x0, 0x01, MVB_MODULE_DATA_LEN_16BYTES, MVB_MODULE_PORT_PERIOD_16MS,
  0x0, 0x00, 0, 0,
  0x0, 0x00, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
},
#endif

#if USE_ETH  
//#if USE_ETH_TRDP_DOUBLE
  {
    //第1车的以太网参数************************************************************************************/
    {
#if S07S   
      //重要过程数据主版本号
      1,
      //重要过程数据子版本号
      1,
      //协议版本
      0x0100,
      //发送消息数据帧回复超时时间（微秒）
      2000,
     //ETH0 参数
      //本地ip地址
      LOCAL_IP_1,
      //子网网关
      LOCAL_GATE_1,
      //子网掩码
      LOCAL_MASK_1,
      //TTDB 组播地址
      0, 0, 0, 0,
      //TTDB 组播端口
      0,
      //mac地址
      0x00, 0x00, 0x00, 0x00, 0x00,0x00,
      //DNS 地址
      0, 0, 0, 0,
      //DNS 端口
      0,
      //本机SMI
      0x00,
      //本机commid
      41055,
      //组播地址
      239, 255, 4,55,
      0, 0, 0, 0,
      //组播端口号
      17224, 0,
      //接收组播地址
      239, 255, 2, 1,
      //接收组播端口号
      17224,
      //自由单播地址
      10, 0, 1, 1,
      0, 0, 0, 0,
      //宿端口 
      17224, 0,
      // 源端口
      17224,0,
      //接收commid
      20000, 20001, 0, 0,
      //接收SMI
      0, 0, 0, 0, 0, 0,
      //编组唯一标识符
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
          
#elif S07R
      //重要过程数据主版本号
      1,
      //重要过程数据子版本号
      1,
      //协议版本
      0x0100,
      //发送消息数据帧回复超时时间（微秒）
      2000,
      //ETH0 参数
      //本地ip地址
      192,168,1,43,
      //子网网关
      192,168,1,2,
      //子网掩码
      255, 255, 0, 0,
      //TTDB 组播地址
      0, 0, 0, 0,
      //TTDB 组播端口
      0,
      //mac地址
      0x00, 0x00, 0x00, 0x00, 0x00,0x00,
      //DNS 地址
      0, 0, 0, 0,
      //DNS 端口
      0,
      //本机SMI
      0x00,
      //本机commid
      4001,
      //组播地址
      239,255,35,1,
      0, 0, 0, 0,
      //组播端口号
      17224, 0,
      //接收组播地址
      239, 255, 31, 1,
      //接收组播端口号
      17224,
      //自由单播地址
      192, 168, 1, 111,
      0, 0, 0, 0,
      //宿端口 
      17224, 0,
      // 源端口
      17224, 0,
      //接收commid
      1001, 0, 0, 0,
      //接收SMI
      0, 0, 0, 0, 0, 0,
      //编组唯一标识符
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
#endif
#if ETH_DOUBLE_MODULE    
     //ETH1 参数
      //本地ip地址
      10, 0, 1, 55,
      //子网网关
      10, 0, 1, 2,
      //子网掩码
      255, 255, 192, 0,
      //TTDB 组播地址
      0, 0, 0, 0,
      //TTDB 组播端口
      0,
      //mac地址
      0x00, 0x00, 0x00, 0x00, 0x00,0x00,
      //DNS 地址
      0, 0, 0, 0,
      //DNS 端口
      0,
      //本机SMI
      0x00,
      //本机commid
      31055,
      //组播地址
      239,255,3,55,
      0, 0, 0, 0,
      //组播端口号
      17224, 0,
      //接收组播地址
      239, 255, 1, 1,
      //接收组播端口号
      17224,
      //自由单播地址
      10, 0, 1, 1,
      0, 0, 0, 0,
      //宿端口 
      17224, 0,
      // 源端口
      17224, 0,
      //接收commid
      10000, 0, 0, 0,
      //接收SMI
      0, 0, 0, 0, 0, 0,
      //编组唯一标识符
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      
#endif
    },
    //第2车以太网的参**********************************************************************************/
    {
#if S07S
      //重要过程数据主版本号
      1,
      //重要过程数据子版本号
      1,
      //协议版本
      0x0100,
      //发送消息数据帧回复超时时间（微秒）
      2000,
      //ETH0 参数
      //本地ip地址
      LOCAL_IP_2,
      //子网网关
      LOCAL_GATE_2,
      //子网掩码
      LOCAL_MASK_2,
      //TTDB 组播地址
      0, 0, 0, 0,
      //TTDB 组播端口
      0,
      //mac地址
      0x00, 0x00, 0x00, 0x00, 0x00,0x00,
      //DNS 地址
      0, 0, 0, 0,
      //DNS 端口
      0,
      //本机SMI
      0x00,
      //本机commid
      46055,
      //组播地址
      239, 255, 4, 55,
      0, 0, 0, 0,
      //组播端口号
      17224, 0,
      //接收组播地址
      239, 255, 2, 1,
      //接收组播端口号
      17224,
      //自由单播地址
      10, 0, 6, 1,
      0, 0, 0, 0,
      //宿端口 
      17224, 0,
      // 源端口
      17224, 0,
      //接收commid
      20000, 20001, 0, 0,
      //接收SMI
      0, 0, 0, 0, 0, 0,
      //编组唯一标识符
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,     
       
#elif S07R
      //重要过程数据主版本号
      1,
      //重要过程数据子版本号
      1,
      //协议版本
      0x0100,
      //发送消息数据帧回复超时时间（微秒）
      2000,
      //ETH0 参数
      //本地ip地址
      192,168,6,43,
      //子网网关
      192,168,6,2,
      //子网掩码
      255, 255, 0, 0,
      //TTDB 组播地址
      0, 0, 0, 0,
      //TTDB 组播端口
      0,
      //mac地址
      0x00, 0x00, 0x00, 0x00, 0x00,0x00,
      //DNS 地址
      0, 0, 0, 0,
      //DNS 端口
      0,
      //本机SMI
      0x00,
      //本机commid
      4006,
      //组播地址
      239,255,35,6,
      0, 0, 0, 0,
      //组播端口号
      17224, 0,
      //接收组播地址
      239, 255, 31, 1,
      //接收组播端口号
      17224,
      //自由单播地址
      192, 168, 6, 111,
      0, 0, 0, 0,
      //宿端口 
      17224, 0,
      // 源端口
      17224, 0,
      //接收commid
      1001, 0, 0, 0,
      //接收SMI
      0, 0, 0, 0, 0, 0,
      //编组唯一标识符
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
#endif

#if ETH_DOUBLE_MODULE   
      //ETH1 参数
      //本地ip地址
      10, 0, 6, 55,
      //子网网关
      10, 0, 6, 2,
      //子网掩码
      255, 255, 192, 0,
      //TTDB 组播地址
      0, 0, 0, 0,
      //TTDB 组播端口
      0,
      //mac地址
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      //DNS 地址
      0, 0, 0, 0,
      //DNS 端口
      0,
      //本机SMI
      0x00,
      //本机commid
      36055,
      //组播地址
      239, 255, 3, 55,
      0, 0, 0, 0,
      //组播端口号
      17224, 0,
      //接收组播地址
      239, 255, 1, 1,
      //接收组播端口号
      17224,
      //自由单播地址
      10, 0, 6, 1,
      0, 0, 0, 0,
      //宿端口 
      17224, 0,
      // 源端口
      17224, 0,
      //接收commid
      10000, 0, 0, 0,
      //接收SMI
      0, 0, 0, 0, 0, 0,
      //编组唯一标识符
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

#endif
    }
  }, 
#endif    
  // soc init flg
  1,
  //soc  actual
	NEW_MRX100_CAP,
  // voltage and 2 current and 2 temp calib
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  // voltage and current rate
  CONVERSION_VOLT_K, 0, 
  0.4, -600, 
  0.4, -600,
  
  1038,727.9,0.1076,1.747,48.63,19.02,
  1038,727.9,0.1076,1.747,48.63,19.02,
#if S07S
  24,24
#elif S07R
  10, 0 
#endif
};

User_paras_t User_paras = {
#if S07Y
  // period in seconds
  1, 1, 300,//1, 300, 300,
  // battery status threshold
  5, 5, -2.5, 1,
#elif S07T
  //S07T采集板采样频率修改为5秒/次
  // period in seconds
  1, 5, 300,
  // battery status threshold
  5, 5, -1, 1,
#else
  // period in seconds
  1, 300, 300,
  // battery status threshold
  5, 5, -1, 1,
#endif

#if S07Y  //等待确认
  // battery alarm thress 
  134,138,      //  TOTAL_VOLT_HIGH
  86,80,        //  TOTAL_VOLT_LOW = 0,
  6,9,          //  TOTAL_VOLT_DEVIATE_HI,
  50,60,        //  TEMP_HIGH,
  43.5,48,      //  CHARGE_CUR_HIGH,
  143,160,      //  DISCHARGE_CUR_HIGH,
  20,10,        //  SOC_LOW,
  80,70,        //  SOH_LOW,
  7.2,8,        //  CELL_VOLT_HIGH,
  4,3.2,        //  CELL_VOLT_LOW,
  2.8,3.2,      //	CELL_VOLT_DIFF_HIGH,
  5,10,         //  CELL TEMP HIGH
  3,3,          //  CELL_COMM_ERROR,无用

  // battery alarm reset thress 告警撤销值
  132,        //  TOTAL_VOLT_HIGH
  90,         //  TOTAL_VOLT_LOW
  5,          //  TOTAL_VOLT_DEVIATE_HI,
  48,         //  TEMP_HIGH,
  32,         //  CHARGE_CUR_HIGH,
  130,        //  DISCHARGE_CUR_HIGH,
  20,         //  SOC_LOW,
  80,         //  SOH_LOW,
  7,          //  CELL_VOLT_HIGH,
  4.4,        //  CELL_VOLT_LOW,
  2.4,        //  CELL_VOLT_DIFF_HIGH,
  5,          //  CELL TEMP DIFF HIGH
  1,          //  CELL_COMM_ERROR,无用

#elif S07T
  // battery alarm thress 
  88,86,    //  TOTAL_VOLT_LOW = 0,
  3,5,      //  TOTAL_VOLT_DEVIATE_HI,
  55,60,    //  TEMP_HIGH,
  80,100,   //  CHARGE_CUR_HIGH,
  35,25,    //  SOC_LOW,
  80,70,    //  SOH_LOW,
  17.5,18,  //  CELL_VOLT_HIGH,
  10.5,10,  //  CELL_VOLT_LOW,
  0.5,0.75,//	CELL_VOLT_DIFF_HIGH,
  3,3,      //  CELL_COMM_ERROR,无用
  // battery alarm reset thress
  91,2.8,55,80,38,85,17.5,10,0.5,1, 
#elif S07S
	// battery alarm thress
	85,82,
    6,9,
    50,60,
    62,104,
    30,20,
    80,70,
    17.75,
    20,10,
    7,1.97,
    2.02,
    3,3,
	// battery alarm reset thress
	87,5,48,55,40,85,16,11.25,1.8,1,
#elif S07R
  // battery alarm thress
	3,5,85,82,50,60,47,54,172,180,69,62,14,15,8.5,8,1.97,2.02,3,3,
	// battery alarm reset thress
	3,88,50,39,162,69,12.8,8.8,1.97,1,
#endif
	// trigger delays in seconds
#if S07Y
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//900,900,
  300,300,//300,300,
#elif S07T 
  900,900,
  900,900,
  900,900,
  60,10,
  900,900,
  900,900,
  900,900,
  300,60,
  900,900,
  600,180,
 #else
  900,900,
  900,900,
  900,900,
  5400,5400,
  900,900,
  900,900,
  900,900,
  900,900,
  900,900,
  900,900,
 #endif  
    // reset delays in seconds
    60,
    60,
    60,
    60,
    60,
    60,
    60,
    60,
    60,
    60,
    60,
    60,
    60
};

const Cell_adc_config_paras_t  Cell_adc_config_paras[ACQ_MAX_CNT] = {

true,4,TYPE_VOLT,
true,4,TYPE_VOLT,
true,3,TYPE_VOLT,
true,3,TYPE_VOLT,
true,3,TYPE_VOLT,
true,4,TYPE_VOLT,
true,4,TYPE_VOLT,
true,3,TYPE_VOLT,
true,3,TYPE_VOLT,
true,3,TYPE_VOLT,
true,4,TYPE_VOLT,
true,4,TYPE_VOLT,
    
true,4,TYPE_TEMP,
true,4,TYPE_TEMP,
true,3,TYPE_TEMP,
true,3,TYPE_TEMP,
true,3,TYPE_TEMP,
true,4,TYPE_TEMP,
true,4,TYPE_TEMP,
true,3,TYPE_TEMP,
true,3,TYPE_TEMP,
true,3,TYPE_TEMP,
true,4,TYPE_TEMP,
true,4,TYPE_TEMP,
    
false,4,TYPE_VOLT
};

Batt_data_t Batt_data_buff = {0};
Cell_sample_data_t cell_data_adc_voltage[CELL_CNT];
Soh_record_t Soh_record = {0};

//Paras_NoInit_t paraNoInit __attribute__((zero_init));
//Paras_NoInit_t paraNoInit __attribute__((zero_init));
Paras_NoInit_t paraNoInit __attribute__((at(0x2002FC00))); 

