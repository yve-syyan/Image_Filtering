/** 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
Filter::Filter() {}
Filter::~Filter() {}
void Filter::ApplyToBuffer(PixelBuffer* image_) {
  int width_ = image_->width();
  int height_ = image_ -> height();
  PixelBuffer* copied_image_;

  // copy buffer if color data cannot be calculated in place
  if (!can_calculate_in_place()) {
    copied_image_ = new PixelBuffer(*image_);
  } else {copied_image_ = image_;}
  SetUpFilter();

  // compute color data for each pixel within the buffer
  for (int imageX = 0; imageX < width_; imageX++) {
    for (int imageY = 0; imageY < height_; imageY++) {
      ColorData new_color_;
      new_color_ =
        CalculateFilterPixel(copied_image_, imageX, imageY);
      image_ -> set_pixel(imageX, imageY, new_color_);
    }
  }
  CleanUpFilter();
}
void Filter::SetUpFilter() {}
void Filter::CleanUpFilter() {}
} /* namespace image_tools */
