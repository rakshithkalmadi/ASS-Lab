#include<stdio.h>
#include<pthread.h>
void *tfunction(void *param){
    int id = (int)param;
    printf("In the thread function for %d!!\n",id);
    return (void*)id+1;
}
int main(int argc, char const *argv[])
{
    pthread_t thread[10];
    int returnValue[10];
    for(int i=0;i<5;i++){
        pthread_create(&thread[i],0,&tfunction,(void*)i);
    }
    for(int i=0;i<5;i++){
        pthread_join(&thread[i],(void**)&returnValue[i]);
        printf("End thread %d",returnValue[i]);
    }
    printf("In the main thread\n");
    return 0;
}
