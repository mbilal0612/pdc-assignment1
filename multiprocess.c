#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MOD 5
#define SIZE 10
#define SIZE_1 10
#define SIZE_2 100
#define SIZE_3 1000
#define num_processes 4 // You can adjust the number of process


void multiply_matrices(int **A, int **B, int **result, int size, int start_row, int end_row)
{
    for (int i = start_row; i < end_row; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            result[i][j] = 0.0f;
            for (int k = 0; k < size; ++k)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
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

    int chunk_size = SIZE_1 / num_processes;



    // Create a pipe for communication
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    clock_t start_time = clock();
    for (int i = 0; i < num_processes; ++i)
    {
        int child_pid = fork();
        if (child_pid == 0)
        {
            // Child process:
            multiply_matrices((int**)&arr, (int**)&arrb_transposed, (int**)arrc, SIZE_1, i * chunk_size, (i + 1) * chunk_size);

            // Send the calculated submatrix to the parent
            write(pipefd[1], arrc, sizeof(arrc));

            close(pipefd[0]); // Close unused read end
            close(pipefd[1]); // Close write end
            return 0;
        }
        else if (child_pid < 0)
        {
            perror("fork");
            return 1;
        }
    }

    close(pipefd[1]); // Close write end in parent

    // Receive the results from child processes
    for (int i = 0; i < num_processes; ++i)
    {
        read(pipefd[0], arrc, sizeof(arrc));
    }

    close(pipefd[0]); // Close read end in parent

    // Wait for all child processes
    for (int i = 0; i < num_processes; ++i)
    {
        wait(NULL);
    }

    clock_t end_time = clock();


    printf("Execution Time for 10x10: %f seconds\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);


    //100x100
    chunk_size = SIZE_2 / num_processes;

    // Create a pipe for communication
    pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    start_time = clock();

    for (int i = 0; i < num_processes; ++i)
    {
        int child_pid = fork();
        if (child_pid == 0)
        {
            // Child process:
            multiply_matrices((int**)&arr2, (int**)&arr2b_transposed, (int**)arr2c, SIZE_2, i * chunk_size, (i + 1) * chunk_size);

            // Send the calculated submatrix to the parent
            write(pipefd[1], arr2c, sizeof(arr2c));

            close(pipefd[0]); // Close unused read end
            close(pipefd[1]); // Close write end
            return 0;
        }
        else if (child_pid < 0)
        {
            perror("fork");
            return 1;
        }
    }

    close(pipefd[1]); // Close write end in parent

    // Receive the results from child processes
    for (int i = 0; i < num_processes; ++i)
    {
        read(pipefd[0], arr2c, sizeof(arr2c));
    }

    close(pipefd[0]); // Close read end in parent

    // Wait for all child processes
    for (int i = 0; i < num_processes; ++i)
    {
        wait(NULL);
    }

    end_time = clock();


    printf("Execution Time for 100x100: %f seconds\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);


    chunk_size = SIZE_3 / num_processes;

    // Create a pipe for communication
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    start_time = clock();

    for (int i = 0; i < num_processes; ++i)
    {
        int child_pid = fork();
        if (child_pid == 0)
        {
            // Child process:
            multiply_matrices((int**)&arr3, (int**)&arr3b_transposed, (int**)arr3c, SIZE_3, i * chunk_size, (i + 1) * chunk_size);

            // Send the calculated submatrix to the parent
            write(pipefd[1], arr3c, sizeof(arr3c));

            close(pipefd[0]); // Close unused read end
            close(pipefd[1]); // Close write end
            return 0;
        }
        else if (child_pid < 0)
        {
            perror("fork");
            return 1;
        }
    }

    close(pipefd[1]); // Close write end in parent

    // Receive the results from child processes
    for (int i = 0; i < num_processes; ++i)
    {
        read(pipefd[0], arr3c, sizeof(arr3c));
    }

    close(pipefd[0]); // Close read end in parent

    // Wait for all child processes
    for (int i = 0; i < num_processes; ++i)
    {
        wait(NULL);
    }

    end_time = clock();


    printf("Execution Time for 1000x1000: %f seconds\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);

    return 0;
}
