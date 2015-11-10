#include <iostream>
#include <vector>


using namespace std;

int main(){
	vector<int> myArray;
	for(int i =0; i<100; i++){
		myArray.push_back(i);
	}
	int ones = 0;
	int twos = 0;
	for(int i=0; i<100; i++){
		twos=twos|ones&myArray[i];
		ones = ones ^ myArray[i];
		cout<<twos<<"      "<<ones<<endl;
	}





	return 0;
}