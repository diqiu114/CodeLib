#include "gd25qxx.h"
#include "string.h"

Gd25qxx::Gd25qxx(Spi_if *_spi, Gpio_if *_spi_nss)
{
  spi = _spi;
  spi_nss = _spi_nss;
  memset(id, 0, sizeof(id));

  chip_ready = init();
}

Gd25qxx::~Gd25qxx()
{
  if (spi != NULL)
  {
    delete spi;
    spi = NULL;
  }

  if (spi_nss != NULL)
  {
    delete spi_nss;
    spi_nss = NULL;
  }
}

bool Gd25qxx::init(void)
{
  cs_hi();

  reset();

  read_id(id);

  if ((id[0] != 0) && (id[1] != 0) && (id[2] != 0))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Gd25qxx::ready(void)
{
  return chip_ready;
}

void Gd25qxx::reset(void)
{
  // enable reset
  cs_low();
  spi_comm(GD25QXX_CMD_ENABLE_RESET);
  cs_hi();

  // reset
  cs_low();
  spi_comm(GD25QXX_CMD_RESET_CMD);
  cs_hi();

  if (is_ready())
    write_complete();
}

bool Gd25qxx::read_bytes(unsigned int addr, unsigned char *data, unsigned int data_len)
{
  unsigned int i = 0;

  cs_low();

  spi_comm(GD25QXX_CMD_RD_DATA_BYTE);

  spi_comm((addr >> 16) & 0xff);
  spi_comm((addr >> 8) & 0xff);
  spi_comm((addr >> 0) & 0xff);

  for (i = 0; i < data_len; i++)
  {
    data[i] = spi_comm(0xff);
  }

  cs_hi();

  return true;
}

bool Gd25qxx::write_bytes(unsigned int addr, unsigned char *data, unsigned int data_len)
{
  unsigned int i = 0;

  unsigned char cross_sector = 0;
  unsigned remain_len = 0;

  // erase secor at 1st time before write
  if ((addr % 0x1000) == 0)
  {
    erase_sector(addr);
  }

  // 无法跨sector连续写,所以分为两部分写入
  if ((addr % 0x1000) + data_len > 0x1000)
  {
    //    erase_sector(addr + length);
    cross_sector = 1;
    remain_len = (addr + data_len) % 0x1000;
    data_len = data_len - remain_len;
  }

  if (is_ready())
  {
    write_enable();

    cs_low();

    spi_comm(GD25QXX_CMD_PAGE_PROGRAM);

    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    for (i = 0; i < data_len; i++)
    {
      spi_comm(data[i]);
    }

    cs_hi();

    write_complete();
  }

  if (cross_sector == 1)
  {
    write_bytes(addr + data_len, data + data_len, remain_len);
  }

  return true;
}

void Gd25qxx::read_pages(unsigned int page_idx, unsigned char *data, unsigned int page_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < page_cnt; i++)
  {
    read_page(page_idx, ptr);
    page_idx++;
    ptr += GD25QXX_PAGE_SIZE;
  }
}

void Gd25qxx::write_pages(unsigned int page_idx, unsigned char *data, unsigned int page_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < page_cnt; i++)
  {
    write_page(page_idx, ptr);
    page_idx++;
    ptr += GD25QXX_PAGE_SIZE;
  }
}

void Gd25qxx::read_sectors(unsigned int sector_idx, unsigned char *data, unsigned int sector_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < sector_cnt; i++)
  {
    read_sector(sector_idx, ptr);
    sector_idx++;
    ptr += GD25QXX_SECTOR_SIZE;
  }
}

void Gd25qxx::write_sectors(unsigned int sector_idx, unsigned char *data, unsigned int sector_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < sector_cnt; i++)
  {
    write_sector(sector_idx, ptr);
    sector_idx++;
    ptr += GD25QXX_SECTOR_SIZE;
  }
}

bool Gd25qxx::erase(unsigned int addr)
{
  erase_sector(addr);
  return true;
}

void Gd25qxx::erase_sector(unsigned int addr)
{
  if (is_ready())
  {
    write_enable();
    cs_low();

    spi_comm(GD25QXX_CMD_SECTOR_ERASE);

    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    cs_hi();

    write_complete();
  }
}

void Gd25qxx::erase_32k_block(unsigned int addr)
{
  addr = (addr << 15);

  if (is_ready())
  {
    write_enable();

    cs_low();

    spi_comm(GD25QXX_CMD_BLOCK_ERASE_32K);

    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    cs_hi();

    write_complete();
  }
}

void Gd25qxx::erase_64k_block(unsigned int addr)
{
  addr = (addr << 16);

  if (is_ready())
  {
    write_enable();

    cs_low();

    spi_comm(GD25QXX_CMD_BLOCK_ERASE_64K);
    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    cs_hi();

    write_complete();
  }
}

bool Gd25qxx::erase_full_chip(void)
{
  bool ret = false;

  if (is_ready())
  {
    if (write_enable())
    {
      cs_low();

      spi_comm(GD25QXX_CMD_CHIP_ERASE);

      cs_hi();

      // full chip erase will take about 70 senconds
      ret = write_complete(CHIP_ERASE_TIMEOUT_CNT);
    }
  }

  return ret;
}

void Gd25qxx::read_id(unsigned char *id)
{
  int i = 0;

  cs_low();

  spi_comm(GD25QXX_CMD_RD_ID);
  for (i = 0; i < GD25QXX_ID_LEN; i++)
  {
    id[i] = spi_comm(0x55);
  }

  cs_hi();
}

unsigned char Gd25qxx::write_enable(void)
{
  unsigned int timeout = 0;

  do
  {
    cs_low();
    spi_comm(GD25QXX_CMD_WR_ENABLE_CMD);
    cs_hi();

    if (++timeout > TIMEOUT_CNT)
      return 0;

  } while ((read_status_reg() & GD25QXX_STA_BIT_WEL) == 0);

  return 1;
}

bool Gd25qxx::is_ready(void)
{
  return (((read_status_reg() & GD25QXX_STA_BIT_WIP) == 0) ? true : false);
}

bool Gd25qxx::write_complete(unsigned int timeout)
{
  unsigned int time = 0;

  while ((read_status_reg() & GD25QXX_STA_BIT_WIP))
  {
    if (++time >= timeout)
      return false;
  }

  return true;
}

unsigned char Gd25qxx::read_status_reg(Status_reg reg)
{
  unsigned char ret = 0;

  cs_low();

  spi_comm(reg);

  ret = spi_comm(0xFF);

  cs_hi();

  return ret;
}

void Gd25qxx::write_status_reg(Status_reg reg, unsigned char cfg_val)
{
  if (is_ready())
  {
    write_enable();
    cs_low();

    spi_comm(reg);
    spi_comm(cfg_val);

    cs_hi();

    write_complete();
  }
}

void Gd25qxx::cs_low(void)
{
  spi_nss->set_low();
}

void Gd25qxx::cs_hi(void)
{
  spi_nss->set_hi();
}

unsigned char Gd25qxx::spi_comm(unsigned char s_byte)
{
  unsigned char ret = 0;

  spi->send_receive(&s_byte, &ret, 1);

  return ret;
}

void Gd25qxx::read_sector(unsigned int sector_idx, unsigned char *data)
{
  read_pages(sector_idx * GD25QXX_PAGE_CNT_PER_SECOTR, data, GD25QXX_PAGE_CNT_PER_SECOTR);
}

void Gd25qxx::write_sector(unsigned int sector_idx, unsigned char *data)
{
  write_pages(sector_idx * GD25QXX_PAGE_CNT_PER_SECOTR, data, GD25QXX_PAGE_CNT_PER_SECOTR);
}

void Gd25qxx::read_page(unsigned int page_idx, unsigned char *data)
{
  read_bytes(page_idx * GD25QXX_PAGE_SIZE, data, GD25QXX_PAGE_SIZE);
}

void Gd25qxx::write_page(unsigned int page_idx, unsigned char *data)
{
  write_bytes(page_idx * GD25QXX_PAGE_SIZE, data, GD25QXX_PAGE_SIZE);
}
