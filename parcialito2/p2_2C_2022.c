#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 1.a

struct tiempo {
    int dia, mes, agno;
};

// 1.b

typedef uint32_t tiempo_t;
typedef struct tiempo sttiempo_t;

// 1.c

#define MASK_S 0x400000
#define MASK_A 0x1ffe00
#define MASK_M 0x0001e0
#define MASK_D 0x00001f

#define SHIFT_A 9
#define SHIFT_M 5
#define SHIFT_D 0

// VARIANTE 1
void tiempo_a_sttiempo_1(tiempo_t t, sttiempo_t *st) {
    st->dia = (t & MASK_D) >> SHIFT_D;
    st->mes = (t & MASK_M) >> SHIFT_M;
    st->agno = (t & MASK_A) >> SHIFT_A;
    if(t & MASK_S)
        st->agno *= -1;
}

// VARIANTE 2
void tiempo_a_sttiempo_2(tiempo_t t, sttiempo_t *st) {
    st->dia = t & 0x1f;
    st->mes = (t >> SHIFT_M) & 0xf;
    st->agno = (t >> SHIFT_A) & 0xfff;
    if(t & MASK_S)
        st->agno *= -1;
}


// 2.a

int **matriz_crear(size_t filas, size_t columnas) {
    int **m = malloc(filas * sizeof(int *));
    if(m == NULL) return NULL;

    m[0] = malloc(filas * columnas * sizeof(int));
    if(m[0] == NULL) {
        free(m);
        return NULL;
    }

    for(size_t f = 1; f < filas; f++)
        m[f] = *m + f * columnas;
        // m[f] = m[0] + f * columnas;
        // m[f] = &m[0][f * columnas];

    return m;
}

// 2.b

void matriz_destruir(int **m, size_t filas, size_t columnas) {
    free(m[0]);
    free(m);
}

// 3

char *leer_palabra() {
    char *s = malloc(1 * sizeof(char));
    if(s == NULL) return NULL;

    size_t i = 0;

    int c;
    while(isalnum(c = getchar())) {
        s[i++] = c;

        char *aux = realloc(s, (i + 1) * sizeof(char));
        if(aux == NULL) {
            free(s);
            return NULL;
        }
        s = aux;
    }

    s[i] = '\0';
    return s;
}


int main(void) {
    tiempo_t t = 0x400221;  // 1 de enero de -1
    sttiempo_t st;
    tiempo_a_sttiempo_1(t, &st);
    tiempo_a_sttiempo_2(t, &st);
    printf("%d/%d/%d\n", st.dia, st.mes, st.agno);

    int **m = matriz_crear(3, 2);
    for(size_t f = 0; f < 3; f++)
        for(size_t c = 0; c < 2; c++)
            m[f][c] = f + c;
    matriz_destruir(m, 3, 2);

    char *s = leer_palabra();
    puts(s);
    free(s);

    return 0;
}