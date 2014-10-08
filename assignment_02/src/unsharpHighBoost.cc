#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"
#include <string.h>
// Inlcude Project Soecific
#include "spatial_filtering.h"

int main(int argc, char *argv[]) {
  // Read image file in
  int rows, cols, bytes;
  bool type;

  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[1], image);

  ImageType highboost(rows,cols, bytes);
  ImageType unsharp(rows,cols, bytes);
  ImageType blurred(rows,cols, bytes);

  img_tools::Point anchor = {1, 1};
  img_tools::Point size = {3, 3};
  float ** mask = new float*[size.x];
  for (int i =0; i< size.x; ++i) {
    mask[i] = new float[size.y];
  }
  for (int i = 0; i<size.x; ++i) {
    for (int j =0; j < size.y; ++j) {
      mask[i][j] = -1/9;
    }
  }
  mask[anchor.x][anchor.y] = (atof(argv[3])*9-1)/9;
  printf("%f\n", mask[anchor.x][anchor.y]);

  img_tools::Convolution2D(image, highboost, size, mask, anchor, 0);
  delete [] mask;
  anchor.x = 3;
  anchor.y = 3;
  size.x = 7;
  size.y = 7;
  mask = new float*[size.x];
  for (int i =0; i< size.x; ++i) {
    mask[i] = new float[size.y];
  }
  for (int i = 0; i<size.x; ++i) {
    for (int j =0; j < size.y; ++j) {
      mask[i][j] = img_tools::gaussian7[i][j];
    }
  }
  img_tools::Convolution2D(image, blurred, size, mask, anchor, 0);
  for (int i = 0; i< rows; ++i) {
    for (int j = 0; j< cols; ++j) {
      int original = image.getPixelVal(i,j);
      int lowpass = blurred.getPixelVal(i,j);
      unsharp.setPixelVal(i,j, original - lowpass); //(atof(argv[3])-1)*highpass + 
    }
  }
  img_tools::ReMap(unsharp);
  for (int i = 0; i< rows; ++i) {
    for (int j = 0; j< cols; ++j) {
      int highpass = highboost.getPixelVal(i,j);
      int orginal = unsharp.getPixelVal(i,j);
      unsharp.setPixelVal(i,j, (atof(argv[3])-1)*highpass + orginal); //(atof(argv[3])-1)*highpass + 
    }
  }
  img_tools::ReMap(unsharp);
  writeImage(argv[2], unsharp);

  return 0;
}