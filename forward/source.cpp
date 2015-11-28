#include <iostream>
#include <string>
using namespace std;
void innerFunc(int a, string b){
	cout << "the integer is "<< a <<", and the string is "<< b << endl;
}

template<typename T, typename P>
void outterFunc(T& a, P& b){
	innerFunc(a, b);
}

template<typename T, typename P>
void constFunc(const T& a, const P& b){
	innerFunc(a, b);
}

template<typename A1> 
void f(A1 & a1){
    std::cout << 1 << std::endl;
}

void f(long const &){
    std::cout << 2 << std::endl;
}


int main(){
	int a = 100;
	string b = "hello, world";
	outterFunc(a, b);

	constFunc(100, "hello, world");
	f(5);              // prints 2 under the current rules, 1 after the change
    int const n(5);
    f(n);              // 1 in both cases

	return 0;
}