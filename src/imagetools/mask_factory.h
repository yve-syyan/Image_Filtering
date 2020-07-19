/**
* @file mask_factory.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_MASK_FACTORY_H_
#define IMAGETOOLS_MASK_FACTORY_H_

#include "imagetools/float_matrix.h"

namespace image_tools {

/** @brief This factory is used to create masks used by image editing tools. 
 * Some of the masks are used by more than one tool. The mask stores the “amount
 *  of influence” the tool should have on the canvas for each pixel. */
class MaskFactory {
 public:
 /**
  * @brief Constant mask has a shape of circle*/
  static FloatMatrix* CreateConstantMask(float radius);
 /**
  * @brief Oval mask has a shape of oval*/
  static FloatMatrix* CreateOvalMask(float radius, float angle_in_deg,
                                     float ratio);
 /**
  * @brief Linear mask has a shape of rectangle*/
  static FloatMatrix* CreateLinearFalloffMask(float radius);
 /**
  * @brief Linear mask has a shape of nested circle with empty inner circle.*/
  static FloatMatrix* CreateBullseyeMask(float radius, float linewidth);
};

}  // namespace image_tools

#endif  // IMAGETOOLS_MASK_FACTORY_H_

