// Realice el cálculo de Fibonacci con MPI  mediante un procesador MASTER que solicite cada termino a los procesadores SLAVE
#include <stdio.h>
#include <mpi.h>
#include <math.h>

// Función para calcular el término de Fibonacci utilizando la fórmula explícita
int fibonacci(int n) {
    double phi = (1 + sqrt(5)) / 2;
    return (int) round(pow(phi, n) / sqrt(5));
}

int main(int argc, char** argv) {
    int rank, size;
    int n = 10;  // Número de términos de Fibonacci a calcular

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("El número de procesadores debe ser al menos 2.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        int i;
        int terminos_por_procesador = n / (size - 1);
        int terminos_adicionales = n % (size - 1);
        int contador_terminos = 1;

        for (i = 1; i < size; i++) {
            int numero_terminos = terminos_por_procesador + (i <= terminos_adicionales ? 1 : 0);
            MPI_Send(&numero_terminos, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&contador_terminos, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            contador_terminos += numero_terminos;
        }

        for (i = 1; i < size; i++) {
            int j;
            for (j = 0; j < terminos_por_procesador + (i <= terminos_adicionales ? 1 : 0); j++) {
                int result;
                MPI_Recv(&result, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("%d  ", result);
            }
        }
    } else {
        int numero_terminos, start_term;
        MPI_Recv(&numero_terminos, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&start_term, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int i;
        for (i = 0; i < numero_terminos; i++) {
            int term = start_term + i;
            int result = fibonacci(term);
            MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}