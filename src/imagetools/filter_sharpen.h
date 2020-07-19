/**
* @file filter_sharpen.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_SHARPEN_H_
#define IMAGETOOLS_FILTER_SHARPEN_H_

#include "imagetools/ConvolutionFilter.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  /**@brief Sharpen is a ConvolutionFilter that enhances edges of images,
   * making it look sharper. It adds the original image and image after 
   * edge detection to each other, incrementing center value of pixel with 1. 
   * The sum of filter elements is 1 and the result will be an image with 
   * same brightness but sharper.*/
class FilterSharpen : public ConvolutionFilter {
 private:
  float radius;

 public:
  explicit FilterSharpen(float r);
  virtual ~FilterSharpen();
  FilterSharpen();

  /**@brief create a kernel with center value as size of matrix and the
    *  rest as -1*/
  FloatMatrix* CreateKernel() override;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_SHARPEN_H_
