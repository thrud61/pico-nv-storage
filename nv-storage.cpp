#include "nv-storage.h"
#include <string.h>
#include "hardware/i2c.h"


NV_Storage::NV_Storage(void)
{
  // Set to use I2C0 on GPIO0 (SDA) and GPIO1 (SCL)
  i2c_init(i2c0, 100 * 1000);
  gpio_set_function(0, GPIO_FUNC_I2C);
  gpio_set_function(1, GPIO_FUNC_I2C);
  gpio_pull_up(0);
  gpio_pull_up(1);

  // read the entire EEPRom
  full_read();
}

bool NV_Storage::full_read(void)
{
  uint8_t control = DEVICE_ADDR | NV_READ;
  uint8_t addr = 0;

  // first write the address which for the full read is 0
  i2c_write_blocking(i2c0, control, &addr, 1, true);
  // now read the data, we will read it all into cache
  i2c_read_blocking(i2c0, control, nv, NV_MAX_SIZE, true);

  return true;
}

bool NV_Storage::read(void *NV_Data, int size)
{
  //we don't need to read the EEProm as it is in the nv array
  // don't do anything if there is no valid data size
  if (size < 1 || size > NV_MAX_SIZE)
    return false;

  memcpy(NV_Data, nv, size);

  return true;
}

//
// write a single byte from the internal buffer to
// the same byte on the EEProm
//
// we only need the address as the nv cache is mapped 1 to 1 with eeprom data
bool NV_Storage::write_byte(int addr)
{
  uint8_t control = DEVICE_ADDR | ((addr & 0x700) >> 7 ) | NV_WRITE;
  uint8_t buffer[2];

  buffer[0] = addr & 0xFF;
  buffer[1] = nv[addr];
  i2c_write_blocking(i2c0, control, buffer, 1, true);

  return true;
}

bool NV_Storage::full_write(void)
{
  uint8_t control = DEVICE_ADDR | NV_WRITE;

  i2c_write_blocking(i2c0, control, nv, NV_MAX_SIZE, true);

  return true;
}


bool NV_Storage::write(void *NV_Data, int size)
{
  int i;

  // don't do anything if there is no valid data size
  if (size < 1 || size > NV_MAX_SIZE)
    return  false;

  // make sure something has changed
  if (memcmp(NV_Data, nv, size) == 0)
    return true;

  // move the data to our internal buffer and write to EEProm
  for (i = 0; i < size; i++)
  {
    // we will write out only changed bytes, to reduce time waiting on eeprom
    if (nv[i] != ((uint8_t *)NV_Data)[i])
    {
      nv[i] = ((uint8_t *)NV_Data)[i];
      write_byte(i);
    }
  }

  return true;
}
