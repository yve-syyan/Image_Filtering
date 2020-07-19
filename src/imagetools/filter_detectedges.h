/**
* @file filter_detectedges.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_DETECTEDGES_H_
#define IMAGETOOLS_FILTER_DETECTEDGES_H_
#include "imagetools/ConvolutionFilter.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  /** @brief Edgedetect filter is a ConvolutionFilter that detects edges in all directions.
   * Detect edge's kernel operates as a discrete version of derivative:
   * taking current pixel and subtracting the value of the previous one
   * frome it, thus a value representing the difference between those two
   * or the slope of the function is reached.*/
class FilterDetectEdges : public ConvolutionFilter {
 public:
  FilterDetectEdges();
  virtual ~FilterDetectEdges();

  /**@brief create a kernel with center value at 8 and 
   * the rest of cells at -1*/ 
  FloatMatrix* CreateKernel() override;

 private:
  float radius;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_DETECTEDGES_H_
