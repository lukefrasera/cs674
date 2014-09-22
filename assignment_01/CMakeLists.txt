include_directories( 
  include/
)

ADD_EXECUTABLE( histogram
  src/histogram_main.cpp
  src/histogram.cpp
  ${image_HEADERS}
)
