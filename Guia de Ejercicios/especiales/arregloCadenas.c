#include <stdio.h>

#define MAX_CADENA 100

void imprimir_arreglo_cadenas(char ac[][MAX_CADENA], size_t n) {
    for(size_t i = 0; i < n; i++) {
        //printf("%s\n", ac[i]);
        for(size_t j = 0; ac[i][j] != '\0'; j++)
            putchar(ac[i][j]);
        putchar('\n');
    }
}

int main(void) {
    int m[3][2] = {
        {1, 2}, 
        {3, 4}, 
        {5, 6}
    };

    for(size_t f = 0; f < 3; f++) {
        for(size_t c = 0; c < 2; c++)
            printf("%d\t", m[f][c]);
        putchar('\n');
    }

    char arreglo_cadenas[][MAX_CADENA] = {
        "Hola", 
        "que", 
        "tal"
    };
    
    imprimir_arreglo_cadenas(arreglo_cadenas, 3);

    return 0;
}