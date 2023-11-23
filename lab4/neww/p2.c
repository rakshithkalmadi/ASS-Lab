#include <stdio.h>
#include <sys/stat.h>

int main(int argc,char* argv[]) {
    char *filename=argv[1];

    // Input the filename

    // Structure to store file information
    struct stat fileStat;

    // Use stat function to get file information
    if (stat(filename, &fileStat) == 0) {
        // Print out the complete stat structure
        printf("File Information for %s:\n", filename);
        printf("=====================================\n");
        printf("File Size: \t\t%ld bytes\n", fileStat.st_size);
        printf("Number of Links: \t%ld\n", fileStat.st_nlink);
        printf("Inode Number: \t\t%ld\n", fileStat.st_ino);
        printf("File Permissions: \t");
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
        printf("Device ID: \t\t%ld\n", fileStat.st_dev);
        printf("Number of Blocks: \t%ld\n", fileStat.st_blocks);
        // Add more fields as needed

    } else {
        // Print an error message if the file doesn't exist or there was an error
        perror("Error");
    }

    return 0;
}
