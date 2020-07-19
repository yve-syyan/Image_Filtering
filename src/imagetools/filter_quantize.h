/**
* @file filter_quantize.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_QUANTIZE_H_
#define IMAGETOOLS_FILTER_QUANTIZE_H_
#include <string>
#include "imagetools/filter.h"

namespace image_tools {
  /** @brief Quantize is a simple Filter that reduces the number of unique
   * colors in the image by binning similar colors. Takes input as the preset
   * number of bins. Input is ristricted to integers larger than 1.*/
class FilterQuantize : public Filter {
 public:
  explicit FilterQuantize(int n);
  FilterQuantize();
  virtual ~FilterQuantize();

  /**
   * @brief Take input as a preset number of bins and bines similar colors.
   */
  ColorData CalculateFilterPixel(PixelBuffer* buffer,
    int x, int y) override;
  /**
   * @brief A simple filter thus can be calculated in place.*/ 
  bool can_calculate_in_place() override { return true; }

 private:
  int num_;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_QUANTIZE_H_
