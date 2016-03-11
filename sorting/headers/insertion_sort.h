/*
    File Name: insertion_sort.h
    Xiaolong Zhang
    03. 10. 2016
*/

#ifndef INSERTION_SORT_H_
#define INSERTION_SORT_H_

#include <vector>

typedef std::vector<int>  Array;

class InsertionSort{
  public:
	void operator()( Array& elements );
};

#endif