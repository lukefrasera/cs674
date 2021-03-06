//"experiment2.cc"
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
#include "fft.h"
#include "fft_tools.h"
#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"
#include <stdio.h>
#include <complex>
#include <math.h>

#define PI 3.14159265359

int main(int argc, char *argv[]) {
  // import image
  int rows, cols, bytes;
  bool type;

  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[1], image);

  float ** image_real = new float*[rows+1];
  float ** image_imag = new float*[rows+1];
  image_real[0] = new float[cols+1];
  image_imag[0] = new float[cols+1];
  // Transfer to floating point
  for (int i = 0; i < rows; ++i) {
    image_real[i+1] = new float[cols+1];
    image_imag[i+1] = new float[cols+1];
    for (int j = 0; j < cols; ++j) {
      image_real[i+1][j+1] = image.getPixelVal(i, j);
      image_imag[i+1][j+1] = 0;
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
    }
  }

  // compute 2D tranform
  int N = rows;
  int M = cols;
  img_tools::fft2D(M, N, image_real, image_imag, -1);

  // Perfrom complex division
  std::complex<float> complex_num;
  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) {
      complex_num = std::complex<float>(image_real[i][j], image_imag[i][j]);
      complex_num /= N*N;
      image_real[i][j] = complex_num.real();
      image_imag[i][j] = complex_num.imag();
    }
  }

  if (atoi(argv[3])==0) {
    // Set phase to zero
    for (int i = 1; i < N+1; ++i) {
      for (int j = 1; j < N+1; ++j) {
        image_real[i][j] = sqrt(pow(image_real[i][j],2) + pow(image_imag[i][j],2));
        image_imag[i][j] = 0;
      }
    }
  } else {
    // set magnitude to 1
    float theta;
    for (int i = 1; i < N+1; ++i) {
      for (int j = 1; j < N+1; ++j) {
        theta = atan2(image_imag[i][j],image_real[i][j]);
        image_real[i][j] = cos(theta);
        image_imag[i][j] = sin(theta);
      }
    }
  }
  // computer inverse tranform
  img_tools::fft2D(M, N, image_real, image_imag, 1);

  if (atoi(argv[3])==0) {
    for (int i = 1; i < N+1; ++i) {
      for (int j = 1; j < N+1; ++j) {
        if ((i + j)%2)
          image_real[i][j] *= -1;
        image_real[i][j] = abs(image_real[i][j])<255.0 ? image_real[i][j] : 255.0;
      }
    }
    // img_tools::ReMapShift(image_real, N, N);
  } else {
    for (int i = 1; i < N+1; ++i) {
      for (int j = 1; j < N+1; ++j) {
        // image_real[i][j] = abs(image_real[i][j]);
        if ((i + j)%2)
          image_real[i][j] *= -1;
      }
    }
    img_tools::ReMapShift(image_real, N, N);
  }

  // save image to disk
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image.setPixelVal(i, j, abs(image_real[i+1][j+1]));
      // printf("Image Value: %d\n", image.getPixelVal(i,j));
    }
  }
  writeImage(argv[2], image);
  return 0;
}