#include <stddef.h>
#include <stdbool.h>

//EJ1
typedef struct {
    struct nodo *prim;
} lista_t;

struct nodo {
    struct nodo *sig; 
    int dato;
};

//CORREGIR
void unir_listas_ordenadas(lista_t *d, lista_t *o){

    if(o->prim == NULL) return;
    if(d->prim == NULL){
        d->prim = o->prim;
        return;
    }

    struct nodo *actuald = d->prim;
    struct nodo *anteriord = NULL;
    struct nodo *actualo = o->prim;

    while(actualo != NULL){

        if(actualo->dato < actuald->dato){
            if(anteriord == NULL){
                d->prim = actualo;
                anteriord = actualo;
                o->prim = actualo->sig;
                actualo->sig = actuald;
            }
            else{
                anteriord->sig = actualo;
                actualo = actualo->sig;
                anteriord = anteriord->sig;
                anteriord->sig = actuald;
                o->prim = actualo;
            }

        }
        else if(actuald->dato < actualo->dato){
            anteriord = actuald;
            actuald = actuald->sig;
        }
        else{ //si son iguales incremento los dos
            anteriord = actuald;
            actuald = actual->sig;
            actualo = actualo->sig;
        }
    }

    o->prim = NULL;
    free(o);
}

//EJ2
void *buscar(void *v[], size_t n, const void *e, int (*cmp)(const void *a, const void *b)){

    for(size_t i = 0; i < n; i++){
        if(!cmp(v[i], e)){
            return v[i];
        }
    }

    return NULL;
}

//EJ3
bool es_potencia(int n, int b) {
    //**n es potencia de b si al dividir n/b en algun momento se llega a 1.

    //caso base
    if (n == 1) {
        return true;
    }
    if (n < 1 || b == 0) {
        return false;
    }
    if (n % b != 0) {
        return false;
    }

    //caso recursivo
    return es_potencia_de(n / b, b);
}








