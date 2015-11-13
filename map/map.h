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
	  		T pairElement;
	  		int insertCount;
	  public:
	  		ThePair(const std::string& key, const T& element):pairKey(key), pairElement(element){}
	  		ThePair():pairKey("hello"),pairElement(){}
	  		~ThePair(){
	  		}
	  		const std::string& getKey(){
	  			return pairKey;
	  		}
	  		const T& getValue() const{
	  			return pairElement;
	  		}
	};


	template<typename T, template<typename> class NodeType>
	class Map{
	  public:
        Map(sgdm::IAllocator<NodeType<T>>* alloc);
	  	Map(Map<T, NodeType>& otherMap);
	  	Map(Map<T, NodeType>&& otherMap);


	  	void push(NodeType<T>);
	  	T output() const;

	  	

	  	bool has(const std::string& key);
	  	T remove(const std::string& key);
	  	DynamicArray<std::string> keys() const;  //Retrieves all keys(immutable)
	  	DynamicArray<T> values() const;          //Retrieves all values(immutable)
        T operator[](const std::string& key) const;
        T& operator[](const std::string& key);

	  private:
	  	int initSize;
	  	DynamicArray<ThePair<T>> mapArray;
        int insertCount;
	};

	template<typename T, template<typename> class NodeType>
	Map<T, NodeType>::Map(sgdm::IAllocator<NodeType<T>>* alloc):mapArray(*alloc){
		insertCount = 0;
		/*
		for(int i = 0; i < mapArray.getMax(); i++){
			mapArray.push(NodeType<T>());
		}
		*/
	}

	template<typename T, template<typename> class NodeType>
	void Map<T, NodeType>::push(NodeType<T> x){
		mapArray.push(x);
	}

	template<typename T, template<typename> class NodeType>
	T Map<T,NodeType>::output() const {
		return mapArray[0].getValue();
	}


}




#endif