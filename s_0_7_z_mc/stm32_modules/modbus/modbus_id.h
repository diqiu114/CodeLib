/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      modbus id 
*
* 版本:
* V1.0 2018-11-22 初始程序编写 
***********************************************************/

#include <stdint.h>

#ifndef _MODBUS_ID_H_
#define _MODBUS_ID_H_

#include "device_id.h"

#define DEFAULT_ID    ( 1 )
class Modbus_id : public Device_id
{
	public:
		Modbus_id();
		virtual bool set_id(char id);
		virtual char get_id(void);
		~Modbus_id();
	private:
		char modbus_id;
    	char get_id_from_eeprom(void);
};

#endif // _MODBUS_ID_H_
