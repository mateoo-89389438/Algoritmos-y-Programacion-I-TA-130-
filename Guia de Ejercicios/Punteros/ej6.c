// Ej_6. Implementar una función swap que reciba 2 datos a y b por puntero y los intercambie, de forma tal que b sea a y viceversa.

#include <stdio.h>

void swap(int *x, int*y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int main() {
    int a=4;
    int b=5;
    printf("a= %d , b=%d\n",a,b);
    swap(&a,&b);
    printf("a=%d , b=%d\n",a,b);
    return 0;
}