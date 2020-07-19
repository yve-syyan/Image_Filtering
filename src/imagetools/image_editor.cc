/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/image_editor.h"
#include <assert.h>
#include <mingfx.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>

namespace image_tools {

ImageEditor::ImageEditor(PixelBuffer *buffer) {
    current_buffer_ = buffer;
  }

ImageEditor::ImageEditor() {
    current_buffer_ = NULL;
}

ImageEditor::~ImageEditor() {}

Tool *ImageEditor::GetToolByName(const std::string &name) {
  if (name == t_blur_.name()) {
    return &t_blur_;
  } else if (name == t_calligraphy_pen_.name()) {
    return &t_calligraphy_pen_;
  } else if (name == t_chalk_.name()) {
    return &t_chalk_;
  } else if (name == t_eraser_.name()) {
    return &t_eraser_;
  } else if (name == t_highlighter_.name()) {
    return &t_highlighter_;
  } else if (name == t_pen_.name()) {
    return &t_pen_;
  } else if (name == t_spray_can_.name()) {
    return &t_spray_can_;
  } else if (name == t_stamp_.name()) {
    return &t_stamp_;
  } else {
    return NULL;
  }
}

void ImageEditor::StartStroke(const std::string &tool_name,
                              const ColorData &color, float radius, int x,
                              int y) {
  current_tool_ = GetToolByName(tool_name);
  tool_color_ = color;
  tool_radius_ = radius;
  if ((current_tool_) && (current_buffer_)) {
    SaveStateForPossibleUndo();
    current_tool_->StartStroke(current_buffer_, x, y, tool_color_,
                               tool_radius_);
  }
}

void ImageEditor::AddToStroke(int x, int y) {
  if ((current_tool_) && (current_buffer_)) {
    current_tool_->AddToStroke(x, y);
  }
}

void ImageEditor::EndStroke(int x, int y) {
  if ((current_tool_) && (current_buffer_)) {
    current_tool_->EndStroke(x, y);
  }
}

void ImageEditor::LoadFromFile(const std::string &filename) {
  if (current_buffer_ != NULL) {
    SaveStateForPossibleUndo();
    current_buffer_->LoadFromFile(filename);
  } else {
  current_buffer_ = new PixelBuffer(filename);
  }
}

void ImageEditor::SaveToFile(const std::string &filename) {
  current_buffer_->SaveToFile(filename);
}

void ImageEditor::ApplyBlurFilter(float radius) {
  SaveStateForPossibleUndo();
  Filter* apply_blur_ = new FilterBlur(radius);
  apply_blur_ -> ApplyToBuffer(current_buffer_);
  delete apply_blur_;
}

void ImageEditor::ApplyMotionBlurFilter(
    float rad, FilterMotionblur::MBlurDir dir) {
  SaveStateForPossibleUndo();
  Filter* apply_motionblur_ = new FilterMotionblur(rad, dir);
  apply_motionblur_ -> ApplyToBuffer(current_buffer_);
  delete apply_motionblur_;
}

void ImageEditor::ApplySharpenFilter(float rad) {
  SaveStateForPossibleUndo();
  Filter* apply_sharpen_ = new FilterSharpen(rad);
  apply_sharpen_ -> ApplyToBuffer(current_buffer_);
  delete apply_sharpen_;
}

void ImageEditor::ApplyEdgeDetectFilter() {
  SaveStateForPossibleUndo();
  Filter* apply_detectedges_ = new FilterDetectEdges();
  apply_detectedges_ -> ApplyToBuffer(current_buffer_);
  delete apply_detectedges_;
}

void ImageEditor::ApplyThresholdFilter(float value) {
  SaveStateForPossibleUndo();
  Filter* apply_threshold_ = new FilterThreshold(value);
  apply_threshold_ -> ApplyToBuffer(current_buffer_);
  delete apply_threshold_;
}

void ImageEditor::ApplySaturateFilter(float scale) {
  SaveStateForPossibleUndo();
  Filter* apply_saturate_ = new FilterSaturation(scale);
  apply_saturate_ -> ApplyToBuffer(current_buffer_);
  delete apply_saturate_;
}

void ImageEditor::ApplyChannelsFilter(float red, float green, float blue) {
  SaveStateForPossibleUndo();
  Filter* apply_channel_ = new FilterChannel(red, green, blue);
  apply_channel_ -> ApplyToBuffer(current_buffer_);
  delete apply_channel_;
}

void ImageEditor::ApplyQuantizeFilter(int num) {
  SaveStateForPossibleUndo();
  Filter* apply_quantize_ = new FilterQuantize(num);
  apply_quantize_ -> ApplyToBuffer(current_buffer_);
  delete apply_quantize_;
}

bool ImageEditor::can_undo() {
  return saved_states_.size();
}

bool ImageEditor::can_redo() {
  return undone_states_.size();
}

void ImageEditor::Undo() {
  if (can_undo()) {
    // save state for a possilbe redo
    undone_states_.push_front(current_buffer_);
    // comment for push
    // make the top state on the undo stack the current one
    current_buffer_ = saved_states_.front();
    saved_states_.pop_front();
  }
}

void ImageEditor::Redo() {
  if (can_redo()) {
    // save state for a possible undo
    saved_states_.push_front(current_buffer_);

    // make the top state on the redo stack the current one
    current_buffer_ = undone_states_.front();
    undone_states_.pop_front();
  }
}

PixelBuffer *ImageEditor::pixel_buffer() { return current_buffer_; }

void ImageEditor::SaveStateForPossibleUndo() {
  PixelBuffer *buffer_copy = new PixelBuffer(*current_buffer_);
  saved_states_.push_front(buffer_copy);

  // remove the oldest undos if we've over our limit
  while (saved_states_.size() > max_undos_) {
    delete saved_states_.back();
    saved_states_.pop_back();
  }

  // committing a new state invalidates the states saved in the redo stack,
  // so, we simply clear out this stack.
  while (!undone_states_.empty()) {
    delete undone_states_.back();
    undone_states_.pop_back();
  }
}

void ImageEditor::set_pixel_buffer(PixelBuffer *buffer) {
  current_buffer_ = buffer;
}
} /* namespace image_tools */
