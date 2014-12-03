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
#include "image.h"
#include "restoration_tools.h"
namespace img_tools {
enum Boundries {
  MIRROR=0,
  ZERO,
};

// struct Point {
//   int x,y;
// };

void Convolution2D(ImageType &input, ImageType &output, Point mask_size,
    float** mask, Point anchor, int boundries);
void Correlation2D(ImageType &input, ImageType &output, Point mask_size,
    float** mask, Point anchor, int boundries);
void Filter2D(ImageType &input, ImageType &output, Point size,
    float** kernel, Point anchor, int boundries);
void Convolution2Df(float** input, int rows, int cols, Point mask_size,
    float** mask, Point anchor, int boundries);
void Correlation2Df(float** input, int rows, int cols, Point mask_size,
    float** mask, Point anchor, int boundries);
void Filter2Df(float** input, int rows, int cols, Point size,
    float** kernel, Point anchor, int boundries);
void FlipKernel2D(float** kernel, Point size);
void ImageToMask(ImageType image, float** mask);
void ReMap(ImageType &image);
void MedianFilter(ImageType &input, ImageType &output, Point size, Point anchor, int boundries);

// Oredefined masks
static const float sobelx[][3] = {
  {-1.0, -2.0, -1.0},
  {0.0, 0.0, 0.0},
  {1.0, 2.0, 1.0},
};
static const float sobely[][3] = {
  {-1.0, 0.0, 1.0},
  {-2.0, 0.0, 2.0},
  {-1.0, 0.0, 1.0}
};
static  const float prewittx[][3] = {
  {-1.0, -1.0, -1.0},
  {0.0, 0.0, 0.0},
  {1.0, 1.0, 1.0}
};
static const float prewitty[][3] = {
  {-1.0, 0.0, 1.0},
  {-1.0, 0.0, 1.0},
  {-1.0, 0.0, 1.0}
};
static const float laplacian[][3] = {
  {0.0, 1.0, 0.0},
  {1.0, -4.0, 1.0},
  {0.0, 1.0, 0.0}
};
static const float highboost[][3] = {
  {-1.0, -1.0, -1.0},
  {-1.0, 1,-1.0},
  {-1.0, -1.0, -1.0}
};

static  const float gaussian15[][15] = {
  {2.0f /2044.0f,2.0f /2044.0f,3.0f /2044.0f,4.0f /2044.0f,5.0f /2044.0f,5.0f /2044.0f,6.0f /2044.0f,6.0f /2044.0f,6.0f /2044.0f,5.0f /2044.0f,5.0f /2044.0f,4.0f /2044.0f,3.0f /2044.0f,2.0f /2044.0f,2.0f /2044.0f},
  {2.0f /2044.0f,3.0f /2044.0f,4.0f /2044.0f,5.0f /2044.0f,7.0f /2044.0f,7.0f /2044.0f,8.0f /2044.0f,8.0f /2044.0f,8.0f /2044.0f,7.0f /2044.0f,7.0f /2044.0f,5.0f /2044.0f,4.0f /2044.0f,3.0f /2044.0f,2.0f /2044.0f},
  {3.0f /2044.0f,4.0f /2044.0f,6.0f /2044.0f,7.0f /2044.0f,9.0f /2044.0f,10.0f/2044.0f,10.0f/2044.0f,11.0f/2044.0f,10.0f/2044.0f,10.0f/2044.0f,9.0f /2044.0f,7.0f /2044.0f,6.0f /2044.0f,4.0f /2044.0f,3.0f /2044.0f},
  {4.0f /2044.0f,5.0f /2044.0f,7.0f /2044.0f,9.0f /2044.0f,10.0f/2044.0f,12.0f/2044.0f,13.0f/2044.0f,13.0f/2044.0f,13.0f/2044.0f,12.0f/2044.0f,10.0f/2044.0f,9.0f /2044.0f,7.0f /2044.0f,5.0f /2044.0f,4.0f /2044.0f},
  {5.0f /2044.0f,7.0f /2044.0f,9.0f /2044.0f,11.0f/2044.0f,13.0f/2044.0f,14.0f/2044.0f,15.0f/2044.0f,16.0f/2044.0f,15.0f/2044.0f,14.0f/2044.0f,13.0f/2044.0f,11.0f/2044.0f,9.0f /2044.0f,7.0f /2044.0f,5.0f /2044.0f},
  {5.0f /2044.0f,7.0f /2044.0f,10.0f/2044.0f,12.0f/2044.0f,14.0f/2044.0f,16.0f/2044.0f,17.0f/2044.0f,18.0f/2044.0f,17.0f/2044.0f,16.0f/2044.0f,14.0f/2044.0f,12.0f/2044.0f,10.0f/2044.0f,7.0f /2044.0f,5.0f /2044.0f},
  {6.0f /2044.0f,8.0f /2044.0f,10.0f/2044.0f,13.0f/2044.0f,15.0f/2044.0f,17.0f/2044.0f,19.0f/2044.0f,19.0f/2044.0f,19.0f/2044.0f,17.0f/2044.0f,15.0f/2044.0f,13.0f/2044.0f,10.0f/2044.0f,8.0f /2044.0f,6.0f /2044.0f},
  {6.0f /2044.0f,8.0f /2044.0f,11.0f/2044.0f,13.0f/2044.0f,16.0f/2044.0f,18.0f/2044.0f,19.0f/2044.0f,20.0f/2044.0f,19.0f/2044.0f,18.0f/2044.0f,16.0f/2044.0f,13.0f/2044.0f,11.0f/2044.0f,8.0f /2044.0f,6.0f /2044.0f},
  {6.0f /2044.0f,8.0f /2044.0f,10.0f/2044.0f,13.0f/2044.0f,15.0f/2044.0f,17.0f/2044.0f,19.0f/2044.0f,19.0f/2044.0f,19.0f/2044.0f,17.0f/2044.0f,15.0f/2044.0f,13.0f/2044.0f,10.0f/2044.0f,8.0f /2044.0f,6.0f /2044.0f},
  {5.0f /2044.0f,7.0f /2044.0f,10.0f/2044.0f,12.0f/2044.0f,14.0f/2044.0f,16.0f/2044.0f,17.0f/2044.0f,18.0f/2044.0f,17.0f/2044.0f,16.0f/2044.0f,14.0f/2044.0f,12.0f/2044.0f,10.0f/2044.0f,7.0f /2044.0f,5.0f /2044.0f},
  {5.0f /2044.0f,7.0f /2044.0f,9.0f /2044.0f,11.0f/2044.0f,13.0f/2044.0f,14.0f/2044.0f,15.0f/2044.0f,16.0f/2044.0f,15.0f/2044.0f,14.0f/2044.0f,13.0f/2044.0f,11.0f/2044.0f,9.0f /2044.0f,7.0f /2044.0f,5.0f /2044.0f},
  {4.0f /2044.0f,5.0f /2044.0f,7.0f /2044.0f,9.0f /2044.0f,10.0f/2044.0f,12.0f/2044.0f,13.0f/2044.0f,13.0f/2044.0f,13.0f/2044.0f,12.0f/2044.0f,10.0f/2044.0f,9.0f /2044.0f,7.0f /2044.0f,5.0f /2044.0f,4.0f /2044.0f},
  {3.0f /2044.0f,4.0f /2044.0f,6.0f /2044.0f,7.0f /2044.0f,9.0f /2044.0f,10.0f/2044.0f,10.0f/2044.0f,11.0f/2044.0f,10.0f/2044.0f,10.0f/2044.0f,9.0f /2044.0f,7.0f /2044.0f,6.0f /2044.0f,4.0f /2044.0f,3.0f /2044.0f},
  {2.0f /2044.0f,3.0f /2044.0f,4.0f /2044.0f,5.0f /2044.0f,7.0f /2044.0f,7.0f /2044.0f,8.0f /2044.0f,8.0f /2044.0f,8.0f /2044.0f,7.0f /2044.0f,7.0f /2044.0f,5.0f /2044.0f,4.0f /2044.0f,3.0f /2044.0f,2.0f /2044.0f},
  {2.0f /2044.0f,2.0f /2044.0f,3.0f /2044.0f,4.0f /2044.0f,5.0f /2044.0f,5.0f /2044.0f,6.0f /2044.0f,6.0f /2044.0f,6.0f /2044.0f,5.0f /2044.0f,5.0f /2044.0f,4.0f /2044.0f,3.0f /2044.0f,2.0f /2044.0f,2.0f /2044.0f},
};

static const float gaussian7[][7] = {
  {1.0f /148.0f,1.0f /148.0f,2.0f /148.0f,2.0f /148.0f,2.0f /148.0f,1.0f /148.0f,1.0f /148.0f},
  {1.0f /148.0f,2.0f /148.0f,2.0f /148.0f,4.0f /148.0f,2.0f /148.0f,2.0f /148.0f,1.0f /148.0f},
  {2.0f /148.0f,2.0f /148.0f,4.0f /148.0f,8.0f /148.0f,8.0f /148.0f,2.0f /148.0f,2.0f /148.0f},
  {2.0f /148.0f,4.0f /148.0f,8.0f /148.0f,16.0f/148.0f,8.0f /148.0f,4.0f /148.0f,2.0f /148.0f},
  {2.0f /148.0f,2.0f /148.0f,4.0f /148.0f,8.0f /148.0f,8.0f /148.0f,2.0f /148.0f,2.0f /148.0f},
  {1.0f /148.0f,2.0f /148.0f,2.0f /148.0f,4.0f /148.0f,2.0f /148.0f,2.0f /148.0f,1.0f /148.0f},
  {1.0f /148.0f,1.0f /148.0f,2.0f /148.0f,2.0f /148.0f,2.0f /148.0f,1.0f /148.0f,1.0f /148.0f},
};
}
#endif // SPATIAL_FILTERING_H_