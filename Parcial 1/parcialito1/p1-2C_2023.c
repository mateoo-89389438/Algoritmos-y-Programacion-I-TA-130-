#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool es_vocal(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

/*
bool es_vocal(char c) {
    char vocales[] = {'a', 'e', 'i', 'o', 'u'};
    for(size_t i = 0; i < 5; i++)
        if(c == vocales[i])
            return true;
    return false;
}*/

void abreviar_texto(char texto[]) {
    size_t i = 0;
    size_t j = 0;

    while(texto[j] != '\0') {
   //     if(texto[j] == 'a' || texto[j] == 'e' || texto[j] == 'i')
          if(es_vocal(texto[j]))
            j++;
        else
            texto[i++] = texto[j++];
    }
    texto[i] = '\0';
}
/*
void abreviar_texto(char texto[]) {
    for(size_t i = 0; texto[i] != '\0'; i++) {
        if(es_vocal(texto[i])) {
            for(size_t j = i; texto[j] != '\0'; j++)
                texto[j] = texto[j + 1];
            i--;
        }
    }
}*/


bool es_suma(size_t n, size_t m, float matriz[n][m]) {
    for(size_t f = 1; f < n; f++)
        for(size_t c = 1; c < m; c++)
            if(matriz[f][c] != matriz[f - 1][c] + matriz[f][c - 1])
                return false;
    return true;
}

#define M 3

int main(void) {
    char texto[] = "algoritmos y programacion";
    abreviar_texto(texto);
    puts(texto);

    float m[M][M] = {
        {1, 2, 3},
        {4, 6, 9},
        {5, 11, 20}
    };

    if(es_suma(M, M, m))
        printf("Cumple la propiedad de suma\n");

/*    printf("La matriz %scumple la propiedad\n",
        es_suma(M, M, m) ? "" : "no");*/

    char aux[100];
    printf("Ingrese los minutos: ");
    fgets(aux, 100, stdin);
    int minutos = atoi(aux);

    printf("Ingrese el tiempo: ");
    fgets(aux, 100, stdin);
    int tiempo = atoi(aux);

    if(minutos < 0 || minutos > 45 || tiempo <= 0 || tiempo > 2) {
        fprintf(stderr, "Minutos o tiempo incorrectos\n");
        return 1;
    }

    int tiempo_total = minutos;
    if(tiempo == 2)
        tiempo_total += 45;

    printf("El tiempo total es: %d\n", tiempo_total);

    return 0;
}