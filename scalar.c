#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MOD 5
#define SIZE 10
#define SIZE_2 100
#define SIZE_3 1000


int main(void)
{
    int arr[SIZE][SIZE];
    int arrb[SIZE][SIZE];
    int arrc[SIZE][SIZE];

    int arr2[SIZE_2][SIZE_2];
    int arr2b[SIZE_2][SIZE_2];
    int arr2c[SIZE_2][SIZE_2];

    //static to prevent segmentation fault
    static int arr3[SIZE_3][SIZE_3];
    static int arr3b[SIZE_3][SIZE_3];
    static int arr3c[SIZE_3][SIZE_3];



    // initializing the array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
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
   

    // initializing the time
    clock_t start, end;
    // initializing total
    start = clock();
    
    
    
    //multiply both mmatrices
    //row
    for (int i = 0; i < SIZE; i++)
    {
        // column
        for (int j = 0; j < SIZE; j++)
        {

            // multiply
            int total = 0;
            for (int k = 0; k < SIZE; k++)
            {
                total += (arr[i][k] * arrb[k][j]);
            }
            arrc[i][j] = total;
        }
    }

    end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    // print the time
    printf("SIZE elements Time taken for execution : %f \n", time_taken);

    // for SIZE_2 elements

    start = clock();
    

    //multiply both matrices
    //row
    for (int i = 0; i < SIZE_2; i++)
    {
        // column
        for (int j = 0; j < SIZE_2; j++)
        {

            // multiply
            int total = 0;
            for (int k = 0; k < SIZE_2; k++)
            {
                total += (arr2[i][k] * arr2b[k][j]);
            }
            arr2c[i][j] = total;
        }
    }

    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    // print the time
    printf("SIZE_2 elements  Time taken for execution : %f \n", time_taken);

    // for SIZE_3 elements

    
    start = clock();
    // initializing total
    
    // multiply both matrices
    // row

    for (int i = 0; i < SIZE_3; i++)
    {
        // column
        for (int j = 0; j < SIZE_3; j++)
        {

            // multiply
            int total = 0;
            for (int k = 0; k < SIZE_3; k++)
            {
                total += (arr3[i][k] * arr3b[k][j]);
            }
            arr3c[i][j] = total;
        }
    }

    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    // print the time
    printf("SIZE_3 elements Time taken for execution : %f \n", time_taken);

    
}