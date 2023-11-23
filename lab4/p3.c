#include <stdio.h>
#include <unistd.h>

int main() {
    char oldPath[100], newPath[100];

    printf("Enter the old path: ");
    scanf("%s", oldPath);

    printf("Enter the new path: ");
    scanf("%s", newPath);

    if (link(oldPath, newPath) == 0 && unlink(newPath) == 0) {
        printf("Hard link created and unlinked successfully. New path: %s\n", newPath);
    } else {
        perror("Error");
        return 1;
    }

    return 0;
}
