/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_saturation.h"
#include <algorithm>
#include <cmath>
#include "imagetools/image_tools_math.h"

namespace image_tools {
  FilterSaturation::FilterSaturation(float scale) {
  scale_ = scale;}

  FilterSaturation::FilterSaturation() {}
  FilterSaturation::~FilterSaturation() {}

  ColorData FilterSaturation::CalculateFilterPixel
  (PixelBuffer* buffer, int x, int y) {
  ImageToolsMath* math_;
  ColorData current_color_ = buffer -> pixel(x, y);
  float red_ = current_color_.red();
  float green_ = current_color_.green();
  float blue_ = current_color_.blue();
  float luminance_ = current_color_.Luminance();

  // linearly interpolate between grayscale of color and the color
  float new_red_ = math_ -> Lerp<float>(luminance_, red_, scale_);
  float new_green_ = math_ -> Lerp<float>(luminance_, green_, scale_);
  float new_blue_ = math_ -> Lerp<float>(luminance_, blue_, scale_);
  ColorData new_color_(new_red_, new_green_, new_blue_);
  return new_color_;
  }
} /* namespace image_tools */
