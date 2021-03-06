//"sample.cpp"
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
#ifndef SAMPLE_H_
#define SAMPLE_H_
#include "image.h"
#include <stdio.h>
#include <string.h>
namespace img_tools {
ImageType * SubSample(ImageType image, int type);
ImageType * ScaleImageSquare256(ImageType * image);
}
#endif // SAMPLE_H_