CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

##################################
## General Parameter
##################################

## Set Variables
SET(PROJECT_NAME SortingTests)
SET(PROJECT_TEST ${PROJECT_NAME}Test)

## Project Name
PROJECT(${PROJECT_NAME})

## Files
FILE(GLOB_RECURSE FILE_SRC headers/*.cpp)
FILE(GLOB_RECURSE FILE_TESTS tests/*.cpp)

## Include
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/headers/
	${PROJECT_SOURCE_DIR}/tests/
	${PROJECT_SOURCE_DIR}
)

## Set flag to C++ 11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## GTest
## Enable ExternalProject CMake module and set default root directory
INCLUDE(ExternalProject)

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/libs)

# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip

    # Disable install step and log output
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Get properties from googletest
ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

# Set include directory and library parameters
SET(GTEST_INCLUDE_DIR ${source_dir}/include)
SET(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
SET(GTEST_LIBRARY gtest)

# Add library
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIR})
ADD_LIBRARY(${GTEST_LIBRARY} UNKNOWN IMPORTED)
SET_PROPERTIES(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION
                ${GTEST_LIBRARY_PATH} )
ADD_DEPENDENCIES(${GTEST_LIBRARY} googletest)


#################################################
## Executable & Link
#################################################

# Main Project
ADD_EXECUTABLE(${PROJECT_TEST} test.m.cpp ${FILE_SRC} ${FILE_TESTS})
TARGET_LINK_LIBRARIES(${PROJECT_TEST} ${GTEST_LIBRARY} pthread)






