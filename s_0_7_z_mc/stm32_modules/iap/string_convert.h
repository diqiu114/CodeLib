/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      字符转换类 
*
***********************************************************/

#ifndef _STRING_CONVERT_H_
#define _STRING_CONVERT_H_

/* Exported macro ------------------------------------------------------------*/
#define IS_CAP_LETTER(c) (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c) (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c) (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c) (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c) IS_09(c)
#define CONVERTDEC(c) (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A' + 10) : ((c) - 'a' + 10))
#define CONVERTHEX(c) (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))

class String_conv
{
public:
  String_conv();
  ~String_conv();

  void int_to_str(unsigned char *p_str, unsigned int intnum);
  unsigned int str_to_int(unsigned char *inputstr, unsigned int *intnum);
};

#endif // _STRING_CONVERT_H_
