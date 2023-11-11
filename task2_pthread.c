#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 5

struct ThreadParams {
    char name[20];
    char str[50];
    int num;
};

void *threadFunction(void *arg) {
    struct ThreadParams *params = (struct ThreadParams *) arg;

    for (int i = 1; i <= params->num; ++i) {
        printf("Thread %s. %s %d\n", params->name, params->str, i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadParams threadParams[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        sprintf(threadParams[i].name, "Thread%d", i + 1);
        sprintf(threadParams[i].str, "Str");
        threadParams[i].num = NUM_ITERATIONS;

        if (pthread_create(&threads[i], NULL, threadFunction, (void *)&threadParams[i]) != 0) {
            perror("Error creating thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error joining thread");
            return EXIT_FAILURE;
        }
    }

    return 0;
}