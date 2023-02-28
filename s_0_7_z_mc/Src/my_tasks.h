/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      FREE RTOS任务创建与执行
*
* 版本:
* V1.0 2018-12-11 初始版本程序编写 
***********************************************************/
#ifndef _MY_TASKS_H_
#define _MY_TASKS_H_


     
#include "proj_tasks.h"
#include "cmsis_os.h"

bool MT_create_tasks(void);
void fs_format(void);
     


#endif // _MY_TASKS_H_
