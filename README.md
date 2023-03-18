# pico-nv-storage
project to help with using EEProm (24LCxx chips) on the RPi Pico as non-volatile storage.

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
