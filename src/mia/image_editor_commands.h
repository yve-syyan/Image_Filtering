/**
* @file image_editor_commands.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/


#ifndef MIA_IMAGE_EDITOR_COMMANDS_H_
#define MIA_IMAGE_EDITOR_COMMANDS_H_

#include <string>

#include "imagetools/color_data.h"
#include "imagetools/filter_motionblur.h"
#include "imagetools/image_editor.h"

namespace image_tools {

/**@brief Base class for all image editor commands. Each command knows how to execute
 itself, including sending and required parameters to the image editor. This
 structure follows the Command Design Pattern.  The command pattern is also
 often used to implement undo.  However, we don't do that here because all of
 the commands get "undone" in exactly the same way -- we simply restore the
 pixel buffer that was in place before the command was executed.  So, it's
 quite clean to implement the undo feature directly within the ImageEditor
 class, which simply maintains a list of previous pixel buffers.  The main
 reason for implementing these command wrappers around the image editor
 functionality is to be able to easily create a list of commands to run later
 while parsing command line arguments.  If instead we just processed each
 command as it appears on the command line (e.g., blur then threshold then ...)
 the process can potentially run for quite a long time before discovering that
 there is an error in the syntax at the end of the command line.  So, it is nice
 to be able to parse the whole command line first building up a list of commands
 to send to the image editor and then, if the whole command line looks good, run
 the whole list of commands. */
class ImageEditorCommand {
 public:
  explicit ImageEditorCommand(ImageEditor *image_editor);
  virtual ~ImageEditorCommand();

  virtual void Execute() = 0;

 protected:
  ImageEditor *image_editor_;
};

/**@brief Specific command for executing a FilterBlur. */
class BlurFilterCommand : public ImageEditorCommand {
 public:
  BlurFilterCommand(ImageEditor *image_editor, float radius);
  virtual ~BlurFilterCommand();

  void Execute() override;
  bool getactive_();

 private:
  float radius_;
};

/**@brief Specific command for executing an FilterDetectEdges. */
class EdgeFilterCommand : public ImageEditorCommand {
 public:
  explicit EdgeFilterCommand(ImageEditor *image_editor);
  virtual ~EdgeFilterCommand();

  void Execute() override;
  bool getactive_();
};

/**@brief  Specific command for executing a FilterSharpen. */
class SharpenFilterCommand : public ImageEditorCommand {
 public:
  SharpenFilterCommand(ImageEditor *image_editor, float radius);
  virtual ~SharpenFilterCommand();

  void Execute() override;
  bool getactive_();
 private:
  float radius_;
};

/**@brief  Specific command for executing the FilterChannel. */
class ChannelsFilterCommand : public ImageEditorCommand {
 public:
  ChannelsFilterCommand(ImageEditor *image_editor, float red_scale,
                        float green_scale, float blue_scale);
  virtual ~ChannelsFilterCommand();

  void Execute() override;
  bool getactive_();
 private:
  float r_, g_, b_;
};

/**@brief  Specific command for executing a FilterQuantize. */
class QuantizeFilterCommand : public ImageEditorCommand {
 public:
  QuantizeFilterCommand(ImageEditor *image_editor, int bins);
  virtual ~QuantizeFilterCommand();

  void Execute() override;
  bool getactive_();
 private:
  int bins_;
};

/**@brief  Specific command for executing a FilterSaturation. */
class SaturateFilterCommand : public ImageEditorCommand {
 public:
  SaturateFilterCommand(ImageEditor *image_editor, float scale);
  virtual ~SaturateFilterCommand();

  void Execute() override;
  bool getactive_();
 private:
  float scale_;
};

/**@brief  Specific command for executing a FilterThreshold. */
class ThresholdFilterCommand : public ImageEditorCommand {
 public:
  ThresholdFilterCommand(ImageEditor *image_editor, float cutoff);
  virtual ~ThresholdFilterCommand();

  void Execute() override;
  bool getactive_();
 private:
  float cutoff_;
};

/**@brief  Specific command for executing a motion FilterBlur. */
class MotionBlurFilterCommand : public ImageEditorCommand {
 public:
  MotionBlurFilterCommand(ImageEditor *image_editor, float radius,
                          FilterMotionblur::MBlurDir dir);
  virtual ~MotionBlurFilterCommand();

  void Execute() override;
  bool getactive_();
 private:
  float radius_;
  FilterMotionblur::MBlurDir dir_;
};

/**@brief Specific command for executing an undo. */
class UndoCommand : public ImageEditorCommand {
 public:
  explicit UndoCommand(ImageEditor *image_editor);
  virtual ~UndoCommand();

  void Execute() override;
};

/**@brief  Specific command for executing a redo. */
class RedoCommand : public ImageEditorCommand {
 public:
  explicit RedoCommand(ImageEditor *image_editor);
  virtual ~RedoCommand();

  void Execute() override;
};

/**@brief  Specific command for starting a stroke. */
class StartStrokeCommand : public ImageEditorCommand {
 public:
  StartStrokeCommand(ImageEditor *image_editor, const std::string &tool_name,
                     const ColorData &color, float radius, int x, int y);
  virtual ~StartStrokeCommand();

  void Execute() override;

 private:
  std::string tool_name_;
  ColorData color_;
  float radius_;
  int x_, y_;
};

/**@brief  Specific command for adding to the most recently started stroke. */
class AddToStrokeCommand : public ImageEditorCommand {
 public:
  AddToStrokeCommand(ImageEditor *image_editor, int x, int y);
  virtual ~AddToStrokeCommand();

  void Execute() override;

 private:
  int x_, y_;
};

/**@brief  Specific command for ending the stroke. */
class EndStrokeCommand : public ImageEditorCommand {
 public:
  EndStrokeCommand(ImageEditor *image_editor, int x, int y);
  virtual ~EndStrokeCommand();

  void Execute() override;

 private:
  int x_, y_;
};

/**@brief  Specific command for loading a file. */
class LoadCommand : public ImageEditorCommand {
 public:
  LoadCommand(ImageEditor *image_editor, const std::string &filename);
  virtual ~LoadCommand();

  void Execute() override;

 private:
  std::string filename_;
};

/**@brief  Specific command for saving a file. */
class SaveCommand : public ImageEditorCommand {
 public:
  SaveCommand(ImageEditor *image_editor, const std::string &filename);
  virtual ~SaveCommand();

  void Execute() override;

 private:
  std::string filename_;
};

}  // namespace image_tools

#endif  // MIA_IMAGE_EDITOR_COMMANDS_H_
