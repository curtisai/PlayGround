cmake_minimum_required(VERSION 2.8)
project (testit)
#add_library(CountingAllocator counting_allocator.h counting_allocator.cpp)
add_executable(testit testit.c)
#ADD_EXECUTABLE(brokenTest broken.cpp)

#add_subdirectory(src/engine/memory/)

SET(CMAKE_VEROBOSE_MAKEFILE on)

#SET(CMAKE_CXX_FLAGS "-g")

SET(CMAKE_BUILD_TYPE Debug)
#ADD_DEFINITIONS(-std=c++11)

#add_executable(googletesttry googletesttry.cpp Factorial.h Factorial.cpp )
#target_link_libraries(googletesttry gtest gtest_main)
#include_directories(/usr/include/gtest/)
#enable_testing()
