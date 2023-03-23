// EEProm class to connect the 24LCxx series EEProms to the rpi pico
// only supports upto 24LC16 which give 2k bytes non-volatile storage
// bigger than that needs a different protocol, and probably higher speed
// clock to be useful.
//
// Author James Wilson
// 18th March 2023
//

// #include <Arduino.h> // only needed for debugging with Serial.printf
#include "nv-storage.h"
#include <string.h>
#include "hardware/i2c.h"

 
#include "pico/stdlib.h"

using namespace _NV;

_NV::NV_Storage::NV_Storage(void)
{
  // Set to use I2C0 on GPIO12 (SDA) and GPIO13 (SCL)
  // can't run at 100KHz with internal pull-up, needed external pull-ups
  // adding 2.2k external pull up allowed 400KHz, didn't do much testing though
  // fine at 100KHz for small devices
  i2c_init(i2c0, 100 * 1000);

  // set up for I2C0 on GPIO 12/13
  gpio_set_function(12, GPIO_FUNC_I2C);
  gpio_set_function(13, GPIO_FUNC_I2C);
  gpio_init(14);
  gpio_set_dir(14, GPIO_OUT);
  gpio_put(14, 1);
  
  gpio_pull_up(12);
  gpio_pull_up(13);
  sleep_ms(100);
  // read the entire EEPRom
  full_read();
}

//
//reads the entire eeprom into internal cache
//
int _NV::NV_Storage::full_read(void)
{
  uint8_t control = NV_DEVICE_ADDR | NV_READ;
  uint8_t addr = 0;
  int r;

  // first write the address, which for the full read is 0
  r = i2c_write_blocking(i2c0, NV_DEVICE_ADDR, &addr, 1, false);

  sleep_ms(1);

  // now read the data, we will read it all into cache
  r = i2c_read_blocking(i2c0, control, nv, NV_MAX_SIZE, false);

  return r;
}

// copies the internal cache into our object
bool _NV::NV_Storage::read(void *NV_Data, int size)
{
  //we don't need to read the EEProm as it is in the nv array
  // don't do anything if there is no valid data size
  if (size < 1 || size > NV_MAX_SIZE)
    return false;

  memcpy(NV_Data, nv, size);

  return true;
}

//
// write a single byte from the internal cache to
// the same byte on the EEProm
//
// we only need the address as the nv cache is mapped 1 to 1 with eeprom data
bool _NV::NV_Storage::write_byte(uint16_t addr)
{
  // support up to 24LC16
  uint8_t control = NV_DEVICE_ADDR | (((addr >> 8) & 7) << 1) | NV_WRITE;
  uint8_t buffer[2];

  buffer[0] = addr & 0xFF;
  buffer[1] = nv[addr];
  i2c_write_blocking(i2c0, control, buffer, 2, false);
  return true;
}

// write a page of cache to the eeprom
bool _NV::NV_Storage::write_page(uint16_t addr)
{
  uint8_t control;
  uint8_t buffer[9];
  int r;

  control = NV_DEVICE_ADDR | (((addr >> 8) & 7) << 1) | NV_WRITE;
  buffer[0] = addr & 0xFF;

  memcpy(&buffer[1], &nv[addr], NV_PAGE_SIZE);
  r = i2c_write_blocking(i2c0, control, buffer, NV_PAGE_SIZE + 1 , false);
  sleep_ms(NV_WRITE_DELAY);

  return r > 0;
}

//
// Write out our object to the cache then the eeprom
//
bool _NV::NV_Storage::write(void *NV_Data, int size)
{
  int i;
  uint8_t control;
  uint8_t buffer[9];
  bool res;

  // don't do anything if there is no valid data size
  if (size < 1 || size > NV_MAX_SIZE)
    return  false;

  // copy our object to the cache
  memcpy(nv, NV_Data, size);

  // look for pages/bytes to write out
  for (i = 0; i < size;)
  {
    // if we are on the page boundary and the amount to write is atleast a page
    if (((i % NV_PAGE_SIZE) == 0) && (size - i) >= NV_PAGE_SIZE)
    {
      res = write_page(i);
      i += NV_PAGE_SIZE;
    }
    else
    {
      // nope just a byte
      res = write_byte(i);
      i++;
    }
    sleep_ms(NV_WRITE_DELAY);
  }

  return true;
}
