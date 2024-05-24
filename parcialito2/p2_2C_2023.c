#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// EJ1

bool misma_cantidad(uint32_t n) {
    //calculo los pares
    int pares = 0;

    for(size_t i = 0; i < 32; i+=2){
        if((1 << i) & n)
            pares++;
    }

    //calculo los impares
    int impares = 0;

    for(size_t i = 1; i < 32; i+=2){
        if((1 << i) & n)
            impares++;
    }

    //comparo
    return if pares == impares;
}

// EJ2

char *join(char *cadenas[], size_t n, char separador) {

    size_t longitud = 0;

    for(size_t i = 0; i < n; i++){
        longitud += strlen(cadenas[i]);
    }

    char *s = malloc( (longitud + n) * sizeof(char) );

    if(s == NULL){
        return NULL;
    }

    s[0] = '\0';

    for(size_t i = 0; i < n; i++) {

        strcat(s, cadenas[i]);

        if(i != n) {
            size_t ultimo = strlen(s);
            s[ultimo] = separador;
            s[ultimo + 1] = '\0';
        }
    }

    return s;
}

// EJ3

// a)
enum palos {ORO, COPA, ESPADA, BASTO};

struct carta {
    int valor;
    enum palos palo;
};

// b)
typedef struct carta carta_t;

// c)
carta_t *sacar_carta_del_mazo();

carta_t **tirar_reyes(size_t *n) {

    carta_t **v = NULL;

    *n = 0;

    carta_t *c;

    do {
        c = sacar_carta_del_mazo();
        if(c == NULL) return v; // Podria ahorrarme este chequeo.

        carta_t **aux = realloc(v, (*n + 1) * sizeof(carta_t*));
        if(aux == NULL)
            // No se si sacar_carta_del_mazo() devuelve cartas con dimÃ¡nica o no,
            // entonces en vez de ponerme a liberar devuelvo lo que tengo.
            return v;
        v = aux;

        v[(*n)++] = c;
    } while(c->valor != 12);

    return v;
}


// Pruebas

int main(void) {
    // EJ1
    printf("0x4B %stiene la misma cantidad\n", misma_cantidad(0x4B) ? "" : "no ");

    // EJ2
    char *texto[] = {"Hola", "que", "tal"};
    char *s = join(texto, 3, ' ');
    puts(s);
    free(s);

    // EJ3
    char *palos[] = {"oro", "copa", "espada", "basto"};
    size_t n;
    carta_t **cartas = tirar_reyes(&n);
    for(size_t i = 0; i < n; i++)
        printf("%d %s\n", cartas[i]->valor, palos[cartas[i]->palo]);

    for(size_t i = 0; i < n; i++)
        free(cartas[i]);
    free(cartas);

    return 0;
}

// Esta es una posible implementaciÃ³n, poco realista, mazo infinito aleatorio
carta_t *sacar_carta_del_mazo() {
    carta_t *c = malloc(sizeof(carta_t));
    if(c == NULL) return NULL;
    c->palo = rand() % 4;
    c->valor = rand() % 12 + 1;
    return c;
}