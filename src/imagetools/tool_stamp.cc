/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/tool_stamp.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolStamp::ToolStamp() {
  // the Stamp is circular so the overlap might be able to be a bit smaller
  // than 0.9, but it looks best with a high overlap like 0.9.
  stamp_overlap_ = 0.9;
}

ToolStamp::~ToolStamp() {}

FloatMatrix* ToolStamp::CreateMask(float radius) {
  return MaskFactory::CreateBullseyeMask(radius, 0.2 * radius);
}

void ToolStamp::AddToStroke(int x, int y) {
  (void) x;
  (void) y;}

}  // namespace image_tools

