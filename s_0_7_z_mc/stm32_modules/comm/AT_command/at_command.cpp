#include "at_command.h"
#include "modules_def.h"

At_command::At_command(Double_buffered_comm *_comm, int _buff_size)
{
  comm = _comm;
  buff_size = _buff_size;
  buff = new char[buff_size];
}

At_command::~At_command()
{
  if (comm != NULL)
  {
    delete comm;
    comm = NULL;
  }

  if (buff != NULL)
  {
    delete[] buff;
    buff = NULL;
  }
}

bool At_command::set_echo(bool display)
{
  bool ret = false;
  if (display)
  {
    ret = send("ATE1\r\n", "OK");
  }
  else
  {
    ret = send("ATE0\r\n", "OK");
  }
  return ret;
}

/**
 * send 发送接收AT命令，接收单次数据后，与期望结果对比
 * @param commandd AT命令
 * @param expected_answer1 期待返回的数据字符串1
 * @param expected_answer2 期待返回的数据字符串2
 * @param rev_timeout 接收超时时间，在接收时间内，收到1次数据后，退出接收数据状态
 * @return 接收的数据符合expected_answer1或expected_answer2 返回ture 否则返回false
 */
bool At_command::send(const char *command, const char *expected_answer1, const char *expected_answer2, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;

  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, strlen(command));

  if (received_data(rev_timeout))
  {
    int data_cnt = comm->data_available();
    if (data_cnt > buff_size)
    {
      data_cnt = buff_size;
    }

    comm->read((unsigned char *)buff, data_cnt);

    ret = strstr(buff, expected_answer1) != NULL;

    if (expected_answer2 != NULL)
    {
      ret |= (strstr(buff, expected_answer2) != NULL);
    }
  }

  return ret;
}

/**
 * send 发送接收AT命令，接收单次数据后，与期望结果对比
 * @param command AT命令
 * @param command_len AT命令长度
 * @param expected_answer1 期待返回的数据字符串1
 * @param expected_answer2 期待返回的数据字符串2
 * @param rev_timeout 接收超时时间，在接收时间内，收到1次数据后，退出接收数据状态
 * @return 接收的数据符合expected_answer1或expected_answer2 返回ture 否则返回false
 */
bool At_command::send(const char *command, int command_len, const char *expected_answer1, const char *expected_answer2, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;

  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, command_len);

  if (received_data(rev_timeout))
  {
    int data_cnt = comm->data_available();
    if (data_cnt > buff_size)
    {
      data_cnt = buff_size;
    }

    comm->read((unsigned char *)buff, data_cnt);

    ret = strstr(buff, expected_answer1) != NULL;

    if (expected_answer2 != NULL)
    {
      ret |= (strstr(buff, expected_answer2) != NULL);
    }
  }

  return ret;
}

/**
 * send_until 发送接收AT命令，直到接收时间耗完再退出。用于数据分多次和慢速返回场景
 * @param commandd AT命令
 * @param expected_answer1 期待返回的数据字符串1
 * @param expected_answer2 期待返回的数据字符串2
 * @param rev_timeout 接收超时时间，在接收时间内，一直处于接收数据状态，超时退出
 * @return 接收的数据符合expected_answer1或expected_answer2 返回ture 否则返回false
 */
bool At_command::send_until(const char *command, const char *expected_answer1, const char *expected_answer2, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;
  int timeout = rev_timeout;
  int total_cnt = 0;
  int data_cnt = 0;

  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, strlen(command));

  while (timeout)
  {
    if (received_data(1))
    {
      data_cnt = comm->data_available();
      
      char *data_buff = new char[data_cnt];

      if (data_buff == NULL)
      {
        return false;
      }

      comm->read((unsigned char *)data_buff, data_cnt);

      if(buff_size - total_cnt > data_cnt)
      {
        memcpy(buff+total_cnt, data_buff, data_cnt);
        total_cnt += data_cnt;
      }

      delete[] data_buff;
    }

    DELAY_MS(1);

    timeout--;
  }
  ret = find_str(buff, expected_answer1, data_cnt);

  if (expected_answer2 != NULL)
  {
    ret |= find_str(buff, expected_answer2, data_cnt);
  }

  return ret;
}

/**
 * send_until 发送接收AT命令，直到接收时间耗完再退出。用于数据分多次和慢速返回场景
 * @param commandd AT命令或数据
 * @param commandd_len AT命令或数据长度
 * @param expected_answer1 期待返回的数据字符串1
 * @param expected_answer2 期待返回的数据字符串2
 * @param rev_timeout 接收超时时间，在接收时间内，一直处于接收数据状态，超时退出
 * @return 接收的数据符合expected_answer1或expected_answer2 返回ture 否则返回false
 */

bool At_command::send_until(const char *command, int command_len, const char *expected_answer1, const char *expected_answer2, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;
  int timeout = rev_timeout;
  int total_cnt = 0;
  int data_cnt = 0;  

  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, command_len);

  while (timeout)
  {
    if (received_data(1))
    {
      data_cnt = comm->data_available();
      
      char *data_buff = new char[data_cnt];

      if (data_buff == NULL)
      {
        return false;
      }

      comm->read((unsigned char *)data_buff, data_cnt);

      if(buff_size - total_cnt > data_cnt)
      {
        memcpy(buff+total_cnt, data_buff, data_cnt);
        total_cnt += data_cnt;
      }
      delete[] data_buff;
    }

    DELAY_MS(1);

    timeout--;
  }
  ret = find_str(buff, expected_answer1, data_cnt);

  if (expected_answer2 != NULL)
  {
    ret |= find_str(buff, expected_answer2, data_cnt);
  }

  return ret;
}

/**
 * send_receive 发送接收AT命令，并接收单次返回的数据
 * @param commandd AT命令
 * @param ret_str 接收返回数据指针
 * @param rev_timeout 接收超时时间
 * @return 接收数据成功-true,否则-false
 */
bool At_command::send_receive(const char *command, char *ret_str, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;
  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, strlen(command));

  if (received_data(rev_timeout))
  {
    int data_cnt = comm->data_available();

    char *data_buff = new char[data_cnt];

    if (data_buff == NULL)
    {
      return false;
    }

    comm->read((unsigned char *)data_buff, data_cnt);

//    comm->read((unsigned char *)data_buff, data_cnt);

    strcpy(ret_str, data_buff);

    delete[] data_buff;

    ret = true;
  }

  return ret;
}

/**
 * send_receive 发送接收AT命令，并接收单次返回的数据
 * @param command AT命令
 * @param command_len AT命令长度
 * @param ret_str 接收返回数据指针
 * @param rev_timeout 接收超时时间
 * @return 接收数据成功-true,否则-false
 */
bool At_command::send_receive(const char *command, int command_len, char *ret_str, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;
  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, command_len);

  if (received_data(rev_timeout))
  {
    int data_cnt = comm->data_available();

    char *data_buff = new char[data_cnt];

    if (data_buff == NULL)
    {
      return false;
    }

    comm->read((unsigned char *)data_buff, data_cnt);

//    comm->read((unsigned char *)data_buff, data_cnt);

    strcpy(ret_str, data_buff);

    delete[] data_buff;

    ret = true;
  }

  return ret;
}

/**
 * send_receive_until 发送接收AT命令，接收一定时间内数据，并返回
 * @param commandd AT命令
 * @param ret_str 接收返回数据指针
 * @param rev_timeout 接收超时时间
 * @return 接收数据成功-true,否则-false
 */
bool At_command::send_receive_until(const char *command, char *ret_str, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;
  int timeout = rev_timeout;

  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, strlen(command));

  while (timeout)
  {
    if (received_data(1))
    {
      int data_cnt = comm->data_available();

      char *data_buff = new char[data_cnt];

      if (data_buff == NULL)
      {
        return false;
      }

      comm->read((unsigned char *)data_buff, data_cnt);

      if (buff_size - strlen(buff) > data_cnt)
      {
        strncat(buff, data_buff, data_cnt);
      }

      delete[] data_buff;
    }

    DELAY_MS(1);

    timeout--;
  }

  if (strlen(buff) > 0)
  {
    strcpy(ret_str, buff);
    ret = true;
  }

  return ret;
}

/**
 * send_receive_until 发送接收AT命令，接收一定时间内数据，并返回
 * @param command AT命令
 * @param command_len AT命令长度
 * @param ret_str 接收返回数据指针
 * @param rev_timeout 接收超时时间
 * @return 接收数据成功-true,否则-false
 */
bool At_command::send_receive_until(const char *command, int command_len, char *ret_str, int rev_timeout)
{
  if ((buff == NULL) || (command == NULL))
  {
    return false;
  }

  bool ret = false;
  int timeout = rev_timeout;

  memset(buff, 0, buff_size);

  comm->send((unsigned char *)command, command_len);

  while (timeout)
  {
    if (received_data(1))
    {
      int data_cnt = comm->data_available();

      char *data_buff = new char[data_cnt];

      if (data_buff == NULL)
      {
        return false;
      }

      comm->read((unsigned char *)data_buff, data_cnt);

      if (buff_size - strlen(buff) > data_cnt)
      {
        strncat(buff, data_buff, data_cnt);
      }

      delete[] data_buff;
    }

    DELAY_MS(1);

    timeout--;
  }

  if (strlen(buff) > 0)
  {
    strcpy(ret_str, buff);
    ret = true;
  }

  return ret;
}

/**
 * received_data 判断指定时间内是否接收到数据
 * @param timeout 超时时间
 * @return 有数据-true,无数据-false
 */
bool At_command::received_data(int timeout)
{
  bool ret = true;
  while (comm->data_available() == 0)
  {
    timeout--;
    if (timeout <= 0)
    {
      ret = false;
      break;
    }
    DELAY_MS(1);
  }
  return ret;
}

/**
 * @brief read a frame data from buffer
 * 
 * @param ret_str data pointer
 * @param data_len data length to be read, 0 means read all
 * @return false no data or read error
 */
bool At_command::read_buffer(char *ret_str, int data_len)
{
  if (comm->data_available() > 0)
  {
    if (data_len == 0)
    {
      comm->read_all((unsigned char *)ret_str);
    }
    else
    {
      comm->read((unsigned char *)ret_str, data_len);
    }
    return true;
  }

  return false;
}

/**
 * @brief read data from buffer at fixed time
 * 
 * @param ret_str data pointer
 * @param @param data_len data length to be read, 0 means read all
 * @param rev_timeout receive timeout 
 * @return false no data or read error
 */
bool At_command::read_buffer_until(char *ret_str, int data_len, int rev_timeout)
{
  bool ret = false;
  int timeout = rev_timeout;

  memset(buff, 0, buff_size);

  while (timeout)
  {
    if (received_data(1))
    {
      int data_cnt = comm->data_available();

      data_cnt = data_cnt < data_len ? data_cnt : data_len;

      char *data_buff = new char[data_cnt];

      if (data_buff == NULL)
      {
        return false;
      }

      comm->read((unsigned char *)data_buff, data_cnt);

      if (buff_size - strlen(buff) > data_cnt)
      {
        strncat(buff, data_buff, data_cnt);
      }

      delete[] data_buff;
    }

    DELAY_MS(1);

    timeout--;
  }

  if (strlen(buff) > 0)
  {
    strcpy(ret_str, buff);
    ret = true;
  }

  return ret;
}

int At_command::buffer_data_cnt(void)
{
  return comm->data_available();
}

bool At_command::find_str(char *buffer, const char *str, unsigned int buffer_len)
{
  int     i   = 0;
  bool ret = false;
  unsigned short len = strlen(str);
  for(i = 0; i < buffer_len; i++)
  {
    if( buffer[i] == str[0] )
    {
      if( memcmp(buffer + i, str, len) == 0 )
      {
        ret = true;
        break;
      }
    }
  }

  return ret;
}
