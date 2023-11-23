#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// Shared data
int buffer[BUFFER_SIZE];
int itemCount = 0;

// Semaphores
sem_t empty, full;

// Mutex for synchronization
pthread_mutex_t mutex;

// Function prototypes
void* producer(void* arg);
void* consumer(void* arg);

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* producer(void* arg) {
    int producedItems = 0;

    while (1) {
        // Produce item
        int item = rand() % 100;
        
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Check if the consumer has consumed at most 10 items less than produced
        if (itemCount <= 10) {
            buffer[itemCount++] = item;
            printf("Produced: %d (Total Produced: %d)\n", item, ++producedItems);
        } else {
            printf("Producer waiting as consumer is behind\n");
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        // Simulate some delay
        sleep(1);
    }

    return NULL;
}

void* consumer(void* arg) {
    int consumedItems = 0;

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Consume item
        int item = buffer[--itemCount];
        printf("Consumed: %d (Total Consumed: %d)\n", item, ++consumedItems);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // Simulate some delay
        sleep(1);
    }

    return NULL;
}
