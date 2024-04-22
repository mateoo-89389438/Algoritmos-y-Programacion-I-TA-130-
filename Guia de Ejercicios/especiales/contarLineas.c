#include <stdio.h>

//programa para contar lineas ingresadas por el usuario
int main(){

	int c;
	size_t enters = 0;
	while( (c = getchar()) != EOF){ //EOF == crl+d
		if(c == '\n'){
			enters ++;
		}
	}
	
	printf("%zd\n", enters);
	return 0;

}