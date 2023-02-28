/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      通用循环buffer类，根据TM_BUFFER移植
*
***********************************************************/
#ifndef _CIRCULAR_BUFFER_
#define _CIRCULAR_BUFFER_

#include "stdbool.h"
#include "string.h"

/**
 * @brief  Buffer structure
 */
typedef struct _tag_buffer_t
{
  unsigned int Size;             /*!< Size of buffer in units of bytes, DO NOT MOVE OFFSET, 0 */
  unsigned int In;               /*!< Input pointer to save next value, DO NOT MOVE OFFSET, 1 */
  unsigned int Out;              /*!< Output pointer to read next value, DO NOT MOVE OFFSET, 2 */
  unsigned char *Buffer;         /*!< Pointer to buffer data array, DO NOT MOVE OFFSET, 3 */
  unsigned char Flags;           /*!< Flags for buffer, DO NOT MOVE OFFSET, 4 */
  unsigned char StringDelimiter; /*!< Character for string delimiter when reading from buffer as string, DO NOT MOVE OFFSET, 5 */
  void *UserParameters;          /*!< Pointer to user value if needed */
} Buffer_t;

class Circular_buffer
{
public:
  Circular_buffer(unsigned int size, unsigned char *ex_buffer = NULL);
  ~Circular_buffer();
  
  unsigned int write(unsigned char *data, unsigned int len);
  unsigned int write(char *data);
  unsigned int write_top(unsigned char *data, unsigned int len);
  unsigned int write_top(char *data);
  unsigned int read(unsigned char *data, unsigned int len);
  unsigned int read(char *data);
  unsigned int get_free(void);
  unsigned int get_full(void);
  unsigned int get_size(void);
  void reset(void);
  int find_element(unsigned char element);
  int find(unsigned char *data, unsigned int size);
  void set_delimiter(unsigned char str);
  char check_element(unsigned int pos, unsigned char *element);

private:
  Buffer_t *buffer;
};

#endif //_CIRCULAR_BUFFER_
