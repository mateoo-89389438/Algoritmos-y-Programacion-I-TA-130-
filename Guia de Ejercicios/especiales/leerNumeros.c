#include <stdio.h>
#include <stdlib.h>

void imprimir_vector(const int v[], size_t n) {
    for(size_t i = 0; i < n; i++)
        printf("%d\n", v[i]);
}

float promediar(const int v[], size_t n) {
    int suma = 0;
    for(size_t i = 0; i < n; i++)
        suma += v[i];

    return (float)suma / n;
}

int main(void) {
    int v[10];
    size_t n = sizeof(v) / sizeof(v[0]);

    for(size_t i = 0; i < n; i++) {
        printf("Ingrese un nÃºmero: ");
        char aux[100];
        fgets(aux, 100, stdin);
        v[i] = atoi(aux);
    }

    imprimir_vector(v, n);

    printf("%f\n", promediar(v, n));

    return 0;
}
