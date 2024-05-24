#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stdbool.h>
#include <stddef.h> //para incluir size_t

conjunto_t *conjunto_crear();
void conjunto_destruir(conjunto_t *c);

void conjunto_destruir(conjunto_t *c)
bool conjunto_agregar(conjunto_t *c, int elem);
bool conjunto_pertenece(conjunto_t *c, int elem);





#endif