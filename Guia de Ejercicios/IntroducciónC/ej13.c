// Ej_13. Escribir un programa que imprima la tabla de multiplicar del número 7.
#include <stdio.h>

int main() {
    short i;
    for (i=0; i<=10; i++) {
        printf("7 x %d = %d \n", i, 7*i); 
    }
    return 0;
}