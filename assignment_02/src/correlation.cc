// Include I/O
#include <stdio.h>
// Include Image Headers
#include "image.h"
#include "ReadImage.h"
#include "ReadImageHeader.h"
#include "WriteImage.h"
// Inlcude Project Soecific
#include "spatial_filtering.h"

int main(int argc, char *argv[]) {
  // Read image file in
  int rows, cols, bytes;
  bool type;

  readImageHeader(argv[2], rows, cols, bytes, type);
  ImageType image(rows, cols, bytes);
  readImage(argv[2], image);
  ImageType out_image(rows, cols, bytes);

  float **mask;
  // Load correlation mask
  readImageHeader(argv[1], rows, cols, bytes, type);
  ImageType mask_image(rows, cols, bytes);
  readImage(argv[1], mask_image);
  mask = new float*[rows];
  for (int i=0; i<rows; ++i) {
    mask[i] = new float[cols];
  }
  img_tools::ImageToMask(mask_image, mask);

  // convolve mask
  img_tools::Point anchor = {rows/2, cols/2};
  img_tools::Point size = {rows, cols};
  img_tools::Correlation2D(image, out_image, size, mask, anchor, 0);
  // remap image to 0-255
  img_tools::ReMap(out_image);
  // save image out
  writeImage(argv[3], out_image);

  return 0;
}