#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

volatile sig_atomic_t keep_running = 1;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        keep_running = 0;
    }
}

void* worker_func(void* arg) {
    long id = (long)arg;
    while (keep_running) {
        printf("Thread %ld running...\n", id);
        sleep(1);
    }
    printf("Thread %ld exiting.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("Cannot catch SIGINT\n");
    }

    pthread_create(&t1, NULL, worker_func, (void*)1);
    pthread_create(&t2, NULL, worker_func, (void*)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads cleanly exited. Goodbye.\n");
    return 0;
}
