#include <stdio.h>
#define MAX_STRING 100

char *readline(FILE *f){
	char *s = malloc(MAX_STRING*sizeof(char));
	if (s == NULL){
		return NULL;
	} 

	int c; //el caracter leido
	size_t i = 0; //la posicion en la que esta leyendo/guardando

	while( (c = fgetc(f)) != EOF && (c != '\0') && (c != '\n')){
		s[i] = c;
		i++;
	}
	s[i] = '\0';

	return s;
}

bool readline(FILE *f, char **cadena){
	char *cadena = malloc(MAX_STRING * sizeof(char));
	if (*cadena == NULL){
		return false;
	}

	int c; //el caracter leido
	size_t i = 0; //la posicion en la que esta leyendo/guardando

	while( (c = fgetc(f)) != EOF && (c != '\0') && (c != '\n')){
		*cadena[i] = c;
		i++;
	}
	*cadena[i] = '\0';

	return true;

}



int main(int argc, char * argv[]){

	if(argc != 2){
		fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
		return 1;
	}

	//...


	return 0;
}



















