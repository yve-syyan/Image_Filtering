/**
* @file image_editor.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef IMAGETOOLS_IMAGE_EDITOR_H_
#define IMAGETOOLS_IMAGE_EDITOR_H_

#include <deque>
#include <string>
#include <vector>
#include <map>

#include "imagetools/pixel_buffer.h"

// filters
#include "imagetools/filter_blur.h"
#include "imagetools/filter_detectedges.h"
#include "imagetools/filter_motionblur.h"
#include "imagetools/filter_sharpen.h"
#include "imagetools/filter_channels.h"
#include "imagetools/filter_quantize.h"
#include "imagetools/filter_saturation.h"
#include "imagetools/filter_threshold.h"

// tools
#include "imagetools/tool.h"
#include "imagetools/tool_blur.h"
#include "imagetools/tool_calligraphy_pen.h"
#include "imagetools/tool_chalk.h"
#include "imagetools/tool_eraser.h"
#include "imagetools/tool_highlighter.h"
#include "imagetools/tool_pen.h"
#include "imagetools/tool_spray_can.h"
#include "imagetools/tool_stamp.h"


namespace image_tools {

/**@brief This is the major class of the FlashPhoto application.  In the
 model-view-controller paradigm, we can think of this class as implementing
 the model for an ImageEditor that could be controlled by various controllers
 (e.g., interactive mouse and keyboard, command line) and viewed different
 ways (e.g., interactively with a GUI, with files written to disk). */
class ImageEditor {
 public:
  /**@brief  The ImageEditor requires a current pixel buffer, so this is the preferred
   constructor. */
  explicit ImageEditor(PixelBuffer *buffer);

  /**@brief Creates an editor with a NULL pixel buffer.  You will need to set the
   pixel buffer before performing any editing operations. */
  ImageEditor();

  /**@brief  Deletes the current pixel buffer if not null. */
  virtual ~ImageEditor();

  // FILE SAVING AND LOADING

  /**@brief Loads a pixel buffer from a PNG formatted file. */
  void LoadFromFile(const std::string &filename);

  /**@brief Saves the current pixel buffer to a PNG file. */
  void SaveToFile(const std::string &filename);

  // TOOLS

  Tool *GetToolByName(const std::string &name);

  /**@brief Call this from the controller to being a new stroke at pixel (x,y) using
   the tool named tool_name and the specified color and radius.  Since it
   takes multiple frames to complete a stroke the tool_name, color, and radius
   are saved as state variables and are used for subsequent calls to
   AddToStroke() and EndStroke(). */
  void StartStroke(const std::string &tool_name, const ColorData &color,
                   float radius, int x, int y);

  /**@brief Call this from the controller to add to a stroke that was recently
   started with a call to StartStroke(). */
  void AddToStroke(int x, int y);

  /**@brief Call this from the controller to end a stroke started with
   StartStroke(). */
  void EndStroke(int x, int y);

  // FILTERS

  /**@brief Call this from the controller to apply the blur filter to the current
   pixel buffer using the current blur filter state. */
  void ApplyBlurFilter(float radius);

  /**@brief Call this from the controller to apply the filter to the current
   pixel buffer using the current motion blur filter state. */
  void ApplyMotionBlurFilter(float radius,
                              FilterMotionblur::MBlurDir dir);

  /**@brief Call this from the controller to apply the sharpen filter to the current
   pixel buffer using the current sharpen filter state. */
  void ApplySharpenFilter(float radius);

  /**@brief Call this from the controller to apply the edge detect filter to the
   current
   pixel buffer using the current edge detect filter state. */
  void ApplyEdgeDetectFilter();

  /**@brief Call this from the controller to apply the threshold filter to the current
   pixel buffer using the current threshold filter state. */
  void ApplyThresholdFilter(float cutoff_value);

  /**@brief Call this from the controller to apply the saturate filter to the current
   pixel buffer using the current saturate filter state. */
  void ApplySaturateFilter(float scale_factor);

  /**@brief Call this from the controller to apply the channels filter to the current
   pixel buffer using the current channels filter state. */
  void ApplyChannelsFilter(float red_scale, float green_scale,
                           float blue_scale);

  /**@brief Call this from the controller to apply the quantize filter to the current
   pixel buffer using the current quantize filter state. */
  void ApplyQuantizeFilter(int num_bins);

  /**@brief Undo the last operation applied to the pixel buffer. */
  void Undo();

  /**@brief Redo the last undone operation. */
  void Redo();

  /**@brief True if the the log of applied commands is not empty, i.e., it is
   possible to perform an undo operation. */
  bool can_undo();

  /**@brief True if the log of undone commands is not empty, i.e., it is possible to
   perform a redo operation. */
  bool can_redo();

  PixelBuffer *pixel_buffer();

  void set_pixel_buffer(PixelBuffer *buffer);

 private:
  FilterBlur f_blur_;
  FilterDetectEdges f_edge_;
  FilterMotionblur f_motion_blur_;
  FilterSharpen f_sharpen_;
  FilterChannel f_channels_;
  FilterQuantize f_quantize_;
  FilterSaturation f_saturate_;
  FilterThreshold f_threshold_;

  ToolBlur t_blur_;
  ToolCalligraphyPen t_calligraphy_pen_;
  ToolChalk t_chalk_;
  ToolEraser t_eraser_;
  ToolHighlighter t_highlighter_;
  ToolPen t_pen_;
  ToolSprayCan t_spray_can_;
  ToolStamp t_stamp_;

  // state data saved during calls to StartStroke, AddToStroke, EndStroke
  Tool *current_tool_;
  ColorData tool_color_;
  float tool_radius_;

  PixelBuffer *current_buffer_;

  void SaveStateForPossibleUndo();

  unsigned int max_undos_;
  std::deque<PixelBuffer *> saved_states_;   // undo
  std::deque<PixelBuffer *> undone_states_;  // redo
};

}  // namespace image_tools

#endif  // IMAGETOOLS_IMAGE_EDITOR_H_

