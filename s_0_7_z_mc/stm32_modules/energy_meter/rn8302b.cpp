#include "rn8302b.h"
#include <string.h>
#include "modules_def.h"

#define FSOC (8192000.0f)
#define DEV_ID (0x830200)
#define CMD_WR (0x80)
#define WDATA_REG_LEN (3)
#define DATA_MODULE  (0xFFFFFFFF)

/**
 * @brief Construct a new Rn 8 3 0 2b:: Rn 8 3 0 2b object
 * 
 * @param _spi spi communicate object
 * @param _crc8 crc check object
 * @param _params rn8302b parameters
 */
Rn8302b::Rn8302b(Spi_if *_spi, Gpio_if *_spi_cs, Crc8_if *_crc8, Rn8302b_params *_params)
{
  spi = _spi;
  crc = _crc8;
  if (_params == NULL)
  {
    params = new Rn8302b_params();
  }
  else
  {
    params = _params;
  }
  spi_cs = _spi_cs;
}

Rn8302b::~Rn8302b()
{
  if (spi != NULL)
  {
    delete spi;
    spi = NULL;
  }
}

/**
 * @brief initalize rn8302 registers
 *        read chip id, write calibare register values
 *        config rn8302 mode
 * 
 * @return true ok
 * @return false failed
 */
bool Rn8302b::init(void)
{
  bool ret = false;
  int retry = 3;
  int id = 0;

  // 读设备ID
  while (retry--)
  {
    id = get_reg_val(DeviceID, 3);
    if (id == DEV_ID)
    {
      ret = true;
      break;
    }
    DELAY_MS(50);
  }

  // 打开写使能
  ret = ret && write_reg_val(WREN, 0xE5, 1);

  // 切换到计量（EMM）模式
  ret = ret && write_reg_val(WMSW, 0xA2, 1);

  // 软重启
  write_reg_val(SOFTRST, 0xFA, 1);
  DELAY_MS(30);

  // 打开写使能
  ret = ret && write_reg_val(WREN, 0xE5, 1);

  // 高频脉冲常数
  ret = ret && write_reg_val(HFCONST1, 0x397, 2);//0x3E73

  // 电压增益初始化
  ret = ret && write_reg_val(GSUA, 0x19C9, 2);//0x17BD
  ret = ret && write_reg_val(GSUB, 0x00, 2);
  ret = ret && write_reg_val(GSUC, 0x19C9, 2);
  // 电流增益初始化
  ret = ret && write_reg_val(GSIA, 0x137B, 2);//0xF6DD
  ret = ret && write_reg_val(GSIB, 0x00, 2);
  ret = ret && write_reg_val(GSIC, 0x137B, 2);
  // 通道电压相位校正
  ret = ret && write_reg_val(PHSUA, 0x00, 1);
  ret = ret && write_reg_val(PHSUB, 0x00, 1);
  ret = ret && write_reg_val(PHSUC, 0x00, 1);
  // 通道电流相位校正
  ret = ret && write_reg_val(PHSIA, 0x00, 3);
  ret = ret && write_reg_val(PHSIB, 0x00, 3);
  ret = ret && write_reg_val(PHSIC, 0x00, 3);
  // 功率增益
  ret = ret && write_reg_val(GPA, 0x00, 2);
  ret = ret && write_reg_val(GPB, 0x00, 2);
  ret = ret && write_reg_val(GPC, 0x00, 2);
  // 功率相位
  ret = ret && write_reg_val(PA_PHSM, 0x00, 3);
  ret = ret && write_reg_val(PA_PHSH, 0x00, 3);
  ret = ret && write_reg_val(PB_PHSM, 0x00, 3);
  ret = ret && write_reg_val(PB_PHSH, 0x00, 3);
  ret = ret && write_reg_val(PC_PHSM, 0x00, 3);
  ret = ret && write_reg_val(PC_PHSH, 0x00, 3);

  ret = ret && write_reg_val(QA_PHSM, 0x00, 3);
  ret = ret && write_reg_val(QA_PHSH, 0x00, 3);
  ret = ret && write_reg_val(QB_PHSM, 0x00, 3);
  ret = ret && write_reg_val(QB_PHSH, 0x00, 3);
  ret = ret && write_reg_val(QC_PHSM, 0x00, 3);
  ret = ret && write_reg_val(QC_PHSH, 0x00, 3);

  // 相位分段
  ret = ret && write_reg_val(PRTH1L, 0x00, 2);
  ret = ret && write_reg_val(PRTH1H, 0x00, 2);
  ret = ret && write_reg_val(PRTH2L, 0x00, 2);
  ret = ret && write_reg_val(PRTH2H, 0x00, 2);

  // 启动阈值寄存器
  ret = ret && write_reg_val(IStart_PS, 0x250, 2);
  ret = ret && write_reg_val(IStart_Q, 0x250, 2);

  // 功率OFFSET寄存器
  ret = ret && write_reg_val(PA_OS, 0x00, 2);
  ret = ret && write_reg_val(PB_OS, 0x00, 2);
  ret = ret && write_reg_val(PC_OS, 0x00, 2);

  ret = ret && write_reg_val(QA_OS, 0x00, 2);
  ret = ret && write_reg_val(QB_OS, 0x00, 2);
  ret = ret && write_reg_val(QC_OS, 0x00, 2);

  // 电流有效值OFFSET寄存器
  ret = ret && write_reg_val(IA_OS, 0x00, 2);
  ret = ret && write_reg_val(IB_OS, 0x00, 2);
  ret = ret && write_reg_val(IC_OS, 0x00, 2);

  // 失压阈值
  ret = ret && write_reg_val(LostVoltT, 0x4000, 2);

  // 过零阈值
  ret = ret && write_reg_val(ZXOT, 0x73, 2);

  // 脉冲口配置
  ret = ret && write_reg_val(CFCFG, 0x043210, 3);

  // 三相三线制模式配置
  ret = ret && write_reg_val(MODSEL, 0x33, 1);

  // 通道配置 电能累加型
  ret = ret && write_reg_val(EMUCFG, 0x480000, 3);

  // 通道使能
  ret = ret && write_reg_val(EMUCON, 0xFF, 3);

  // 关闭写使能
  ret = ret && write_reg_val(WREN, 0xDC, 1);

  return ret;
}

/**
 * @brief get UA/B/C, IA/B/C, PA/B/C QA/B/C, SA/B/C, EA/B/C/T
 *        and voltage frequence
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_all_data(Rn8302b_data *data)
{
  bool ret = true;
  ret = ret && get_volt(&data->volt);
  ret = ret && get_current(&data->curr);
  ret = ret && get_power(&data->power);
  ret = ret && get_reactive_power(&data->rtv_power);
  ret = ret && get_apparent_power(&data->apt_power);
  ret = ret && get_energy(&data->energy);
  ret = ret && get_volt_freq(&data->freq);

  return ret;
}

/**
 * @brief get A/B/C voltage RMS value
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_volt(Rn8302b_volt *data)
{
  int reg_val = get_reg_val(UA, 4);
  data->ua = params->volt_scale * reg_val;

  reg_val = get_reg_val(UB, 4);
  data->ub = params->volt_scale * reg_val;

  reg_val = get_reg_val(UC, 4);
  data->uc = params->volt_scale * reg_val;

  return true;
}

/**
 * @brief get A/B/C current RMS value
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_current(Rn8302b_curr *data)
{
  int reg_val = get_reg_val(IA, 4);
  data->ia = params->curr_scale * reg_val;

  reg_val = get_reg_val(IB, 4);
  data->ib = params->curr_scale * reg_val;

  reg_val = get_reg_val(IC, 4);
  data->ic = params->curr_scale * reg_val;

  return true;
}

/**
 * @brief get A/B/C power RMS value
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_power(Rn8302b_power *data)
{
  int reg_val = get_reg_val(PA, 4);
  data->pa = params->power_scale * reg_val;
  

  reg_val = get_reg_val(PB, 4);
  data->pb = params->power_scale * reg_val;

  reg_val = get_reg_val(PC, 4);
  data->pc = params->power_scale * reg_val;
  
  reg_val = get_reg_val(PT, 4);
  data->pt = params->power_scale * reg_val;

  return true;
}

/**
 * @brief get A/B/C reactive power RMS value
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_reactive_power(Rn8302b_reactive_power *data)
{
  int reg_val = get_reg_val(QA, 4);
  data->qa = params->rtv_power_scale * reg_val;

  reg_val = get_reg_val(QB, 4);
  data->qb = params->rtv_power_scale * reg_val;

  reg_val = get_reg_val(QC, 4); 
  data->qc = params->rtv_power_scale * reg_val;

  reg_val = get_reg_val(QT, 4);
  data->qt = params->rtv_power_scale * reg_val;  

  return true;
}

/**
 * @brief get A/B/C apparent power RMS value
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_apparent_power(Rn8302b_apparent_power *data)
{
  int reg_val = get_reg_val(SA, 4); 
  data->sa = params->apt_power_scale * reg_val;

  reg_val = get_reg_val(SB, 4);
  data->sb = params->apt_power_scale * reg_val;

  reg_val = get_reg_val(SC, 4);
  data->sc = params->apt_power_scale * reg_val;

  reg_val = get_reg_val(STA, 4);
  data->st = params->apt_power_scale * reg_val;
  return true;
}

/**
 * @brief get A/B/C energy and total energy RMS value
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_energy(Rn8302b_energy *data)
{
  int reg_val = get_reg_val(EPA, 3);
  data->ea = params->energy_scale * reg_val;

  reg_val = get_reg_val(EPB, 3);
  data->eb = params->energy_scale * reg_val;

  reg_val = get_reg_val(EPC, 3);
  data->ec = params->energy_scale * reg_val;

  reg_val = get_reg_val(EPT, 3);
  data->et = params->energy_scale * reg_val;

  return true;
}

/**
 * @brief get voltage frequence,unit Hz
 * 
 * @param data read data pointer
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::get_volt_freq(float *data)
{

  int reg_val = get_reg_val(UFreq, 3);
  *data = FSOC * 8 / reg_val;

  return true;
}

/**
 * @brief UA/B/C, IA/B/C gain calibration
 * 样正方法参照手册第69页 4.3功率样表法举例
 * @param reg_addr register adress
 * @return int gain regsister value
 */
int Rn8302b::get_calib_gain(unsigned short reg_addr)
{
  int reference = 0;
  int ret = 0;

  if (reg_addr == UA || reg_addr == UB || reg_addr == UC)
  {
    reference = RN8302B_REF_VOLTAGE_REG_VAL;
  }
  else if (reg_addr == IA || reg_addr == IB || reg_addr == IC)
  {
    reference = RN8302B_REF_CURRENT_REG_VAL;
  }
  else if (reg_addr == PA || reg_addr == PB || reg_addr == PC)
  {
    //return 0;
    reference = RN8302B_REF_POWER_REG_VAL;
  }
  else
  {
    return 0;
  }

  int reg_val = get_reg_val(reg_addr, 4);
  float err = (float)(reg_val - reference) / reference;
  err = (-err) / (err + 1);

  if (err >= 0)
  {
    ret = (int)(err * 32768);
  }
  else
  {
    ret = (int)(65536 + err * 32768);
  }
  return ret;
}

/**
 * @brief UA/B/C,IA/B/C offset calibration
 * 参照手册第68页 4.2.7 OFFSET校正
 * @param reg_addr register address
 * @return int offset register value
 */
int Rn8302b::get_calib_offset(unsigned short reg_addr)
{
  if (reg_addr != UA && reg_addr != UB && reg_addr != UC && reg_addr != IA && reg_addr != IB && reg_addr != IC)
  {
    return 0;
  }
  int avg_times = 12;

  int reg_val_total = 0;

  for (int i = 0; i < avg_times; i++)
  {
    reg_val_total += get_reg_val(reg_addr, 4);
    // resiger value refresh interval
    DELAY_MS(300);
  }

  reg_val_total /= avg_times;
  reg_val_total = reg_val_total * reg_val_total;
  reg_val_total = ~reg_val_total;
  short temp = (reg_val_total / 0x4000) & 0xFFFF;
  if (reg_val_total < 0)
  {
    temp |= 0x8000;
  }

  return temp;
}

/**
 * @brief istart_PS and istart_Q setting
 * 参照手册第37页 3.4.2启动电流阈值寄存器
 * @param k A相启动电流和标称电流的比值
 * @return int register setting value
 */
int Rn8302b::get_istart_setting(float k)
{
  int ret = get_reg_val(IA, 4);
  // istart = reg_val * K / 2^4
  ret = ret * k / 16;

  return ret;
}

/**
 * @brief lost voltage setting
 * 参照手册第37页 3.4.3失压阈值寄存器
 * @param k A相失压电压和额定电压的比值
 * @return int register setting value
 */
int Rn8302b::get_lost_voltage_setting(float k)
{
  int ret = get_reg_val(UA, 4);
  // lost voltage = reg_val * k / 2^12
  ret = ret * k / 4096;

  return ret;
}

/**
 * @brief 过零阈值寄存器设置
 * 参照手册第37页 3.4.4过零阈值寄存器
 * @param k 过零阈值和A相电流的比值
 * @return int register setting value
 */
int Rn8302b::get_zxot_setting(float k)
{
  int ret = get_reg_val(IA, 4);
  // zxot = reg_val * K / 2^12
  ret = ret * k / 4096;

  return ret;
}
/**
 * @brief 过零阈值寄存器设置
 * 参照手册第37页 3.4.4过零阈值寄存器
 * @param k 过零阈值和A相电流的比值
 * @return int register setting value
 */
unsigned short Rn8302b::get_phase_status(void)
{
  unsigned short ret = get_reg_val(PHASES, 2);

  return ret;
}
/**
 * @brief get register value
 * 
 * @param reg_addr register address
 * @param data_len read data length
 * @return int read data
 */
int Rn8302b::get_reg_val(unsigned short reg_addr, unsigned char data_len)
{
  int ret = 0;

  memset(buff, 0, sizeof(buff));
  if (read_reg(reg_addr, buff, data_len))
  {
    for (int i = 0; i < data_len; i++)
    {
      ret |= buff[i] << ((data_len - i - 1) * 8);
    }
  }

  return ret;
}

/**
 * @brief write register value
 * 
 * @param reg_addr register address
 * @param data write data
 * @param data_len write data length
 * @return true ok
 * @return false failed
 */
bool Rn8302b::write_reg_val(unsigned short reg_addr, int data, unsigned char data_len)
{
  memset(buff, 0, sizeof(buff));
  for (int i = 0; i < data_len; i++)
  {
    buff[i] = (unsigned char)(data >> ((data_len - i - 1) * 8));
  }

  return write_reg(reg_addr, buff, data_len);
}

/**
 * @brief read regester value
 * 
 * @param reg_addr register address
 * @param ret_data read data pointer
 * @param data_len read data length
 * @return true read ok
 * @return false read failed
 */
bool Rn8302b::read_reg(unsigned short reg_addr, unsigned char *ret_data, unsigned char data_len)
{
  if ((ret_data == NULL) || (data_len > RN8302B_REG_LEN_MAX))
  {
    return false;
  }

  bool ret = false;

  // Addr(1byte) + CMD(1byte) + Register length(max 4bytes) + CRC(1byte)
  unsigned char tmp[RN8302B_REG_LEN_MAX + 3];
  memset(tmp, 0, sizeof(tmp));

  tmp[0] = (unsigned char)reg_addr;
  tmp[1] = (unsigned char)(reg_addr >> 4) & 0xF0;

  spi_cs->set_hi();
  spi_cs->set_low();
  DELAY_MS(2);
  // send address and command
  int idx = 0;
  spi_read_write(tmp[idx++]);
  spi_read_write(tmp[idx++]);

  // read rn8302b feedback
  for (int i = 0; i < data_len + 1; i++)
  {
    tmp[idx++] = spi_read_write();
  }

  unsigned char calc_crc = crc->calc(tmp, idx - 1);

  // check crc
  if (calc_crc == tmp[idx - 1])
  {
    memcpy(ret_data, tmp + 2, data_len);
    ret = true;
  }

  spi_cs->set_hi();
  return ret;
}

/**
 * @brief write regester value
 * 
 * @param reg_addr register address
 * @param ret_data write data pointer
 * @param data_len write data length
 * @return true write ok
 * @return false write failed
 */
bool Rn8302b::write_reg(unsigned short reg_addr, unsigned char *data, unsigned char data_len)
{
  if ((data == NULL) || (data_len > RN8302B_REG_LEN_MAX))
  {
    return false;
  }

  bool ret = false;

  // Addr(1byte) + CMD(1byte) + Register length(max 4bytes) + CRC(1byte)
  unsigned char tmp[RN8302B_REG_LEN_MAX + 3];
  memset(tmp, 0, sizeof(tmp));
  int idx = 0;

  tmp[idx++] = (unsigned char)reg_addr;
  tmp[idx++] = ((unsigned char)(reg_addr >> 4) & 0xF0) | CMD_WR;

  memcpy(tmp + idx, data, data_len);
  idx += data_len;

  unsigned char calc_crc = crc->calc(tmp, idx);
  tmp[idx++] = calc_crc;

  spi_cs->set_hi();
  spi_cs->set_low();
  DELAY_MS(2);  

  for (int i = 0; i < idx; i++)
  {
    spi_read_write(tmp[i]);
  }

  memset(tmp, 0, sizeof(tmp));
  // 读取最后一次SPI写入的数据,验证是否写入成功
  tmp[0] = (unsigned char)WData;
  tmp[1] = (unsigned char)(WData >> 4) & 0xf0;

  // send address and command
  idx = 0;
  spi_read_write(tmp[idx++]);
  spi_read_write(tmp[idx++]);

  // read rn8302b feedback
  for (int i = 0; i < WDATA_REG_LEN + 1; i++)
  {
    tmp[idx++] = spi_read_write();
  }

  calc_crc = crc->calc(tmp, idx - 1);

  // check crc
  if (calc_crc == tmp[idx - 1])
  {
    ret = true;
  }

  spi_cs->set_hi();
  return ret;
}

/**
 * @brief spi read write
 * 
 * @param data write data
 * @return unsigned char read out data
 */
unsigned char Rn8302b::spi_read_write(unsigned char data)
{
  unsigned char ret = 0;

  spi->send_receive(&data, &ret, 1);

  return ret;
}
