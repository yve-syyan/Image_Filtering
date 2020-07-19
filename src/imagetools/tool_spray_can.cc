/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/tool_spray_can.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolSprayCan::ToolSprayCan() {
  // overlap should be pretty high since the mask is so transparent
  stamp_overlap_ = 0.75;
}

ToolSprayCan::~ToolSprayCan() {}

FloatMatrix* ToolSprayCan::CreateMask(float radius) {
  FloatMatrix* mask = MaskFactory::CreateLinearFalloffMask(radius);
  mask->Scale(0.1);
  return mask;
}

}  // namespace image_tools
