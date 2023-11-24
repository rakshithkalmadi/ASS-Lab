#include<stdio.h>
#include<pthread.h>
#include <stdint.h>


int a[10]={1,-1,1,-2,10};

void *val(void* param){
    int sum;
    for(int i=0;i<10;i++){
        if(a[i]>0){
            sum+=a[i];
        }
    }
    return (void *)(intptr_t)sum;

}
int main(int argc, char const *argv[])
{
    /* code */
    int sum;
    pthread_t pt;
    pthread_create(&pt,0,val,0);
    // pthread_join(pt,&sum);
    pthread_join(pt,(void**)&sum);
    printf("Sum is %d\n",sum);
    return 0;
}


// #include <stdio.h>
// #include <pthread.h>
// #include <stdint.h>

// // Structure to hold parameters for the thread function
// struct ThreadParams {
//     int *arr;
//     int size;
// };

// // Thread function to calculate the sum of positive elements in the array
// void *val(void *param) {
//     struct ThreadParams *params = (struct ThreadParams *)param;

//     int sum = 0;
//     for (int i = 0; i < params->size; i++) {
//         if (params->arr[i] > 0) {
//             sum += params->arr[i];
//         }
//     }

//     pthread_exit((void *)(intptr_t)sum);
// }

// int main() {
//     int a[10] = {1, -1, 1, -2, 10, -3, 4, -5, 6, -7};

//     pthread_t pt;
//     struct ThreadParams params = {a, 10};

//     pthread_create(&pt, NULL, val, (void *)&params);

//     int sum;
//     pthread_join(pt, (void **)&sum);

//     printf("Sum of positive elements is %d\n", sum);

//     return 0;
// }
