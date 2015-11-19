#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_


#include <new>
#include "counting_allocator.h"
namespace sgdc{
	template<typename T>
	class DynamicArray{
	  private:
	  	sgdm::IAllocator<T>& elementAllocator;
	  	int end;
	  	int max;
	  	int expand;
	  	size_t elementSize;
	  	T *contents;


	  	inline void enlarge();
	  	inline void shiftRight(int index, int count);
	  	inline void shiftLeft(int index, int count);
	  	DynamicArray(const DynamicArray<T>& other);




	  public:
	  	DynamicArray(sgdm::IAllocator<T> &alloc, int initSize = 100);
        DynamicArray(DynamicArray<T>&& other);
	  	~DynamicArray();


	  	void push(const T& element);
        void push(T&& element);
	  	void pushFront(const T& element);
        

	  	const int getMax();

	  	T pop();
	  	T popFront();
	  	const unsigned int getLength();
	  	const T at(unsigned int index);
	  	T& operator[](unsigned int index);
	  	T operator[](unsigned int index) const;
	  	T removeAt(unsigned int index);
	  	void insertAt(unsigned int index, const T& element);
	  	
	};


	template<typename T>
	DynamicArray<T>::DynamicArray(DynamicArray<T>&& other):elementAllocator(other.elementAllocator){
		end = other.end;
		max = other.max;
		expand = other.expand;
		elementSize = other.elementSize;
		contents = other.contents;
		other.contents = nullptr;
	}

	template<typename T>
	void DynamicArray<T>::enlarge(){
		T *temp =  contents;
		contents = elementAllocator.get(expand + max, temp);
		for(int i = 0; i <= max; i++){
		    //elementAllocator.construct(contents + i, T(temp[i]))	
            new (contents + i) T(std::move(temp[i]));//contents[i] = temp[i];
			temp[i].~T();
		}
		max = expand + max;
		elementAllocator.clean();
		temp = nullptr;

	}


	template<typename T>
	const int DynamicArray<T>::getMax(){
		return max;
	}

	
	template<typename T>
	void DynamicArray<T>::shiftRight(int index, int count){
		for(int i = end + count -1; i >= index + count; i--){
			new (contents + i) T(contents[i - count]);
			contents[i - count].~T();
		}
		end += count;

	}

	template<typename T>
	void DynamicArray<T>::shiftLeft(int index, int count){
		if (index - count >= 0){
			//contents[index-count].~T();
			for (int i = index - count; i < end - count ; i++){
				new (contents + i) T(contents[i + count]);
				contents[i + count].~T();
			}
			if(end - count < index){
				for(int i = end - count; i < index; i++){
					contents[i].~T();
				}
			}
				end -= count;
		}
	}


	template<typename T>
	DynamicArray<T>::DynamicArray(sgdm::IAllocator<T> &alloc, int initSize):elementAllocator(alloc){
		//elementAllocator = alloc; class-member reference type must 
		//be initialized in the constructor initialization list
		expand = initSize;
		elementSize = sizeof(T);
		contents = elementAllocator.get(initSize);
		end = 0;
		max = initSize/2;
	}

	template<typename T>
	DynamicArray<T>::~DynamicArray(){
        elementAllocator.destruct(this->contents, end);
		
		//elementAllocator.~IAllocator();
		elementAllocator.release(this->contents);
        contents = nullptr;
	}

	template<typename T>
	void DynamicArray<T>::push(const T& element){
		if(end <= max){
            elementAllocator.construct(contents + end, element);
			end++;
		}
		else{
			enlarge();
			push(element);
		}
	}
    
    template<typename T>
    void DynamicArray<T>::push(T&& element){
        if(end <= max){
            elementAllocator.construct(contents + end, std::move(element)); //new (contents + end) T(element);
            end++;
        }
        else{
            enlarge();
            push(std::move(element));
        }
    }

	template<typename T>
	void DynamicArray<T>::pushFront(const T& element){
		if(end == 0)push(element);
		else
			if(end <= max){
				shiftRight(0,1);
			//end++;  shifRight takes care of this
				elementAllocator.construct(contents, T(element)); //new (contents) T(element);
			}
			else{
				enlarge();
				pushFront(element);
			}
	}

	template<typename T>
	T DynamicArray<T>::pop(){
		T temp = contents[end-1];
		elementAllocator.destruct(contents + end -1); //contents[end-1].~T();
		end--;
		return temp;
	}

	template<typename T>
	T DynamicArray<T>::popFront(){
		T temp = contents[0];
		//contents[0].~T(); //this should be done by the shift functions
		elementAllocator.destruct(contents);
		shiftLeft(1,1);
		//end--;   shiftLeft takes care of this
		return temp;
	}


	template<typename T>
	const unsigned int DynamicArray<T>::getLength(){
		return end;
	}

	template<typename T>
	const T DynamicArray<T>::at(unsigned int index){
		if(index >= end){
			throw "DynamicArray::at() Out of boundary";
		}
		else
			return contents[index];
	}

	template<typename T>
	T DynamicArray<T>::operator[](unsigned int index) const{
		return contents[index];
	}


	template<typename T>
	T& DynamicArray<T>::operator[](unsigned int index){
		return contents[index];
	}

	template<typename T>
	T DynamicArray<T>::removeAt(unsigned int index){
		if(index >= end){
			throw "DynamicArray::removeAt()  Out of boundary";
		}
		else{
			T temp = contents[index];
			//contents[index].~T();
			shiftLeft(index + 1, 1);
			//end--;
			return temp;
		}
	}


	template<typename T>
	void DynamicArray<T>::insertAt(unsigned int index, const T& element){
		if(index > end){
			throw "DynamicArray::insertAt()  Out of boundary";
		}
		else{
			if(end <= max){
				shiftRight(index, 1);
				//end++;
				new (contents + index) T(element);
			}
			else{
				enlarge();
				insertAt(index, element);
			}
		}
	}
}


#endif