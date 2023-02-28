/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      AT指令
*
***********************************************************/

#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

#include <stdbool.h>
#include <string.h>
#include "..\Double_buffered_comm.h"

#define AT_COMMAND_REV_TIMEOUT (1000)
#define AT_COMMAND_REV_UNTIL_TIMEOUT (1000)
#define AT_COMMAND_BUFF_SIZE (200)

class At_command
{
public:
  At_command(Double_buffered_comm *_comm, int _buff_size = AT_COMMAND_BUFF_SIZE);
  virtual ~At_command();
  bool set_echo(bool display = true);
  bool send(const char *command, const char *expected_answer1, const char *expected_answer2 = NULL, int rev_timeout = AT_COMMAND_REV_TIMEOUT);
  bool send(const char *command, int command_len, const char *expected_answer1, const char *expected_answer2 = NULL, int rev_timeout = AT_COMMAND_REV_TIMEOUT);
  bool send_receive(const char *command, char *ret_str, int rev_timeout = AT_COMMAND_REV_TIMEOUT);
  bool send_receive(const char *command, int command_len, char *ret_str, int rev_timeout = AT_COMMAND_REV_TIMEOUT);
  bool send_until(const char *command, const char *expected_answer1, const char *expected_answer2 = NULL, int rev_timeout = AT_COMMAND_REV_UNTIL_TIMEOUT);
  bool send_until(const char *command, int command_len, const char *expected_answer1, const char *expected_answer2 = NULL, int rev_timeout = AT_COMMAND_REV_UNTIL_TIMEOUT);
  bool send_receive_until(const char *command, char *ret_str, int rev_timeout = AT_COMMAND_REV_UNTIL_TIMEOUT);
  bool send_receive_until(const char *command, int command_len, char *ret_str, int rev_timeout = AT_COMMAND_REV_UNTIL_TIMEOUT);
  bool read_buffer(char *ret_str, int data_len = 0);
  bool read_buffer_until(char *ret_str, int str_len = 0, int rev_timeout = AT_COMMAND_REV_UNTIL_TIMEOUT);
  int buffer_data_cnt(void);

private:
  bool received_data(int timeout);
  bool find_str(char *buffer, const char *str, unsigned int buffer_len);
  Double_buffered_comm *comm;
  char *buff;
  int buff_size;
};

#endif // _AT_COMMAND_H_
