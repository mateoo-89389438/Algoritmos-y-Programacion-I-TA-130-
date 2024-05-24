#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define N 3

// 1.a

void centrar(char cadena[], size_t largo) {
    size_t l;
    for(l = 0; cadena[l] != '\0'; l++);

    // if(l >= largo) return;

    // Asumimos que (largo - l) es par
    size_t espacios = (largo - l) / 2;

    for(int i = l - 1; i >= 0; i--) {
        cadena[l + espacios] = cadena[l];
    }

    for(size_t i = 0; i < espacios; i++)
        cadena[i] = ' ';
    for(size_t i = espacios + l; i < largo; i++)
        cadena[i] = ' ';
    cadena[largo] = '\0';
}

// 1.b

char cadena[11] = "hola";
centrar(cadena, 10);
puts(cadena);

// 2.a

bool es_simetrica(float m[N][N]) {
    for(size_t i = 0; i < N; i++)
        for(size_t j = i + 1; j < N; j++)
            if(m[i][j] != m[j][i])
                return false;
    return true;
}

// 2.b
/*
float matriz[N][N] = {{1, 2, 3}, {2, 3, 1}, {3, 2, 1}};
//if(es_simetrica(matriz))
//    printf("Es simetrica\n");
printf("La matriz%s es simetrica\n", es_simetrica(matriz) ? "" : " no");
*/
// 3

int main(void) {
    size_t contador = 0;

    int c;
    char anterior = ' ';
    while((c = getchar()) != EOF) {
        if(isalnum(c) && ! isalnum(anterior))
            contador++;
        anterior = c;
    }

    printf("%zd\n", contador);

    return 0;
}





