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

  int mask_size = atoi(argv[3]);
  img_tools::Point anchor = {mask_size/2, mask_size/2};
  img_tools::Point size = {mask_size, mask_size};
  // float ** mask = new float*[size.x];
  // for (int i =0; i< size.x; ++i) {
  //   mask[i] = new float[size.y];
  // }
  // for (int i = 0; i<size.x; ++i) {
  //   for (int j =0; j < size.y; ++j) {
  //     mask[i][j] = 1;
  //   }
  // }
  img_tools::MedianFilter(image, output, size, anchor, 0);

  writeImage(argv[2], output);

  return 0;
}