#include "nv-storage.h"
#include <string.h>

NV_Storage NV;

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
  
  // put your setup code here, to run once:
//  NV.read(&NV_data, sizeof(NV_data));

  Serial.printf("Loaded %d\nX       %d\nY       %d\ntext   %10s\n",NV_data.loaded,NV_data.x,NV_data.y,NV_data.text);

  NV_data.loaded = true;
  NV_data.x=25;
  NV_data.y=11;
  strcpy(NV_data.text,"Working");

  Serial.printf("Loaded %d\nX       %d\nY       %d\ntext   %10s\n",NV_data.loaded,NV_data.x,NV_data.y,NV_data.text);

//  NV.write(&NV_data, sizeof(NV_data));
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.printf("loop\n");
sleep_ms(1000);
}

void loop1()
{
  // lets flash the led at 1/10th of the actual call rate
  led++;
  gpio_put(PICO_DEFAULT_LED_PIN, (led / 10) & 1);
  sleep_ms(10);
}
