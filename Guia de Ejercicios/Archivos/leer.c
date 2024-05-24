#include <stdio.h>

// ./programa archivo
int main(int argc, char *argv[]) {
    //verifico el numero de argumentos recibidos
    if(argc != 2) {
        //muestro en un mensaje como se deberia operar por terminal
        fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
        return 1;
    }

    //LECTURA
    FILE *fi = fopen(argv[1], "r"); //abre el archivo en modo lectura

    //verifico que se haya abierto el archivo correctamente
    if(fi == NULL) {
        fprintf(stderr, "No puedo abrir \"%s\"\n", argv[1]);
        return 1;
    }

    //imprimo lo leido por lineas
    char aux[100];
    while(fgets(aux, 100, fi) != NULL)
        printf("%s", aux);

    fclose(fi); // cerrar/destruir el archivo

    return 0;
}