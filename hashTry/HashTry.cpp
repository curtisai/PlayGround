#include <string>
#include <iostream>
#include <queue>
#include <random>


using namespace std;


unsigned int stringSum(const string& key){
	unsigned int res = 0;
	for(int i = 0; i < key.size(); i++){
		//res=(res<<8)^(res>>24)^key[i];
		res ^= key[i] + 0x9e3779b9 + (res << 6) + (res >> 2);
		//res = 65599*res+key[i];
	}
	return res;//^(res>>16);
}

unsigned int hashing(unsigned int key, int count){
	return (key%97);
}

unsigned int hashingAgain(unsigned int key){
	return (17*key+2851)%100;	//table size should be prime
}


unsigned int hashFunc(const string& key, int count){
	//return stringSum(key)%47+2;
	return hashingAgain(hashing(stringSum(key), count));
}

int main(){
	priority_queue<int> myqueue;
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(0, 1000000);
	//int currentGuess = dist(gen);
	
	int count = 0;
	
	while(count<200){
		int currentOne = dist(gen);
		cout<<currentOne<<"        "<<stringSum(to_string(currentOne))<<endl;
		int hashres = hashFunc(std::to_string(currentOne), count);
		myqueue.push(hashres);
		count++;
	}
	int k =0;
	int m =0;
	int currentTop = myqueue.top();
	myqueue.pop();
	while(!myqueue.empty()){
		m++;
		if(currentTop!=myqueue.top()){
			cout<<myqueue.top()<<"    "<<k<<"    "<<m<<endl;
			k++;
			m=0;
			currentTop = myqueue.top();
			myqueue.pop();
		}
		else{
			myqueue.pop();
		}
		
		
	}
	return 0;
}