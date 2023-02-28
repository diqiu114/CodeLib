/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      one wire communication driver
*
* 版本:
* V1.0 2019-08-16 初始版本编写
***********************************************************/

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_

#include "delay\delay_if.h"
#include "hw_interface\gpio\gpio_if.h"
#include "stddef.h"

/* OneWire commands */
#define CMD_RSCRATCHPAD   (0xBE)
#define CMD_WSCRATCHPAD   (0x4E)
#define CMD_CPYSCRATCHPAD (0x48)
#define CMD_RECEEPROM     (0xB8)
#define CMD_RPWRSUPPLY    (0xB4)
#define CMD_SEARCHROM     (0xF0)
#define CMD_READROM       (0x33)
#define CMD_MATCHROM      (0x55)
#define CMD_SKIPROM       (0xCC)

typedef struct {
  Gpio_if *io;
  unsigned char LastDiscrepancy;       /*!< Search private */
  unsigned char LastFamilyDiscrepancy; /*!< Search private */
  unsigned char LastDeviceFlag;        /*!< Search private */
  unsigned char ROM_NO[8];             /*!< 8-bytes address of last search device */
} Onewire_t;

class Onewire
{
public:
  Onewire(Gpio_if* gpio, Delay_if* _delay);
  
  void power();
  unsigned char reset();
  void write_byte(unsigned char byte);
  unsigned char read_byte();

  unsigned char first(void);
  unsigned char next(void);
  void reset_search(void);
  int verify(void);
  void target_setup(unsigned char family_code);
  void family_skip_setup(void);
  unsigned char get_rom(unsigned char index);
  void select(unsigned char *addr);
  void select_with_pointer(unsigned char *ROM);
  void get_full_rom(unsigned char *firstIndex);

  ~Onewire();

private:
  Onewire_t ow;
  Delay_if* microseconds;

  unsigned char io_read(void);
  void write_bit(unsigned char bit);
  unsigned char read_bit();

  unsigned char search(unsigned char command);

};
#endif
