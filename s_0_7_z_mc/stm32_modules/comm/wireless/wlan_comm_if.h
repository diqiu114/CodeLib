/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-28
 * 
 * @brief WLAN communication interface
 * 
 * ***********************************************************
 */

#ifndef _WLAN_COMM_IF_H_
#define _WLAN_COMM_IF_H_

class Wlan_comm_if
{
public:
  virtual bool init(void) = 0;
  virtual bool open_net(void) = 0;
  virtual bool close_net(void) = 0;
  virtual bool tcp_connect(char* server, unsigned short port) = 0;
  virtual bool udp_connect(char* server, unsigned short dst_port, unsigned short src_port = 0) = 0;
  virtual bool disconnect(void) = 0;
  virtual bool send(char* data, int data_len) = 0;
  virtual bool get(char* ret_data, int data_len = 0) = 0;
  virtual ~Wlan_comm_if(){};
};

#endif // _WLAN_COMM_IF_H_
