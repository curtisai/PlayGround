/*
file name iallocator.h
Xiaolong Zhang
Dec. 22 2015
*/

#ifndef IALLOCATOR_H_
#define IALLOCATOR_H_

namespace StevensDev{
	namespace sgdm{    //stand for Stevens Game Development Memory

		template<typename T>
		class IAllocator{
		  public:
		  	virtual T* get(unsigned int count) = 0;    //get specific amount of T type memory
		  	virtual T* release(T* oldMemory) = 0;    //free memory block
		  	virtual void construct(T* placeToAllocate, const T& element) = 0;  //copy construct T type element at 
		  	                                                                   //address placeToAllocate
		  	virtual void construct(T* placeToAllocate, T&& element) = 0;       //copy construct T type element at
		  	                                                                   //address placeToAllocate
		  	virtual void destruct(T* pointer) = 0;                             //destruct pointed T type object

		  	virtual void destruct(T& object) = 0;                              //destruct T type object
		};

		/*partial specialized template to handle pointers*/
		template<typename T>
		class IAllocator<T*>{
		  public:
		  	virtual T** get(unsigned int count) = 0;    //get specific amount of T type memory
		  	virtual T** release(T** oldMemory) = 0;    //free memory block
		  	virtual void construct(T** placeToAllocate, T* element) = 0;  //copy construct T type element at 
		  	                                                                   //address placeToAllocate
		  	virtual void destruct(T** pointer) = 0;                             //destruct pointed T type object

		};

	}
}



#endif