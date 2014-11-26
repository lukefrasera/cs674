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
namespace img_tools {

#define PI 3.14159265359

Filter::Filter(Point size) {
  data = new std::complex<float>*[size.y];
  for (int i = 0; i < size.y, ++i)
    data[i] = new std::complex<float>[size.x];
}
Filter::~Filter() {
  for (int i = 0; i < size.y; ++i)
    delete [] data[i];
  delete [] data;
}
// Image Tools NameSpace
void ComputeMotionFilter(Filter H, float a, float b, float T) {
  int cols = H.size.x;
  int rows = H.size.y;
  complex<float> A,B,C; // filter equation component mltipliers
  for (int i = 0; i < rows, ++i) {
    for (int j = 0; j < cols, ++j) {
      A = T / (PI * (static_cast<float>(j)*a + static_cast<float>(i)*b));
      B = sin(PI * (static_cast<float>(j)*a +static_cast<float>(i)*b));
      C = exp(complex(0.0, 1) * PI *(static_cast<float>(j)*a +static_cast<float>(i)*b));
      H.data[i][j] = A * B * C;
    }
  }
}

void MultFilterImage(Filter H, Filter F) {
  if (H.size.x != F.size.x && H.size.y != F.size.y) {
    printf("Rows and/or Cols of Filter and Image are different\n");
  } else {
    for (int i = 0; i < H.size.y; ++i) {
      for (int j = 0; j < H.size.x; ++i) {
        F.data[i][j] = H.data[i][j] * F.data[i][j];
      }
    }
  }
}
} // namespace img_tools