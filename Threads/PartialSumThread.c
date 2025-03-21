#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 10

int array[ARRAY_SIZE];

void* sum_part(void* arg) {
    int index = *(int*)arg; // Retrieve the thread index
    int start = index * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);
    
    int* thread_sum = (int*)malloc(sizeof(int)); // Allocate memory to store partial sum
    *thread_sum = 0;
    for (int i = start; i < end; i++) {
        *thread_sum += array[i];
    }
    
    pthread_exit(thread_sum); // Exit thread and return pointer to computed partial sum
}

int main() {
    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS]; // To pass unique index to each thread
    int total_sum = 0;
    
    // Initialize the array with values (e.g., 1 to 1000)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, sum_part, &indices[i]);
    }
    
    // Wait for all threads to finish and collect results
    for (int i = 0; i < NUM_THREADS; i++) {
        int* result_sum;
        pthread_join(threads[i], (void**)&result_sum); // Retrieve pointer to the returned partial sum
        total_sum += *result_sum; // Accumulate the partial sum from each thread
        free(result_sum); // Free dynamically allocated memory after use to prevent memory leak
    }
    
    printf("Total sum: %d\n", total_sum);
    return 0;
}
