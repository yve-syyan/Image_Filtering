/**
* @file filter_threshold.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_THRESHOLD_H_
#define IMAGETOOLS_FILTER_THRESHOLD_H_

#include <string>
#include "imagetools/filter.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  /** @brief Threshold filter is a simple Filter finds the average intensity of pixel by 
   * averaging its Red, Green and Blue values. By comparing the average
   * intensity with entered cutoff value, if average intensity is 
   * greater than the cutoff, the pixel is set to white; otherwise 
   * it is turned into black. */
class FilterThreshold : public Filter {
 public:
  explicit FilterThreshold(float cutoff_);
  FilterThreshold();
  virtual ~FilterThreshold();

  /**@brief Reset all pixels with an average intensity value greater than 
    * the threshold parameter into the GUI  white; 
    * otherwise turn the pixel black.*/
  ColorData CalculateFilterPixel(PixelBuffer* buffer,
    int x, int y) override;

  /**@brief Simple filter thus can be calculated in place.*/
  bool can_calculate_in_place() override {return true; }

 private:
  float thresh_cutoff_;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_THRESHOLD_H_
