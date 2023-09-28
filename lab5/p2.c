#include<stdio.h>
// #include<stdlib.h>
#include<sys/types.h>//Used for pid_t
// #include<sys/wait.h>
// #include<unistd.h>
int main(int argc, char const *argv[])
{
    /* code */
    pid_t pid;
    printf("Parent process starts\n");
    pid=fork();
    if(pid<0){
        perror("Fork Failed");
        exit(1);
    }else if(pid==0){
        printf("Child process started\n");
        execl("./p1","p1",NULL);
        perror("Exec failed");
        exit(1);
    }else{
        wait(NULL);
        printf("Parent process completed\n");
    }
    return 0;
}
