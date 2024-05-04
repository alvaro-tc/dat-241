// En C implemente las funciones básicas (+.-.*./); utilice punteros (Ej. Multiplicación en base a sumas, división en base a restas).
#include <stdio.h>
// Los punteros se usan para funciones donde se
// requiera modificar el valor de la variable 
// para trabajar con punteros se emplea el signo (*)
// Para poner el puntero de un dato se usa (&)

void suma(int* x, int* y, int* resultado){
    *resultado = *x+*y;
}
void resta(int* x, int* y, int* resultado){
    *resultado = *x-*y;
}
void multiplicacion(int* x, int* y, int* resultado){
    int x1 = *x;
    int y1 = *y;
    *resultado=0;
    if (y1 == 0) {
        *resultado =0;
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
    *resultado=0;
    if (y1 == 0) {
        printf("Error: no se puede dividir por cero\n");
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
 
    //Division
    while (x1 >= y1) {
        x1 -= y1;
        *resultado+=1;
    }
    *resultado = (*resultado) * signo;
}
int main(){
    int x = 20;
    int y = -2;
    int resultado = 0;

    suma(&x,&y,&resultado);
    printf("La suma es:  %d\n",resultado);
    resta(&x,&y,&resultado);
    printf("La resta es:  %d\n",resultado);
    multiplicacion(&x,&y,&resultado);
    printf("La multiplicacion es:  %d\n",resultado);
    division(&x,&y,&resultado);
    printf("La division es:  %d\n",resultado);

}
