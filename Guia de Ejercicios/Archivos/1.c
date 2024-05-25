#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100


int main(int argc, char *argv[]){

    if(argc != 3){
        fprintf(stderr, "Uso: %s <archivo> \"centilena\"\n", argv[0]);
        return 1;
    }

    size_t len = strlen(argv[2]);
    char *centinela = malloc((len + 2) * sizeof(char)); // \n y \0
    if(centinela == NULL){
        return 1;
    } 

    memcpy(centinela, argv[2], len);
    centinela[len] = '\n';
    centinela[len+1] = '\0';


    FILE *fo = fopen(argv[1], "w");
    if (fo == NULL){
        free(centinela);
        return 1;
    }

    char buffer[MAX_STRING];

    while( fgets(buffer, MAX_STRING, stdin) != NULL){
        if( ! strcmp(buffer, centinela)){
            break;
        }
        fputs(buffer, fo);
    }

    fclose(fo);
    free(centinela);

    return 0;
}