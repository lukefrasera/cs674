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
#include <fstream>

#define PI 3.14159265359

int main(int argc, char *argv[]) {
  float  f_1d[] = {0, 1, 0, 2, 0, 4, 0, 4, 0};

  // Center Spektrum
  for (int i = 0; i < 4; ++i) {
    if ((i+1)%2)
      f_1d[2*i+1] *= -1;
  }

  // Perfrom Forward Transform
  fft(f_1d, 4, -1);

  // Display Result
  for (int i = 0; i < 4 ; ++i) {
    printf("F(%d)_real: %f\n", i+1, f_1d[2*i+1]);
    printf("F(%d)_imag: %f\n", i+1, f_1d[2*i+2]);
  }
  printf("\n");

  // Perfrom Complex Devision // This could be done after to reduce computation
  std::complex<float> complex_num;
  for (int i = 1; i < 9; i += 2) {
    complex_num = std::complex<float>(f_1d[i], f_1d[i+1]);
    complex_num /= 4;
    f_1d[i] = complex_num.real();
    f_1d[i+1] = complex_num.imag();
  }

  // Perfrom Inverse Transfrom
  fft(f_1d, 4, 1);

  // Negate Center Spektrum components
  for (int i = 0; i < 4; ++i) {
    if ((i+1)%2)
      f_1d[2*i+1] *= -1;
  }

  for (int i = 0; i < 4 ; ++i) {
    printf("F(%d)_real: %f\n", i+1, f_1d[2*i+1]);
    printf("F(%d)_imag: %f\n", i+1, f_1d[2*i+2]);
  }
  printf("\n");

  // Sample Cosine Function
  printf("Cosine Sample\n");
  float f_cos[257];
  for (int i = 0; i < 128; ++i) {
    f_cos[2*i+1] = cos(2.0*PI*8.0*(float)(i+1)/128.0);
    f_cos[2*i+2] = 0;
  }

  // Center Spektrum
  for (int i = 0; i < 128; ++i) {
    if ((i+1)%2)
      f_cos[2*i+1] *= -1;
  }

  // Perfrom Forward Transform
  fft(f_cos, 128, -1);

  for (int i = 1; i < 257; i += 2) {
    complex_num = std::complex<float>(f_cos[i], f_cos[i+1]);
    complex_num /= 128.0;
    f_cos[i] = complex_num.real();
    f_cos[i+1] = complex_num.imag();
  }
  for (int i = 0; i < 128 ; ++i) {
    printf("F(%d)_real: %f\n", i+1, f_cos[2*i+1]);
    printf("F(%d)_imag: %f\n", i+1, f_cos[2*i+2]);
  }
  printf("\n");
  // create sinc function

  // import data
  std::ifstream fin;
  float rect[257];
  fin.open("../assignment_03/Rect_128.dat");
  if(fin.is_open()) {
    for (int i = 0; i < 128; ++i) {
      fin >> rect[2*i+1];
      rect[2*i+2] = 0;
    }
    fin.close();
  } else {
    printf("File Not Found\n");
  }

  // Center Spektrum
  for (int i = 0; i < 128; ++i) {
    if ((i+1)%2)
      rect[2*i+1] *= -1;
  }

  // display data
  for ( int i = 0; i < 128; ++i) {
    printf("F(%d)_real: %f\n", (i+1)/*-128/2*/, rect[2*i+1]);
    printf("F(%d)_imag: %f\n", (i+1)/*-128/2*/, rect[2*i+2]);
  }
  // compute FT
  fft(rect, 128, -1);
  for (int i = 1; i < 257; i += 2) {
    complex_num = std::complex<float>(rect[i], rect[i+1]);
    complex_num /= 128.0;
    rect[i] = complex_num.real();
    rect[i+1] = complex_num.imag();
  }

  
  return 0;
}