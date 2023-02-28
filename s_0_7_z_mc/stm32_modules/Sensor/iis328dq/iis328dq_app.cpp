#include "iis328dq_app.h"
#include "string.h"

Iis328dq_app::Iis328dq_app(iis328dq_fs_t _full_scale, iis328dq_dr_t _data_rate)
{
  full_scale = _full_scale;
  data_rate = _data_rate;

  dev_ctx.write_reg = stm32_write_regs;
  dev_ctx.read_reg = stm32_read_regs;
  dev_ctx.handle = comm_handle;

  memset((void*)&acc_raw_data, 0, sizeof(acc_raw_data));
}

Iis328dq_app::~Iis328dq_app()
{
}

bool Iis328dq_app::dev_found(void)
{
  unsigned char whoamI = 0;

  iis328dq_device_id_get(&dev_ctx, &whoamI);

  return (whoamI == IIS328DQ_ID);
}

void Iis328dq_app::set_full_scale(iis328dq_fs_t fs)
{
  full_scale = fs;
  dev_init();
}

void Iis328dq_app::dev_init(void)
{
  /*
   *  Enable Block Data Update
   */
  iis328dq_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Set full scale
   */
  iis328dq_full_scale_set(&dev_ctx, full_scale);

  /*
   * Configure filtering chain
   */
  /* Accelerometer - High Pass / Slope path */
  iis328dq_hp_path_set(&dev_ctx, IIS328DQ_HP_ON_OUT);
//  iis328dq_hp_path_set(&dev_ctx, IIS328DQ_HP_DISABLE);

  /*
   * Set Output Data Rate
   */
  iis328dq_data_rate_set(&dev_ctx, data_rate);
}

bool Iis328dq_app::get_acc_data(float *data)
{
  bool ret = false;
  iis328dq_reg_t reg;
  
  iis328dq_status_reg_get(&dev_ctx, &reg.status_reg);
  
  // data updated
  if (reg.status_reg.zyxda)
  {
    memset((void*)&acc_raw_data, 0, sizeof(acc_raw_data));
    iis328dq_acceleration_raw_get(&dev_ctx, acc_raw_data.u8bit);
    switch (full_scale)
    {
    case IIS328DQ_2g:
      data[0] = IIS328DQ_FROM_FS_2g_TO_mg(acc_raw_data.i16bit[0]);
      data[1] = IIS328DQ_FROM_FS_2g_TO_mg(acc_raw_data.i16bit[1]);
      data[2] = IIS328DQ_FROM_FS_2g_TO_mg(acc_raw_data.i16bit[2]);
      break;
    case IIS328DQ_4g:
      data[0] = IIS328DQ_FROM_FS_4g_TO_mg(acc_raw_data.i16bit[0]);
      data[1] = IIS328DQ_FROM_FS_4g_TO_mg(acc_raw_data.i16bit[1]);
      data[2] = IIS328DQ_FROM_FS_4g_TO_mg(acc_raw_data.i16bit[2]);
      break;
    case IIS328DQ_8g:
      data[0] = IIS328DQ_FROM_FS_8g_TO_mg(acc_raw_data.i16bit[0]);
      data[1] = IIS328DQ_FROM_FS_8g_TO_mg(acc_raw_data.i16bit[1]);
      data[2] = IIS328DQ_FROM_FS_8g_TO_mg(acc_raw_data.i16bit[2]);
      break;
    default:
      data[0] = acc_raw_data.i16bit[0];
      data[1] = acc_raw_data.i16bit[1];
      data[2] = acc_raw_data.i16bit[2];
      break;
    }

    ret = true;
  }

  return ret;
}
