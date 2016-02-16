#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define NUM_THREADS      5

void *wait(void *id){
	int i;
	long tid;

	tid = (long) i;

	sleep(1);
	cout << "sleeping in thread " << tid << "\n";
	cout << "Thread with id: " << tid << "...exiting.\n";
	pthread_exit(NULL);
}

int main(){
	int rc;
	int i;

	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for( int i = 0; i < NUM_THREADS; i++){
		cout << "main(): create thread, " << i << "\n";
		rc = pthread_create( &threads[i], NULL, wait, (void*)i );

		if(rc){
			cout << "unable to create thread: " << rc << "\n";
			exit(-1);
		}
	}

	//free attributes and wait for the other threads
	pthread_attr_destroy(&attr);
	for( int i = 0; i < NUM_THREADS; i++ ){
		rc = pthread_join(threads[i], &status);
		if(rc){
			cout << "fail to join: " << rc << "\n";
			exit(-1);
		}
		cout << "Main: completed thread id :" << i ;
        cout << "  exiting with status :" << status << endl;
	}
	cout << "Main: program exiting." << endl;
    pthread_exit(NULL);

}