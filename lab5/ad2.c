#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t childPid;
    int status;

    // Create a child process
    if ((childPid = fork()) == 0) {
        // This is the child process

        // Display the PID of the parent before becoming orphan
        printf("Child: My parent's PID before becoming orphan: %d\n", getppid());

        // Sleep for a while to delay termination
        sleep(5);

        // Display the PID of the parent after becoming orphan
        printf("Child: My parent's PID after becoming orphan: %d\n", getppid());

        // Exit with a status code
        exit(42);
    } else if (childPid > 0) {
        // This is the parent process

        // Wait for the child process to terminate
        wait(&status);

        // Display the PID of the child
        printf("Parent: My child's PID: %d\n", childPid);

        // Display the exit return code of the child
        printf("Parent: Child's exit return code: %d\n", WEXITSTATUS(status));
    } else {
        perror("Error forking process");
        return 1;
    }

    return 0;
}
