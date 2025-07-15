#include <stdio.h>

#include "color.h"

rgb_color build_color(uint16_t color_base) {
  uint16_t width = 255;
  double ratio = (width * 3) / 1023.0;

  uint16_t color = color_base * ratio;

  uint16_t threshold_1 = width;
  uint16_t threshold_2 = width * 2;
  uint16_t relative_color;

  if (color > threshold_2) {
    relative_color = color - threshold_2;
    uint8_t R = relative_color;
    uint8_t B = (width - relative_color);
    uint8_t G = 0;
    return (rgb_color){ R, B, G };
  } else if (color >= threshold_1) {
    relative_color = color - threshold_1;
    uint8_t R = 0;
    uint8_t B = relative_color;
    uint8_t G = (width - relative_color);
    return (rgb_color){ R, B, G };
  } else {
    relative_color = color - threshold_1;
    uint8_t R = (width - relative_color);
    uint8_t B = 0;
    uint8_t G = relative_color;
    return (rgb_color){ R, B, G };
  }
}