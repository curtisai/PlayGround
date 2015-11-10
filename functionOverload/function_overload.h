//This code is a experiment based on following link
//http://stackoverflow.com/questions/226144/overload-a-c-function-according-to-the-return-value


#include <string>
using std::string;
//Three ways of doing the overloading thing

//1 Explicitly differentiate the calls by typing

string mul(char c, int n){
	return string(n, c);
}

int mul(int i, int j){
	return i * j;
}

//2 Explicitly differentiate the calls by dummy pointer

int mul(int *, int i, int j){
	return i * j;
}

string mul(std::string *, char c, int n){
	return string(n, c);
}

//3 Explicity differentiate the calls by templating the return value
template<typename T>
T mul(int i, int j){
	const int k = 25; k = 36;
}

template<>
int mul<int>(int i, int j){
	return i * j;
}

template<>
string mul<string>(int i, int j){
	return string(j, static_cast<char>(i));
}
