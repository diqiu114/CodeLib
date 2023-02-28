#include "ymodem.h"
#include "string.h"

#define CRC16_F /* activate the CRC16 integrity */

Ymodem::Ymodem(Ymodem_tranceiver_if *_tranceiver, Flash_ops_if *_flash_ops)
{
  tranceiver = _tranceiver;
  flash_ops = _flash_ops;

  flash_start_addr = flash_ops->get_start_addr();
  flash_size = flash_ops->get_flash_size();
}

Ymodem::~Ymodem()
{
  if (tranceiver != NULL)
  {
    delete tranceiver;
    tranceiver = NULL;
  }
}

bool Ymodem::download(void)
{
  bool ret = false;

  put_string((unsigned char *)"Press '1' to download image\n\r");
  put_string((unsigned char *)"Press '2' to upload image\n\r");
  put_string((unsigned char *)"Press '3' to exit transmission\n\r");
  unsigned char key = 0;
//  unsigned char status = 0;
  bool end_session = false;
  COM_StatusTypeDef result;

  while (1)
  {
    key = 0;
    bool rev_ok = (tranceiver->receive(&key, sizeof(key), RX_TIMEOUT) == YMODEM_OK);
    switch (key)
    {
    case '1':
      put_string((unsigned char *)"Waiting for the file to be sent ... (press 'a' to abort)\n\r");

      result = receive();
      if (result == COM_OK)
      {
        ret = true;
        put_string((unsigned char *)"\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n File Name: ");
        put_string(file_name_str);
        put_string((unsigned char *)"\n\r Size: ");
        put_string(file_size_str);
        put_string((unsigned char *)" Bytes\r\n");
        put_string((unsigned char *)"-------------------\n");
        put_string((unsigned char *)"***** Note: Do NOT turn power off immediately!! *****\n\r");
      }
      else if (result == COM_LIMIT)
      {
        put_string((unsigned char *)"\n\n\rThe image size is higher than the allowed space memory!\n\r");
      }
      else if (result == COM_DATA)
      {
        put_string((unsigned char *)"\n\n\rVerification failed!\n\r");
      }

      else if (result == COM_ABORT)
      {
        put_string((unsigned char *)"\r\n\nAborted by user.\n\r");
      }
      else
      {
        put_string((unsigned char *)"\n\rFailed to receive the file!\n\r");
      }
      end_session = true;
      break;
    case '2':

//      put_string((uint8_t *)"\n\n\rSelect Receive File\n\r");

//      tranceiver->receive(&status, 1, RX_TIMEOUT);
//      if (status == CRC16)
//      {
//        /* Transmit the flash image through ymodem protocol */
//        status = upload((uint8_t *)flash_ops->get_start_addr(), (const uint8_t *)"UploadedFlashImage.bin", flash_ops->get_flash_size());

//        if (status != 0)
//        {
//          put_string((uint8_t *)"\n\rError Occurred while Transmitting File\n\r");
//        }
//        else
//        {
//          put_string((uint8_t *)"\n\rFile uploaded successfully \n\r");
//        }
//      }
      
      break;
    case '3':
      put_string((unsigned char *)"\n\r ***** Quit ymodem transmission! ***** \n\r");
      end_session = true;
      ret = false;
      break;
    default:
      break;
    }

    if (end_session)
    {
      break;
    }
  }

  return ret;
}

/**
  * @brief  Receive a packet from sender
  * @param  data
  * @param  length
  *     0: end of transmission
  *     2: abort by sender
  *    >0: packet length
  * @param  timeout
  * @retval YMODEM_OK: normally return
  *         YMODEM_BUSY: abort by user
  */
YMODEM_STATUS Ymodem::receive_packet(unsigned char *p_data, unsigned int *p_length, unsigned int timeout)
{
  unsigned int crc;
  unsigned int packet_size = 0;
  YMODEM_STATUS status;
  unsigned char char1;

  *p_length = 0;
  status = tranceiver->receive(&char1, 1, timeout);

  if (status == YMODEM_OK)
  {
    switch (char1)
    {
    case SOH:
      packet_size = PACKET_SIZE;
      break;
    case STX:
      packet_size = PACKET_1K_SIZE;
      break;
    case EOT:
      break;
    case CA:
      if ((tranceiver->receive(&char1, 1, timeout) == YMODEM_OK) && (char1 == CA))
      {
        packet_size = 2;
      }
      else
      {
        status = YMODEM_ERROR;
      }
      break;
    case ABORT1:
    case ABORT2:
      status = YMODEM_BUSY;
      break;
    default:
      status = YMODEM_ERROR;
      break;
    }
    *p_data = char1;

    if (packet_size >= PACKET_SIZE)
    {
      status = tranceiver->receive(&p_data[PACKET_NUMBER_INDEX], packet_size + PACKET_OVERHEAD_SIZE, timeout);

      /* Simple packet sanity check */
      if (status == YMODEM_OK)
      {
        if (p_data[PACKET_NUMBER_INDEX] != ((p_data[PACKET_CNUMBER_INDEX]) ^ NEGATIVE_BYTE))
        {
          packet_size = 0;
          status = YMODEM_ERROR;
        }
        else
        {
          /* Check packet CRC */
          crc = p_data[packet_size + PACKET_DATA_INDEX] << 8;
          crc += p_data[packet_size + PACKET_DATA_INDEX + 1];
          if (calc_CRC16(&p_data[PACKET_DATA_INDEX], packet_size) != crc)
          {
            packet_size = 0;
            status = YMODEM_ERROR;
          }
        }
      }
      else
      {
        packet_size = 0;
      }
    }
  }
  *p_length = packet_size;
  return status;
}

/**
  * @brief  Prepare the first block
  * @param  p_data:  output buffer
  * @param  p_file_name: name of the file to be sent
  * @param  length: length of the file to be sent in bytes
  * @retval None
  */
void Ymodem::prepare_intial_packet(unsigned char *p_data, const unsigned char *p_file_name, unsigned int length)
{
  unsigned int i, j = 0;
  unsigned char astring[10];

  /* first 3 bytes are constant */
  p_data[PACKET_START_INDEX] = SOH;
  p_data[PACKET_NUMBER_INDEX] = 0x00;
  p_data[PACKET_CNUMBER_INDEX] = 0xff;

  /* Filename written */
  for (i = 0; (p_file_name[i] != '\0') && (i < FILE_NAME_LENGTH); i++)
  {
    p_data[i + PACKET_DATA_INDEX] = p_file_name[i];
  }

  p_data[i + PACKET_DATA_INDEX] = 0x00;

  /* file size written */
  str_conv.int_to_str(astring, length);
  i = i + PACKET_DATA_INDEX + 1;
  while (astring[j] != '\0')
  {
    p_data[i++] = astring[j++];
  }

  /* padding with zeros */
  for (j = i; j < PACKET_SIZE + PACKET_DATA_INDEX; j++)
  {
    p_data[j] = 0;
  }
}

/**
  * @brief  Prepare the data packet
  * @param  p_source: pointer to the data to be sent
  * @param  p_packet: pointer to the output buffer
  * @param  pkt_nr: number of the packet
  * @param  size_blk: length of the block to be sent in bytes
  * @retval None
  */
void Ymodem::prepare_packet(unsigned char *p_source, unsigned char *p_packet, unsigned char pkt_nr, unsigned int size_blk)
{
  unsigned char *p_record;
  unsigned int i, size, packet_size;

  /* Make first three packet */
  packet_size = size_blk >= PACKET_1K_SIZE ? PACKET_1K_SIZE : PACKET_SIZE;
  size = size_blk < packet_size ? size_blk : packet_size;
  if (packet_size == PACKET_1K_SIZE)
  {
    p_packet[PACKET_START_INDEX] = STX;
  }
  else
  {
    p_packet[PACKET_START_INDEX] = SOH;
  }
  p_packet[PACKET_NUMBER_INDEX] = pkt_nr;
  p_packet[PACKET_CNUMBER_INDEX] = (~pkt_nr);
  p_record = p_source;

  /* Filename packet has valid data */
  for (i = PACKET_DATA_INDEX; i < size + PACKET_DATA_INDEX; i++)
  {
    p_packet[i] = *p_record++;
  }
  if (size <= packet_size)
  {
    for (i = size + PACKET_DATA_INDEX; i < packet_size + PACKET_DATA_INDEX; i++)
    {
      p_packet[i] = 0x1A; /* EOF (0x1A) or 0x00 */
    }
  }
}

/**
  * @brief  Update CRC16 for input byte
  * @param  crc_in input value 
  * @param  input byte
  * @retval None
  */
unsigned short Ymodem::update_CRC16(unsigned short crc_in, unsigned char byte)
{
  unsigned int crc = crc_in;
  unsigned int in = byte | 0x100;

  do
  {
    crc <<= 1;
    in <<= 1;
    if (in & 0x100)
      ++crc;
    if (crc & 0x10000)
      crc ^= 0x1021;
  }

  while (!(in & 0x10000));

  return crc & 0xffffu;
}

/**
  * @brief  Cal CRC16 for YModem Packet
  * @param  data
  * @param  length
  * @retval None
  */
unsigned short Ymodem::calc_CRC16(const unsigned char *p_data, unsigned int size)
{
  unsigned int crc = 0;
  const unsigned char *dataEnd = p_data + size;

  while (p_data < dataEnd)
    crc = update_CRC16(crc, *p_data++);

  crc = update_CRC16(crc, 0);
  crc = update_CRC16(crc, 0);

  return crc & 0xffffu;
}

/**
  * @brief  Calculate Check sum for YModem Packet
  * @param  p_data Pointer to input data
  * @param  size length of input data
  * @retval unsigned char checksum value
  */
unsigned char Ymodem::calc_checksum(const unsigned char *p_data, unsigned int size)
{
  unsigned int sum = 0;
  const unsigned char *p_data_end = p_data + size;

  while (p_data < p_data_end)
  {
    sum += *p_data++;
  }

  return (sum & 0xffu);
}

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  Receive a file using the ymodem protocol with CRC16.
  * @param  p_size The size of the file.
  * @retval COM_StatusTypeDef result of reception/programming
  */
COM_StatusTypeDef Ymodem::receive(void)
{
  unsigned int i, packet_length, session_done = 0, file_done, errors = 0, session_begin = 0;
  unsigned int flashdestination, ramsource, filesize;
  unsigned char *file_ptr;
  unsigned char tmp, packets_received;
  unsigned int p_size = 0;
  COM_StatusTypeDef result = COM_OK;
  bool header_received = false;
  /* Initialize flashdestination variable */
  flashdestination = flash_start_addr;

  while ((session_done == 0) && (result == COM_OK))
  {
    packets_received = 0;
    file_done = 0;
    header_received = false;
    while ((file_done == 0) && (result == COM_OK))
    {
      switch (receive_packet(aPacketData, &packet_length, DOWNLOAD_TIMEOUT))
      {
      case YMODEM_OK:
        errors = 0;
        switch (packet_length)
        {
        case 2:
          /* Abort by sender */
          put_byte(ACK);
          result = COM_ABORT;
          break;
        case 0:
          /* End of transmission */
          put_byte(ACK);
          file_done = 1;
          break;
        default:
          /* Normal packet */
          if (aPacketData[PACKET_NUMBER_INDEX] != packets_received)
          {
            put_byte(NAK);
          }
          else
          {
            if (!header_received && packets_received == 0)
            {
              /* File name packet */
              if (aPacketData[PACKET_DATA_INDEX] != 0)
              {
                /* File name extraction */
                i = 0;
                file_ptr = aPacketData + PACKET_DATA_INDEX;
                while ((*file_ptr != 0) && (i < FILE_NAME_LENGTH))
                {
                  file_name_str[i++] = *file_ptr++;
                }

                /* File size extraction */
                file_name_str[i++] = '\0';
                i = 0;
                file_ptr++;
                while ((*file_ptr != ' ') && (i < FILE_SIZE_LENGTH))
                {
                  file_size_str[i++] = *file_ptr++;
                }
                file_size_str[i++] = '\0';
                str_conv.str_to_int(file_size_str, &filesize);

                /* Test the size of the image to be sent */
                /* Image size is greater than Flash size */
                if (p_size > (flash_size + 1))
                {
                  /* End session */
                  tmp = CA;
                  tranceiver->send(&tmp, 1, NAK_TIMEOUT);
                  tranceiver->send(&tmp, 1, NAK_TIMEOUT);
                  result = COM_LIMIT;
                }
                /* erase user application area */
                flash_ops->erase(flash_start_addr, flash_size);
                p_size = filesize;
                
                header_received = true;
                put_byte(ACK);
                put_byte(CRC16);
              }
              /* File header packet is empty, end session */
              else
              {
                put_byte(ACK);
                header_received = false;
                file_done = 1;
                session_done = 1;
                break;
              }
            }
            else /* Data packet */
            {
              ramsource = (unsigned int)&aPacketData[PACKET_DATA_INDEX];

              /* Write received data in Flash */
              if (flash_ops->write(flashdestination, (unsigned int *)ramsource, packet_length / 4) == 0)
              {
                flashdestination += packet_length;
                put_byte(ACK);
              }
              else /* An error occurred while writing to Flash memory */
              {
                /* End session */
                put_byte(CA);
                put_byte(CA);
                result = COM_DATA;
              }
            }
            packets_received++;
            session_begin = 1;
          }
          break;
        }
        break;
      case YMODEM_BUSY: /* Abort actually */
        put_byte(CA);
        put_byte(CA);
        result = COM_ABORT;
        break;
      default:
        if (session_begin > 0)
        {
          errors++;
        }
        if (errors > MAX_ERRORS)
        {
          /* Abort communication */
          put_byte(CA);
          put_byte(CA);
        }
        else
        {
          put_byte(CRC16); /* Ask for a packet */
        }
        break;
      }
    }
  }
  return result;
}

/**
  * @brief  Transmit a file using the ymodem protocol
  * @param  p_buf: Address of the first byte
  * @param  p_file_name: Name of the file sent
  * @param  file_size_str: Size of the transmission
  * @retval COM_StatusTypeDef result of the communication
  */
COM_StatusTypeDef Ymodem::upload(unsigned char *p_buf, const unsigned char *p_file_name, unsigned int file_size_str)
{
  unsigned int errors = 0, ack_recpt = 0, size = 0, pkt_size;
  unsigned char *p_buf_int;
  COM_StatusTypeDef result = COM_OK;
  unsigned int blk_number = 1;
  unsigned char a_rx_ctrl[2];
  unsigned char i;
#ifdef CRC16_F
  unsigned int temp_crc;
#else  /* CRC16_F */
  unsigned char temp_chksum;
#endif /* CRC16_F */

  /* Prepare first block - header */
  prepare_intial_packet(aPacketData, p_file_name, file_size_str);

  while ((!ack_recpt) && (result == COM_OK))
  {
    /* Send Packet */
    tranceiver->send(&aPacketData[PACKET_START_INDEX], PACKET_SIZE + PACKET_HEADER_SIZE, NAK_TIMEOUT);

    /* Send CRC or Check Sum based on CRC16_F */
#ifdef CRC16_F
    temp_crc = calc_CRC16(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
    put_byte(temp_crc >> 8);
    put_byte(temp_crc & 0xFF);
#else  /* CRC16_F */
    temp_chksum = calc_checksum(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
    put_byte(temp_chksum);
#endif /* CRC16_F */

    /* Wait for Ack and 'C' */
    if (tranceiver->receive(&a_rx_ctrl[0], 1, NAK_TIMEOUT) == YMODEM_OK)
    {
      if (a_rx_ctrl[0] == ACK)
      {
        ack_recpt = 1;
      }
      else if (a_rx_ctrl[0] == CA)
      {
        if ((tranceiver->receive(&a_rx_ctrl[0], 1, NAK_TIMEOUT) == YMODEM_OK) && (a_rx_ctrl[0] == CA))
        {
//          HAL_Delay(2);
          //          __HAL_UART_FLUSH_DRREGISTER(&huart1);
          result = COM_ABORT;
        }
      }
    }
    else
    {
      errors++;
    }
    if (errors >= MAX_ERRORS)
    {
      result = COM_ERROR;
    }
  }

  p_buf_int = p_buf;
  size = file_size_str;

  /* Here 1024 bytes length is used to send the packets */
  while ((size) && (result == COM_OK))
  {
    /* Prepare next packet */
    prepare_packet(p_buf_int, aPacketData, blk_number, size);
    ack_recpt = 0;
    a_rx_ctrl[0] = 0;
    errors = 0;

    /* Resend packet if NAK for few times else end of communication */
    while ((!ack_recpt) && (result == COM_OK))
    {
      /* Send next packet */
      if (size >= PACKET_1K_SIZE)
      {
        pkt_size = PACKET_1K_SIZE;
      }
      else
      {
        pkt_size = PACKET_SIZE;
      }

      tranceiver->send(&aPacketData[PACKET_START_INDEX], pkt_size + PACKET_HEADER_SIZE, NAK_TIMEOUT);

      /* Send CRC or Check Sum based on CRC16_F */
#ifdef CRC16_F
      temp_crc = calc_CRC16(&aPacketData[PACKET_DATA_INDEX], pkt_size);
      put_byte(temp_crc >> 8);
      put_byte(temp_crc & 0xFF);
#else  /* CRC16_F */
      temp_chksum = calc_checksum(&aPacketData[PACKET_DATA_INDEX], pkt_size);
      put_byte(temp_chksum);
#endif /* CRC16_F */

      /* Wait for Ack */
      if ((tranceiver->receive(&a_rx_ctrl[0], 1, NAK_TIMEOUT) == YMODEM_OK) && (a_rx_ctrl[0] == ACK))
      {
        ack_recpt = 1;
        if (size > pkt_size)
        {
          p_buf_int += pkt_size;
          size -= pkt_size;
          if (blk_number == (flash_size / PACKET_1K_SIZE))
          {
            result = COM_LIMIT; /* boundary error */
          }
          else
          {
            blk_number++;
          }
        }
        else
        {
          p_buf_int += pkt_size;
          size = 0;
        }
      }
      else
      {
        errors++;
      }

      /* Resend packet if NAK  for a count of 10 else end of communication */
      if (errors >= MAX_ERRORS)
      {
        result = COM_ERROR;
      }
    }
  }

  /* Sending End Of Transmission char */
  ack_recpt = 0;
  a_rx_ctrl[0] = 0x00;
  errors = 0;
  while ((!ack_recpt) && (result == COM_OK))
  {
    put_byte(EOT);

    /* Wait for Ack */
    if (tranceiver->receive(&a_rx_ctrl[0], 1, NAK_TIMEOUT) == YMODEM_OK)
    {
      if (a_rx_ctrl[0] == ACK)
      {
        ack_recpt = 1;
      }
      else if (a_rx_ctrl[0] == CA)
      {
        if ((tranceiver->receive(&a_rx_ctrl[0], 1, NAK_TIMEOUT) == YMODEM_OK) && (a_rx_ctrl[0] == CA))
        {
//          HAL_Delay(2);
          //          __HAL_UART_FLUSH_DRREGISTER(&huart1);
          result = COM_ABORT;
        }
      }
    }
    else
    {
      errors++;
    }

    if (errors >= MAX_ERRORS)
    {
      result = COM_ERROR;
    }
  }

  /* Empty packet sent - some terminal emulators need this to close session */
  if (result == COM_OK)
  {
    /* Preparing an empty packet */
    aPacketData[PACKET_START_INDEX] = SOH;
    aPacketData[PACKET_NUMBER_INDEX] = 0;
    aPacketData[PACKET_CNUMBER_INDEX] = 0xFF;
    for (i = PACKET_DATA_INDEX; i < (PACKET_SIZE + PACKET_DATA_INDEX); i++)
    {
      aPacketData[i] = 0x00;
    }

    /* Send Packet */
    tranceiver->send(&aPacketData[PACKET_START_INDEX], PACKET_SIZE + PACKET_HEADER_SIZE, NAK_TIMEOUT);

    /* Send CRC or Check Sum based on CRC16_F */
#ifdef CRC16_F
    temp_crc = calc_CRC16(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
    put_byte(temp_crc >> 8);
    put_byte(temp_crc & 0xFF);
#else  /* CRC16_F */
    temp_chksum = calc_checksum(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
    put_byte(temp_chksum);
#endif /* CRC16_F */

    /* Wait for Ack and 'C' */
    if (tranceiver->receive(&a_rx_ctrl[0], 1, NAK_TIMEOUT) == YMODEM_OK)
    {
      if (a_rx_ctrl[0] == CA)
      {
//        HAL_Delay(2);
        //          __HAL_UART_FLUSH_DRREGISTER(&huart1);
        result = COM_ABORT;
      }
    }
  }

  return result; /* file transmitted successfully */
}

/**
  * @brief  Print a string on the HyperTerminal
  * @param  p_string: The string to be printed
  * @retval None
  */
void Ymodem::put_string(unsigned char *p_string)
{
  unsigned short length = 0;

  while (p_string[length] != '\0')
  {
    length++;
  }
  tranceiver->send(p_string, length, TX_TIMEOUT);
}

/**
  * @brief  Transmit a byte to the HyperTerminal
  * @param  param The byte to be sent
  * @retval HAL_StatusTypeDef YMODEM_OK if OK
  */
YMODEM_STATUS Ymodem::put_byte(unsigned char param)
{
  return tranceiver->send(&param, 1, TX_TIMEOUT);
}

/**
  * @}
  */

/*******************(C)COPYRIGHT 2016 STMicroelectronics *****END OF FILE****/
