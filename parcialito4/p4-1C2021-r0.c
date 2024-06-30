#include <stdbool.h>



typedef struct {
      struct nodo *prim;
} lista_ordenada_t;


struct nodo {
      struct nodo *sig;
      int dato;
};

bool lista_ordenada_completar(lista_ordenada_t *l){

      if(l->prim == NULL || l->prim->sig == NULL){
            return true;
      }

      struct nodo *actual = l->prim;
      while(actual->sig != NULL){
            struct nodo *siguiente = actual->sig;
            if((actual->dato + 1) < siguiente->dato){
                  //creo un nodo
                  struct nodo *nuevo = malloc(sizeof(struct nodo));
                  if(nuevo == NULL) return false;
                  nuevo->dato = (actual->dato + 1);
                  nuevo->sig = siguiente;
                  actual->sig = nuevo;
            }
            else if(actual->dato == siguiente->dato){
                  //hay que borrar el siguiente
                  actual->sig = siguiente->sig;
                  free(siguiente);
            }
            else{
                  actual->actual->sig;
            }
      }
      return true;
}



