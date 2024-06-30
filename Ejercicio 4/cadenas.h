#ifndef CADENAS_H
#define CADENAS_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_STRING 100

//Compara si dos cadenas son iguales 
bool son_iguales(const char a[], const char b[]);

//lee una linea de la terminal con getchar()
bool leer_linea(char s[]);

//lee una linea del descriptor de archivo con read()
bool leer_linea_archivos(char s[], int sockfd);

//devuelve por el nombre la cantidad de campos de una linea ingresada 
size_t cantidad_campos(const char s[]);

//devuelve el campo c de la cadena s y lo guarda en la cadena campo
bool extraer_campo(char campo[], const char s[], size_t c);

//busca si la cadena s es alguna de las n_opciones cadenas del vector de cadenas opciones
// devuelve el índice de opciones en el cual se encontró o n_opciones si no se encontró 
size_t buscar_cadena(const char s[], char opciones[][MAX_STRING], size_t n_opciones);

#endif



