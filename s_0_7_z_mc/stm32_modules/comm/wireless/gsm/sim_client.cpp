#include "sim_client.h"
/**
 * @brief Construct a new Sim_client::Sim_client object
 * 
 * @param _sim sim7600 class pointer
 */
Sim_client::Sim_client(Sim7600 *_sim)
{
  sim = _sim;
}

Sim_client::~Sim_client()
{
  if (sim != NULL)
  {
    delete sim;
    sim = NULL;
  }
}

/**
 * @brief initialize
 * 
 * @return true initialize ok
 * @return false initialize failed
 */
bool Sim_client::init(void)
{
  bool ret = true;
  sim->power_up();

  ret = ret && sim->ready();
  ret = ret && sim->get_data_manually();
  ret = ret && sim->sim_card_ready();
  ret = ret && sim->registed();
  ret = ret && sim->signal_quality_ok();
  ret = ret && sim->curr_operator();
//  ret = ret && sim->config_pdp_context();
  ret = ret && sim->active_pdp_context();

  return ret;
}

/**
 * @brief open gprs network
 * 
 * @return true open ok
 * @return false open failed
 */
bool Sim_client::open_net(void)
{
  bool ret = true;

  ret = ret && sim->net_open();
  ret = ret && sim->ip_addr();

  return ret;
}

/**
 * @brief close gprs network
 * 
 * @return true close ok
 * @return false close failed
 */
bool Sim_client::close_net(void)
{
  return sim->net_close();
}

/**
 * @brief connect to tcp sever
 * 
 * @param server server ip or server address
 * @param port server port
 * @return true connect ok
 * @return false connect failed
 */
bool Sim_client::tcp_connect(char *server, unsigned short port)
{
  return sim->tcp_connect(server, port);
}

/**
 * @brief conenct to udp server
 * 
 * @param server server ip or server address
 * @param dst_port server port
 * @param src_port device port
 * @return true connect ok
 * @return false connect failed
 */
bool Sim_client::udp_connect(char *server, unsigned short dst_port, unsigned short src_port)
{
  return sim->udp_connect(server, dst_port, src_port);
}

/**
 * @brief disconnect from tcp/udp server
 * 
 * @return true ok
 * @return false failed
 */
bool Sim_client::disconnect(void)
{
  return sim->tcp_udp_disconnect();
}

/**
 * @brief send data to server
 * 
 * @param data data pointer 
 * @param data_len data length
 * @return true send ok
 * @return false send failed
 */
bool Sim_client::send(char *data, int data_len)
{
  return sim->send(data, data_len);
}

/**
 * @brief get data from sim7600 buffer
 * 
 * @param ret_data data pointer
 * @param data_len data length to be read
 * @return true get data ok
 * @return false no data or get data error
 */
bool Sim_client::get(char *ret_data, int data_len)
{
  return sim->get_data(ret_data, data_len);
}
