/**
* @file filter_saturation.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_SATURATION_H_
#define IMAGETOOLS_FILTER_SATURATION_H_

#include <string>
#include "imagetools/filter.h"

namespace image_tools {
  /** @brief Saturation filter is a simple filter that measures the vibrance
   * of colors in the images. A completely non-saturated image would be a
   * grayscale version of the image; a 100% sacturated image has ths original color;
   * a 200% saturated filter has a really vibrant new color.*/
class FilterSaturation : public Filter {
 public:
  explicit FilterSaturation(float scale);
  virtual ~FilterSaturation();
  FilterSaturation();

  /**
   * @brief Convert pixel to a grayscale value and linearly interpolate
    * between grayscale version of the color and the color*/
  ColorData CalculateFilterPixel(PixelBuffer* buffer,
    int x, int y) override;
  /**
   * @brief A simple filter thus can be calculated in place.*/ 
  bool can_calculate_in_place() override { return true; }

 private:
  float scale_;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_SATURATION_H_
