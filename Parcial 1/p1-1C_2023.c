#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// Ejercicio 1

void abreviar_nombre(char nombre[]) {
    size_t i;
    for(i = 0; nombre[i] != '\0'; i++);

    // if(i < 3 || i > 11) return;

    nombre[1] = i - 2 + '0';
    nombre[2] = nombre[i - 1];
    nombre[3] = '\0';
}

/*
    char s[] = "kubernetes";
    abreviar_nombre(s);
    //puts(s);
*/

// 2

bool es_simetrica(size_t n, float m[n][n]) {
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
            if(m[i][j] != m[j][i])
                return false;
    return true;
}
/*
    float m[N][N] = {{1, 2, 3},
                     {2, 4, 5},
                     {3, 5, 6}};

    printf("La matriz %ses simÃ©trica\n", es_simetrica(N, m) ? "": "no ");
*/

#define PI		3.14159265358979323846
#define MAX_STR 100

int main(void) {
    char aux[MAX_STR];

    printf("Ingrese la masa: ");
    fgets(aux, MAX_STR, stdin);

    float m = atof(aux);

    printf("Ingrese la constante del resorte: ");
    fgets(aux, MAX_STR, stdin);

    float k = atof(aux);

    if(m <= 0 || k <= 0) {
        fprintf(stderr, "Los datos son invÃ¡lidos\n");
        return 1;
    }

    float t = 2 * PI * sqrt(m / k);

    printf("T = %f\n", t);

    return 0;
}