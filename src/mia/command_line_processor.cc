/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "mia/command_line_processor.h"
#include <stdio.h>
#include <stdlib.h>
#include <mingfx.h>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include "imagetools/image_editor.h"

namespace image_tools {
  CommandLineProcessor::CommandLineProcessor() {
  image_editor_ = new ImageEditor();
  }

  CommandLineProcessor::~CommandLineProcessor() {}

  CommandLineProcessor::CommandLineProcessor(ImageEditor* image_) {
    image_editor_ = image_;
  }

  void CommandLineProcessor::ProcessCommandLine(int argc, char* argv[]) {
      if (argc <= 2 && static_cast<std::string>(argv[1]) != "-h") {
         std::cout<< "insufficient argument\n" << std::endl;
          help();
      }
      if ((static_cast<std::string>(argv[0]) == "mia" && static_cast
      <std::string>(argv[1]) == "-h") && argc == 2) {
        help();
        return;
     }
    try {
    for (int i = 1; i < argc; i ++) {
        std::string cmd = static_cast<std::string>(argv[i]);
        if (i == 1) {
        if (cmd.find(".png") != std::string::npos ||
          cmd.find(".PNG") != std::string::npos) {
        ImageEditorCommand* load_c_ =
        new LoadCommand(image_editor_, cmd);
        commands_.push_back(load_c_);} else {
        std::string err = "missing input file\n";
        throw err;
        }
    } else if (i == (argc - 1)) {
         if (cmd.find (".png") != std::string::npos || cmd.find(".PNG")
         != std::string::npos) {
          ImageEditorCommand* save_c_ = new SaveCommand(image_editor_, cmd);
        commands_.push_back(save_c_);
    } else {
        std::string err = "missing output file\n";
        throw err;
      }
    } else if (cmd == "-blur") {
    try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* blur_c_ =
        new BlurFilterCommand(image_editor_, f);
        commands_.push_back(blur_c_);
        i++;
    }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
    }
    } else if (cmd == "-edgedetect") {
        ImageEditorCommand* edge_c_ =
        new EdgeFilterCommand(image_editor_);
        commands_.push_back(edge_c_);
    } else if (cmd == "-sharpen") {
      try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* sharpen_c_ = new SharpenFilterCommand
        (image_editor_, f);
        commands_.push_back(sharpen_c_);
        i++;
    }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
      }
    } else if (cmd == "-red") {
      try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* channel_r_ =
        new ChannelsFilterCommand(image_editor_, f, 1.0, 1.0);
        commands_.push_back(channel_r_);
        i++;
    }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
      }
    } else if (cmd == "-green") {
      try {
       float f = std::stoi(argv[i+1]);
       ImageEditorCommand* channel_g_ = new ChannelsFilterCommand
       (image_editor_, 1.0, f, 1.0);
       commands_.push_back(channel_g_);
       i++;
    }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
      }
    } else if (cmd == "-blue") {
        try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* channel_b_ = new ChannelsFilterCommand
        (image_editor_, 1.0, 1.0, f);
        commands_.push_back(channel_b_);
        i++;
      }
      catch(...) {
       std::string err = "invalid argument needs float\n";
        throw err;
    }
    } else if (cmd == "-quantize") {
      try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* quantize_c_ = new QuantizeFilterCommand
        (image_editor_, static_cast<int>(f));
        commands_.push_back(quantize_c_);
        i++;
    }
    catch(...) {
        std::string err = "invalid argument needs int\n";
        throw err;
    }
    } else if (cmd == "-saturate") {
      try {
        float f = std::stoi(argv[i+1]);
      ImageEditorCommand* saturate_c_ =
      new SaturateFilterCommand(image_editor_, f);
      commands_.push_back(saturate_c_);
      i++;
  }
  catch(...) {
      std::string err = "invalid argument needs float\n";
      throw err;
  }
    } else if (cmd == "-threshold") {
      try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* threshold_c_ = new ThresholdFilterCommand
        (image_editor_, f);
        commands_.push_back(threshold_c_);
        i++;
    }
    catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
    }
    } else if (cmd == "-motionblur-n-s") {
      try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* ns_motionblur_ =
        new MotionBlurFilterCommand(image_editor_, f,
        FilterMotionblur::MBLUR_DIR_N_S);
        commands_.push_back(ns_motionblur_);
        i++;
    }
    catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
    }
    } else if (cmd == "-motionblur-ne-sw") {
       try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* nesw_motionblur_ =
        new MotionBlurFilterCommand(image_editor_, f,
        FilterMotionblur::MBLUR_DIR_NE_SW);
          commands_.push_back(nesw_motionblur_);
          i++;
      }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
    }
    } else if (cmd == "-motionblur-e-w") {
       try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* ew_motionblur_ =
        new MotionBlurFilterCommand(image_editor_, f,
          FilterMotionblur::MBLUR_DIR_E_W);
          commands_.push_back(ew_motionblur_);
          i++;
      }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
      }
    } else if (cmd == "-motionblur-nw-se") {
      try {
        float f = std::stoi(argv[i+1]);
        ImageEditorCommand* nwse_motionblur_ =
        new MotionBlurFilterCommand(image_editor_, f,
        FilterMotionblur::MBLUR_DIR_NW_SE);
        commands_.push_back(nwse_motionblur_);
        i++;
        }
      catch(...) {
        std::string err = "invalid argument needs float\n";
        throw err;
    }
    } else {
      throw cmd;
    }
  }}
    catch (std::string error) {
    std::cout << "invalid message" << error;
    help();
}
  for (std::vector<int>::size_type j = 0; j != commands_.size(); j++) {
    commands_[j] -> Execute();
}
}

void CommandLineProcessor::help() {
  std::string help_ =
  std::string("usage: mia infile.png [image processing commands ...]")+
  "outfile.png\n"+
  "infile.png:\tinput image file in png format\n"+
  "outfile.png:\tfilename to use for saving the result\n\n"+
  "image processing comamnds:\n"+
  "-blur r: \tapply a gaussian blur of radius r\n"+
  "-edgedetect: \tapply an edge detection filter\n"+
  "-sharpen r: \tapply a sharpening filter of radius r\n"+
  "-red s: \tscale the red channel by factor s\n"+
  "-green s:\tscale the green channel by factor s\n"+
  "-blue s: \tscale the blue channel by factor s\n"+
  "-quantize n:\tquantize each color channel into n bins\n"+
  "-saturate s: \tsaturate colors by scale factor s\n"+
  "-threshold c: \tthreshold using cutoff value c\n"+
  "-motionblur-n-s r:\tnorth-south motion blur with kernel radius r\n"+
  "-motionblur-e-w r:\teast-west motion blur with kernel radius r\n"+
  "-motionblur-ne-sw r: ne-sw motion blur with kernel radius r\n"+
  "-motionblur-nw-se r: nw-se motion blur with kernel radius r\n";
  std::cout << help_;
}

std::vector<ImageEditorCommand*> CommandLineProcessor::getcmd() {
    return commands_;
}

int CommandLineProcessor::vector_size() {
    return commands_.size();
}
}  // namespace image_tools
