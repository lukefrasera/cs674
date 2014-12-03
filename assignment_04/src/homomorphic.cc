//"homomorphic.cc"
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
#include <fstream>

int main(int argc, char * argv[]) {
  // import image
  int rows, cols, bytes;
  bool type;
  
  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[1], image);
  int N = cols;

  // Prepare for FT
  float ** image_real = new float*[rows+1];
  float ** image_imag = new float*[rows+1];
  image_real[0] = new float[cols+1];
  image_imag[0] = new float[cols+1];
  // Transfer to floating point
  for (int i = 0; i < rows; ++i) {
    image_real[i+1] = new float[cols+1];
    image_imag[i+1] = new float[cols+1];
    for (int j = 0; j < cols; ++j) {
      image_real[i+1][j+1] = log(image.getPixelVal(i, j)+1);
      image_imag[i+1][j+1] = 0;
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
    }
  }
  img_tools::fft2D(N, N, image_real, image_imag, -1);

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
  img_tools::Filter F(img_tools::Point(N, N));
  img_tools::Filter H(img_tools::Point(N, N));
  img_tools::ComputeButterWorthFilter(H, atof(argv[3]), atof(argv[4]), atof(argv[5]));
  for (int i = 1; i < rows+1; ++i) { 
    for (int j = 1; j < cols+1; ++j) { 
      F.data[i-1][j-1] = std::complex<float>(image_real[i][j], image_imag[i][j]);
    }
  }


  img_tools::MultFilterImage(H, F);

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] = F.data[i-1][j-1].real();
      image_imag[i][j] = F.data[i-1][j-1].imag();
    }
  }

  img_tools::fft2D(N, N, image_real, image_imag, 1);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
    }
  }

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] =  exp(sqrt(pow(image_real[i][j],2) + pow(image_imag[i][j], 2)))-1;
    }
  }
  img_tools::ReMapShift(image_real,N,N);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image.setPixelVal(i,j, static_cast<int>(image_real[i+1][j+1]));     
    }
  }
  writeImage(argv[2], image);
  return 0;
}