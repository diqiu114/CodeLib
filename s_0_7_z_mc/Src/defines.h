/*********************************************************** 
  * @copyright  (C) COPYRIGHT DANFINSWE
  * @author      DFS Technology Department
  *
  * @brief      configure project
  *
  *
  ***********************************************************/
#ifndef _DEFINES_H_
#define _DEFINES_H_

#define USE_IWDG      (1)
#define USE_FREE_RTOS (1)

#define DRIVER_NAME "NAND:"

#define PROGRAM_UPGRADE_ADDR (0x1111)
#define PROGRAM_UPGRADE_ADDR_CNT (1)
#define PROGRAM_UPGRADE_VAL (0xb255)
#define PROGRAM_NOT_UPGRADE_VAL (0x2222)


#define PROGRAM_UPGRADE_ADDR_1     (0x1200)
#define PROGRAM_UPGRADE_ADDR_CNT_1 (12)
#define PROGRAM_UPGRADE_VAL_1      (0xFFFF)
#define PROGRAM_NOT_UPGRADE_VAL_1  (0xFFFF)

#define NAND_FORMAT_ADDR (0x2222)
#define NAND_FORMAT_ADDR_ADDR_CNT (1)
#define NAND_FORMAT_ADDR_VAL (0xfe12)
#define NAND_FORMAT_ADDR_NOT_FORMAT_VAL (0x10ab)



#define SYS_PARA_FILE_NAME ("sys_paras.txt")
#define DEV_PARA_FILE_NAME ("dev_paras.txt")
#define USER_PARA_FILE_NAME ("user_paras.txt")
#define DISCHARGED_CAP_FILE_NAME ("dis_cap.txt")
#define SOH_RECORD_FILE_NAME     ("soh_record.txt")

#define AFE_CONFIG_PARAS_FILE_NAME ("afe_config_paras.txt")


#define HISTORY_DATA_FILE_NAME ( "his_data.txt")
#define ALARM_DATA_FILE_NAME ( "alm_data.txt")
#define RUNNING_LOG_FILE_NAME ( "log.txt")

#include "modules_def.h"
#include "proj_def.h"
#include "proj_eth_define.h"

#endif // _DEFINES_H_
