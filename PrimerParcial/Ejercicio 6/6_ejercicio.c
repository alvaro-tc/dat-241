// En MPI realizar el cálculo de PI
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int num_procesadores, n_proceso;
    int num_iteraciones=65;
    double pi_local = 0.0;
    double pi = 0.0;
    int signo;
    int divisor;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesadores);  
    MPI_Comm_rank(MPI_COMM_WORLD, &n_proceso);  


    MPI_Bcast(&num_iteraciones, 1, MPI_INT, 0, MPI_COMM_WORLD);  
    int iteraciones_por_proceso = num_iteraciones / num_procesadores; 
    int inicio = n_proceso * iteraciones_por_proceso; 
    int fin = inicio + iteraciones_por_proceso;

    if (n_proceso == num_procesadores - 1) {
        fin = num_iteraciones;  // Ajusta el índice de fin si el número de iteraciones no es divisible exactamente por el número de procesos
    }

    for (int i = inicio; i < fin; i++) {
        signo = (i % 2 == 0) ? 1 : -1;  
        divisor = 2 * i + 1;  
        pi_local += (double) signo / divisor;  
    }

    MPI_Reduce(&pi_local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  

    if (n_proceso == 0) {
        pi *= 4 ;  
        printf("El valor aproximado de pi es: %f\n", pi);  
    }

    MPI_Finalize();  

    return 0;
}