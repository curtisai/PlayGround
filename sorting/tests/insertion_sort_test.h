/*
    File Name: insertion_sort_test.h
    Xiaolong Zhang
    03. 10. 2016
*/

#ifndef INSERTION_SORT_TEST_H_
#define INSERTION_SORT_TEST_H_

#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include "headers/insertion_sort.h"

typedef std::vector<int> Array;

class InsertionSortTest : public ::testing::Test{
  public:

  	Array                 d_array;
  	
  	InsertionSort         d_insertion_sort;

  	//constructor
  	InsertionSortTest();

  	//member functions

  	virtual void SetUp();
  	    // setup work for each test

  	virtual void TearDown();
  	    // clean-up after each test


};

TEST_F( InsertionSortTest, Sorting ){

	d_insertion_sort( d_array );

	for( int i = 1; i < d_array.size(); ++i ){

		EXPECT_TRUE( d_array[i - 1] <= d_array[i] );

	}

}

#endif