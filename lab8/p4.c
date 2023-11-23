#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>

#define MAX_CUSTOMERS 5

// Shared data
int waitingCustomers = 0;
sem_t customerSemaphore, barberSemaphore, accessSeatsSemaphore;

// Function prototypes
void* barber(void* arg);
void* customer(void* arg);

int main() {
    // Initialize semaphores
    sem_init(&customerSemaphore, 0, 0);
    sem_init(&barberSemaphore, 0, 0);
    sem_init(&accessSeatsSemaphore, 0, 1);

    // Create barber thread
    pthread_t barberThread;
    pthread_create(&barberThread, NULL, barber, NULL);

    // Create customer threads
    pthread_t customerThreads[MAX_CUSTOMERS];
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        pthread_create(&customerThreads[i], NULL, customer, (void*)(intptr_t)i);
    }

    // Join threads
    pthread_join(barberThread, NULL);
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        pthread_join(customerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&customerSemaphore);
    sem_destroy(&barberSemaphore);
    sem_destroy(&accessSeatsSemaphore);

    return 0;
}

void* barber(void* arg) {
    while (1) {
        // Wait for a customer to arrive
        sem_wait(&customerSemaphore);

        // Acquire access to seats
        sem_wait(&accessSeatsSemaphore);
        waitingCustomers--;

        // Signal the barber that a customer is ready
        sem_post(&barberSemaphore);

        // Release access to seats
        sem_post(&accessSeatsSemaphore);

        // Simulate cutting hair
        printf("Barber is cutting hair\n");
        sleep(1);
    }

    return NULL;
}

void* customer(void* arg) {
    int customerID = (intptr_t)arg;

    while (1) {
        // Acquire access to seats
        sem_wait(&accessSeatsSemaphore);

        if (waitingCustomers < MAX_CUSTOMERS) {
            // Increment the number of waiting customers
            waitingCustomers++;

            // Signal the barber that a customer has arrived
            sem_post(&customerSemaphore);

            // Release access to seats
            sem_post(&accessSeatsSemaphore);

            // Wait for the barber to finish
            sem_wait(&barberSemaphore);

            // Simulate getting a haircut
            printf("Customer %d is getting a haircut\n", customerID);
            sleep(1);
        } else {
            // Release access to seats if no more seats are available
            sem_post(&accessSeatsSemaphore);

            // Simulate leaving if no seats are available
            printf("Customer %d left - No seats available\n", customerID);
            sleep(1);
        }
    }

    return NULL;
}
