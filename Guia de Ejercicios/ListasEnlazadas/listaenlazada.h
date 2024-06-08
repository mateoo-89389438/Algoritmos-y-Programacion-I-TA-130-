#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <stdlib.h>
#include <stdbool.h>

struct nodo {
	void *dato;
	struct nodo *sig;
};


typedef struct {
	struct nodo *prim;
} lista_t;


////////////////////////////////////////////////////////////////////////////////////
//EJ1
lista_t *lista_crear();

void lista_destruir(lista_t *l, void (*destruir_dato)(void *dato));


bool lista_es_vacia(const lista_t *l);

bool lista_insertar_comienzo(lista_t *l, void *dato);

bool lista_insertar_final(lista_t *l, void *dato);

void *lista_extraer_primero(lista_t *l);

void *lista_extraer_ultimo(lista_t *l);

void *lista_buscar(const lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b));

void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b));

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra);


//EJ2
void lista_mapear(lista_t *l, void *(*f)(void *dato, void *extra), void *extra);

lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra);

bool lista_extender(lista_t *a, const lista_t *b);

void **lista_a_vector(const lista_t *l, size_t *n);





















#endif