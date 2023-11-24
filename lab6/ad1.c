#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 3

int A[MATRIX_SIZE][MATRIX_SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int B[MATRIX_SIZE][MATRIX_SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int C[MATRIX_SIZE][MATRIX_SIZE];

// Structure to hold parameters for the thread function
struct ThreadParams {
    int row;
};

// Thread function to perform matrix multiplication
void *multiply(void *param) {
    struct ThreadParams *params = (struct ThreadParams *)param;
    int row = params->row;

    for (int j = 0; j < MATRIX_SIZE; j++) {
        C[row][j] = 0;
        for (int k = 0; k < MATRIX_SIZE; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MATRIX_SIZE];
    struct ThreadParams params[MATRIX_SIZE];

    // Create threads
    for (int i = 0; i < MATRIX_SIZE; i++) {
        params[i].row = i;
        pthread_create(&threads[i], NULL, multiply, (void *)&params[i]);
    }

    // Join threads
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix C
    printf("Result Matrix C:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
