#ifndef COUNTING_ALLOCATOR_H_
#define COUNTING_ALLOCATOR_H_

#include "default_allocator.h"

namespace sgdm{
	template<typename T>
	class CountingAllocator : public DefaultAllocator<T>{
	  private:
	  	static int totalAllocation;
	  	static int totalRelesing;

	  	int allocationCount;
	  	int releaseCount;

	  public:
	  	CountingAllocator();
	  	CountingAllocator(IAllocator<T>& alloc);
	  	~CountingAllocator();



	  	const int getAllocationCount();
	  	const int getReleaseCount();
	  	const int getOutstandingCOunt();

	  	static int getTotalAllocationCOunt();
	  	static int getTotoalReleaseCount();
	  	static int getTotalOutstandingCount();

	  	virtual T* get(int count, T* oldAddress = nullptr);
	  	virtual void release(T* address);

	};

	template<typename T>
	int CountingAllocator<T>::totalAllocation = 0;

	template<typename T>
	int CountingAllocator<T>::totalRelesing = 0;



	template<typename T>
	CountingAllocator<T>::CountingAllocator():DefaultAllocator<T>(){
		allocationCount = 0;
		releaseCount = 0;
	}

	template<typename T>
	CountingAllocator<T>::CountingAllocator(IAllocator<T>& alloc):DefaultAllocator<T>(alloc){}

	template<typename T>
	CountingAllocator<T>::~CountingAllocator(){}



	template<typename T>
	const int CountingAllocator<T>::getAllocationCount(){
		return allocationCount;
	}

	template<typename T>
	const int CountingAllocator<T>::getReleaseCount(){
		return releaseCount;
	}

	template<typename T>
	const int CountingAllocator<T>::getOutstandingCOunt(){
		return allocationCount - releaseCount;
	}

	template<typename T>
	int CountingAllocator<T>::getTotalAllocationCOunt(){
		return totalAllocation;
	}

	template<typename T>
	int CountingAllocator<T>::getTotoalReleaseCount(){
		return totalRelesing;
	}

	template<typename T>
	int CountingAllocator<T>::getTotalOutstandingCount(){
		return totalAllocation - totalRelesing;
	}

	template<typename T>
	T* CountingAllocator<T>::get(int count, T* oldAddress){
		return DefaultAllocator<T>::get(count, oldAddress);
	}
	

	template<typename T>
	void CountingAllocator<T>::release(T* address){
		if(address != NULL){
			delete (void*)address;
		}
	}
	

}


#endif