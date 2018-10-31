#include <FastLED.h>

#define LED_PIN 7

CRGB leds[1];

int r = 0, g = 255 / 2, b = 255, bright = 5;


void setup() 
{
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, 1);
}

void loop() 
{
  leds[0] = CRGB(r, g, b);
  FastLED.setBrightness(bright);

  FastLED.show();

  r += 3;
  g += 9;
  b += 7;
  bright += 5;

  r = r % 255;
  g = g % 255;
  b = b % 255;
  bright = (bright >= 255 ? 5 : bright);

  FastLED.delay(500);
}
