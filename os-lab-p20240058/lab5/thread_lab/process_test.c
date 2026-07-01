#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 10;

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        global_var += 20;
        printf("Child process: global_var = %d\n", global_var);
    } else {
        wait(NULL);
        printf("Parent process: global_var = %d\n", global_var);
    }
    return 0;
}
