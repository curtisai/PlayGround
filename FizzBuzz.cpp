#include<iostream>

int main(){
	using namespace std;

	for(int i=53;i<=191;i++){
		
		if(!(i%5))cout<<"Fizz";
		if(!(i%3))cout<<"Buzz";
		if((i%3)&&(i%5))cout<<i;

		cout<<endl;
	}
	return 0;
}
