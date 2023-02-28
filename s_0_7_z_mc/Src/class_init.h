/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      类初始化
*
* 版本:
* V1.0 2018-11-06 
***********************************************************/

#ifndef _CLASS_INIT_H_
#define _CLASS_INIT_H_

#include <stdbool.h>
#include "defines.h"
#include "usb_device.h"
#include "eeprom_flag.h"
#include "comm/Double_buffered_comm.h"
#include "usb_comm.h"
#include "proj_class_init.h"


extern Usb_comm* Host_comm;
extern Eeprom_flag* Program_upgrade;
extern Eeprom_flag* Nand_format;
extern USBD_HandleTypeDef hUsbDeviceFS;

void usb_comm_callback(void);

bool Class_init(void);

#endif // _CLASS_INIT_H_
