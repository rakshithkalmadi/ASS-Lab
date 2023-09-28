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

    // Wait for the thread to finish before exiting
    pthread_join(thread, NULL);

    return 0;

}



// When a child thread completes its execution, it can return a value to the main thread. This returned value can be accessed by the main thread using the pthread_join() function.

// pthread_join() Function: pthread_join() is a function used to wait for a specific thread to complete its execution. It takes two parameters:

// The first parameter is the handle of the thread that the main thread wants to wait for.
// The second parameter is either zero or the address of a pointer to a void type. If the second parameter is not zero, it will hold the value returned by the child thread.