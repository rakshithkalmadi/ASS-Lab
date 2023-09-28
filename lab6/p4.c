#include <stdio.h>
#include <pthread.h>

int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void *cal(void *param)
{
    int opt = (int)param;
    int sum;
    for(int i=0;i<=10;i++){
        if(opt==0){
            if(a[i]%2==0){
                sum+=a[i];
            }
        }
        if(opt==1){
            if(a[i]%2==1){
                sum+=a[i];
            }
        }

    }
    return (void*)sum;
}
int main(int argc, char const *argv[])
{
    int sum1, sum2;
    pthread_t thread1, thread2;
    pthread_create(&thread1, 0, cal, (void *)0);
    pthread_create(&thread2, 0, cal, (void *)1);
    pthread_join(thread1, (void **)&sum1);
    pthread_join(thread2, (void **)&sum2);
    printf("sum1 : %d\n", sum1);
    printf("sum2 : %d\n", sum2);
    return 0;
}
