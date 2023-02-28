/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-14
 * 
 * @brief SIM7600 AT指令驱动
 * datasheet：https://simcom.ee/documents/SIM7600C/SIM7500_SIM7600%20Series_AT%20Command%20Manual_V1.01.pdf 
 * 
 * ***********************************************************
 */

#ifndef _SIM7600_H_
#define _SIM7600_H_
#include <stdio.h>
#include "comm\AT_command\at_command.h"
#include "hw_interface\gpio\gpio_if.h"

#define SIM7600_POWER_UP_DELAY (20000)
#define SIM7600_COMM_BUFF_SIZE (50)
#define SIM7600_CID (1)
#define SIM7600_LINK_NUM (0)
#define SIM7600_SEND_TIMEOUT_MS (1000)
#define SIM7600_REV_TIMEOUT_MS (1000)
#define SIM7600_MANUAL_READ_PREFIX_DATA_LEN (40)

typedef enum _sim7600_register_status
{
  SIM_NOT_REGISTERED_NOT_SEARCHING,
  SIM_REGISTERED_HOME_NETWORK,
  SIM_NOT_REGISTERED_SEARCHING,
  SIM_REGISTRATION_DENIED,
  SIM_UNKOWN,
  SIM_REGISTERED_ROAMING
}Sim7600_reg_status;

typedef enum _sim7600_transmission_mode_
{
  SIM_COMMAND_MODE = 1,
  SIM_DATA_MODE = 2,
} Sim7600_transmission_mode;

typedef enum _sim7600_protocol_
{
  SIM_PROTOCOL_TCP = 1,
  SIM_PROTOCOL_UDP,
}Sim7600_protocol;

class Sim7600
{
public:
  Sim7600(At_command *_at_comm, Gpio_if* _power_pin, Gpio_if *_rst_pin = NULL, int command_buff_size = SIM7600_COMM_BUFF_SIZE);
  ~Sim7600();
  void power_up(void);
  bool reset(void);
  bool ready(void);
  bool sim_card_ready(void);

  Sim7600_reg_status register_status(void);
  bool registed(void);

  unsigned char signal_quality(void);
  bool signal_quality_ok(void);

  bool curr_operator(void);
  bool config_pdp_context(unsigned char _cid = SIM7600_CID, const char* pdp_type = "IP"); // AT+CGDCONT
  bool active_pdp_context(void);
  bool net_open(void);
  bool net_close(void);
  bool ip_addr(const char* ret_ip = NULL);
  int get_ntp_time(char *ret_str,  const char *ntp_server);  // 获取实时网络时间

  bool tcp_connect(const char *ip, unsigned short port, char _link_num = SIM7600_LINK_NUM);
  bool udp_connect(const char *ip, unsigned short port, unsigned short local_port = 0, char _link_num = SIM7600_LINK_NUM);
  bool tcp_udp_disconnect(void);

  bool get_data_manually(bool manu_ret = true);
  // bool enter_transparent_mode(void);
  // bool exit_transparent_mode(void);

  bool send(char *data, int data_len);
  bool read_buffer(char* data, int data_len = 0);
  bool read_buffer_until(char* data, int data_len = 0, int timeout = SIM7600_REV_TIMEOUT_MS);

  bool get_data(char* data, int data_len = 0);

  // TODO: add gprs functions
  // TODO: add ftp functions
private:
  At_command* at_comm;
  Sim7600_transmission_mode transmission_mode;
  Gpio_if* power_pin;
  Gpio_if* rst_pin;
  char* buff;
  int buff_size;
  char cid;
  char* server_ip;
  unsigned short server_port;
  Sim7600_protocol protocol;
  char link_num;
};

#endif // _SIM7600_H_
