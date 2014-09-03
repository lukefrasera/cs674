include_directories( 
  src/
)

ADD_EXECUTABLE( threshold
  src/Threshold.cpp
  ${image_HEADERS}
)