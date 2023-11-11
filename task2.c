#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 5

void threadFunction(char *name, char *str, int num) {
    for (int i = 1; i <= num; ++i) {
        printf("Thread %s. %s %d\n", name, str, i);
        sleep(rand() % 2);
    }
}

int main() {
    pid_t pid;

    for (int i = 0; i < NUM_THREADS; ++i) {
        pid = fork();

        if (pid == -1) {
            perror("Error creating process");
            return EXIT_FAILURE;
        }

        if (pid == 0) {
            char name[20];
            char str[50];
            sprintf(name, "Thread%d", i + 1);
            sprintf(str, "Str");
            threadFunction(name, str, NUM_ITERATIONS);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        wait(NULL);
    }

    return 0;
}