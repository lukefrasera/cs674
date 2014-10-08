#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"
#include <string.h>
#include <cmath>
// Inlcude Project Soecific
#include "spatial_filtering.h"

void GradientMag(ImageType inputx, ImageType inputy, ImageType &output) {
  int rows, cols, levels;
  inputy.getImageInfo(rows, cols, levels);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int x = inputx.getPixelVal(i,j);
      int y = inputy.getPixelVal(i,j);
      output.setPixelVal(i,j, sqrt(x*x + y*y));
    }
  }
}
int main(int argc, char *argv[]) {
  // Read image file in
  int rows, cols, bytes;
  bool type;

  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[1], image);
  ImageType outputx(rows,cols, bytes);
  ImageType outputy(rows,cols, bytes);

  img_tools::Point anchor = {1, 1};
  img_tools::Point size = {3, 3};

  float ** mask = new float*[size.x];
  for (int i =0; i< size.x; ++i) {
    mask[i] = new float[size.y];
  }

  if (atoi(argv[3])==1) {
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::sobelx[i][j];
      }
    }
    img_tools::Convolution2D(image, outputx, size, mask, anchor, 0);

    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::sobely[i][j];
      }
    }
    img_tools::Convolution2D(image, outputy, size, mask, anchor, 0);
  } else if (atoi(argv[3])==2){
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::prewittx[i][j];
      }
    }
    img_tools::Convolution2D(image, outputx, size, mask, anchor, 0);

    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::prewitty[i][j];
      }
    }
    img_tools::Convolution2D(image, outputy, size, mask, anchor, 0);
  } else {
    for (int i = 0; i<size.x; ++i) {
      for (int j =0; j < size.y; ++j) {
        mask[i][j] = img_tools::laplacian[i][j];
      }
    }
    img_tools::Convolution2D(image, outputy, size, mask, anchor, 0);
    img_tools::ReMap(outputy);
    writeImage(argv[2], outputy);
    return 0;
  }
  ImageType output(rows, cols, bytes);

  GradientMag(outputx, outputy, output);
  img_tools::ReMap(output);


  writeImage(argv[2], output);


  return 0;
}