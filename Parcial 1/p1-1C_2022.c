#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define N 3
#define MAX_STR 100

void left_trim(char cadena[]) {
    size_t i;
    for(i = 0; cadena[i] == ' '; i++);

/*    size_t j;
    for(j = 0; cadena[j + i] != '\0'; j++)
        cadena[j] = cadena[j + i];
    cadena[j] = '\0';*/

//    for(size_t j = 0; (cadena[j] = cadena[j + i]); j++);

    for(size_t j = 0; (cadena[j] = cadena[i]); i++, j++);
}

// C89
bool es_triangular_superior_89(float matriz[][N]) {
    for(size_t f = 0; f < N; f++)
        for(size_t c = 1; c < N; c++)
            if(f > c && matriz[f][c] != 0)
                return false;
    return true;
}

// C99
bool es_triangular_superior_99(size_t n, float matriz[][n]) {
    for(size_t f = 1; f < n; f++)
        for(size_t c = 0; c < f; c++)
            if(matriz[f][c] != 0)
                return false;
    return true;
}


int main(void) {
    char cadena[] = "   hola mundo   ";
    left_trim(cadena);
    printf("#%s#\n", cadena);

    float matriz[N][N] = {{1, 2, 3}, {0, 1, 2}, {0, 0, 5}};
/*    if(es_triangular_superior(matriz))
        puts("Es triangular");*/
    printf("La matriz %ses triangular superior\n", es_triangular_superior_99(N, matriz) ? "" : "no "); 


    // Ejercicio 3:
    char aux[MAX_STR];
    printf("Ingrese un nÃºmero: ");
    fgets(aux, MAX_STR, stdin);

    float n = atof(aux);

    if(n < 0) {
        printf("NÃºmero no vÃ¡lido\n");
        return 1;
    }

    printf("%f\n", sqrt(n));

    return 0;
}