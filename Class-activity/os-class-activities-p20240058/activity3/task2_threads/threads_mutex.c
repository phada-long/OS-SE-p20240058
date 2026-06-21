/* threads_mutex.c — Threads with Mutex Synchronization */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

int shared_counter = 0;
/* Initialize the POSIX Mutex lock object */
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d (TID: %lu): starting execution loop...\n", id, (unsigned long)pthread_self());

    for (int i = 0; i < 100000; i++) {
        /* Acquire lock before entering critical section */
        pthread_mutex_lock(&counter_mutex);
        
        shared_counter++;  /* Safe inside critical section */
        
        /* Release lock immediately after update complete */
        pthread_mutex_unlock(&counter_mutex);
    }

    printf("Thread %d (TID: %lu): completed work loop.\n", id, (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Main thread (TID: %lu): spawning %d synchronized workers...\n", (unsigned long)pthread_self(), NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads finished execution.\n");
    printf("Expected counter value: %d\n", NUM_THREADS * 100000);
    printf("Actual counter value:   %d\n", shared_counter);

    if (shared_counter == NUM_THREADS * 100000) {
        printf("✅ Counter matches perfectly! Mutex lock successfully prevented race conditions.\n");
    }

    /* Destroy the Mutex lock object to clean up memory resources */
    pthread_mutex_destroy(&counter_mutex);
    return 0;
}
