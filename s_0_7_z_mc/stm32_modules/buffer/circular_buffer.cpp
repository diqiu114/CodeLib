#include "circular_buffer.h"

Circular_buffer::Circular_buffer(unsigned int size, unsigned char *ex_buffer)
{
  buffer = new Buffer_t();

  memset(buffer, 0, sizeof(Buffer_t));

  if (ex_buffer != NULL)
  {
    buffer->Buffer = ex_buffer;
  }
  else
  {
    buffer->Buffer = (unsigned char *)new unsigned char[size];
  }

  buffer->StringDelimiter = '\n';
  buffer->Size = size;
}

/**
 * @param data
 * @param unsigned int len
 * @return unsigned int
 */
unsigned int Circular_buffer::write(unsigned char *data, unsigned int len)
{
  // check parameter correct
  if ((!data) && (len == 0))
  {
    return 0;
  }

  // Check input pointer
  if (buffer->In >= buffer->Size)
  {
    buffer->In = 0;
  }

  // Get free memory
  unsigned int free = get_free();
  // Check available memory
  if (free < len)
  {
    // If no memory, stop execution
    if (free == 0)
    {
      return 0;
    }

    // Set values for write
    len = free;
  }

  // Calculate number of elements we can put at the end of buffer
  unsigned int tocopy = buffer->Size - buffer->In;

  // Check for copy count
  if (tocopy > len)
  {
    tocopy = len;
  }

  // Copy content to buffer
  memcpy(&buffer->Buffer[buffer->In], data, tocopy);

  // Increase number of bytes we copied already
  int i = 0;
  i += tocopy;
  buffer->In += tocopy;
  len -= tocopy;

  // Check if anything to write
  if (len > 0)
  {
    // Start from the beginning of buffer
    buffer->In = 0;

    // Copy content
    memcpy(&buffer->Buffer[buffer->In], &data[i], len);

    // Set input pointer
    buffer->In = len;
  }

  // Check input overflow
  if (buffer->In >= buffer->Size)
  {
    buffer->In = 0;
  }

  // Return number of elements stored In memory
  return (i + len);
}

/**
 * @param data
 * @return unsigned int
 */
unsigned int Circular_buffer::write(char *data)
{
  return write((unsigned char *)data, strlen(data));
}

/**
 * @param data
 * @param unsigned int len
 * @return unsigned int
 */
unsigned int Circular_buffer::write_top(unsigned char *data, unsigned int len)
{
  unsigned int i = 0;

  // check parameter correct
  if ((!data) && (len == 0))
  {
    return 0;
  }

  // Check input pointer
  if (buffer->In >= buffer->Size)
  {
    buffer->In = 0;
  }

  if (buffer->Out >= buffer->Size)
  {
    buffer->Out = 0;
  }

  // Get free memory
  unsigned int free = get_free();
  // Check available memory
  if (free < len)
  {
    // If no memory, stop execution
    if (free == 0)
    {
      return 0;
    }

    // Set values for write
    len = free;
  }

  // We have calculated memory for write

  // Start on bottom
  data += len - 1;

  // Go through all elements
  while (len--)
  {
    if (buffer->Out == 0)
    {
      buffer->Out = buffer->Size - 1;
    }
    else
    {
      buffer->Out--;
    }

    // Add to buffer
    buffer->Buffer[buffer->Out] = *data--;

    // Increase pointers
    i++;
  }

  // Return number of elements written
  return i;
}

/**
 * @param data
 * @return unsigned int
 */
unsigned int Circular_buffer::write_top(char *data)
{
  return write_top((unsigned char *)data, strlen(data));
}

/**
 * @param data
 * @param unsigned int len
 * @return unsigned int
 */
unsigned int Circular_buffer::read(unsigned char *data, unsigned int len)
{
  unsigned int i = 0;
  unsigned int full;
  unsigned int tocopy;

  // check parameter correct
  if ((!data) && (len == 0))
  {
    return 0;
  }

  if (buffer->Out >= buffer->Size)
  {
    buffer->Out = 0;
  }

  // Get free memory
  full = get_full();

  // Check available memory
  if (full < len)
  {
    // If no memory, stop execution
    if (full == 0)
    {
      return 0;
    }

    // Set values for write
    len = full;
  }

  // Calculate number of elements we can put at the end of buffer
  tocopy = buffer->Size - buffer->Out;

  // Check for copy count
  if (tocopy > len)
  {
    tocopy = len;
  }

  // Copy content from buffer
  memcpy(data, &buffer->Buffer[buffer->Out], tocopy);

  // Increase number of bytes we copied already
  i += tocopy;
  buffer->Out += tocopy;
  len -= tocopy;

  // Check if anything to read
  if (len > 0)
  {
    // Start from the beginning of buffer
    buffer->Out = 0;

    // Copy content
    memcpy(&data[i], &buffer->Buffer[buffer->Out], len);

    // Set input pointer
    buffer->Out = len;
  }

  // Check output overflow
  if (buffer->Out >= buffer->Size)
  {
    buffer->Out = 0;
  }

  // Return number of elements stored In memory
  return (i + len);
}

/**
 * @param data
 * @return unsigned int
 */
unsigned int Circular_buffer::read(char *data)
{
  return read((unsigned char *)data, strlen(data));
}

/**
 * @param void
 * @return unsigned int
 */
unsigned int Circular_buffer::get_free(void)
{
  unsigned int ret = 0;

  if (buffer->In == buffer->Out)
  {
    ret = buffer->Size;
  }
  else if (buffer->Out > buffer->In)
  {
    ret = buffer->Out - buffer->In;
  }
  else if (buffer->In > buffer->Out)
  {
    ret = buffer->Size - (buffer->In - buffer->Out);
  }
  else
  {
    ret = 0;
  }

  return ret - 1;
}

/**
 * @param void
 * @return unsigned int
 */
unsigned int Circular_buffer::get_full(void)
{
  unsigned int ret = 0;

  if (buffer->In == buffer->Out)
  {
    ret = 0;
  }
  else if (buffer->In > buffer->Out)
  {
    ret = buffer->In - buffer->Out;
  }
  else if (buffer->Out > buffer->In)
  {
    ret = buffer->Size - (buffer->Out - buffer->In);
  }
  else
  {
    ret = 0;
  }

  return ret;
}

unsigned int Circular_buffer::get_size(void)
{
  return buffer->Size;
}

/**
 * @param void
 * @return void
 */
void Circular_buffer::reset(void)
{
  buffer->In = 0;
  buffer->Out = 0;
}

/**
 * @param element
 * @return int
 */
int Circular_buffer::find_element(unsigned char element)
{
  unsigned int Num = 0;
  unsigned int Out = 0;
  unsigned int retval = 0;

  // Create temporary variables
  Num = get_free();
  Out = buffer->Out;

  // Go through input elements
  while (Num > 0)
  {
    // Check output overflow
    if (Out >= buffer->Size)
    {
      Out = 0;
    }

    // Check for element
    if ((unsigned char)buffer->Buffer[Out] == (unsigned char)element)
    {
      // Element found, return position in buffer
      return retval;
    }

    // Set new variables
    Out++;
    Num--;
    retval++;
  }

  // Element is not in buffer
  return -1;
}

/**
 * @param data
 * @param size
 * @return int
 */
int Circular_buffer::find(unsigned char *data, unsigned int size)
{
  unsigned int Num = 0;
  unsigned int Out = 0;
  unsigned int i = 0;
  unsigned int retval = 0;
  unsigned char found = 0;

  // number of elements in buffer
  if ((Num = get_full()) < size)
  {
    return -1;
  }

  // Create temporary variables
  Out = buffer->Out;

  // Go through input elements in buffer
  while (Num > 0)
  {
    // Check output overflow
    if (Out >= buffer->Size)
    {
      Out = 0;
    }

    // Check if current element in buffer matches first element in data array
    if ((unsigned char)buffer->Buffer[Out] == (unsigned char)data[0])
    {
      found = 1;
    }

    // Set new variables
    Out++;
    Num--;
    retval++;

    // We have found first element
    if (found)
    {
      // First character found
      // Check others
      i = 1;
      while (i < size && Num > 0)
      {
        // Check output overflow
        if (Out >= buffer->Size)
        {
          Out = 0;
        }

        // Check if current character in buffer matches character in string
        if ((unsigned char)buffer->Buffer[Out] != (unsigned char)data[i])
        {
          retval += i - 1;
          break;
        }

        // Set new variables
        Out++;
        Num--;
        i++;
      }

      // We have found data sequence in buffer
      if (i == size)
      {
        return retval;
      }
    }
  }

  // Data sequence is not in buffer
  return -1;
}

/**
 * @param str
 * @return void
 */
void Circular_buffer::set_delimiter(unsigned char str)
{
  buffer->StringDelimiter = str;
}

/**
 * @param pos
 * @param element
 * @return char
 */
char Circular_buffer::check_element(unsigned int pos, unsigned char *element)
{
  unsigned int In, Out, i = 0;

  // Read current values
  In = buffer->In;
  Out = buffer->Out;

  // Set pointers to right location
  while (i < pos && (In != Out))
  {
    // Increase output pointer
    Out++;
    i++;

    // Check overflow
    if (Out >= buffer->Size)
    {
      Out = 0;
    }
  }

  // If positions match
  if (i == pos)
  {
    // Save element
    *element = buffer->Buffer[Out];

    // Return OK
    return 1;
  }

  // Return zero
  return 0;
}

Circular_buffer::~Circular_buffer()
{
}
