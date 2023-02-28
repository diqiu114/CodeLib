/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-28
 * 
 * @brief sim7600 client mode
 * 
 * ***********************************************************
 */

#ifndef _SIM_CLIENT_H_
#define _SIM_CLIENT_H_

#include "sim7600.h"
#include "..\wlan_comm_if.h"

class Sim_client : public Wlan_comm_if
{
  public :
  Sim_client(Sim7600 *_sim);
  virtual ~Sim_client();
  virtual bool init(void);
  virtual bool open_net(void);
  virtual bool close_net(void);
  virtual bool tcp_connect(char* server, unsigned short port);
  virtual bool udp_connect(char* server, unsigned short dst_port, unsigned short src_port = 0);
  virtual bool disconnect(void);
  virtual bool send(char* data, int data_len);
  virtual bool get(char* ret_data, int data_len = 0);
  private:
    Sim7600 *sim;
};



#endif // _SIM_CLIENT_H_
