#include "CONJUNTO.H"

#include <stdbool.h>
#include <stdlib.h>

struct conjunto {
	int *v; //v son los elementos del conjunto
	size_t n; // n es la cnatidad de elementos del conjunto
	// si n == 0 entonces v == NULL y viceversa
	// 1) Desordenado, repetido
	// 2) Ordenado, no repetidos
	// 3) Ordenado, no repetidos
};

conjunto_t *conjunto_crear(){
	conjunto_t *c = malloc(sizeof(conjunto_t));
	if(c == NULL){
		return NULL;
	}

	c->v = NULL;
	c->n = 0;

	return c;
}


void conjunto_destruir(conjunto_t *c){
	free(c->v);
	free(c);
}

//no tengo que verificar nada pq para eso defini el invariante de representacion
bool conjunto_es_vacio(const conjunto_t *c){
	if( c->n == 0){
		return true;
	}
	return false;
}


bool conjunto_agregar(conjunto_t *c, int elem){
	//primero hay que pedir memoria para el nuevo elemento
	int *aux = realloc(c->v, (c->v+1) * sizeof(int));
	if( aux == NULL){ //no hay que liberar nada
		return false;
	}

	c->v = aux;

	//meto el elemento al final del vector
	c->v[c->n] = elem;
	//aumento el largo del vector
	c->n++;
	return true;
}

bool conjunto_pertenece(conjunto_t *c, int elem){
	for(size_t i = 0; i < (c->n); i++){
		if( c->v[i] = elem){
			return true;
		}
	}
	return false;
}





































