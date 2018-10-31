#include <FastLED.h>
#include <avr/pgmspace.h>

#define LED_PIN 7
#define NUM_LEDS 16
#define BRIGHT_PIN A0
#define DYNAMIC_PIN 2

// ===================================================

CRGB leds[NUM_LEDS];

// ===================================================

const long Frame0[] PROGMEM = 
{
  0xFF0000, 0xFF00A2, 0x0600FF, 0xD8FF00, 
  0xFF6600, 0x12FF00, 0xFF6600, 0x00FCFF, 
  0xFF004E, 0x000000, 0xFFF600, 0x0C00F9, 
  0x2C7E2A, 0xFFFFFF, 0x00FF9C, 0x4D2A00
};

const long Frame1[] PROGMEM = 
{
  0xFF6600, 0x12FF00, 0xFF6600, 0x00FCFF, 
  0x2C7E2A, 0xFFFFFF, 0x00FF9C, 0x4D2A00,
  0xFF0000, 0xFF00A2, 0x0600FF, 0xD8FF00, 
  0xFF004E, 0x000000, 0xFFF600, 0x0C00F9
};

// ===================================================

void GetBrightness()
{
  FastLED.setBrightness(analogRead(BRIGHT_PIN) / 4);
}

void DisplayFrame(const long* frame, int delayTime = 0, bool checkLoop = false)
{
  GetBrightness();
  do
  {
    for(int i = 0; i < NUM_LEDS; ++i)
    {      
      leds[i] = pgm_read_dword(&(frame[i]));
    }
  
    FastLED.show();
  
    if(delayTime > 0) FastLED.delay(delayTime);
  
  }while(checkLoop && !digitalRead(DYNAMIC_PIN));
}

void Test()
{
  GetBrightness();

  FastLED.clear();

  leds[0] = CRGB(255, 0, 0);
  leds[1] = CRGB(0, 255, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(255, 255, 0);
  leds[4] = CRGB(0, 255, 255);
  leds[5] = CRGB(255, 0, 255);
  leds[6] = CRGB(255, 255, 255);
  leds[7] = CRGB(128, 0, 200);
  
  leds[8] = CRGB(255, 0, 0);
  leds[9] = CRGB(255, 0, 0);
  leds[10] = CRGB(255, 0, 0);
  leds[11] = CRGB(255, 0, 0);
  leds[12] = CRGB(255, 0, 0);
  leds[13] = CRGB(255, 0, 0);
  leds[14] = CRGB(255, 0, 0);
  leds[15] = CRGB(255, 0, 0);
  
  FastLED.show();

  FastLED.delay(1000);
}

// ===================================================


void setup() 
{
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  pinMode(DYNAMIC_PIN, INPUT);
  pinMode(BRIGHT_PIN, INPUT);
  GetBrightness();
}

void loop() {
  // put your main code here, to run repeatedly:

  //Test();
  DisplayFrame(&Frame0[0], 500);
  DisplayFrame(&Frame1[0], 500);

}
