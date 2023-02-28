
#ifndef _IIS328DQ_COMM_H_
#define _IIS328DQ_COMM_H_

#ifdef __cplusplus
  extern "C" {
#endif
    
#define USE_SPI (1)
#define USE_I2C (0)

extern void *comm_handle;

int stm32_write_regs(void *handle, unsigned char Reg, unsigned char *Bufp, unsigned short len);
int stm32_read_regs(void *handle, unsigned char Reg, unsigned char *Bufp, unsigned short len);

#ifdef __cplusplus
}
#endif
    
#endif // _IIS328DQ_COMM_H_

