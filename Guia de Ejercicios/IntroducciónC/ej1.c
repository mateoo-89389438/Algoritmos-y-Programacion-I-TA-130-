#include <math.h> 
#include <stdio.h>

unsigned long monto_final(unsigned long c, int x, char n){
    return c * pow(1+ x/100.0, n)+ 0.5;
    // el return devuelve double, pero se trunca por el unsigned long de la funcion original

}

int main(){
    printf("Su monto a pagar es: %lu :)\n", monto_final(100,118,1) );
    // el printf no es necesario, pero te muestra el valor del monto final que vos pongas
    return 0;

}

