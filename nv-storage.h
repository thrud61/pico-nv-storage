#ifndef __NV
#define __NV

#include "pico/stdlib.h"

// 24LC16B
#define DEVICE_ADDR 0xA0
#define NV_READ 1
#define NV_WRITE 0

// size in bytes for
#define NV_MAX_SIZE 2048

class NV_Storage
{
  private:
    uint8_t nv[NV_MAX_SIZE];
    bool write_byte(int);
    bool full_read(void);
    bool full_write(void);
    
  public:
    NV_Storage(void);
    bool read(void *NV_Data, int size);
    bool write(void *NV_Data, int size);
} ;
#endif
