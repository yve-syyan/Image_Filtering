/**
* @copyright 2018 3081 Staff, All rights reserved.
*/


#include "imagetools/tool_eraser.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolEraser::ToolEraser() { stamp_overlap_ = 0.9; }

ToolEraser::~ToolEraser() {}

FloatMatrix *ToolEraser::CreateMask(float radius) {
  return MaskFactory::CreateConstantMask(radius);
}

void ToolEraser::StartStroke(PixelBuffer *buffer, int x, int y,
                             const ColorData &paint_color, float radius) {
  (void)paint_color;
  // The eraser is a special case -- the buffer's background color is used as
  // the paint color for the tool.
  Tool::StartStroke(buffer, x, y, buffer->background_color(), radius);
}

} /* namespace image_tools */
