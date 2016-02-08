//file name default_allocator.h
/*
Xiaolong Zhang
Dec. 22 2015
*/
#ifndef DEFAULT_ALLOCATOR_H_
#define DEFAULT_ALLOCATOR_H_


#include <new>
#include <utility>
#include "iallocator.h"
#include <iostream>

namespace StevensDev{
	namespace sgdm{    // stands for Stevens Game Development Memory
		template<typename T>
		class DefaultAllocator : public IAllocator<T>{
		  public:
		  	T* get(unsigned int count);  //get specific T type memory, and return the pointer;
		  	T* release(T* oldAddress); //release the address oldAddress;
		  	void construct(T* pointer, const T& element); //do the in-placement copy construction
		  	void construct(T* pointer, T&& element);      //do the in-placement move construction
		  	void destruct(T* pointer);                    //destruct pointed T type object
		  	void destruct(T& object);                     //destruct T type object;


		};

		template<typename T>
		T* DefaultAllocator<T>::get(unsigned int count){
			return (T*) ::operator new(sizeof(T) * count);
		}

		template<typename T>
		T* DefaultAllocator<T>::release(T* oldAddress){
			if(oldAddress!=nullptr)
				delete (void*) oldAddress;
			return nullptr;
		}

		template<typename T>
		void DefaultAllocator<T>::construct(T* pointer, const T& element){
			new (pointer) T(element);
		}

		template<typename T>
		void DefaultAllocator<T>::construct(T* pointer, T&& element){
			new (pointer) T(std::move(element));
		}

		template<typename T>
		void DefaultAllocator<T>::destruct(T* pointer){
			pointer->~T();
		}

		template<typename T>
		void DefaultAllocator<T>::destruct(T& object){
			object.~T();
		}


        /*Partial Specialized template to handle pointers*/
		template<typename T>
		class DefaultAllocator<T*> : public IAllocator<T*>{
		  public:
		  	T** get(unsigned int count);               //get specific T type memory, and return the pointer;
		  	T** release(T** oldAddress);               //release the address oldAddress;
		  	void construct(T** pointer, T* element);   //do the in-placement copy construction
		  	void destruct(T** pointer);                //destruct pointed T type object
		    void clean(T** pointer);
		    void enlargeMove(T** pointer, T* element);
		};

		template<typename T>
		T** DefaultAllocator<T*>::get(unsigned int count){
			return (T**) ::operator new(sizeof(T*) * count);
		}

		template<typename T>
		T** DefaultAllocator<T*>::release(T** oldAddress){
			if(oldAddress!=nullptr)
				delete (void**) oldAddress;
			return nullptr;
		}

		template<typename T>
		void DefaultAllocator<T*>::construct(T** pointer, T* element){
			new (*pointer) T(*element);
			std::cout << "pointer construct called\n";
		}

		template<typename T>
		void DefaultAllocator<T*>::destruct(T** pointer){
			delete (*pointer);
			std::cout << "pointer destruct called\n";
		}
		template<typename T>
		void DefaultAllocator<T*>::clean(T** pointer){
			(*pointer) = nullptr;
		}
		template<typename T>
		void DefaultAllocator<T*>::enlargeMove(T** pointer, T* element){
			(*pointer) = element;
		}
	}
}


#endif