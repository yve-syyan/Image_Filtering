/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_detectedges.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  FilterDetectEdges::FilterDetectEdges() {
    radius = 1.0;
}

  FilterDetectEdges::~FilterDetectEdges() {}

  FloatMatrix* FilterDetectEdges::CreateKernel() {
  FloatMatrix* new_kernel_ = new FloatMatrix(1);
  // set up a kernel with center value 8.0 and rest of cells as -1
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      new_kernel_ -> set_value(x, y, -1.0);}
    }
  new_kernel_ -> set_value(1, 1, 8.0);
  return new_kernel_;
  }
} /* namespace image_tools */
