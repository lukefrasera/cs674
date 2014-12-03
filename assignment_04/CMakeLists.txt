include_directories( 
  include/
)

#ADD_EXECUTABLE( sample
#  src/image_sampling.cpp
#  src/sample.cpp
#  ${image_HEADERS}
#)

ADD_EXECUTABLE( noise_removal
  src/noise_removal.cc
  src/fft.cc
  src/fft_tools.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)

ADD_EXECUTABLE( convolution_freq
  src/convolution_freq.cc
  src/fft.cc
  src/fft_tools.cc
  src/restoration_tools.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)

ADD_EXECUTABLE( motionblur
  src/motionblur.cc
  src/fft.cc
  src/fft_tools.cc
  src/restoration_tools.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)

ADD_EXECUTABLE( homomorphic
  src/homomorphic.cc
  src/fft.cc
  src/fft_tools.cc
  src/restoration_tools.cc
  ${image_HEADERS}
)