// En openMP realice la multiplicación y división en base a sumas y restas.
#include <stdio.h>
#include <omp.h>

int main() {
    int x = 2;
    int y = 1000;
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < y; ++i) {
        sum += x;
    }

    printf("Multiplicacion: %d\n", sum);

    return 0;
}
