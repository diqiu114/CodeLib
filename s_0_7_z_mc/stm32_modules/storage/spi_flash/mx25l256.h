/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief         macronix MX25L25635E spi driver
* datasheet link https://www.alldatasheet.com/datasheet-pdf/pdf/575568/MCNIX/MX25L25635E.html
*
***********************************************************/
#ifndef _MX25L256_H_
#define _MX25L256_H_

#define MX25L25635E

#include "main.h"
#include <stdbool.h>

#define MX25_Enable HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET)
#define MX25_Disable HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET)

#define TIMEOUT_CNT 100000
#define CHIP_ERASE_TIMEOUT_CNT 0xFFFFFFFF

// 4bytes adress access mode
#define ADDR_4BYTES_MODE (1)

#define MX_BLOCK_SIZE (32768)
#define MX_SECTOR_SIZE (4096)
#define MX_PAGE_SIZE (256)
#define MX_PAGE_CNT_PER_SECOTR (MX_SECTOR_SIZE / MX_PAGE_SIZE)

#define MX_BLOCK_CNT (1024)
#define MX_SECTOR_CNT (8192)
#define MX_PAGE_CNT (131072)

/*** MX25 series command hex code definition ***/
//ID commands
#define MX25_CMD_RDID 0x9F  //RDID (Read Identification)
#define MX25_CMD_RES 0xAB   //RES (Read Electronic ID)
#define MX25_CMD_REMS 0x90  //REMS (Read Electronic & Device ID)
#define MX25_CMD_QPIID 0xAF //QPIID (QPI ID Read)

//Register commands
#define MX25_CMD_WRSR 0x01    //WRSR (Write Status Register)
#define MX25_CMD_RDSR 0x05    //RDSR (Read Status Register)
#define MX25_CMD_WRSCUR 0x2F  //WRSCUR (Write Security Register)
#define MX25_CMD_RDSCUR 0x2B  //RDSCUR (Read Security Register)
#define MX25_CMD_RDCR 0x15    //RDCR (Read Configuration Register)
#define MX25_CMD_RDEAR 0xC8   //RDEAR (Read Extended Address Register)
#define MX25_CMD_WREAR 0xC5   //WREAR (Write Extended Address Register)
#define MX25_CMD_RDFBR 0x16   //RDFBR (read fast boot Register)
#define MX25_CMD_WRFBR 0x17   //WRFBR (write fast boot Register)
#define MX25_CMD_ESFBR 0x18   //ESFBR (erase fast boot Register)
#define MX25_CMD_WRLR 0x2C    //WRLR (write lock Register)
#define MX25_CMD_RDLR 0x2D    //RDLR (read lock Register)
#define MX25_CMD_RDSPB 0xE2   //RDSPB (read SPB status)
#define MX25_CMD_WRSPB 0xE3   //WRSPB (write SPB bit)
#define MX25_CMD_ESSPB 0xE4   //ESSPB (erase all SPB status)
#define MX25_CMD_SPBLK 0xA6   //SPBLK (SPB lock set)
#define MX25_CMD_RDSPBLK 0xA7 //SPBLK (read SPB lock register)
#define MX25_CMD_WRPASS 0x28  //WRPASS (write password Register)
#define MX25_CMD_RDPASS 0x27  //RDPASS (read password Register)
#define MX25_CMD_PASSULK 0x29 //RDPASS (password unlock)
#define MX25_CMD_RDDPB 0xE0   //RDDPB (read DPB register)
#define MX25_CMD_WRDPB 0xE1   //WRDPB (write DPB register)

//READ commands
#define MX25_CMD_READ 0x03       //READ (1 x I/O)
#define MX25_CMD_2READ 0xBB      //2READ (2 x I/O)
#define MX25_CMD_4READ 0xEB      //4READ (4 x I/O)
#define MX25_CMD_4READ_TOP 0xEA  //4READ (4 x I/O read from top 128Mb)
#define MX25_CMD_FASTREAD 0x0B   //FAST READ (Fast read data).
#define MX25_CMD_DREAD 0x3B      //DREAD (1In/2 Out fast read)
#define MX25_CMD_QREAD 0x6B      //QREAD (1In/4 Out fast read)
#define MX25_CMD_RDSFDP 0x5A     //RDSFDP (Read SFDP)
#ifdef MX25L25635F
#define MX25_CMD_READ4B 0x13     //READ4B (1 x I/O with 4 byte address)
#endif
#ifdef MX25L25635E
#define MX25_CMD_READ4B MX25_CMD_READ
#endif

#define MX25_CMD_FASTREAD4B 0x0C //FASTREAD4B (1 x I/O with 4 byte address)
#define MX25_CMD_2READ4B 0xBC    //2READ4B (2 x I/O with 4 byte address)
#define MX25_CMD_4READ4B 0xEC    //4READ4B (4 x I/O with 4 byte address)
#define MX25_CMD_DREAD4B 0x3C    //DREAD4B (1In/2 Out fast read with 4 byte addr)
#define MX25_CMD_QREAD4B 0x6C    //QREAD4B (1In/4 Out fast read with 4 byte addr)

//Program commands
#define MX25_CMD_WREN 0x06  //WREN (Write Enable)
#define MX25_CMD_WRDI 0x04  //WRDI (Write Disable)
#define MX25_CMD_PP 0x02    //PP (page program)
#define MX25_CMD_4PP 0x38   //4PP (Quad page program)
#ifdef MX25L25635F
#define MX25_CMD_PP4B 0x12  //PP4B (page program with 4 byte address)
#endif
#ifdef MX25L25635E
#define MX25_CMD_PP4B MX25_CMD_PP
#endif

#define MX25_CMD_4PP4B 0x3E //4PP4B (Quad page program with 4 byte address)

//Erase commands
#define MX25_CMD_SE 0x20      //SE (Sector Erase)
#define MX25_CMD_BE32K 0x52   //BE32K (Block Erase 32kb)
#define MX25_CMD_BE 0xD8      //BE (Block Erase)
#define MX25_CMD_CE 0xC7      //CE (Chip Erase) hex code: 60 or C7
#ifdef MX25L25635F
#define MX25_CMD_SE4B 0x21    //SE (Sector Erase with 4 byte addr)
#define MX25_CMD_BE32K4B 0x5C //BE32K4B (Block Erase 32kb with 4 byte addr)
#define MX25_CMD_BE4B 0xDC    //BE4B (Block Erase with 4 byte address)
#endif
#ifdef MX25L25635E
#define MX25_CMD_SE4B MX25_CMD_SE
#define MX25_CMD_BE32K4B MX25_CMD_BE32K
#define MX25_CMD_BE4B MX25_CMD_BE
#endif

//Mode setting commands
#define MX25_CMD_DP 0xB9    //DP (Deep Power Down)
#define MX25_CMD_RDP 0xAB   //RDP (Release form Deep Power Down)
#define MX25_CMD_ENSO 0xB1  //ENSO (Enter Secured OTP)
#define MX25_CMD_EXSO 0xC1  //EXSO  (Exit Secured OTP)
#define MX25_CMD_EQIO 0x35  //EQIO (Enable Quad I/O)
#define MX25_CMD_WPSEL 0x68 //WPSEL (Enable block protect mode)
#ifdef SBL_CMD_0x77
#define MX25_CMD_SBL 0x77 //SBL (Set Burst Length), new: 0x77
#else
#define MX25_CMD_SBL 0xC0 //SBL (Set Burst Length), old: 0xC0
#endif
#define MX25_CMD_EN4B 0xB7 //EN4B( Enter 4-byte Mode )
#define MX25_CMD_EX4B 0xE9 //EX4B( Exit 4-byte Mode )

//Reset commands
#define MX25_CMD_RSTEN 0x66  //RSTEN (Reset Enable)
#define MX25_CMD_RST 0x99    //RST (Reset Memory)
#define MX25_CMD_RSTQIO 0xF5 //RSTQIO (Reset Quad I/O)

//Security commands
#define MX25_CMD_GBLK 0x7E  //GBLK (Gang Block Lock)
#define MX25_CMD_GBULK 0x98 //GBULK (Gang Block Unlock)

//Suspend/Resume commands
#ifdef PGM_ERS_0xB0
#define MX25_CMD_PGM_ERS_S 0xB0 //PGM/ERS Suspend (Suspends Program/Erase) old: 0xB0
#define MX25_CMD_PGM_ERS_R 0x30 //PGM/ERS Erase (Resumes Program/Erase) old: 0x30
#else
#define MX25_CMD_PGM_ERS_S 0x75 //PGM/ERS Suspend (Suspends Program/Erase) old: 0xB0
#define MX25_CMD_PGM_ERS_R 0x7A //PGM/ERS Erase (Resumes Program/Erase) old: 0x30
#endif

#define MX25_CMD_NOP 0x00 //NOP (No Operation)

// status register
#define WIP (1 << 0)  //写处理标记 1-写操作中 0-无写操作
#define WEL (1 << 1)  //写使能标记 1-写使能   0-写禁止
#define BP0 (1 << 2)  //块保护设置
#define BP1 (1 << 3)  //块保护设置
#define BP2 (1 << 4)  //块保护设置
#define BP3 (1 << 5)  //块保护设置
#define QE (1 << 6)   //4线操作使能
#define SRWD (1 << 7) //状态寄存器写保护 1-写禁止 0-写使能

// config register
#define ODS0 (1 << 0)    //驱动能力设置
#define ODS1 (1 << 1)    //驱动能力设置
#define ODS2 (1 << 2)    //驱动能力设置
#define TB (1 << 3)      //0-顶部区域保护 1-底部区域保护
#define RESERVE (1 << 4) //空
#define MOD_4B (1 << 5)  //地址模式 0-3地址模式 1-4地址模式
#define DC0 (1 << 6)     //dummy clock cycles设置
#define DC1 (1 << 7)     //dummy clock cycles设置

// security register
#define SECURED_OTP (1 << 0)    //4K-bit Security OTP,(ro)
#define LDSO (1 << 1)    //lock-down 4K-bit Secured OTP,(otp)
#define BYTE4 (1 << 2)    //0=3byte(default),1=4bute,(ro)
#define SECURITY_BIT3 (1 << 3)      //保留,(ro)
#define CP_MODE (1 << 4) //Continuously Program mode，0=normal Program mode 1=CP mode (default=0)
#define P_FAIL (1 << 5)  //0=normal Program succeed，1=indicate Program failed (default=0)
#define E_FAIL (1 << 6)     //0=normal Erase succeed 1=indicate Erase failed (default=0)
#define WPSEL (1 << 7)     //0=normal WP mode 1=individual WP mode (default=0)

//#define ACTUAL_VALUE_ADDR	(0x00000)
#define TOTAL_VALUE_ADDR (0x01000)
#define ID_ADDR (0x02000)
#define INIT_FLAG_ADDR (0x04000)
#define WL_SAVE_ADDR (0x08000)

#define MX25_ID_LEN (3)

#include "hw_interface\spi\spi_if.h"
#include "hw_interface\gpio\gpio_if.h"
#include "spi_flash_if.h"

class Mx25l256 : public Spi_flash_if
{
public:
  Mx25l256(Spi_if *_spi, Gpio_if *_spi_nss,bool _auto_erase = true);
  virtual ~Mx25l256();
  bool init(void);
  void reset(void);
  bool ready(void);
  virtual bool read_bytes(unsigned int addr, unsigned char *data, unsigned int data_len);
  virtual bool write_bytes(unsigned int addr, unsigned char *data, unsigned int data_len);
  void read_pages(unsigned int addr_idx, unsigned char *data, unsigned int page_cnt);
  void write_pages(unsigned int page_idx, unsigned char *data, unsigned int page_cnt);
  void read_sectors(unsigned int sector_idx, unsigned char *data, unsigned int sector_cnt);
  void write_sectors(unsigned int sector_idx, unsigned char *data, unsigned int sector_cnt);
  void erase_sector(unsigned int addr);
  virtual bool erase(unsigned int addr);

  void erase_32k_block(unsigned int addr);
  void erase_64k_block(unsigned int addr);
  bool erase_full_chip(void);

private:
  unsigned char spi_comm(unsigned char s_byte);
  bool is_ready(void);
  void cs_low(void);
  void cs_hi(void);
  bool write_complete(unsigned int timeout = TIMEOUT_CNT);
  unsigned char read_status_reg(void);
  void mode_4bytes_sw(unsigned char enable);
  unsigned char write_enable(void);
  void write_status_reg(unsigned char stat_val);
  void read_sector(unsigned int sector_idx, unsigned char *data);
  void write_sector(unsigned int sector_idx, unsigned char *data);
  void read_page(unsigned int page, unsigned char *data);
  void write_page(unsigned int page, unsigned char *data);
  void read_id(unsigned char *id);

  Spi_if *spi;
  Gpio_if *spi_nss;
  bool auto_erase;
  unsigned char id[MX25_ID_LEN];
  bool chip_ready;
};

#endif //_MX25L256_H_
