#include "cmt2300a_tranceiver.h"
#include "cmt2300a_params.h"
#include <string.h>

#define SYNC_WORD_SIZE_MIN (1)
#define SYNC_WORD_SIZE_MAX (4)

#define CMT_HOPPING_STEP_HZ (500000)

// 30k发射速率, 发送254字节需要花费70ms
#define CMT_30K_RATE_SEND_TIME_MAX (70)

#define CMT_NOISE_THR (-90)

// one step size 2.5kHz
#define HOPPING_STEP_SIZE (2500)
#define HOPPING_HZ_TO_STEP_NUM(x) ((x) / HOPPING_STEP_SIZE)

#if (CMT_HOPPING_STEP_HZ < HOPPING_STEP_SIZE)
#error "hopping frequence must greater than 2500Hz"
#endif

#define CMT_HOPPING_CNT (100)
// 跳频AFC_OVF寄存器值列表， 参考 AN197（配套）-CMT2300A-CMT2219B 跳频计算表.xlsx
// 表中频点从420MHz~469.5MHz，每500HZ一个频点，共100个
// 0 - 420.0MHz
// 1 - 420.5MHz
// 2 - 430.0MHz
// ...
// 99 - 469.5MHz
char Hopping_afc_val_list[CMT_HOPPING_CNT] =
    {
        10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
        10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
        11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
        11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
        11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
        11, 11, 11, 11, 11, 11, 11, 11, 11, 11};

#define TX_POWER_BANK_CNT (3)

// tx power level from 0~6. the larger the number, the storger the signal
const unsigned char Tx_power_list[CMT2300_TX_POWER_LEVELS][TX_POWER_BANK_CNT] =
    {
        {0x1C, 0x05, 0x01}, // -10dbm
        {0x1C, 0x0A, 0x01}, // -5dbm
        {0x1C, 0x10, 0x02}, // 0dbm
        {0x1C, 0x1D, 0x03}, // 5dbm
        {0x1C, 0x33, 0x06}, // 10dbm
        {0x1C, 0x62, 0x0C}, // 15dbm
        {0x1D, 0x8A, 0x18}  // 20dbm
};

#define FIFO_TH (CMT2300_FIFO_SIZE / 2)

/**
 * @brief Construct a new Cmt2300a_tranceiver manual switch antenna
 * CMT2300A IO1 and IO2 for tx/rx done and tx/rx fifo threshold interrupt
 * CMT2300A IO3 for DOUT
 * @param _cmt2300a cmt2300a object pointer
 * @param buff_size receive data buffer size
 * @param _int interrupt gpios
 * gpio[0] - gpio1
 * gpio[1] - gpio2
 * @param _ant_sw antenna switch gpios
 * gpio[0] - sw1
 * gpio[1] - sw2 (if needed)
 * @param _tx_timeout send data timeout
 */
Cmt2300a_tranceiver::Cmt2300a_tranceiver(Cmt2300a *_cmt2300a, unsigned int buff_size,
                                         vector<Gpio_if *> &_int, bool _auto_antenna_sw,
                                         Cmt2300a_antenna_sw *_ant_sw, unsigned char _tx_power, unsigned int _tx_timeout)
    : Double_buffered_comm(buff_size)
{
  cmt2300a = _cmt2300a;
  tx_timeout = _tx_timeout;
  rx_done_callback = NULL;
  state = CMT_STATE_IDLE;

  if (_int.size() == 1)
  {
    gpio2 = _int[0];
  }
  else if (_int.size() == 2)
  {
    gpio1 = _int[0];
    gpio2 = _int[1];
  }
  else
  {
    gpio1 = NULL;
    gpio2 = NULL;
  }

  ant_sw = _ant_sw;

  auto_antenna_sw = _auto_antenna_sw;

  hopping_freq_num = 0;

  if (_tx_power >= CMT2300_TX_POWER_LEVELS)
  {
    _tx_power = CMT2300_TX_POWER_LEVELS - 1;
  }

  init();

  set_tx_power(_tx_power);
}

Cmt2300a_tranceiver::~Cmt2300a_tranceiver()
{
  if (cmt2300a != NULL)
  {
    delete cmt2300a;
    cmt2300a = NULL;
  }
}
/**
 * @brief config cmt2300 communication gpio and registers
 * 
 */
void Cmt2300a_tranceiver::init(void)
{
  unsigned char tmp;

  cmt2300a->init();

  // Config registers
  cmt2300a->config_reg_bank(CMT2300A_CMT_BANK_ADDR, g_cmt2300aCmtBank, CMT2300A_CMT_BANK_SIZE);
  #if(CMT2300A_SLP_RX)
    cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank_LowPower, CMT2300A_SYSTEM_BANK_SIZE);
  #else
    cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank, CMT2300A_SYSTEM_BANK_SIZE);
  #endif
  cmt2300a->config_reg_bank(CMT2300A_FREQUENCY_BANK_ADDR, g_cmt2300aFrequencyBank, CMT2300A_FREQUENCY_BANK_SIZE);
  cmt2300a->config_reg_bank(CMT2300A_DATA_RATE_BANK_ADDR, g_cmt2300aDataRateBank, CMT2300A_DATA_RATE_BANK_SIZE);
  cmt2300a->config_reg_bank(CMT2300A_BASEBAND_BANK_ADDR, g_cmt2300aBasebandBank, CMT2300A_BASEBAND_BANK_SIZE);
  cmt2300a->config_reg_bank(CMT2300A_TX_BANK_ADDR, g_cmt2300aTxBank, CMT2300A_TX_BANK_SIZE);

  // xosc_aac_code[2:0] = 2
  tmp = (~0x07) & cmt2300a->read_reg(CMT2300A_CUS_CMT10);
  cmt2300a->write_reg(CMT2300A_CUS_CMT10, tmp | 0x02);

  config();
}

/**
 * @brief config cmt2300 interrupt gpios, interrupt trigger, fifo and so on 
 * 
 */
void Cmt2300a_tranceiver::config(void)
{

  if (auto_antenna_sw)
  {
    // If you enable antenna switch, GPIO1/GPIO2 will output RX_ACTIVE/TX_ACTIVE,
    // and it can't output INT1/INT2 via GPIO1/GPIO2
    cmt2300a->ant_swtich_enable(0);
    cmt2300a->config_gpio(CMT2300A_GPIO3_SEL_INT2);
  }
  else
  {
    // config gpios
    cmt2300a->config_gpio(
        CMT2300A_GPIO1_SEL_INT1 | // INT1 -> GPIO1
        CMT2300A_GPIO2_SEL_INT2   // INT2 -> GPIO2
    );
  }

  // Enable interrupt
  cmt2300a->interrupt_enable(
      CMT2300A_MASK_TX_DONE_EN | CMT2300A_MASK_PKT_DONE_EN | CMT2300A_MASK_SYNC_OK_EN);

  // Config gpio interrupt, default receive state
  set_gpio_rev_int();

  // low frequency SOC switch
  #if(CMT2300A_SLP_RX)
    cmt2300a->fosc_enable(false);
  #else
    cmt2300a->fosc_enable(true);
  #endif

  // Use a single 64-byte FIFO for either Tx or Rx
  cmt2300a->fifo_merge_enable(true);

  // fifo threshold
  cmt2300a->set_fifo_thr(FIFO_TH);

  // set hopping step
  cmt2300a->set_freq_step(HOPPING_HZ_TO_STEP_NUM(CMT_HOPPING_STEP_HZ));

  // set hopping inital afc register value
  cmt2300a->set_afc_overflow_thr(Hopping_afc_val_list[0]);

  // Go to sleep for configuration to take effect
  #if(CMT2300A_SLP_RX == 0)
    cmt2300a->to_sleep();
  #endif
}

/**
 * @brief send data done callback
 * 
 * @param func callback function
 */
void Cmt2300a_tranceiver::set_tx_done_callback(cmt_tx_done_callback func)
{
  tx_done_callback = func;
}

/**
 * @brief receive data done callback
 * 
 * @param func callback function
 */
void Cmt2300a_tranceiver::set_rx_done_callback(cmt_rx_done_callback func)
{
  rx_done_callback = func;
}

bool Cmt2300a_tranceiver::set_hopping_freq(unsigned char freq_num)
{
  if (freq_num > (CMT_HOPPING_CNT - 1))
  {
    freq_num = CMT_HOPPING_CNT - 1;
  }

  hopping_freq_num = freq_num;

  cmt2300a->to_stby();

  // turn duty cycle off and config registers to normal mode
  #if(CMT2300A_SLP_RX)
  cmt2300a->dutycycle_enable(false);
  cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank, CMT2300A_SYSTEM_BANK_SIZE);
  cmt2300a->write_reg(0x35, 0x01);
  #endif

  cmt2300a->set_afc_overflow_thr(Hopping_afc_val_list[freq_num]);

  cmt2300a->set_freq_channel(freq_num);

  // config registers to sleep states
  #if(CMT2300A_SLP_RX)
  cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank_LowPower, CMT2300A_SYSTEM_BANK_SIZE);
  cmt2300a->write_reg(0x35, 0x012);
  #endif

  return true;
}

/**
 * @brief set tx power 
 * 
 * @param tx_power power level from 0 ~ 6
 */
void Cmt2300a_tranceiver::set_tx_power(unsigned char tx_power)
{
  if (tx_power >= CMT2300_TX_POWER_LEVELS)
  {
    tx_power = CMT2300_TX_POWER_LEVELS - 1;
  }

  cmt2300a->to_stby();

  cmt2300a->write_reg(CMT2300A_CMT_BANK_ADDR + 3, Tx_power_list[tx_power][0]);
  cmt2300a->write_reg(CMT2300A_TX_BANK_ADDR + 7, Tx_power_list[tx_power][1]);
  cmt2300a->write_reg(CMT2300A_TX_BANK_ADDR + 8, Tx_power_list[tx_power][2]);
}

/**
 * @brief send data
 * 
 * @param data data pointer
 * @param data_len data length
 * @return true send success
 * @return false send failed
 */
bool Cmt2300a_tranceiver::send(unsigned char *data, unsigned int data_len)
{
  if (data == NULL || data_len == 0)
  {
    return false;
  }

  if (data_len > CMT2300_SEND_DATA_CNT_MAX)
  {
    data_len = CMT2300_SEND_DATA_CNT_MAX;
  }

  unsigned int send_len = (data_len < CMT2300_FIFO_SIZE) ? data_len : CMT2300_FIFO_SIZE;
  unsigned int send_delay = 0;

  // check signal noise
//  check_no_signal_noise(CMT_30K_RATE_SEND_TIME_MAX);

  // go standby
  cmt2300a->to_stby();

  // turn duty cycle off and config registers to normal mode
  #if(CMT2300A_SLP_RX)
  cmt2300a->dutycycle_enable(false);
  cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank, CMT2300A_SYSTEM_BANK_SIZE);
  cmt2300a->write_reg(0x35, 0x01);
  #endif

  // set gpio interrupt
  set_gpio_send_int();
  cmt2300a->clear_interrupt();
  cmt2300a->clear_tx_fifo();

  // set payload size
  cmt2300a->set_payload_length(data_len);
  cmt2300a->write_fifo_enable();

  // write fifo
  cmt2300a->write_fifo(data, send_len);

  // set atenna send status
  set_ant_send();

  // send data
  if (!cmt2300a->to_tx())
  {
    cmt2300a->to_stby();
    cmt2300a->clear_interrupt();
    cmt2300a->clear_tx_fifo();

    // config registers to sleep states
    #if(CMT2300A_SLP_RX)
    cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank_LowPower, CMT2300A_SYSTEM_BANK_SIZE);
    cmt2300a->write_reg(0x35, 0x012);
    #endif

    cmt2300a->to_sleep();
    state = CMT_STATE_ERROR;

    return false;
  }

  state = CMT_STATE_TX_WAIT;

  while (1)
  {
    // tx done
    if (tx_done_int_trigger())
    {
      cmt2300a->to_stby();
      cmt2300a->clear_tx_fifo();
      cmt2300a->clear_interrupt();

      // config registers to sleep states
      #if(CMT2300A_SLP_RX)
      cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank_LowPower, CMT2300A_SYSTEM_BANK_SIZE);
      cmt2300a->write_reg(0x35, 0x012);
      #endif

      state = CMT_STATE_TX_DONE;

      if (tx_done_callback != NULL)
      {
        tx_done_callback();
      }

      // restart receive data
      start_rev_it();

      break;
    }

    // tx fifo threshold
    if ((data_len > send_len) && (tx_fifo_thr_int_trigger()))
    {
      if (data_len - send_len > FIFO_TH)
      {
        cmt2300a->write_fifo(&data[send_len], FIFO_TH);
        send_len += FIFO_TH;
      }
      else
      {
        cmt2300a->write_fifo(&data[send_len], data_len - send_len);
        send_len = data_len;
      }
    }

    DELAY_MS(1);
    send_delay++;
    if (send_delay > tx_timeout)
    {
      cmt2300a->to_stby();
      cmt2300a->clear_interrupt();
      cmt2300a->clear_tx_fifo();

      // config registers to sleep states
      #if(CMT2300A_SLP_RX)
      cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank_LowPower, CMT2300A_SYSTEM_BANK_SIZE);
      cmt2300a->write_reg(0x35, 0x012);
      #endif

      cmt2300a->to_sleep();
      state = CMT_STATE_ERROR;
      return false;
    }
  }

  return true;
}

/**
 * @brief read data from buffer
 * 
 * @param data read out data buffer
 * @param data_len read out data length
 * @return unsigned int actually read data length
 */
unsigned int Cmt2300a_tranceiver::read(unsigned char *data, unsigned int data_len)
{
  unsigned int read_data_len = data_len >= data_buffer->buffer_used() ? data_buffer->buffer_used() : data_len;
  return data_buffer->read_out(data, read_data_len);
}

/**
 * @brief read all buffer data
 * 
 * @param data data pointer
 * @return unsigned int actually read data length
 */
unsigned int Cmt2300a_tranceiver::read_all(unsigned char *data)
{
  return data_buffer->read_all(data);
}

/**
 * @brief receive data process 
 * 通过调用此函数，查询是否接收到数据，并判断数据是否接收完成
 */
void Cmt2300a_tranceiver::rx_process(void)
{
  if (state != CMT_STATE_RX_WAIT)
  {
    return;
  }

  unsigned int rx_len = 0;
  unsigned int data_len = 0;
  do
  {
    // rx threshold
    if (rx_fifo_thr_int_trigger())
    {
      cmt2300a->read_fifo(tranceiver_buffer, FIFO_TH);

      if (data_len == 0)
      {
        // first byte of data is length of data to be receied
        data_len = tranceiver_buffer[0];
        data_buffer->write(tranceiver_buffer + 1, FIFO_TH - 1);
        rx_len += FIFO_TH - 1;
      }
      else
      {
        data_buffer->write(tranceiver_buffer, FIFO_TH);
        rx_len += FIFO_TH;
      }
    }

    // rx done
    if (rx_done_int_trigger())
    {
      cmt2300a->to_stby();

      if (rx_len == 0)
      {
        cmt2300a->read_fifo(tranceiver_buffer, 1);
        data_len = tranceiver_buffer[0];
      }

      if ((data_len > rx_len) && (data_len - rx_len <= FIFO_TH))
      {
        cmt2300a->read_fifo(tranceiver_buffer, data_len - rx_len);
        data_buffer->write(tranceiver_buffer, data_len - rx_len);
      }

      rx_len = data_len;

      cmt2300a->clear_rx_fifo();
      cmt2300a->clear_interrupt();

      #if(CMT2300A_SLP_RX == 0)
        cmt2300a->to_sleep();
      #endif
      
      state = CMT_STATE_RX_DONE;

      data_buffer->buffer_switch();

      // rx done callback
      if (rx_done_callback != NULL)
      {
        rx_done_callback();
      }

      return;
    }

  } while (rx_len);
}

bool Cmt2300a_tranceiver::set_sync_word(int sync_word, unsigned char word_size)
{
  if (word_size > SYNC_WORD_SIZE_MAX)
  {
    word_size = SYNC_WORD_SIZE_MAX;
  }
  else if (word_size < SYNC_WORD_SIZE_MIN)
  {
    word_size = SYNC_WORD_SIZE_MIN;
  }

  cmt2300a->to_stby();

  // turn duty cycle off and config registers to normal mode
  #if(CMT2300A_SLP_RX)
  cmt2300a->dutycycle_enable(false);
  cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank, CMT2300A_SYSTEM_BANK_SIZE);
  cmt2300a->write_reg(0x35, 0x01);
  #endif

  unsigned char word_size_reg = sync_word_size_to_reg_val(word_size);

  // set sync word size register
  // read out register value before write
  // because sync word size only use bit1~bit3
  unsigned char size_reg_val = cmt2300a->read_reg(CMT2300A_BASEBAND_BANK_ADDR + 4);
  size_reg_val = size_reg_val | word_size_reg;
  cmt2300a->write_reg(CMT2300A_BASEBAND_BANK_ADDR + 4, size_reg_val);
  unsigned char *reg_val = (unsigned char *)&sync_word;

  // set sync word value register
  for (int i = word_size - 1; i >= 0; i--)
  {
    cmt2300a->write_reg(CMT2300A_BASEBAND_BANK_ADDR + 9 + i, reg_val[i]);
  }

  // config registers to sleep states
  #if(CMT2300A_SLP_RX)
  cmt2300a->config_reg_bank(CMT2300A_SYSTEM_BANK_ADDR, g_cmt2300aSystemBank_LowPower, CMT2300A_SYSTEM_BANK_SIZE);
  cmt2300a->write_reg(0x35, 0x012);
  #endif
      
  return true;
}

unsigned char Cmt2300a_tranceiver::sync_word_size_to_reg_val(unsigned char word_size)
{
  unsigned char ret = 6;

  switch (word_size)
  {
  case 1:
    ret = 0;
    break;
  case 2:
    ret = 2;
    break;
  case 3:
    ret = 4;
    break;
  case 4:
    ret = 6;
    break;
  default:
    ret = 6;
    break;
  }

  return ret;
}

/**
 * @brief 将CMT2300A中断寄存器设置为发送中断
 * 
 */
void Cmt2300a_tranceiver::set_gpio_send_int(void)
{
  cmt2300a->config_interrupt(
      CMT2300A_INT_SEL_SYNC_OK,   // Config INT1 as SYNC_OK interrupt
      CMT2300A_INT_SEL_TX_FIFO_TH // Config INT2 as TX_FIFO_TH interrupt
  );
}

/**
 * @brief 将CMT2300A中断寄存器设置为接收中断
 * 
 */
void Cmt2300a_tranceiver::set_gpio_rev_int(void)
{
  cmt2300a->config_interrupt(
      CMT2300A_INT_SEL_SYNC_OK,   // Config INT1 as SYNC_OK interrupt
      CMT2300A_INT_SEL_RX_FIFO_TH // Config INT2 as RX_FIFO_TH interrupt
  );
}

/**
 * @brief switch antenna send status
 * 
 */
bool Cmt2300a_tranceiver::set_ant_send(void)
{
  if (auto_antenna_sw || (ant_sw == NULL))
  {
    return false;
  }

  return ant_sw->set_send_state();
}

/**
 * @brief switch antenna receive status
 * 
 */
bool Cmt2300a_tranceiver::set_ant_rev(void)
{
  if (auto_antenna_sw || (ant_sw == NULL))
  {
    return false;
  }

  return ant_sw->set_rev_state();
}

/**
 * @brief start receive data
 * 
 * @return true switch to receive status ok
 * @return false switch to receive status failed
 */
bool Cmt2300a_tranceiver::start_rev_it(void)
{
  cmt2300a->to_stby();
  set_gpio_rev_int();
  cmt2300a->clear_interrupt();

  cmt2300a->read_fifo_enable();
  cmt2300a->clear_rx_fifo();

  // set antenna status receive
  set_ant_rev();

  #if(CMT2300A_SLP_RX)
  if (cmt2300a->to_sleep())
  #else
  if (cmt2300a->to_rx())
  #endif
  {
    state = CMT_STATE_RX_WAIT;
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief tx done interrupt trigger
 * 
 * @return true triggered
 * @return false not triggered
 */
bool Cmt2300a_tranceiver::tx_done_int_trigger(void)
{
  return ((cmt2300a->read_reg(CMT2300A_CUS_INT_CLR1) & CMT2300A_MASK_TX_DONE_FLG) == CMT2300A_MASK_TX_DONE_FLG);
}

/**
 * @brief rx done interrupt trigger
 * 
 * @return true triggered
 * @return false not triggered
 */
bool Cmt2300a_tranceiver::rx_done_int_trigger(void)
{
  return ((cmt2300a->read_reg(CMT2300A_CUS_INT_FLAG) & CMT2300A_MASK_PKT_OK_FLG) == CMT2300A_MASK_PKT_OK_FLG);
}

/**
 * @brief tx fifo threshold interrupt trigger
 * 
 * @return true triggered
 * @return false not triggered
 */
bool Cmt2300a_tranceiver::tx_fifo_thr_int_trigger(void)
{
  if (gpio2 == NULL)
  {
    return false;
  }
  return (gpio2->read() == GPIO_LOW);
}

/**
 * @brief rx fifo threshold interrupt trigger
 * 
 * @return true triggered
 * @return false not triggered
 */
bool Cmt2300a_tranceiver::rx_fifo_thr_int_trigger(void)
{
  if (gpio2 == NULL)
  {
    return false;
  }
  return (gpio2->read() == GPIO_HI);
}

/**
 * @brief received data handle(NOT USE)
 * 
 * @param data data pointer
 * @param data_len data length
 * @return true process ok
 * @return false process failed
 */
bool Cmt2300a_tranceiver::rev_data_handle(unsigned char *data, unsigned int data_len)
{
  return false;
}

/**
 * @brief 检查空中是否有信号干扰, 一般用于发送前,防止同频段两个从机同时发射的情况.
 * 
 * @param timeout 检查的时间,如果无干扰信号,则立即退出.
 * @return true 无干扰信号存在
 * @return false 持续时间内一直有干扰信号存在
 */
bool Cmt2300a_tranceiver::check_no_signal_noise(int timeout)
{
  bool ret = false;
  int delay = timeout;

  // to rx mode
  cmt2300a->to_rx();

  while(delay)
  {
    // no noise
    if(cmt2300a->get_rssi_dbm() < CMT_NOISE_THR)
    {
      ret = true;
      break;
    }
    
    delay--;
    DELAY_MS(1);
  }

  return ret;
}
