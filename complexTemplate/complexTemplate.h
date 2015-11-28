#include <string>
#include <vector>
#include <iostream>


template<typename T>
class One{
private:
	T value;
public:
	One(T newVal): value(newVal){}
	T output(){
		return value;
	}
};

template<typename one, template<typename> class two>
class Two{
private:
	std::vector<two<one>> value;
public:
	Two():value(){}
	void push(one cool){
		//One<T> theOne(cool);
		value.push_back(two<one>(cool));//One<T>(cool));
	}
	void show(){
		for(int i = 0; i < value.size(); i++){
			std::cout<<value[i].output()<<std::endl;
		}
	}

};

