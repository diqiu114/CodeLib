/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      项目外围硬件初始化及任务创建与执行
*
* 版本:
* V1.0 2019-06-20 初始版本程序编写 
***********************************************************/
#ifndef _PROJ_TASKS_H_
#define _PROJ_TASKS_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
#include <stdint.h>
#include "debug.h"
     
bool Proj_task_create(void);
void Proj_hw_init(void);
void Proj_hw_config(void);
void Usb_connected_process(void);
void Usb_disconnected_process(void);
void eth_sendbytes(uint8_t *pdata,uint16_t length);
void bat_infor_print(COMM_TYPE_t commType);
void sys_infor_print(COMM_TYPE_t commType);
void cell_sendbytes(uint8_t *,uint16_t);
errStatus_t cell_data_update(uint8_t id,uint8_t *pdata,uint16_t length);
uint16_t fill_query_config(uint8_t *p);
uint16_t fill_query_status(uint8_t which_one,uint8_t *p);
errStatus_t de_protocol_handle_config(uint8_t *pdata,uint16_t length);
void CellTranferRequest(uint8_t *pMsg,uint16_t length);
uint16_t fill_query_logger_header(uint8_t which,uint8_t *p);
uint16_t fill_query_logger(uint8_t which,
                           uint8_t type,
                           uint8_t lvl,
                           uint32_t start_time,
                           uint32_t end_time,
                           uint8_t *p);
uint16_t get_alarm_his_data_one(uint8_t type,
                                uint8_t lvl,
                                uint32_t start_time,
                                uint32_t end_time,
                                uint32_t *offset,
                                uint16_t count,
                                uint8_t *p);
                                
uint16_t get_alarm_his_data_all(uint8_t type,
                                uint8_t lvl,
                                uint32_t start_time,
                                uint32_t end_time,
                                uint32_t *offset);
bool logger_set_ack(uint8_t msgId,uint8_t tag);
void System_SoftReset(void);

bool clear_history_data(void);
bool clear_alarm_data(void);



void paraNoInitSave(void);
bool paraNoInitReload(void);
#if(TASK_DEBUG)
extern TaskHandle_t Data_acq_handle;
extern TaskHandle_t Cell_comm_handle;
extern TaskHandle_t Mvb_init_handle;
extern TaskHandle_t Eth_init_handle;
extern TaskHandle_t Observer_process_handle;
#endif

#ifdef __cplusplus
}
#endif

#endif // _PROJ_TASKS_H_
