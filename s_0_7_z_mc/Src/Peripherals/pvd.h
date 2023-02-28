#ifndef __PVD_H_
#define __PVD_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
#include <stdint.h>
void pvd_init(void);    
uint8_t pvd_get_power_flag(void);
     
#ifdef __cplusplus
}
#endif


#endif
