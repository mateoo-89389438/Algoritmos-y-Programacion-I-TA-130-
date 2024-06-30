#include <stdlib.h>

//EJ1
struct nodo { 
    void *dato; 
    struct nodo *sig; 
}; 

typedef struct { 
    struct nodo *prim; 
} lista_t;

void *lista_borrar(lista_t *l, void *e, int (*cmp)(void *a, void *b)){

    if(l->prim == NULL){
        return NULL;
    }

    struct nodo *actual = l->prim;
    struct nodo *anterior = NULL;
    while(actual != NULL){
        if(!cmp(actual->dato, e)){
            if(anterior == NULL){
                l->prim = actual->sig;
            }
            else{
                anterior->sig = actual->sig;

            }
            actual->sig = NULL;
            void *dato = actual->dato;
            free(actual);
            return dato;
        }
        anterior = actual;
        actual = actual->sig;
    }
    return NULL;
}

//EJ2
int *marmoles_todavia_peligrosos(int marmoles_peligrosos[], size_t n_marmoles_peligrosos,
int marmoles_reparados[], size_t n_marmoles_reparados,
size_t *n_marmoles_todavia_peligrosos){

    *n_marmoles_todavia_peligrosos = n_marmoles_peligrosos - n_marmoles_reparados;
    
    int *marmoles_todavia_peligrosos = malloc((*n_marmoles_todavia_peligrosos)*sizeof(int));
    if(marmoles_todavia_peligrosos == NULL) return NULL;

    size_t mp = 0, mr = 0, msr = 0;

    while(mr < n_marmoles_reparados){
        if(marmoles_peligrosos[mp] < marmoles_reparados[mr]){
            marmoles_todavia_peligrosos[msr] = marmoles_peligrosos[mp];
            mp++;
            msr++;
        }
        else{
            mp++;
            mr++;
        }
    }

    while(mp < n_marmoles_peligrosos){
        marmoles_todavia_peligrosos[msr] = marmoles_peligrosos[mp];
        mp++;
        msr++;
    }

    return marmoles_todavia_peligrosos;
}

//EJ3
float sumar_elementos(float v[], size_t n){

    //caso base
    if(n == 0){
        return 0;
    }

    //caso recursivo
    return v[0] + sumar_elementos(v+1, n-1);
}














