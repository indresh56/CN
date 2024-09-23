#include <stdio.h>
#include <signal.h>

void sigusr1_handler(int sig) {
    printf("Caught SIGUSR1 signal: %d\n", sig);
}

int main() {
    // Set up a signal handler for SIGUSR1
    signal(SIGUSR1, sigusr1_handler);

    // Raise SIGUSR1 signal to self
    raise(SIGUSR1);

    return 0;
}
