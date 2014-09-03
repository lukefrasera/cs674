cmake_minimum_required(VERSION 2.8)

PROJECT(cs674)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)


INCLUDE_DIRECTORIES(
  include/
)

# Setup image library header directory
SET(image_HEADERS
  ${PROJECT_SOURCE_DIR}/include/ReadImage.h
  ${PROJECT_SOURCE_DIR}/include/WriteImage.h
  ${PROJECT_SOURCE_DIR}/include/ReadImageHeader.h
  ${PROJECT_SOURCE_DIR}/include/image.cpp
  ${PROJECT_SOURCE_DIR}/include/image.h
)
# Include subdirectories
ADD_SUBDIRECTORY(threshold_example)