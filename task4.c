#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_CATALAN 10
#define MAX_PRIME 10

int catalanNumbers[MAX_CATALAN];
int primeNumbers[MAX_PRIME];

int fact(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}
int catalanNumber(int n) {
    printf("cat -- %d | n -- %d | fact(n) -- %d\n",fact(2 * n) / ((fact(n + 1) * fact(n))), n, fact(n));
    return fact(2 * n) / ((fact(n + 1) * fact(n)));
}

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

void calculatePrimeNumbers(int n) {
    int count = 0;
    int num = 2;

    while (count < n) {
        if (isPrime(num)) {
            primeNumbers[count] = num;
            ++count;
        }
        ++num;
    }
}

void *catalanThreadFunction() {
    for (int i = 0; i < MAX_CATALAN; ++i) {
        catalanNumbers[i] = catalanNumber(i);
    }

    pthread_exit(NULL);
}

void *primeThreadFunction() {
    calculatePrimeNumbers(MAX_PRIME);

    pthread_exit(NULL);
}

int main() {
    pthread_t catalanThread, primeThread;

    if (pthread_create(&catalanThread, NULL, catalanThreadFunction, NULL) != 0) {
        perror("Error creating Catalan thread");
        return EXIT_FAILURE;
    }

    if (pthread_create(&primeThread, NULL, primeThreadFunction, NULL) != 0) {
        perror("Error creating prime thread");
        return EXIT_FAILURE;
    }

    if (pthread_join(catalanThread, NULL) != 0) {
        perror("Error joining Catalan thread");
        return EXIT_FAILURE;
    }

    if (pthread_join(primeThread, NULL) != 0) {
        perror("Error joining prime thread");
        return EXIT_FAILURE;
    }

    printf("Catalan Numbers: ");
    for (int i = 0; i < MAX_CATALAN; ++i) {
        printf("%d ", catalanNumbers[i]);
    }


    printf("\nPrime Numbers: ");
    for (int i = 0; i < MAX_PRIME; ++i) {
        printf("%d ", primeNumbers[i]);
    }

    return 0;
}