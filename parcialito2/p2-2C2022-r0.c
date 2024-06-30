#include <stdint>
#include <stdbool>
#include <stdlib.h>


//EJ2 
int **matriz_crear(size_t filas, size_t columnas){
  int **m = malloc(filas*sizeof(int *));
  if(m == NULL){
    return NULL;
  }

  for(size_t i = 0; i < filas; i++){
    m[i] = malloc(columnas*sizeof(int));
    if(m[i] == NULL){
        for(size_t j = 0; j < i; j++){
            free(m[j]);
        }
        free(m);
        return NULL;
    }
  }

  return m;
}

void matriz_destruir(int **m, size_t filas, size_t columnas){
    for(size_t j = 0; j < filas; j++){
        free(m[j]);
    }
    free(m);
}

///////EJ3
char *leer_palabra() {
    char *cadena_palabra = NULL;
    size_t letra_leida;
    int i = 0;

    while ((letra_leida = getchar()) != EOF) {
        if (isalnum(letra_leida) == false) {
            break;
        }

        char *puntero_auxiliar = realloc(cadena_palabra, i + 1);

        if (puntero_auxiliar == NULL) {
            free(cadena_palabra);
            return NULL;
        }

        cadena_palabra = puntero_auxiliar;
        cadena_palabra[i] = letra_leida;
        i++;
    }

    return cadena_palabra;
}

int main(){

	char *cadena_palabra = leer_palabra();
	
    puts(cadena_palabra);
    free(cadena_palabra);

	return 0;
}


