/**
* @copyright 2018 3081 Staff, All rights reserved.
*/

#include "imagetools/mask_factory.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace image_tools {

FloatMatrix* MaskFactory::CreateConstantMask(float radius) {
  int ctr = ceil(radius);  // center of the mask is at coordinates (ctr,ctr)
  int size = 2 * ctr + 1;  // mask has height=size and width=size
  FloatMatrix* mask = new FloatMatrix(size, size);

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      float hyp = sqrt((x - ctr) * (x - ctr) + (y - ctr) * (y - ctr));

      if (hyp <= radius) {
        mask->set_value(x, y, 1.0);
      } else {
        mask->set_value(x, y, 0.0);
      }
    }
  }
  return mask;
}

FloatMatrix* MaskFactory::CreateOvalMask(float radius, float angle,
                                         float ratio) {
  int ctr = ceil(radius);  // center of the mask is at coordinates (ctr,ctr)
  int size = 2 * ctr + 1;  // mask has height=size and width=size
  FloatMatrix* mask = new FloatMatrix(size, size);

  float a = radius;
  float b = ratio * radius;
  float theta = angle / 180.0 * M_PI;

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      float h =
          powf((x - ctr) * cos(theta) + (y - ctr) * sin(theta), 2) /
              powf(a, 2) +
          powf((x - ctr) * sin(theta) - (y - ctr) * cos(theta), 2) / powf(b, 2);
      if (h < 1) {
        mask->set_value(x, y, 1.0);
      } else {
        mask->set_value(x, y, 0.0);
      }
    }
  }
  return mask;
}

FloatMatrix* MaskFactory::CreateLinearFalloffMask(float radius) {
  int ctr = ceil(radius);  // center of the mask is at coordinates (ctr,ctr)
  int size = 2 * ctr + 1;  // mask has height=size and width=size
  FloatMatrix* mask = new FloatMatrix(size, size);

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      float hyp = sqrt((x - ctr) * (x - ctr) + (y - ctr) * (y - ctr));

      if (hyp <= radius) {
        mask->set_value(x, y, 1.0 - hyp / radius);
      } else {
        mask->set_value(x, y, 0.0);
      }
    }
  }
  return mask;
}

FloatMatrix* MaskFactory::CreateBullseyeMask(float radius, float linewidth) {
  int ctr = ceil(radius);  // center of the mask is at coordinates (ctr,ctr)
  int size = 2 * ctr + 1;  // mask has height=size and width=size
  FloatMatrix* mask = new FloatMatrix(size, size);

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      float hyp = sqrt((x - ctr) * (x - ctr) + (y - ctr) * (y - ctr));

      // ((w/in inner circle) || (inside outer ring))
      if ((hyp <= linewidth) ||
          ((hyp <= radius) && (radius - hyp <= linewidth))) {
        mask->set_value(x, y, 1.0);
      } else {
        mask->set_value(x, y, 0.0);
      }
    }
  }
  return mask;
}

}  // namespace image_tools

