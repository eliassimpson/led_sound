
#include <Adafruit_NeoPixel.h>

#include "color.h"

#define PIN_NEO_PIXEL 13  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 144    // The number of LEDs (pixels) on NeoPixel

#define SOUND_IN 5
#define THRESHOLD_IN 4
#define COLOR_IN 3

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  NeoPixel.begin();
}

void loop() {
  color(0, 8);
}

void color(int iteration, int iteration_max) {
  int sound_in = analogRead(SOUND_IN);
  int threshold = analogRead(THRESHOLD_IN) / 4;
  uint16_t color_in = analogRead(COLOR_IN);
  
  Serial.println(threshold);
  if (sound_in > threshold) {
    iteration = (iteration + 1) % (iteration_max * 2);
    delay(200);
  }
  rgb_color rgb_in = build_color(color_in);
  for (int i = 0; i < NUM_PIXELS; i++) {
    if (iteration < iteration_max) {
      NeoPixel.setPixelColor(i, NeoPixel.Color(increase_color(iteration, rgb_in.red), increase_color(iteration, rgb_in.green), increase_color(iteration, rgb_in.blue), 0));
    } else {
      NeoPixel.setPixelColor(i, NeoPixel.Color(reduce_color(iteration_max, iteration, rgb_in.red), reduce_color(iteration_max, iteration, rgb_in.green), reduce_color(iteration_max, iteration, rgb_in.blue), 0));
    }
  }
  NeoPixel.show();

  color(iteration, iteration_max);
}

uint8_t increase_color(uint8_t iteration, uint8_t color) {
  return iteration * color / 18;
}

uint8_t reduce_color(uint8_t iteration_max, uint8_t iteration, uint8_t color) {
  return (iteration_max * color - (iteration - iteration_max) * color) / 18;
}
