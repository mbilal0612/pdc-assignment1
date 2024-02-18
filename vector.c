#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <immintrin.h>

#define MOD 5
#define SIZE_1 10
#define SIZE_2 100
#define SIZE_3 1000

void multiplyMatrices1(int arrc[SIZE_1][SIZE_1], int arr[SIZE_1][SIZE_1], int arrb_transposed[SIZE_1][SIZE_1]) {
    __m256i sum;
    for (int i = 0; i < SIZE_1; i++) {
        for (int j = 0; j < SIZE_1; j++) {
            sum = _mm256_setzero_si256();  // Initialize the sum to zero
            for (int k = 0; k < SIZE_1; k += 8) {
                __m256i row = _mm256_loadu_si256((__m256i *)&arr[i][k]);
                __m256i col = _mm256_loadu_si256((__m256i *)&arrb_transposed[j][k]);
                __m256i vec = _mm256_mullo_epi32(row, col);
                sum = _mm256_add_epi32(sum, vec);
            }
            int result[8];
            _mm256_storeu_si256((__m256i *)result, sum);
            long total = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];
            arrc[i][j] = total;
        }
    }
}


void multiplyMatrices2(int arrc[SIZE_2][SIZE_2], int arr[SIZE_2][SIZE_2], int arrb_transposed[SIZE_2][SIZE_2]) {
    __m256i sum;
    for (int i = 0; i < SIZE_2; i++) {
        for (int j = 0; j < SIZE_2; j++) {
            sum = _mm256_setzero_si256();  // Initialize the sum to zero
            for (int k = 0; k < SIZE_2; k += 8) {
                __m256i row = _mm256_loadu_si256((__m256i *)&arr[i][k]);
                __m256i col = _mm256_loadu_si256((__m256i *)&arrb_transposed[j][k]);
                __m256i vec = _mm256_mullo_epi32(row, col);
                sum = _mm256_add_epi32(sum, vec);
            }
            int result[8];
            _mm256_storeu_si256((__m256i *)result, sum);
            long total = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];
            arrc[i][j] = total;
        }
    }
}


void multiplyMatrices3(int arrc[SIZE_3][SIZE_3], int arr[SIZE_3][SIZE_3], int arrb_transposed[SIZE_3][SIZE_3]) {
    __m256i sum;
    for (int i = 0; i < SIZE_3; i++) {
        for (int j = 0; j < SIZE_3; j++) {
            sum = _mm256_setzero_si256();  // Initialize the sum to zero
            for (int k = 0; k < SIZE_3; k += 8) {
                __m256i row = _mm256_loadu_si256((__m256i *)&arr[i][k]);
                __m256i col = _mm256_loadu_si256((__m256i *)&arrb_transposed[j][k]);
                __m256i vec = _mm256_mullo_epi32(row, col);
                sum = _mm256_add_epi32(sum, vec);
            }
            int result[8];
            _mm256_storeu_si256((__m256i *)result, sum);
            long total = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];
            arrc[i][j] = total;
        }
    }
}

int main(void) {
    int arr[SIZE_1][SIZE_1];
    int arrb[SIZE_1][SIZE_1];
    int arrb_transposed[SIZE_1][SIZE_1];
    int arrc[SIZE_1][SIZE_1];

    int arr2[SIZE_2][SIZE_2];
    int arr2b[SIZE_2][SIZE_2];
    int arr2b_transposed[SIZE_2][SIZE_2];
    int arr2c[SIZE_2][SIZE_2];

    static int arr3[SIZE_3][SIZE_3];
    static int arr3b[SIZE_3][SIZE_3];
    static int arr3b_transposed[SIZE_3][SIZE_3];
    static int arr3c[SIZE_3][SIZE_3];

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
    // This is that the memory locations for the columns are continous, making it easier to pickup with SIMD Instructions
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
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


    // Multiply for SIZE_1 elements
    clock_t start = clock();
    multiplyMatrices1(arrc, arr, arrb_transposed);
    clock_t end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_1 elements Time taken for execution : %f \n", time_taken);

    // Multiply for SIZE_2 elements
    start = clock();
    multiplyMatrices2(arr2c, arr2, arr2b_transposed);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_2 elements Time taken for execution : %f \n", time_taken);

    // Multiply for SIZE_3 elements
    start = clock();
    multiplyMatrices3(arr3c, arr3, arr3b_transposed);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("SIZE_3 elements Time taken for execution : %f \n", time_taken);

    return 0;
}
