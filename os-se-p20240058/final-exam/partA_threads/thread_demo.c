#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define NUM_THREADS 3

typedef struct {
    int id;
    int result;
} worker_data_t;

void *worker(void *arg) {
    worker_data_t *data = (worker_data_t *)arg;
    pid_t tid = (pid_t) syscall(SYS_gettid);
    data->result = (data->id + 1) * 10;
    printf("Worker %d: pthread_id=%lu kernel_tid=%d computed_value=%d\n",
           data->id, (unsigned long)pthread_self(), tid, data->result);
    sleep(2);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    worker_data_t data[NUM_THREADS];

    printf("Main process PID: %d\n", getpid());

    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].id = i;
        data[i].result = 0;
        if (pthread_create(&threads[i], NULL, worker, &data[i]) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
    }

    int total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total += data[i].result;
    }

    printf("Summary: all %d workers joined. Total of results = %d\n", NUM_THREADS, total);
    return 0;
}
