/**
* @file filter_blur.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_BLUR_H_
#define IMAGETOOLS_FILTER_BLUR_H_

#include <string>
#include "imagetools/ConvolutionFilter.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  /**
   * @brief Filter blur is a convolution filter that change colordata of
   * current pixel under the influence of its neighbors. The bigger the
   * size of a blur fitler, the more blur the image is. For a smoother 
   * blur, we use a gaussian kernel whose value expotentially decreases 
   * as distance away from center increases.*/
class FilterBlur : public ConvolutionFilter {
 private:
  float radius;

 public:
  explicit FilterBlur(float r);
  FilterBlur();
  void set_radius(float r);
  virtual ~FilterBlur();

  /**
   * @brief Create a blur kernel of radius r using gaussian formula*/
  FloatMatrix* CreateKernel() override;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_BLUR_H_
