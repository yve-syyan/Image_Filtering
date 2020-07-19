/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/tool_calligraphy_pen.h"
#include "imagetools/mask_factory.h"

namespace image_tools {

ToolCalligraphyPen::ToolCalligraphyPen() {
  // since the mask shape is narrow, the overlap needs to be fairly large
  // in order to get a nice continuous stroke.
  stamp_overlap_ = 0.9;
}

ToolCalligraphyPen::~ToolCalligraphyPen() {}

FloatMatrix* ToolCalligraphyPen::CreateMask(float radius) {
  return MaskFactory::CreateOvalMask(radius, 70.0, 0.333);
}

}  // namespace image_tools
