/**
* @copyright 2018 3081 Staff, All rights reserved.
*/


#include "imagetools/tool_blur.h"
#include "imagetools/mask_factory.h"
#include "imagetools/color_data.h"

namespace image_tools {

ToolBlur::ToolBlur() {
  // TODO(Students) setup your blur filter to use a radius of 5.0 here

  // the blur operation is not fast, so space the repeated applications of the
  // stamp out as far as we can get away with while still having it look good
  // 1/3 overlap is pretty good for this.
  blur_filter_.set_radius(5.0);
  blur_filter_.SetUpFilter();
  stamp_overlap_ = 0.333;
}

ToolBlur::~ToolBlur() {
  blur_filter_.CleanUpFilter();
}

FloatMatrix* ToolBlur::CreateMask(float radius) {
  return MaskFactory::CreateLinearFalloffMask(radius);
}

ColorData ToolBlur::LookupPaintColor(int x, int y) {
  // Use blur filter to compute the blurred version of the pixel at (x,y)
  // in *buffer_ and return the new color to make this tool work.
  ColorData filtered_pixel_ =
  blur_filter_.CalculateFilterPixel(buffer_, x, y);
  // color for now.
  return filtered_pixel_;
}

} /* namespace image_tools */
