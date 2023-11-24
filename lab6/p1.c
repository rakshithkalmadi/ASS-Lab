#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* generateFibonacci(void* arg) {
    int n = *((int*)arg);
    int* fib = (int*)malloc(sizeof(int) * n);

    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // Create a pointer to the Fibonacci series bcz fib is out of scope

    return (void*)fib;
    // pthread_exit((void*)fib); -> you can use the above one
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <number_of_fibonacci_numbers>\n", argv[0]);
        return 1;
    }
    int num=atoi(argv[1]);
    pthread_t thread;
    pthread_create(&thread,0,generateFibonacci,&num);

    void* result;
    pthread_join(thread, &result);

    int* fib = (int*)result;

    printf("Fibonacci Series:\n");
    for (int i = 0; i < num; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(fib);

    return 0;
}
