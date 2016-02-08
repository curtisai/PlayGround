#include "stack.h"
#include <string>
#include <iostream>



int main(){
	using std::string;
	using std::cout;
	using std::endl;
	using std::cin;

	char p[40];

	cin>>p;
	Stack<char[40]> stringStack;
	stringStack.push(p);
/*
	for(int i = 0; i < 100; i++){
	cout<<p[i]<<"    "<<*p++<<"    "<<sizeof(p)<<endl;
	}
*/

	return 0;
}