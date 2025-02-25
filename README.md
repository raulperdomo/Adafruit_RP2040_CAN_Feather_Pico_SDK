Adafruit RP2040 CAN Feather Pico SDK Template  
---------------------------------------------------------
This is a template project for Adafruit RP2040 CAN Feather board. It is using the optimized [pico-mcp2515](https://github.com/adamczykpiotr/pico-mcp2515) for the CAN communication. I updated the library headers to work with the [Adafruit devboard](https://www.adafruit.com/product/5724) (spi1) instead of the Seeed Studio devboard. 

I also included the [pico_neopixels](https://github.com/martinkooij/pi-pico-adafruit-neopixels) library to control the onboard neopixel.

In the current configuration, the CAN bus is set to 500kbps. The neopixel is controlled by the second core of the RP2040 and rotates through a series of colors and a rainbow pattern.
