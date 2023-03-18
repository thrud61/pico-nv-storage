// EEProm class to connect the 24LCxx series EEProms to the rpi pico
// only supports upto 24LC16 which give 2k bytes non-volatile storage
// bigger than that needs a different protocol, and probably higher speed
// clock to be useful.
//
// Author James Wilson
// 18th March 2023
//
#ifndef __NV
#define __NV

#include "pico/stdlib.h"
#include "hardware/i2c.h"

namespace _NV
{
  // 24LCxxB
  const uint16_t NV_MAX_SIZE = 256; // size in bytes for 24LC02

  // these change less frequently
  const uint8_t NV_PAGE_SIZE = 8;

  // may never change
  const uint8_t NV_DEVICE_ADDR = 0x50;

  // not sure these ever change
  const uint8_t NV_READ = 1;
  const uint8_t NV_WRITE = 0;
  const uint8_t NV_WRITE_DELAY = 5;
  
  class NV_Storage
  {
    private:
      uint8_t nv[NV_MAX_SIZE];
      bool write_byte(uint16_t);
      bool write_page(uint16_t);

    public:
      NV_Storage(void);
      bool read(void *NV_Data, int size);
      bool write(void *NV_Data, int size);
      int full_read(void);
  } ;
}
#endif
