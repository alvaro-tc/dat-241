// En openMP realice la multiplicación y división en base a sumas y restas.
#include <stdio.h>
#include <omp.h>

int main() {
    int x = 1000;
    int y = 2;
    int div = 0;

    int signo = 1;
    if (x < 0) {
        x = -x;
        signo = -signo;
    }
    if (y < 0) {
        y = -y;
        signo = -signo;
    }

    #pragma omp parallel for reduction(+:div)
    for (int i = x; i >= y; i -= y) {
        div += 1;
    }

    printf("Division: %d\n", div);

    return 0;
}
