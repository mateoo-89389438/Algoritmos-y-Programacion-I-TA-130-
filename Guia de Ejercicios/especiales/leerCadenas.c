#include <stdio.h>

#define MAX_CADENA 50

int main(){
	char cadena[MAX_CADENA];
	while( fgets(cadena, MAX_CADENA, stdin) != NULL){
		printf("#%s#\n", cadena);
	}
	return 0;
}