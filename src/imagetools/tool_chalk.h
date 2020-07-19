/**
* @file tool_chalk.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_TOOL_CHALK_H_
#define IMAGETOOLS_TOOL_CHALK_H_

#include <string>
#include "imagetools/tool.h"

namespace image_tools {

/** @brief This tool simulates chalk drawing on a rough paper. The class
 overrides Tool's default color blending function to insert random noise as
 the tool is moved around. */
class ToolChalk : public Tool {
 public:
  ToolChalk();

  virtual ~ToolChalk();

  static const std::string name() { return "Chalk"; }

  FloatMatrix *CreateMask(float radius) override;

/**
 * @brief Overrides Tool's default color blending function 
 * to insert random noise as the tool is moved around. */
  ColorData CombinePaintAndCanvasColor(const ColorData &paint_color,
                                       const ColorData &canvas_color,
                                       float mask_intensity) override;
  void set_seed(int n);

 private:
  static unsigned int seed_;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_CHALK_H_
