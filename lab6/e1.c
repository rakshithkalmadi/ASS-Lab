#include<pthread.h>
#include<stdio.h>

void *thread_execution(void* param){
    printf("In thread execution");
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    pthread_create(&thread,0,&thread_execution,0);
    printf("In the main thread");

// This will also wait for the process execution
    // sleep(1);

    // Wait for the thread to finish before exiting
    // pthread_join(thread, NULL);

    return 0;

}



// pthread_create(): This is a function provided by the pthread library to create a new thread. It takes several parameters, including:

// A pointer to a pthread_t structure: This is used to store the handle to the newly created thread.
// A pointer to a pthread attributes structure: This can be set to NULL if default attributes are to be used.
// The address of the routine to be executed in the new thread.
// A value or pointer to be passed as a parameter to the new thread's routine.