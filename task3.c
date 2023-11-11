#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 5
#define RANDOM_STOP 39


void *printString() {

    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(1);
    }

    pthread_exit(NULL);
}


void *generateRandomNumbers() {

    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        int randomNumber = rand() % 100;

        printf("Child Thread. Random Number: %d\n", randomNumber);

        if (randomNumber == RANDOM_STOP) {
            printf("%d number occured", RANDOM_STOP);
            pthread_exit(NULL);
        }

        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threadPrint, threadRandom;

    if (pthread_create(&threadPrint, NULL, printString, NULL) != 0) {
        perror("Error creating print thread");
        return EXIT_FAILURE;
    }


    if (pthread_create(&threadRandom, NULL, generateRandomNumbers, NULL) != 0) {
        perror("Error creating random thread");
        return EXIT_FAILURE;
    }


    if (pthread_join(threadPrint, NULL) != 0) {
        perror("Error joining print thread");
        return EXIT_FAILURE;
    }

    if (pthread_join(threadRandom, NULL) != 0) {
        perror("Error joining random thread");
        return EXIT_FAILURE;
    }


    printf("\nMain Thread: All threads have completed.\n");

    return 0;
}