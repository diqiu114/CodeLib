/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      ymodem 数据收发接口类
*
***********************************************************/

#ifndef _YMODEM_TRANCEIVER_IF_H_
#define _YMODEM_TRANCEIVER_IF_H_

typedef enum
{
  YMODEM_OK = 0,
  YMODEM_ERROR = 1,
  YMODEM_BUSY = 2,
  YMODEM_TIMEOUT = 3
} YMODEM_STATUS;

class Ymodem_tranceiver_if
{
public:
  virtual YMODEM_STATUS receive(unsigned char *data, unsigned int data_len, unsigned int timeout) = 0;
  virtual YMODEM_STATUS send(unsigned char *data, unsigned int data_len, unsigned int timeout) = 0;
  virtual ~Ymodem_tranceiver_if(){};
};

#endif // _YMODEM_TRANCEIVER_IF_H_
