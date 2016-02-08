#include <iostream>
	using std::cout;
	using std::endl;
class ConstructAddress{


public:
	ConstructAddress(){
		cout<<"Object created at "<<this<<" by Default Construcotr." <<endl;
	}
	ConstructAddress(int x){
		cout<<"Object created at "<<this<<" by Int Construcotr." <<endl;
	}
	ConstructAddress(const ConstructAddress& obj){
		cout<<"Object created at "<<this<<" by Copy Construcotr." <<endl;
	}
	~ConstructAddress(){
		cout<<"Object destoried at "<<this<<" by Destrucotr." <<endl;
	}
};



int main(){
	ConstructAddress a;
	ConstructAddress b(10);
	ConstructAddress c(a);
	ConstructAddress& d = c;
	cout<<&d<<endl;
}