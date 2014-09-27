include_directories( 
  include/
)

#ADD_EXECUTABLE( sample
#  src/image_sampling.cpp
#  src/sample.cpp
#  ${image_HEADERS}
#)

ADD_EXECUTABLE( correlation
  src/correlation.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)
