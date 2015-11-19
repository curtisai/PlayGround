#include "map.h"
#include <string>
#include <iostream>


int main(){

	using namespace sgdm;
	using namespace sgdc;
	using std::string;
	using std::cout;
	using std::endl;
    using std::cin;

	CountingAllocator<ThePair<string>> alloc;
	Map<string, ThePair>* myMap;
	/*
    for (int k = 0; k < 10; k++) {
        myMap = new Map<string, ThePair>(&alloc);
        for (int i = 0; i < 100000; i++) {
            myMap->push(std::to_string(i), "hello");
            if(!myMap->has(std::to_string(i)))cout<<"fail to find"<<endl;
        }
        
        delete myMap;
    }
    */
    myMap = new Map<string, ThePair>(&alloc);
        for (int i = 0; i < 1000; i++) {
            myMap->push(std::to_string(i), "hello");
            if(!myMap->has(std::to_string(i)))cout<<"fail to find"<<endl;
        }
        string k = myMap->remove("10");
        cout<<k<<"   "<<myMap->has("10")<<endl;
    cout<<"input"<<endl;

   // DynamicArray<string> myValues = myMap->values();
    //DynamicArray<string> myKeys = myMap->keys();
    
    string x;
    cin>>x;

    delete myMap;
	




	return 0;
}