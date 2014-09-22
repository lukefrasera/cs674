//"histrogram_main.cpp"
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

// Include I/O
#include <stdio.h>
#include <string.h>
// Include Image Headers
#include "image.h"
#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"

ImageType * quantize(ImageType image, int type) {
  int rows, cols, levels;
  image.getImageInfo(rows, cols, levels);
  ImageType * out_image = new ImageType(rows, cols, levels);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      out_image->setPixelVal(i, j, (256/type) * (image.getPixelVal(i,j) / (256/type)));
    }
  }
  return out_image;
}

int main(int argc, char* argv[]) {
  // Read image file in
  int rows, cols, bytes;
  bool type;
  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType in_image(rows, cols, bytes);
  readImage(argv[1], in_image);

  ImageType * out_image = NULL;
  if (atoi(argv[2]) == 0) {
    out_image = quantize(in_image, 128);
  }
  if (atoi(argv[2]) == 1) {
    out_image = quantize(in_image, 32);
  }
  if (atoi(argv[2]) == 2) {
    out_image = quantize(in_image, 8);
  }
  if (atoi(argv[2]) == 3) {
    out_image = quantize(in_image, 2);
  }

  writeImage(argv[3], *out_image);
  return 0;
}