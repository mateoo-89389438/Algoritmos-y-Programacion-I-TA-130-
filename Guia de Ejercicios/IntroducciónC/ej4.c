// Ej_4. Cantidad de segundos

#include <stdio.h>

unsigned long cantidad_segundos (unsigned long h, char m, char s){
    return h*3600 + m*60 + s;
}

int main(){
    printf("Su hora en segundos es: %lu\n",cantidad_segundos(67,34,3));
    return 0;
    
}
    