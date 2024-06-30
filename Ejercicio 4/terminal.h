#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINEA 100

typedef struct {
    // El prompt:
    char prompt[MAX_LINEA];

    // El historial, la cantidad de cadenas y el índice de la línea que se está editando:
    char (*historial)[MAX_LINEA];
    int nhistorial, ihistorial;

    // La línea que se está editando, su longitud y la posición del cursor:
    char *linea;
    int nlinea, ilinea;

    // La copia de la configuración de terminal original:
    struct termios config_original;
} terminal_t;

// Crea una estructura terminal:
terminal_t *terminal_crear(const char *prompt);

// La destruye:
void terminal_destruir(terminal_t *t);

//lee un caracter por la terminal, hace lo necesario y lo devuelve
int terminal_leer(terminal_t *t);

//imprime la linea, maneja el cursor y el historial
void terminal_imprimir(const terminal_t *t);

//devuelve una linea del historial de la terminal
char *terminal_historial(const terminal_t *t, int i);


#endif 


