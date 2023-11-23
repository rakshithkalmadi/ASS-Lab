#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Shared data
int sharedResource = 0;

// Semaphores
sem_t semaphore1, semaphore2;

// Function prototypes
void* process1(void* arg);
void* process2(void* arg);

int main() {
    // Initialize semaphores
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 1);

    // Create threads
    pthread_t thread1, thread2;

    // Start both threads
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process2, NULL);

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy semaphores
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);

    return 0;
}

void* process1(void* arg) {
    while (1) {
        // Process 1 entry section
        sem_wait(&semaphore1);

        // Simulate some processing
        printf("Process 1 is in critical section (sharedResource: %d)\n", sharedResource);
        sharedResource++;

        // Simulate some delay
        sleep(1);

        // Process 1 exit section
        sem_post(&semaphore1);

        // Process 1 tries to enter the critical section of Process 2
        sem_wait(&semaphore2);

        // Simulate some processing
        printf("Process 1 is accessing Process 2's critical section (sharedResource: %d)\n", sharedResource);

        // Simulate some delay
        sleep(1);

        // Process 1 exit section
        sem_post(&semaphore2);
    }

    return NULL;
}

void* process2(void* arg) {
    while (1) {
        // Process 2 entry section
        sem_wait(&semaphore2);

        // Simulate some processing
        printf("Process 2 is in critical section (sharedResource: %d)\n", sharedResource);
        sharedResource--;

        // Simulate some delay
        sleep(1);

        // Process 2 exit section
        sem_post(&semaphore2);

        // Process 2 tries to enter the critical section of Process 1
        sem_wait(&semaphore1);

        // Simulate some processing
        printf("Process 2 is accessing Process 1's critical section (sharedResource: %d)\n", sharedResource);

        // Simulate some delay
        sleep(1);

        // Process 2 exit section
        sem_post(&semaphore1);
    }

    return NULL;
}
