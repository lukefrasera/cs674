//"convolution_freq.cc"
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
#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"
#include <stdio.h>
#include "fft.h"
#include "fft_tools.h"
#include <complex>
#include <math.h>
#include "restoration_tools.h"
#include "spatial_filtering.h"
#include <fstream>

int main(int argc, char * argv[]) {
  // import image
  int rows, cols, bytes;
  bool type;
  
  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[1], image);
  int N = cols;
  int M = 512;
  // Load Filter

  float ** image_real = new float*[M+1];
  float ** image_imag = new float*[M+1];
  image_real[0] = new float[M+1];
  image_imag[0] = new float[M+1];
  float ** mask_real = new float*[M+1];
  float ** mask_imag = new float*[M+1];
  mask_real[0] = new float[M+1];
  mask_imag[0] = new float[M+1];
  // Transfer to floating point
  for (int i = 0; i < M; ++i) {
    image_real[i+1] = new float[M+1];
    image_imag[i+1] = new float[M+1];
    mask_real[i+1] = new float[M+1];
    mask_imag[i+1] = new float[M+1];
    image_real[i][0] = 0;
    for (int j = 0; j < M; ++j) {
      if ( i < cols && j < cols) {
        image_real[i+1][j+1] = image.getPixelVal(i, j);
      } else {
        image_real[i+1][j+1] = 0;
      }
      image_imag[i+1][j+1] = 0;
      mask_imag[i+1][j+1] = 0;
      mask_real[i+1][j+1] = 0;
      if ((i+1 + j+1)%2){
        image_real[i+1][j+1] *= -1;
      }
    }
  }

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mask_real[i + M/2-1][j + M/2-1] = img_tools::sobely[i][j];
      if ((i + M/2-1 + j + M/2-1)%2)
        mask_real[i + M/2-1][j + M/2-1] *= -1;
    }
  }

  img_tools::fft2D(M, M, image_real, image_imag, 1);
  img_tools::fft2D(M, M, mask_real, mask_imag, 1);

  // Perfrom complex division
  std::complex<float> complex_num;
  for (int i = 1; i < M+1; ++i) {
    for (int j = 1; j < M+1; ++j) {
      complex_num = std::complex<float>(image_real[i][j], image_imag[i][j]);
      complex_num /= M*M;
      image_real[i][j] = complex_num.real();
      image_imag[i][j] = complex_num.imag();
    }
  }

  for (int i = 1; i < M+1; ++i) {
    for (int j = 1; j < M+1; ++j) {
      complex_num = std::complex<float>(mask_real[i][j], mask_imag[i][j]);
      complex_num /= M*M;
      mask_real[i][j] = complex_num.real();
      mask_imag[i][j] = complex_num.imag();
    }
  }

  img_tools::Filter F(img_tools::Point(M, M));
  img_tools::Filter H(img_tools::Point(M, M));
  for (int i = 1; i < rows+1; ++i) { 
    for (int j = 1; j < cols+1; ++j) { 
      F.data[i-1][j-1] = std::complex<float>(image_real[i][j], image_imag[i][j]);
      H.data[i-1][j-1] = std::complex<float>(mask_real[i][j], mask_imag[i][j]);
    }
  }

  img_tools::MultFilterImage(H, F);

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] = F.data[i-1][j-1].real();
      image_imag[i][j] = F.data[i-1][j-1].imag();
    }
  }

  img_tools::fft2D(M, M, image_real, image_imag, -1);
  img_tools::fft2D(M, M, mask_real, mask_imag, -1);
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < M; ++j) {
      if ((i+1 + j+1)%2){
        image_real[i+1][j+1] *= -1;
        mask_real[i+1][j+1] *= -1;
      }
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image.setPixelVal(i,j, static_cast<int>(image_real[i+1][j+1]));
    }
  }
  writeImage(argv[2], image);
  return 0;
}