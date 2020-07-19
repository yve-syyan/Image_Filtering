/**
* @file command_line_processor.h
* 
* @copyright 2018 3081 Staff, All rights reserved.
*/

#ifndef MIA_COMMAND_LINE_PROCESSOR_H_
#define MIA_COMMAND_LINE_PROCESSOR_H_

#include <mingfx.h>
#include <deque>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include "imagetools/image_editor.h"
#include "mia/image_editor_commands.h"

namespace image_tools {
  /** @brief This processor is used to match entered command with
   * corresponding filter implementation.*/
class CommandLineProcessor {
 public:
  CommandLineProcessor();
  ~CommandLineProcessor();
  explicit CommandLineProcessor(ImageEditor*);
  /**@brief takes in a command and number of arguments, then 
   * implement required filter/tool */
  void ProcessCommandLine(int argc, char* argv[]);
  /**
   * @brief Motionblur Filter motion dictionary.*/
    enum MBlurDir {
    MBLUR_DIR_N_S,
    MBLUR_DIR_E_W,
    MBLUR_DIR_NE_SW,
    MBLUR_DIR_NW_SE
  };
    /**
   * @brief Returns number of commands stored within a ImageEditorCommand* vector.*/
  int vector_size();
  std::vector<ImageEditorCommand*> getcmd();

 private:
  ImageEditor* image_editor_;
  void help();
  std::vector<ImageEditorCommand*> commands_;
};
} /* namespace image_tools */

#endif  // MIA_COMMAND_LINE_PROCESSOR_H_
