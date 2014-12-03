//"motionblur.cc"
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

  img_tools::Filter F(img_tools::Point(N, N));
  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      F.data[i-1][j-1] = std::complex<float>(image_real[i][j], image_imag[i][j]);
    }
  }

  // compute H(u,v)
  img_tools::Filter H(img_tools::Point(cols,rows));
  img_tools::ComputeMotionFilter(H, 0.1, 0.1, 1);

  ImageType filter(rows, cols, bytes);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      filter.setPixelVal(i, j, abs(static_cast<int>(H.data[i][j].real() * 250)));
    }
  }
  writeImage(const_cast<char*>("filter.pgm"), filter);

  // complex multiplication
  img_tools::MultFilterImage(H, F);

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] = F.data[i-1][j-1].real();
      image_imag[i][j] = F.data[i-1][j-1].imag();
    }
  }
  // compute inverse
  img_tools::fft2D(M, N, image_real, image_imag, 1);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
    }
  }
  // img_tools::ReMap(image_real, N, N);
  // save image
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j == 0) {
        image.setPixelVal(i,j, static_cast<int>(image_real[i+1][j+2]));
      } else {
        image.setPixelVal(i,j, static_cast<int>(image_real[i+1][j+1]));
      }
        
    }
  }
  writeImage(argv[2], image);

  // perform inverse Filtering /////////////////////////////////////////////////

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
      image_imag[i+1][j+1] = 0;
    }
  }
  img_tools::fft2D(M, N, image_real, image_imag, -1);

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) {
      complex_num = std::complex<float>(image_real[i][j], image_imag[i][j]);
      complex_num /= N*N;
      image_real[i][j] = complex_num.real();
      image_imag[i][j] = complex_num.imag();
    }
  }

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      F.data[i-1][j-1] = std::complex<float>(image_real[i][j], image_imag[i][j]);
    }
  }
  // img_tools::InverseFiltering(H, F);
  img_tools::WienerFiltering( H, F, atof(argv[6]));
  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] = F.data[i-1][j-1].real();
      image_imag[i][j] = F.data[i-1][j-1].imag();
    }
  }

  img_tools::fft2D(M, N, image_real, image_imag, 1);
  // img_tools::ReMapSllhift(image_real, rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
      // printf("Image Value: %f\n", image_real[i+1][j+1]);
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image.setPixelVal(i,j, abs(static_cast<int>(image_real[i+1][j+1])));
    }
  }
  writeImage(argv[3], image);

  // Add Noise
  srand((time(NULL)));
  readImage(argv[1], image);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image_real[i+1][j+1] = image.getPixelVal(i, j);
      image_imag[i+1][j+1] = 0;
      image_real[i+1][j+1] = image_real[i+1][j+1];
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
    }
  }

  img_tools::fft2D(M, N, image_real, image_imag, -1);

  // Perfrom complex division
  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) {
      complex_num = std::complex<float>(image_real[i][j], image_imag[i][j]);
      complex_num /= N*N;
      image_real[i][j] = complex_num.real();
      image_imag[i][j] = complex_num.imag();
    }
  }

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      F.data[i-1][j-1] = std::complex<float>(image_real[i][j], image_imag[i][j]);
    }
  }


  // complex multiplication
  img_tools::MultFilterImage(H, F);

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] = F.data[i-1][j-1].real();
      image_imag[i][j] = F.data[i-1][j-1].imag();
    }
  }
  // compute inverse
  img_tools::fft2D(M, N, image_real, image_imag, 1);

  float min = 0.0f, max = 255.0f;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;

      image_real[i+1][j+1] = image_real[i+1][j+1] + img_tools::box_muller(0.0f, 1000);
      if (image_real[i+1][j+1] > max)
        max = image_real[i+1][j+1];
      if (image_real[i+1][j+1] < min)
        min = image_real[i+1][j+1];
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image_real[i+1][j+1] = (image_real[i+1][j+1] - min)/(max-min)*255;
    }
  }
  // img_tools::ReMapShift(image_real, N, N);
  // save image
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j == 0) {
        image.setPixelVal(i,j, static_cast<int>(image_real[i+1][j+2]));
      } else {
        image.setPixelVal(i,j, static_cast<int>(image_real[i+1][j+1]));
      }
        
    }
  }
  writeImage(argv[4], image);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
      image_imag[i+1][j+1] = 0;
    }
  }
  img_tools::fft2D(M, N, image_real, image_imag, -1);

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) {
      complex_num = std::complex<float>(image_real[i][j], image_imag[i][j]);
      complex_num /= N*N;
      image_real[i][j] = complex_num.real();
      image_imag[i][j] = complex_num.imag();
    }
  }

  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      F.data[i-1][j-1] = std::complex<float>(image_real[i][j], image_imag[i][j]);
    }
  }
  // img_tools::InverseFiltering(H, F);
  img_tools::WienerFiltering( H, F, atof(argv[6]));
  for (int i = 1; i < N+1; ++i) {
    for (int j = 1; j < N+1; ++j) { 
      image_real[i][j] = F.data[i-1][j-1].real();
      image_imag[i][j] = F.data[i-1][j-1].imag();
    }
  }

  img_tools::fft2D(M, N, image_real, image_imag, 1);
  // img_tools::ReMapSllhift(image_real, rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if ((i+1 + j+1)%2)
        image_real[i+1][j+1] *= -1;
      // printf("Image Value: %f\n", image_real[i+1][j+1]);
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      image.setPixelVal(i,j, abs(static_cast<int>(image_real[i+1][j+1])));
    }
  }
  writeImage(argv[5], image);
  return 0;
}