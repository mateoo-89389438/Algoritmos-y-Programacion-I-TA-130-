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
lista_t *lista_crear(){
	lista_t *l = malloc(sizeof(lista_t));
	if(l == NULL){
		return NULL
	}

	l->prim = NULL;
	return l;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *dato)){
	
	while(l->prim != NULL){
		struct nodo *actual = l->prim;
		destruir_dato(actual->dato);
		l-prim = actual->sig;
		free(actual);
	}
	free(l);
}


bool lista_es_vacia(const lista_t *l){
	if( l->prim != NULL){
		return false;
	}
	return true;
}

bool lista_insertar_comienzo(lista_t *l, void *dato){
	struct nodo *n = crear_nodo(dato, l->prim);
	if(n == NULL) return false;

	l->prim = n;
	return true;
}

bool lista_insertar_final(lista_t *l, void *dato){

	//verifico si la lista esta vacia
	if(lista es vacia(l)){
		lista_insertar_comienzo(l, dato);
		return true;
	}

	//parece que la lista no estaba vacia ... 
	struct nodo *nuevo = crear_nodo(dato, NULL);
	if(nuevo == NULL)	return false;
	struct nodo *actual = l->prim;
	while(actual->sig != NULL){
		actual = actual->sig;
	}

	actual->sig = nuevo;n
	free(nuevo);
	return true;
}

void *lista_extraer_primero(lista_t *l){
	struct nodo *n = l->prim;
	l->prim = l->prim->sig;

	void *dato = l->prim->dato;
	free(prim);
	return dato;
}

void *lista_extraer_ultimo(lista_t *l){

	if(lista_es_vacia(l)){
		return NULL;
	}

	struct nodo *actual = l->prim;
	strcut nodo *siguiente = l->prim->sig;
	while(actual->sig != NULL){
		actual = actual->sig;
		siguiente = actual->sig;
	}
	actual->sig = NULL;
	return siguiente->dato;
}


void *lista_buscar(const lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b)){

	struct nodo *actual = l->prim;
	while(actual != NULL){
		if(!cmp(actual->dato, dato)){
			return actual->dato;
		}
		actual = actual->sig;
	}

	//parece que el dato no estaba
	return NULL;
}



void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b)){

	if( lista_esta_vacia(l)){
		return NULL;
	}

	struct nodo *actual = l->prim;
	struct nodo *anterior = NULL;

	while(actual != NULL){
		if(!cmp(actual->dato, dato)){
			void *dato_borrado = actual->dato;
			//si hay que borrar justo el primero es un caso particular
			if(anterior == NULL){
				l->prim = actual->sig;
			}
			else{
				anterior->siguiente = actual->siguiente;
			}
			free(actual);
			return dato_borrado;
		}
		anterior = actual;
		actual = actual->sig;
	}
	return NULL;
}

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra){

	struct nodo *actual = l->prim;
	while(actual != NULL){
		if(!visitar(actual->dato, extra)){
			return;
		}
		actual = actual->sig;
	}
}



















