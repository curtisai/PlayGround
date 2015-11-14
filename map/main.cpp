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
	myMap.push(ThePair<string>("hello",greetings));
	cout<<myMap.output()<<endl;



	return 0;
}