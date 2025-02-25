#include "pico/stdlib.h"
#include "utils/NeoPixel_utils.h"




// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
static uint32_t Wheel(Adafruit_NeoPixel &onboard, uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return onboard.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return onboard.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return onboard.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void colorWipe(Adafruit_NeoPixel &onboard, uint32_t c, uint32_t wait) {
  for(uint16_t i=0; i<onboard.numPixels(); i++) {
    onboard.setPixelColor(i, c);
    onboard.show();
    sleep_ms(wait);
  }
}

void rainbow(Adafruit_NeoPixel &onboard, uint32_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<onboard.numPixels(); i++) {
      onboard.setPixelColor(i, Wheel(onboard, (uint8_t)((i+j) & 255)));
    }
    onboard.show();
    sleep_ms(wait);
  }
}

