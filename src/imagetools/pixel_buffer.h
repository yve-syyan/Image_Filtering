/**
* @file pixel_buffer.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/


#ifndef IMAGETOOLS_PIXEL_BUFFER_H_
#define IMAGETOOLS_PIXEL_BUFFER_H_

/**********************************************************************
 * Includes
 *********************************************************************/

#include <string>
#include <vector>
#include "imagetools/color_data.h"

namespace image_tools {

/** @brief Stores an array of ColorData, such as an image that can be drawn to
    the screen.

    The data are stored internally in a 1D array, laid out in row-major order
    with 4 floats (RGBA) for each pixel in the image.  The raw data can be
    accessed directly with data() and individual pixels can be accessed with
    get_pixel(x,y).
 */
class PixelBuffer {
 public:
  /** 
   * @brief Fills the new pixel buffer with the background color. 
   */
  PixelBuffer(int w, int h, ColorData background_color);

  /** @brief Loads a PNG image and stores it in the buffer.  Sets the background
   color to white. */
  explicit PixelBuffer(const std::string &filename);

  /** @brief Copy constructor */
  PixelBuffer(const PixelBuffer &rhs);

  virtual ~PixelBuffer();

  /** @brief Assignment operator */
  PixelBuffer &operator=(const PixelBuffer &rhs);

  inline int height() const { return height_; }

  inline int width() const { return width_; }

  /** @brief Get the background color that was used to initialize the
     PixelBuffer
      @return The background color
   */
  const ColorData &background_color() const { return background_color_; }

  /** @brief Get the color of a specific pixel. */
  ColorData pixel(int x, int y) const;

  /** @brief Set the value for a specific pixel. */
  void set_pixel(int x, int y, const ColorData &color);

  /** @brief Returns a pointer to the raw pixel data array stored in row-major order
      as RGBA floats. */
  inline float const *data() const { return &pixels_[0]; }

  /** @brief Resizes the buffer, cropping the image and/or creating new pixels as
     needed. New pixels will use the background color. */
  void Resize(int new_width, int new_height);

  /** @brief  Saves to a PNG file, the filename should include a .png 
   * extension. */
  void SaveToFile(const std::string &filename);
  /** @brief Loads from a PNG file.  Will resize the buffer as 
   * needed. */
  void LoadFromFile(const std::string &filename);
  /** @brief Check for "equality", taking floating point imprecision
   *  into account */
  friend bool operator==(const PixelBuffer &a, const PixelBuffer &b);
  /** @brief Check for "inequality", taking floating point imprecision
   *  into account */
  friend bool operator!=(const PixelBuffer &a, const PixelBuffer &b);

 private:
  int width_;
  int height_;

  std::vector<float> pixels_;  /**< Raw pixel data */
  ColorData background_color_; /** Color used to initialize the pixel buffer */
};

}  // namespace image_tools

#endif  // IMAGETOOLS_PIXEL_BUFFER_H_
