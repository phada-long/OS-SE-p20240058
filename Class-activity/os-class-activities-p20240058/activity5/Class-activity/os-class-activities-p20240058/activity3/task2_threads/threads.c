/* threads.c — POSIX Threads demonstration with a Race Condition */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

int shared_counter = 0;

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d (TID: %lu): starting execution loop...\n", id, (unsigned long)pthread_self());

    /* High iteration count makes the race condition obvious */
    for (int i = 0; i < 100000; i++) {
        shared_counter++;  /* Race condition occurs here due to lack of synchronization */
    }

    printf("Thread %d (TID: %lu): completed work loop.\n", id, (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Main thread (TID: %lu): spawning %d concurrent workers...\n", (unsigned long)pthread_self(), NUM_THREADS);
    printf("PID: %d — Check threads now via ps or htop monitoring\n\n", getpid());

    /* Create the worker threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, worker, &thread_ids[i]) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for all worker threads to complete */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads finished execution.\n");
    printf("Expected counter value: %d\n", NUM_THREADS * 100000);
    printf("Actual counter value:   %d\n", shared_counter);

    if (shared_counter != NUM_THREADS * 100000) {
        printf("⚠️ Race condition detected! Counter value is inaccurate.\n");
    }

    return 0;
}
