#include "insertion_sort.h"

void InsertionSort::operator()( Array& elements ){
	if ( elements.size() > 1 ){
		for ( int i = 1; i < elements.size(); ++i ){
			int j = i;
			while( j > 0 && elements[j - 1] > elements[j]){
				std::swap( elements[j - 1], elements[j] );
				--j;
			}
		}
	}
}

