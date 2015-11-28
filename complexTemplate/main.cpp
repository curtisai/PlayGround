#include "complexTemplate.h"



int main(){
	One<std::string> myString = std::string("the beast");
	Two<std::string, One> myVector;
	for(int i = 0; i < 100; i++){
		std::string k = std::to_string(i);
		myVector.push(k);
	}
	myVector.show();

	return 0;
}