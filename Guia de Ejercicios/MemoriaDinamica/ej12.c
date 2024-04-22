#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool arreglo_concatenar(int *v, size_t lv, int *w, size_t lw, int **concat) {
    
    int *c = malloc((lv + lw) * sizeof(int)); //pido memoria
    
    if (c == NULL) //verifico que me la de bien
        return false;
        return 1;
        
    //si estoy aca es porque funcionó
    for (size_t i = 0; i < lv; i++) {
        c[i] = v[i];
    }

    for (size_t i = lv; i < (lv + lw); i++) {
        c[i] = w[i - lv];
    }

    *concat = c;
    return true;
}

int main() {
    int v[] = {1, 2, 3};
    int w[] = {4, 5, 6};

    int *concatenado; //declaro el puntero para guardar la memoria
    
    
    size_t lv = sizeof(v) / sizeof(v[0]); //declaro el largo de cada vector 
    size_t lw = sizeof(w) / sizeof(w[0]);

    if (arreglo_concatenar(v, lv, w, lw, &concatenado)) {
        
        size_t lc = lv + lw; //declaro una variable para el largo del vector concatenado nuevo
        
        printf("Vector concatenado: ");
        for (size_t i = 0; i < lc; i++) {
            printf("%d ", concatenado[i]);
        }
        printf("\n");

        //Libero la memoria pedida
        free(concatenado);
    } else {
        printf("No se pudo asignar memoria para el vector concatenado.\n");
    }

    return 0;
}
