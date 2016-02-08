#ifndef COUNTING_ALLOCATOR_H_
#define COUNTING_ALLOCATOR_H_

#include "default_allocator.h"

namespace StevensDev{
	namespace sgdm{    //stands for Stevens Game Development Memory
		template <typename T>
		class CountingAllocator : public DefaultAllocator<T>{
		  private:
		  	static unsigned int totalAllocation;
		  	static unsigned int totalReleasing;

		  	int allocationCount;
		  	int releaseCount;

		  public:
		  	/*constructors*/
		  	CountingAllocator();
		  	CountingAllocator(const CountingAllocator<T>& other);
		  	CountingAllocator(CountingAllocator<T>&& other);

		  	/*member functions*/
		  	const unsigned int getAllocationCount();
		  	const unsigned int getReleasingCount();
		  	const unsigned int getOutstandingCount();

		  	static const unsigned int getTotalAllocationCount();
		  	static const unsigned int getTotalReleasingCount();
		  	static const unsigned int getTotalOutstandingCount();

		  	virtual T* get(unsigned int count);
		  	virtual T* release(T* oldAddress);

		  	virtual void construct(T* placeToConstruct, const T& element);
		  	virtual void construct(T* placeToConstruct, T&& element);

		  	/*operators*/
		  	CountingAllocator<T>& operator=(const CountingAllocator<T>& otherAllocator);
		  	CountingAllocator<T>& operator=(CountingAllocator<T>&& otherAllocator);
		};


		/*initializing static data member*/
		template<typename T>
		unsigned int CountingAllocator<T>::totalAllocation = 0;
		template<typename T>
		unsigned int CountingAllocator<T>::totalReleasing = 0;



        /*Constructor implementation*/
		template<typename T>
		CountingAllocator<T>::CountingAllocator():allocationCount(0),releaseCount(0){}

		template<typename T>
		CountingAllocator<T>::CountingAllocator(const CountingAllocator<T>& other)
		:  allocationCount(other.allocationCount),
		   releaseCount(other.releaseCount){}

		template<typename T>
		CountingAllocator<T>::CountingAllocator(CountingAllocator<T>&& other)
		:  allocationCount(other.allocationCount),
		   releaseCount(other.releaseCount){}

        /*member functions*/
		template<typename T>
		void CountingAllocator<T>::construct(T* placeToConstruct, const T& element){
			DefaultAllocator<T>::construct(placeToConstruct, element);
		}

		template<typename T>
		void CountingAllocator<T>::construct(T* placeToConstruct, T&& element){
			DefaultAllocator<T>::construct(placeToConstruct, element);
		}



        template<typename T>
		const unsigned int CountingAllocator<T>::getAllocationCount(){
			return allocationCount;
		}

		template<typename T>
		const unsigned int CountingAllocator<T>::getReleasingCount(){
			return releaseCount;
		}

		template<typename T>
		const unsigned int CountingAllocator<T>::getOutstandingCount(){
			return allocationCount - releaseCount;
		}

		template<typename T>
		const unsigned int CountingAllocator<T>::getTotalAllocationCount(){
			return totalAllocation;
		}

		template<typename T>
		const unsigned int CountingAllocator<T>::getTotalReleasingCount(){
			return totalReleasing;
		}

		template<typename T>
		const unsigned int CountingAllocator<T>::getTotalOutstandingCount(){
			return totalAllocation - totalReleasing;
		}

		template<typename T>
		T* CountingAllocator<T>::get(unsigned int count){
			allocationCount++;
			totalAllocation++;
			return DefaultAllocator<T>::get(count);
		}

		template<typename T>
		T* CountingAllocator<T>::release(T* oldAddress){
			releaseCount++;
			totalReleasing++;
			return DefaultAllocator<T>::release(oldAddress);
		}
	}
}





#endif