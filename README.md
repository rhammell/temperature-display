# temperature-display
An Arduino project that displays current and historic air temperature measurements.

The `temperature_display.ino` Arduino sketch programs a Trinket M0 to capture air temperature measurements every 15 minutes using a TMP36 sensor. The latest measurements, along with a graph of the previous 24 hours of measurements, are shown on an I2C OLED display. 

## Components
- [Adafruit Trinket M0](https://www.adafruit.com/product/3500)
- [TMP36 analog temperature sensor](https://www.adafruit.com/product/165)
- [Monochrome 128x32 I2C OLED display](https://www.adafruit.com/product/4440)

## Circuit  
<img src="/circuit.png" width="600">

* TMP36 VIN to Trinket M0 3V
* TMP36 VOUT to Trinket M0 pin 4 (A4)
* TMP36 GND to Trinket M0 GND
* OLED SDA to Trinket M0 pin 0 (SDA) 
* OLED SLC to Trinket M0 pin 2 (SLC) 
* OLED VIN to Trinket M0 3V
* OLED GND to Trinket M0 GND

