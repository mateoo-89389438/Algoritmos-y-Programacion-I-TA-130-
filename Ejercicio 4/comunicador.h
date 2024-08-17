#ifndef COMUNICADOR_H
#define COMUNICADOR_H

#include <stdbool.h>

typedef struct comunicador comunicador_t;

// Crea el comunicador:
comunicador_t *comunicador_crear();

// Lo destruye:
void comunicador_destruir(comunicador_t *c);

// Intenta conectar el comunicador a esa dirección y puerto. Si falla devuelve false:
bool comunicador_conectar(comunicador_t *c, const char *direccion, int puerto);

// True si el comunicador está conectado:
bool comunicador_esta_conectado(const comunicador_t *c);

// Devuelve el mensaje de error del comunicador (si falló). Es una cadena estática:
char *comunicador_get_error(const comunicador_t *c);

// Devuelve el descriptor de archivo del socket con el servidor:
int comunicador_get_sockfd(const comunicador_t *c);

// Espera por datos tanto en el socket como por stdin. Si llegaron datos por
// stdin devuelve 0, si llegaron datos por el socket devuelve el descriptor de
//archivo del socket, y si hubiera una falla devuelve -1 (y desconecta el
//comunicador):
int comunicador_esperar_datos(comunicador_t *c);

#endif
