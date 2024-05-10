#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        execl("/bin/ls", "ls", NULL);
        printf("This line will not be printed\n");
    } else {
        printf("Parent process: PID = %d\n", getpid());
        wait(&status);
        if (status>>8 == 1) {
            printf("Child process exited with status: %d\n", status>>8);
        } else {
            printf("Child process exited abnormally: %d\n", status>>8);
        }
    }
    return 0;
}