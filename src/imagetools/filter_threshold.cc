/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_threshold.h"

namespace image_tools {
  FilterThreshold::FilterThreshold(float cutoff_) {
  thresh_cutoff_ = cutoff_;}

  FilterThreshold::~FilterThreshold() {}
  FilterThreshold::FilterThreshold() {}

  ColorData FilterThreshold::CalculateFilterPixel
  (PixelBuffer* buffer, int x, int y) {
  ColorData current_color_ = buffer -> pixel(x, y);
  float red_ = current_color_.red();
  float green_ = current_color_.green();
  float blue_ = current_color_.blue();
  float average = (red_ + green_ + blue_)/3;
  // set color values to white if larger than the threshold
  if (average > thresh_cutoff_) {
    current_color_.set_red(1.0);
    current_color_.set_green(1.0);
    current_color_.set_blue(1.0);
  } else {
  // set color values to black if smaller than or equal to the threshold
    current_color_.set_red(0.0);
    current_color_.set_green(0.0);
    current_color_.set_blue(0.0);}
  return current_color_;}
} /* namespace image_tools */
