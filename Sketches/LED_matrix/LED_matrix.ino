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
#define LEDS_W 4
#define LEDS_H 4
#define NUM_LEDS LEDS_W * LEDS_H

// LEDs brightness
#define BRIGHTNESS 15

// Leds data pin
#define DATA_PIN 6

// Interrumption pin for the pulsor 
#define INTERRUPT_PIN 2 // 3 also abailable

#define BRIGHT_PIN A1

// LEDs object
CRGB leds[NUM_LEDS];

// Loop throw different images/aniamtions or only reproduce one
volatile boolean dynamic = true;

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

const long t[2][256] PROGMEM = 
{
  test, test1
};

// ================================================================

// Function to display a single frame
void DisplayFrame(const long* frame)
{
    // Clearing all leds
  FastLED.clear();
  
  // Looping throw a frame to  display it
  for(int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = pgm_read_word(&(frame[i]));
  }

  // Actually display the led info when setted
  FastLED.show();
}

void DisplayAnimation(const long** anim, int frames, int delayBetweenFrames)
{
  for(int i = 0; i < frames; ++i)
  {
    DisplayFrame(anim[i]);
    FastLED.delay(delayBetweenFrames);
  }
}

void ButtonDown()
{
  // Change the dynamic state according to the toggle button state.
  dynamic = digitalRead(INTERRUPT_PIN);
}

void Brightness()
{
  // Read the analog potentiometer value, map it to brightness range and set the leds brightness.
  // TODO: May be define a min and max brightness and clamp the value
  int brightness = analogRead(BRIGHT_PIN) / 4;
  //int mapped = map(a, 0, 1023, 0, 255);

  // Constrain/Clamp the value
  //mapped = constrain(mapped, MIN, MAX);

  FastLED.setBrightness(brightness);
}

// ----------------------------------------------------------------------------

void setup() 
{
  // Init the LEDs
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // Setting the LEDs brightness
  Brightness();

  // Setting the interrupt pin
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), ButtonDown, CHANGE);

  // Init the dynamic boolean according to the initial toggle buttton state
  dynamic = digitalRead(INTERRUPT_PIN);

  Serial.begin(9600);
}

void loop() 
{
  // Display a single frame
  DisplayFrame(test);

  // Small delay between frames updates
  FastLED.delay(500);

  // Check and set the brightness.
  Brightness();
}
