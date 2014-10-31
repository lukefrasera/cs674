include_directories( 
  include/
)

#ADD_EXECUTABLE( sample
#  src/image_sampling.cpp
#  src/sample.cpp
#  ${image_HEADERS}
#)

ADD_EXECUTABLE( experiment_1
  src/experiment1.cc
  src/fft.cc
  ${image_HEADERS}
)