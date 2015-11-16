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


	  	virtual T* get(int count, T* oldAddress = nullptr);
	  	virtual void release(T* address);
	};


    

	template<typename T>
	T* DefaultAllocator<T>::get(int count, T* oldAddress){
		return IAllocator<T>::get(count, oldAddress);
	}

	
	template<typename T>
	void DefaultAllocator<T>::release(T* address){
		IAllocator<T>::release(address);
	}
	

	template<typename T>
	DefaultAllocator<T>::DefaultAllocator(IAllocator<T>& alloc):IAllocator<T>(alloc){}

	template<typename T>
	DefaultAllocator<T>::DefaultAllocator():IAllocator<T>(){}

	template<typename T>
	DefaultAllocator<T>::~DefaultAllocator(){}


}



#endif