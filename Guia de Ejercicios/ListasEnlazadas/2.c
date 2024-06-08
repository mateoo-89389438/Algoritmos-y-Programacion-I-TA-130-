#include "listaenlazada.h"

#include <stdlib.h>
#include <stdbool.h>

//funcion auxiliar interna de la implementacion
static struct nodo *crear_nodo(void *dato, struct nodo *sig){

	struct nodo *n = malloc(sizeof(struct nodo));
	if( n == NULL) return NULL;

	n->dato = dato;
	n->sig = sig;
	return n;
}

////////////////////////////////////////////////////////////////////////////////////

void lista_mapear(lista_t *l, void *(*f)(void *dato, void *extra), void *extra){

	struct nodo *actual = l->prim;
	while(actual != NULL){
		actual->dato = f(actual->dato, extra);
		actual = actual->sig;
	}
}


lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra) {

	lista_t *p = lista_crear();
	if (p == NULL) {
		return NULL;
	}

	struct nodo *actual = l->prim;
	struct nodo *anterior = NULL;

	while (actual != NULL) {
		struct nodo *siguiente = actual->sig; // guardo el siguiente nodo antes de modificarlo

		if( f(actual->dato, extra) ) {
			// primero lo saco de la lista l
			if (anterior == NULL) { // si es el primer nodo
				l->prim = siguiente;
			} 
			else { // si no es el primer nodo
				anterior->sig = siguiente;
			}

			// ahora lo agrego a la lista p
			lista_insertar_final(p, actual->dato);
			free(actual); // libero el nodo de la lista original
		} 
		else {
			anterior = actual;
		}

		actual = siguiente;
	}

	return p;
}


bool lista_extender(lista_t *a, const lista_t *b){

	struct nodo *actual_a = a->prim;
	struct nodo *actual_b = b->prim;
	
	//caso particular si alguna es vacia
	if(lista_es_vacia(a)){
		if(lista_es_vacia(b)){
			return true;
		}

		a->prim = crear_nodo(actual_b, NULL);
		if(a->prim == NULL){
			return false;
		}
		actual_a = a->prim;
		actual_b = actual_b->sig;
	}


	// voy hasta el final de la lista `a`
	while(actual_a->sig != NULL){
		actual_a = actual_a->sig;
	}
	while(actual_b != NULL){
		actual_a->sig = crear_nodo(actual_b->dato, NULL);
		if(actual_a->sig == NULL){
			return NULL;
		}
		actual_b = actual_b->sig;
		actual_a = actual_a->sig;
	}

	return true;
}

void **lista_a_vector(const lista_t *l, size_t *n){

	struct nodo *actual = l->prim;
	void **v = NULL;
	*n = 0;

	//cuento los elementos de la lista asi ya me guardo el n
	while(actual != NULL){
		(*n)++;
		actual = actual->sig;
	}


	v = malloc((*n) * sizeof(void *));
	if( v == NULL){
		return NULL;
	}

	//llevo actual de nuevo al principio para arrancar a copiar
	actual = l->prim;

	for(size_t i = 0; actual != NULL; i++){
		v[i] = actual->dato;
		actual = actual->sig;
	}

	return v;
}






















