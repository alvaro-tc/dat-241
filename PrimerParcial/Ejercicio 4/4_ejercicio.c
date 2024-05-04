// Realizar en OPEnMP la multiplicación de una matriz nxn, con un vector de dimensión n.
#include <stdio.h>
#include <omp.h>

int main() {
    int n=2;
    int matrix[n][n];
    int vector[n];
    int result[n];
    matrix[0][0]=1;
    matrix[0][1]=2;
    matrix[1][0]=3;
    matrix[1][1]=4;
    vector[0]=2;
    vector[1]=1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        int sumColumnas = 0;
        for (int j = 0; j < n; ++j) {
            sumColumnas += matrix[j][i] * vector[j];
        }
        result[i] = sumColumnas;
    }
    

    printf("Resultado de la multiplicación de matriz por vector:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}