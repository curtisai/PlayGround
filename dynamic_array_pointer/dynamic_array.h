/*
  file name: dynamic_array.h
  Xiaolong Zhang
  Dec. 22 2015
*/

#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include "default_allocator.h"
#include <iostream>


namespace StevensDev{
	namespace sgdc{    //stands for Stevens Game Development Containers
		template<typename T>
		class DynamicArray{
		  private:
		  	sgdm::DefaultAllocator<T>* arrayAlloc;   //the Allocator
		  	double expandsRatio;               //the expanding ratio
		  	unsigned int endIndex;                  //the index after the last element
		  	unsigned int capacity;                  //array will enlarge when end exceeds capacity
		  	T* contents;                       //the real array

            /*Help Functions*/
		  	void enlarge();                    //enlarge the array when encessary
		  	void shiftRight(unsigned int index);
		  	void shiftLeft(unsigned int index);


		  public:
		  	/*Constructors*/
		  	DynamicArray(sgdm::DefaultAllocator<T>* alloc, unsigned int initsize = 20);  
		  	DynamicArray(const DynamicArray<T>& other);         //copy constructor
		  	DynamicArray(DynamicArray<T>&& other);              //move constructor

		  	/*destructor*/
		  	~DynamicArray();

		  	/*copy assignment*/
		  	DynamicArray<T>& operator=(const DynamicArray<T>& other);

		  	/*move assignment*/
		  	DynamicArray<T>& operator=(DynamicArray<T>&& other);

		  	/*Member functions*/
		  	void push(const T& newElement);         //copy new element at the end of array
		  	void push(T&& newElement);              //move new element at the end of array

		  	void pushFront(const T& newElement);    //copy new element at the front of array
		  	void pushFront(T&& newElement);         //move new element at the front of array

		  	T pop();              //remove the last element of this array, and return it
		  	/*due to copy/move elision rule, following function probably coule be deleted*/
		  	//T&& pop_move();       //remove the last element of this array, and return it by move
		  	T popFront();         //remove the first element of this array, and return it
		  	/*due to copy/move elision rule, following function probably coule be deleted*/
		  	//T&& popFront_move();  //remove the first element of this array, and return it by move

		  	T removeAt(unsigned int index);         //remove specific element
		  	T&& removeAt_move(unsigned int index);  //remove specific element by move
		  	void insertAt(unsigned int index, const T& element);
		  	void insertAt(unsigned int index, T&& element);

		  	const unsigned int getLength();               //return current length of the array


		  	/*Operators*/
		  	T& operator[](unsigned int index);
		  	const T& operator[](unsigned int index) const;



		};

		template<typename T>
		const unsigned int DynamicArray<T>::getLength(){
			return endIndex;
		}

		template<typename T>
		void DynamicArray<T>::enlarge(){
			if(endIndex >= capacity){
				capacity*=expandsRatio;
				T* temp = arrayAlloc->get(capacity);
				for(int i = 0; i < endIndex; i++){
					arrayAlloc->construct(temp + i, std::move(contents[i]));
					arrayAlloc->destruct(contents[i]);
				}
				contents = arrayAlloc->release(contents);
				contents = temp;
				temp = nullptr;
			}
		}

		template<typename T>
		void DynamicArray<T>::shiftRight(unsigned int index){
			enlarge();
			for(int i = endIndex; i > index; i--){
				arrayAlloc->construct(contents + i, std::move(contents[i-1]));
				arrayAlloc->destruct(contents[i-1]);
			}
		}

		template<typename T>
		void DynamicArray<T>::shiftLeft(unsigned int index){
			arrayAlloc->destruct(contents[index-1]);
			for(int i = index-1; i < endIndex -1; i++){
				arrayAlloc->construct(contents + i, std::move(contents[i + 1]));
				arrayAlloc->destruct(contents[i+1]);
			}
		}

        /*Constructor*/
		template<typename T>
		DynamicArray<T>::DynamicArray(sgdm::DefaultAllocator<T>* alloc, unsigned int initsize)
		:endIndex(0),
		 capacity(initsize),
		 arrayAlloc(alloc),
		 expandsRatio(1.5),
		 contents(arrayAlloc->get(initsize)){}

        /*Copy Constructor*/
		template<typename T>
		DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
		:endIndex(other.endIndex),
		 arrayAlloc(other.arrayAlloc),
		 capacity(other.capacity),
		 expandsRatio(other.expandsRatio),
		 contents(arrayAlloc->get(other.capacity)){
		 	for(int i = 0; i < other.endIndex; i++){
		 		arrayAlloc->construct(contents + i, other.contents[i]);
		 	}
		 }

		/*Move Constructor*/
		template<typename T>
		DynamicArray<T>::DynamicArray(DynamicArray<T>&& other)
		:endIndex(other.endIndex),
		 arrayAlloc(other.arrayAlloc),
		 capacity(other.capacity),
		 expandsRatio(other.expandsRatio){
		 	contents = other.contents;
		 	other.contents = nullptr;
		 }

		/*Destructor*/
		template<typename T>
		DynamicArray<T>::~DynamicArray(){
			if(contents != nullptr && endIndex!=0){
				for(int i =0; i < endIndex; i++){
					arrayAlloc->destruct(contents[i]);
				}
				arrayAlloc->release(contents);
				contents = nullptr;
				arrayAlloc = nullptr;                    //destructor doesn't delete allocator
			}
			else if(contents != nullptr){
				arrayAlloc->release(contents);
				contents = nullptr;
				arrayAlloc = nullptr;                    //destructor doesn't delete allocator
			}
		}

		template<typename T>
		DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other){
			if(this != &other){
				for(int i = 0; i < endIndex; i++){           //delete old objects in target array
					arrayAlloc->destruct(contents[i]);       //before copying
				}
				contents = arrayAlloc->release(contents);    //release old memory
				contents = arrayAlloc->get(other.capacity);  //get new chunk of memory for copying

				                                             //arrayAlloc = other.arrayAlloc; still thinking
                                                             //if need to delete this line
				endIndex = other.endIndex;
				capacity = other.capacity;
				expandsRatio = other.expandsRatio;

				/*copy elements into target place*/
				for(int i = 0; i < other.endIndex; i++){
					arrayAlloc->construct(contents + i, other.contents[i]);
				}
			}
		}

		template<typename T>
		DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other){
			if(this != &other){
				for(int i = 0; i < endIndex; i++){
					arrayAlloc->destruct(contents[i]);
				}
				contents = arrayAlloc->release(contents);
				contents = other.contents;
				other.contents = nullptr;
				                                                //arrayAlloc = other.arrayAlloc;still thinking
                                                                //if need to delete this line
				endIndex = other.endIndex;
				capacity = other.capacity;
				expandsRatio = other.expandsRatio;
			}
		}

		template<typename T>
		const T& DynamicArray<T>::operator[](unsigned int index)const{
			return contents[index];
		}

		template<typename T>
		T& DynamicArray<T>::operator[](unsigned int index){
			return contents[index];
		}


		template<typename T>
		void DynamicArray<T>::push(const T& element){
			enlarge();
			arrayAlloc->construct(contents + endIndex, element);
			endIndex++;
		}

		template<typename T>
		void DynamicArray<T>::push(T&& element){
			enlarge();
			arrayAlloc->construct(contents + endIndex, std::move(element));
			endIndex++;
		}

		template<typename T>
		void DynamicArray<T>::pushFront(const T& element){
			enlarge();
			shiftRight(0);
			arrayAlloc->construct(contents, element);
			endIndex++;
		}

		template<typename T>
		void DynamicArray<T>::pushFront(T&& element){
			enlarge();
			shiftRight(0);
			arrayAlloc->construct(contents, std::move(element));
			endIndex++;
		}

		template<typename T>
		T DynamicArray<T>::popFront(){
			T res(std::move(contents[0]));        //use the move constructor
			shiftLeft(1);
			endIndex--;
			return res;
		}

/*      //due to the copy/move elision rule, this functions can be deleted, still thinking
		template<typename T>
		T&& DynamicArray<T>::popFront_move(){
			T res(std::move(contents[0]));
			shiftLeft(1);
			endIndex--;
			return std::move(res);
		}
*/

		template<typename T>
		T DynamicArray<T>::pop(){
			T res(std::move(contents[endIndex - 1]));
			arrayAlloc->destruct(contents[endIndex - 1]);
			endIndex--;
			return res;
		}

/*      //due to the copy/move elision rule, this functions can be deleted, still thinking
		template<typename T>
		T&& DynamicArray<T>::pop_move(){
			T res(std::move(contents[endIndex - 1]));
			arrayAlloc->destruct(contents[endIndex - 1]);
			endIndex--;
			return std::move(res);
		}
*/


		template<typename T>
		void DynamicArray<T>::insertAt(unsigned int index, const T& element){
			enlarge();
			shiftRight(index);
			arrayAlloc->construct(&contents[index], element);
			endIndex++;
		}

		template<typename T>
		void DynamicArray<T>::insertAt(unsigned int index, T&& element){
			enlarge();
			shiftRight(index);
			arrayAlloc->construct(&contents[index], std::move(element));
			endIndex++;
		}


		template<typename T>
		T DynamicArray<T>::removeAt(unsigned int index){
			T res(contents[index]);
			shiftLeft(index + 1);
			endIndex--;
			return res;
		}

		template<typename T>
		T&& DynamicArray<T>::removeAt_move(unsigned int index){
			T res(std::move(contents[index]));
			shiftLeft(index + 1);
			endIndex--;
			return std::move(res);
		}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		
		//Partial Specialized Template to handle poiners
		template<typename T>
		class DynamicArray<T*>{
		  private:
		  	sgdm::DefaultAllocator<T*>* arrayAlloc;   //the Allocator
		  	double expandsRatio;                      //the expanding ratio
		  	unsigned int endIndex;                    //the index after the last element
		  	unsigned int capacity;                    //array will enlarge when end exceeds capacity
		  	T** contents;                             //the real array

            /*Help Functions*/
		  	void enlarge();                    //enlarge the array when encessary
		  	void shiftRight(unsigned int index);
		  	void shiftLeft(unsigned int index);


		  public:
		  	/*Constructors*/
		  	DynamicArray(sgdm::DefaultAllocator<T*>* alloc, unsigned int initsize = 20);
		  	DynamicArray(const DynamicArray<T*>& other);
		  	DynamicArray(DynamicArray<T*>&& other);
            /*destructor*/
		  	~DynamicArray();

		  	/*Member functions*/
		  	void push(T* newElement);                    //copy new element at the end of array
		  
		  	void pushFront(T* newElement);               //copy new element at the front of array
		  	
		  	T* pop();                                    //remove the last element of this array, and return it
		  	T* popFront();                               //remove the first element of this array, and return it
		  	
		  	T* removeAt(unsigned int index);             //remove specific element
		  	void insertAt(unsigned int index, T* element);
		  	
		  	const unsigned int getLength();              //return current length of the array

		  	DynamicArray<T*>& operator=(const DynamicArray<T*>& other);
		  	                                             //copy assignment operator

		  	DynamicArray<T*>& operator=(DynamicArray<T*>&& other);
		  	                                             //move assignment operator


		  	
		    //T const * const operator[](unsigned int index) const;
		  	T  * operator[](unsigned int index);


		};

		template<typename T>
		const unsigned int DynamicArray<T*>::getLength(){
			return endIndex;
		}

		template<typename T>
		void DynamicArray<T*>::enlarge(){
			if(endIndex >= capacity){
				capacity *= expandsRatio;
				T** temp = arrayAlloc->get(capacity);
				for(int i = 0; i < endIndex; i++){
					arrayAlloc->enlargeMove(temp + i, contents[i]);
					arrayAlloc->clean(contents + i);
				}
				contents = arrayAlloc->release(contents);
				contents = temp;
				temp = nullptr;
				std::cout << "enlarge() called \n";
			}
			
		}

		template<typename T>
		void DynamicArray<T*>::shiftRight(unsigned int index){
			enlarge();
			for(int i = endIndex; i > index; i--){
				arrayAlloc->construct(contents + i, contents[i-1]);
				arrayAlloc->clean(contents + i-1);
			}
		}

		template<typename T>
		void DynamicArray<T*>::shiftLeft(unsigned int index){
			arrayAlloc->clean(contents + index-1);
			for(int i = index-1; i < endIndex -1; i++){
				arrayAlloc->construct(contents + i, contents[i + 1]);
				arrayAlloc->clean(contents + i + 1);
			}
		}

        /*Constructor*/
		template<typename T>
		DynamicArray<T*>::DynamicArray(sgdm::DefaultAllocator<T*>* alloc, unsigned int initsize)
		:endIndex(0),
		 capacity(initsize),
		 arrayAlloc(alloc),
		 expandsRatio(1.5),
		 contents(arrayAlloc->get(initsize)){}

		template<typename T>
		DynamicArray<T*>::DynamicArray(const DynamicArray<T*>& other)
		: endIndex(other.endIndex),
		  capacity(other.capacity),
		  arrayAlloc(other.arrayAlloc),
		  expandsRatio(other.expandsRatio){
		  	contents = arrayAlloc->get(other.capacity);
		  	for(int i = 0; i < endIndex; i++){

		  	}
		  }

		

		/*Destructor*/
		template<typename T>
		DynamicArray<T*>::~DynamicArray(){
			if(contents != nullptr && endIndex!=0){
				for(int i =0; i < endIndex; i++){
					arrayAlloc->destruct(contents + i);
				}
				arrayAlloc->release(contents);
				contents = nullptr;
				arrayAlloc = nullptr;                    //destructor doesn't delete allocator
			}
			else if(contents != nullptr){
				arrayAlloc->release(contents);
				contents = nullptr;
				arrayAlloc = nullptr;                    //destructor doesn't delete allocator
			}
		}

/*
		template<typename T>
		T const * const DynamicArray<T*>::operator[](unsigned int index)const {
			return contents[index];
		}
*/
		template<typename T>
		T * DynamicArray<T*>::operator[](unsigned int index){
			return *(contents + index);
		}

		template<typename T>
		void DynamicArray<T*>::push(T* element){
			enlarge();
			arrayAlloc->construct(contents + endIndex, element);
			endIndex++;
			std::cout << "pointer push called \n";
		}

		template<typename T>
		void DynamicArray<T*>::pushFront(T* element){
			enlarge();
			shiftRight(0);
			arrayAlloc->construct(contents, element);
			endIndex++;
		}

		

		template<typename T>
		T* DynamicArray<T*>::popFront(){
			T* res = contents[0];
			arrayAlloc->clean(contents);
			shiftLeft(1);
			endIndex--;
			return res;
		}


		

		template<typename T>
		T* DynamicArray<T*>::pop(){
			T* res = contents[endIndex - 1];
			arrayAlloc->clean(contents + endIndex - 1);
			endIndex--;
			return res;
		}

	


		template<typename T>
		void DynamicArray<T*>::insertAt(unsigned int index, T* element){
			enlarge();
			shiftRight(index);
			arrayAlloc->construct(contents + index, element);
			endIndex++;
		}



		template<typename T>
		T* DynamicArray<T*>::removeAt(unsigned int index){
			T* res = contents[index];
			arrayAlloc->clean(contents + index);
			shiftLeft(index + 1);
			endIndex--;
			return res;
		}
	}
}

#endif