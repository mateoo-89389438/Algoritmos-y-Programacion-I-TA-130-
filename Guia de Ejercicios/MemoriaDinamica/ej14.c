//14. a) Implementá una función que retorne una matriz dinámica, de un tamaño pasado como argumento, siendo la misma inicializada con: ceros.


#include <stdio.h>
#include <stdlib.h>

// creo 3 funciones, una para crear la matriz pidiendo memoria, otra para librerar la memoria y otra para imprimir la matriz. 


//funcion1: para crear la matriz pidiendo memoria
int **crearMatriz(int filas, int columnas){
    //pido la memoria para las filas
    int **matriz = malloc(filas * sizeof(int *));
    if (matriz == NULL){
        printf("Error al asignar memoria para filas");
        exit(EXIT_FAILURE);
    }
    
    //pido memoria para las columnas
    for (int i= 0; i < filas; i++){
        matriz[i] = malloc(columnas*sizeof(int));
        if (matriz[i] == NULL){
            printf("Error al asignar memoria para filas");
            exit(EXIT_FAILURE);
        }
        
        //relleno la matriz con ceros
        for (int j=0; j<columnas; j++){
            matriz[i][j] = 23;
        }
    }
    return matriz;
}

//funcion2; para imprimir la matriz
void imprimirMatriz(int **matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}


//funcion3: para liberar la memoria pedida
void librerarMatriz(int **matriz, int filas){
    for (int k=0; k<filas; k++){
        free(matriz[k]);
    }
}


int main(){
    int filas = 3;
    int columnas = 4;
    
    int **matriz = crearMatriz(filas, columnas);
    imprimirMatriz(matriz,filas, columnas);
    librerarMatriz(matriz, filas);
    
    return 0;
}