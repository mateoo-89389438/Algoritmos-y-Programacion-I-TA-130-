#include <stdio.h>

//programa para contar caracteres ingresados por el usuario
int main(){

	int c;
	size_t caracteres = 0;
	size_t enters = 0;
	while( (c = getchar()) != EOF){ //EOF == crl+d
		caracteres ++;
		if(c == '\n'){
			enters ++;
			caracteres--; //esto no deberia estar pero mi compu cuenta el enter
		}
	}
	
	printf("%zd\t%zd\t\n", caracteres);
	return 0;

}