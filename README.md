# SoccerLamp
An IKEA lamp that blinks soccer scores powered by esp8266 and Neopixel Ring

## Hardware
- [TVÄRS IKEA Lamp](http://www.ikea.com/at/de/catalog/products/20356136)
- esp8266 development board (e.g. [NodeMCU V2](https://www.amazon.de/gp/product/B06Y1LZLLY))
- [Neopixel Ring](https://www.amazon.de/gp/product/B00KI2RLOI)
- 1000µF capacitor (to protect your LEDs)
- 330 ohm resistor (to protect your LEDs)
- 3.3V -> 5V level shifter (may not be necessary for short LED strips)

## Software
- [Silicon Labs VCP Driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) (for CP210x based LED strips)
- [football-data.org](https://api.football-data.org) free API key

## Arduino libraries
- [esp8266 core for Arduino](https://github.com/esp8266/Arduino)
- [FastLED](http://fastled.io)
- [ArduinoJSON](http://arduinojson.org)
