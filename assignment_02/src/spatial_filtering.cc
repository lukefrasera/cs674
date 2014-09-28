//"spatial_filtering.cc"
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

#include "spatial_filtering.h"

namespace img_tools {
void Convolution2D(const ImageType &input, ImageType &output, int mask_size,
    float** mask, Point anchor, int boundries) {
  FlipKernel2D(mask, mask_size);
  // anchor = /*new anchor position*/;
  Filter2D(input, output, mask_size, mask, anchor, boundries);
}

void Correlation2D(const ImageType &input, ImageType &output, int mask_size,
    float** mask, Point anchor, int boundries) {
  Filter2D(input, output, mask_size, mask, anchor, boundries);
}

void Filter2D(const ImageType &input, ImageType &output, int size,
    float** kernel, Point anchor, int boundries) {
  int rows, cols, levels;
  input.getImageInfo(rows, cols, levels);
  // For each pixel in the input image
  for (int i=0; i<rows, ++i) {
    for (int j=0; j<cols, ++j) {
      // Perform the convolution
      float sum = 0;
      Point sample;
      for (int k=0; k<size; ++k) {
        for (int l=0; l<size; ++l) {
          // handle image bounds
          sample.x = abs(i+k-anchor.x);
          sample.y = abs(j+l-anchor.y);
          if (sample.x >= cols)
            sample.x = cols - cols % sample.x;
          if (sample.y >= rows)
            sample.y = rows - rows % sample.y;

          sum += (float)input.getPixelVal(sample.x,sample.y)*kernel[k][l];
        }
      }
      output.setPixelVal(i,j,sum);
    }
  }
}
void FlipKernel2D(float** kernel, int size) {
  float value[size][size];
  for (int i=0, i<size; ++i) {
    for (int j=0; j<size; ++j) {
      value[size-i-1][size-j-1] = kernel[i][j];
    }
  }
  for (int i=0, i<size; ++i) {
    for (int j=0; j<size; ++j) {
      kernel[i][j] = value[i][j];
    }
  }
}
} // img_tools
