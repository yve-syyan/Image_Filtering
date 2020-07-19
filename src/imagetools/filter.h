/**
* @file filter.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_H_
#define IMAGETOOLS_FILTER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /** @brief Base class for all filters that change each pixel in the image
   *  in some way. All filters are applied to the canvas as a whole, 
   * using loops to go through each pixel in canvas and update its color 
   * in some way based on each filters' characteristics */
class Filter {
 public:
  Filter();
  virtual ~Filter();

  /**@brief Create a template for filtered buffer computation*/
  void ApplyToBuffer(PixelBuffer*);

  /**@brief Setup a kernel for convolution filters. 
   * Not used for simple filters.*/
  virtual void SetUpFilter();

  /**@brief Calculate colordata for pixel within buffer at (x,y). 
    * Redefined by each simple filters and ConvolutionFilter*/
  virtual ColorData CalculateFilterPixel
    (PixelBuffer*, int x , int y) = 0;

  /**@brief Clean up kernel for convolution filters*/
  virtual void CleanUpFilter();

  /**@brief Determine if color data can be computed in place. 
    * Simple filters can be calculated in place.
    * Convolution filters cannot be calculated in place.*/
  virtual bool can_calculate_in_place(){return true;}
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_H_
