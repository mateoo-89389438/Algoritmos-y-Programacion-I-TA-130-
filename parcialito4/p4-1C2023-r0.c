#include <stdbool.h>

struct nodo { 
    int dato; 
    int verificacion; 
    struct nodo *siguiente; 
};

typedef struct{ 
    struct nodo *primero 
} blockchain_t;

//EJ1
bool verificar_blockchain(const blockchain_t *b){

    //hay que verificar que si esta vacia
    if(b->primero == NULL){
        return true;
    }

    //puedo seguir porque ya se que al menos hay un nodo en la lista si o si
    struct nodo *actual = b->primero;
    while(actual->siguiente != NULL){
        if(actual->verificacion != (actual->dato + actual->siguiente->verificacion)){
            return false;
        }
        actual = actual->siguiente;
    }

    return actual->dato == actual->verificacion;
}

//EJ2
struct alumno {
    char nombre[MAX_NOMBRE]; 
    int padron; 
};

struct alumno *alumnos_antisociales(const struct alumno alumnos[], size_t nalumnos, const int padrones_grupos[], size_t npadrones, size_t *nantisociales){
    *nantisociales = nalumnos - npadrones;

    struct alumno *antisociales = malloc((*nantisociales) * sizeof(struct alumno));
    if(antisociales == NULL) return NULL;

    size_t i = 0, j = 0, k = 0;
    
    while(j < npadrones){

        if( alumnos[i].padron == padrones_grupos[j]){
            i++;
            j++;
        }
        else{
            antisociales[k] = alumnos[i]; //se pueden copiar estructuras directo no hace falta strcpy ni malloc
            k++
            i++;
        }
    }

    while(k < nalumnos){
        antisociales[k] = alumnos[i]; //se pueden copiar estructuras directo no hace falta strcpy ni malloc
        k++
        i++;
    }


    return p;

}


//EJ3
unsigned int dividir(unsigned int a, unsigned int b){

    //caso base
    if(a < b){
        return 0;
    }

    return dividir(a - b, b) + 1; 
}




















