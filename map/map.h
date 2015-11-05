#ifndef MAP_H_
#define MAP_H_

#include "counting_allocator.h"
#include "dynamic_array.h"
#include <string>

namespace sgdc{
	template<typename T>
	class ThePair{
	  private:
	  		std::string pairKey;
	  		T* elementList;
	  		int insertCount;
	  public:
	  		ThePair(const std::string& key, T* element):pairKey(key), pairElement(element){}
	  		ThePair():pairKey(),pairElement(){}
	  		~ThePair(){
	  			delete pairKey;
	  			pairKey = NULL;
	  		}
	  		const std::string& getKey(){
	  			return pairKey;
	  		}
	  		const T getValue(){
	  			return pairElement;
	  		}
	};

	template<typename pair, typename T>
	class Map{
	  public:
	  	Map(IAllocator<pair<T>>* alloc);
	  	Map(Map<pair<T>>& otherMap);  //copy constructor
	  	Map(Map<pair<T>>&& otherMap);
	  	//move constructor awaits

	  	bool has(const std::string& key);
	  	T remove(const std::string& key);
	  	DynamicArray<std::string> keys() const;  //Retrieves all keys(immutable)
	  	DynamicArray<T> values() const;   //Retrieves all values(immutable)
	  	const T& operator[](const string& key);
	  	T& operator[](const string& key);

	  private:
	  	int initSize;
	  	DynamicArray<pair<T>>* mapArray;
	};

	template<typename T>
	Map<ThePair<T>>::Map(IAllocator<ThePair<T>>* alloc):mapArray(alloc){
		insertCount = 0;
	}


}




#endif