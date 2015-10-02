cmake_minimum_required(VERSION 2.8)
project (asTwo)
#add_library(CountingAllocator counting_allocator.h counting_allocator.cpp)

#ADD_EXECUTABLE(brokenTest broken.cpp)

add_subdirectory(src/engine/memory/)

SET(CMAKE_VEROBOSE_MAKEFILE on)

#add_executable(googletesttry googletesttry.cpp Factorial.h Factorial.cpp )
#target_link_libraries(googletesttry gtest gtest_main)
#include_directories(/usr/include/gtest/)
#enable_testing()
