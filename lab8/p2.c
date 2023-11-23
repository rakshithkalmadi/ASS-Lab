#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

// Shared data
int sharedData = 0;
int readersCount = 0;

// Semaphores
sem_t mutex, wrt;

// Function prototypes
void* reader(void* arg);
void* writer(void* arg);

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader and writer threads
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_create(&readerThreads[i], NULL, reader, (void*)(intptr_t)i);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_create(&writerThreads[i], NULL, writer, (void*)(intptr_t)i);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

void* reader(void* arg) {
    int readerID = (intptr_t)arg;

    while (1) {
        // Reader entry section
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Read shared data
        printf("Reader %d is reading: %d\n", readerID, sharedData);

        // Reader exit section
        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);

        // Simulate some delay
        sleep(1);
    }

    return NULL;
}

void* writer(void* arg) {
    int writerID = (intptr_t)arg;

    while (1) {
        // Writer entry section
        sem_wait(&wrt);

        // Write to shared data
        sharedData++;
        printf("Writer %d is writing: %d\n", writerID, sharedData);

        // Writer exit section
        sem_post(&wrt);

        // Simulate some delay
        sleep(1);
    }

    return NULL;
}
