#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////EJ2

struct vector{
    int *valores;
    size_t len;
};

typedef struct vector vector_t;

vector_t *vector_clonar(const vector_t *v){
    
    vector_t *clon = malloc(sizeof(vector_t));
    
    if (clon == NULL){
        return NULL;
    }

    clon->valores = malloc((v->len) * sizeof(int));
    
    if (clon->valores == NULL){
        free (clon);
        return NULL;
    }
    
    memcpy(clon->valores, v->valores, v->len*sizeof(int));
    clon->len = v->len;
    
    return clon;
}



///////EJ3
int *leer_notas(size_t *n) {
    char buffer[100];
    *n = 0;
    int *v = NULL;

    while(fgets(buffer, 100, stdin) != NULL) {

        int nota = atoi(buffer);

        if(nota < 0 || nota > 100)
            break; //"return NULL" no porque se perderia lo que ya se guardo

        int * p = realloc(v, (*n + 1) * sizeof(int));
        if(p == NULL) {
            free(v);
            return NULL;
        }
        v = p;

        v[*n] = nota; //guarda la nota en su lugar
        (*n)++; //incrementa lo apuntado por n
    }

    return v;
}






int main(){

    ////////////////////////main del EJ2//////////////////////
    int vector1[] = {1,2,3,4,6};
    
    vector_t vectorInstancia_1 = {vector1, 5};
    
    vector_t *clon = vector_clonar(&vectorInstancia_1);
    
    for (int i = 0; i < clon->len; i++){
        printf("%d", clon->w[i]);
    }

    // Liberar la memoria del vector clonado
    free(clon->w);
    free(clon);


    //EJ3

    size_t n; //aca se guarda la cantidad total de notas

    int * notas = leer_notas(&n); //aca se guardan las notas
    if(notas == NULL)
        return 1;

    printf("Se leyeron las siguientes %zd notas: \n", n);

    for(size_t i = 0; i < n; i++){
        printf("%d ", notas[i]);
    }

    puts("");
    free(notas); //libero la memoria del arreglo de notas

    return 0;
}
