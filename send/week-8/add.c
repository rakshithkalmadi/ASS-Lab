#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopstick[NUM_PHILOSOPHERS];
pthread_t philosopher[NUM_PHILOSOPHERS];

void *philosopher_action(void *id) {
    int philosopher_id = *((int *)id);
    int left_chopstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", philosopher_id);

        // Pick up chopsticks
        pthread_mutex_lock(&chopstick[left_chopstick]);
        pthread_mutex_lock(&chopstick[right_chopstick]);

        // Eating
        printf("Philosopher %d is eating\n", philosopher_id);

        // Put down chopsticks
        pthread_mutex_unlock(&chopstick[left_chopstick]);
        pthread_mutex_unlock(&chopstick[right_chopstick]);

        // Back to thinking
    }
}

int main() {
    int i;
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each chopstick
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosopher[i], NULL, philosopher_action, (void *)&philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (which will never happen in this case)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosopher[i], NULL);
    }

    // Destroy mutex locks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopstick[i]);
    }

    return 0;
}
