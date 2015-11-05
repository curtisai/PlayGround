#ifndef DEFAULT_ALLOCATOR_H_
#define DEFAULT_ALLOCATOR_H_

#include "iallocator.h"

namespace sgdm{
	template<typename T>
	class DefaultAllocator:public IAllocator<T>{
	  public:

	  	DefaultAllocator();
	  	DefaultAllocator(IAllocator<T>& alloc);
	  	~DefaultAllocator();


	  	virtual T* get(int count);
	  	virtual void release(T* address, int count);
	};




	template<typename T>
	T* DefaultAllocator<T>::get(int count){
		return IAllocator<T>::get(count);
	}

	template<typename T>
	void DefaultAllocator<T>::release(T* address, int count){
		if(address != NULL){
			for(int i=0;i<count;i++){
			address[i].~T();
			}
		}
	}

	template<typename T>
	DefaultAllocator<T>::DefaultAllocator(IAllocator<T>& alloc):IAllocator<T>(alloc){}

	template<typename T>
	DefaultAllocator<T>::DefaultAllocator():IAllocator<T>(){}

	template<typename T>
	DefaultAllocator<T>::~DefaultAllocator(){}


}



#endif