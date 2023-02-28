/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      无线433芯片 cmt2300A 应用程序
* 由于需实现可变包长接收与发送，需配合GPIO中断方式进行
* 实现可变包长的发送与接收需要以下4个中断,且GPIO只能同一时间绑定一个中断
* 1.接收FIFO阈值中断 RX_FIFO_TH
* 2.接收完成中断 PKT_OK
* 3.发送FIFO阈值中断 TX_FIFO_TH
* 4.发送完成中断 TX_DONE
*
* 结合天线收发控制，可以有以下两种方式实现：
* 方式1：由CMT2300通过控制GPIO1和GPIO2的高低电平切换天线收发(自动天线切换模式)
*        GPIO3配置为接收阈值中断或发送阈值中断，绑定CMT2300A INT2中断
*        发送完成与接收完成中断通过读取寄存器的方式判断
* 注：由于GPIO引脚数量限制，无法配置sync_ok中断，导致CMT2300A无法进行休眠接收，有低功耗要求的场合不推荐使用！
*
* 方式2：由MCU控制天线收发，GPIO1作为接收以及发送阈值中断，GPIO2作为sync_ok(同步字完成)中断
*        GPIO2配置为接收阈值中断或发送阈值中断，绑定CMT2300A INT2中断
*        发送完成与接收完成中断通过读取寄存器的方式判断
*        GPIO1配置为sync_ok中断，绑定CMT2300A INT1中断，当接收到同步字完成时，产生中断，唤醒MCU。
*
***********************************************************/
#ifndef _CMT2300A_TRANCEIVER_H_
#define _CMT2300A_TRANCEIVER_H_

#include "comm\Double_buffered_comm.h"
#include "cmt2300a.h"
#include "modules_def.h"
#include "cmt2300a_antenna_sw.h"

// cmt2300 state machine
typedef enum _tag_cmt_state_
{
  CMT_STATE_IDLE = 0,
  CMT_STATE_RX_WAIT,
  CMT_STATE_RX_DONE,
  CMT_STATE_RX_TIMEOUT,
  CMT_STATE_TX_WAIT,
  CMT_STATE_TX_DONE,
  CMT_STATE_TX_TIMEOUT,
  CMT_STATE_ERROR,
} Cmt_state;

#define CMT2300_SEND_DATA_CNT_MAX (255)
#define CMT2300_FIFO_SIZE (64)
#define CMT2300_TX_TIMEOUT_MS (2000)
#define CMT2300_INTERRUPT_GPIO_CNT (3)
#define CMT2300_TX_POWER_LEVELS (7)

typedef void (*cmt_tx_done_callback)(void);
typedef void (*cmt_rx_done_callback)(void);

class Cmt2300a_tranceiver : public Double_buffered_comm
{
public:
  Cmt2300a_tranceiver(Cmt2300a *_cmt2300a, unsigned int buff_size, 
                      vector<Gpio_if *> &_int, bool _auto_antenna_sw = false, 
                      Cmt2300a_antenna_sw* _ant_sw = NULL, unsigned char _tx_power = CMT2300_TX_POWER_LEVELS - 1, 
                      unsigned int _tx_timeout = CMT2300_TX_TIMEOUT_MS);
  virtual ~Cmt2300a_tranceiver();

  virtual bool send(unsigned char *data, unsigned int data_len);
  virtual unsigned int read(unsigned char *data, unsigned int data_len);
  virtual unsigned int read_all(unsigned char *data);

  virtual bool rev_data_handle(unsigned char *data = NULL, unsigned int data_len = 0);

  virtual bool start_rev_it(void);

  void rx_process(void);
  void init(void);
  void set_tx_done_callback(cmt_tx_done_callback func);
  void set_rx_done_callback(cmt_rx_done_callback func);

  bool set_hopping_freq(unsigned char freq_num);
  void set_tx_power(unsigned char tx_power);
  bool set_sync_word(int sync_word, unsigned char word_size);

private:
  void set_gpio_send_int(void);
  void set_gpio_rev_int(void);
  bool set_ant_send(void);
  bool set_ant_rev(void);
  void config(void);
  unsigned char sync_word_size_to_reg_val(unsigned char word_size);
  bool check_no_signal_noise(int timeout);

  bool tx_done_int_trigger(void);
  bool tx_fifo_thr_int_trigger(void);
  bool rx_done_int_trigger(void);
  bool rx_fifo_thr_int_trigger(void);
  unsigned char hopping_freq_num;
  unsigned char tranceiver_buffer[CMT2300_FIFO_SIZE];
  Cmt2300a *cmt2300a;
  Cmt_state state;
  unsigned int tx_timeout;
  cmt_rx_done_callback rx_done_callback;
  cmt_tx_done_callback tx_done_callback;
  bool auto_antenna_sw;
  Gpio_if *gpio1;
  Gpio_if *gpio2;
  Cmt2300a_antenna_sw* ant_sw;
  
};

#endif // _CMT2300A_TRANCEIVER_H_
