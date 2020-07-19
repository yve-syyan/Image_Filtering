/**
* @file float_matrix.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_FLOAT_MATRIX_H_
#define IMAGETOOLS_FLOAT_MATRIX_H_

#include <iostream>
#include <vector>

namespace image_tools {

/**@brief This class holds a 2D array of floats that can be accessed by (row,column).
 It also includes a number of utility functions for working with the array,
 such as normalizing it or multiplying every element by some scale factor. */
class FloatMatrix {
 public:
  /**@brief Creates a 1 by 1 matrix that stores a 1.0*/
  FloatMatrix();

  /**@brief Creates a 2*radius+1 by 2*radius+1 matrix with 1.0 in each element*/
  explicit FloatMatrix(int radius);

  /**@brief Creates a w by h matrix with 1.0 in each element*/
  FloatMatrix(int w, int h);

  virtual ~FloatMatrix();

  /** @brief Get the sum total of all elements of the matrix. */
  float Sum();

  /** @brief "Normalize" the matrix by dividing each element by the sum. */
  void Normalize();

  /** @brief Multiply every element in FloatMatrix by a constant. */
  void Scale(const float c);

  /** @brief Provides access to the raw float array. */
  float const *float_array() const { return &float_array_[0]; }

  /** @brief Get the width of the 2D float matrix. */
  int width() const { return width_; }

  /** @brief Get the height of the 2D float matrix. */
  int height() const { return height_; }

  /** @brief Get the value of a specific element. */
  virtual float value(int x, int y) const;

  /** @brief Set the value of an element (x,y) of the float matrix. */
  void set_value(int x, int y, float v);

  /**@brief The ostream operator is overloaded to make printing the matrix easy for
   debugging. Just send the matrix to std::cout. */
  friend std::ostream &operator<<(std::ostream &s, const FloatMatrix &mat);

 private:
  /* Copy assignment/construction is disallowed */
  FloatMatrix(const FloatMatrix &rhs) = delete;
  FloatMatrix &operator=(const FloatMatrix &rhs) = delete;

  const int height_;
  const int width_;
  std::vector<float> float_array_; /**< The raw float array  */
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FLOAT_MATRIX_H_
