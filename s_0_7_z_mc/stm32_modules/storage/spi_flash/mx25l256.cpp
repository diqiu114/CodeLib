#include "mx25l256.h"
#include "string.h"

Mx25l256::Mx25l256(Spi_if *_spi, Gpio_if *_spi_nss,bool _auto_erase)
{
  spi = _spi;
  spi_nss = _spi_nss;
  auto_erase = _auto_erase;
  memset(id, 0, sizeof(id));

  chip_ready = init();
}

Mx25l256::~Mx25l256()
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

bool Mx25l256::init(void)
{
  cs_hi();

  reset();

  write_status_reg(0);

  if (ADDR_4BYTES_MODE)
  {
    mode_4bytes_sw(1);
  }
  else
  {
    mode_4bytes_sw(0);
  }

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

bool Mx25l256::ready(void)
{
  return chip_ready;
}

void Mx25l256::reset(void)
{
  cs_low();
  spi_comm(MX25_CMD_RSTEN);
  cs_hi();

  cs_low();
  spi_comm(MX25_CMD_RST);
  cs_hi();

  if (is_ready())
    write_complete();
}

bool Mx25l256::read_bytes(unsigned int addr, unsigned char *data, unsigned int data_len)
{
  unsigned int i = 0;

  cs_low();
  if (ADDR_4BYTES_MODE)
  {
    spi_comm(MX25_CMD_READ4B);
    spi_comm((addr >> 24) & 0xff);
  }
  else
  {
    spi_comm(MX25_CMD_READ);
  }
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

bool Mx25l256::write_bytes(unsigned int addr, unsigned char *data, unsigned int data_len)
{
  unsigned int i = 0;

  unsigned char cross_page = 0;
  unsigned remain_len = 0;
  if (auto_erase)
  {
    // erase secor at 1st time before write
    if ((addr % 0x1000) == 0)
    {
      erase_sector(addr);
    }
  }

  // 无法跨page连续写,所以分为多部分写入
  if ((addr % 0x100) + data_len > 0x100)
  {
    //    erase_sector(addr + length);
    cross_page = 1;
    //修复因data跨两个page而remain_len错误的bug
    remain_len = data_len - (0x100 - (addr % 0x100));
    data_len = data_len - remain_len;
  }

  if (is_ready())
  {
    write_enable();

    cs_low();

    if (ADDR_4BYTES_MODE)
    {
      spi_comm(MX25_CMD_PP4B);
      spi_comm((addr >> 24) & 0xff);
    }
    else
    {
      spi_comm(MX25_CMD_PP);
    }
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

  if (cross_page == 1)
  {
    write_bytes(addr + data_len, data + data_len, remain_len);
  }
  return true;
}

void Mx25l256::read_pages(unsigned int page_idx, unsigned char *data, unsigned int page_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < page_cnt; i++)
  {
    read_page(page_idx, ptr);
    page_idx++;
    ptr += MX_PAGE_SIZE;
  }
}

void Mx25l256::write_pages(unsigned int page_idx, unsigned char *data, unsigned int page_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < page_cnt; i++)
  {
    write_page(page_idx, ptr);
    page_idx++;
    ptr += MX_PAGE_SIZE;
  }
}

void Mx25l256::read_sectors(unsigned int sector_idx, unsigned char *data, unsigned int sector_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < sector_cnt; i++)
  {
    read_sector(sector_idx, ptr);
    sector_idx++;
    ptr += MX_SECTOR_SIZE;
  }
}

void Mx25l256::write_sectors(unsigned int sector_idx, unsigned char *data, unsigned int sector_cnt)
{

  unsigned char *ptr = data;
  for (int i = 0; i < sector_cnt; i++)
  {
    write_sector(sector_idx, ptr);
    sector_idx++;
    ptr += MX_SECTOR_SIZE;
  }
}

bool Mx25l256::erase(unsigned int addr)
{
  erase_sector(addr);
  return true;
}

void Mx25l256::erase_sector(unsigned int addr)
{
  if (is_ready())
  {
    write_enable();
    cs_low();

    if (ADDR_4BYTES_MODE)
    {
      spi_comm(MX25_CMD_SE4B);
      spi_comm((addr >> 24) & 0xff);
    }
    else
    {
      spi_comm(MX25_CMD_SE);
    }
    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    cs_hi();

    write_complete();
  }
}

void Mx25l256::erase_32k_block(unsigned int addr)
{
  addr = (addr << 15);

  if (is_ready())
  {
    write_enable();

    cs_low();

    if (ADDR_4BYTES_MODE)
    {
      spi_comm(MX25_CMD_BE32K4B);
      spi_comm((addr >> 24) & 0xff);
    }
    else
    {
      spi_comm(MX25_CMD_BE32K);
    }
    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    cs_hi();

    write_complete();
  }
}

void Mx25l256::erase_64k_block(unsigned int addr)
{
  addr = (addr << 16);

  if (is_ready())
  {
    write_enable();

    cs_low();

    if (ADDR_4BYTES_MODE)
    {
      spi_comm(MX25_CMD_BE4B);
      spi_comm((addr >> 24) & 0xff);
    }
    else
    {
      spi_comm(MX25_CMD_BE);
    }
    spi_comm((addr >> 16) & 0xff);
    spi_comm((addr >> 8) & 0xff);
    spi_comm((addr >> 0) & 0xff);

    cs_hi();

    write_complete();
  }
}

bool Mx25l256::erase_full_chip(void)
{
  bool ret = false;

  if (is_ready())
  {
    if (write_enable())
    {
      cs_low();

      spi_comm(MX25_CMD_CE);

      cs_hi();

      // full chip erase will take about 300 senconds
      ret = write_complete(CHIP_ERASE_TIMEOUT_CNT);
    }
  }

  return ret;
}

void Mx25l256::read_id(unsigned char *id)
{
  int i = 0;

  cs_low();

  spi_comm(MX25_CMD_RDID);

  for (i = 0; i < 3; i++)
  {
    id[i] = spi_comm(0x55);
  }

  cs_hi();
}

void Mx25l256::mode_4bytes_sw(unsigned char enable)
{
  cs_low();

  if (enable)
  {
    spi_comm(MX25_CMD_EN4B);
  }
  else
  {
    spi_comm(MX25_CMD_EX4B);
  }

  cs_hi();
}

unsigned char Mx25l256::write_enable(void)
{
  unsigned int timeout = 0;

  do
  {
    cs_low();
    spi_comm(MX25_CMD_WREN);
    cs_hi();

    if (++timeout > TIMEOUT_CNT)
      return 0;

  } while ((read_status_reg() & WEL) == 0);

  return 1;
}

bool Mx25l256::is_ready(void)
{
  return (((read_status_reg() & WIP) == 0) ? true : false);
}

bool Mx25l256::write_complete(unsigned int timeout)
{
  unsigned int time = 0;

  while ((read_status_reg() & WIP))
  {
    if (++time >= timeout)
      return false;
  }

  return true;
}

unsigned char Mx25l256::read_status_reg(void)
{
  unsigned char ret = 0;

  cs_low();

  spi_comm(MX25_CMD_RDSR);

  ret = spi_comm(0x55);

  cs_hi();

  return ret;
}

void Mx25l256::write_status_reg(unsigned char stat_val)
{
  if (is_ready())
  {
    write_enable();
    cs_low();

    spi_comm(MX25_CMD_WRSR);
    spi_comm(stat_val);

    cs_hi();

    write_complete();
  }
}

void Mx25l256::cs_low(void)
{
  spi_nss->set_low();
}

void Mx25l256::cs_hi(void)
{
  spi_nss->set_hi();
}

unsigned char Mx25l256::spi_comm(unsigned char s_byte)
{
  unsigned char ret = 0;

  spi->send_receive(&s_byte, &ret, 1);

  return ret;
}

void Mx25l256::read_sector(unsigned int sector_idx, unsigned char *data)
{
  read_pages(sector_idx * MX_PAGE_CNT_PER_SECOTR, data, MX_PAGE_CNT_PER_SECOTR);
}

void Mx25l256::write_sector(unsigned int sector_idx, unsigned char *data)
{
  write_pages(sector_idx * MX_PAGE_CNT_PER_SECOTR, data, MX_PAGE_CNT_PER_SECOTR);
}

void Mx25l256::read_page(unsigned int page_idx, unsigned char *data)
{
  read_bytes(page_idx * MX_PAGE_SIZE, data, MX_PAGE_SIZE);
}

void Mx25l256::write_page(unsigned int page_idx, unsigned char *data)
{
  write_bytes(page_idx * MX_PAGE_SIZE, data, MX_PAGE_SIZE);
}
