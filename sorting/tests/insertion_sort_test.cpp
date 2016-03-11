#include "insertion_sort_test.h"

InsertionSortTest::InsertionSortTest()
: d_array(100),
  d_insertion_sort(){}



void InsertionSortTest::SetUp(){
	std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine(rnd_device());
    
    std::uniform_int_distribution<int> dist(1, 100);

    auto gen = std::bind(dist, mersenne_engine);
    
    std::generate(std::begin(d_array), std::end(d_array), gen);
}

void InsertionSortTest::TearDown(){}