#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 10

void *childThreadFunction(void *arg) {
    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t childThread;

    if (pthread_create(&childThread, NULL, childThreadFunction, NULL) != 0) {
        perror("Error creating thread");
        return EXIT_FAILURE;
    }

    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }

    if (pthread_join(childThread, NULL) != 0) {
        perror("Error joining thread");
        return EXIT_FAILURE;
    }

    return 0;
}