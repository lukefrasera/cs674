//" spatial_filtering.cc"
//
//   Copyright (c) Luke Fraser 2014
//
//   This file is part of cs674Class.
//
//     cs674Class is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     cs674Class is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with cs674Class.  If not, see <http://www.gnu.org/licenses/>.

#include "spatial_filtering.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
namespace img_tools {
void Convolution2D(ImageType &input, ImageType &output, Point mask_size,
    float** mask, Point anchor, int boundries) {
  FlipKernel2D(mask, mask_size);
  // anchor = /*new anchor position*/;
  Filter2D(input, output, mask_size, mask, anchor, boundries);
}

void Convolution2Df(float** input, int rows, int cols, Point mask_size,
    float** mask, Point anchor, int boundries) {
  FlipKernel2D(mask, mask_size);
  // anchor = /*new anchor position*/;
  Filter2Df(input, rows, cols, mask_size, mask, anchor, boundries);
}

void Correlation2D(ImageType &input, ImageType &output, Point mask_size,
    float** mask, Point anchor, int boundries) {
  Filter2D(input, output, mask_size, mask, anchor, boundries);
}

void Correlation2Df(float** input, int rows, int cols, Point mask_size,
    float** mask, Point anchor, int boundries) {
  Filter2Df(input, rows, cols, mask_size, mask, anchor, boundries);
}

void Filter2D(ImageType &input, ImageType &output, Point size,
    float** kernel, Point anchor, int boundries) {
  int rows, cols, levels;
  input.getImageInfo(rows, cols, levels);
  // For each pixel in the input image
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // Perform the convolution
      float sum = 0;
      Point sample;
      for (int k = 0; k < size.x; ++k) {
        for (int l = 0; l < size.y; ++l) {
          // handle image bounds
          sample.x = abs(i + k - anchor.x);
          sample.y = abs(j + l - anchor.y);
          if (sample.x >= rows)
            sample.x = rows-1 - sample.x % rows;
          if (sample.y >= cols)
            sample.y = cols-1 - sample.y % cols;
          sum += static_cast<float>(input.getPixelVal(sample.x, sample.y)) * kernel[k][l];
        }
      }
      output.setPixelVal(i, j, sum);
      // printf("Sum: %f\n", sum);
    }
  }
}

void Filter2Df(float** input, int rows, int cols, Point size,
    float** kernel, Point anchor, int boundries) {

  float ** output  = new float*[rows];
  for (int i = 0; i < rows; ++i)
    output[i] = new float[cols];
  // For each pixel in the input image
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // Perform the convolution
      float sum = 0;
      Point sample;
      for (int k = 0; k < size.x; ++k) {
        for (int l = 0; l < size.y; ++l) {
          // handle image bounds
          sample.x = abs(i + k - anchor.x);
          sample.y = abs(j + l - anchor.y);
          if (sample.x >= rows)
            sample.x = rows-1 - sample.x % rows;
          if (sample.y >= cols)
            sample.y = cols-1 - sample.y % cols;
          sum += input[sample.x][sample.y] * kernel[k][l];
        }
      }
      output[i][j] = sum;
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      input[i][j] = output[i][j];
    }
    delete [] output[i];
  }
  delete [] output;
}

void MedianFilter(ImageType &input, ImageType &output, Point size, Point anchor, int boundries) {
  int rows, cols, levels;
  input.getImageInfo(rows, cols, levels);
  // For each pixel in the input image
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      // Perform the convolution
      std::vector<int> values;
      Point sample;
      for (int k = 0; k < size.x; ++k) {
        for (int l = 0; l < size.y; ++l) {
          // handle image bounds
          sample.x = abs(i + k - anchor.x);
          sample.y = abs(j + l - anchor.y);
          if (sample.x >= rows)
            sample.x = rows-1 - sample.x % rows;
          if (sample.y >= cols)
            sample.y = cols-1 - sample.y % cols;
          values.push_back(input.getPixelVal(sample.x, sample.y));
        }
      }
      // sort values
      std::sort(values.begin(), values.end());
      output.setPixelVal(i, j, values[values.size()/2]);
      values.clear();
    }
  }
}

void FlipKernel2D(float** kernel, Point size) {
  float value[size.x][size.y];
  for (int i = 0; i < size.x; ++i) {
    for (int j = 0; j < size.y; ++j) {
      value[size.x-i-1][size.y-j-1] = kernel[i][j];
    }
  }
  for (int i = 0; i < size.x; ++i) {
    for (int j = 0; j < size.y; ++j) {
      kernel[i][j] = value[i][j];
    }
  }
}

void ReMap( ImageType &image) {
  int rows, cols, levels;
  image.getImageInfo(rows, cols, levels);
  int min=255, max=0;
  for (int i =0; i<rows; ++i) {
    for (int j = 0; j<cols; ++j) {
      int pixelval = image.getPixelVal(i,j);
      if (min > pixelval) {min = pixelval;};
      if (max < pixelval) {max = pixelval;};
    }
  }
  // compute remap values
  float scale_factor = 255.0f/(max - min);
  float shift_factor = -scale_factor*static_cast<float>(min);

  for (int i = 0; i<rows; ++i) {
    for (int j = 0; j<cols; ++j) {
      image.setPixelVal(i,j, scale_factor * image.getPixelVal(i,j) + shift_factor);
    }
  }
}

void ImageToMask(ImageType image, float** mask) {
  int rows, cols, levels;

  image.getImageInfo(rows, cols, levels);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      mask[i][j] = 1.0f/((static_cast<float>(image.getPixelVal(i,j)) * static_cast<float>(rows*cols))) * 1000;
      if (image.getPixelVal(i,j)==0) {
        mask[i][j] = 0;
      }
      // printf("Mask: %f\n", mask[i][j]);
    }
  }
}
}  // namespace img_tools
