//"noise_removal.cc"
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
#include "spatial_filtering.h"

#define PI 3.14159265359

int main(int argc, char * argv[]) {
	// import image
  int rows, cols, bytes;
  bool type;

  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[1], image);

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

  // Find Noise in the image

    // compute magnitude image
  float ** f_image = new float*[rows];
  float ** f_grad_x = new float*[rows];
  float ** f_grad_y = new float*[rows];
  for (int i = 0; i < rows; ++i) {
    f_image[i] = new float[cols];
    f_grad_x[i] = new float[cols];
    f_grad_y[i] = new float[cols];
    for (int j = 0; j < cols; ++j) {
      // image.setPixelVal(i, j, log(1.+sqrt(pow(image_real[i+1][j+1], 2.) + pow(image_imag[i+1][j+1], 2.))));
      // printf("Mag:%f\n", log(1.+sqrt(pow(image_real[i+1][j+1], 2.) + pow(image_imag[i+1][j+1], 2.))));
      f_image[i][j] = sqrt(pow(image_real[i+1][j+1], 2.) + pow(image_imag[i+1][j+1], 2.));
      f_grad_x[i][j] = f_image[i][j];
      f_grad_y[i][j] = f_image[i][j];
      // printf("Image Value: %d\n", image.getPixelVal(i,j));
    }
  }
    // Take image gradient
  // img_tools::Point anchor = {1, 1};
  // img_tools::Point size = {3, 3};
  // float ** mask = new float*[size.x];
  // for (int i =0; i< size.x; ++i) {
  //   mask[i] = new float[size.y];
  // }
  // for (int i = 0; i<size.x; ++i) {
  //   for (int j =0; j < size.y; ++j) {
  //     mask[i][j] = img_tools::sobelx[i][j];
  //   }
  // }
  // img_tools::Convolution2Df(f_grad_x, rows, cols, size, mask, anchor, 0);
  // for (int i = 0; i<size.x; ++i) {
  //   for (int j =0; j < size.y; ++j) {
  //     mask[i][j] = img_tools::sobely[i][j];
  //   }
  // }
  // img_tools::Convolution2Df(f_grad_y, rows, cols, size, mask, anchor, 0);
  // delete [] mask;
  //   // Search for local maximum in that are spherical
  // for (int i = 0; i < rows; ++i) {
  //   for (int j = 0; j < cols; ++j) {
  //     f_grad_x[i][j] = abs(f_grad_x[i][j]);
  //   }
  // }
    // Set to zero
  float dist;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      dist = sqrt(pow(i-rows/2,2)+pow(j-cols/2,2)); // Euclidean distance
      if (dist > 34.27 && f_image[i][j] > .0190 && dist < 37.5){
        f_image[i][j] = 0.0;
        // printf("Points set to zero: %d, %d value: %f, i%f\n", i, j, image_real[i][j], image_imag[i][j]);
        image_real[i][j] = 0.0;
        image_imag[i][j] = 0.0;
      }
    }
  }

  img_tools::fft2D(M, N, image_real, image_imag, 1);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
      f_image[i][j] = log(1.0 + sqrt(pow(f_grad_x[i][j],2) + pow(f_grad_y[i][j], 2)));
    }
  }

  img_tools::ReMap(f_image, rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image.setPixelVal(i,j, image_real[i][j]);
    }
  }
  writeImage(argv[2], image);
  return 0;
}
