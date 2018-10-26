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
#define LEDS_W 8
#define LEDS_H 8
#define NUM_LEDS LEDS_W * LEDS_H

// LEDs brightness
#define BRIGHTNESS 15

// Leds data pin
#define DATA_PIN 6

// Interrumption pin for the pulsor 
#define INTERRUPT_PIN 2 // 3 also abailable

// LEDs object
CRGB leds[NUM_LEDS];

// ==== Frames ====================================================

// A simple frame storing single pixel color values in hex mode (8x8 for example)
const long Frame0[] PROGMEM = 
{
  // Row 0
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
   // Row 1
   0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
    // Row 2
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
    // Row 3
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
    // Row 4
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
    // Row 5
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
    // Row 6
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc,
    // Row 7
  0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc, 0xcccccc
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

// ----------------------------------------------------------------------------

void setup() 
{
  // Init the LEDs
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // Setting the LEDs brightness
  FastLED.setBrightness(BRIGHTNESS);

}

void loop() 
{
  // Display a single frame
  DisplayFrame(Frame0);

  // Small delay between frames updates
  delay(500);
}
