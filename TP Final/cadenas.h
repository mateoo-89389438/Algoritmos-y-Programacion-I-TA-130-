#ifndef CADENAS_H
#define CADENAS_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_STRING 100

// Compara si dos cadenas son iguales 
bool son_iguales(const char a[], const char b[]);

// Lee una linea de la terminal con getchar() y la devuelve por la interfaz
bool leer_linea(char s[]);

// Lee una linea del descriptor de archivo con read() y la devuelve por el nombre
char *leer_linea_archivos(int fd);

// Devuelve la cantidad de campos de una linea ingresada por el nombre 
size_t cantidad_campos(const char s[]);

// Devuelve el campo numero c de la cadena s y por la interfaz en la cadena campo
bool extraer_campo(char campo[], const char s[], size_t c);

// Busca si la cadena s es alguna de las n_opciones cadenas del vector de cadenas opciones
// Devuelve por el nombre el índice del vector 'opciones' en el cual se encontró o n_opciones si no se encontró 
size_t buscar_cadena(const char s[], char opciones[][MAX_STRING], size_t n_opciones);

#endif



