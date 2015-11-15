#ifndef MAP_H_
#define MAP_H_

#include "counting_allocator.h"
#include "dynamic_array.h"
#include <string>

namespace sgdc{
	using std::string;
	template<typename T>
	class ThePair{
	  private:
	  		std::string pairKey;
	  		T pairElement;
	  		int insertCount;
	  public:
	  		ThePair(const std::string& key, const T& element):pairKey(key), pairElement(element){}
	  		//ThePair():pairKey(),pairElement(){} //this might be not necessary
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


	  	void push(const string& key, const T& value);
	  	T output() const;

	  	

	  	bool has(const std::string& key);
	  	T remove(const std::string& key);
	  	DynamicArray<std::string> keys() const;  //Retrieves all keys(immutable)
	  	DynamicArray<T> values() const;          //Retrieves all values(immutable)
        T operator[](const std::string& key) const;
        T& operator[](const std::string& key);

	  private:
	  	//int initSize;  needed no more
	  	DynamicArray<NodeType<T>>* mapArray[50];

	  	unsigned int hashFunction(const string& key);
        //int insertCount; needed no more
	};

	template<typename T, template<typename> class NodeType>
	unsigned int Map<T, NodeType>::hashFunction(const string& key){
		unsigned int res = 0;
		for(int i = 0; i < key.size(); i++){
			res ^= key[i] + 0x9e3779b9 + (res << 6) + (res >> 2);
		}
		return res % 50;
	}

	template<typename T, template<typename> class NodeType>
	Map<T, NodeType>::Map(sgdm::IAllocator<NodeType<T>> *alloc){
		for(int i =0; i < 10; i++){
			mapArray[i] = new DynamicArray<NodeType<T>>(*alloc);
		}
		//insertCount = 0;
		/*
		for(int i = 0; i < mapArray.getMax(); i++){
			mapArray.push(NodeType<T>());
		}
		*/
	}

	template<typename T, template<typename> class NodeType>
	void Map<T, NodeType>::push(const string& key, const T& value){
		unsigned int index = hashFunction(key);
		mapArray[index]->push(NodeType<T>(key, value));
	}

	template<typename T, template<typename> class NodeType>
	bool Map<T, NodeType>::has(const string& key){
		unsigned int index = hashFunction(key);
		for(int i = 0; i < mapArray[index]->getLength(); i++){
			if(key == (*mapArray[index])[i]->getKey())return true;
		}
		return false;
	}

	template<typename T, template<typename> class NodeType>
	T Map<T, NodeType>::remove(const string& key){
		unsigned int index = hashFunction(key);
		for(int i = 0; i< mapArray[index]->getLength();i++){
			if(key==(*mapArray[index])[i]->getKey()){
				T res((*mapArray[index])[i]->getValue());
				*mapArray[index]->removeAt(i);
				return res;    //move constructor needed
			}
		}
		return T();
	}

	template<typename T, template<typename> class NodeType>
	DynamicArray<string> Map<T,NodeType>::keys() const{
		DynamicArray<string> res;
		for(int i = 0; i < 50; i++){
			for(int k = 0; k < mapArray[i]->getLength(); k++){
				res.push((*mapArray[i])[k].getKey());
			}
		}
		return std::move(res);
	}

	template<typename T, template<typename> class NodeType>
	DynamicArray<T> Map<T,NodeType>::values() const{
		DynamicArray<T> res;
		for(int i = 0; i < 50; i++){
			for(int k = 0; k < mapArray[i]->getLength(); k++){
				res.push((*mapArray[i])[k].getValue());
			}
		}
		return std::move(res);
	}


}




#endif