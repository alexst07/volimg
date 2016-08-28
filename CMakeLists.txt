cmake_minimum_required (VERSION 2.8)
project(erised C CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(BASE_IMG_LIB CACHE PATH "Directory for class img library")

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${BASE_IMG_LIB}/include/)

AUX_SOURCE_DIRECTORY(src/ LIB_SRC_FILES)

add_library (volimg ${LIB_SRC_FILES})

target_link_libraries (volimg LINK_PUBLIC ${BASE_IMG_LIB}/lib/libmo815-3dvis.a)
