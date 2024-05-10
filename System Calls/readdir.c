#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
    }
    printf("File opened\n");
    if (close(fd) == -1) {
        perror("close");
    }
    printf("File closed\n");
    struct stat fileStat;
    if (stat("example.txt", &fileStat) == -1) {
        perror("stat");
    }
    printf("File size: %ld bytes\n", fileStat.st_size);
    DIR* dir;
    struct dirent* entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");  
    }
    printf("Contents of the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}