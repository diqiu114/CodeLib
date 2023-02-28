/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      华普 无线433芯片 cmt2300A 驱动程序 
*             基于官方驱动程序移植
*
***********************************************************/
#ifndef _CMT2300A_H_
#define _CMT2300A_H_

#include "hw_interface\gpio\gpio_if.h"
#include "delay\delay_if.h"
#include <vector>

using namespace std;

class Cmt2300a
{
public:
  Cmt2300a(Delay_if* _delay, vector<Gpio_if *> &gpios, bool _auto_sw = true);
  ~Cmt2300a();
  /* ************************************************************************
   The following are for chip status controls.
*  ************************************************************************ */
  void soft_rst(void);
  unsigned char get_status(void);
  bool auto_switch_status(unsigned char nGoCmd);
  bool to_sleep(void);
  bool to_stby(void);
  bool to_tfs(void);
  bool to_rfs(void);
  bool to_tx(void);
  bool to_rx(void);
  /* ************************************************************************
*  The following are for chip interrupts, GPIO, FIFO operations.
*  ************************************************************************ */
  void config_gpio(unsigned char nGpioSel);
  void config_interrupt(unsigned char nInt1Sel, unsigned char nInt2Sel);
  void set_int_polar(bool bActiveHigh);
  void set_fifo_thr(unsigned char nFifoThreshold);
  void ant_swtich_enable(unsigned char nMode);
  void interrupt_enable(unsigned char nEnable);
  void rx_fifo_auto_clear_enable(bool bEnable);
  void fifo_merge_enable(bool bEnable);
  void read_fifo_enable(void);
  void write_fifo_enable(void);
  void restore_fifo(void);
  unsigned char clear_tx_fifo(void);
  unsigned char clear_rx_fifo(void);
  unsigned char clear_interrupt(void);

  /* ************************************************************************
*  The following are for Tx DIN operations in direct mode.
*  ************************************************************************ */
  void config_tx_din(unsigned char nDinSel);
  void tx_din_enable(bool bEnable);
  void tx_din_invert_enable(bool bEnable);

  /* ************************************************************************
*  The following are general operations.
*  ************************************************************************ */
  bool exist(void);
  unsigned char get_rssi(void);
  int get_rssi_dbm(void);
  void set_freq_channel(unsigned char nChann);
  void set_freq_step(unsigned char nOffset);
  void set_payload_length(unsigned short nLength);
  void fosc_enable(bool bEnable = true);
  void fosc_output_enable(bool bEnable = true);
  void afc_enable(bool bEnable = true);
  void set_afc_overflow_thr(unsigned char afcOvfTh);
  void dutycycle_enable(bool bEnable = true);
  /* ************************************************************************
*  The following are for chip initializes.
*  ************************************************************************ */
  void init(void);
  bool config_reg_bank(unsigned char base_addr, const unsigned char bank[], unsigned char len);

  unsigned char read_reg(unsigned char addr);
  void write_reg(unsigned char addr, unsigned char dat);
  void read_fifo(unsigned char buf[], unsigned short len);
  void write_fifo(const unsigned char buf[], unsigned short len);

private:
  void spi_gpio_init(void);
  void spi_delay(void);
  void spi_delay_us(void);
  void spi_send(unsigned char data8);
  unsigned char spi_receive(void);
  void spi_write_reg(unsigned char addr, unsigned char dat);
  void spi_read_reg(unsigned char addr, unsigned char *p_dat);
  void spi_write_fifo(const unsigned char *p_buf, unsigned short len);
  void spi_read_fifo(unsigned char *p_buf, unsigned short len);
  
  Delay_if* microseconds;
  Gpio_if *clk;
  Gpio_if *sdio;
  Gpio_if *cs;
  Gpio_if *fcs;
  bool auto_sw;
};

#endif // _CMT2300A_H_
