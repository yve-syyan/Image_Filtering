/**
* @file tool_spray_can.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_TOOL_SPRAY_CAN_H_
#define IMAGETOOLS_TOOL_SPRAY_CAN_H_

/**********************************************************************
 * Includes
 *********************************************************************/

#include <string>
#include "imagetools/tool.h"

namespace image_tools {

/** 
 * @brief This tool has a linear falloff so that it looks like the paint has been
 sprayed onto the canvas.  It also has the interesting property that it
 continues to paint even when held stationary so paint continues to accumulate on the
 canvas the longer you hold it still. 
 * */

class ToolSprayCan : public Tool {
 public:
  ToolSprayCan();
  virtual ~ToolSprayCan();
  static const std::string name() { return "Spray Can"; }

  FloatMatrix* CreateMask(float radius) override;
 /**
  * @brief Paint can accumulate even when held
   stationary.
   */

  bool applies_paint_when_stationary() override { return true; }
};

} /* namespace image_tools */

#endif  // IMAGETOOLS_TOOL_SPRAY_CAN_H_
