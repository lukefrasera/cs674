//"histogram.cpp"
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
#include "histogram.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
namespace img_tools {
float * ImHist(ImageType image) {
  int rows, cols, bytes;
  image.getImageInfo(rows, cols, bytes);
  if (bytes > 256) {
    printf("Only 8 Bit single Channel Image accepted: input:%d\n", bytes);
    return NULL;
  }
  int total_pixels = rows * cols;
  float * hist = new float[256];
  memset(hist, 0, sizeof(float)*256);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      if(image.getPixelVal(i,j) < 256 && image.getPixelVal(i,j) >= 0)
        hist[image.getPixelVal(i,j)] += 1.0f/(float)total_pixels;
    }
  }
  return hist;
}

float * ImCumHist(const float * hist) {
  float * cumhist;
  float sum = 0;
  cumhist = new float[256];
  memset(cumhist, 0, sizeof(float)*256);
  for (int i=0; i<256; ++i) {
    sum += hist[i];
    cumhist[i] = sum;
  }
  return cumhist;
}

int * InverseMap(const float * in_hist, const float * out_hist) {
  int * map = new int[256];
  float var = 0, prev_var = 256;

  for (int i=0; i<256; ++i) {
    for(int j=0; j<256; ++j) {
      var = std::abs(out_hist[j] - in_hist[i]);
      printf("Difference[%d]:-%f\n", i, var);
      if (var > prev_var) {
        map[i] = j-1;
        break;
      } else if (j==255) {
        map[i] = 255;
      }
      prev_var = var;
    }
    prev_var = 256;
  }
  return map;
}

ImageType * MapImage(const int * map, ImageType image) {
  int rows, cols, bytes;
  image.getImageInfo(rows, cols, bytes);
  ImageType * out_image = new ImageType(rows, cols, bytes);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      out_image->setPixelVal(i, j, map[image.getPixelVal(i,j)]);
    }
  }
  return out_image;
}

ImageType * DisplayHist(float * hist) {
  // Zero image
  ImageType * hist_img = new ImageType(256,256,256);
  float sum = 0.0f;
  for (int i=0; i<256; ++i) {
      printf("%f\n", hist[i]);
      sum += hist[i];
    for ( int j=0; j<256; ++j) {
      if (i<=(hist[j]*255)) {
        hist_img->setPixelVal(i,j,0);
      } else {
        hist_img->setPixelVal(i,j,255);
      }
    }
  }
  printf("sum:%f\n", sum);
  return hist_img;
}
} // namespace img_tools