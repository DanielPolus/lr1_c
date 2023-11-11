#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM_ITERATIONS 10

void childThreadFunction() {
    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
}

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error creating process");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        childThreadFunction();
    } else {
        for (int i = 1; i <= NUM_ITERATIONS; ++i) {
            printf("Main Thread. Iteration: %d\n", i);
            sleep(rand() % 3);
        }
    }
    return 0;
}