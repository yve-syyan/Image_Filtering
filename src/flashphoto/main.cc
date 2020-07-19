/**
* @copyright 2018 3081 Staff, All rights reserved.
*/


#include "imagetools/image_editor.h"
#include "flashphoto/flashphoto_app.h"

int main() {
  image_tools::FlashPhotoApp app(1280, 720, image_tools::ColorData(1, 1, 1));

  // Run returns when the user closes the graphics window.
  app.Run();
  exit(0);
}
