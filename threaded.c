#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <pthread.h>

#define MOD 5
#define SIZE_1 10
#define SIZE_2 100
#define SIZE_3 1000
#define NUM_THREADS 4  // You can adjust the number of threads

// Data structure to pass information to threads
struct ThreadData {
    int (*arrc)[SIZE_3];
    int (*arr)[SIZE_3];
    int (*arrb_transposed)[SIZE_3];
    int start_row;
    int end_row;
};

// Thread function for matrix multiplication
void *multiplyMatricesThread(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < SIZE_3; j++) {
            __m256i sum = _mm256_setzero_si256();  // Initialize the sum to zero
            for (int k = 0; k < SIZE_3; k += 8) {
                __m256i row = _mm256_loadu_si256((__m256i *)&(data->arr[i][k]));
                __m256i col = _mm256_loadu_si256((__m256i *)&(data->arrb_transposed[j][k]));
                __m256i vec = _mm256_mullo_epi32(row, col);
                sum = _mm256_add_epi32(sum, vec);
            }
            int result[8];
            _mm256_storeu_si256((__m256i *)result, sum);
            long total = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];
            data->arrc[i][j] = total;
        }
    }

    pthread_exit(NULL);
}

// Function to perform matrix multiplication using multiple threads
void multiplyMatricesParallel(int arrc[SIZE_3][SIZE_3], int arr[SIZE_3][SIZE_3], int arrb_transposed[SIZE_3][SIZE_3]) {
    pthread_t threads[NUM_THREADS];
    struct ThreadData threadData[NUM_THREADS];

    // Divide the workload among threads
    int rows_per_thread = SIZE_3 / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].arrc = arrc;
        threadData[i].arr = arr;
        threadData[i].arrb_transposed = arrb_transposed;
        threadData[i].start_row = i * rows_per_thread;
        threadData[i].end_row = (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiplyMatricesThread, (void *)&threadData[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main(void) {
    // Initialization (unchanged)

    int arr[SIZE_3][SIZE_3];
    int arrb[SIZE_3][SIZE_3];
    int arrb_transposed[SIZE_3][SIZE_3];
    int arrc[SIZE_3][SIZE_3];

    // Transposing Matrix b's (unchanged)

    // Initializing the time (unchanged)

    // Multiply for SIZE_3 elements in parallel
    clock_t start = clock();
    multiplyMatricesParallel(arrc, arr, arrb_transposed);
    clock_t end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_3 elements Time taken for execution : %f \n", time_taken);

    return 0;
}
