CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(helloworld)

set(EIGEN_INCLUDE_DIR "/usr/local/include/eigen3")
include_directories(${EIGEN_INCLUDE_DIR})

option(EMBIND "Use emscripten with embind" OFF)
if(EMBIND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
endif()

#set(GLOG_INCLUDE_DIR "/usr/local/include")
#include_directories(GLOG_INCLUDE_DIR)

FIND_PACKAGE(Ceres REQUIRED)
INCLUDE_DIRECTORIES(${CERES_INCLUDE_DIRS})

# helloworld
ADD_EXECUTABLE(helloworld helloworld.cc)
TARGET_LINK_LIBRARIES(helloworld ${CERES_LIBRARIES})

