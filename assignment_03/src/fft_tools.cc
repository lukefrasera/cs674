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

namespace img_tools {
void fft2D(int N, int M, float ** real_fuv, float ** imag_fuv, int isign) {
  float * strip = new float[2*N+1];
  if (N == M) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        // Build the strip
        strip[2*j+1] = real_fuv[i][j];
        strip[2*j+2] = imag_fuv[i][j];
      }

      // compute the forurier transform of the strip
      fft(strip, N, isign);
      for (int j = 0; j < N; ++j) {
        // copy strip back to pointers
        real_fuv[i][j] = strip[2*j+1];
        imag_fuv[i][j] = strip[2*j+2];
      }
    }

    // compute transform of columns
    for (int j = 0; j < N; ++j) {
      for (int i = 0; i < N; ++i) {
        // Build the strip
        strip[2*i+1] = real_fuv[i][j];
        strip[2*i+2] = imag_fuv[i][j];
      }
      for ( int k = 0; k < 2*N+1; ++k) {
        printf("Strip:%f\n", strip[k]);
      }
      printf("\n");
      fft(strip, N, isign);
      for (int i = 0; i < N; ++i) {
        // copy strip back to pointers
        real_fuv[i][j] = strip[2*i+1];
        imag_fuv[i][j] = strip[2*i+2];
      }
    }
  } else {
    printf("Image Width and Height are not Equal: M:%d, N:%d\n", M, N);
  }
}
} // namespace img_tools