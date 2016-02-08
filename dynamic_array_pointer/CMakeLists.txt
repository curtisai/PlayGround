CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(CONSTRUCT)   #to see if I can construct object based on pointers

FILE(GLOB_RECURSE SRC_FILES dynamic_array.cpp default_allocator.cpp copyClass.cpp)

SET(CMAKE_CXX_FLAGS "-std=c++11")
ADD_DEFINITIONS("-g")
ADD_DEFINITIONS("-fno-elide-constructors")
ADD_EXECUTABLE(test main.cpp ${SRC_FILES})