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

ADD_EXECUTABLE( smoothing
  src/smoothing.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)

ADD_EXECUTABLE( sharpening
  src/sharpening.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)

ADD_EXECUTABLE( median
  src/median.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)

ADD_EXECUTABLE( highboost
  src/unsharpHighBoost.cc
  src/spatial_filtering.cc
  ${image_HEADERS}
)