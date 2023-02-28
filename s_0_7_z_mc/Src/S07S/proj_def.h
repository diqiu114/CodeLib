#ifndef _PROJ_DEF_H_
#define _PROJ_DEF_H_

#if defined S07Y
#define USE_MVB        1
#define USE_ETH        1
#define USE_485        0
#define USE_W433       0
#define USE_WIFI_4G    0
#define USE_CELL       1
#define ACQ_RES        0
#define USE_MC_TEMP    0
#define USE_AFE_TEMP   1
#define USE_AFE_CONFIG 0
#define USE_USB_DEBUG  0

#define LOCAL_IP_1     10, 0, 1, 113
#define LOCAL_GATE_1   10, 0, 1, 1
#define LOCAL_MASK_1   255, 255, 192, 0

#define LOCAL_IP_2     10, 0, 5, 113
#define LOCAL_GATE_2   10, 0, 5, 1
#define LOCAL_MASK_2   255, 255, 192, 0

      
      
#elif defined S07S
#define USE_MVB  0
#define USE_ETH  1
#define USE_485  1
#define USE_W433 0
#define USE_WIFI_4G 0
#define USE_CELL 1
#define ACQ_RES  0
#define USE_MC_TEMP   0
#define USE_AFE_TEMP   1
#elif defined S07R
#define USE_MVB  0
#define USE_ETH  1
#define USE_485  1
#define USE_W433 0
#define USE_WIFI_4G 0
#define USE_CELL 1
#define ACQ_RES  0
#define USE_MC_TEMP   1
#define USE_AFE_TEMP  0
#if USE_ETH
#endif
#endif

// total battery adc channel and sample counts
#define TB_CH_CNT (3)
#define PT1000_CH_CNT (2)
#define TB_CH_SAMP_CNT (100)
#define PT1000_CH_SAMP_CNT (30)
#define AD_MAX (4096)
#define AD_REF_VOLT (3000)

#define CELL_CNT (2)
#define MAX_BAT_CNT_OF_PACK (4)
#define VOL_CH_OF_ONE_CELL  (11)
#define TEMP_CH_OF_ONE_CELL (6)
// count of master conrtoller per train
#if S07S
#define MC_CNT_PER_TRAIN (2)
#elif S07R
#define MC_CNT_PER_TRAIN (2)
#endif
// master controller adress detection
#define ADDR_SW_CNT (4)

#define CUR_CH_CNT (2)
#define VOLT_CH_CNT (1)

#define IP_ADDR_CNT (2)

#define HISTORY_DATA_STORE_CNT (60000)
#define ALARM_DATA_STORE_CNT   (20000)

#define FILE_DATA_VER (1)
#define ALARM_DEVICE_ID_CNT (2)

#define CELL_COMM_BUFF_SIZE (1100)
#define MVB_COMM_BUFF_SIZE (50)
#define MVB_REC_BUFF_SIZE (20)
#define ETH_COMM_BUFF_SIZE (1528)

// mvb increase vital data index
#define MVB_INC_OFFSET (0x12)
// mvb special data
#define MVB_SPECIAL_DATA (0xCE)
#define MVB_SEND_BUFF_SIZE (160)
#define ETH_SEND_BUFF_SIZE (160)

#define FNC265_NOMIAL_CAP (265)
#define FNC265_INIT_BUFF_SIZE (60)
#define FNC265_UPDATE_CLK (1000)

// SOC defines
#define NEW_MRX100_CAP  (float)(112.546)

// battery capacity estimate paramers
#define BATT_NOMIAN_CAP (100)
#define BATT_CUR_MAX (500.0f)
#define BATT_CUR_MIN (-500.0f)
#define BATT_CHARGE_CUR_THR (0.5)
#define BATT_DISCHARGE_CUR_THR (-0.5)
#define BATT_CAP_CALC_PERIOD_MS (1000)

// battery capacity initalize paramers
#define BATT_INIT_DATA_BUFFER_SIZE (60)
#define BATT_INIT_VOLT_UPPER_LIMIT (112)
#define BATT_INIT_VOLT_LOWER_LIMIT (80)
#define BATT_INIT_CUR_UPPER_LIMIT (-5)
#define BATT_INIT_CUR_LOWER_LIMIT (-100)
#define BATT_INIT_VOLT_DIFF (0.3f)
#define BATT_INIT_CUR_DIFF (1.0f)

// battery capacity initalize table paramers
#define BATT_INIT_TABLE_LINE_SIZE (96)
#define BATT_INIT_TABLE_ROW_SIZE (321)
#define BATT_INIT_TABLE_LINE_OFFSET (-5)
#define BATT_INIT_TABLE_ROW_OFFSET (800)
#define BATT_INIT_TABLE_LINE_RATE (1)
#define BATT_INIT_TABLE_ROW_RATE (10)
#define BATT_INIT_TABLE_VAL_RATE (600)
#define BATT_INIT_TABLE_LINE_ORDER ((bool)(false))

// battery capacity current table paramers
#define BATT_CUR_TABLE_LINE_SIZE (501)
#define BATT_CUR_TABLE_ROW_SIZE (1)
#define BATT_CUR_TABLE_LINE_OFFSET (0)
#define BATT_CUR_TABLE_ROW_OFFSET (0)
#define BATT_CUR_TABLE_LINE_RATE (1)
#define BATT_CUR_TABLE_ROW_RATE (1)
#define BATT_CUR_TABLE_VAL_RATE (100)

// battery capacity temperature compensation table paramers
#define BATT_TEMP_COMPENSATION_TABLE_LINE_SIZE ((unsigned int)(96))
#define BATT_TEMP_COMPENSATION_TABLE_ROW_SIZE ((unsigned int)(1))
#define BATT_TEMP_COMPENSATION_TABLE_LINE_OFFSET ((int)(-25))
#define BATT_TEMP_COMPENSATION_TABLE_ROW_OFFSET ((int)(1))

#define BATT_TEMP_COMPENSATION_TABLE_LINE_RATE ((float)(1.0f))
#define BATT_TEMP_COMPENSATION_TABLE_ROW_RATE ((float)(1.0f))
#define BATT_TEMP_COMPENSATION_TABLE_VAL_RATE ((float)(1.0f))
#define BATT_TEMP_COMPENSATION_TABLE_LINE_ORDER ((bool)(true))

// battery capacity adjustment params
#define BATT_ADJ_CAP_MIN (0)
#define BATT_ADJ_CAP_MAX (100)

// charge adjustment paramers
#define BATT_CHARGE_ADJ_VOLT (117.6f)
#define BATT_CHARGE_ADJ_CUR (1)
#define BATT_CHARGE_ADJ_TEMP (20)
#define BATT_CHARGE_ADJ_RATE (0.01f)
#define BATT_CHARGE_ADJ_TERMINAL (100)

#define BATT_CHARGE_ADJ_VOLT_CURVE_K (-0.2335f)
#define BATT_CHARGE_ADJ_VOLT_CURVE_B (122.18f)

// discharge adjustment paramers
#define BATT_DISCHARGE_ADJ_VOLT (80)
#define BATT_DISCHARGE_ADJ_CUR (1)
#define BATT_DISCHARGE_ADJ_TEMP (20)
#define BATT_DISCHARGE_ADJ_RATE (0.0001f)
#define BATT_DISCHARGE_ADJ_TERMINAL (0)
#define BATT_CHARGE_ADJ_TEMP_MIN (-30)
#define BATT_CHARGE_ADJ_TEMP_MAX (60)

// discharged capacity paramers
#define BATT_DISCHARGED_CAP_MIN (-126.0f)
#define BATT_CHARGE_EFFI (0.977413894753664f)

#define BATT_SELF_DISCHARGE_RATE_PER_MONTH (0.3)

#define ACQ_MAX_CNT  (25) 
#define ACQ_VOLT_CNT (12)
#define ACQ_TEMP_CNT (12)
#define ACQ_VOLT_OFFSET (0)
#define ACQ_TEMP_OFFSET (ACQ_VOLT_CNT)

#define CH_CALIB_CONFIG_CNT_PER (6)
#define CH_RATE_CONFIG_CNT_PER  (3)
#define COUNT_OF_TEMP            2

#define CMD_IDX 0
#define GET_ALL       0x74
#define GET_VOL_TEMP  0x75
#define GET_SOFT_VER  0x13
#define CALIB_MODE     0x80
#define CALIB_VOLT     0x81
#define CALIB_RES      0x82
#define CALIB_ADD_TEMP 0x83
#define CALIB_USE_LOWPWR  0x84
#define CALIB_NONUSE_LOWPWR  0x85
#define CALIB_LIMIT          0x86
#define CALIB_ID       0x88
#define CALIB_DEC_TEMP 0x93
#define CALIB_RESET    0x94
#define UPDATE         0x99
#define CALIB_CH_START 0xA0



#define REG_ADDR_CH_DROP_VALUE_START (0X00)
#define REG_ADDR_CH_VALUE_START (0X00 + ACQ_MAX_CNT)

// software and hardware version
#define REG_ADDR_SW_VER_X (0x60)
#define REG_ADDR_SW_VER_Y (0x61)
#define REG_ADDR_SW_VER_Z (0x62)
#define REG_ADDR_HW_VER_X (0x63)
#define REG_ADDR_HW_VER_Y (0x64)
#define REG_ADDR_HW_VER_Z (0x65)

// device config
#define REG_ADDR_DEV_ID (0x00)
#define REG_ADDR_DEV_BAUDRATE (0x01)
#define REG_ADDR_DEV_PERIOD (0x02)

#define REG_ADDR_RESTORE_CALIB_VAL (0x03)
#define REG_ADDR_PROGRAM_UPGRADE (0x04)

// cell data config
#define REG_ADDR_CH_ENABEL_START (0x30)
#define REG_ADDR_ACQ_MODE_START (0x31)
#define REG_ADDR_ACQ_TYPE_START (0x32)
#define REG_ADDR_CH_CALIB_SCALE_START (0x33)
#define REG_ADDR_CH_CALIB_K_VAL_START (0x34)
#define REG_ADDR_CH_CALIB_B_VAL_START (0x35)

#define CALDATA_OVER_FLAG_ADDR (0xC6)

#define REG_ADDR_CH_RATE_SCALE_START (0x100)
#define REG_ADDR_CH_RATE_K_VAL_START (0x101)
#define REG_ADDR_CH_RATE_B_VAL_START (0x102)

#define CALDATA_OVER_VAL (0x22)
#define MODBUS_RESTORE_CALIB_VAL (66)
#define MODBUS_PROGRAM_UPGRADE_VAL (88)

#if USE_485
#define MODBUS_MAX_DELAY         210
#elif USE_W433
#define MODBUS_MAX_DELAY         170
#endif
#endif
