#include<stdio.h>
#include<pthread.h>

void *thread_process(void *param){
    int id = (int)param;
    printf("Start thread %d\n",id);
    return (void*)id;
}

int main(int argc, char const *argv[])
{
    pthread_t thread[10];
    int return_value[10];
    for(int i=0;i<10;i++){
        pthread_create(&thread[i],0,&thread_process,(void*)i);
    }
    for(int i=0;i<10;i++){
        pthread_join(thread[i],(void**)&return_value[i]);
        printf("Enf thread : %d\n",return_value[i]);
    }
    

    return 0;
}
