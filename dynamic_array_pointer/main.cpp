#include "dynamic_array.h"
#include "copyClass.h"
#include <string>



using namespace std;


int main(){
	StevensDev::sgdm::DefaultAllocator<copyClass*> strPtrAlloc;
	StevensDev::sgdc::DynamicArray<copyClass*> pointerArray(&strPtrAlloc);

	for(int i = 0; i < 100; i++){
		copyClass* strPtr =  new copyClass();
		pointerArray.push(strPtr);
		delete strPtr;
	}
	//******************************************************
	copyClass* testPtr = new copyClass();
	copyClass testObj(*testPtr);
	delete testPtr;
	testObj.show();
	copyClass* temp =(copyClass*) ::operator new(sizeof(copyClass));
	cout << "before placement new \n";
	new (temp) copyClass(&testObj);
	cout << "after placement new \n";
	temp->show();
	delete temp;
	
	for(int i = 0; i < pointerArray.getLength(); i++){
		pointerArray[i]->show();
	}
	return 0;
}