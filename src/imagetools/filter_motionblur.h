/**
* @file filter_motionblur.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/
#ifndef IMAGETOOLS_FILTER_MOTIONBLUR_H_
#define IMAGETOOLS_FILTER_MOTIONBLUR_H_


#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include "imagetools/ConvolutionFilter.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  /**@brief Motion blur is a ConvolutionFilter achieved by blurring in only 1 direction. 
   * Four possible directions of blurring is available: North-South, 
   * East-West, Northeast-Southwest, Southeast-Northwest.*/
class FilterMotionblur : public ConvolutionFilter {
 public:
  FilterMotionblur();
  virtual ~FilterMotionblur();
  /**
   * @brief Create kernel with elements filled only on one direction.*/
  FloatMatrix* CreateKernel() override;
  /**
   * @brief Motionblur direction dictionary*/
  enum MBlurDir {
    MBLUR_DIR_N_S,
    MBLUR_DIR_E_W,
    MBLUR_DIR_NE_SW,
    MBLUR_DIR_NW_SE
  };
  /**
   * @brief Turns a direction from MBlurDir to corresponding string.*/
  static std::string MotionBlurDirectionName(MBlurDir dir);
  FilterMotionblur(float r, MBlurDir d);

 private:
  float radius;
  std::string direction;
  static const std::map<MBlurDir, std::string> mblur_dir_names_;
};
} /* namespace image_tools */
#endif  // IMAGETOOLS_FILTER_MOTIONBLUR_H_
