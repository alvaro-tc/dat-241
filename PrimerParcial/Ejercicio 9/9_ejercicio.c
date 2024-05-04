// Genere la serie 2, 4, 6, 8, 10, 12, 14, 16, 18… en M vectores(procesadores) para N términos con MPI 
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 16 // Número de elementos del vector

int main(int argc, char *argv[]) {
    int rank, size;
    int local_n;
    int local_vec[N];
    int global_vec[N];

    MPI_Init(&argc, &argv);
    // N Proceso
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //N procesadores
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size != 0) {
        if (rank == 0) {
            printf("El número de elementos debe ser divisible por el número de procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    local_n = N / size;

    // Generar vector local
    for (int i = 0; i < local_n; i++) {
        local_vec[i] = (rank * local_n + i + 1) * 2;
    }

    // Mostrar qué proceso genera qué vector
    printf("Proceso %d genera el vector: ", rank);
    for (int i = 0; i < local_n; i++) {
        printf("%d ", local_vec[i]);
    }
    printf("\n");

    // Reunir todos los vectores en el proceso raíz
    MPI_Gather(local_vec, local_n, MPI_INT, global_vec, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Mostrar vector final en el proceso raíz
    if (rank == 0) {
        printf("Vector final: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", global_vec[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
