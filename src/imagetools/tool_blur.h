/**
* @file tool_blur.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_TOOL_BLUR_H_
#define IMAGETOOLS_TOOL_BLUR_H_

#include <stdio.h>
#include <string>
#include "imagetools/tool.h"
#include "imagetools/filter_blur.h"
#include "imagetools/filter.h"
#include "imagetools/color_data.h"

namespace image_tools {

/** @brief This tool serves as a mobile version of the blur filter, functions
  much like the spray can, except with blurring neighboring pixels rather than
  coloring them (linear falloff). */
class ToolBlur : public Tool {
 public:
  ToolBlur();
  virtual ~ToolBlur();
  FloatMatrix* CreateMask(float radius) override;

  static const std::string name() { return "Blur"; }
  /**
   * @brief Calculate blurred pixel using kernel created by
   * Gaussian distribution, new color is computed based on colordata
   * from nearby pixels.*/
  ColorData LookupPaintColor(int x, int y) override;

 private:
  ToolBlur(const ToolBlur& rhs) = delete;
  ToolBlur& operator=(const ToolBlur& rhs) = delete;
  FilterBlur blur_filter_;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_BLUR_H_
