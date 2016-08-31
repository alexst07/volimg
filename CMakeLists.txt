cmake_minimum_required (VERSION 2.8)
project(erised C CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(BASE_IMG_LIB CACHE PATH "Directory for class img library")

include_directories(${BASE_IMG_LIB}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/)

file(GLOB LIB_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_library(volimg SHARED ${LIB_SRC_FILES})

target_link_libraries (volimg LINK_PUBLIC ${BASE_IMG_LIB}/lib/libmc920.a)

add_subdirectory(tests/)
