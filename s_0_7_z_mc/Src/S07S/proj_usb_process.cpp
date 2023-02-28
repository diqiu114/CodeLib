#include "proj_usb_process.h"
#include "class_init.h"
#include "dfs_proto.h"
#include "cell_comm.h"
#include "my_stm32_ftl.h"
#include "task.h"
#include "debug.h"
#include "diskio.h"

#define CMD_IDX 0
#define PARA_PART 8

#if (USE_IWDG)
extern TimerHandle_t Iwdg_timer_handle;
#endif

#define CELL_COMM_DELAY_MAX (20000)

extern TaskHandle_t Cell_comm_handle;
extern QueueHandle_t Cell_comm_cpl_queue;

Usb_process::Usb_process(USBD_HandleTypeDef *usb_handle, usb_idle_callback callback)
    : Usb_comm(usb_handle, USB_COMM_BUFF_SIZE, USB_COMM_BUFF_SIZE, callback)
{
  usb_prot = new DFS_proto(PROT_VER2);
  uc_send_buff = NULL;
}

#define START_HISDATA_REC_CMD "starthisdata"
#define STOP_HISDATA_REC_CMD "stophisdata"
#define PRINT_FAT_INFO_CMD "printfatfsinfo"
#define PERCENT_PRINT_CNT 100
TaskHandle_t HisdataRecHandle = NULL;
uint32_t hisDataRecStart = 0;
void His_Data_Rec(void *pvParameters)
{
  hisDataRecStart = 1;
  uint32_t recNum = (uint32_t)pvParameters;
  uint32_t recCnt = 0;
  char printBuf[100];
  uint32_t printLen;
  vTaskDelay(500);
  printLen = sprintf(printBuf, "his data record thread start,recnum:%d\r\n", recNum);
  Host_comm->send((unsigned char *)printBuf, printLen);
  while (hisDataRecStart && recCnt != recNum) {
      taskENTER_CRITICAL();
      Batt_hist_data_store->store_data();
      taskEXIT_CRITICAL();
      recCnt++;
      if (recCnt % PERCENT_PRINT_CNT == 0) {
        printLen = sprintf(printBuf, "his record process:%d%%\r\n", recCnt * 100 / recNum);
        Host_comm->send((unsigned char *)printBuf, printLen);
      }
      vTaskDelay(25);
  }
  vTaskDelay(500);
  printLen = sprintf(printBuf, "his data record thread exit\r\n");
  Host_comm->send((unsigned char *)printBuf, printLen);
  taskENTER_CRITICAL();
  vTaskDelete(HisdataRecHandle);
  HisdataRecHandle = NULL;
  taskEXIT_CRITICAL();
}

extern FATFS USERFatFS;
bool commandHandle(COMM_TYPE_t commType,char *command,void *para);
void Usb_process::process(void)
{
  // get data from usb cdc
  unsigned int pack_len = read_all(uc_rev_buff);
  if (pack_len == 0)
  {
    return;
  }
  
  if(commandHandle(COMM_TYPE_COM,(char *)uc_rev_buff,NULL)) {
    return;
  }

  // check pack if complete
  unsigned int data_len = usb_prot->unpack(uc_rev_buff, pack_len, uc_rev_buff);
  if (data_len == 0)
  {
    if (memcmp(uc_rev_buff, START_HISDATA_REC_CMD, strlen(START_HISDATA_REC_CMD)) == 0) {
           if (HisdataRecHandle != NULL) {
               uint32_t sendLen = sprintf((char *)uc_rev_buff, "his data record task running\r\n");
               send(uc_rev_buff, sendLen);
               return;
           }
           uint32_t recNum = atoi((char *)uc_rev_buff + strlen(START_HISDATA_REC_CMD));
           xTaskCreate(His_Data_Rec, "Hisdatarec", 256, (void *)recNum, configMAX_PRIORITIES - 2, &HisdataRecHandle);
           uint32_t sendLen = sprintf((char *)uc_rev_buff, "start his data record,recnum:%d\r\n", recNum);
           send(uc_rev_buff, sendLen);
           return;
       } else if (memcmp(uc_rev_buff, STOP_HISDATA_REC_CMD, strlen(STOP_HISDATA_REC_CMD)) == 0) {
           hisDataRecStart = 0;
           uint32_t sendLen = sprintf((char *)uc_rev_buff, "stop his data record, wait thread exit\r\n");
           send(uc_rev_buff, sendLen);
           return;
       } else if (memcmp(uc_rev_buff, PRINT_FAT_INFO_CMD, strlen(PRINT_FAT_INFO_CMD)) == 0) {          
           uint32_t sendLen = sprintf((char *)uc_rev_buff, "start output fatinfo:\r\n");
           send(uc_rev_buff, sendLen);
           uint32_t sectorSize = sizeof(USERFatFS.win);
           disk_ioctl(0, GET_SECTOR_SIZE, &sectorSize);
           uint8_t *sectorData = new uint8_t[sectorSize];
           for (uint32_t i = USERFatFS.volbase; i <= USERFatFS.database; i++) {
             if (disk_read(0, sectorData, i, 1) == RES_OK) {
                 sendLen = sprintf((char *)uc_rev_buff, "sector[%d]:\r\n", i);
                 send(uc_rev_buff, sendLen);
                 send(sectorData, sectorSize);
             } else {
                 sendLen = sprintf((char *)uc_rev_buff, "sector[%d] readfail\r\n", i);
                 send(uc_rev_buff, sendLen);
             }
           }
           delete []sectorData;
           return;
       } else {
           ;
       }
       return;if (memcmp(uc_rev_buff, START_HISDATA_REC_CMD, strlen(START_HISDATA_REC_CMD)) == 0) {
       if (HisdataRecHandle != NULL) {
           uint32_t sendLen = sprintf((char *)uc_rev_buff, "his data record task running\r\n");
           send(uc_rev_buff, sendLen);
           return;
       }
       uint32_t recNum = atoi((char *)uc_rev_buff + strlen(START_HISDATA_REC_CMD));
       xTaskCreate(His_Data_Rec, "Hisdatarec", 256, (void *)recNum, configMAX_PRIORITIES - 2, &HisdataRecHandle);
       uint32_t sendLen = sprintf((char *)uc_rev_buff, "start his data record,recnum:%d\r\n", recNum);
       send(uc_rev_buff, sendLen);
       return;
     } else if (memcmp(uc_rev_buff, STOP_HISDATA_REC_CMD, strlen(STOP_HISDATA_REC_CMD)) == 0) {
       hisDataRecStart = 0;
       uint32_t sendLen = sprintf((char *)uc_rev_buff, "stop his data record, wait thread exit\r\n");
       send(uc_rev_buff, sendLen);
       return;
     } else if (memcmp(uc_rev_buff, PRINT_FAT_INFO_CMD, strlen(PRINT_FAT_INFO_CMD)) == 0) {          
       uint32_t sendLen = sprintf((char *)uc_rev_buff, "start output fatinfo:\r\n");
       send(uc_rev_buff, sendLen);
       uint32_t sectorSize = sizeof(USERFatFS.win);
       disk_ioctl(0, GET_SECTOR_SIZE, &sectorSize);
       uint8_t *sectorData = new uint8_t[sectorSize];
       for (uint32_t i = USERFatFS.volbase; i <= USERFatFS.database; i++) {
         if (disk_read(0, sectorData, i, 1) == RES_OK) {
             sendLen = sprintf((char *)uc_rev_buff, "sector[%d]:\r\n", i);
             send(uc_rev_buff, sendLen);
             send(sectorData, sectorSize);
         } else {
             sendLen = sprintf((char *)uc_rev_buff, "sector[%d] readfail\r\n", i);
             send(uc_rev_buff, sendLen);
         }
       }
       delete []sectorData;
       return;
     } else {
       ;
     }
     return;
  }

  // command parse and handle
  cmd = (Usb_cmd)uc_rev_buff[CMD_IDX];
  unsigned char dmy = 0;

  switch (cmd)
  {
  case USB_READ_TIME:
    reply_date_time();
    break;   
  case USB_READ_SYS_PARA:
#if S07S
    Sys_paras.batt_info.nomial_cap = 260;
    reply_data(USB_READ_SYS_PARA, &Sys_paras, sizeof(Sys_paras));
    Sys_paras.batt_info.nomial_cap = 100;
#elif S07R
    Sys_paras.batt_info.nomial_cap = 180;
    reply_data(USB_READ_SYS_PARA, &Sys_paras, sizeof(Sys_paras));
    Sys_paras.batt_info.nomial_cap = 100;
#endif
    break;
  case USB_READ_CELL_PARA:
    reply_data(USB_READ_CELL_PARA, (void *)Cell_adc_config_paras, sizeof(Cell_adc_config_paras));
    break;
  case USB_READ_DEV_PARA:
    reply_data(USB_READ_DEV_PARA, &Dev_paras, sizeof(Dev_paras));
    break;
  case USB_READ_USER_PARA:
    reply_data(USB_READ_USER_PARA, &User_paras, sizeof(User_paras));
    break;
  case USB_READ_REAL_DATA:
    //reset cell data
    memset(&Batt_data_buff.cell_data[0], 0, sizeof(Batt_data_buff.cell_data));
    xQueueReset(Cell_comm_cpl_queue);
    // resume cell comm
    vTaskResume(Cell_comm_handle);

    xQueueReceive(Cell_comm_cpl_queue, &dmy, CELL_COMM_DELAY_MAX);

    reply_data(USB_READ_REAL_DATA, &Batt_data_buff, sizeof(Batt_data_buff));
    break;
  case USB_READ_HIST_DATA_HEADER:
    if (!reply_file_header(Hist_data_file))
    {
      reply_status(USB_READ_HIST_DATA_HEADER, USB_FAIL);
    }
    break;
  case USB_READ_HIST_DATA:
    if (!reply_file_data(Hist_data_file))
    {
      reply_status(USB_READ_HIST_DATA, USB_FAIL);
    }
    break;
  case USB_READ_ALARM_DATA_HEADER:
    if (!reply_file_header(Alm_data_file))
    {
      reply_status(USB_READ_ALARM_DATA_HEADER, USB_FAIL);
    }
    break;
  case USB_READ_ALARM_DATA:
    if (!reply_file_data(Alm_data_file))
    {
      reply_status(USB_READ_ALARM_DATA, USB_FAIL);
    }
    break;
  case USB_READ_FLASH_SIZE:
    reply_flash_size();
    break;
  case USB_CELL_COMM:
    modbus_comm_pross((uc_rev_buff + USB_COMM_CMD_LEN)[1]);
    break;
  case USB_READ_MC_REAL_DATA:
    reply_data(USB_READ_MC_REAL_DATA, &Batt_data_buff, sizeof(Batt_data_buff.total_data) + sizeof(Batt_data_buff.soc));
    break;
  case USB_SET_TIME:
    set_date_time(uc_rev_buff + USB_COMM_CMD_LEN);
    break;
  case USB_WRITE_SYS_PARA:
    memcpy(&Sys_paras.dev_id, uc_rev_buff + USB_COMM_CMD_LEN, sizeof(Sys_paras.dev_id));
    if (Sys_para_file->write(&Sys_paras.dev_id))
    {
      reply_status(USB_WRITE_SYS_PARA, USB_OK);
    }
    else
    {
      reply_status(USB_WRITE_SYS_PARA, USB_FAIL);
    }
    break;
  case USB_WRITE_DEV_PARA:
    memcpy((unsigned char *)&Dev_paras , uc_rev_buff + USB_COMM_CMD_LEN, sizeof(Dev_paras));
    if (Dev_para_file->write(&Dev_paras))
    {
      unsigned char temp_para_offset = VOLT_CH_CNT + CUR_CH_CNT;
      reply_status(USB_WRITE_DEV_PARA, USB_OK);

      tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[0])), 0);
      tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[1])), 1);
      tb_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[2])), 2);

      Pt1000_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[temp_para_offset])), 0);
      Pt1000_adc->modify_calib(new Polynomial1(new Py1_params(&Dev_paras.calib.total_batt[temp_para_offset + 1])), 1);
    }
    else
    {
      reply_status(USB_WRITE_DEV_PARA, USB_FAIL);
    }
    break;
  case USB_WRITE_USER_PARA:
    memcpy((unsigned char *)&User_paras , uc_rev_buff + USB_COMM_CMD_LEN, sizeof(User_paras));
    if (User_para_file->write(&User_paras))
    {
      reply_status(USB_WRITE_USER_PARA, USB_OK);
    }
    else
    {
      reply_status(USB_WRITE_USER_PARA, USB_FAIL);
    }
    break;
  case USB_WRITE_SOC_INIT_FLAG:
    memcpy(&Dev_paras.soc_init, uc_rev_buff + USB_COMM_CMD_LEN, sizeof(Dev_paras.soc_init));
    if (Dev_para_file->write(&Dev_paras))
    {
      reply_status(USB_WRITE_SOC_INIT_FLAG, USB_OK);
    }
    else
    {
      reply_status(USB_WRITE_SOC_INIT_FLAG, USB_FAIL);
    }
    break;
  case USB_WRITE_SOC:
    write_soc(uc_rev_buff + USB_COMM_CMD_LEN);
    break;
  case USB_WRITE_SOH:
    memcpy(&Soh_record.soh, uc_rev_buff + USB_COMM_CMD_LEN, sizeof(Soh_record.soh));
    if(Soh_record_file->write(&Soh_record))
    {
      reply_status(USB_WRITE_SOH, USB_OK);
    }
    else
    {
      reply_status(USB_WRITE_SOH, USB_FAIL);
    }
    break;
  case USB_CLEAR_HIST_DATA:
    if ((Hist_data_file->clear() == F_OK) && (Alm_data_file->clear() == F_OK))
    {
      reply_status(USB_CLEAR_HIST_DATA, USB_OK);
#if (USE_IWDG)
      xTimerStop(Iwdg_timer_handle, 0);
#endif
    }
    else
    {
      reply_status(USB_CLEAR_HIST_DATA, USB_FAIL);
    }
    break;
  case USB_PROGRAM_UPDATE:
    break;
  case USB_RESET_MC:
    reply_status(USB_RESET_MC, USB_OK);
#if (USE_IWDG)
    xTimerStop(Iwdg_timer_handle, 0);
#endif
    break;
  case USB_FORMAT_FLASH:
    break;
  default:
    break;
  }
}

void Usb_process::write_soc(void *data)
{
  if (data)
  {
    float val = 0;
    memcpy(&val, data, sizeof(val));

    Batt_soc->set_cap(val, true);

    // modify dishcarged capacity
    if (Discharge_soc_record != NULL)
    {
      float nomial_cap = Batt_soc->get_nomial_cap();

      Discharge_soc_record->set_discharged_cap(((val / 100 * nomial_cap ) - nomial_cap) / Discharge_soc_record->get_charge_efficiency(), true);
    }

    reply_status(USB_WRITE_SOC, USB_OK);
  }
  else
  {
    reply_status(USB_WRITE_SOC, USB_FAIL);
  }
}

bool Usb_process::cell_comm(unsigned char *data, unsigned int data_len)
{
  bool resp = data[0];
  if (resp)
  {
    unsigned int resp_len = Cell_node->transparent(data + 1, data_len - 1, true, uc_rev_buff);
    if (resp_len > 0)
    {
      return send(uc_rev_buff, resp_len);
    }
    else
    {
      return false;
    }
  }
  else
  {
    Cell_node->transparent(data + 1, data_len - 1);
  }

  return true;
}

bool Usb_process::reply_file_header(File *file)
{
  if (file == NULL)
  {
    return false;
  }

  File_header header;
  bool ret = true;
  ret = file->read_header(&header);
  if (ret != F_OK)
  {
    return false;
  }

  // send header
  ret = send((unsigned char *)(&header), sizeof(header));
  if (ret)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Usb_process::reply_file_data(File *file)
{
  if (file == NULL)
  {
    return false;
  }

  bool ret = file->forward_data();
  if (ret)
  {
    unsigned char test[] = {'-', '-', 'E', 'O', 'F', '-', '-'};

    send(test, sizeof(test));
  }

  return ret;
}

void Usb_process::reply_flash_size(void)
{
  FATFS *fs;
  DWORD fre_clust, fre_sect, tot_sect;
  unsigned int flash_size[2] = {0};

  if (f_getfree(DRIVER_NAME, &fre_clust, &fs) == FR_OK)
  {
    tot_sect = ((fs->n_fatent - 2) * fs->csize) / 2;
    fre_sect = (fre_clust * fs->csize) / 2;

    flash_size[0] = tot_sect;
    flash_size[1] = fre_sect;
  }

  reply_data(USB_READ_FLASH_SIZE, &flash_size, sizeof(flash_size));
}

void Usb_process::reply_data(Usb_cmd cmd, void *data, unsigned int len)
{
  unsigned data_len = len + USB_COMM_CMD_LEN;
  unsigned int buff_len = data_len + usb_prot->prot_len();

  uc_send_buff = new unsigned char[buff_len];
  if (uc_send_buff == NULL)
  {
    return;
  }

  memset(uc_send_buff, 0, buff_len);

  uc_send_buff[0] = cmd;
  memcpy(uc_send_buff + USB_COMM_CMD_LEN, data, len);

  unsigned int pack_len = usb_prot->pack(uc_send_buff, data_len, uc_send_buff);

  send(uc_send_buff, pack_len);

  delete[] uc_send_buff;
  uc_send_buff = NULL;
}

void Usb_process::reply_date_time(void)
{
  unsigned int ts = Rtc->get_ts();
  reply_data(USB_READ_TIME, &ts, sizeof(ts));
}

void Usb_process::set_date_time(unsigned char *data)
{
  unsigned int ts = 0;
  memcpy(&ts, data, sizeof(ts));

  if (Rtc->set_datetime(ts))
  {
    reply_status(USB_SET_TIME, USB_OK);
  }
  else
  {
    reply_status(USB_SET_TIME, USB_FAIL);
  }
}

void Usb_process::reply_status(Usb_cmd cmd, Usb_status status)
{
  unsigned int buff_len = sizeof(status) + USB_COMM_CMD_LEN + usb_prot->prot_len();

  uc_send_buff = new unsigned char[buff_len];
  if (uc_send_buff == NULL)
  {
    return;
  }

  memset(uc_send_buff, 0, buff_len);
  unsigned int idx = 0;

  uc_send_buff[idx++] = cmd;
  uc_send_buff[idx++] = (unsigned char)(status);

  unsigned int pack_len = usb_prot->pack(uc_send_buff, idx, uc_send_buff);

  send(uc_send_buff, pack_len);

  delete[] uc_send_buff;
  uc_send_buff = NULL;
}

unsigned short recvbuff[600] = {0};
void Usb_process::modbus_comm_pross(short cell_cmd)
{
  Modbus_data reg_info = {0};
  reg_info.id = (uc_rev_buff + USB_COMM_CMD_LEN)[2];
  unsigned int ret_len = 0;
  char index = 0;
//  switch (cell_cmd)
//  {
//  case GET_ALL:
//  case CALIB_MODE:
  if(cell_cmd == GET_ALL || cell_cmd == CALIB_MODE)
  {
    reg_info.cmd = 0x04;
    reg_info.reg_cnt = ACQ_MAX_CNT;
    reg_info.reg_addr = REG_ADDR_CH_DROP_VALUE_START;
    ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff);
    //must delay 1ms
    DELAY_MS(10);
    reg_info.cmd = 0x03;
    reg_info.reg_cnt = (ACQ_MAX_CNT  / 2) * CH_CALIB_CONFIG_CNT_PER;
    reg_info.reg_addr = REG_ADDR_CH_ENABEL_START;
    ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff + ret_len);
    reg_info.reg_cnt = (ACQ_MAX_CNT  / 2 + ACQ_MAX_CNT  % 2) * CH_CALIB_CONFIG_CNT_PER;
    reg_info.reg_addr = REG_ADDR_CH_ENABEL_START + (ACQ_MAX_CNT  / 2) * CH_CALIB_CONFIG_CNT_PER;
    ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff + ret_len);
    reg_info.reg_cnt = ACQ_MAX_CNT * CH_RATE_CONFIG_CNT_PER;
    reg_info.reg_addr = REG_ADDR_CH_RATE_SCALE_START;
    ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff + ret_len);
    reg_info.cmd = 0x04;
    reg_info.reg_cnt = ACQ_MAX_CNT;
    reg_info.reg_addr = REG_ADDR_CH_VALUE_START;
    ret_len += Comm_cell_modbuse->read_reg(&reg_info, recvbuff + ret_len);
    if (ret_len == ACQ_MAX_CNT * 2 + ACQ_MAX_CNT * CH_CALIB_CONFIG_CNT_PER + ACQ_MAX_CNT * CH_RATE_CONFIG_CNT_PER)
    {
      int len = usb_prot->pack((unsigned char *)recvbuff,ret_len * 2,(unsigned char *)recvbuff);
      send((unsigned char *)recvbuff, len);
    }
  }
  #if USE_AFE_CONFIG
  else if(cell_cmd >= CALIB_CH_START &&  cell_cmd <= CALIB_CH_START +  ACQ_MAX_CNT)
  {
    index = cell_cmd - CALIB_CH_START;
    reg_info.cmd = 0x06;
    reg_info.reg_addr = REG_ADDR_CH_ENABEL_START + index * CH_CALIB_CONFIG_CNT_PER;
    Cell_adc_config_paras[index].is_enable = (uc_rev_buff + USB_COMM_CMD_LEN)[3] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[4];
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, Cell_adc_config_paras[index].is_enable);
    if(ret_len == 1)
    {
      Cell_config_para_file->write(&Cell_adc_config_paras);
    }
    reg_info.reg_addr = REG_ADDR_ACQ_MODE_START + index * CH_CALIB_CONFIG_CNT_PER;
    Cell_adc_config_paras[index].acq_mode = (Adc_acq_mode_e)((uc_rev_buff + USB_COMM_CMD_LEN)[5] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[6]);
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, Cell_adc_config_paras[index].acq_mode);
    if(ret_len == 2)
    {
      Cell_config_para_file->write(&Cell_adc_config_paras);
    }
    reg_info.reg_addr = REG_ADDR_ACQ_TYPE_START + index * CH_CALIB_CONFIG_CNT_PER;
    Cell_adc_config_paras[index].acq_type = (Adc_acq_type_e)((uc_rev_buff + USB_COMM_CMD_LEN)[7] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[8]);
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, Cell_adc_config_paras[index].acq_type);
    if(ret_len == 3)
    {
      Cell_config_para_file->write(&Cell_adc_config_paras);
    }
  
    reg_info.reg_addr = REG_ADDR_CH_CALIB_SCALE_START + index * CH_CALIB_CONFIG_CNT_PER;
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[9] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[10]);
    reg_info.reg_addr = REG_ADDR_CH_CALIB_K_VAL_START + index * CH_CALIB_CONFIG_CNT_PER;
    ret_len = Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[11] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[12]);
    reg_info.reg_addr = REG_ADDR_CH_CALIB_B_VAL_START + index * CH_CALIB_CONFIG_CNT_PER;
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[13] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[14]);
    reg_info.reg_addr = REG_ADDR_CH_RATE_SCALE_START + index * CH_RATE_CONFIG_CNT_PER;
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[15] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[16]);
    reg_info.reg_addr = REG_ADDR_CH_RATE_K_VAL_START + index * CH_RATE_CONFIG_CNT_PER;
    ret_len = Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[17] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[18]);
    reg_info.reg_addr = REG_ADDR_CH_RATE_B_VAL_START + index * CH_RATE_CONFIG_CNT_PER;
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[19] << 8 | (uc_rev_buff + USB_COMM_CMD_LEN)[20]);
    reg_info.reg_addr = CALDATA_OVER_FLAG_ADDR;
    ret_len += Comm_cell_modbuse->write_reg(&reg_info, CALDATA_OVER_VAL);
    if (ret_len == 10)
    {
      //success
    }
    
    Dev_paras.volt_cnt = 0;
    Dev_paras.temp_cnt = 0;
    for(int i = 0; i < ACQ_MAX_CNT; i++)
    {
      if(Cell_adc_config_paras[i].is_enable)
      {
        if(Cell_adc_config_paras[i].acq_type == TYPE_TEMP)
        {
          Dev_paras.temp_cnt++;
        }
        else if(Cell_adc_config_paras[i].acq_type == TYPE_VOLT)
        {
          Dev_paras.volt_cnt++;
        }
      }
    }
    if (Dev_para_file->write(&Dev_paras))
    {
      reply_status(USB_CELL_COMM, USB_OK);
    }
    else
    {
      reply_status(USB_CELL_COMM, USB_FAIL);
    }
  }
  #endif
  else if(cell_cmd == GET_SOFT_VER)
  {
    reg_info.cmd = 0x04;
    reg_info.reg_cnt = 6;
    reg_info.reg_addr = REG_ADDR_SW_VER_X;
    ret_len = Comm_cell_modbuse->read_reg(&reg_info, recvbuff);
    if (ret_len > 0)
    {
      //             int len = pack_proto->pack((unsigned char *)recvbuff,ret_len * 2,(unsigned char *)recvbuff);
      send((unsigned char *)recvbuff, ret_len * 2);
    }
  }
 
  else if(cell_cmd ==  CALIB_ID)
  {
    reg_info.cmd = 0x06;
    reg_info.reg_addr = REG_ADDR_DEV_ID;
    ret_len = Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[3]);
    if (ret_len == 1)
    {
      //success
    }
  }
  else if(cell_cmd ==  CALIB_RESET)
  {
    is_first = true;
    reg_info.cmd = 0x06;
    reg_info.reg_addr = REG_ADDR_RESTORE_CALIB_VAL;
    ret_len = Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[3]);
    if (ret_len == 1)
    {
      //success
    }
  }

  else if(cell_cmd ==  UPDATE)
  {
    reg_info.cmd = 0x06;
    reg_info.reg_addr = REG_ADDR_PROGRAM_UPGRADE;
    ret_len = Comm_cell_modbuse->write_reg(&reg_info, (uc_rev_buff + USB_COMM_CMD_LEN)[3]);
    if (ret_len == 1)
    {
      //success
    }
  }
}

Usb_process::~Usb_process()
{
}
