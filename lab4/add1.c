#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    char dirName[100];

    // Input the directory name
    printf("Enter the directory name: ");
    scanf("%s", dirName);

    // Open the directory
    DIR *dir = opendir(dirName);

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Create the full path of the file
        char fullPath[256];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dirName, entry->d_name);

        // Use stat function to get file information
        if (stat(fullPath, &fileStat) == 0) {
            // Print the inode number
            printf("File: %s, Inode: %ld\n", entry->d_name, fileStat.st_ino);
        } else {
            perror("Error getting file information");
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
