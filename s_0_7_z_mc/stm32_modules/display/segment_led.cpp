#include "segment_led.h"

//用于数字到字符的偏移
#define ZREO_ASCII ('0')
//数码管支持显示的ascii最小的字符
#define MIN_ASCII ('-')
//数码管支持显示的ascii最大的字符
#define MAX_ASCII ('Z')
//遇上无法显示或超出的字符时用空格代替，因为“?”无法显示
#define SPACE_ASCII ('?')
//数字转字符
#define NUMBER_2_ASCII(number)  (number + ZREO_ASCII)
//数码管内支持的最大小数点个数
#define POINT_CNT (4)

//数码管编码参考网址
//http://www.51hei.com/bbs/dpj-179315-1.html
unsigned char ascii_code[]=
{
  0x40,0x80,  //-.
  0x00,     //空格
  0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,  //0~9
  0x00,0x00,0x00,0x00,0x00,0x00,0x00, //:;<=>?@，7个无法显示的字符，遇到时显示为空格
  0x77,0x7C,0x39,0x5E,0x79,0x71,0x3D, //A~G
  0x76,0x30,0x0E,0x7A,0x38,0x55,0x54, //H~M
  0x3F,0x73,0x67,0x50,0x6D,0x78,  //O~T
  0x3E,0x1C,0x6A,0x64,0x6E,0x5A,  //U~Z
};

/**
 * @brief Segmeng_led 构造函数
 * 
 * @param _comm_gpios 数码管公共端引脚vector
 * @param _seg_gpios 数码管段led引脚vector
 * @param _sel_comm_sta 数码管共阴/共阳
* @param _delay 数码管内部显示延迟，数字越大，亮度越高，可选参数
 */
Segment_led::Segment_led( vector<Gpio_if*> &_comm_gpios,
            vector<Gpio_if*> &_seg_gpios,
            GPIO_STATUES _sel_comm_sta,
            unsigned short _delay)
{
  //显示数据时，点和7段数码管是分开显示的，所以数据长度时数码管个数 + 支持显示的点的个数
  data_len = _comm_gpios.size() + POINT_CNT;
  comm_gpios = _comm_gpios;
  seg_gpios = _seg_gpios;
  sel_comm_sta = _sel_comm_sta;
  
  data = new unsigned char[data_len];
  if(data != NULL)
  {
    memset(data,0,data_len);
  }
  
  delay = _delay;
}

/**
 * @brief Segmeng_led 析构函数
 */
Segment_led::~Segment_led()
{
  for(int i=0;i < comm_gpios.size() ;i++)
  {
    if(comm_gpios[i] != NULL)
    {
      delete comm_gpios[i];
      comm_gpios[i] = NULL;
    }
  }
  for(int i=0;i < seg_gpios.size() ;i++)
  {
    if(seg_gpios[i] != NULL)
    {
      delete seg_gpios[i];
      seg_gpios[i] = NULL;
    }
  }
  delete data;
}


/**
 * @brief set_ascii 设置需要显示的数据
 * 
 * @param _data 需要进行显示的数据
* @param offset 在数码管上的偏移数，可选参数，不常用
 */
void Segment_led::set_data(unsigned char* _data, unsigned char offset)
{
  if(data == NULL)
  {
    return;
  }
  while(*_data != '\0' && offset < data_len )
  {
    //*(p++) = *_data++
    data[offset++] = *(_data++);
  }
}

/**
 * @brief show_data 显示数据，需要一被调用
 * 
 */
void Segment_led::show_data()
{
  unsigned char* p = data;
  for(int dis=0;dis < data_len ;dis++)
  {
    show_ascii(SPACE_ASCII);
    set_common(dis);
    show_ascii(*(p++));
    led_delay(delay);
    //遇上连续“.”时，优化显示
    if(*p == '.' && *(p-1) != '.')
    {
      show_ascii(*(p++));
      led_delay(delay);
    }
  }
}

void Segment_led::led_delay(unsigned int _delay)
{
  volatile unsigned short delay = _delay;
  while(delay--);
}

/**
 * @brief set_common 选择那个数码管被点亮
 * 
 * @param common 希望被点亮的数码管的下标（从0开始）
 */
void Segment_led::set_common(unsigned char common)
{
  if(sel_comm_sta == GPIO_LOW)
  {
    for(int i=0;i < comm_gpios.size() ;i++)
    {
      if(common == i)
      {
        comm_gpios[i]->set_low();
      }
      else
      {
        comm_gpios[i]->set_hi();
      }
    }
  }
  else
  {
    for(int i=0;i < comm_gpios.size() ;i++)
    {
      if(common == i)
      {
        comm_gpios[i]->set_hi();
      }
      else
      {
        comm_gpios[i]->set_low();
      }
    }
  }
}

/**
 * @brief show_ascii 单个数码管显示ascii字符
 * 
 * @param ascii 需要显示的字符
 */
void Segment_led::show_ascii(unsigned char ascii)
{
  if(ascii >= 'a' && ascii <= 'z')
  {
    ascii -= 'a'-'A';
  }
  else if((ascii < MIN_ASCII) || (ascii > MAX_ASCII))
  {
    ascii = SPACE_ASCII;
  }
  if(sel_comm_sta == GPIO_LOW)
  {
    for(int i=0;i< seg_gpios.size() ;i++)
    {
      if((ascii_code[ ascii - MIN_ASCII] >> i ) & 0x01)
      {
        seg_gpios[i]->set_hi();
      }
      else
      {
        seg_gpios[i]->set_low();
      }
    }
  }
  else
  {
    for(int i=0;i<seg_gpios.size();i++)
    {
      if((ascii_code[ ascii - MIN_ASCII] >> i ) & 0x01)
      {
        seg_gpios[i]->set_low();
      }
      else
      {
        seg_gpios[i]->set_hi();
      }
    }
  }
}
/**
 * @brief show_ascii_mid 中间单个数码管显示ascii字符
 * 
 * @param ascii 需要显示的字符
 */
void Segment_led::show_ascii_single(unsigned char ascii, unsigned short location)
{
  set_common(location);
  if(ascii >= 'a' && ascii <= 'z')
  {
    ascii -= 'a'-'A';
  }
  else if((ascii < MIN_ASCII) || (ascii > MAX_ASCII))
  {
    ascii = SPACE_ASCII;
  }
  if(sel_comm_sta == GPIO_LOW)
  {
    for(int i=0;i< seg_gpios.size() ;i++)
    {
      if((ascii_code[ ascii - MIN_ASCII] >> i ) & 0x01)
      {
        seg_gpios[i]->set_hi();
      }
      else
      {
        seg_gpios[i]->set_low();
      }
    }
  }
  else
  {
    for(int i=0;i<seg_gpios.size();i++)
    {
      if((ascii_code[ ascii - MIN_ASCII] >> i ) & 0x01)
      {
        seg_gpios[i]->set_low();
      }
      else
      {
        seg_gpios[i]->set_hi();
      }
    }
  }
}

