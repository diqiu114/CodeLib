#include "onewire.h"

Onewire::Onewire(Gpio_if* gpio, Delay_if *_delay)
{
  ow.io = gpio;
  microseconds = _delay;
}

Onewire::~Onewire()
{
  if(ow.io != NULL)
  {
    delete ow.io;
    ow.io = NULL;
  }
}

/**
 * reset
 * @return 0 ok, 1 error
 */
unsigned char Onewire::reset(void)
{
  // 0 = OK, 1 = ERROR
  unsigned char ret = 1;

  // Line low, and wait 480us
  ow.io->set_low();

  ow.io->set_mode_out();

  microseconds->delay(480);

  // Release line and wait for 70us
  ow.io->set_mode_in();

  microseconds->delay(100);

  // Check bit value
  ret = io_read();

  // Delay for 410 us
  microseconds->delay(380);

  return ret;
}

/**
 * write_bit
 * @param bit bit to be write
 */
void Onewire::write_bit(unsigned char bit)
{
  if (bit)
  {
    // Set line low
    ow.io->set_low();
    ow.io->set_mode_out();
    microseconds->delay(10);

    // Bit high
    ow.io->set_hi();
    ow.io->set_mode_out();

    // Wait for 55 us and release the line
    microseconds->delay(55);
  }
  else
  {
    // Set line low
    ow.io->set_low();
    ow.io->set_mode_out();
    microseconds->delay(65);

    // Bit high
    ow.io->set_hi();
    ow.io->set_mode_out();

    // Wait for 5 us and release the line
    microseconds->delay(5);
  }
}

inline unsigned char Onewire::io_read(void)
{
  return ow.io->read();
}

/**
 * read_bit
 * @return read bit
 */
unsigned char Onewire::read_bit()
{
  unsigned char bit = 0;

  // Line low
  ow.io->set_mode_out();
  ow.io->set_low();

  // Release line
  ow.io->set_mode_in();
  microseconds->delay(3);

  // Read line value
  if (io_read())
  {
    // Bit is HIGH
    bit = 1;
  }

  // Wait 50us to complete 60us period
  microseconds->delay(50);

  // Return bit value
  return bit;
}

/**
 * write_byte
 * @param byte byte to be write
 */
void Onewire::write_byte(unsigned char byte)
{
  unsigned char i = 8;

  // Write 8 bits
  while (i--)
  {
    // LSB bit is first
    write_bit(byte & 0x01);
    byte >>= 1;
  }
}

/**
 * read_byte
 * @return read byte
 */
unsigned char Onewire::read_byte(void)
{
  unsigned char i = 8, byte = 0;

  while (i--)
  {
    byte >>= 1;
    byte |= (read_bit() << 7);
  }

  return byte;
}

/**
 * first
 * @return device statues:
 *      - 0: No devices detected
 *      - > 0: Device detected
 */
unsigned char Onewire::first(void)
{
  // Reset search values
  reset_search();

  // Start with searching
  return search(CMD_SEARCHROM);
}

/**
 * next
 * @return Device status:
 *            - 0: No devices detected any more
 *            - > 0: New device detected
 */
unsigned char Onewire::next(void)
{
  // Leave the search state alone
  return search(CMD_SEARCHROM);
}

/**
 * reset_search
 *
 */
void Onewire::reset_search(void)
{
  // Reset the search state
  ow.LastDiscrepancy = 0;
  ow.LastDeviceFlag = 0;
  ow.LastFamilyDiscrepancy = 0;
}

/**
 * search Searches for OneWire devices on specific Onewire port
 * @param command search command
 * @return Device status:
 *            - 0: No devices detected
 *            - > 0: Device detected
 */
unsigned char Onewire::search(unsigned char command)
{
  unsigned char id_bit_number;
  unsigned char last_zero, rom_byte_number, search_result;
  unsigned char id_bit, cmp_id_bit;
  unsigned char rom_byte_mask, search_direction;

  // Initialize for search
  id_bit_number = 1;
  last_zero = 0;
  rom_byte_number = 0;
  rom_byte_mask = 1;
  search_result = 0;

  // Check if any devices
  if (!ow.LastDeviceFlag)
  {
    // 1-Wire reset
    if (reset())
    {
      // Reset the search
      ow.LastDiscrepancy = 0;
      ow.LastDeviceFlag = 0;
      ow.LastFamilyDiscrepancy = 0;
      return 0;
    }

    // Issue the search command
    write_byte(command);

    // Loop to do the search
    do
    {
      // Read a bit and its complement
      id_bit = read_bit();
      cmp_id_bit = read_bit();

      // Check for no devices on 1-wire
      if ((id_bit == 1) && (cmp_id_bit == 1))
      {
        break;
      }
      else
      {
        // All devices coupled have 0 or 1
        if (id_bit != cmp_id_bit)
        {
          // Bit write value for search
          search_direction = id_bit;
        }
        else
        {
          // If this discrepancy is before the Last Discrepancy on a previous next then pick the same as last time
          if (id_bit_number < ow.LastDiscrepancy)
          {
            search_direction = ((ow.ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
          }
          else
          {
            // If equal to last pick 1, if not then pick 0
            search_direction = (id_bit_number == ow.LastDiscrepancy);
          }

          // If 0 was picked then record its position in LastZero
          if (search_direction == 0)
          {
            last_zero = id_bit_number;

            // Check for Last discrepancy in family
            if (last_zero < 9)
            {
              ow.LastFamilyDiscrepancy = last_zero;
            }
          }
        }

        // Set or clear the bit in the ROM byte rom_byte_number with mask rom_byte_mask
        if (search_direction == 1)
        {
          ow.ROM_NO[rom_byte_number] |= rom_byte_mask;
        }
        else
        {
          ow.ROM_NO[rom_byte_number] &= ~rom_byte_mask;
        }

        // Serial number search direction write bit
        write_bit(search_direction);

        // Increment the byte counter id_bit_number and shift the mask rom_byte_mask
        id_bit_number++;
        rom_byte_mask <<= 1;

        // If the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
        if (rom_byte_mask == 0)
        {
          rom_byte_number++;
          rom_byte_mask = 1;
        }
      }
      // Loop until through all ROM bytes 0-7
    } while (rom_byte_number < 8);

    // If the search was successful then
    if (!(id_bit_number < 65))
    {
      // Search successful so set LastDiscrepancy, LastDeviceFlag, search_result
      ow.LastDiscrepancy = last_zero;

      // Check for last device
      if (ow.LastDiscrepancy == 0)
      {
        ow.LastDeviceFlag = 1;
      }

      search_result = 1;
    }
  }

  // If no device found then reset counters so next 'search' will be like a first
  if (!search_result || !ow.ROM_NO[0])
  {
    ow.LastDiscrepancy = 0;
    ow.LastDeviceFlag = 0;
    ow.LastFamilyDiscrepancy = 0;
    search_result = 0;
  }

  return search_result;
}

/**
 * verify
 * @return TODO
 */
int Onewire::verify(void)
{
  unsigned char rom_backup[8];
  int i, rslt, ld_backup, ldf_backup, lfd_backup;

  // Keep a backup copy of the current state
  for (i = 0; i < 8; i++)
    rom_backup[i] = ow.ROM_NO[i];
  ld_backup = ow.LastDiscrepancy;
  ldf_backup = ow.LastDeviceFlag;
  lfd_backup = ow.LastFamilyDiscrepancy;

  // Set search to find the same device
  ow.LastDiscrepancy = 64;
  ow.LastDeviceFlag = 0;

  if (search(CMD_SEARCHROM))
  {
    // Check if same device found
    rslt = 1;
    for (i = 0; i < 8; i++)
    {
      if (rom_backup[i] != ow.ROM_NO[i])
      {
        rslt = 1;
        break;
      }
    }
  }
  else
  {
    rslt = 0;
  }

  // Restore the search state
  for (i = 0; i < 8; i++)
  {
    ow.ROM_NO[i] = rom_backup[i];
  }
  ow.LastDiscrepancy = ld_backup;
  ow.LastDeviceFlag = ldf_backup;
  ow.LastFamilyDiscrepancy = lfd_backup;

  // Return the result of the verify
  return rslt;
}

/**
 * target_setup
 * @param family_code device family code to be set
 */
void Onewire::target_setup(unsigned char family_code)
{
  unsigned char i;

  // Set the search state to find SearchFamily type devices
  ow.ROM_NO[0] = family_code;
  for (i = 1; i < 8; i++)
  {
    ow.ROM_NO[i] = 0;
  }

  ow.LastDiscrepancy = 64;
  ow.LastFamilyDiscrepancy = 0;
  ow.LastDeviceFlag = 0;
}

/**
 * family_skip_setup
 *
 */
void Onewire::family_skip_setup(void)
{
  // Set the Last discrepancy to last family discrepancy
  ow.LastDiscrepancy = ow.LastFamilyDiscrepancy;
  ow.LastFamilyDiscrepancy = 0;

  // Check for end of list
  if (ow.LastDiscrepancy == 0)
  {
    ow.LastDeviceFlag = 1;
  }
}

/**
 * get_rom Gets ROM number from device from search
 * @param index device rom index
 * @return rom index value
 */
unsigned char Onewire::get_rom(unsigned char index)
{
  return ow.ROM_NO[index];
}

/**
 * select Selects specific slave on bus
 * @param addr Pointer to first location of 8-bytes long ROM address
 */
void Onewire::select(unsigned char *addr)
{
  unsigned char i;

  write_byte(CMD_MATCHROM);

  for (i = 0; i < 8; i++)
  {
    write_byte(*(addr + i));
  }
}

/**
 * select_with_pointer Selects specific slave on bus with pointer address
 * @param ROM Pointer to first byte of ROM address
 */
void Onewire::select_with_pointer(unsigned char *ROM)
{
  unsigned char i;

  write_byte(CMD_MATCHROM);

  for (i = 0; i < 8; i++)
  {
    write_byte(*(ROM + i));
  }
}

/**
 * get_full_rom
 * @param firstIndex Pointer to first location for first byte, other bytes are automatically incremented
 */
void Onewire::get_full_rom(unsigned char *firstIndex)
{
  unsigned char i;

  for (i = 0; i < 8; i++)
  {
    *(firstIndex + i) = ow.ROM_NO[i];
  }
}

void Onewire::power(void)
{
  ow.io->set_hi();
  ow.io->set_mode_out();
}

