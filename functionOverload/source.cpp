#include "function_overload.h"
#include <iostream>

using std::cout;
using std::endl;

int main(){
	cout<<mul<int>(9,9)<<endl;
	cout<<mul<string>(55, 4)<<endl;
	return 0;
}