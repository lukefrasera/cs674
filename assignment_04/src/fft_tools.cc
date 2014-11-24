//"fft_tools.cc"
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
// Inlcude Project Soecific
#include "fft_tools.h"
#include "fft.h" 
#include <complex>

namespace img_tools {
void fft2D(int N, int M, float ** real_fuv, float ** imag_fuv, int isign) {
  float * strip = new float[2*N+1];
  if (N == M) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        // Build the strip
        strip[2*j+1] = real_fuv[i+1][j+1];
        strip[2*j+2] = imag_fuv[i+1][j+1];
      }

      // compute the forurier transform of the strip
      fft(strip, N, isign);

      for (int j =01; j < N; ++j) {
        // copy strip back to pointers
        real_fuv[i+1][j+1] = strip[2*j+1];
        imag_fuv[i+1][j+1] = strip[2*j+2];
      }
    }
    // compute transform of columns
    for (int j = 0; j < N; ++j) {
      for (int i = 0; i < N; ++i) {
        // Build the strip
        strip[2*i+1] = real_fuv[i+1][j+1];
        strip[2*i+2] = imag_fuv[i+1][j+1];
      }
      fft(strip, N, isign);

      for (int i = 0; i < N; ++i) {
        // copy strip back to pointers
        real_fuv[i+1][j+1] = strip[2*i+1];  
        imag_fuv[i+1][j+1] = strip[2*i+2];
      }
    }
  } else {
    printf("Image Width and Height are not Equal: M:%d, N:%d\n", M, N);
  }
}

void ReMap(float ** image, int w, int h) {
  float min=255, max=0;
  for (int i =0; i<h; ++i) {
    for (int j = 0; j<w; ++j) {
      float pixelval = image[i][j];
      if (min > pixelval) {min = pixelval;};
      if (max < pixelval) {max = pixelval;};
    }
  }
  // compute remap values
  float scale_factor = 255.0f/(max - min);
  float shift_factor = -scale_factor*min;

  for (int i = 0; i<h; ++i) {
    for (int j = 0; j<w; ++j) {
      image[i][j] =  scale_factor * image[i][j] + shift_factor;
    }
  }
}

void ReMapShift(float ** image, int w, int h) {
  float min=255, max=0;
  for (int i =1; i<h+1; ++i) {
    for (int j = 1; j<w+1; ++j) {
      float pixelval = image[i][j];
      if (min > pixelval) {min = pixelval;};
      if (max < pixelval) {max = pixelval;};
    }
  }
  // compute remap values
  float scale_factor = 255.0f/(max - min);
  float shift_factor = -scale_factor*min;

  for (int i = 1; i<h+1; ++i) {
    for (int j = 1; j<w+1; ++j) {
      image[i][j] =  scale_factor * image[i][j] + shift_factor;
    }
  }
}
} // namespace img_tools