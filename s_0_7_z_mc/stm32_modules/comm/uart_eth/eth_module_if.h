/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      以太网模块接口类

***********************************************************/

#ifndef _ETH_MODULEH_
#define _ETH_MODULEH_
#include ".\hw_interface\gpio\gpio_if.h"
#include "modules_def.h"
#include "eth_config_data.h"

class ETH_Module_if
{
public:
  virtual ~ETH_Module_if(){};
  virtual bool init() = 0;
  virtual bool send_data(unsigned char train_idx, unsigned char *send_buff, unsigned int send_len) = 0;
  virtual unsigned int recieve_data(unsigned char *data, unsigned int data_len = 0) = 0;
  virtual bool set_recv_queue(QueueHandle_t *recv_queue) = 0;
};

#endif //_ETH_MODULEH_
