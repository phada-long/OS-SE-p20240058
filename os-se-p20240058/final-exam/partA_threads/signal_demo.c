#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void handle_signal(int signum) {
    if (signum == SIGINT) {
        printf("\n[signal_demo] Caught SIGINT (interactive interrupt, Ctrl+C).\n");
    } else if (signum == SIGTERM) {
        printf("\n[signal_demo] Caught SIGTERM (polite termination request).\n");
    }
    printf("[signal_demo] Cleaning up... goodbye.\n");
    keep_running = 0;
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    printf("[signal_demo] PID=%d running. Send SIGINT (Ctrl+C) or SIGTERM to stop.\n", getpid());

    int count = 0;
    while (keep_running) {
        printf("[signal_demo] Looping... iteration %d (PID %d)\n", count++, getpid());
        sleep(1);
    }

    printf("[signal_demo] Exited cleanly.\n");
    return 0;
}
