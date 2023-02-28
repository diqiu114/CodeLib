#include "si4432.h"
#include "string.h"

Si4432::Si4432(SPI_HandleTypeDef *_hspi, Si4432_setting *_settings)
{
  hspi = _hspi;
  memset((unsigned char *)&settings, 0, sizeof(settings));
  nss_port = NULL;
  nss_pin = 0;
  sdn_port = NULL;
  sdn_pin = 0;
  irq_port = NULL;
  irq_pin = 0;
  
  if (_settings == NULL) // use default values
  {
    settings.carrier_freq = FREQ_435_5;
    settings.data_rate = DATA_RATE_9_6_K;
    settings.freq_deviation = DEVI_FREQ_35K;
    settings.modualation = MODULATION_GFSK;
    settings.tx_pwr = TX_POWER_20DB;
    settings.data_len_max = DATA_LEN_MAX;

    // copy default header
    memcpy(settings.header, Default_header, sizeof(Default_header));
  }
  else
  {
    memcpy((unsigned char *)&settings, (unsigned char *)_settings, sizeof(settings));
  }
}

bool Si4432::init(void)
{
  bool ret = true;

  // power on delay
  DELAY_MS(2000);

  ret = ret && software_reset();
  ret = ret && to_ready_mode();
  ret = ret && set_GPIO();
  ret = ret && set_freq(settings.carrier_freq);
  ret = ret && set_data_rate(settings.data_rate);
  ret = ret && set_data_fmt(settings.header);
  ret = ret && set_tx_power(settings.tx_pwr);
  ret = ret && set_freq_deviation(settings.freq_deviation);
  ret = ret && set_modulation(settings.modualation);

  ret = ret && to_rx_mode();

  // gpio hi/low, test si4432 driver is ok
  // write_reg(0x0d, 0xfd);
  // write_reg(0x0d, 0xff);
  // write_reg(0x0d, 0xfd);
  // write_reg(0x0d, 0xff);

  return ret;
}

bool Si4432::switch_mode(Si4432_mode mode)
{
  bool ret = true;
  switch (mode)
  {
  case MODE_RDY:
    ret = to_ready_mode();
    break;
  case MODE_TX:
    ret = to_tx_mode();
    break;
  case MODE_RX:
    ret = to_rx_mode();
    break;
  }

  return ret;
}

Si4432_status Si4432::get_status(void)
{
  Si4432_status ret = SI4432_NO_INT;
  // interrupts occur
  if (irq())
  {
    // read interrupts and clear them
    unsigned char int_status1 = read_reg(SI4432_REG_ISTATUS1);
    unsigned char int_status2 = read_reg(SI4432_REG_ISTATUS2);

    // bit 2 set means rx done, bit 3 set means tx done
    if ((int_status1 & 0x02) == 0x02)
    {
      ret = SI4432_RX_DONE;
    }
    else if ((int_status1 & 0x04) == 0x04)
    {
      ret = SI4432_TX_DONE;
    }
  }
  return ret;
}

unsigned int Si4432::read_data(unsigned char *data)
{
  unsigned char data_cnt = read_reg(SI4432_REG_PACK_LEN);

  nss_hi();
  nss_low();

  DELAY_MS(1);

  send_address(SI4432_REG_FIFO, false);

  for (int i = 0; i < data_cnt; i++)
  {
    data[i] = spi_read();
  }

  DELAY_MS(1);

  nss_low();

  to_rx_mode();

  return data_cnt;
}

bool Si4432::send_data(unsigned char *data, unsigned int data_len)
{
  bool ret = true;

  to_ready_mode();

  clear_fifo();

  // set send length
  ret = ret && write_reg(SI4432_REG_PACK_LEN, data_len);

  nss_hi();
  nss_low();

  DELAY_MS(1);

  // send data
  ret = ret && send_address(SI4432_REG_FIFO);

  ret = ret && spi_write(data, data_len);

  DELAY_MS(1);

  nss_low();

  to_tx_mode();

  return ret;
}

void Si4432::set_nss_pin(GPIO_TypeDef *_port, unsigned short _pin)
{
  nss_port = _port;
  nss_pin = _pin;
}

void Si4432::set_sdn_pin(GPIO_TypeDef *_port, unsigned short _pin)
{
  sdn_port = _port;
  sdn_pin = _pin;
}

void Si4432::set_irq_pin(GPIO_TypeDef *_port, unsigned short _pin)
{
  irq_port = _port;
  irq_pin = _pin;
}

void Si4432::set_frame_header(Si4432_frame_header _header)
{
  memcpy(settings.header, _header, sizeof(_header));
}

bool Si4432::set_GPIO(void)
{
  bool ret = true;

  ret = ret && write_reg(SI4432_REG_GPIO0_CFG, 0xf4); // gpio 0 for received data output
  ret = ret && write_reg(SI4432_REG_GPIO1_CFG, 0xef); // gpio 1 TX/RX data clk output
  ret = ret && write_reg(SI4432_REG_GPIO2_CFG, 0x00); // gpio 2 micro-controller clk output

  return ret;
}

bool Si4432::set_freq(unsigned char idx)
{
  if (idx >= FREQ_MAX)
  {
    return false;
  }

  bool ret = true;

  // frequency setting
  ret = ret && write_reg(SI4432_REG_FREQ_OFFSET1, 0x00);
  ret = ret && write_reg(SI4432_REG_FREQ_OFFSET2, 0x00);

  // frequency hopping
  ret = ret && write_reg(SI4432_REG_FREQ_HOPPING_SEL, 0x00);
  ret = ret && write_reg(SI4432_REG_FREQ_HOPPING_STEP_SIZE, 0x00);

  // set frequency
  ret = ret && write_reg(SI4432_REG_FREQ_BW_SEL, Freq_table[idx].freq_bw_sel);
  ret = ret && write_reg(SI4432_REG_CARRY_FREQ1, Freq_table[idx].nomial_carrier1);
  ret = ret && write_reg(SI4432_REG_CARRY_FREQ2, Freq_table[idx].nomial_carriew2);

  return ret;
}

bool Si4432::set_data_rate(unsigned char idx)
{
  if (idx >= DATA_RATE_MAX)
  {
    return false;
  }

  bool ret = true;

  // set tx data rate
  ret = ret && write_reg(SI4432_REG_TX_RATE1, Data_rate_table[idx].tx_rate1);
  ret = ret && write_reg(SI4432_REG_TX_RATE0, Data_rate_table[idx].tx_rate0);

  // set rx data rate
  ret = ret && write_reg(SI4432_REG_IF_BW, Data_rate_table[idx].if_bw);
  ret = ret && write_reg(SI4432_REG_AFC, Data_rate_table[idx].afc);
  ret = ret && write_reg(SI4432_REG_CLK_REC_RATIO, Data_rate_table[idx].clk_rec_ratio);
  ret = ret && write_reg(SI4432_REG_CLK_REC_OFFSET2, Data_rate_table[idx].clk_rec_offset2);
  ret = ret && write_reg(SI4432_REG_CLK_REC_OFFSET1, Data_rate_table[idx].clk_rec_offset1);
  ret = ret && write_reg(SI4432_REG_CLK_REC_OFFSET0, Data_rate_table[idx].clk_rec_offset0);
  ret = ret && write_reg(SI4432_REG_CLK_REC_GAIN1, Data_rate_table[idx].clk_rec_gain1);
  ret = ret && write_reg(SI4432_REG_CLK_REC_GAIN0, Data_rate_table[idx].clk_rec_gain0);
  ret = ret && write_reg(SI4432_REG_AFC_LIMIT, Data_rate_table[idx].afc_limit);
  ret = ret && write_reg(SI4432_REG_MODULATION_CTRL1, Data_rate_table[idx].modulation_ctrl1);

  return ret;
}

bool Si4432::set_data_fmt(Si4432_frame_header &_header)
{
  bool ret = true;

  // data format setting
  ret = ret && write_reg(SI4432_REG_DATA_AC, Frame_fmt_talbe[0]);
  ret = ret && write_reg(SI4432_REG_HEADER_CTRL1, Frame_fmt_talbe[1]);
  ret = ret && write_reg(SI4432_REG_HEADER_CTRL2, Frame_fmt_talbe[2]);
  ret = ret && write_reg(SI4432_REG_PREAM_LEN, Frame_fmt_talbe[3]);
  ret = ret && write_reg(SI4432_REG_SYNC_WORD3, Frame_fmt_talbe[4]);
  ret = ret && write_reg(SI4432_REG_SYNC_WORD2, Frame_fmt_talbe[5]);
  ret = ret && write_reg(SI4432_REG_SYNC_WORD1, Frame_fmt_talbe[6]);
  ret = ret && write_reg(SI4432_REG_SYNC_WORD0, Frame_fmt_talbe[7]);
  ret = ret && write_reg(SI4432_REG_PREAM_DC, Frame_fmt_talbe[8]);
  ret = ret && write_reg(SI4432_REG_HEADER3_EN, Frame_fmt_talbe[9]);
  ret = ret && write_reg(SI4432_REG_HEADER2_EN, Frame_fmt_talbe[10]);
  ret = ret && write_reg(SI4432_REG_HEADER1_EN, Frame_fmt_talbe[11]);
  ret = ret && write_reg(SI4432_REG_HEADER0_EN, Frame_fmt_talbe[12]);

  // max data length setting
  ret = ret && write_reg(SI4432_REG_PACK_LEN, settings.data_len_max);

  // header setting
  ret = ret && write_reg(SI4432_REG_TRANS_HEADER3, _header[0]);
  ret = ret && write_reg(SI4432_REG_TRANS_HEADER2, _header[1]);
  ret = ret && write_reg(SI4432_REG_TRANS_HEADER1, _header[2]);
  ret = ret && write_reg(SI4432_REG_TRANS_HEADER0, _header[3]);
  ret = ret && write_reg(SI4432_REG_CHK_HEADER3, _header[0]);
  ret = ret && write_reg(SI4432_REG_CHK_HEADER2, _header[1]);
  ret = ret && write_reg(SI4432_REG_CHK_HEADER1, _header[2]);
  ret = ret && write_reg(SI4432_REG_CHK_HEADER0, _header[3]);

  return ret;
}

bool Si4432::set_tx_power(unsigned char idx)
{
  if (idx >= TX_POWER_MAX)
  {
    return false;
  }

  // set tx power
  return write_reg(SI4432_REG_TX_POWER, Tx_power_table[idx]);
}

bool Si4432::set_freq_deviation(unsigned char idx)
{
  if (idx >= DEVI_FREQ_MAX)
  {
    return false;
  }

  // set deviation frequency
  return write_reg(SI4432_REG_FREQ_DEVIATION, Devi_freq_table[idx]);
}

bool Si4432::set_modulation(unsigned char idx)
{
  if (idx >= MODULATION_MAX)
  {
    return false;
  }

  // set modulation mode
  return write_reg(SI4432_REG_MODULATION_CTRL2, Modulation_table[idx]);
}

void Si4432::nss_hi(void)
{
  HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
}

void Si4432::nss_low(void)
{
  HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_RESET);
}

void Si4432::sdn_hi(void)
{
  HAL_GPIO_WritePin(sdn_port, sdn_pin, GPIO_PIN_SET);
}

void Si4432::sdn_low(void)
{
  HAL_GPIO_WritePin(sdn_port, sdn_pin, GPIO_PIN_RESET);
}

bool Si4432::irq(void)
{
  if (HAL_GPIO_ReadPin(irq_port, irq_pin) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Si4432::write_reg(unsigned char addr, unsigned char val)
{
  bool ret = false;

  nss_hi();
  nss_low();

  DELAY_MS(1);

  send_address(addr);
  ret = spi_write(&val, sizeof(val));

  DELAY_MS(1);
  nss_hi();

  return ret;
}

unsigned char Si4432::read_reg(unsigned char addr)
{
  unsigned ret = 0;
  nss_hi();
  nss_low();

  DELAY_MS(1);

  send_address(addr, false);
  ret = spi_read();

  DELAY_MS(1);

  nss_hi();

  return ret;
}

bool Si4432::send_address(unsigned char addr, bool write)
{
  unsigned char data = 0;
  if (write)
  {
    data = addr | 0x80;
  }
  else
  {
    data = addr & 0x7F;
  }

  return spi_write(&data, sizeof(data));
}

unsigned char Si4432::spi_read(void)
{
  unsigned char ret = 0;
  unsigned char dummy = 0xFF;

  HAL_SPI_TransmitReceive(hspi, &dummy, &ret, 1, SI4432_SPI_TIMEOUT);

  return ret;
}

bool Si4432::spi_write(unsigned char *data, unsigned int data_len)
{
  bool ret = true;
  for (int i = 0; i < data_len; i++)
  {
    if (HAL_SPI_Transmit(hspi, &data[i], 1, SI4432_SPI_TIMEOUT) != HAL_OK)
    {
      ret = false;
    }
  }

  return ret;
}

bool Si4432::swith_ant(bool tx)
{
  bool ret = true;

  if (tx)
  {
    ret = ret && write_reg(SI4432_REG_GPIO0_CFG, 0xfd); //gpio 0  hi
    ret = ret && write_reg(SI4432_REG_GPIO1_CFG, 0xff); //gpio 1  low
  }
  else
  {
    ret = ret && write_reg(SI4432_REG_GPIO0_CFG, 0xff); //gpio 0  low
    ret = ret && write_reg(SI4432_REG_GPIO1_CFG, 0xfd); //gpio 1  hi
  }

  return ret;
}

bool Si4432::clear_fifo(void)
{
  bool ret = true;

  ret = ret && write_reg(SI4432_REG_OFC2, 0x03);
  ret = ret && write_reg(SI4432_REG_OFC2, 0x00);

  return ret;
}

bool Si4432::to_tx_mode(void)
{
  bool ret = true;

  ret = ret && write_reg(SI4432_REG_OFC1, 0x09);
  ret = ret && write_reg(SI4432_REG_IEN1, 0x06);

  // switch antenna to tx mode
  ret = ret && swith_ant();

  return ret;
}

bool Si4432::to_rx_mode(void)
{
  bool ret = true;

  // back to ready mode and clear fifo
  ret = ret && to_ready_mode();
  ret = ret && clear_fifo();

  ret = ret && write_reg(SI4432_REG_IEN2, 0x80);
  ret = ret && write_reg(SI4432_REG_OFC1, 0x05);
  ret = ret && write_reg(SI4432_REG_IEN1, 0x06);

  // swithc antenna to rx mode
  ret = ret && swith_ant(false);

  return ret;
}

bool Si4432::to_ready_mode(void)
{
  bool ret = true;

  // clear interrupts
  read_reg(SI4432_REG_ISTATUS1);
  read_reg(SI4432_REG_ISTATUS2);

  // switch to ready mode
  ret = ret && write_reg(SI4432_REG_IEN1, 0x00);
  ret = ret && write_reg(SI4432_REG_IEN2, 0x00);
  ret = ret && write_reg(SI4432_REG_OFC1, 0x01);

  return ret;
}

bool Si4432::software_reset(void)
{
  unsigned delay_max = SI4432_SOFT_RESET_DELAY;
  unsigned delay = 0;

  write_reg(SI4432_REG_OFC1, 0x80);

  while (!irq())
  {
    ++delay;
    if (delay >= delay_max)
    {
      break;
    }

    DELAY_MS(1);
  }

  if (delay >= delay_max)
  {
    return false;
  }

  // clear interrupts
  read_reg(SI4432_REG_ISTATUS1);
  read_reg(SI4432_REG_ISTATUS2);

  return true;
}

bool Si4432::hardware_reset(void)
{
  sdn_hi();
  DELAY_MS(10);
  sdn_low();

  unsigned delay_max = SI4432_HW_RESET_DELAY;
  unsigned delay = 0;

  while (!irq())
  {
    ++delay;
    if (delay >= delay_max)
    {
      break;
    }

    DELAY_MS(1);
  }

  if (delay >= delay_max)
  {
    return false;
  }

  DELAY_MS(SI4432_POR_DELAY);

  // clear interrupts
  read_reg(SI4432_REG_ISTATUS1);
  read_reg(SI4432_REG_ISTATUS2);

  return true;
}

Si4432::~Si4432()
{
}
