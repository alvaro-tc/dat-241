// Genere la serie 2, 4, 6, 8, 10, 12, 14, 16, 18… en M vectores(procesadores) para N términos con OPENMP
#include <stdio.h>
#include <omp.h>

int main() {
    // Definimos la cantidad de procesadores 
    int num_procs = omp_get_num_procs();
    printf("Numero de procesadores disponibles: %d\n", num_procs);

    // Definir el número de términos 
    int N = 10;
    int M = num_procs; 

    // Calcular cuántos términos le corresponde a cada vector
    int terminos_por_vector = N / M;
    // Calcular los terminos adicionales
    int terminos_extras = N % M;

    // Vector de la serie
    int series[N];


    #pragma omp parallel num_threads(M)
    {
        // Obtener el numero del procesador
        int procesador_n = omp_get_thread_num();

        // Calcular el rango de términos para este vector
        int inicio = procesador_n * terminos_por_vector + 1;
        int fin = (procesador_n + 1) * terminos_por_vector;

        // Si es el último vector, calcular los ultimos terminos
        if (procesador_n == omp_get_num_procs() - 1) {
            fin += terminos_extras;
        }

        int indice_inicio = procesador_n * terminos_por_vector;
        printf("Procesador %d generando la serie: ", procesador_n);
        for (int i = inicio; i <= fin; i++) {
      
            printf("%d ", 2 * i);
            series[indice_inicio + (i - inicio)] = 2 * i;
        }
        printf("\n");
    }

 
    printf("Serie generada: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", series[i]);
    }
    printf("\n");

    return 0;
}
