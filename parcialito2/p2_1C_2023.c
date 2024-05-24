#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

//1
int bcd_a_numero(uint32_t bcd) {
    int suma = 0;
    for(size_t i = 0; i < 8; i++)
                         // (bcd >> (i * 4)) & 0xF;
       suma += pow(10, i) * ((bcd & (0xF << (i * 4))) >> (i * 4));
    return suma;
}

int bcd_a_numero(uint32_t bcd) {
    int suma = 0;
    for(int i = 7; i >= 0; i--) {
        suma *= 10;
        suma += (bcd & (0xF << (i * 4))) >> (i * 4);
    }
    return suma;
}

int main(void) {
    printf("%d\n", bcd_a_numero(0x12345678));
    return 0;
}


// 2.a
struct vector {
    int *v;
    size_t n;
};

// 2.b
typedef struct vector vector_t;

// 2.c
vector_t *vector_clonar(const vector_t *v) {

    vector_t *c = malloc(sizeof(vector_t));

    if(c == NULL) return NULL;

    c->v = malloc(v->n * sizeof(int));
    
    if(c->v == NULL) {
        free(c);
        return NULL;
    }

    c->n = v->n;
    memcpy(c->v, v->v, v->n * sizeof(int));
//    for(size_t i = 0; i < v->n; i++)
//        c->v[i] = v->v[i];

    return c;
}

int main(void) {
    int datos[] = {1, 2, 3, 4, 5};
    vector_t v = {datos, 5};

    vector_t *clon = vector_clonar(&v);

    return 0;
}


// 3

int *leer_notas(size_t *n) {
    char aux[100];

    *n = 0;
    int *v = NULL;

    while(fgets(aux, 100, stdin) != NULL) {
        int nota = atoi(aux);
        if(nota < 0 || nota > 100)
            break;

        int *aux = realloc(v, (*n + 1) * sizeof(int));
        if(aux == NULL) {
            //break;
            free(v);
            return NULL;
        }
        v = aux;

        v[(*n)++] = nota;
    }

    return v;
}


int main(void) {
    size_t n;
    int *notas = leer_notas(&n);
    if(notas == NULL)
        return 1;

    for(size_t i = 0; i < n; i++)
        printf("%d\n", notas[i]);

    free(notas);

    return 0;
}