#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    char* shm, * data;
    key = ftok("shared_memory_key", 'R');
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shm = shmat(shmid, NULL, 0);
    if (shm == (char*)-1) {
        perror("shmat");
        exit(1);
    }
    data = malloc(SHM_SIZE);
    strncpy(data, shm, SHM_SIZE);
    printf("Data read from shared memory: %s\n", data);
    shmdt(shm);
    return 0;
}