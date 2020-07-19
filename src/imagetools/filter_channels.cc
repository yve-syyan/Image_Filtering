/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_channels.h"
#include <algorithm>
#include <cmath>
#include "imagetools/image_tools_math.h"

namespace image_tools {

  FilterChannel::FilterChannel(float r, float g, float b) {
    red_scale_ = r;
    green_scale_ = g;
    blue_scale_ = b;}

  FilterChannel::FilterChannel() {}
  FilterChannel::~FilterChannel() {}

  ColorData FilterChannel::CalculateFilterPixel
  (PixelBuffer* buffer, int x, int y) {
    ColorData current_color_ = buffer -> pixel(x, y);
    float red_ = current_color_.red();
    float green_ = current_color_.green();
    float blue_ = current_color_.blue();
    // scale vibrance of each color based on its scaling factor
    float new_red_ = red_ * red_scale_;
    float new_green_ = green_ * green_scale_;
    float new_blue_ = blue_ * blue_scale_;
    ColorData new_color_(new_red_, new_green_, new_blue_);
    return new_color_;
    return new_color_;}
} /* namespace image_tools */
