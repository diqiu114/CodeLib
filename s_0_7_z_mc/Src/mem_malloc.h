#ifndef __MEM_MALLOC_H_
#define __MEM_MALLOC_H_

#ifdef __cplusplus
 extern "C" {
#endif
     
void *sys_malloc(size_t size);
void sys_free(void *mem);

     
#ifdef __cplusplus
}
#endif

#endif
