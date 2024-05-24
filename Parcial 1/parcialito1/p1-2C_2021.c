#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define N 3
#define M 2

#define MAX_STRING 256

bool tiene_extension(const char archivo[], const char extension[]) {
    size_t la, le;
    for(la = 0; archivo[la] != '\0'; la++);
    for(le = 0; extension[le] != '\0'; le++);

    if(le > la) return false;

    for(size_t i = 0; extension[i] != '\0'; i++)
        if(archivo[i + la - le] != extension[i])
            return false;

    return true;
}








bool es_nonegativa(size_t n, size_t m, float matriz[n][m]) {
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < m; j++)
            if(matriz[i][j] < 0)
                return false;
    return true;
}


int leer_numero(const char mensaje[]) {
    char aux[MAX_STRING];
    printf("%s", mensaje);
    fgets(aux, MAX_STRING, stdin);
    return atoi(aux);
}


int main(void) {
    float matriz[N][M] = {
        {0, 2},
        {1.1, -3},
        {2, 3.14},
    };

    if(es_nonegativa(N, M, matriz))
        printf("No negativa\n");
    else
        printf("Negativa\n");

    assert(tiene_extension("archivo.txt", ".txt"));
    assert(! tiene_extension("paquete.zip", ".rar"));
    assert(tiene_extension("paquete.tar.gz", ".tar.gz"));
    assert(tiene_extension("paquete.tar.gz", ".gz"));
    assert(! tiene_extension("archivo.con.punto.en.el.medio.html", ".con"));
    assert(! tiene_extension("e1.c", ".html"));



    int grados, minutos, segundos;

/*
    char aux[MAX_STRING];

    printf("Ingrese los grados: ");
    fgets(aux, MAX_STRING, stdin);
    grados = atoi(aux);

    printf("Ingrese los minutos: ");
    fgets(aux, MAX_STRING, stdin);
    minutos = atoi(aux);

    printf("Ingrese los segundos: ");
    fgets(aux, MAX_STRING, stdin);
    segundos = atoi(aux);*/

    grados = leer_numero("Ingrese los grados: ");
    minutos = leer_numero("Ingrese los minutos: ");
    segundos = leer_numero("Ingrese los segundos: ");

    if(grados < 0 || grados >= 360 || minutos < 0 || minutos >= 60 || segundos < 0 || segundos >= 60) {
        printf("Error, valores invalidos\n");
        return 1;
    }

    double grados_totales = (segundos / 60.0 + minutos) / 60 + grados;

    printf("%dÂº%d'%d\" = %f\n", grados, minutos, segundos, grados_totales);

    return 0;
}