/**
* @file filter_channels.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_CHANNELS_H_
#define IMAGETOOLS_FILTER_CHANNELS_H_

#include <string>
#include "imagetools/filter.h"

namespace image_tools {
  /** @brief Filter channel is a simple filter that changes the vibrance 
   * of Red, Green or Blue channels seperately. Given some scale factors
   * from the user, one for each color channel, the filter multiply Red, 
   * Green and Blue component for each pixel in the image seperately by
   * scale factor entered.*/
class FilterChannel : public Filter {
 public:
  FilterChannel(float r, float g, float b);
  FilterChannel();
  virtual ~FilterChannel();

  /**@brief Given scale factors from users, Red, Green and Blue's vibrance
    * are multiplied seperately by the scale factor*/
  ColorData CalculateFilterPixel(PixelBuffer* buffer,
    int x, int y) override;

  bool can_calculate_in_place() override { return true; }

 private:
  float red_scale_;
  float green_scale_;
  float blue_scale_;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_CHANNELS_H_
