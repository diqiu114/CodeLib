/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      SI4432 Sub-G无线通讯驱动
*
* 版本: 
* V1.0 2019-08-26 初始程序编写  
***********************************************************/
#ifndef _SI4432_H_
#define _SI4432_H_

#include <stdbool.h>
#include "main.h"
#include "modules_def.h"

// si4432 carrier frequency settings
typedef enum _tag_si4432_freq_
{
  FREQ_408,
  FREQ_408_5,
  FREQ_409,
  FREQ_409_5,
  FREQ_410,
  FREQ_410_5,
  FREQ_411,
  FREQ_411_5,
  FREQ_412,
  FREQ_412_5,
  FREQ_413,
  FREQ_413_5,
  FREQ_414,
  FREQ_414_5,
  FREQ_415,
  FREQ_415_5,
  FREQ_416,
  FREQ_416_5,
  FREQ_417,
  FREQ_417_5,
  FREQ_418,
  FREQ_418_5,
  FREQ_419,
  FREQ_419_5,
  FREQ_420,
  FREQ_420_5,
  FREQ_421,
  FREQ_421_5,
  FREQ_422,
  FREQ_422_5,
  FREQ_423,
  FREQ_423_5,
  FREQ_424,
  FREQ_424_5,
  FREQ_425,
  FREQ_425_5,
  FREQ_426,
  FREQ_426_5,
  FREQ_427,
  FREQ_427_5,
  FREQ_428,
  FREQ_428_5,
  FREQ_429,
  FREQ_429_5,
  FREQ_430,
  FREQ_430_5,
  FREQ_431,
  FREQ_431_5,
  FREQ_432,
  FREQ_432_5,
  FREQ_433,
  FREQ_433_5,
  FREQ_434,
  FREQ_434_5,
  FREQ_435,
  FREQ_435_5,
  FREQ_436,
  FREQ_436_5,
  FREQ_437,
  FREQ_437_5,
  FREQ_438,
  FREQ_438_5,
  FREQ_439,
  FREQ_439_5,
  FREQ_440,
  FREQ_440_5,
  FREQ_441,
  FREQ_441_5,
  FREQ_442,
  FREQ_442_5,
  FREQ_443,
  FREQ_443_5,
  FREQ_444,
  FREQ_444_5,
  FREQ_445,
  FREQ_445_5,
  FREQ_446,
  FREQ_446_5,
  FREQ_447,
  FREQ_447_5,
  FREQ_448,
  FREQ_448_5,
  FREQ_449,
  FREQ_449_5,
  FREQ_450,
  FREQ_450_5,
  FREQ_451,
  FREQ_451_5,
  FREQ_452,
  FREQ_452_5,
  FREQ_453,
  FREQ_453_5,
  FREQ_454,
  FREQ_454_5,
  FREQ_455,
  FREQ_455_5,
  FREQ_456,
  FREQ_456_5,
  FREQ_457,
  FREQ_457_5,
  FREQ_MAX
} Si4432_freq;

typedef struct _freq_t_
{
  unsigned char freq_bw_sel;
  unsigned char nomial_carrier1;
  unsigned char nomial_carriew2;
} Freq_t;

const Freq_t Freq_table[FREQ_MAX] =
    {
        0x50, 0xC8, 0x00, //408M-1
        0x50, 0xD4, 0x80, //408.5M-2
        0x50, 0xE1, 0x00, //409M-3
        0x50, 0xED, 0x80, //409.5M-4
        0x51, 0x00, 0x00, //410M-5
        0x51, 0x0C, 0x80, //410.5M-6
        0x51, 0x19, 0x00, //411M-7
        0x51, 0x25, 0x80, //411.5M-8
        0x51, 0x32, 0x00, //412M-9
        0x51, 0x3e, 0x80, //412.5M-10

        0x51, 0x4B, 0x00, //413M-11
        0x51, 0x57, 0x80, //413.5M-12
        0x51, 0x64, 0x00, //414M-13
        0x51, 0x70, 0x80, //414.5M-14
        0x51, 0x7D, 0x00, //415M-15
        0x51, 0x89, 0x80, //415.5M-16
        0x51, 0x96, 0x00, //416M-17
        0x51, 0xA2, 0x80, //416.5M-18
        0x51, 0xAF, 0x00, //417M-19
        0x51, 0xBB, 0x80, //417.5M-20

        0x51, 0xC8, 0x00, //418M-21
        0x51, 0xD4, 0x80, //418.5M-22
        0x51, 0xE1, 0x00, //419M-23
        0x51, 0xED, 0x80, //419.5M-24
        0x52, 0x00, 0x00, //420M-25
        0x52, 0x0C, 0x80, //420.5M-26
        0x52, 0x19, 0x00, //421M-27
        0x52, 0x25, 0x80, //421.5M-28
        0x52, 0x32, 0x00, //422M-29
        0x52, 0x3E, 0x80, //422.5M-30

        0x52, 0x4B, 0x00, //423M-31
        0x52, 0x57, 0x80, //423.5M-32
        0x52, 0x64, 0x00, //424M-33
        0x52, 0x70, 0x80, //424.5M-34
        0x52, 0x7D, 0x00, //425M-35
        0x52, 0x89, 0x80, //425.5M-36
        0x52, 0x96, 0x00, //426M-37
        0x52, 0xA2, 0x80, //426.5M-38
        0x52, 0xAF, 0x00, //427M-39
        0x52, 0xBB, 0x80, //427.5M-40

        0x52, 0xC8, 0x00, //428M-41
        0x52, 0xD4, 0x80, //428.5M-42
        0x52, 0xE1, 0x00, //429M-43
        0x52, 0xED, 0x80, //429.5M-44
        0x53, 0x00, 0x00, //430M-45
        0x53, 0x0C, 0x80, //430.5M-46
        0x53, 0x19, 0x00, //431M-47
        0x53, 0x25, 0x80, //431.5M-48
        0x53, 0x32, 0x00, //432M-49
        0x53, 0x3E, 0x80, //432.5M-50

        0x53, 0x4B, 0x00, //433M-51
        0x53, 0x57, 0x80, //433.5M-52
        0x53, 0x64, 0x00, //434M-53
        0x53, 0x70, 0x80, //434.5M-54
        0x53, 0x7D, 0x00, //435M-55
        0x53, 0x89, 0x80, //435.5M-56
        0x53, 0x96, 0x00, //436M-57
        0x53, 0xA2, 0x80, //436.5M-58
        0x53, 0xAF, 0x00, //437M-59
        0x53, 0xBB, 0x80, //437.5M-60

        0x53, 0xC8, 0x00, //438M-61
        0x53, 0xD4, 0x80, //438.5M-62
        0x53, 0xE1, 0x00, //439M-63
        0x53, 0xED, 0x80, //439.5M-64
        0x54, 0x00, 0x00, //440M-65
        0x54, 0x0C, 0x80, //440.5M-66
        0x54, 0x19, 0x00, //441M-67
        0x54, 0x25, 0x80, //441.5M-68
        0x54, 0x32, 0x00, //442M-69
        0x54, 0x3E, 0x80, //442.5M-70

        0x54, 0x4B, 0x00, //443M-71
        0x54, 0x57, 0x80, //443.5M-72
        0x54, 0x64, 0x00, //444M-73
        0x54, 0x70, 0x80, //444.5M-74
        0x54, 0x7D, 0x00, //445M-75
        0x54, 0x89, 0x80, //445.5M-76
        0x54, 0x96, 0x00, //446M-77
        0x54, 0xA2, 0x80, //446.5M-78
        0x54, 0xAF, 0x00, //447M-79
        0x54, 0xBB, 0x80, //447.5M-80

        0x54, 0xC8, 0x00, //448M-81
        0x54, 0xD4, 0x80, //448.5M-82
        0x54, 0xE1, 0x00, //449M-83
        0x54, 0xED, 0x80, //449.5M-84
        0x55, 0x00, 0x00, //450M-85
        0x55, 0x0C, 0x80, //450.5M-86
        0x55, 0x19, 0x00, //451M-87
        0x55, 0x25, 0x80, //451.5M-88
        0x55, 0x32, 0x00, //452M-89
        0x55, 0x3E, 0x80, //452.5M-90

        0x55, 0x4B, 0x00, //453M-91
        0x55, 0x57, 0x80, //453.5M-92
        0x55, 0x64, 0x00, //454M-93
        0x55, 0x70, 0x80, //454.5M-94
        0x55, 0x7D, 0x00, //455M-95
        0x55, 0x89, 0x80, //455.5M-96
        0x55, 0x96, 0x00, //456M-97
        0x55, 0xA2, 0x80, //456.5M-98
        0x55, 0xAF, 0x00, //457M-99
        0x55, 0xBB, 0x80, //457.5M-100
};

// si4432 tx/rx data rate settings
typedef struct _tag_data_rate_
{
  unsigned char tx_rate1;
  unsigned char tx_rate0;
  unsigned char if_bw;
  unsigned char afc;
  unsigned char clk_rec_ratio;
  unsigned char clk_rec_offset2;
  unsigned char clk_rec_offset1;
  unsigned char clk_rec_offset0;
  unsigned char clk_rec_gain1;
  unsigned char clk_rec_gain0;
  unsigned char afc_limit;
  unsigned char modulation_ctrl1;
} Data_rate_t;

typedef enum _tag_si4432_data_rate_
{
  DATA_RATE_2_4_K,
  DATA_RATE_4_8_K,
  DATA_RATE_9_6_K,
  DATA_RATE_38_4_K,
  DATA_RATE_MAX
} Si4432_data_rate;

const Data_rate_t Data_rate_table[DATA_RATE_MAX] =
{
  //2.4kbps
  0x13, 0xa9, 0x1d, 0x40, 0x41, 0x60, 0x27, 0x52, 0x00, 0x06, 0x1e, 0x20,
  //4.8kbps
  0x27, 0x52, 0x1d, 0x40, 0xa1, 0x20, 0x4e, 0xa5, 0x00, 0x13, 0x1e, 0x20,
  //9.6kbps
  0x4e, 0xa5, 0x1e, 0x40, 0xd0, 0x00, 0x9d, 0x49, 0x00, 0x45, 0x20, 0x20,
  //38.4kbps
  0x09, 0xd5, 0xad, 0x40, 0x4e, 0x01, 0xa3, 0x6e, 0x02, 0xcf, 0x2c, 0x00
};

// si4432 tx power settings
typedef enum _tag_si4432_tx_power_
{
  TX_POWER_20DB,
  TX_POWER_MAX
}Si4432_tx_power;

const char Tx_power_table[TX_POWER_MAX] = { 0x0f };

// si4432 deviation freqeuncy settings
typedef enum _tag_deviation_freq_
{
  DEVI_FREQ_35K,
  DEVI_FREQ_MAX
}Si4432_devi_freq;

const char Devi_freq_table[DEVI_FREQ_MAX] = { 0x38 };

// si4432 modulation mode settings
typedef enum _tag_modulation_mode_
{
  MODULATION_FSK,
  MODULATION_GFSK,
  MODULATION_MAX
}Si4432_modulation_mode;

const char Modulation_table[MODULATION_MAX] = { 0x22, 0x23 };

// si4432 frame format settings
#define SI4432_FRAME_FMT_SIZE (13)
#define SI4432_FRAME_HEADER_SIZE (4)

typedef char Si4432_frame_header[SI4432_FRAME_HEADER_SIZE];

const Si4432_frame_header Default_header = { 'D', 'F', 'S', 'G'};

#define DATA_LEN_MAX  (150)

const char Frame_fmt_talbe[SI4432_FRAME_FMT_SIZE] = 
{
  0x8c,	// enable packet handler, msb first, enable crc, //	0x31 only readable	
  0xff,	// 0x32 address enable for headere byte 0, 1,2,3, receive header check for byte 0, 1,2,3
  0x42,	// header 3, 2, 1,0 used for head length, fixed packet length, synchronize word length 3, 2,
  0x2d,	// 2byte synchronize word
  0xd4,						
  0x00,
  0x00,
  0x64,	// 32byte preamble
  0x20, // 0x35 set the length of the detect preamble.(need to detect 16bit preamble)
  0xff,	// all the bit to be checked
  0xff,						
  0xff,						
  0xff						
};

typedef struct  _tag_si4432_settings
{
  unsigned char carrier_freq;
  unsigned char data_rate;
  unsigned char tx_pwr;
  unsigned char freq_deviation;
  unsigned char modualation;
  unsigned char data_len_max;
  Si4432_frame_header header;
}Si4432_setting;

// si4432 register definition
#define SI4432_SPI_TIMEOUT (0xFF)
#define SI4432_SOFT_RESET_DELAY (10)
#define SI4432_HW_RESET_DELAY (1000)
#define SI4432_POR_DELAY (25)

// device infomation
#define SI4432_REG_DEV_TYPE (0x00)
#define SI4432_REG_DEV_VER (0x01)
#define SI4432_REG_DEV_STATUS (0X02)
// interrupt status
#define SI4432_REG_ISTATUS1 (0x03)
#define SI4432_REG_ISTATUS2 (0x04)
// interrupt enable
#define SI4432_REG_IEN1 (0x05)
#define SI4432_REG_IEN2 (0x06)
// Operating & Function Control
#define SI4432_REG_OFC1 (0x07)
#define SI4432_REG_OFC2 (0x08)
// GPIO Configuration
#define SI4432_REG_GPIO0_CFG (0x0b)
#define SI4432_REG_GPIO1_CFG (0x0c)
#define SI4432_REG_GPIO2_CFG (0x0d)
// IF Filter Bandwidth
#define SI4432_REG_IF_BW (0x1c)
// AFC Loop Gearshift Override
#define SI4432_REG_AFC (0x1d)
// Clock Recovery
#define SI4432_REG_CLK_REC_RATIO (0x20)
#define SI4432_REG_CLK_REC_OFFSET2 (0x21)
#define SI4432_REG_CLK_REC_OFFSET1 (0x22)
#define SI4432_REG_CLK_REC_OFFSET0 (0x23)
#define SI4432_REG_CLK_REC_GAIN1 (0x24)
#define SI4432_REG_CLK_REC_GAIN0 (0x25)
// AFC Limiter
#define SI4432_REG_AFC_LIMIT (0x2a)
// Data Access Control
#define SI4432_REG_DATA_AC (0x30)
// Header Control
#define SI4432_REG_HEADER_CTRL1 (0x32)
#define SI4432_REG_HEADER_CTRL2 (0x33)
// Preamble length
#define SI4432_REG_PREAM_LEN (0x34)
// Preamble Detection Control
#define SI4432_REG_PREAM_DC (0x35)
// Sync Word
#define SI4432_REG_SYNC_WORD3 (0x36)
#define SI4432_REG_SYNC_WORD2 (0x37)
#define SI4432_REG_SYNC_WORD1 (0x38)
#define SI4432_REG_SYNC_WORD0 (0x39)
// Transmit Header
#define SI4432_REG_TRANS_HEADER3 (0x3a)
#define SI4432_REG_TRANS_HEADER2 (0x3b)
#define SI4432_REG_TRANS_HEADER1 (0x3c)
#define SI4432_REG_TRANS_HEADER0 (0x3d)
// Packet Length
#define SI4432_REG_PACK_LEN (0x3e)
// Check Header
#define SI4432_REG_CHK_HEADER3 (0x3f)
#define SI4432_REG_CHK_HEADER2 (0x40)
#define SI4432_REG_CHK_HEADER1 (0x41)
#define SI4432_REG_CHK_HEADER0 (0x42)
// Header Enable
#define SI4432_REG_HEADER3_EN (0x43)
#define SI4432_REG_HEADER2_EN (0x44)
#define SI4432_REG_HEADER1_EN (0x45)
#define SI4432_REG_HEADER0_EN (0x46)
// TX Power
#define SI4432_REG_TX_POWER (0x6d)
// TX Data Rate
#define SI4432_REG_TX_RATE1 (0x6e)
#define SI4432_REG_TX_RATE0 (0x6f)
// Modulation Mode Control
#define SI4432_REG_MODULATION_CTRL1 (0x70)
#define SI4432_REG_MODULATION_CTRL2 (0x71)
// Frequency Deviation
#define SI4432_REG_FREQ_DEVIATION (0x72)
// Frequency Offset
#define SI4432_REG_FREQ_OFFSET1 (0x73)
#define SI4432_REG_FREQ_OFFSET2 (0x74)
// Frequency Band Select
#define SI4432_REG_FREQ_BW_SEL (0x75)
// Nominal Carrier Frequency
#define SI4432_REG_CARRY_FREQ1 (0x76)
#define SI4432_REG_CARRY_FREQ2 (0x77)
// Frequency Hopping Channel Select
#define SI4432_REG_FREQ_HOPPING_SEL (0x79)
// Frequency Hopping Step Size
#define SI4432_REG_FREQ_HOPPING_STEP_SIZE (0x7a)
// FIFO Access
#define SI4432_REG_FIFO (0x7f)

typedef enum _tag_SI4432_status_
{
  SI4432_NO_INT,
  SI4432_TX_DONE,
  SI4432_RX_DONE,
} Si4432_status;

typedef enum _tag_si4432_mode_
{
  MODE_RDY,
  MODE_TX,
  MODE_RX,
} Si4432_mode;

class Si4432
{
public:
  Si4432(SPI_HandleTypeDef *_hspi, Si4432_setting* _settings = NULL);
  void set_nss_pin(GPIO_TypeDef *_port, unsigned short _pin);
  void set_sdn_pin(GPIO_TypeDef *_port, unsigned short _pin);
  void set_irq_pin(GPIO_TypeDef *_port, unsigned short _pin);
  void set_frame_header(Si4432_frame_header _header);
  bool init(void);
  Si4432_status get_status(void);
  unsigned int read_data(unsigned char *data);
  bool send_data(unsigned char *data, unsigned int data_len);
  bool switch_mode(Si4432_mode mode);
  
  ~Si4432();

private:
  bool set_GPIO(void);
  bool set_freq(unsigned char idx);
  bool set_data_rate(unsigned char idx );
  
  bool set_data_fmt(Si4432_frame_header& _header);
  bool set_tx_power(unsigned char idx);
  bool set_freq_deviation(unsigned char idx);
  bool set_modulation(unsigned char idx);

  bool clear_fifo(void);

  bool to_tx_mode(void);
  bool to_rx_mode(void);
  bool to_ready_mode(void);

  bool swith_ant(bool tx = true);

  bool software_reset(void);
  bool hardware_reset(void);

  bool write_reg(unsigned char addr, unsigned char val);
  unsigned char read_reg(unsigned char addr);

  bool send_address(unsigned char addr, bool write = true);

  unsigned char spi_read(void);
  bool spi_write(unsigned char *data, unsigned int data_len);

  void nss_hi(void);
  void nss_low(void);
  void sdn_hi(void);
  void sdn_low(void);
  bool irq(void);

  SPI_HandleTypeDef *hspi;
  GPIO_TypeDef *nss_port;
  unsigned short nss_pin;
  GPIO_TypeDef *sdn_port;
  unsigned short sdn_pin;
  GPIO_TypeDef *irq_port;
  unsigned short irq_pin;
  Si4432_setting settings;
};

#endif
