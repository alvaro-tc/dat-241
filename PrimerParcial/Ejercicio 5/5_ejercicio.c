// Realizar en MPI la multiplicación de una matriz NxN, con un vector de dimensión N.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Tamaño de la matriz y el vector


void mostrar_matriz(int A[][N], int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int rank, size;
    int A[N][N], x[N], y[N], local_y[N];
    int i, j;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Solo el proceso 0 inicializa la matriz y el vector
    if (rank == 0)
    {
        // Inicializar la matriz A
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                A[i][j] = rand() % 10; // Valores aleatorios entre 0 y 9
            }
        }

        // Inicializar el vector x
        for (i = 0; i < N; i++)
        {
            x[i] = rand() % 10; // Valores aleatorios entre 0 y 9
        }

        printf("Matriz A:\n");
        mostrar_matriz(A, N);

        printf("\nVector x:\n");
        for (i = 0; i < N; i++)
        {
            printf("%d\n", x[i]);
        }
    }

    // Se distribuye la matriz y el vector a todos los procesos
    MPI_Bcast(A, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada proceso calcula una parte de la multiplicación
    for (i = 0; i < N; i++)
    {
        local_y[i] = 0;
        for (j = 0; j < N; j++)
        {
            local_y[i] += A[i][j] * x[j];
        }
    }

    // Se reúnen los resultados parciales de todos los procesos en el proceso 0
    MPI_Reduce(local_y, y, N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso 0 imprime el resultado final
    if (rank == 0)
    {
        printf("\nResultado de la multiplicacion:\n");
        for (i = 0; i < N; i++)
        {
            printf("%d\n", y[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
