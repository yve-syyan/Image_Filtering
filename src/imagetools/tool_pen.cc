/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/tool_pen.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolPen::ToolPen() {
  // the pen is circular so the overlap might be able to be a bit smaller
  // than 0.9, but it looks best with a high overlap like 0.9.
  stamp_overlap_ = 0.9;
}

ToolPen::~ToolPen() {}

FloatMatrix* ToolPen::CreateMask(float radius) {
  return MaskFactory::CreateConstantMask(radius);
}

}  // namespace image_tools
