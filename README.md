# pico-nv-storage
project to help with using EEProm (24LCxx chips) on the RPi Pico as non-volatile storage, supports chips upto 24LC16B, configured currently for the 24LC02B.

I tried using the internal pull up resitors on the SDA/SCL for the I2C, but it only worked with the scope probes on the SCL (which was a shame as they were connected all day), I added 2x 2k2 pull ups externally, which allowed 400KHz running, but I used 100KHz as the chips are small and don't need to run fast. 


Uses I2C0 mapped to GPIO 12 and 13 on the Pico.
<br>
<table>
<tr>
  <td>Pico</td><td></td><td>24LCxx</td>
</tr>
<tr>
  <td></td><td></td><td></td>
</tr>
<tr>
  <td>GPIO 12</td><td>-</td><td>SDA</td>
</tr>
<tr>
  <td>GPIO 13</td><td>-</td><td>SCL</td>
</tr>
<tr>
  <td>VCC</td><td>-</td><td>VCC</td>
</tr>
<tr>
  <td>GND</td><td>-</td><td>GND</td>
</tr>
<tr>
  <td>GND</td><td>-</td><td>WP</td>
</tr>
<tr>
  <td>VCC</td><td>2k2</td><td>SDA</td>
</tr>
<tr>
  <td>VCC</td><td>2k2</td><td>SCL</td>
</tr>
</table>

<b>Summary provided by ChatGPT</b>

This code is a C++ implementation of a class called NV_Storage which provides an interface to interact with the 24LCxx series EEPROMs using the Raspberry Pi Pico board.

The code initializes the I2C communication using i2c_init() function and sets up the GPIO pins for I2C communication. It also includes the necessary headers and libraries for the code to function correctly.

The class provides several methods to read and write data to the EEPROMs. The full_read() method reads the entire EEPROM data into an internal cache, while the read() method reads the data from the cache. The write_byte() method writes a single byte to the EEPROM, and write_page() writes an entire page to the EEPROM. The write() method copies the data to be written to the cache and then writes it to the EEPROM using either the write_byte() or write_page() method, depending on the amount of data to be written.

The code also defines some constants such as the maximum size of data that can be stored in the EEPROM (NV_MAX_SIZE), the delay between write operations (NV_WRITE_DELAY), and the device address of the EEPROM (NV_DEVICE_ADDR).

Overall, the code provides a simple and efficient way to interface with the 24LCxx series EEPROMs using the Raspberry Pi Pico board.

Use Arduino IDE to build.
