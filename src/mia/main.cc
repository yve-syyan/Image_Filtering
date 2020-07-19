/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "mia/command_line_processor.h"
#include "mia/mia_app.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    // command line mode
    image_tools::CommandLineProcessor cmd_processor;
    cmd_processor.ProcessCommandLine(argc, argv);
  } else {
    // gui mode
    image_tools::MiaApp gui(1280, 720, image_tools::ColorData(1, 1, 1));
    // Run returns when the user closes the graphics window.
    gui.Run();
  }
}
