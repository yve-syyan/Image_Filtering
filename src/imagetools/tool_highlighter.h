/**
* @file tool_highlighter.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/


#ifndef IMAGETOOLS_TOOL_HIGHLIGHTER_H_
#define IMAGETOOLS_TOOL_HIGHLIGHTER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/tool.h"

namespace image_tools {

/** @brief This tool simulates a Highlighter.  It has a semi-transparent oval
 mask.  It overrides the default Tool's color blend function to make the
 blending
 dependent upon the luminance of the underlying canvas color. */
class ToolHighlighter : public Tool {
 public:
  ToolHighlighter();
  virtual ~ToolHighlighter();

  static const std::string name() { return "Highlighter"; }

  FloatMatrix *CreateMask(float radius) override;

  /** @brief Overrides the super's function to include the luminance of the
   canvas_color in the calculation of the tool's intensity. */
  ColorData CombinePaintAndCanvasColor(const ColorData &paint_color,
                                       const ColorData &canvas_color,
                                       float mask_intensity) override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_HIGHLIGHTER_H_
