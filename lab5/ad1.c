#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t childPid;

    // Create a child process
    if ((childPid = fork()) == 0) {
        // This is the child process

        // Display the PID of the parent before becoming orphan
        printf("Child: My parent's PID before becoming orphan: %d\n", getppid());

        // Sleep for a while to delay termination
        sleep(5);

        // Display the PID of the parent after becoming orphan
        printf("Child: My parent's PID after becoming orphan: %d\n", getppid());
    } else if (childPid > 0) {
        // This is the parent process

        // Sleep to allow the child to become orphan
        sleep(2);

        // Display the PID of the child
        printf("Parent: My child's PID: %d\n", childPid);

        // Parent process exits, making the child an orphan
        exit(0);
    } else {
        perror("Error forking process");
        return 1;
    }

    return 0;
}
