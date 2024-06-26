#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUM_ITERATIONS 1000

int balance = 0;
pthread_mutex_t mutex;

void* deposit(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        balance++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* withdraw(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        balance--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    // Create deposit threads
    for (int i = 0; i < NUM_THREADS / 2; i++) {
        pthread_create(&threads[i], NULL, deposit, NULL);
    }

    // Create withdraw threads
    for (int i = 0; i < NUM_THREADS / 2; i++) {
        pthread_create(&threads[i + NUM_THREADS / 2], NULL, withdraw, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final balance: %d\n", balance);
    pthread_mutex_destroy(&mutex);
    return 0;
}
