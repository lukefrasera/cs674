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
  ImageType output(rows,cols, bytes);

  if (atoi(argv[3])==1) {
    img_tools::Point anchor = {7, 7};
    img_tools::Point size = {15, 15};
    float ** mask = new float*[size.x];
    for (int i =0; i< size.x; ++i) {
      mask[i] = new float[size.y];
    }
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::gaussian15[i][j];
      }
    }
    img_tools::Convolution2D(image, output, size, mask, anchor, 0);

    writeImage(argv[2], output);
  } else if(atoi(argv[3])==2){
    img_tools::Point anchor = {3, 3};
    img_tools::Point size = {7, 7};
    float ** mask = new float*[size.x];
    for (int i =0; i< size.x; ++i) {
      mask[i] = new float[size.y];
    }
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::gaussian7[i][j];
      }
    }
    img_tools::Convolution2D(image, output, size, mask, anchor, 0);

    writeImage(argv[2], output);
  } else if (atoi(argv[3])==3) {
    img_tools::Point anchor = {3, 3};
    img_tools::Point size = {7, 7};
    float ** mask = new float*[size.x];
    for (int i =0; i< size.x; ++i) {
      mask[i] = new float[size.y];
    }
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = 1.0f/49.0f;
      }
    }
    img_tools::Convolution2D(image, output, size, mask, anchor, 0);

    writeImage(argv[2], output);
  } else {
    img_tools::Point anchor = {7, 7};
    img_tools::Point size = {15, 15};
    float ** mask = new float*[size.x];
    for (int i =0; i< size.x; ++i) {
      mask[i] = new float[size.y];
    }
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = 1.0f/225.0f;
      }
    }
    img_tools::Convolution2D(image, output, size, mask, anchor, 0);

    writeImage(argv[2], output);
  }
  return 0;
}