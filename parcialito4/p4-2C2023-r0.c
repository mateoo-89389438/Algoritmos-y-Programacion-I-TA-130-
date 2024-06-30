#include <stdlib.h>

//EJ1
struct nodo { 
    void *dato; 
    struct nodo *sig; 
}; 

typedef struct { 
    struct nodo *prim; 
} lista_t;

lista_t *lista_clonar(const lista_t *l, void *(*clonar_dato)(const void *)){
    if(l->prim == NULL){
        return NULL;
    }
    if(l->prim == NULL) {
        clon->prim = NULL;
        return clon;
    }

    lista_t *c = malloc(sizeof(lista_t));
    if( c == NULL){
        return NULL;
    } 
    
    c->prim = NULL;

    struct nodo *actual_l = l->prim;
    struct nodo *actual_c = c->prim;

    while(actual_l != NULL){
        struct nodo *nuevo = malloc(sizeof(struct nodo));
        //deberia liberar todos los nodos anteriores
        nuevo->dato = clonar_dato(actual_l->dato);
        nuevo->sig = NULL;
        if(c->prim == NULL){ //es el primero de la lista de clonados
            c->prim = nuevo;
        }
        else{
            actual_c->sig = nuevo;
        }
        actual_c = nuevo;
        actual_l = actual_l->sig;
    }
    return c;
}


//EJ3
float sumar_elementos(const float v[], size_t n){

    if(n == 1){
        return v[0];
    }

    return sumar_elementos(v+1, n-1) + v[0];
}





















