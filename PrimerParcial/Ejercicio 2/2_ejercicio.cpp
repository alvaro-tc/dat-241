// Lleve el anterior código en c++.
#include <iostream>
using namespace std;

void suma(int* x, int* y, int* resultado){
    *resultado = *x + *y;
}

void resta(int* x, int* y, int* resultado){
    *resultado = *x - *y;
}

void multiplicacion(int* x, int* y, int* resultado){
    int x1 = *x;
    int y1 = *y;
    *resultado = 0;
    if (y1 == 0) {
        *resultado = 0;
    }
    int signo = 1;
    if (x1 < 0) {
        x1 = -x1;
        signo = -signo;
    }
    
    if (y1 < 0) {
        y1 = -y1;
        signo = -signo;
    }
 

    for (int i = 0; i < y1; i++) {
        *resultado += x1;
    }
    *resultado = (*resultado) * signo;
}

void division(int* x, int* y, int* resultado) {
    int x1 = *x;
    int y1 = *y;
    *resultado = 0;
    if (y1 == 0) {
        cout << "Error: no se puede dividir por cero\n";
        return;
    }
    int signo = 1;
    if (x1 < 0) {
        x1 = -x1;
        signo = -signo;
    }
    
    if (y1 < 0) {
        y1 = -y1;
        signo = -signo;
    }
 
    // División
    while (x1 >= y1) {
        x1 -= y1;
        (*resultado)++;
    }
    *resultado = (*resultado) * signo;
}

int main() {
    int x = 20;
    int y = -2;
    int resultado = 0;

    suma(&x, &y, &resultado);
    cout << "La suma es: " << resultado << endl;
    resta(&x, &y, &resultado);
    cout << "La resta es: " << resultado << endl;
    multiplicacion(&x, &y, &resultado);
    cout << "La multiplicacion es: " << resultado << endl;
    division(&x, &y, &resultado);
    cout << "La division es: " << resultado << endl;

    return 0;
}