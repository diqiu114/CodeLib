/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief         Giga Device GD25Q64C(8Mbytes) spi driver
* datasheet link https://www.alldatasheet.com/datasheet-pdf/pdf/575568/MCNIX/MX25L25635E.html
*
***********************************************************/
#ifndef _GD25QXX_H_
#define _GD25QXX_H_
#include <stdbool.h>

#define TIMEOUT_CNT 100000
#define CHIP_ERASE_TIMEOUT_CNT 0xFFFFFFFF

//The status and control bits of the Status Register:
//REG1
#define GD25QXX_STA_BIT_WIP (0x01)      //The Write In Progress (WIP) bit indicates whether the memory is busy in program/erase/write status register progress.
#define GD25QXX_STA_BIT_WEL (0x01 << 1) //The Write Enable Latch (WEL) bit indicates the status of the internal Write Enable Latch.
#define GD25QXX_STA_BIT_BP0 (0x01 << 2)
#define GD25QXX_STA_BIT_BP1 (0x01 << 3)
#define GD25QXX_STA_BIT_BP2 (0x01 << 4)
#define GD25QXX_STA_BIT_BP3 (0x01 << 5)
#define GD25QXX_STA_BIT_BP4 (0x01 << 6)
#define GD25QXX_STA_BIT_SRP0 (0x01 << 7)

//REG2
#define GD25QXX_STA_BIT_SRP1 (0x01 << 8)
#define GD25QXX_STA_BIT_QE (0x01 << 9)
#define GD25QXX_STA_BIT_SUS2 (0x01 << 10) //read only bit,The Program Suspend will set the SUS2 to 1
#define GD25QXX_STA_BIT_LB1 (0x01 << 11)
#define GD25QXX_STA_BIT_LB2 (0x01 << 12)
#define GD25QXX_STA_BIT_LB3 (0x01 << 13)
#define GD25QXX_STA_BIT_CMP (0x01 << 14)
#define GD25QXX_STA_BIT_SUS1 (0x01 << 15) //read only bit,The Erase Suspend will set the SUS1 to 1

//REG3
#define GD25QXX_STA_BIT_HPF (0x01 << 20)
#define GD25QXX_STA_BIT_DRV0 (0x01 << 21)
#define GD25QXX_STA_BIT_DRV1 (0x01 << 22)

/****************write cmd*********************/
//Set Status Registor
#define GD25QXX_CMD_WR_STATUS_REG1 (0x01) //Write Status Register-1
#define GD25QXX_CMD_WR_STATUS_REG2 (0x31) //Write Status Register-2
#define GD25QXX_CMD_WR_STATUS_REG3 (0x11) //Write Status Register-3

//Write operation
#define GD25QXX_CMD_PAGE_PROGRAM (0x02)     //Page Program
#define GD25QXX_CMD_QUAD_PAGE_PROGRAM (32H) //Quad Page Program
#define GD25QXX_CMD_FAST_PAGE_PROGRAM (0xF2)

//Erase instruction
#define GD25QXX_CMD_SECTOR_ERASE (0x20)    //Sector Erase
#define GD25QXX_CMD_BLOCK_ERASE_32K (0x52) //Block Erase (32K)
#define GD25QXX_CMD_BLOCK_ERASE_64K (0xD8) //Block Erase (64K)
#define GD25QXX_CMD_CHIP_ERASE (0xC7)      //Chip Erase

//Reset cmd
#define GD25QXX_CMD_ENABLE_RESET (0x66) //Enable_Reset
#define GD25QXX_CMD_RESET_CMD (0x99)    //Reset

//Suspend/Resume cmd
#define GD25QXX_CMD_PROG_ERASE_SUS (0x75) //Program/Erase Suspend
#define GD25QXX_CMD_PROG_ERASE_RES (0x7A) //Program/Erase Resume

//Power down
#define GD25QXX_CMD_DEEP_POWER_DOWN (0xB9)
#define GD25QXX_CMD_RELEASE_FROM_DEEP_POWER_DOWN (0xAB)

//Write operation switch
#define GD25QXX_CMD_WR_ENABLE_CMD (0x06)    //Write Enable
#define GD25QXX_CMD_WR_DISABLE_CMD (0x04)   //Write Disable
#define GD25QXX_CMD_VOL_SR_WR_ENABLE (0x50) //Volatile SR Write Enable

/****************read cmd*********************/
//Get Status Registor
#define GD25QXX_CMD_RD_STATUS_REG1 (0x05) //Read Status Register-1
#define GD25QXX_CMD_RD_STATUS_REG2 (0x35) //Read Status Register-2
#define GD25QXX_CMD_RD_STATUS_REG3 (0x15) //Read Status Register-3

//Read operation
#define GD25QXX_CMD_RD_DATA_BYTE (0x03) //Read Data
#define GD25QXX_CMD_FST_RD (0x0B)       //Fast Read
#define DUAL_OUTPUT_FSTRD (0x3B)        //Dual Output Fast Read (3BH)
#define DUAL_IO_FSTRD (0xBB)            //Dual I/O Fast Read (BBH)
#define QUAD_OUTPUT_FSTRD (0x6B)        //Quad Output Fast Read (6BH)
#define QUAD_IO_FSTRD (0xEB)            //Quad I/O Fast Read (EBH)
#define QUAD_IO_WORD_FSTRD (0xE7)       //Quad I/O Word Fast Read (E7H)

//Get ID
#define GD25QXX_CMD_RD_ID (0x9F)                      //Read Identification
#define GD25QXX_CMD_MENUFACTURE_DEV_ID (0x90)         //Manufacturer/Device ID
#define GD25QXX_CMD_MENUFACTURE_DEV_ID_BY_DUAL (0x92) //Manufacture/Device ID by Dual I/O
#define GD25QXX_CMD_MENUFACTURE_DEV_ID_BY_QUAD (0x94) //Manufacture/Device ID by Quad I/O

#ifndef USE_FLASH_GD25Q64
#define USE_FLASH_GD25Q32 (1)
#else
#define USE_FLASH_GD25Q64 (1)
#endif

#define GD25Q64_ID_LEN (3)

#define GD25Q64_PAGE_SIZE (0x100)
#define GD25Q64_SECTOR_SIZE (0x1000)
#define GD25Q64_BLOCK_SIZE_32KB (0x8000)
#define GD25Q64_BLOCK_SIZE_64KB (0x10000)
#define GD25Q64_CHIP_SIZE (0x800000)

#define GD25Q64_PAGE_CNT (32768)
#define GD25Q64_SECTOR_CNT (2048)
#define GD25Q64_BLOCK_CNT (128)
#define GD25Q64_PAGE_CNT_PER_SECOTR (GD25Q64_SECTOR_SIZE / GD25Q64_PAGE_SIZE)

#define GD25Q32_ID_LEN (3)

#define GD25Q32_PAGE_SIZE (0x100)
#define GD25Q32_SECTOR_SIZE (0x1000)
#define GD25Q32_BLOCK_SIZE_32KB (0x8000)
#define GD25Q32_BLOCK_SIZE_64KB (0x10000)
#define GD25Q32_CHIP_SIZE (0x400000)

#define GD25Q32_PAGE_CNT (16384)
#define GD25Q32_SECTOR_CNT (1024)
#define GD25Q32_BLOCK_CNT (64)
#define GD25Q32_PAGE_CNT_PER_SECOTR (GD25Q32_SECTOR_SIZE / GD25Q32_PAGE_SIZE)

#if USE_FLASH_GD25Q64
#define GD25QXX_ID_LEN GD25Q64_ID_LEN

#define GD25QXX_PAGE_SIZE GD25Q64_PAGE_SIZE
#define GD25QXX_SECTOR_SIZE GD25Q64_SECTOR_SIZE
#define GD25QXX_BLOCK_SIZE_32KB GD25Q64_BLOCK_SIZE_32KB
#define GD25QXX_BLOCK_SIZE_64KB GD25Q64_BLOCK_SIZE_64KB
#define GD25QXX_CHIP_SIZE GD25Q64_CHIP_SIZE

#define GD25QXX_PAGE_CNT GD25Q64_PAGE_CNT
#define GD25QXX_SECTOR_CNT GD25Q64_SECTOR_CNT
#define GD25QXX_BLOCK_CNT GD25Q64_BLOCK_CNT
#define GD25QXX_PAGE_CNT_PER_SECOTR GD25Q64_PAGE_CNT_PER_SECOTR
#endif

#if USE_FLASH_GD25Q32
#define GD25QXX_ID_LEN GD25Q32_ID_LEN

#define GD25QXX_PAGE_SIZE GD25Q32_PAGE_SIZE
#define GD25QXX_SECTOR_SIZE GD25Q32_SECTOR_SIZE
#define GD25QXX_BLOCK_SIZE_32KB GD25Q32_BLOCK_SIZE_32KB
#define GD25QXX_BLOCK_SIZE_64KB GD25Q32_BLOCK_SIZE_64KB
#define GD25QXX_CHIP_SIZE GD25Q32_CHIP_SIZE

#define GD25QXX_PAGE_CNT GD25Q32_PAGE_CNT
#define GD25QXX_SECTOR_CNT GD25Q32_SECTOR_CNT
#define GD25QXX_BLOCK_CNT GD25Q32_BLOCK_CNT
#define GD25QXX_PAGE_CNT_PER_SECOTR GD25Q32_PAGE_CNT_PER_SECOTR
#endif

typedef enum _tag_status_reg_
{
  STATUS_REG_1 = 0x05,
  STATUS_REG_2 = 0x35,
  STATUS_REG_3 = 0x15
} Status_reg;

#include "hw_interface\spi\spi_if.h"
#include "hw_interface\gpio\gpio_if.h"
#include "spi_flash_if.h"

class Gd25qxx : public Spi_flash_if
{
public:
  Gd25qxx(Spi_if *_spi, Gpio_if *_spi_nss);
  virtual ~Gd25qxx();
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
  unsigned char read_status_reg(Status_reg reg = STATUS_REG_1);
  void mode_4bytes_sw(unsigned char enable);
  unsigned char write_enable(void);
  void write_status_reg(Status_reg reg, unsigned char cfg_val);
  void read_sector(unsigned int sector_idx, unsigned char *data);
  void write_sector(unsigned int sector_idx, unsigned char *data);
  void read_page(unsigned int page, unsigned char *data);
  void write_page(unsigned int page, unsigned char *data);
  void read_id(unsigned char *id);

  Spi_if *spi;
  Gpio_if *spi_nss;
  unsigned char id[GD25Q64_ID_LEN];
  bool chip_ready;
};

#endif //_MX25L256_H_
