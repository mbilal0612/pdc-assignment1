#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(void)
{
    printf("getting here6\n");
    int arr[10][10];
    int arrb[10][10];
    int arrc[10][10];

    int arr2[100][100];
    int arr2b[100][100];
    int arr2c[100][100];

    //static to prevent segmentation fault
    static int arr3[1000][1000];
    static int arr3b[1000][1000];
    static int arr3c[1000][1000];

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            arr3[i][j] = rand() % 100;
            arr3b[i][j] = rand() % 100;
        }
    }

    // initializing the array
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arr[i][j] = rand() % 100;
            arrb[i][j] = rand() % 100;
        }
    }
    

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            arr2[i][j] = rand() % 100;
            arr2b[i][j] = rand() % 100;
        }
    }
    
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            arr3[i][j] = rand() % 100;
            arr3b[i][j] = rand() % 100;
        }
    }
   

    // initializing the time
    clock_t start, end;
    // initializing total
    start = clock();
    
    
    
    //multiply both mmatrices
    //row
    for (int i = 0; i < 10; i++)
    {
        // column
        for (int j = 0; j < 10; j++)
        {

            // multiply
            int total = 0;
            for (int k = 0; k < 10; k++)
            {
                total += (arr[i][k] * arrb[k][j]);
            }
            arrc[i][j] = total;
        }
    }

    end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    // print the time
    printf("10 elements Time taken for execution : %f \n", time_taken);

    // for 100 elements

    start = clock();
    

    //multiply both matrices
    //row
    for (int i = 0; i < 100; i++)
    {
        // column
        for (int j = 0; j < 100; j++)
        {

            // multiply
            int total = 0;
            for (int k = 0; k < 100; k++)
            {
                total += (arr2[i][k] * arr2b[k][j]);
            }
            arr2c[i][j] = total;
        }
    }

    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    // print the time
    printf("100 elements  Time taken for execution : %f \n", time_taken);

    // for 1000 elements

    
    start = clock();
    // initializing total
    
    // multiply both matrices
    // row

    for (int i = 0; i < 1000; i++)
    {
        // column
        for (int j = 0; j < 1000; j++)
        {

            // multiply
            int total = 0;
            for (int k = 0; k < 1000; k++)
            {
                total += (arr3[i][k] * arr3b[k][j]);
            }
            arr3c[i][j] = total;
        }
    }

    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    // print the time
    printf("1000 elements Time taken for execution : %f \n", time_taken);

    
}