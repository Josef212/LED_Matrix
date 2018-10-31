#include <FastLED.h>
#include <avr/pgmspace.h>

#define LED_PIN 7
#define NUM_LEDS 16
#define BRIGHT_PIN A0
#define DYNAMIC_PIN 2

#define TIME_BETWEEN_FRAMES 500

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
  0xFF0000, 0x12FF00, 0xFF6600, 0x00FCFF, 
  0x2C7E2A, 0xFFFFFF, 0x00FF9C, 0x4D2A00,
  0xFF0000, 0xFF00A2, 0x0600FF, 0xD8FF00, 
  0xFF004E, 0x000000, 0xFFF600, 0x0C00F9
};

const long Frame2[] PROGMEM = 
{ 
  0x2C7E2A, 0xFFFFFF, 0x00FF9C, 0x4D2A00,
  0xFF0000, 0xFF00A2, 0x0600FF, 0xD8FF00,
  0xFF6600, 0x12FF00, 0xFF6600, 0x00FCFF, 
  0xFF004E, 0x000000, 0xFFF600, 0x0C00F9
};

const long Frame3[] PROGMEM = 
{ 
  0x2C7E2A, 0x000000, 0xFFF600, 0x0C00F9,
  0xFF0000, 0xFF00A2, 0x0600FF, 0xD8FF00,
  0x2C7E2A, 0xFFFFFF, 0x00FF9C, 0x4D2A00,
  0xFF6600, 0x12FF00, 0xFF6600, 0x00FCFF 
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

void Display2FramesAnimation(const long* frame0, const long* frame1, int delayBetweenFrames = TIME_BETWEEN_FRAMES, bool checkLoop = true)
{
  do
  {
    DisplayFrame(frame0, delayBetweenFrames);
    DisplayFrame(frame1, delayBetweenFrames);
  }while(checkLoop && !digitalRead(DYNAMIC_PIN));
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

  //DisplayFrame(&Frame0[0], 500);
  //DisplayFrame(&Frame1[0], 500);

  Display2FramesAnimation(&Frame0[0], &Frame1[0]);

  Display2FramesAnimation(&Frame2[0], &Frame3[0]);


}
