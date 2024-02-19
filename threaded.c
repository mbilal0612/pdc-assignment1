#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <pthread.h>

#define MOD 5
#define SIZE 10
#define SIZE_1 10
#define SIZE_2 100
#define SIZE_3 1000
#define NUM_THREADS 4 // You can adjust the number of threads

// Data structure to pass information to threads
typedef struct
{
    int start;
    int end;
    int size;
    int (*arr)[SIZE_1];
    int (*arrb)[SIZE_1];
    int (*arrb_transposed)[SIZE_1];
    int (*arrc)[SIZE_1];

} thread_data_t;

typedef struct
{
    int start;
    int end;
    int size;
    int (*arr)[SIZE_2];
    int (*arrb)[SIZE_2];
    int (*arrb_transposed)[SIZE_2];
    int (*arrc)[SIZE_2];

} thread_data_t_2;

typedef struct
{
    int start;
    int end;
    int size;
    int (*arr)[SIZE_3];
    int (*arrb)[SIZE_3];
    int (*arrb_transposed)[SIZE_3];
    int (*arrc)[SIZE_3];

} thread_data_t_3;

// Thread function for matrix multiplication for SIZE_1 elements
void *multiplyMatricesThread(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;

    for (int i = data->start; i < data->end; i++)
    {
        for (int j = 0; j < SIZE_1; j++)
        {
            int temp_sum = 0;
            for (int k = 0; k < SIZE_1; k++)
            {
                temp_sum += data->arr[i][k] * data->arrb_transposed[j][k];
            }
            data->arrc[i][j] = temp_sum;
        }
    }

    pthread_exit(NULL);
}

// Thread function for matrix multiplication for SIZE_2 elements
void *multiplyMatricesThread2(void *arg)
{
    thread_data_t_2 *data = (thread_data_t_2 *)arg;

    for (int i = data->start; i < data->end; i++)
    {
        for (int j = 0; j < SIZE_2; j++)
        {
            int temp_sum = 0;
            for (int k = 0; k < SIZE_2; k++)
            {
                temp_sum += data->arr[i][k] * data->arrb_transposed[j][k];
            }
            data->arrc[i][j] = temp_sum;
        }
    }

    pthread_exit(NULL);
}

// Thread function for matrix multiplication for SIZE_3 elements
void *multiplyMatricesThread3(void *arg)
{
    thread_data_t_3 *data = (thread_data_t_3 *)arg;

    for (int i = data->start; i < data->end; i++)
    {
        for (int j = 0; j < SIZE_3; j++)
        {
            int temp_sum = 0;
            for (int k = 0; k < SIZE_3; k++)
            {
                temp_sum += data->arr[i][k] * data->arrb_transposed[j][k];
            }
            data->arrc[i][j] = temp_sum;
        }
    }

    pthread_exit(NULL);
}

// Function to perform matrix multiplication using multiple threads for SIZE_1 elements
void multiplyMatricesParallel(int arrc[SIZE_1][SIZE_1], int arr[SIZE_1][SIZE_1], int arrb_transposed[SIZE_1][SIZE_1])
{
    pthread_t threads[NUM_THREADS];
    thread_data_t threadData[NUM_THREADS];

    // Divide the workload among threads
    int rows_per_thread = SIZE_1 / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].arrc = arrc;
        threadData[i].arr = arr;
        threadData[i].arrb_transposed = arrb_transposed;
        threadData[i].start = i * rows_per_thread;
        threadData[i].end = (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiplyMatricesThread, (void *)&threadData[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

// Function to perform matrix multiplication using multiple threads for SIZE_2 elements
void multiplyMatricesParallel2(int arrc[SIZE_2][SIZE_2], int arr[SIZE_2][SIZE_2], int arrb_transposed[SIZE_2][SIZE_2])
{
    pthread_t threads[NUM_THREADS];
    thread_data_t_2 threadData[NUM_THREADS];

    // Divide the workload among threads
    int rows_per_thread = SIZE_2 / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].arrc = arrc;
        threadData[i].arr = arr;
        threadData[i].arrb_transposed = arrb_transposed;
        threadData[i].start = i * rows_per_thread;
        threadData[i].end = (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiplyMatricesThread2, (void *)&threadData[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

// Function to perform matrix multiplication using multiple threads for SIZE_3 elements
void multiplyMatricesParallel3(int arrc[SIZE_3][SIZE_3], int arr[SIZE_3][SIZE_3], int arrb_transposed[SIZE_3][SIZE_3])
{
    pthread_t threads[NUM_THREADS];
    thread_data_t_3 threadData[NUM_THREADS];

    // Divide the workload among threads
    int rows_per_thread = SIZE_3 / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].arrc = arrc;
        threadData[i].arr = arr;
        threadData[i].arrb_transposed = arrb_transposed;
        threadData[i].start = i * rows_per_thread;
        threadData[i].end = (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiplyMatricesThread3, (void *)&threadData[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

int main(void)
{

    int arr[SIZE_1][SIZE_1];
    int arrb[SIZE_1][SIZE_1];
    int arrb_transposed[SIZE_1][SIZE_1];
    // resultant matrix
    int arrc[SIZE_1][SIZE_1];

    int arr2[SIZE_2][SIZE_2];
    int arr2b[SIZE_2][SIZE_2];
    int arr2b_transposed[SIZE_2][SIZE_2];
    // resultant matrix
    int arr2c[SIZE_2][SIZE_2];

    // static to prevent segmentation fault
    static int arr3[SIZE_3][SIZE_3];
    static int arr3b[SIZE_3][SIZE_3];
    static int arr3b_transposed[SIZE_3][SIZE_3];
    // resultant matrix
    static int arr3c[SIZE_3][SIZE_3];

    for (int i = 0; i < SIZE_3; i++)
    {
        for (int j = 0; j < SIZE_3; j++)
        {
            arr3[i][j] = rand() % MOD;
            arr3b[i][j] = rand() % MOD;
        }
    }

    // initializing the array
    for (int i = 0; i < SIZE_1; i++)
    {
        for (int j = 0; j < SIZE_1; j++)
        {
            arr[i][j] = rand() % MOD;
            arrb[i][j] = rand() % MOD;
        }
    }

    for (int i = 0; i < SIZE_2; i++)
    {
        for (int j = 0; j < SIZE_2; j++)
        {
            arr2[i][j] = rand() % MOD;
            arr2b[i][j] = rand() % MOD;
        }
    }

    for (int i = 0; i < SIZE_3; i++)
    {
        for (int j = 0; j < SIZE_3; j++)
        {
            arr3[i][j] = rand() % MOD;
            arr3b[i][j] = rand() % MOD;
        }
    }

    // Transposing Matrix b's
    // This is that the memory locations for the columns are continuous, making it easier to pick up with SIMD Instructions
    for (int i = 0; i < SIZE_1; ++i)
    {
        for (int j = 0; j < SIZE_1; ++j)
        {
            arrb_transposed[j][i] = arrb[i][j];
        }
    }

    for (int i = 0; i < SIZE_2; ++i)
    {
        for (int j = 0; j < SIZE_2; ++j)
        {
            arr2b_transposed[j][i] = arr2b[i][j];
        }
    }

    for (int i = 0; i < SIZE_3; ++i)
    {
        for (int j = 0; j < SIZE_3; ++j)
        {
            arr3b_transposed[j][i] = arr3b[i][j];
        }
    }

    // Multiply for SIZE_1 elements in parallel
    clock_t start = clock();
    multiplyMatricesParallel(arrc, arr, arrb_transposed);
    clock_t end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_1 elements Time taken for execution: %f seconds\n", time_taken);

    // Multiply for SIZE_2 elements in parallel
    start = clock();
    multiplyMatricesParallel2(arr2c, arr2, arr2b_transposed);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_2 elements Time taken for execution: %f seconds\n", time_taken);

    // Multiply for SIZE_3 elements in parallel
    start = clock();
    multiplyMatricesParallel3(arr3c, arr3, arr3b_transposed);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_3 elements Time taken for execution: %f seconds\n", time_taken);

    return 0;
}
