#include <stdio.h>

//programa para contar mayusuclas ingresadas por el usuario
int main(){

	int c;
	size_t mayus = 0;
	while( (c = getchar()) != EOF){ //EOF == crl+d
		if(c >= 'A' && c <= 'Z'){
			mayus ++;
		}
	}
	
	printf("%zd\n", mayus);
	return 0;

}