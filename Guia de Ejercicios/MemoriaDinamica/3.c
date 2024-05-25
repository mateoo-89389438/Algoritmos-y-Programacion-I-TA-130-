#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#define MAX_STRING 100

char *strip_comment(char *string, char c){
	char *copia = malloc(MAX_STRING*sizeof(char));
	if(copia == NULL){
		return NULL;
	}

	size_t i;
	for(i = 0; string[i] != c; i++){
		copia[i] = string[i];
	}
	copia[i] = '\0';

	return copia;
}

int main(){
	char *cadenaCortada = strip_comment("Esto va ; esto no va", ';');
	printf("%s\n", cadenaCortada);

	free(cadenaCortada);
	return 0;
}

