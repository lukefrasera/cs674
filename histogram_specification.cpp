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
// Include Image Headers
#include "image.h"
#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"
// Inlcude Project Soecific
#include "histogram.h"

int main(int argc, char *argv[]) {
  // Read image file in
  int rows, cols, bytes;
  bool type;
  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType in_image(rows, cols, bytes);
  readImage(argv[1], in_image);

  readImageHeader(argv[2], rows, cols, bytes, type);
  ImageType out_image(rows, cols, bytes);
  readImage(argv[2], out_image);

  // Calclate Histogram
  float * in_hist = img_tools::ImHist(in_image);
  float * out_hist = img_tools::ImHist(out_image);

  float * in_cum_hist = img_tools::ImCumHist(in_hist);
  float * out_cum_hist = img_tools::ImCumHist(out_hist);

  int * map = img_tools::InverseMap(in_cum_hist, out_cum_hist);

  for (int i=0; i<256; ++i) {
    printf("Map%d -> %d\n", i, map[i]);
  }

  ImageType * mapped_image = img_tools::MapImage(map, in_image);

  // store to file
  writeImage(argv[3], *mapped_image);
  return 0;
}