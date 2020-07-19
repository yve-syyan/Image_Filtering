/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/pixel_buffer.h"
#include <mingfx.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "imageio/image_manager.h"
#include "imagetools/color_data.h"

using std::cerr;
using std::endl;
namespace image_tools {

PixelBuffer::PixelBuffer(int w, int h, ColorData background_color)
    : width_(w), height_(h), background_color_(background_color) {
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      pixels_.push_back(background_color.red());
      pixels_.push_back(background_color.green());
      pixels_.push_back(background_color.blue());
      pixels_.push_back(background_color.alpha());
    }
  }
}

PixelBuffer::PixelBuffer(const std::string &filename)
    : width_(0.0), height_(0.0), background_color_(ColorData(1, 1, 1)) {
  LoadFromFile(filename);
}

PixelBuffer::PixelBuffer(const PixelBuffer &rhs)
    : PixelBuffer(rhs.width_, rhs.height_, rhs.background_color_) {
  std::copy(rhs.pixels_.begin(), rhs.pixels_.end(), pixels_.begin());
}

PixelBuffer::~PixelBuffer() {}

ColorData PixelBuffer::pixel(int x, int y) const {
  ColorData pixel_data;

  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "pixel(x,y): out of range: " << x << " " << y << endl;
  } else {
    int index = 4 * (x + width_ * y);
    pixel_data = ColorData(pixels_[index + 0], pixels_[index + 1],
                           pixels_[index + 2], pixels_[index + 3]);
  }
  return pixel_data;
}

void PixelBuffer::set_pixel(int x, int y, const ColorData &new_pixel) {
  if ((x < 0) || (x >= width_) || (y < 0) || (y >= height_)) {
    cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
  } else {
    int index = 4 * (x + width_ * y);  // x + width*(height-(y+1));
    pixels_[index + 0] = new_pixel.red();
    pixels_[index + 1] = new_pixel.green();
    pixels_[index + 2] = new_pixel.blue();
    pixels_[index + 3] = new_pixel.alpha();
  }
}

PixelBuffer &PixelBuffer::operator=(const PixelBuffer &rhs) {
  /* Check for self-assignment! */
  if (this == &rhs) {
    return *this;
  }
  this->width_ = rhs.width_;
  this->height_ = rhs.height_;
  this->pixels_ = rhs.pixels_;
  this->background_color_ = rhs.background_color_;

  return *this;
} /* operator=() */

void PixelBuffer::Resize(int new_width, int new_height) {
  PixelBuffer tmp(new_width, new_height, background_color_);
  for (int y = 0; y < new_height; y++) {
    for (int x = 0; x < new_width; x++) {
      if ((x < width_) && (y < height_)) {
        tmp.set_pixel(x, y, pixel(x, y));
      } else {
        tmp.set_pixel(x, y, background_color_);
      }
    }
  }
  *this = tmp;
}

void PixelBuffer::SaveToFile(const std::string &filename) {
  imageio::Image* image = new imageio::Image(width_, height_, 4);
  for (int y = 0; y < height_; y++) {
      for (int x = 0; x < width_; x++) {
           image -> SetFloatValue(x, y, 0, pixel(x, y).red());
           image -> SetFloatValue(x, y, 1, pixel(x, y).green());
           image -> SetFloatValue(x, y, 2, pixel(x, y).blue());
           image -> SetFloatValue(x, y, 3, pixel(x, y).alpha());
       }
    }
    imageio::ImageManager::instance().SaveToFile(filename, *image);
    delete image;
}

void PixelBuffer::LoadFromFile(const std::string &filename) {
  imageio::Image* image =
  imageio::ImageManager::instance().LoadFromFile(filename);

  if (mingfx::Platform::FileExists(filename)) {
    if (image -> Pixels() == NULL) {
       std :: cout << "Pixelbuffer nonexistant" << filename
      << std::endl;
    } else {
    Resize(image -> Width(), image -> Height());
      for (int y = 0; y < image->Height(); y++) {
      for (int x = 0; x < image -> Width(); x++) {
        int index = 4 * (x + width_ * y);  // x + width*(height-(y+1));
        pixels_[index + 0] = image->FloatValue(x, y, 0);
        pixels_[index + 1] = image->FloatValue(x, y, 1);
        pixels_[index + 2] = image->FloatValue(x, y, 2);
        pixels_[index + 3] = image->FloatValue(x, y, 3);
    }
  }
  } } else {
    std::cout << "file does not exist" << std::endl;
  }
}

bool operator==(const PixelBuffer &a, const PixelBuffer &b) {
  if ((a.width() != b.width()) || (a.height() != b.height())) {
    return false;
  } else {
    // check the actual pixels
    for (int y = 0; y < a.height(); y++) {
      for (int x = 0; x < a.width(); x++) {
        if (a.pixel(x, y) != b.pixel(x, y)) {
          return false;
        }
      }
    }
    return true;
  }
}

bool operator!=(const PixelBuffer &a, const PixelBuffer &b) {
  return !(a == b);
}

} /* namespace image_tools */
