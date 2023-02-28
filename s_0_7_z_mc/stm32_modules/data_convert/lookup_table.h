/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      查表法

***********************************************************/

#ifndef _LOOKUP_TABLE_H_
#define _LOOKUP_TABLE_H_
#include "data_convert_if.h"
#include <math.h>

#define ROUND(x) ((x > 0.0f) ? (x + 0.5f) : (x - 0.5f))

class Lookup_table_params
{
public:
  Lookup_table_params(unsigned int _line_size,
                      unsigned int _row_size = 1,
                      int _line_offset = 0,
                      int _row_offset = 0,
                      float _line_rate = 1,
                      float _row_rate = 1,
                      float _val_rate = 1,
                      bool _line_order = true,
                      bool _row_order = true)
  {
    if(_line_size < 1)
    {
      _line_size = 1;
    }
    if(_row_size < 1)
    {
      _row_size = 1;
    }
    line_size = _line_size;
    row_size = _row_size;
    line_offset = _line_offset;
    row_offset = _row_offset;
    line_rate = _line_rate;
    row_rate = _row_rate;
    val_rate = _val_rate;
    line_order = _line_order;
    row_order = _row_order;
  };

  unsigned int line_size;
  unsigned int row_size;
  int line_offset;
  int row_offset;
  float line_rate;
  float row_rate;
  float val_rate;
  bool line_order;
  bool row_order;
};

template <typename T>
class Lookup_table : public Data_convert_if
{
public:
  Lookup_table(T *_table, Lookup_table_params *_params);
  virtual ~Lookup_table();
  virtual float convert(float value1, float value2 = 0, float value3 = 0);

private:
  T *table;
  int line_offset;
  int row_offset;
  unsigned int line_size;
  float val_rate;
  Lookup_table_params *params;
};

template <typename T>
Lookup_table<T>::Lookup_table(T *_table, Lookup_table_params *_params)
{
  table = _table;
  params = _params;
}

template <typename T>
Lookup_table<T>::~Lookup_table()
{
}

template <typename T>
float Lookup_table<T>::convert(float value1, float value2, float value3)
{
  if (table == NULL)
  {
    return 0;
  }

  int line_idx = 0;
  int row_idx = 0;
  int raw_line_idx = ROUND(value1 * params->line_rate);
  int raw_row_idx = ROUND(value2 * params->row_rate);

  if (params->line_size > 1)
  {
    if (params->line_order)
    {
      if (raw_line_idx < params->line_offset)
      {
        raw_line_idx = params->line_offset;
      }

      line_idx = raw_line_idx - params->line_offset;
    }
    else
    {
      if (raw_line_idx > params->line_offset)
      {
        raw_line_idx = params->line_offset;
      }
      line_idx = params->line_offset - raw_line_idx;
    }
  }

  if (params->row_size > 1)
  {
    if (params->row_order)
    {
      if (raw_row_idx < params->row_offset)
      {
        raw_row_idx = params->row_offset;
      }

      row_idx = raw_row_idx - params->row_offset;
    }
    else
    {
      if (raw_row_idx > params->row_offset)
      {
        raw_row_idx = params->row_offset;
      }
      row_idx = params->row_offset - raw_row_idx;
    }
  }
  if (line_idx >= params->line_size)
  {
    line_idx = params->line_size - 1; 
  }
  if (row_idx >= params->row_size)
  {
    row_idx = params->row_size - 1;
  }

  int offset = row_idx == 0 ? line_idx : line_idx + (row_idx * params->line_size);
  return table[offset] / params->val_rate;
}

#endif // _LOOKUP_TABLE_H_
