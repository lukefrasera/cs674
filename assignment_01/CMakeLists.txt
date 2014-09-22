include_directories( 
  include/
)

ADD_EXECUTABLE( histogram
  src/histogram_specification.cpp
  src/histogram.cpp
  ${image_HEADERS}
)

ADD_EXECUTABLE( hist_equalization
  src/histogram_equalization.cpp
  src/histogram.cpp
  ${image_HEADERS}
)

ADD_EXECUTABLE( quantization
  src/quantization.cpp
  ${image_HEADERS}
)

ADD_EXECUTABLE( sample
  src/image_sampling.cpp
  src/sample.cpp
  ${image_HEADERS}
)
