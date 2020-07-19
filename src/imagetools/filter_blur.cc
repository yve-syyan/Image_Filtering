/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_blur.h"
#include <cmath>
#include "imagetools/float_matrix.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

  FilterBlur::FilterBlur(float r) {
  radius = r;}

  FilterBlur::FilterBlur() {}

  FilterBlur::~FilterBlur() {}

  void FilterBlur::set_radius(float r) {
    radius = r;
  }
  FloatMatrix* FilterBlur::CreateKernel() {
  int r = static_cast<int>(radius);
  FloatMatrix* new_kernel_ = new FloatMatrix(r);
  ImageToolsMath* math_tool_;
  float width = 2.0 * radius +1;
  float height = 2.0 * radius + 1;
  for (float matrixY = 0; matrixY < height; matrixY ++) {
  for (float matrixX = 0; matrixX < width; matrixX ++) {
    float distance =
      sqrt((matrixX-radius) * (matrixX-radius) +
      (matrixY-radius) * (matrixY-radius));
  // compute elements within the matrix using distance away from center
  // as x and radius of kernel as sigma
    float element = math_tool_ -> Gaussian(distance, radius);
    int x = static_cast<int> (matrixX);
    int y = static_cast<int> (matrixY);
    new_kernel_-> set_value(x, y, element);}
  }
  new_kernel_ -> Normalize();
  return new_kernel_;}
} /* namespace image_tools */
