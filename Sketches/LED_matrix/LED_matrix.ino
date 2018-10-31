/*
  Author: Josef21296

  Sketch to control a LED matrix with an arduino to display diferent images and simple animations.
  Using FastLED library to control the WS2812 LED Strips.

*/

// Library to use Flash memory in order to store more images
#include <avr/pgmspace.h>
// FastLED library include 
#include <FastLED.h>

// Number of leds
#define LEDS_W 16
#define LEDS_H 16
#define NUM_LEDS LEDS_W * LEDS_H

// LEDs brightness
#define DEFAULT_BRIGHTNESS 15
#define MIN_BRIGHTNESS 5

// Leds data pin
#define DATA_PIN 6

#define BRIGHT_PIN A1

#define DYNAMIC_PIN 2

// LEDs object
CRGB leds[NUM_LEDS];

// ==== Frames ====================================================

// A simple frame storing single pixel color values in hex mode (8x8 for example)
const long test[] PROGMEM = 
{
  0xff0000, 0xff9000, 0xff9000, 0x9600ff, 0xffffff, 0xf0ff00, 0x004eff, 0xf0ff00, 
  0xf0ff00, 0xf0ff00, 0xff0090, 0x9600ff, 0x9600ff, 0x1eff00, 0x1eff00, 0x004eff, 
  0xff0000, 0x004eff, 0x1eff00, 0x004eff, 0x9600ff, 0xff0090, 0x004eff, 0x004eff, 
  0x004eff, 0xf0ff00, 0xff0090, 0x000000, 0x004eff, 0xffffff, 0xff0000, 0xff9000, 
  0x00ffc0, 0xff9000, 0xff0000, 0xffffff, 0x000000, 0x000000, 0xffffff, 0x00ffc0, 
  0x00ffc0, 0x1eff00, 0x1eff00, 0x1eff00, 0x004eff, 0xff0000, 0x00ffc0, 0x00ffc0, 
  0xf0ff00, 0x00ffc0, 0x9600ff, 0x9600ff, 0x9600ff, 0xff9000, 0xff9000, 0x00ffc0, 
  0xff0000, 0xff0000, 0xff9000, 0xffffff, 0x000000, 0x000000, 0x004eff, 0x004eff
};

const long test1[] PROGMEM = 
{
  0xf0ff00, 0xf0ff00, 0xff0090, 0x9600ff, 0x9600ff, 0x1eff00, 0x1eff00, 0x004eff, 
  0x00ffc0, 0x1eff00, 0x1eff00, 0x1eff00, 0x004eff, 0xff0000, 0x00ffc0, 0x00ffc0, 
  0xff0000, 0x004eff, 0x1eff00, 0x004eff, 0x9600ff, 0xff0090, 0x004eff, 0x004eff, 
  0xf0ff00, 0x00ffc0, 0x9600ff, 0x9600ff, 0x9600ff, 0xff9000, 0xff9000, 0x00ffc0, 
  0xff0000, 0xff9000, 0xff9000, 0x9600ff, 0xffffff, 0xf0ff00, 0x004eff, 0xf0ff00, 
  0x004eff, 0xf0ff00, 0xff0090, 0x000000, 0x004eff, 0xffffff, 0xff0000, 0xff9000, 
  0x00ffc0, 0xff9000, 0xff0000, 0xffffff, 0x000000, 0x000000, 0xffffff, 0x00ffc0, 
  0xff0000, 0xff0000, 0xff9000, 0xffffff, 0x000000, 0x000000, 0x004eff, 0x004eff
};

// ================================================================

void Brightness()
{
  // Getting the brightness from the potentiometer, mapping the value and clamping it before setting it.
  FastLED.setBrightness(constrain(analogRead(BRIGHT_PIN) / 4, MIN_BRIGHTNESS, 255));
}

// Function to display a single frame
void DisplayFrame(const long* frame, int delayTime = 0, bool checkLoop = false)
{
  do
  {
    Brightness();
  
    // Looping throw a frame to  display it
    for(int i = 0; i < NUM_LEDS; ++i)
    {
      leds[i] = pgm_read_dword(&(frame[i]));
    }

    // Actually display the led info when setted
    FastLED.show();

    if(delayTime > 0) FastLED.delay(delayTime);
    
  }while(checkLoop && !digitalRead(INTERRUPT_PIN));
}

void Display2FramesAnimation(const long* frame0, const long* frame1, int delayBetweenFrames = TIME_BETWEEN_FRAMES, bool checkLoop = true)
{
  do
  {
    DisplayFrame(frame0, delayBetweenFrames);
    DisplayFrame(frame1, delayBetweenFrames);
  }while(checkLoop && !digitalRead(DYNAMIC_PIN));
}

// ----------------------------------------------------------------------------

void setup() 
{
  // Init the LEDs
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  pinMode(DYNAMIC_PIN, INPUT);
  pinMode(BRIGHT_PIN, INPUT);
  
  // Setting the LEDs brightness
  Brightness();
}

void loop() 
{
  // Display a single frame
  DisplayFrame(&test[0], 500, true);
  DisplayFrame(&test1[0], 500, true);
}
