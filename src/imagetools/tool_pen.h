/**
* @file tool_pen.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_TOOL_PEN_H_
#define IMAGETOOLS_TOOL_PEN_H_

#include <string>
#include "imagetools/tool.h"

namespace image_tools {

/** @brief The simplest of tools, this has a mask that is a completely opaque
 circle. */
class ToolPen : public Tool {
 public:
  ToolPen();
  virtual ~ToolPen();

  static const std::string name() { return "Pen"; }

  FloatMatrix* CreateMask(float radius) override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_PEN_H_
