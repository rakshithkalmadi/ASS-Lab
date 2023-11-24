// row and col sum 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 3

int matrix[MATRIX_SIZE][MATRIX_SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int rowSums[MATRIX_SIZE] = {0};
int colSums[MATRIX_SIZE] = {0};

// Structure to hold parameters for the thread function
struct tParam {
    int index;
};

// Thread function to calculate row sum
void *calculateRowSum(void *param) {
    struct tParam *params = (struct tParam *)param;
    int rowIndex = params->index;

    for (int j = 0; j < MATRIX_SIZE; j++) {
        rowSums[rowIndex] += matrix[rowIndex][j];
    }

    pthread_exit(NULL);
}

// Thread function to calculate column sum
void *calculateColSum(void *param) {
    struct tParam *params = (struct tParam *)param;
    int colIndex = params->index;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        colSums[colIndex] += matrix[i][colIndex];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t rowThreads[MATRIX_SIZE], colThreads[MATRIX_SIZE];
    struct tParam rowParams[MATRIX_SIZE], colParams[MATRIX_SIZE];

    // Create threads for row sums
    for (int i = 0; i < MATRIX_SIZE; i++) {
        rowParams[i].index = i;
        pthread_create(&rowThreads[i], NULL, calculateRowSum, (void *)&rowParams[i]);
    }

    // Create threads for column sums
    for (int j = 0; j < MATRIX_SIZE; j++) {
        colParams[j].index = j;
        pthread_create(&colThreads[j], NULL, calculateColSum, (void *)&colParams[j]);
    }

    // Join threads for row sums
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pthread_join(rowThreads[i], NULL);
    }

    // Join threads for column sums
    for (int j = 0; j < MATRIX_SIZE; j++) {
        pthread_join(colThreads[j], NULL);
    }

    // Print row sums
    printf("Row Sums:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%d ", rowSums[i]);
    }
    printf("\n");

    // Print column sums
    printf("Column Sums:\n");
    for (int j = 0; j < MATRIX_SIZE; j++) {
        printf("%d ", colSums[j]);
    }
    printf("\n");

    return 0;
}
