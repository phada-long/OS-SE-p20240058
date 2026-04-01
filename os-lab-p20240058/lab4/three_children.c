#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    for (i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Child %d (PID %d): sleeping 30s\n", i+1, getpid());
            sleep(30);
            exit(0);
        }
    }
    printf("Parent (PID %d): waiting for all children...\n", getpid());
    int j;
    for (j = 0; j < 3; j++) wait(NULL);
    printf("Parent: all children done.\n");
    return 0;
}
