//"histrogram.cpp"
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
#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include "image.h"
namespace img_tools {
// calculates the histogram of an 8-bit single channel image
float * ImHist(ImageType image);

// generates an 8 bit single channel histogram visualization
ImageType * DisplayHist(float * hist);

float * ImCumHist(const float * hist);

int * InverseMap(const float * in_hist, const float * out_hist);
ImageType * MapImage(const int * map, ImageType image);
} // namespace img_tools
#endif // HISTOGRAM_H_