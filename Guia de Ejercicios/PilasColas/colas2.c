/*
Escribir un programa 'tail' que recibe una ruta a un archivo de texto y un
numero 'n', y que imprima por pantalla las ultimas 'n' líneas del archivo. No
está permitido almacenar todo el archivo en memoria ni recorrer el archivo
más de una vez.
*/
#include <stdio.h>
#include <string.h>

#define MAX_STRING 100

int main(in argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr, "Uso: %s <archivo> <n>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen( argv[1], "rt");
	if( f == NULL){
		return 1;
	}

	int n = atoi(argv[2]);

	cola_t *c = cola_crear();
	if( c == NULL){
		fclose(f);
		return 1;
	}

	char aux[MAX_STRING];
	for(size_t i = 0; fgets(aux, MAX_STRING, f) != NULL && i < n; i++){
		//las 2 condiciones son para no leer demás ni de menos
		cola_encolar(c, strdup(aux));
	}

	while( fgets(aux, MAX_STRING, f) != NULL){
		free(cola_desencolar(c));
		cola_encolar(c, strdup(aux));
	}

	//imprimo los elementos
	while( !cola_esta_vacia(c)){
		char *s = cola_desencolar(c);
		fprintf(stdout, "%s\n", s);
		free(s);
	}
	
	cola_destruir(c);
	fclose(f);
	return 0;
}

















