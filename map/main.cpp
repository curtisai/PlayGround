#include "map.h"
#include <string>
#include <iostream>


int main(){

	using namespace sgdm;
	using namespace sgdc;
	using std::string;
	using std::cout;
	using std::endl;

	CountingAllocator<ThePair<string>> alloc;
	Map<string, ThePair> myMap(&alloc);
	string greetings = "world";
	myMap.push("hello", greetings);
	for(int i = 0; i < 10000; i++){
		myMap.push(std::to_string(i), "hello");
		cout<<i<<"  "<<myMap.has(std::to_string(i))<<endl;
	}



	return 0;
}