//"experiment1.cc"
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
#include "fft.h"
#include <stdio.h>
#include <complex>
#include <math.h>

#define PI 3.14159265359

int main(int argc, char *argv[]) {
  // import image

  // Transfer to floating point

  // Set imaginery numbers to 0

  // Center Spektrum

  // compute 2D tranform
  img_tools::fft2D(M, N, image_real, image_imag, -1);

  // Perfrom complex division

  // computer inverse tranform
  img_tools::fft2D(M, N, image,_real, image_imag, 1);

  // save image to disk
  return 0;
}