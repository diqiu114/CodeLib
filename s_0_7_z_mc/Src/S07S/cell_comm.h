/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      蓄电池采样板通讯类
*
* 版本:
* V1.0 2019-06-21 初始程序编写 
***********************************************************/

#ifndef _CELL_COMM_H_
#define _CELL_COMM_H_

#include <stdbool.h>
#include "rs485_with_protocol.h"
#include "defines.h"

#define CELL_DEFAULT_REV_DELAY (150)

typedef enum _tag_cell_cmd_
{
  // read software version
  CELL_READ_SOFT_VER = 0x13,

  // write/read kx+b calibration value
  CELL_WRITE_POLYNOMIAL_CALIB_VAL = 0x60,
  CELL_READ_POLYNOMIAL_CALIB_VAL,

  // read cell data
  CELL_READ_VOLT = 0x71,
  CELL_READ_RES,
  CELL_READ_TEMP,
  CELL_READ_ALL,
  CELL_READ_VOLT_AND_TEMP,
  // read cell data and calibration value
  CELL_READ_ALL_AND_CALIB_VAL = 0x80,

  // set calibration value
  CELL_CALIB_VOLT = 0x81,
  CELL_CALIB_RES,
  CELL_CALIB_TEMP,

  CELL_RESET_CALIB_VAL = 0x94,

  // modify cell ID
  CELL_MODIFY_ID = 0x88,

  // cell program upgrade
  CELL_PROGRAM_UPGRADE = 0x99

} Cell_cmd;

#define CELL_CMD_IDX (0)
#define CELL_ID_IDX (CELL_CMD_IDX + 1)
#define CELL_DATA_IDX (2)

class Cell_comm :public Rs485_with_protocol
{
public:
  Cell_comm(UART_HandleTypeDef* uart_handle, unsigned int buff_size,  Gpio_if *ctrl_pin,uart_idle_callback callback = NULL );
  void set_rev_timeout(unsigned int m_seconds);
  unsigned int get_rev_timeout(void);

  unsigned int read_sw(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int read_polynomial_val(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int read_volt(unsigned char cell_id, unsigned char *rev_buff);
  // unsigned int read_res(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int read_temp(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int read_volt_and_temp(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int read_all_data(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int read_all_and_calib(unsigned char cell_id, unsigned char *rev_buff);
  unsigned int write_polynomial_val(unsigned char cell_id, unsigned char *data_buff, unsigned data_len);
  unsigned int volt_calib(unsigned char cell_id, unsigned char *data_buff, unsigned data_len);
  // unsigned int res_calib(unsigned char cell_id, unsigned char *data_buff, unsigned data_len);
  unsigned int temp_calib(unsigned char cell_id, unsigned char *data_buff, unsigned data_len);
  unsigned int modify_id(unsigned char cell_id, unsigned char *data_buff, unsigned data_len);
  unsigned int reset_calib(unsigned char cell_id);
  unsigned int program_upgrade(unsigned char cell_id);
  unsigned int transparent(unsigned char* data, unsigned int data_len, bool resp = false, unsigned char* rev_buff = NULL);

#if (USE_FREE_RTOS)
  void set_queue_handle(QueueHandle_t handle);
#endif

  virtual ~Cell_comm();

private:
  Protocol *prot;
#if (USE_FREE_RTOS)
  QueueHandle_t rev_queue;
#endif
  unsigned int unpack_buff_data(Cell_cmd cmd, unsigned char cell_id, unsigned char *data);
  bool received_data(int timeout);
  unsigned int rev_delay;
  unsigned char *send_buff;
  unsigned int send_data_to_cell(Cell_cmd cmd, unsigned char id, unsigned char *data,
                                 unsigned int data_len, unsigned char *rev_data = NULL);
};

#endif // _CELL_COMM_H_
