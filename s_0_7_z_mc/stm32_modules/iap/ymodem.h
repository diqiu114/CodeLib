/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ymodem 程序升级类，根据STM32 IAP修改 
*
***********************************************************/

#ifndef _YMODEM_H_
#define _YMODEM_H_

#include "ymodem_tranceiver_if.h"
#include "string_convert.h"
#include "flash_ops_if.h"

typedef enum
{
  COM_OK = 0,
  COM_ERROR = 1,
  COM_ABORT = 2,
  COM_TIMEOUT = 3,
  COM_DATA = 4,
  COM_LIMIT = 5
} COM_StatusTypeDef;

#define TX_TIMEOUT ((unsigned int)100)
#define RX_TIMEOUT ((unsigned int)0xFFFFFFFF)

/* Exported constants --------------------------------------------------------*/
/* Packet structure defines */
#define PACKET_HEADER_SIZE ((unsigned int)3)
#define PACKET_DATA_INDEX ((unsigned int)4)
#define PACKET_START_INDEX ((unsigned int)1)
#define PACKET_NUMBER_INDEX ((unsigned int)2)
#define PACKET_CNUMBER_INDEX ((unsigned int)3)
#define PACKET_TRAILER_SIZE ((unsigned int)2)
#define PACKET_OVERHEAD_SIZE (PACKET_HEADER_SIZE + PACKET_TRAILER_SIZE - 1)
#define PACKET_SIZE ((unsigned int)128)
#define PACKET_1K_SIZE ((unsigned int)1024)

/* /-------- Packet in IAP memory ------------------------------------------\
 * | 0      |  1    |  2     |  3   |  4      | ... | n+4     | n+5  | n+6  | 
 * |------------------------------------------------------------------------|
 * | unused | start | number | !num | data[0] | ... | data[n] | crc0 | crc1 |
 * \------------------------------------------------------------------------/
 * the first byte is left unused for memory alignment reasons                 */

#define FILE_NAME_LENGTH ((unsigned int)64)
#define FILE_SIZE_LENGTH ((unsigned int)16)

#define SOH ((unsigned char)0x01)   /* start of 128-byte data packet */
#define STX ((unsigned char)0x02)   /* start of 1024-byte data packet */
#define EOT ((unsigned char)0x04)   /* end of transmission */
#define ACK ((unsigned char)0x06)   /* acknowledge */
#define NAK ((unsigned char)0x15)   /* negative acknowledge */
#define CA ((unsigned int)0x18)     /* two of these in succession aborts transfer */
#define CRC16 ((unsigned char)0x43) /* 'C' == 0x43, request 16-bit CRC */
#define NEGATIVE_BYTE ((unsigned char)0xFF)

#define ABORT1 ((unsigned char)0x41) /* 'A' == 0x41, abort by user */
#define ABORT2 ((unsigned char)0x61) /* 'a' == 0x61, abort by user */

#define NAK_TIMEOUT ((unsigned int)0x100000)
#define DOWNLOAD_TIMEOUT ((unsigned int)2000) /* One second retry delay */
#define MAX_ERRORS ((unsigned int)5)

class Ymodem
{
public:
  Ymodem(Ymodem_tranceiver_if *_tranceiver, Flash_ops_if *_flash_ops);
  virtual ~Ymodem();
  bool download(void);
  COM_StatusTypeDef upload(unsigned char *p_buf, const unsigned char *p_file_name, unsigned int file_size);

private:
  COM_StatusTypeDef receive(void);
  void prepare_intial_packet(unsigned char *p_data, const unsigned char *p_file_name, unsigned int length);
  void prepare_packet(unsigned char *p_source, unsigned char *p_packet, unsigned char pkt_nr, unsigned int size_blk);
  YMODEM_STATUS receive_packet(unsigned char *p_data, unsigned int *p_length, unsigned int timeout);
  unsigned short update_CRC16(unsigned short crc_in, unsigned char byte);
  unsigned short calc_CRC16(const unsigned char *p_data, unsigned int size);
  unsigned char calc_checksum(const unsigned char *p_data, unsigned int size);

  void put_string(unsigned char *p_string);
  YMODEM_STATUS put_byte(unsigned char param);

  Ymodem_tranceiver_if *tranceiver;
  Flash_ops_if *flash_ops;
  unsigned char aPacketData[PACKET_1K_SIZE + PACKET_DATA_INDEX + PACKET_TRAILER_SIZE];
  String_conv str_conv;
  unsigned char file_name_str[FILE_NAME_LENGTH];
  unsigned char file_size_str[FILE_SIZE_LENGTH];
  unsigned int flash_start_addr;
  unsigned int flash_size;
};

#endif /* __YMODEM_H_ */
