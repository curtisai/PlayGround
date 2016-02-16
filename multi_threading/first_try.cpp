#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 5


void *PrintHello(void *thread_id){
	long tid;
	tid = (long) thread_id;
	
	cout << "Hello, world. Thread ID, " << tid << "\n";
	
	pthread_exit(NULL);
}

struct thread_data{
	int thread_id;
	char* message;
};

void *PrintHelloWithMsg(void *thread_arg){
	struct thread_data *my_data;
	my_data = (struct thread_data*) thread_arg;
    cout << "Thread ID : " << my_data->thread_id << "\n" ;
    cout << " Message : " << my_data->message << "\n";

   pthread_exit(NULL);
}

int main(){
	pthread_t thread[NUM_THREADS];
	pthread_t thread_with_message[NUM_THREADS];
    struct thread_data td[NUM_THREADS];

	int rc;
	int i;
	for( i = 0; i < NUM_THREADS; i++ ){
		cout << "main(): create thread, " << i << "\n";
		rc = pthread_create( &thread[i], NULL, PrintHello, (void*)i );
		if(rc){
			cout << "unable to create thread, " << rc << ". rc is " << rc << "\n";
			exit(-1);
		}
		cout <<"main(): creating msg thread, " << i << "\n";
        td[i].thread_id = i;
        td[i].message = "This is message\n";

		rc = pthread_create( &thread_with_message[i], NULL, PrintHelloWithMsg, (void*)&td[i]);
		if(rc){
			cout << "unable to create thread, " << rc << ". rc is " << rc << "\n";
			exit(-1);
		}
	}

	pthread_exit(NULL); // with this line, all created threads will keep executing
	                    // until they finish. Other wise, those threads will be
	                    // terminated as soon as main() finishes.
}

/*
    Note:
    pthread_create (thread, attr, start_routine, arg)

    pthread_create creates a new thread and makes it 
    executable. This routine can be called any number 
    of times from anywhere within your code. 


    Here is the description of the parameters:

    thread   |    An opaque, unique identifier for 
             |    the new thread returned by the subroutine.
    ---------+---------------------------------------------
    attr     |    An opaque attribute object that may be 
             |    used to set thread attributes. You can 
             |    specify a thread attributes object, or 
             |    NULL for the default values.
    ---------+---------------------------------------------
    start_rt |    The C++ routine that the thread will execute 
             |    once it is created.
    ---------+---------------------------------------------
    arg      |    A single argument that may be passed to 
             |    start_routine. It must be passed by reference 
             |    as a pointer cast of type void. NULL may be 
             |    used if no argument is to be passed.
    -------------------------------------------------------

    pthread_exit() is used to explicitly exit a thread.

    Typically, the pthread_exit() routine is called after 
    a thread has completed its work and is no longer 
    required to exist.

*/