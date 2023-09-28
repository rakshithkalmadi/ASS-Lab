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
