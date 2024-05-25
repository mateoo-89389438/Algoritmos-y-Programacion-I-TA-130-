#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#define MAX_STRING 100

//NO FUNCIONA
char *left_trim(char *string){
	char *copia = malloc(MAX_STRING*sizeof(char));
	if(copia == NULL){
		return NULL;
	}

	size_t i;

	for(i = 0; string[i] != '\0'; i++){
		if(string[i] != ' '){
			break;
		}
	}
  
  size_t j;
	for(j = i; string[j] != '\0'; j++){
		copia[j] = string[j];
	}
	copia[j] = '\0';

	return copia;
}

int main(){
	char *cadenaSinEsp = left_trim("     la izquierda  ");
	printf("%s\n", cadenaSinEsp);

	free(cadenaSinEsp);
	return 0;
}

