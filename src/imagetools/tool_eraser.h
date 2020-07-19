/**
* @file tool_eraser.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_TOOL_ERASER_H_
#define IMAGETOOLS_TOOL_ERASER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/tool.h"

namespace image_tools {

/** @brief This tool simulates an Eraser. It overrides the Tool's StartStroke
 method to change the paint_color to be the canvas's background color. */
class ToolEraser : public Tool {
 public:
  ToolEraser();
  virtual ~ToolEraser();

  static const std::string name() { return "Eraser"; }

  FloatMatrix *CreateMask(float radius) override;
/**@brief Overrides the Tool's StartStroke
 method to change the paint_color to be the canvas's background color. */
  void StartStroke(PixelBuffer *buffer, int x, int y,
                   const ColorData &paint_color, float radius) override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_ERASER_H_
