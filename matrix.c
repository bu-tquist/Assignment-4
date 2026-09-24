#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_random_matrix(int rows, int cols, int *matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i * cols + j] = rand() % 100;
        }
    }
}

void multiply_matrices(int rows1, int cols1, int *matrix1,
                       int rows2, int cols2, int *matrix2,
                       int *result)
{

    memset(result, 0, rows1 * cols2 * sizeof(int));

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            for (int k = 0; k < cols1; k++)
            {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

void display_matrix(int rows, int cols, int *matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

float do_job(int rows1, int cols1, int cols2, int forever)
{
    struct timespec t0, t1;

    int rows2 = cols1;

    int *matrix1 = (int *)malloc(rows1 * cols1 * sizeof(int));
    int *matrix2 = (int *)malloc(rows2 * cols2 * sizeof(int));
    int *result = (int *)malloc(rows1 * cols2 * sizeof(int));

    timespec_get(&t0, TIME_UTC);

    if (forever == 0)
    {
        generate_random_matrix(rows1, cols1, matrix1);
        generate_random_matrix(rows2, cols2, matrix2);
        multiply_matrices(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
    }
    else
    {
        while (1)
        {
            generate_random_matrix(rows1, cols1, matrix1);
            generate_random_matrix(rows2, cols2, matrix2);
            multiply_matrices(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
        }
    }

    timespec_get(&t1, TIME_UTC);

    // nano seconds elapsed converted to fractional seconds
    float dns = (float)(t1.tv_nsec - t0.tv_nsec) / 1000000000;
    // seconds elapsed
    float ds = (float)(t1.tv_sec - t0.tv_sec);

    float total_time = dns + ds;

    free(matrix1);
    free(matrix2);
    free(result);

    return total_time;
}
