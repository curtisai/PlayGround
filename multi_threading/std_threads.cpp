#include <iostream>
#include <thread>


void callFromThread(){
	std::cout << "Hello, world \n";
}


int main(){
	//launch a thread
	std::thread t[10];
	for( int i = 0; i < 10; i++){
		t[i] = std::thread( callFromThread );
	}
	std::cout << "Launched from the main\n";

	//Join the threads with the main thread
    for ( int i = 0; i < 10; i++ ) {
    	t[i].join();
    }

    std::cout << "before return \n";
	return 0;
}