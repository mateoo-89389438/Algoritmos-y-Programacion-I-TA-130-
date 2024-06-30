#include <stdlib.h>
#include <stdio.h>


//EJ1
typedef struct {
    struct nodo *prim;
} lista_t;

struct nodo {
    struct nodo *sig; 
    int dato;
};

lista_t *lista_desde_vector(const int v[], size_t n){

	lista_t *l = malloc(sizeof(lista_t));
	if( l == NULL) return NULL;
	l->prim = NULL;

	if( n == 0){
		return l;
	}

	struct nodo *actual = malloc(sizeof(struct nodo));
	if( actual == NULL){
		lista_destruir(l);
		return NULL;
	}
	actual->dato = v[0];
	actual->sig = NULL;
	l->prim = actual;
	
	for(size_t i = 1; i < n; i++){

		struct nodo *nuevo = malloc(sizeof(struct nodo));
		if( nuevo == NULL){
			lista_destruir(l);
			return NULL;
		}
		nuevo->sig = NULL;
		nuevo->dato = v[i];
		actual->sig = nuevo;
		actual = nuevo;
	}

	return l;
}

//EJ2
int arreglo_reducir(const int arreglo[], size_t n, int (*f)(int a, int b)) {
	
    if (n == 0) {
        return 0;
    }
    
    int resultado = arreglo[0];
    
    for (size_t i = 1; i < n; i++) {
        resultado = f(resultado, arreglo[i]);
    }
    
    return resultado;
}


//EJ3

float sumar_elementos(float v[], size_t n){

	//caso base
	if( n == 0){
		return 0;
	}

	//caso recursivo
	return v[0] + sumar_elementos(v+1, n-1);
}