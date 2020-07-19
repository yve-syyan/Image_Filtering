/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_sharpen.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  FilterSharpen::FilterSharpen(float r) {
  radius = r; }

  FilterSharpen::~FilterSharpen() {}

  FilterSharpen::FilterSharpen() {}

  FloatMatrix* FilterSharpen::CreateKernel() {
  int int_r_ = static_cast<int> (radius);
  FloatMatrix* new_kernel_ = new FloatMatrix(int_r_);
  float width = 2.0 * radius + 1;
  float height = 2.0 * radius + 1;
  int x , y;
  int center = static_cast<int>(radius);
  for (float matrixY = 0; matrixY < width; matrixY ++) {
    for (float matrixX = 0; matrixX< height; matrixX ++) {
        x = static_cast<int>(matrixX);
        y = static_cast<int>(matrixY);
        if ((x == center) && (x == y)) {
          new_kernel_-> set_value(x, y, width*height);
        } else {
          new_kernel_-> set_value(x, y, -1.0);}
     }
  }
  new_kernel_ -> Normalize();
  return new_kernel_;}
} /* namespace image_tools */
