# temperature-display
An Arduino project that displays current and historic air temperature measurements.

The included sketch programs a Trinket M0 to measure the air temperature every 15 minutes using a TMP36 temperature sensor. This measurement, along with a rolling graph of the previous 24 hours of measurments, are plotted on a connected I2C OLED display. 

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

