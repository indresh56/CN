#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void fun(int signal) {
    printf("Received signal %d\n", signal);

}

int main() {

    signal(SIGUSR1, fun);
    raise(SIGUSR1);


    return 0;
}
