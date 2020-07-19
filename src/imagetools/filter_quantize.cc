/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_quantize.h"
#include <cmath>

namespace image_tools {
  FilterQuantize::FilterQuantize(int n) {
  num_ = n;}

  FilterQuantize::FilterQuantize() {
  num_ = 1;}

  FilterQuantize::~FilterQuantize() {}

  ColorData FilterQuantize::CalculateFilterPixel
  (PixelBuffer* buffer, int x, int y) {
  ColorData current_color_ = buffer -> pixel(x, y);
  float red_ = current_color_.red();
  float green_ = current_color_.green();
  float blue_ = current_color_.blue();
  int num_steps_ = 1;
  if (num_ != 1) {
    num_steps_ = num_ - 1;}

  // Bins colors based on number of bins, num_steps_ = 1 if apply one
  // bin.
  current_color_.set_red(round(red_*num_steps_)/num_steps_);
  current_color_.set_blue(round(blue_*num_steps_)/num_steps_);
  current_color_.set_green(round(green_*num_steps_)/num_steps_);
  return current_color_;
  }
} /* namespace image_tools */
