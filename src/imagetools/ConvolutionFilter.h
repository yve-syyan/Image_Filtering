/**
* @file ConvolutionFilter.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_CONVOLUTIONFILTER_H_
#define IMAGETOOLS_CONVOLUTIONFILTER_H_

#include <string>
#include "imagetools/filter.h"

namespace image_tools {
  /**@brief Convolution filters are Filter with a convolution kernel, a 2D 
   * filter matrix. Kernel is multiplied with 2D and sum of products are
   * taken. Each product is the color value of the current pixel or a 
   * neighbor of it, with corresponding value of filter matirx. For this
   * project, we assume the size of kernels to be uneven. If the sum of elements
   * is larger than 1, the result will be a brighter image. If smaller than
   * 1, the result is a darker image. */
class ConvolutionFilter : public Filter {
 private:
  FloatMatrix* kernel;

 public:
  ConvolutionFilter();
  virtual ~ConvolutionFilter();
  virtual FloatMatrix* CreateKernel() = 0;
  void SetUpFilter() override;

  /**@brief Calculate color data by multiplying kernel with corresponding pixel
    * color data*/
  ColorData CalculateFilterPixel
    (PixelBuffer* image_, int x, int y) override;

  void CleanUpFilter() override;

  /**@brief Color data cannot be calculated in place*/
  bool can_calculate_in_place() override {return false;};
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_CONVOLUTIONFILTER_H_
