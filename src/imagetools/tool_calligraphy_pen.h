/**
* @file tool_calligraphy_pen.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_TOOL_CALLIGRAPHY_PEN_H_
#define IMAGETOOLS_TOOL_CALLIGRAPHY_PEN_H_

#include <cmath>
#include <string>
#include "imagetools/float_matrix.h"
#include "imagetools/tool.h"

namespace image_tools {

/** @brief This tool simulates a Calligraphy Pen, meaning it paints with a
 different thickness depending on which direction it is moved. */
class ToolCalligraphyPen : public Tool {
 public:
  ToolCalligraphyPen();
  virtual ~ToolCalligraphyPen();

  static const std::string name() { return "Caligraphy Pen"; }

/**@brief  It has a oval mask tilted at an angle of 70 degrees 
 * counter-clockwise from the x-axis and an
 elongation ratio of 0.333. */

  FloatMatrix* CreateMask(float radius) override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_CALLIGRAPHY_PEN_H_
