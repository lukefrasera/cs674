//"restoration_tools.h"
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

#ifndef RESTORATION_H_
#define RESTORATION_H_

#include "fft.h"
#include "fft_tools.h"
#include <complex>
#include <math.h>
#include <stdio.h>
// #include <string.h>

namespace img_tools {

class Point {
public:
  int x,y;
  Point(int x_, int y_) {
    x = x_;
    y = y_;
  }
};
class Filter {
public:
  // Filter();
  Filter(Point size);
  // ~Filter();

  std::complex<float> ** data;
  Point size;
};

// Image Tools NameSpace
void ComputeMotionFilter(Filter H, float a, float b, float T);
void MultFilterImage(Filter H, Filter F);
void ComputeButterWorthFilter(Filter H, float lamnda_low, float lamnda_high, float d_not);
void ExtendImagef(float ** &image, int rows, int cols, int N);
void InverseFiltering(Filter H, Filter F);
void WienerFiltering(Filter H, Filter F, float K);
float box_muller(float m, float s);
} // namespace img_tools
#endif // RESTORATION_H_