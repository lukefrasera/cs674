//"restoration_tools.cc"
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
#include "restoration_tools.h"
#include <complex>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
namespace img_tools {

#define PI 3.14159265359


Filter::Filter(Point size_): size(size_.x,size_.y){
  data = new std::complex<float>*[size.y];
  for (int i = 0; i < size.y; ++i){
    data[i] = new std::complex<float>[size.x];
  }
}
// Filter::~Filter() {
//   for (int i = 0; i < size.y; ++i)
//     delete [] data[i];
//   delete [] data;
// }
// Image Tools NameSpace
void ComputeMotionFilter(Filter H, float a, float b, float T) {
  int cols = H.size.x;
  int rows = H.size.y;
  std::complex<float> A,B,C; // filter equation component mltipliers
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      A = T / (PI * (static_cast<float>(j-cols/2) / 2.0f * a + static_cast<float>(i-cols/2) / 2.0f * b));
      B = sin(PI * (static_cast<float>(j-cols/2) / 2.0f * a +static_cast<float>(i-cols/2) / 2.0f * b));
      C = exp(std::complex<float>(0.0, 1) * static_cast<float>(PI) * (static_cast<float>(j-cols/2) / 2.0f * a +static_cast<float>(i-cols/2) / 2.0f * b));
      H.data[i][j] = (A * B * C);
      if ((i-cols/2) == -(j-cols/2))
        H.data[i][j] = std::complex<float>(1.0f,0.0f);
      // if (H.data[i][j].real() < .0001f)
        // H.data[i][j] = std::complex<float>(0.0001f,H.data[i][j].imag());
      // if (H.data[i][j].imag() < .0001f)
        // H.data[i][j] = std::complex<float>(H.data[i][j].real(),0.0001f);
    }
  }
  H.data[cols/2][cols/2]=std::complex<float>(1.0,0.0);
}

void InverseFiltering(Filter H, Filter F) {
  int cols = H.size.x;
  int rows = H.size.y;
  std::complex<float> h_inv;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      h_inv = 1.0f / H.data[i][j];
      if (h_inv.real() < 1000.0f && h_inv.imag() < 1000.0f) {
        F.data[i][j] = F.data[i][j] * h_inv;
      } else {
        F.data[i][j] = std::complex<float>(0.0f,0.0f);
      }
      // printf("F: %f, i%f\n", F.data[i][j].real(), F.data[i][j].imag());
    }
  }
}

void WienerFiltering(Filter H, Filter F, float K) {
  int cols = H.size.x;
  int rows = H.size.y;
  std::complex<float> h_val;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      h_val = pow(sqrt(pow(H.data[i][j],2)),2);
      F.data[i][j] = h_val / (h_val + K) * F.data[i][j] / H.data[i][j];
    }
  }
}

void ComputeButterWorthFilter(Filter H, float lamnda_low, float lamnda_high, float d_not) {
  int cols = H.size.x;
  int rows = H.size.y;
  float D,C;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      D = sqrt(pow(i-cols/2,2)+pow(j-cols/2,2));
      C = pow(d_not/D,2);
      H.data[i][j] = lamnda_low + lamnda_high / (1.0f + C);
    }
  }
}

void ExtendImagef(float ** &image, int rows, int cols, int N) {
  float ** temp = new float*[N];
  for (int i = 0; i < N; ++i) {
    temp[i] = new float[N];
    memset(temp[i], 0, N*sizeof(float));
    if (i < rows)
      memcpy(temp[i], image[i], cols*sizeof(float));
  }
  // delete old memory
  for (int i = 0; i < rows; ++i)
    delete [] image[i];
  delete [] image;
  image = temp;
}

void MultFilterImage(Filter H, Filter F) {
  if (H.size.x != F.size.x && H.size.y != F.size.y) {
    printf("Rows and/or Cols of Filter and Image are different\n");
  } else {
    for (int i = 0; i < H.size.y; ++i) {
      for (int j = 0; j < H.size.x; ++j) {
        F.data[i][j] *= H.data[i][j];
      }
    }
  }
}

// extern float ranf();  ranf() is uniform in 0..1 

float box_muller(float m, float s) {  /* normal random variate generator */
  /* mean m, standard deviation s */
  float x1, x2, w, y1;
  static float y2;
  static int use_last = 0;

  if (use_last) {          /* use value from previous call */
    y1 = y2;
    use_last = 0;
  } else {
    do {
      x1 = 2.0 * (static_cast<double>(rand())/RAND_MAX) - 1.0;
      x2 = 2.0 * (static_cast<double>(rand())/RAND_MAX) - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );

    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;
    use_last = 1;
  }
  // printf("Rand Number: %f\n", static_cast<double>(rand())/RAND_MAX);
  return( m + y1 * s );
}
} // namespace img_tools