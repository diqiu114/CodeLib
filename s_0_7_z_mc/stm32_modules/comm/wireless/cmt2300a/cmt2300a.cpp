#include "cmt2300a.h"
#include "cmt2300a_defs.h"

Cmt2300a::Cmt2300a(Delay_if *_delay, vector<Gpio_if *> &gpios, bool _auto_sw)
{
  microseconds = _delay;
  clk = gpios[0];
  sdio = gpios[1];
  cs = gpios[2];
  fcs = gpios[3];
  auto_sw = _auto_sw;
}

Cmt2300a::~Cmt2300a()
{
  if (microseconds != NULL)
  {
    delete microseconds;
    microseconds = NULL;
  }

  if (clk != NULL)
  {
    delete clk;
    clk = NULL;
  }

  if (sdio != NULL)
  {
    delete sdio;
    sdio = NULL;
  }

  if (cs != NULL)
  {
    delete cs;
    cs = NULL;
  }

  if (fcs != NULL)
  {
    delete fcs;
    fcs = NULL;
  }
}

/*! ********************************************************
* @name    soft_rst
* @desc    Soft reset.
* *********************************************************/
void Cmt2300a::soft_rst(void)
{
  write_reg(0x7F, 0xFF);
}

/*! ********************************************************
* @name    get_status
* @desc    Get the chip status.
* @return
*          CMT2300A_STA_PUP
*          CMT2300A_STA_SLEEP
*          CMT2300A_STA_STBY
*          CMT2300A_STA_RFS
*          CMT2300A_STA_TFS
*          CMT2300A_STA_RX
*          CMT2300A_STA_TX
*          CMT2300A_STA_EEPROM
*          CMT2300A_STA_ERROR
*          CMT2300A_STA_CAL
* *********************************************************/
unsigned char Cmt2300a::get_status(void)
{
  return read_reg(CMT2300A_CUS_MODE_STA) & CMT2300A_MASK_CHIP_MODE_STA;
}

/*! ********************************************************
* @name    auto_switch_status
* @desc    Auto switch the chip status, and 10 ms as timeout.
* @param   nGoCmd: the chip next status
* @return  true or false
* *********************************************************/
bool Cmt2300a::auto_switch_status(unsigned char nGoCmd)
{
  if (auto_sw)
  {
    unsigned int delay = 10;

    unsigned char nWaitStatus;

    switch (nGoCmd)
    {
    case CMT2300A_GO_SLEEP:
      nWaitStatus = CMT2300A_STA_SLEEP;
      break;
    case CMT2300A_GO_STBY:
      nWaitStatus = CMT2300A_STA_STBY;
      break;
    case CMT2300A_GO_TFS:
      nWaitStatus = CMT2300A_STA_TFS;
      break;
    case CMT2300A_GO_TX:
      nWaitStatus = CMT2300A_STA_TX;
      break;
    case CMT2300A_GO_RFS:
      nWaitStatus = CMT2300A_STA_RFS;
      break;
    case CMT2300A_GO_RX:
      nWaitStatus = CMT2300A_STA_RX;
      break;
    }

    write_reg(CMT2300A_CUS_MODE_CTL, nGoCmd);

    while (delay--)
    {
      microseconds->delay(100);

      if (nWaitStatus == get_status())
        return true;

      if (CMT2300A_GO_TX == nGoCmd)
      {
        microseconds->delay(100);

        if (CMT2300A_MASK_TX_DONE_FLG & read_reg(CMT2300A_CUS_INT_CLR1))
          return true;
      }

      if (CMT2300A_GO_RX == nGoCmd)
      {
        microseconds->delay(100);

        if (CMT2300A_MASK_PKT_OK_FLG & read_reg(CMT2300A_CUS_INT_FLAG))
          return true;
      }
    }

    return false;
  }
  else
  {
    write_reg(CMT2300A_CUS_MODE_CTL, nGoCmd);
    return true;
  }
}

/*! ********************************************************
* @name    to_sleep
* @desc    Entry SLEEP mode.
* @return  true or false
* *********************************************************/
bool Cmt2300a::to_sleep(void)
{
  return auto_switch_status(CMT2300A_GO_SLEEP);
}

/*! ********************************************************
* @name    to_stby
* @desc    Entry Sleep mode.
* @return  true or false
* *********************************************************/
bool Cmt2300a::to_stby(void)
{
  return auto_switch_status(CMT2300A_GO_STBY);
}

/*! ********************************************************
* @name    to_tfs
* @desc    Entry TFS mode.
* @return  true or false
* *********************************************************/
bool Cmt2300a::to_tfs(void)
{
  return auto_switch_status(CMT2300A_GO_TFS);
}

/*! ********************************************************
* @name    to_rfs
* @desc    Entry RFS mode.
* @return  true or false
* *********************************************************/
bool Cmt2300a::to_rfs(void)
{
  return auto_switch_status(CMT2300A_GO_RFS);
}

/*! ********************************************************
* @name    to_tx
* @desc    Entry Tx mode.
* @return  true or false
* *********************************************************/
bool Cmt2300a::to_tx(void)
{
  return auto_switch_status(CMT2300A_GO_TX);
}

/*! ********************************************************
* @name    to_rx
* @desc    Entry Rx mode.
* @return  true or false
* *********************************************************/
bool Cmt2300a::to_rx(void)
{
  return auto_switch_status(CMT2300A_GO_RX);
}

/*! ********************************************************
* @name    config_gpio
* @desc    Config GPIO pins mode.
* @param   nGpioSel: GPIO1_SEL | GPIO2_SEL | GPIO3_SEL | GPIO4_SEL
*          GPIO1_SEL:
*            CMT2300A_GPIO1_SEL_DOUT/DIN 
*            CMT2300A_GPIO1_SEL_INT1
*            CMT2300A_GPIO1_SEL_INT2 
*            CMT2300A_GPIO1_SEL_DCLK
*
*          GPIO2_SEL:
*            CMT2300A_GPIO2_SEL_INT1 
*            CMT2300A_GPIO2_SEL_INT2
*            CMT2300A_GPIO2_SEL_DOUT/DIN 
*            CMT2300A_GPIO2_SEL_DCLK
*
*          GPIO3_SEL:
*            CMT2300A_GPIO3_SEL_CLKO 
*            CMT2300A_GPIO3_SEL_DOUT/DIN
*            CMT2300A_GPIO3_SEL_INT2 
*            CMT2300A_GPIO3_SEL_DCLK
*
*          GPIO4_SEL:
*            CMT2300A_GPIO4_SEL_RSTIN 
*            CMT2300A_GPIO4_SEL_INT1
*            CMT2300A_GPIO4_SEL_DOUT 
*            CMT2300A_GPIO4_SEL_DCLK
* *********************************************************/
void Cmt2300a::config_gpio(unsigned char nGpioSel)
{
  write_reg(CMT2300A_CUS_IO_SEL, nGpioSel);
}

/*! ********************************************************
* @name    config_interrupt
* @desc    Config interrupt on INT1 and INT2.
* @param   nInt1Sel, nInt2Sel
*            CMT2300A_INT_SEL_RX_ACTIVE
*            CMT2300A_INT_SEL_TX_ACTIVE
*            CMT2300A_INT_SEL_RSSI_VLD
*            CMT2300A_INT_SEL_PREAM_OK
*            CMT2300A_INT_SEL_SYNC_OK
*            CMT2300A_INT_SEL_NODE_OK
*            CMT2300A_INT_SEL_CRC_OK
*            CMT2300A_INT_SEL_PKT_OK
*            CMT2300A_INT_SEL_SL_TMO
*            CMT2300A_INT_SEL_RX_TMO
*            CMT2300A_INT_SEL_TX_DONE
*            CMT2300A_INT_SEL_RX_FIFO_NMTY
*            CMT2300A_INT_SEL_RX_FIFO_TH
*            CMT2300A_INT_SEL_RX_FIFO_FULL
*            CMT2300A_INT_SEL_RX_FIFO_WBYTE
*            CMT2300A_INT_SEL_RX_FIFO_OVF
*            CMT2300A_INT_SEL_TX_FIFO_NMTY
*            CMT2300A_INT_SEL_TX_FIFO_TH
*            CMT2300A_INT_SEL_TX_FIFO_FULL
*            CMT2300A_INT_SEL_STATE_IS_STBY
*            CMT2300A_INT_SEL_STATE_IS_FS
*            CMT2300A_INT_SEL_STATE_IS_RX
*            CMT2300A_INT_SEL_STATE_IS_TX
*            CMT2300A_INT_SEL_LED
*            CMT2300A_INT_SEL_TRX_ACTIVE
*            CMT2300A_INT_SEL_PKT_DONE
* *********************************************************/
void Cmt2300a::config_interrupt(unsigned char nInt1Sel, unsigned char nInt2Sel)
{
  nInt1Sel &= CMT2300A_MASK_INT1_SEL;
  nInt1Sel |= (~CMT2300A_MASK_INT1_SEL) & read_reg(CMT2300A_CUS_INT1_CTL);
  write_reg(CMT2300A_CUS_INT1_CTL, nInt1Sel);

  nInt2Sel &= CMT2300A_MASK_INT2_SEL;
  nInt2Sel |= (~CMT2300A_MASK_INT2_SEL) & read_reg(CMT2300A_CUS_INT2_CTL);
  write_reg(CMT2300A_CUS_INT2_CTL, nInt2Sel);
}

/*! ********************************************************
* @name    set_int_polar
* @desc    Set the polarity of the interrupt.
* @param   bEnable(true): active-high (default)
*          bEnable(false): active-low
* *********************************************************/
void Cmt2300a::set_int_polar(bool bActiveHigh)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_INT1_CTL);

  if (bActiveHigh)
    tmp &= ~CMT2300A_MASK_INT_POLAR;
  else
    tmp |= CMT2300A_MASK_INT_POLAR;

  write_reg(CMT2300A_CUS_INT1_CTL, tmp);
}

/*! ********************************************************
* @name    set_fifo_thr
* @desc    Set FIFO threshold.
* @param   nFifoThreshold
* *********************************************************/
void Cmt2300a::set_fifo_thr(unsigned char nFifoThreshold)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_PKT29);

  tmp &= ~CMT2300A_MASK_FIFO_TH;
  tmp |= nFifoThreshold & CMT2300A_MASK_FIFO_TH;

  write_reg(CMT2300A_CUS_PKT29, tmp);
}

/*! ********************************************************
* @name    ant_swtich_enable
* @desc    Enable antenna switch, output TX_ACTIVE/RX_ACTIVE
*          via GPIO1/GPIO2.
* @param   nMode 
*            0: RF_SWT1_EN=1, RF_SWT2_EN=0
*               GPIO1: RX_ACTIVE, GPIO2: TX_ACTIVE
*            1: RF_SWT1_EN=0, RF_SWT2_EN=1
*               GPIO1: RX_ACTIVE, GPIO2: ~RX_ACTIVE
* *********************************************************/
void Cmt2300a::ant_swtich_enable(unsigned char nMode)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_INT1_CTL);

  if (0 == nMode)
  {
    tmp |= CMT2300A_MASK_RF_SWT1_EN;
    tmp &= ~CMT2300A_MASK_RF_SWT2_EN;
  }
  else if (1 == nMode)
  {
    tmp &= ~CMT2300A_MASK_RF_SWT1_EN;
    tmp |= CMT2300A_MASK_RF_SWT2_EN;
  }

  write_reg(CMT2300A_CUS_INT1_CTL, tmp);
}

/*! ********************************************************
* @name    interrupt_enable
* @desc    Enable interrupt.
* @param   nEnable 
*            CMT2300A_MASK_SL_TMO_EN   |
*            CMT2300A_MASK_RX_TMO_EN   |
*            CMT2300A_MASK_TX_DONE_EN  |
*            CMT2300A_MASK_PREAM_OK_EN |
*            CMT2300A_MASK_SYNC_OK_EN  |
*            CMT2300A_MASK_NODE_OK_EN  |
*            CMT2300A_MASK_CRC_OK_EN   |
*            CMT2300A_MASK_PKT_DONE_EN
* *********************************************************/
void Cmt2300a::interrupt_enable(unsigned char nEnable)
{
  write_reg(CMT2300A_CUS_INT_EN, nEnable);
}

/*! ********************************************************
* @name    rx_fifo_auto_clear_enable
* @desc    Auto clear Rx FIFO before entry Rx mode.
* @param   bEnable(true): Enable it(default)
*          bEnable(false): Disable it
* *********************************************************/
void Cmt2300a::rx_fifo_auto_clear_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_CTL);

  if (bEnable)
    tmp &= ~CMT2300A_MASK_FIFO_AUTO_CLR_DIS;
  else
    tmp |= CMT2300A_MASK_FIFO_AUTO_CLR_DIS;

  write_reg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    fifo_merge_enable
* @desc    Enable FIFO merge.
* @param   bEnable(true): use a single 64-byte FIFO for either Tx or Rx
*          bEnable(false): use a 32-byte FIFO for Tx and another 32-byte FIFO for Rx(default)
* *********************************************************/
void Cmt2300a::fifo_merge_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_CTL);

  if (bEnable)
    tmp |= CMT2300A_MASK_FIFO_MERGE_EN;
  else
    tmp &= ~CMT2300A_MASK_FIFO_MERGE_EN;

  write_reg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    read_fifo_enable
* @desc    Enable SPI to read the FIFO.
* *********************************************************/
void Cmt2300a::read_fifo_enable(void)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_CTL);
  tmp &= ~CMT2300A_MASK_SPI_FIFO_RD_WR_SEL;
  tmp &= ~CMT2300A_MASK_FIFO_RX_TX_SEL;
  write_reg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    write_fifo_enable
* @desc    Enable SPI to write the FIFO.
* *********************************************************/
void Cmt2300a::write_fifo_enable(void)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_CTL);
  tmp |= CMT2300A_MASK_SPI_FIFO_RD_WR_SEL;
  tmp |= CMT2300A_MASK_FIFO_RX_TX_SEL;
  write_reg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    restore_fifo
* @desc    Restore the FIFO.
* *********************************************************/
void Cmt2300a::restore_fifo(void)
{
  write_reg(CMT2300A_CUS_FIFO_CLR, CMT2300A_MASK_FIFO_RESTORE);
}

/*! ********************************************************
* @name    CMT2300A_ClearFifo
* @desc    Clear the Tx FIFO.
* @return  FIFO flags
*            CMT2300A_MASK_RX_FIFO_FULL_FLG |
*            CMT2300A_MASK_RX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_RX_FIFO_TH_FLG   |
*            CMT2300A_MASK_RX_FIFO_OVF_FLG  |
*            CMT2300A_MASK_TX_FIFO_FULL_FLG |
*            CMT2300A_MASK_TX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_TX_FIFO_TH_FLG
* *********************************************************/
unsigned char Cmt2300a::clear_tx_fifo(void)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_FLAG);
  write_reg(CMT2300A_CUS_FIFO_CLR, CMT2300A_MASK_FIFO_CLR_TX);
  return tmp;
}

/*! ********************************************************
* @name    CMT2300A_ClearFifo
* @desc    Clear the Rx FIFO.
* @return  FIFO flags
*            CMT2300A_MASK_RX_FIFO_FULL_FLG |
*            CMT2300A_MASK_RX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_RX_FIFO_TH_FLG   |
*            CMT2300A_MASK_RX_FIFO_OVF_FLG  |
*            CMT2300A_MASK_TX_FIFO_FULL_FLG |
*            CMT2300A_MASK_TX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_TX_FIFO_TH_FLG
* *********************************************************/
unsigned char Cmt2300a::clear_rx_fifo(void)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_FLAG);
  write_reg(CMT2300A_CUS_FIFO_CLR, CMT2300A_MASK_FIFO_CLR_RX);
  return tmp;
}

/*! ********************************************************
* @name    clear_interrupt
* @desc    Clear all interrupt flags.
* @return  Some interrupt flags
*            CMT2300A_MASK_SL_TMO_EN    |
*            CMT2300A_MASK_RX_TMO_EN    |
*            CMT2300A_MASK_TX_DONE_EN   |
*            CMT2300A_MASK_PREAM_OK_FLG |
*            CMT2300A_MASK_SYNC_OK_FLG  |
*            CMT2300A_MASK_NODE_OK_FLG  |
*            CMT2300A_MASK_CRC_OK_FLG   |
*            CMT2300A_MASK_PKT_OK_FLG
* *********************************************************/
unsigned char Cmt2300a::clear_interrupt(void)
{
  unsigned char nFlag1, nFlag2;
  unsigned char nClr1 = 0;
  unsigned char nClr2 = 0;
  unsigned char nRet = 0;
  unsigned char nIntPolar;

  nIntPolar = read_reg(CMT2300A_CUS_INT1_CTL);
  nIntPolar = (nIntPolar & CMT2300A_MASK_INT_POLAR) ? 1 : 0;

  nFlag1 = read_reg(CMT2300A_CUS_INT_FLAG);
  nFlag2 = read_reg(CMT2300A_CUS_INT_CLR1);

  if (nIntPolar)
  {
    /* Interrupt flag active-low */
    nFlag1 = ~nFlag1;
    nFlag2 = ~nFlag2;
  }

  if (CMT2300A_MASK_LBD_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_LBD_CLR; /* Clear LBD_FLG */
  }

  if (CMT2300A_MASK_COL_ERR_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_PKT_DONE_CLR; /* Clear COL_ERR_FLG by PKT_DONE_CLR */
  }

  if (CMT2300A_MASK_PKT_ERR_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_PKT_DONE_CLR; /* Clear PKT_ERR_FLG by PKT_DONE_CLR */
  }

  if (CMT2300A_MASK_PREAM_OK_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_PREAM_OK_CLR; /* Clear PREAM_OK_FLG */
    nRet |= CMT2300A_MASK_PREAM_OK_FLG;  /* Return PREAM_OK_FLG */
  }

  if (CMT2300A_MASK_SYNC_OK_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_SYNC_OK_CLR; /* Clear SYNC_OK_FLG */
    nRet |= CMT2300A_MASK_SYNC_OK_FLG;  /* Return SYNC_OK_FLG */
  }

  if (CMT2300A_MASK_NODE_OK_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_NODE_OK_CLR; /* Clear NODE_OK_FLG */
    nRet |= CMT2300A_MASK_NODE_OK_FLG;  /* Return NODE_OK_FLG */
  }

  if (CMT2300A_MASK_CRC_OK_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_CRC_OK_CLR; /* Clear CRC_OK_FLG */
    nRet |= CMT2300A_MASK_CRC_OK_FLG;  /* Return CRC_OK_FLG */
  }

  if (CMT2300A_MASK_PKT_OK_FLG & nFlag1)
  {
    nClr2 |= CMT2300A_MASK_PKT_DONE_CLR; /* Clear PKT_OK_FLG */
    nRet |= CMT2300A_MASK_PKT_OK_FLG;    /* Return PKT_OK_FLG */
  }

  if (CMT2300A_MASK_SL_TMO_FLG & nFlag2)
  {
    nClr1 |= CMT2300A_MASK_SL_TMO_CLR; /* Clear SL_TMO_FLG */
    nRet |= CMT2300A_MASK_SL_TMO_EN;   /* Return SL_TMO_FLG by SL_TMO_EN */
  }

  if (CMT2300A_MASK_RX_TMO_FLG & nFlag2)
  {
    nClr1 |= CMT2300A_MASK_RX_TMO_CLR; /* Clear RX_TMO_FLG */
    nRet |= CMT2300A_MASK_RX_TMO_EN;   /* Return RX_TMO_FLG by RX_TMO_EN */
  }

  if (CMT2300A_MASK_TX_DONE_FLG & nFlag2)
  {
    nClr1 |= CMT2300A_MASK_TX_DONE_CLR; /* Clear TX_DONE_FLG */
    nRet |= CMT2300A_MASK_TX_DONE_EN;   /* Return TX_DONE_FLG by TX_DONE_EN */
  }

  write_reg(CMT2300A_CUS_INT_CLR1, nClr1);
  write_reg(CMT2300A_CUS_INT_CLR2, nClr2);

  if (nIntPolar)
  {
    /* Interrupt flag active-low */
    nRet = ~nRet;
  }

  return nRet;
}

/*! ********************************************************
* @name    config_tx_din
* @desc    Used to select whether to use GPIO1 or GPIO2 or GPIO3
*          as DIN in the direct mode. It only takes effect when 
*          call tx_din_enable(true) in the direct mode.
* @param   nDinSel
*            CMT2300A_TX_DIN_SEL_GPIO1
*            CMT2300A_TX_DIN_SEL_GPIO2
*            CMT2300A_TX_DIN_SEL_GPIO3
* *********************************************************/
void Cmt2300a::config_tx_din(unsigned char nDinSel)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_CTL);
  tmp &= ~CMT2300A_MASK_TX_DIN_SEL;
  tmp |= nDinSel;
  write_reg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    tx_din_enable
* @desc    Used to change GPIO1/GPIO2/GPIO3 between DOUT and DIN.
* @param   bEnable(true): used as DIN
*          bEnable(false): used as DOUT(default)
* *********************************************************/
void Cmt2300a::tx_din_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FIFO_CTL);

  if (bEnable)
    tmp |= CMT2300A_MASK_TX_DIN_EN;
  else
    tmp &= ~CMT2300A_MASK_TX_DIN_EN;

  write_reg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    tx_din_invert_enable
* @desc    Used to invert DIN data in direct mode.
* @param   bEnable(true): invert DIN
*          bEnable(false): not invert DIN(default)
* *********************************************************/
void Cmt2300a::tx_din_invert_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_INT2_CTL);

  if (bEnable)
    tmp |= CMT2300A_MASK_TX_DIN_INV;
  else
    tmp &= ~CMT2300A_MASK_TX_DIN_INV;

  write_reg(CMT2300A_CUS_INT2_CTL, tmp);
}

/*! ********************************************************
* @name    exist
* @desc    Chip indentify.
* @return  true: chip is exist, false: chip not found
* *********************************************************/
bool Cmt2300a::exist(void)
{
  unsigned char back, dat;

  back = read_reg(CMT2300A_CUS_PKT17);
  write_reg(CMT2300A_CUS_PKT17, 0xAA);

  dat = read_reg(CMT2300A_CUS_PKT17);
  write_reg(CMT2300A_CUS_PKT17, back);

  if (0xAA == dat)
    return true;
  else
    return false;
}

/*! ********************************************************
* @name    get_rssi
* @desc    Get RSSI code.
* @return  RSSI code
* *********************************************************/
unsigned char Cmt2300a::get_rssi(void)
{
  return read_reg(CMT2300A_CUS_RSSI_CODE);
}

/*! ********************************************************
* @name    get_rssi_dbm
* @desc    Get RSSI dBm.
* @return  dBm
* *********************************************************/
int Cmt2300a::get_rssi_dbm(void)
{
  return (int)read_reg(CMT2300A_CUS_RSSI_DBM) - 128;
}

/*! ********************************************************
* @name    set_freq_channel
* @desc    This defines up to 255 frequency channel
*          for fast frequency hopping operation.
* @param   nChann: the frequency channel
* *********************************************************/
void Cmt2300a::set_freq_channel(unsigned char nChann)
{
  write_reg(CMT2300A_CUS_FREQ_CHNL, nChann);
}

/*! ********************************************************
* @name    set_freq_step
* @desc    This defines the frequency channel step size 
*          for fast frequency hopping operation. 
*          One step size is 2.5 kHz.
* @param   nOffset: the frequency step
* *********************************************************/
void Cmt2300a::set_freq_step(unsigned char nOffset)
{
  write_reg(CMT2300A_CUS_FREQ_OFS, nOffset);
}

/*! ********************************************************
* @name    set_payload_length
* @desc    Set payload length.
* @param   nLength
* *********************************************************/
void Cmt2300a::set_payload_length(unsigned short nLength)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_PKT14);

  tmp &= ~CMT2300A_MASK_PAYLOAD_LENG_10_8;
  tmp |= (nLength >> 4) & CMT2300A_MASK_PAYLOAD_LENG_10_8;
  write_reg(CMT2300A_CUS_PKT14, tmp);

  tmp = nLength & CMT2300A_MASK_PAYLOAD_LENG_7_0;
  write_reg(CMT2300A_CUS_PKT15, tmp);
}

/*! ********************************************************
* @name    fosc_enable
* @desc    If you need use sleep timer, you should enable LFOSC.
* @param   bEnable(true): Enable it(default)
*          bEnable(false): Disable it
* *********************************************************/
void Cmt2300a::fosc_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_SYS2);

  if (bEnable)
  {
    tmp |= CMT2300A_MASK_LFOSC_RECAL_EN;
    tmp |= CMT2300A_MASK_LFOSC_CAL1_EN;
    tmp |= CMT2300A_MASK_LFOSC_CAL2_EN;
  }
  else
  {
    tmp &= ~CMT2300A_MASK_LFOSC_RECAL_EN;
    tmp &= ~CMT2300A_MASK_LFOSC_CAL1_EN;
    tmp &= ~CMT2300A_MASK_LFOSC_CAL2_EN;
  }

  write_reg(CMT2300A_CUS_SYS2, tmp);
}

/*! ********************************************************
* @name    fosc_output_enable
* @desc    LFOSC clock is output via GPIO3.
* @param   bEnable(true): Enable it
*          bEnable(false): Disable it(default)
* *********************************************************/
void Cmt2300a::fosc_output_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_INT2_CTL);

  if (bEnable)
    tmp |= CMT2300A_MASK_LFOSC_OUT_EN;
  else
    tmp &= ~CMT2300A_MASK_LFOSC_OUT_EN;

  write_reg(CMT2300A_CUS_INT2_CTL, tmp);
}

/*! ********************************************************
* @name    afc_enable
* @desc    AFC enable or disanble.
* @param   bEnable(true): Enable it
*          bEnable(false): Disable it(default)
* *********************************************************/
void Cmt2300a::afc_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_FSK5);

  if (bEnable)
    tmp |= 0x10;
  else
    tmp &= ~0x10;

  write_reg(CMT2300A_CUS_FSK5, tmp);
}

/*! ********************************************************
* @name    set_afc_overflow_thr
* @desc    This is optional, only needed when using Rx fast frequency hopping.
* @param   afcOvfTh: AFC_OVF_TH see AN142 and AN197 for details.
* *********************************************************/
void Cmt2300a::set_afc_overflow_thr(unsigned char afcOvfTh)
{
  write_reg(CMT2300A_CUS_FSK4, afcOvfTh);
}

/*! ********************************************************
* @name    dutycycle_enable
* @desc    If you need use close dutyclcle, you should disable .
* @param   bEnable(TRUE): Enable it(default)
*          bEnable(FALSE): Disable it
* *********************************************************/
void Cmt2300a::dutycycle_enable(bool bEnable)
{
  unsigned char tmp = read_reg(CMT2300A_CUS_SYS2);

  if (bEnable)
  {
    tmp &= ~CMT2300A_MASK_DC_PAUSE;
  }
  else
  {
    tmp |= CMT2300A_MASK_DC_PAUSE;
  }

  write_reg(CMT2300A_CUS_SYS2, tmp);
}

/*! ********************************************************
* @name    init
* @desc    Initialize chip status.
* *********************************************************/
void Cmt2300a::init(void)
{
  unsigned char tmp;

  spi_gpio_init();

  soft_rst();
  microseconds->delay(20 * 1000);
  to_stby();

  tmp = read_reg(CMT2300A_CUS_MODE_STA);
  tmp |= CMT2300A_MASK_CFG_RETAIN;  /* Enable CFG_RETAIN */
  tmp &= ~CMT2300A_MASK_RSTN_IN_EN; /* Disable RSTN_IN */
  write_reg(CMT2300A_CUS_MODE_STA, tmp);

  tmp = read_reg(CMT2300A_CUS_EN_CTL);
  tmp |= CMT2300A_MASK_LOCKING_EN; /* Enable LOCKING_EN */
  write_reg(CMT2300A_CUS_EN_CTL, tmp);

  // fosc_enable(false); /* Diable LFOSC */

  clear_interrupt();

  exist();
}

/*! ********************************************************
* @name    config_reg_bank
* @desc    Config one register bank.
* *********************************************************/
bool Cmt2300a::config_reg_bank(unsigned char base_addr, const unsigned char bank[], unsigned char len)
{
  unsigned char i;
  for (i = 0; i < len; i++)
    write_reg(i + base_addr, bank[i]);

  return true;
}

/*! ********************************************************
* @name    read_reg
* @desc    Read the CMT2300A register at the specified address.
* @param   addr: register address
* @return  Register value
* *********************************************************/
unsigned char Cmt2300a::read_reg(unsigned char addr)
{
  unsigned char dat = 0xFF;
  spi_read_reg(addr, &dat);

  return dat;
}

/*! ********************************************************
* @name    write_reg
* @desc    Write the CMT2300A register at the specified address.
* @param   addr: register address
*          dat: register value
* *********************************************************/
void Cmt2300a::write_reg(unsigned char addr, unsigned char dat)
{
  spi_write_reg(addr, dat);
}

/*! ********************************************************
* @name    read_fifo
* @desc    Reads the contents of the CMT2300A FIFO.
* @param   buf: buffer where to copy the FIFO read data
*          len: number of bytes to be read from the FIFO
* *********************************************************/
void Cmt2300a::read_fifo(unsigned char buf[], unsigned short len)
{
  spi_read_fifo(buf, len);
}

/*! ********************************************************
* @name    write_fifo
* @desc    Writes the buffer contents to the CMT2300A FIFO.
* @param   buf: buffer containing data to be put on the FIFO
*          len: number of bytes to be written to the FIFO
* *********************************************************/
void Cmt2300a::write_fifo(const unsigned char buf[], unsigned short len)
{
  spi_write_fifo(buf, len);
}

void Cmt2300a::spi_delay(void)
{
  microseconds->delay(1);
  //    unsigned int n = 7;
  //    while(n--);
}

void Cmt2300a::spi_delay_us(void)
{
  microseconds->delay(1);
  //    unsigned short n = 8;
  //    while(n--);
}

void Cmt2300a::spi_gpio_init(void)
{
  cs->set_hi();
  cs->set_mode_out();
  cs->set_hi(); /* CSB has an internal pull-up resistor */

  clk->set_low();
  clk->set_mode_out();
  clk->set_low(); /* SCLK has an internal pull-down resistor */

  sdio->set_hi();
  sdio->set_mode_out();
  sdio->set_hi();

  fcs->set_hi();
  fcs->set_mode_out();
  fcs->set_hi(); /* FCSB has an internal pull-up resistor */

  spi_delay();
}

void Cmt2300a::spi_send(unsigned char data8)
{
  unsigned char i;

  for (i = 0; i < 8; i++)
  {
    clk->set_low();

    /* Send byte on the rising edge of SCLK */
    if (data8 & 0x80)
      sdio->set_hi();
    else
      sdio->set_low();

    spi_delay();

    data8 <<= 1;
    clk->set_hi();
    spi_delay();
  }
}

unsigned char Cmt2300a::spi_receive(void)
{
  unsigned char i;
  unsigned char data8 = 0xFF;

  for (i = 0; i < 8; i++)
  {
    clk->set_low();
    spi_delay();
    data8 <<= 1;

    clk->set_hi();

    /* Read byte on the rising edge of SCLK */
    if (sdio->read())
      data8 |= 0x01;
    else
      data8 &= ~0x01;

    spi_delay();
  }

  return data8;
}

void Cmt2300a::spi_write_reg(unsigned char addr, unsigned char dat)
{
  sdio->set_hi();
  sdio->set_mode_out();

  clk->set_low();
  clk->set_mode_out();
  clk->set_low();

  fcs->set_hi();
  fcs->set_mode_out();
  fcs->set_hi();

  cs->set_low();

  /* > 0.5 SCLK cycle */
  spi_delay();
  spi_delay();

  /* r/w = 0 */
  spi_send(addr & 0x7F);

  spi_send(dat);

  clk->set_low();

  /* > 0.5 SCLK cycle */
  spi_delay();
  spi_delay();

  cs->set_hi();

  sdio->set_hi();
  sdio->set_mode_in();

  fcs->set_hi();
}

void Cmt2300a::spi_read_reg(unsigned char addr, unsigned char *p_dat)
{
  sdio->set_hi();
  sdio->set_mode_out();

  clk->set_low();
  clk->set_mode_out();
  clk->set_low();

  fcs->set_hi();
  fcs->set_mode_out();
  fcs->set_hi();

  cs->set_low();

  /* > 0.5 SCLK cycle */
  spi_delay();
  spi_delay();

  /* r/w = 1 */
  spi_send(addr | 0x80);

  /* Must set SDIO to input before the falling edge of SCLK */
  sdio->set_mode_in();

  *p_dat = spi_receive();

  clk->set_low();

  /* > 0.5 SCLK cycle */
  spi_delay();
  spi_delay();

  cs->set_hi();

  sdio->set_hi();
  sdio->set_mode_in();

  fcs->set_hi();
}

void Cmt2300a::spi_write_fifo(const unsigned char *p_buf, unsigned short len)
{
  unsigned short i;

  fcs->set_hi();
  fcs->set_mode_out();
  fcs->set_hi();

  cs->set_hi();
  cs->set_mode_out();
  cs->set_hi();

  clk->set_low();
  clk->set_mode_out();
  clk->set_low();

  sdio->set_mode_out();

  for (i = 0; i < len; i++)
  {
    fcs->set_low();

    /* > 1 SCLK cycle */
    spi_delay();
    spi_delay();

    spi_send(p_buf[i]);

    clk->set_low();

    /* > 2 us */
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();

    fcs->set_hi();

    /* > 4 us */
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
  }

  sdio->set_mode_in();

  fcs->set_hi();
}

void Cmt2300a::spi_read_fifo(unsigned char *p_buf, unsigned short len)
{
  unsigned short i;

  fcs->set_hi();
  fcs->set_mode_out();
  fcs->set_hi();

  cs->set_hi();
  cs->set_mode_out();
  cs->set_hi();

  clk->set_low();
  clk->set_mode_out();
  clk->set_low();

  sdio->set_mode_in();

  for (i = 0; i < len; i++)
  {
    fcs->set_low();

    /* > 1 SCLK cycle */
    spi_delay();
    spi_delay();

    p_buf[i] = spi_receive();

    clk->set_low();

    /* > 2 us */
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();

    fcs->set_hi();

    /* > 4 us */
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
    spi_delay_us();
  }

  sdio->set_mode_in();

  fcs->set_hi();
}
