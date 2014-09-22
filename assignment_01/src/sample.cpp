//"sample.cpp"
//
//  Copyright (c) Luke Fraser 2014
//
//  This file is part of cs674Class.
//
//    cs674Class is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    cs674Class is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with cs674Class.  If not, see <http://www.gnu.org/licenses/>.

#include "sample.h"

namespace img_tools {
enum SubSamples {
  SUB128 = 0,
  SUB64,
  SUB32,
};

ImageType * SubSample(ImageType image, int type) {
  int rows, cols, levels;
  image.getImageInfo(rows, cols, levels);
  if (rows != cols) {
    printf("Error: Image not square - rows do not match columns\n");
    return NULL;
  } else if ( rows != 128 && rows != 256 && rows != 512 && rows != 1024) {
    printf("Error: Not power of 2 or not supported size: %d\n", rows);
    return NULL;
  }
  int sample,size;
  if ( type == SUB128) {
    sample = rows / 128;
    size = 128;
  } else if ( type == SUB64) {
    sample = rows / 64;
    size = 64;
  } else {
    sample = rows/ 32;
    size = 32;
  }

  ImageType * out_image = new ImageType(size, size, levels);
  for (int i=0; i<size; ++i) {
    for (int j=0; j<size; ++j) {
      out_image->setPixelVal(i,j,image.getPixelVal(i*sample, j*sample));
    }
  }
  return out_image;
}
ImageType * ScaleImageSquare256(ImageType * image) {

}
}