# pico-nv-storage
project to help with using EEProm (24LCxx chips) on the RPi Pico as non-volatile storage.

I tried using the internal pull up resitors on the SDA/SCL for the I2C, but it only worked with the scope probes on the SCL (which was a shame as they were connected all day), I added 2x 2k2 pull ups externally, which allowed 400KHz running, but I used 100KHz as the chips are small and don't need to run fast. 


Uses I2C0 mapped to GPIO 12 and 13 on the Pico.

Pico          24LCxx
----          ------
GPIO 12   -   SDA      
GPIO 13   -   SCL
VCC       -   VCC
GND       -   GND
GND       -   WP
VCC     2k2   SDA
VCC     2k2   SCL
