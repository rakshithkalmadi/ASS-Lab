#include<stdio.h>
// #include<stdlib.h>
#include<sys/types.h>//Used for pid_t
// #include<sys/wait.h>
// #include<unistd.h>
int main(int argc, char const *argv[])
{
    /* code */
    pid_t pid;
    printf("P1 Parent process starts\n");
    pid=fork();
    if(pid<0){
        perror("Fork Failed");
        exit(1);
    }else if(pid==0){
        printf("P1 Child process started\n");
        sleep(3);
        printf("P1 Child process completed\n");
    }else{
        wait(NULL);
        printf("P1 Parent process completed\n");
    }
    return 0;
}
