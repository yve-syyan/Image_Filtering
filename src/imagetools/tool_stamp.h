/**
* @file tool_stamp.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_TOOL_STAMP_H_
#define IMAGETOOLS_TOOL_STAMP_H_

/**********************************************************************
 * Includes
 *********************************************************************/

#include <string>
#include "imagetools/tool.h"

namespace image_tools {

/**********************************************************************
 * Includes
 **********************************************************************/
/** @brief Stamps a single X marks the spot. */
class ToolStamp : public Tool {
 public:
  ToolStamp();
  virtual ~ToolStamp();

  /** 
   * @brief return name of tool for interface presentation
   */

  static const std::string name() { return "Stamp"; }

  /** 
   * @brief The stamp tool overrides AddToStroke to make it do nothing.  This way,
   each time the stamp tool is used it produces just a single mark on the
   canvas at the first location where it is applied.
   */
  void AddToStroke(int x, int y) override;

  FloatMatrix* CreateMask(float radius) override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_STAMP_H_

