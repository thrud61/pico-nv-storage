//
// Example of using the NV_storage class configured for the 24LC02B eeprom
//
//
// Author James Wilson
// 18th March 2023
//

#include "pico/stdlib.h"
#include "nv-storage.h"
#include <string.h>

using namespace _NV;

NV_Storage NV;

// structure to store the non-volatile data
// can't use pointers as they probably wont work
// so no heap, or char * (which might work
// until on literals, until the code base changes).
struct NV_struct
{
  bool loaded;
  int x;
  int y;
  char text[10];
} NV_data;

int led=0;

void setup() {
  Serial.begin(115200);

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_LED_PIN, 1);

  sleep_ms(5000);

  Serial.printf("read %d\n",NV.full_read());
  
  // put your setup code here, to run once:
  NV.read(&NV_data, sizeof(NV_data));

  Serial.printf("Loaded %d\nx %d\ny %d\ntext %s\n",NV_data.loaded,NV_data.x,NV_data.y,NV_data.text);

  NV_data.loaded = !NV_data.loaded;
  NV_data.x = 9876;
  NV_data.y = 12345;
  strcpy(NV_data.text,"working");

  NV.write(&NV_data, sizeof(NV_data));
  Serial.printf("Loaded %d\nx %d\ny %d\ntext %s\n",NV_data.loaded,NV_data.x,NV_data.y,NV_data.text);
  Serial.printf("read %d\n",NV.full_read());

  // put your setup code here, to run once:
  NV.read(&NV_data, sizeof(NV_data));

  Serial.printf("Loaded %d\nx %d\ny %d\ntext %s\n",NV_data.loaded,NV_data.x,NV_data.y,NV_data.text);

}

void loop() {
  // lets flash the led at 1/10th of the actual call rate
  // lets us know if bad things have happend
  led++;
  gpio_put(PICO_DEFAULT_LED_PIN, (led / 10) & 1);
  sleep_ms(10);
}
