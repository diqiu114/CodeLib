/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      无线433芯片 cmt2300A 应用程序 
*
***********************************************************/
#ifndef _CMT2300A_APP_H_
#define _CMT2300A_APP_H_

#include "cmt2300a.h"
#include "main.h"

/* RF state machine */
typedef enum
{
  RF_STATE_IDLE = 0,
  RF_STATE_RX_START,
  RF_STATE_RX_WAIT,
  RF_STATE_RX_DONE,
  RF_STATE_RX_TIMEOUT,
  RF_STATE_TX_START,
  RF_STATE_TX_WAIT,
  RF_STATE_TX_DONE,
  RF_STATE_TX_TIMEOUT,
  RF_STATE_ERROR,
} EnumRFStatus;

/* RF process function results */
typedef enum
{
  RF_IDLE = 0,
  RF_BUSY,
  RF_RX_DONE,
  RF_RX_TIMEOUT,
  RF_TX_DONE,
  RF_TX_TIMEOUT,
  RF_ERROR,
} EnumRFResult;

typedef unsigned int (*Get_tick_count) (void);

class Cmt2300a_app
{
public:
  Cmt2300a_app(Cmt2300a* _cmt2300, Get_tick_count _func, bool _ant_sw = true, Gpio_if* _int1 = NULL, Gpio_if* _int2 = NULL);
  ~Cmt2300a_app();
  
  bool chip_ready(void);
  typedef void (Handle_func)(void);
  bool set_handle_func(Handle_func * _handle_func);
  EnumRFStatus get_status(void);
  unsigned char get_interrupt_flags(void);

  void start_rx(unsigned char buf[], unsigned short len, unsigned int timeout);
  void start_tx(unsigned char buf[], unsigned short len, unsigned int timeout);
  void init(void);
  EnumRFResult process(void);
//  Gpio_if* int2;

private:
  void set_status(EnumRFStatus nStatus);
  void config(void);
  Cmt2300a* cmt2300a;
  bool ant_sw;
  Gpio_if* int1;
  Gpio_if* int2;
  Get_tick_count get_tick;
  Handle_func *handle_func;
};

#endif // _CMT2300A_APP_H_
