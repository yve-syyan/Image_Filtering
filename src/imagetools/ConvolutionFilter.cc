/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/ConvolutionFilter.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/float_matrix.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
  ConvolutionFilter::ConvolutionFilter() {
    kernel = NULL;
}

  ConvolutionFilter::~ConvolutionFilter() {}

  void ConvolutionFilter::SetUpFilter() {
  kernel = CreateKernel();
}

  ColorData ConvolutionFilter::CalculateFilterPixel
  (PixelBuffer* image_, int x, int y) {
  ImageToolsMath* m_tool_;
  ColorData blur_color_ = image_ -> pixel(x, y);
  int b_width_ = image_ -> width();
  int b_height_ = image_ -> height();
  int width_ = kernel -> width();
  int height_ = kernel -> height();
  int radius_ = (width_-1)/2;
  float red_sum_ = 0.0;
  float green_sum_ = 0.0;
  float blue_sum_ = 0.0;
  int image_x_, image_y_;
  float current_red_, current_blue_, current_green_;
  // multiply color data within image buffer with corresponding values in kernel
  for (int matrix_y_ = 0; matrix_y_ < height_; matrix_y_++) {
    for (int matrix_x_ = 0; matrix_x_ < width_; matrix_x_++) {
      image_y_ = y - radius_  + matrix_y_;
      image_x_ = x - radius_ + matrix_x_;

    if ( ( image_x_ >= 0 && image_x_< b_width_) &&
    (image_y_ >= 0 && image_y_ < b_height_)) {
        ColorData current_color = image_ -> pixel(image_x_, image_y_);
        current_red_ = current_color.red();
        current_blue_ = current_color.blue();
        current_green_ = current_color.green();
        red_sum_ = red_sum_ +
            current_red_ * (kernel -> value(matrix_x_ , matrix_y_));
        green_sum_ = green_sum_ +
            current_green_ * (kernel -> value(matrix_x_ , matrix_y_));
        blue_sum_ = blue_sum_ +
            current_blue_ * (kernel -> value(matrix_x_ , matrix_y_));
    } else {
        // if pixel goes out of bound, opt for color data at image's edges
        image_y_ = m_tool_ -> Clamp(image_y_, 0, b_height_-1);
        image_x_ = m_tool_ -> Clamp(image_x_, 0, b_width_-1);
        ColorData current_color = image_ -> pixel(image_x_, image_y_);
        current_red_ = current_color.red();
        current_blue_ = current_color.blue();
        current_green_ = current_color.green();
        // sum multiplied results for each color green, red and blue
        red_sum_ = red_sum_ +
            current_red_ * (kernel -> value(matrix_x_ , matrix_y_));
        green_sum_ = green_sum_ +
            current_green_ * (kernel -> value(matrix_x_ , matrix_y_));
        blue_sum_ = blue_sum_ +
            current_blue_ * (kernel -> value(matrix_x_ , matrix_y_));
      }
  }
}
  // reset color data for pixel at (x, y)
  blur_color_.set_red(red_sum_);
  blur_color_.set_blue(blue_sum_);
  blur_color_.set_green(green_sum_);
  return blur_color_;}

  void ConvolutionFilter::CleanUpFilter() {
    delete kernel;
    }
} /* namespace image_tools */
