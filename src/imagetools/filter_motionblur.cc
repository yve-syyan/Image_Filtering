/**
* @copyright 2018 3081 Staff, All rights reserved.
*/
#include "imagetools/filter_motionblur.h"
#include <cmath>
#include <cstring>
#include "imagetools/float_matrix.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
  FilterMotionblur::FilterMotionblur(float r, MBlurDir d) {
  radius = r;
  direction = MotionBlurDirectionName(d);}

  FilterMotionblur::FilterMotionblur() {}
  FilterMotionblur::~FilterMotionblur() {}

const std::map<FilterMotionblur::MBlurDir, std::string>
  FilterMotionblur::mblur_dir_names_ = {
    {MBLUR_DIR_N_S,   "North/South"},
    {MBLUR_DIR_E_W,   "East/West"},
    {MBLUR_DIR_NE_SW, "Northeast/Southwest"},
    {MBLUR_DIR_NW_SE, "Northwest/Southeast"}
};

std::string FilterMotionblur::MotionBlurDirectionName
  (MBlurDir dir) {
    return mblur_dir_names_.find(dir)->second;
  }

  FloatMatrix* FilterMotionblur::CreateKernel() {
  int int_radius_ = static_cast<int> (radius);
  FloatMatrix* new_kernel_ = new FloatMatrix(int_radius_);
  float width = 2.0 * radius + 1;
  float height = 2.0 * radius + 1;
  float element = 1 / radius;
  for (float matrixY = 0; matrixY < width; matrixY ++) {
    for (float matrixX = 0; matrixX < height; matrixX++) {
      int x = static_cast<int>(matrixX);
      int y = static_cast<int>(matrixY);
      int center = static_cast<int>(radius+1);
      int edge_length_ = static_cast<int>(width);

    // design the kernel based on directions
    if (direction == "North/South") {
      if (x == center) {
          new_kernel_-> set_value(x, y, element);
       } else {new_kernel_-> set_value(x, y, 0.0);}}
    if (direction == "East/West") {
      if (y == center) {
          new_kernel_-> set_value(x, y, element);
      } else {new_kernel_-> set_value(x, y, 0.0);}}
    if (direction == "Northeast/Southwest") {
      if (x + y == edge_length_) {
      new_kernel_-> set_value(x, y, element);
      } else {new_kernel_-> set_value(x, y, 0.0);}}
    if (direction == "Northwest/Southeast") {
      if (x == y) {
          new_kernel_-> set_value(x, y, element);
      } else {new_kernel_-> set_value(x, y, 0.0);} }
  }}
  new_kernel_ -> Scale(1.0/new_kernel_ -> Sum());
  return new_kernel_;}
} /* namespace image_tools */
