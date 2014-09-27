//"spatial_filtering.h"
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

#ifndef SPATIAL_FILTERING_H_
#define SPATIAL_FILTERING_H_

namespace img_tools {
enum Boundries {
  MIRROR=0,
  ZERO,
};

struct Point {
  int x,y;
};

void Convolution2D(const ImageType &input, ImageType &output, int mask_size,
    float** mask, int anchor, int boundries);
void Correlation2D(const ImageType &input, ImageType &output, int mask_size,
    float** mask, int anchor, int boundries);
void Filter2D(const ImageType &input, ImageType &output, int size,
    float** kernel, int anchor, int boundries);
void FlipKernel2D(float** kernel, int size);
}
#endif // SPATIAL_FILTERING_H_