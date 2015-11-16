// file name iallocator.h

#ifndef IALLOCATOR_H_
#define IALLOCATOR_H_
#include <cstddef>
#include <new>
#include <utility>
namespace sgdm{
	template<typename T>
	class IAllocator{
	  private:
	  	void* allocatedAddress;
	  	void* swap;
	  public:

	  	IAllocator();
	  	IAllocator(IAllocator<T>& alloc);
	  	~IAllocator();

	  	virtual T* get(int count, T* oldAddress = nullptr);
	  	//virtual void release(T* address, int count);  
	  	virtual void release(T* address);  //assignment three
	  	virtual void clean();

	  	virtual void construct(T* address, const T& element);  //assignment three
	  	virtual void construct(T* address, T&& element);  //assignment three
	  	virtual void destruct(T* address, int count);



	};

	template<typename T>
	void IAllocator<T>::clean(){
		if(swap != NULL)
			delete swap;
		swap = NULL;
	}

	template<typename T>
	IAllocator<T>::IAllocator(){
		allocatedAddress = NULL;
		swap = NULL;
	}

	template<typename T>
	IAllocator<T>::IAllocator(IAllocator<T>& alloc){
		allocatedAddress = alloc.allocatedAddress;
		swap = alloc.swap;
	}/*

	template<typename T>   //optional
	IAllocator<T>::IAllocator(IAllocator<T>&& alloc){
		allocatedAddress = alloc.allocatedAddress;
		swap = alloc.swap;
		alloc.allocatedAddress = NULL;
		alloc.swap = NULL;
	}
	*/

	template<typename T>
	IAllocator<T>::~IAllocator(){
        /*
		if(allocatedAddress != NULL){
			delete allocatedAddress;
			allocatedAddress = NULL;
		}
         */
	}



	template<typename T>
	T* IAllocator<T>::get(int count, T* oldAddress){
		swap = oldAddress;
		allocatedAddress = ::operator new(sizeof(T) * count);
		return (T*) allocatedAddress;
	}

	/*
	template<typename T>
	void IAllocator<T>::release(T* address, int count){
		if(address != NULL){
			for(int i=0;i<count;i++){
			address[i].~T();
			}
		}
	}
	*/

	template<typename T>   //assignment three
	void IAllocator<T>::release(T* address){
		if(address != NULL){
			delete (void*)address;
			address = NULL;
		}
	}

	template<typename T>   //assignment three
	void IAllocator<T>::construct(T* address, const T& element){
		new (address) T(element);
	}

	template<typename T>
	void IAllocator<T>::construct(T* address, T&& element){
		new (address) T(std::move(element));
	}

	template<typename T>
	void IAllocator<T>::destruct(T* address, int count){
		if(address!=nullptr){
			for(int i = 0; i < count; i++){
				address[i].~T();
			}
		}

		//address->~T();
	}
	

}


#endif